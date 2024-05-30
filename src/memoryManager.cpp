#include "common.h"


MemoryManager::MemoryManager(int size, ioHandler* io)
{
    memory = calloc(1,size);
    inputBuffer = 0;
    outputBuffer = 0;
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
    startWrite();
    if (address == ACIA_DATA_ADDR){
        outputBuffer = value;
        return;
    }
    uint8_t* memoryLocation = (uint8_t*) getMemory() + address;
    *memoryLocation = value;
    endWrite();

}

void MemoryManager::writeMem(uint16_t address, uint16_t value){
    startWrite();
    uint16_t* memoryLocation = (uint16_t*) getMemory() + address;
    *memoryLocation = value;
    endWrite();
}

uint8_t MemoryManager::readMem(uint16_t address){
    if (address == ACIA_DATA_ADDR)
    {
        return inputBuffer;
    }
    uint8_t* baseAddress = (uint8_t *) getMemory();
    return *(baseAddress + address);
}

void MemoryManager::writeDevMem(uint16_t address, uint8_t value){
    if (address == ACIA_DATA_ADDR){
        inputBuffer = value;
    }
    uint8_t* memoryLocation = (uint8_t*) getMemory() + address;
    *memoryLocation = value;
}

uint8_t MemoryManager::readDevMem(uint16_t address){
    if (address == ACIA_DATA_ADDR){
        return outputBuffer;
    }

    uint8_t* baseAddress = (uint8_t *) getMemory();
    return *(baseAddress + address);
}

uint8_t* MemoryManager::GetMemoryLocation(uint16_t address){
    uint8_t* baseAddress = (uint8_t *) getMemory();
    lastAddress == address;
    
    if (address == ACIA_DATA_ADDR){
        return &inputBuffer;
    }
    return baseAddress + address;
}

void MemoryManager::startWrite(){
    MEMWRITE = true;
}

void MemoryManager::endWrite(){
    MEMWRITE = false;
}

void MemoryManager::startRead(){
    MEMREAD = true;
}

void MemoryManager::endRead(){
    if (lastAddress == uint16_t(ACIA_DATA_ADDR)){
        uint8_t *a = (uint8_t *) getMemory() + ACIA_STATUS_ADDR;
        *a = 0x00; // reset after status after read
    }
    MEMREAD = false;
}