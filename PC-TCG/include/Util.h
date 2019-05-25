#pragma once

#define NOMINMAX

#include <SFML/Network.hpp>
#include <memory>
#include <queue>
#include <Windows.h>

namespace GBAConnect {
	int GetTransferTime(char cmd);

	template <typename T>
	std::unique_ptr<T> MoveFromFront(std::queue<std::unique_ptr<T>>& ptrs);

	std::unique_ptr<sf::TcpSocket> GetNextSocket();
	std::unique_ptr<sf::TcpSocket> GetNextClock();

	void GBAConnectionWaiter();
	void GBAConnectionWaiter_Shutdown();
}
