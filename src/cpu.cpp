#include "common.h"

Cpu::Cpu(MemoryManager SystemRam){
    cpuRegisters = Registers();
    systemRam = SystemRam;
    reset();
}

Cpu::~Cpu(){
    //cpuRegisters.~Registers();
}

void Cpu::reset(){
    std::string upper = std::bitset<8>(*(systemRam.GetMemoryLocation(0xFFFC))).to_string();
    std::string lower = std::bitset<8>(*(systemRam.GetMemoryLocation(0xFFFD))).to_string();
    std::bitset<16> resetvector (lower+upper);
    //std::cout << resetvector.to_string()<<std::endl;
    cpuRegisters.ProgramCounter = resetvector.to_ulong();
    cpuRegisters.StackPointer = 0xFF;
    //processorstatus reset!
    for (size_t i = 0; i < 8; i++)
    {
        if (i == ProcessorStatusFlags.Unused){
            if (!cpuRegisters.ProcessorStatus.test(i))
            {
                cpuRegisters.ProcessorStatus[i].flip();
            }
        }else if (cpuRegisters.ProcessorStatus.test(i))
        {
            cpuRegisters.ProcessorStatus[i].flip();
        }
    }
    cpuRegisters.Accumulator = 0;
    cpuRegisters.XIndex = 0;
    cpuRegisters.YIndex = 0;

}

void Cpu::run(){
    uint8_t opcode = *((uint8_t*)systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter));
    /*
    std::cout<<"opcode: "<<std::setfill('0')<<std::setw(2)<<std::hex<<std::bitset<8>(opcode).to_ulong()<<std::endl;
    std::cout<<"parameter01: "<<std::setfill('0')<<std::setw(2)<<std::hex<<std::bitset<8>(*(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1))).to_ulong()<<std::endl;
    std::cout<<"parameter02: "<<std::setfill('0')<<std::setw(2)<<std::hex<<std::bitset<8>(*(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+2))).to_ulong()<<std::endl;
    */
    switch (opcode)
    {
    case uint8_t(0xAD):
        {
            uint16_t* address = (uint16_t*)systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1);
            char value = *address;
            lda(value);
            cpuRegisters.ProgramCounter++;
            cpuRegisters.ProgramCounter++;
        }
        break;
    case uint8_t(0xA9):
        {
            char value = *(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1));
            lda(value);
            cpuRegisters.ProgramCounter++;
        }
        break;
    case uint8_t(0xAE):
        ldx(*(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1)));
        break;
    case uint8_t(0xAC):
        ldy(*(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1)));
        break;
    case uint8_t(0x8D):
        sta(getOperantBytes());
        cpuRegisters.ProgramCounter++;
        cpuRegisters.ProgramCounter++;
        break;
    case uint8_t(0x8E):
        stx(getOperantBytes());
        cpuRegisters.ProgramCounter++;
        cpuRegisters.ProgramCounter++;
        break;
    case uint8_t(0x8C):
        sty(getOperantBytes());
        cpuRegisters.ProgramCounter++;
        cpuRegisters.ProgramCounter++;
        break;
    case uint8_t(0x20):
        {
            uint16_t value = getOperantBytes();
            //std::cout<<"value "<<std::setfill('0')<<std::setw(4)<<std::hex<<std::bitset<16>(value).to_ulong()<<std::endl;
            jsr(value);
        }
        break;
    case uint8_t(0x60):
        {
            rts();
        }
        break;
    case uint8_t(0x48):
        pha();
        break;
    case uint8_t(0x68):
        pla();
        break;
    case uint8_t(0x3A):
        dec();
        break;
    case uint8_t(0xD0):
        {
            int8_t value = *(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1));
            bne(value);
        }
        break;
    default:
        std::cout<< "Unimplemented Instruction: "<< std::setfill ('0') << std::setw(2) << std::hex<<std::bitset<8>(opcode).to_ulong() << std::endl;
        break;
    }
    cpuRegisters.ProgramCounter++;
}

uint16_t Cpu::getOperantBytes(){
        std::string upper = std::bitset<8>(*(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+1))).to_string();
        std::string lower = std::bitset<8>(*(systemRam.GetMemoryLocation(cpuRegisters.ProgramCounter+2))).to_string();
        std::bitset<16>value(lower+upper);
        return (uint16_t)value.to_ulong();
}

void Cpu::printRegisters(){
    std::cout << cpuRegisters.toString();
}

void Cpu::printMemoryLocation(int memoryLocation){
    // 0x5000 - 0x5010
    
    uint8_t* baseAddress = (systemRam.GetMemoryLocation(memoryLocation));
    std::cout<< "     00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F"<<std::endl;
    std::cout << std::setfill('0')<<std::setw(4) << std::hex << memoryLocation<< " ";
    for (uint8_t* address = baseAddress; address <= baseAddress+0x0F; address++){
        std::cout << std::setfill ('0') << std::setw(2) << std::hex<<std::bitset<8>(*address).to_ulong()<< " ";
    }
    std::cout<<std::endl;
}

void Cpu::setStatusFlag(unsigned Flag){
    if (!cpuRegisters.ProcessorStatus.test(Flag))
    {
        cpuRegisters.ProcessorStatus[Flag].flip();
    }
}

void Cpu::lda(char immediate){
    cpuRegisters.Accumulator = immediate;
}
void Cpu::ldx(char immediate){
    cpuRegisters.XIndex = immediate;
}
void Cpu::ldy(char immediate){
    cpuRegisters.YIndex = immediate;
}

void Cpu::sta(uint16_t address){
    systemRam.writeMem(address, cpuRegisters.Accumulator);
}

void Cpu::stx(uint16_t address){
    systemRam.writeMem(address, cpuRegisters.XIndex);
}
void Cpu::sty(uint16_t address){
    systemRam.writeMem(address, cpuRegisters.YIndex);
}

void Cpu::bne(int8_t relAddress){
    if (cpuRegisters.Accumulator != 0){
        jmp(relAddress);
    }else{
        cpuRegisters.ProgramCounter++;
    }
}

void Cpu::jmp(int8_t relAddress){
    cpuRegisters.ProgramCounter = relAddress+cpuRegisters.ProgramCounter+1;
}
void Cpu::jmp(uint16_t address){
    cpuRegisters.ProgramCounter = address-1;
}

void Cpu::dec(){
    cpuRegisters.Accumulator--;
}

void Cpu::inc(){
    cpuRegisters.Accumulator++;
}


void Cpu::jsr(uint16_t address){
    cpuRegisters.ProgramCounter += 3;

    uint8_t lower_byte = (uint8_t) cpuRegisters.ProgramCounter;
    uint8_t upper_byte = (uint8_t) (cpuRegisters.ProgramCounter  >> 8);

    uint16_t stackAddress = 0x0100+cpuRegisters.StackPointer;
    systemRam.writeMem(stackAddress, upper_byte);
    cpuRegisters.StackPointer--;

    stackAddress = 0x0100+cpuRegisters.StackPointer;
    systemRam.writeMem(stackAddress, lower_byte);
    cpuRegisters.StackPointer--;

    /*
    std::cout<< "jumping from: " <<std::hex<< cpuRegisters.ProgramCounter<<std::endl;
    std::cout<< "jumping to: " <<std::hex<< address<<std::endl;
    */
    jmp(uint16_t(address));
}

void Cpu::rts(){

    cpuRegisters.StackPointer++;
    uint16_t stackAddress = 0x0100+cpuRegisters.StackPointer;
    //std::cout<< "StackAddress: " <<std::setfill('0')<<std::setw(4)<<std::hex<< std::bitset<16>(stackAddress).to_ulong()<<std::endl;
    uint8_t lower_byte = *systemRam.GetMemoryLocation(stackAddress);
    cpuRegisters.StackPointer++;

    stackAddress = 0x0100+cpuRegisters.StackPointer;
    //std::cout<< "StackAddress: " <<std::setfill('0')<<std::setw(4)<<std::hex<< std::bitset<16>(stackAddress).to_ulong()<<std::endl;
    uint8_t upper_byte = *systemRam.GetMemoryLocation(stackAddress);
    uint16_t returnAddress = (((uint16_t)upper_byte) << 8)+lower_byte;
    //std::cout<< "jumping to: " <<std::setfill('0')<<std::setw(4)<<std::hex<<std::bitset<16>(returnAddress).to_ulong()<<std::endl;
    jmp(returnAddress);
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

void Cpu::pha(){
    uint16_t stackAddress = 0x0100+cpuRegisters.StackPointer;
    systemRam.writeMem(stackAddress, cpuRegisters.Accumulator);
    cpuRegisters.StackPointer--;
}

void Cpu::pla(){
    cpuRegisters.StackPointer++;
    uint16_t stackAddress = 0x0100+cpuRegisters.StackPointer;
    //std::cout<< "StackAddress: " <<std::setfill('0')<<std::setw(4)<<std::hex<< std::bitset<16>(stackAddress).to_ulong()<<std::endl;
    cpuRegisters.Accumulator = *systemRam.GetMemoryLocation(stackAddress);
}