#pragma once

#include <iostream>
#include <format>
#include <bitset>
#include <cstdint>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <thread>
#include <ncurses.h>

#include "ioHandler.h"
#include "registers.h"
#include "memoryManager.h"
#include "ioChip.h"
#include "cpu.h"
#include "util.h"

#define SPEED .1

#define ACIA_DATA_ADDR      uint16_t(0x5000)
#define ACIA_STATUS_ADDR    uint16_t(0x5001)
#define ACIA_CMD_ADDR       uint16_t(0x5002)
#define ACIA_CTRL_ADDR      uint16_t(0x5003)