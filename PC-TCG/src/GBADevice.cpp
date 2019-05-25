#include "../include/GBADevice.h"

namespace GBAConnect {
	int GetTransferTime(char cmd) {
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

		int ret = static_cast<int>((bytes_transferred * GC_CPU_Clock) / (std::max(s_num_connected, 1) * BYTES_PER_SECOND));
		return ret;
	}

	int GBADevice::GBAGetStatus() {
		if (!m_Server.IsConnected()) {
			return -1;
		}
	}

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
			m_TimestampSent = std::chrono::high_resolution_clock::now();
			m_NextAction = JoybusNextAction::WAIT;
		}
		case JoybusNextAction::WAIT:
		{
			uint64_t elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>
									(std::chrono::high_resolution_clock::now() - m_TimestampSent).count();

			while (GetTransferTime(m_LastCommand) > elapsed_time) {
				elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>
					(std::chrono::high_resolution_clock::now() - m_TimestampSent).count();
			}

			m_NextAction = JoybusNextAction::RECEIVE;
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

		return 0;
	}
}