#include "common.h"


MemoryManager::MemoryManager(int size, ioHandler* io)
{
    memory = calloc(1,size);
    iohandler = io;
}


MemoryManager::~MemoryManager()
{
    //free(memory);
}

void* MemoryManager::getMemory(){
    return memory;
}


void MemoryManager::writeMem(uint16_t address, uint8_t value){
    uint8_t* memoryLocation = (uint8_t*) getMemory() + address;
    *memoryLocation = value;
    /*
    std::cout <<  "------value: " <<std::setfill('0')<<std::setw(2)<<std::hex<<std::bitset<8>(*memoryLocation).to_ulong()<<std::endl;
    std::cout <<  "------Written to: " <<std::setfill('0')<<std::setw(4)<<std::hex<<std::bitset<16>(address).to_ulong()<<std::endl;
    if (address == uint16_t(0x5000)){
        std::cout<<value;
    }
    */
}

void MemoryManager::writeMem(uint16_t address, uint16_t value){
    uint16_t* memoryLocation = (uint16_t*) getMemory() + address;
    *memoryLocation = value;
    /*
    std::cout <<  "------value: " <<std::setfill('0')<<std::setw(4)<<std::hex<<std::bitset<16>(*memoryLocation).to_ulong()<<std::endl;
    std::cout <<  "------Written to: " <<std::setfill('0')<<std::setw(4)<<std::hex<<std::bitset<16>(address).to_ulong()<<std::endl;
    */
}

uint8_t MemoryManager::readMem(uint16_t address){
    uint8_t* baseAddress = (uint8_t *) getMemory();
return *(baseAddress + address);
}

uint8_t* MemoryManager::GetMemoryLocation(uint16_t address){
    uint8_t* baseAddress = (uint8_t *) getMemory();
    if (address == ACIA_STATUS_ADDR){
        uint8_t *a = baseAddress + ACIA_STATUS_ADDR;
        if (*a == 0x08){
            std::string debug = std::format("{:x}",*a);
            (*iohandler).printDebugString(debug);
        }
    }
    if (address == uint16_t(ACIA_DATA_ADDR)){
        uint8_t a = *(uint8_t *)(baseAddress + ACIA_STATUS_ADDR);
        a = uint8_t(0);
    }
    return baseAddress + address;
}