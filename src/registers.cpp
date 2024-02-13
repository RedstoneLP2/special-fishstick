#include "registers.h"

Registers::Registers(){
            ProgramCounter.reset();
            StackPointer.reset();
            ProcessorStatus.reset();
            Accumulator.reset();
            XIndex.reset();
            YIndex.reset();
        }

Registers::~Registers()
{}

std::string Registers::toString() {
    return std::format("ProgramCounter: {}\n"
        "StackPointer: {}\n"
        "ProcessorStatus: {}\n"
        "ProcessorStatus: NV1BDIZC\n"
        "Accumulator: {}\n"
        "XIndex: {}\n"
        "YIndex: {}\n",
        ProgramCounter.to_string(),
        StackPointer.to_string(),

        ProcessorStatus.to_string(),

        Accumulator.to_string(),
        XIndex.to_string(),
        YIndex.to_string());
        }
