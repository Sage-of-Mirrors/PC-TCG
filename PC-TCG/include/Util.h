#pragma once
#include "Constants.h"
#include "Threads.h"

#include <SFML/Network.hpp>
#include <queue>

static int GetTransferTime(char cmd);

template <typename T>
static std::unique_ptr<T> MoveFromFront(std::queue<std::unique_ptr<T>>& ptrs);

static std::unique_ptr<sf::TcpSocket> GetNextSocket();
static std::unique_ptr<sf::TcpSocket> GetNextClock();

static void GBAConnectionWaiter();
void GBAConnectionWaiter_Shutdown();
