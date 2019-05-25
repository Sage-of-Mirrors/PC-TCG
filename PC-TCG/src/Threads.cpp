#include "../include/Threads.h"

namespace GBAConnect {
	std::thread s_connection_thread;
	std::queue<std::unique_ptr<sf::TcpSocket>> s_waiting_socks;
	std::queue<std::unique_ptr<sf::TcpSocket>> s_waiting_clocks;

	std::mutex s_cs_gba;
	std::mutex s_cs_gba_clk;

	int s_num_connected;
	uint32_t GC_CPU_Clock = 486000000u;
	bool IsServerRunning;
}