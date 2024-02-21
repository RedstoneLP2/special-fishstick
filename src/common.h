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

#define SPEED .05