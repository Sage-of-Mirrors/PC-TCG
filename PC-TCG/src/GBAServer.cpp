#include "Util.cpp"
#include "..\include\GBAServer.h"
#include "..\include\JoybusEnums.h"

#include <array>

GBAServer::GBAServer() {
	if (!s_connection_thread.joinable()) {
		s_connection_thread = std::thread(GBAConnectionWaiter);
	}

	s_num_connected = 0;
}

GBAServer::~GBAServer() {
	Disconnect();
}

void GBAServer::Disconnect() {
	if (m_Client) {
		s_num_connected--;
		m_Client->disconnect();
		m_Client = nullptr;
	}

	if (m_ClockSync) {
		m_ClockSync->disconnect();
		m_ClockSync = nullptr;
	}

	m_LastTimeSlice = 0;
	m_IsBooted = false;
}

void GBAServer::ClockSync() {
	if (!m_ClockSync) {
		if (!(m_ClockSync = GetNextClock())) {
			return;
		}
	}

	int32_t time_slice = 0;

	if (m_LastTimeSlice == 0) {
		s_num_connected++;
	}
	else {

	}

	char bytes[4] = { 0, 0, 0, 0 };
	bytes[0] = (time_slice >> 24) & 0xFF;
	bytes[1] = (time_slice >> 16) & 0xFF;
	bytes[2] = (time_slice >> 8)  & 0xFF;
	bytes[3] =  time_slice        & 0xFF;

	sf::Socket::Status socket_status = m_ClockSync->send(bytes, 4);

	if (socket_status == sf::Socket::Status::Disconnected) {
		m_ClockSync->disconnect();
		m_ClockSync = nullptr;
	}
}

bool GBAServer::Connect() {
	if (!IsConnected()) {
		m_Client = GetNextSocket();
	}

	return IsConnected();
}

bool GBAServer::IsConnected() {
	return static_cast<bool>(m_Client);
}

void GBAServer::Send(const char* si_buffer) {
	if (!Connect()) {
		return;
	}

	std::array<char, SEND_MAX_SIZE> send_data;
	for (size_t i = 0; i < send_data.size(); i++) {
		send_data[i] = si_buffer[i];
	}

	char cmd = send_data[0];
	if (cmd != JoybusCommand::STATUS)
		m_IsBooted = true;

	m_Client->setBlocking(false);
	sf::Socket::Status socket_status;

	if (cmd == JoybusCommand::WRITE) {
		socket_status = m_Client->send(send_data.data(), send_data.size());
	}
	else {
		socket_status = m_Client->send(send_data.data(), 1);
	}

	if (socket_status == sf::Socket::Status::Disconnected)
		Disconnect();
}

int GBAServer::Receive(char* si_buffer) {
	if (!m_Client) {
		return  0;
	}

	if (m_IsBooted) {
		sf::SocketSelector socket_selector;
		socket_selector.add(*m_Client);
		socket_selector.wait(sf::milliseconds(1000));
	}

	size_t num_bytes_recieved = 0;
	std::array<char, RECV_MAX_SIZE> recieved_data;

	sf::Socket::Status recieve_status = m_Client->receive(recieved_data.data(), recieved_data.size(), num_bytes_recieved);

	if (recieve_status == sf::Socket::Status::Disconnected) {
		Disconnect();
		return 0;
	}

	if (recieve_status == sf::Socket::Status::NotReady || num_bytes_recieved == 0) {
		m_IsBooted = false;
		return 0;
	}

	for (size_t i = 0; i < recieved_data.size(); i++) {
		si_buffer[i] = recieved_data[i];
	}

	return static_cast<int>(std::min(num_bytes_recieved, recieved_data.size()));
}