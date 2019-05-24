#pragma once

#include "Threads.h"
#include "Util.h"

#include <SFML/Network.hpp>

class GBAServer {
public:
	GBAServer();
	~GBAServer();

	bool Connect();
	bool IsConnected();

	void ClockSync();
	void Send(const char* si_buffer);

	int Receive(char* si_buffer);

private:
	void Disconnect();

	std::unique_ptr<sf::TcpSocket> m_Client;
	std::unique_ptr<sf::TcpSocket> m_ClockSync;

	uint64_t m_LastTimeSlice = 0;
	bool m_IsBooted = false;
};