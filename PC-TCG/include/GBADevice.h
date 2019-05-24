#pragma once

#include "GBAServer.h"
#include "JoybusEnums.h"

class GBADevice {
public:
	GBADevice();

	int RunBuffer(char* buffer, int length);
	int TransferInterval();
	bool GetData(uint32_t& hi, uint32_t& lo);
	void SendCommand(uint32_t command, char poll);

private:
	GBAServer m_Server;
	JoybusNextAction m_NextAction = JoybusNextAction::SEND;
	char m_LastCommand;
	uint64_t m_TimestampSent = 0;
};