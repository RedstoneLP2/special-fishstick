#include "common.h"


MemoryManager::MemoryManager(int size)
{
    memory = calloc(1,size);
}
MemoryManager::MemoryManager()
{
    MemoryManager(0xFFFF);
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
uint8_t* MemoryManager::GetMemoryLocation(uint16_t address){
    uint8_t* baseAddress = (uint8_t *) getMemory();
    return baseAddress + address;
}