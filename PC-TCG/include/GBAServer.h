#pragma once

#include "../include/Constants.h"
#include "../include/JoybusEnums.h"
#include "../include/Util.h"
#include "../include/Threads.h"

#include <SFML/Network.hpp>
#include <array>
#include <chrono>

namespace GBAConnect
{
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

		std::chrono::steady_clock::time_point m_LastTimeSlice = std::chrono::steady_clock::time_point::min();
		bool m_IsBooted = false;
	};
}