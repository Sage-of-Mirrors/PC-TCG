#pragma once

#include <SFML/Network.hpp>
#include <queue>
#include <thread>
#include <mutex>

std::thread s_connection_thread;
std::queue<std::unique_ptr<sf::TcpSocket>> s_waiting_socks;
std::queue<std::unique_ptr<sf::TcpSocket>> s_waiting_clocks;

std::mutex s_cs_gba;
std::mutex s_cs_gba_clk;

int s_num_connected;
bool IsServerRunning;