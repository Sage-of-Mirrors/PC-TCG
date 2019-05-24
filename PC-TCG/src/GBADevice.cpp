#include "Util.cpp"
#include "../include/GBADevice.h"

int GBADevice::RunBuffer(char* buffer, int length) {
	switch (m_NextAction) {
	case JoybusNextAction::SEND:
	{
		m_Server.ClockSync();

		if (m_Server.Connect()) {
			m_Server.Send(buffer);
		}
		else {
			return -1;
		}

		m_LastCommand = buffer[0];
		//m_TimestampSent = CoreTiming::GetTicks();
		m_NextAction = JoybusNextAction::WAIT;
		[[fallthrough]]; // This allows us to fall into the case for WAIT below. So this code will send the buffer and immediately start waiting.
	}
	case JoybusNextAction::WAIT:
	{
		int elapsed_time = static_cast<int>(/*CoreTiming::GetTicks() -*/ m_TimestampSent);

		if (GetTransferTime(m_LastCommand) > elapsed_time) {
			return 0;
		}

		m_NextAction = JoybusNextAction::RECEIVE;
		[[fallthrough]]; // This allows us to fall into the case for RECEIVE below. So this code will start receiving if the wait finished.
	}
	case JoybusNextAction::RECEIVE:
	{
		int num_bytes_recieved = m_Server.Receive(buffer);
		m_NextAction = JoybusNextAction::SEND;

		if (num_bytes_recieved == 0) {
			return -1;
		}

		return num_bytes_recieved;
	}
	}
}