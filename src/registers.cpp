#include "common.h"

Registers::Registers(){
            ProgramCounter = 0;
            StackPointer = 0;
            ProcessorStatus.reset();
            Accumulator = 0;
            XIndex = 0;
            YIndex = 0;
        }

Registers::~Registers()
{}

std::string Registers::toString() {
    return std::format("\n ProgramCounter: {:x}\n"
        " StackPointer: {:x}\n"
        " ProcessorStatus: {}\n"
        " ProcessorStatus: NV1BDIZC\n"
        " Accumulator: {:x}\n"
        " XIndex: {:x}\n"
        " YIndex: {:x}\n",
        ProgramCounter,
        StackPointer,
        ProcessorStatus.to_string(),
        Accumulator,
        XIndex,
        YIndex);
        }
