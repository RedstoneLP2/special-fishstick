#include "cpu.h"

Cpu::Cpu(){
    cpuRegisters = Registers();
    systemRam = Ram(16384);
}

Cpu::~Cpu(){
    //cpuRegisters.~Registers();
}

void Cpu::printRegisters(){
    std::cout << cpuRegisters.toString();
}
void Cpu::printDisplayMemory(){
    // 0x5000 - 0x5010
    char* baseAddress = (char *) systemRam.getMemory();
    baseAddress = baseAddress + 0x5000;
    for (char* address = baseAddress; address <= baseAddress+16; address++){
        std::cout << *address;
    }

}

void Cpu::setStatusFlag(unsigned Flag){
    if (!cpuRegisters.ProcessorStatus.test(Flag))
    {
        cpuRegisters.ProcessorStatus[Flag].flip();
    }
}

void Cpu::lda(char op){
    cpuRegisters.Accumulator = std::bitset<8>(op);
}
void Cpu::ldx(char op){
    cpuRegisters.XIndex = std::bitset<8>(op);
}
void Cpu::ldy(char op){
    cpuRegisters.YIndex = std::bitset<8>(op);
}

void Cpu::sta(uint address){
    char* memoryLocation = (char*) systemRam.getMemory() + address;
    *memoryLocation = static_cast<char>(cpuRegisters.Accumulator.to_ulong());
}
void Cpu::stx(uint address){
    char* memoryLocation = (char*) systemRam.getMemory() + address;
    *memoryLocation = static_cast<char>(cpuRegisters.XIndex.to_ulong());
}
void Cpu::sty(uint address){
    char* memoryLocation = (char*) systemRam.getMemory() + address;
    *memoryLocation = static_cast<char>(cpuRegisters.YIndex.to_ulong());
}


void Cpu::clc(){
    if (cpuRegisters.ProcessorStatus.test(0))
    {
        cpuRegisters.ProcessorStatus[0].flip();
    }
}
void Cpu::cld(){
    if (cpuRegisters.ProcessorStatus.test(3))
    {
        cpuRegisters.ProcessorStatus[3].flip();
    }
}
void Cpu::cli(){
    if (cpuRegisters.ProcessorStatus.test(2))
    {
        cpuRegisters.ProcessorStatus[2].flip();
    }
}
void Cpu::clv(){
    if (cpuRegisters.ProcessorStatus.test(6))
    {
        cpuRegisters.ProcessorStatus[6].flip();
    }
}
