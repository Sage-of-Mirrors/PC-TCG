#pragma once

#define NOMINMAX

#include <Windows.h>

#include "../include/Util.h"
#include "../include/JoybusEnums.h"

static int GetTransferTime(char cmd) {
	uint64_t bytes_transferred = 0;

	switch (cmd) {
	case JoybusCommand::RESET:
	case JoybusCommand::STATUS:
		bytes_transferred = 4;
		break;
	case JoybusCommand::READ:
		bytes_transferred = 6;
		break;
	case JoybusCommand::WRITE:
		bytes_transferred = 1;
		break;
	default:
		bytes_transferred = 1;
		break;
	}

	return static_cast<int>(bytes_transferred / (std::max(s_num_connected, 1) * BYTES_PER_SECOND));
}

static void GBAConnectionWaiter() {
	IsServerRunning = true;

	sf::TcpListener server;
	sf::TcpListener clock_server;

	if (server.listen(0xd6ba) != sf::Socket::Status::Done) {
		return;
	}
	if (server.listen(0xc10c) != sf::Socket::Status::Done) {
		return;
	}

	server.setBlocking(false);
	clock_server.setBlocking(false);

	auto new_client = std::make_unique<sf::TcpSocket>();

	while (IsServerRunning) {
		if (server.accept(* new_client) == sf::Socket::Status::Done) {
			std::lock_guard<std::mutex> lk(s_cs_gba);
			s_waiting_socks.push(std::move(new_client));

			new_client = std::make_unique<sf::TcpSocket>();
		}

		if (clock_server.accept(*new_client) == sf::Socket::Status::Done) {
			std::lock_guard<std::mutex> lk(s_cs_gba_clk);
			s_waiting_clocks.push(std::move(new_client));

			new_client = std::make_unique<sf::TcpSocket>();
		}

		Sleep(1);
	}
}

void GBAConnectionWaiter_Shutdown() {
	IsServerRunning = false;

	if (s_connection_thread.joinable()) {
		s_connection_thread.join();
	}
}

template <typename T>
static std::unique_ptr<T> MoveFromFront(std::queue<std::unique_ptr<T>>& ptrs) {
	if (ptrs.empty()) {
		return nullptr;
	}

	std::unique_ptr<T> ptr = std::move(ptrs.front());
	ptrs.pop();

	return ptr;
}

static std::unique_ptr<sf::TcpSocket> GetNextSocket() {
	std::lock_guard<std::mutex> lk(s_cs_gba);
	return MoveFromFront(s_waiting_socks);
}

static std::unique_ptr<sf::TcpSocket> GetNextClock() {
	std::lock_guard<std::mutex> lk(s_cs_gba_clk);
	return MoveFromFront(s_waiting_clocks);
}