#pragma once

#include "GBAServer.h"
#include <chrono>

namespace GBAConnect {
	class GBADevice {
		GBAServer m_Server;

		JoybusNextAction m_NextAction = JoybusNextAction::SEND;
		char m_LastCommand;
		std::chrono::steady_clock::time_point m_TimestampSent = std::chrono::steady_clock::time_point::min();
	public:
		//GBADevice();

		int GBAGetStatus();
		int RunBuffer(char* buffer, int length);
		int TransferInterval();
		bool GetData(uint32_t& hi, uint32_t& lo);
		void SendCommand(uint32_t command, char poll);
	};

	int GetTransferTime(char cmd);
}