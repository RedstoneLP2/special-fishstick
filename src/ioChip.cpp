#include "common.h"

ioChip::ioChip(MemoryManager mem)
{
    mm = mem;
    ACIA_DATA_ADDR      = 0x5000;
    ACIA_STATUS_ADDR    = 0x5001;
    ACIA_CMD_ADDR       = 0x5002;
    ACIA_CTRL_ADDR      = 0x5003;
}

ioChip::~ioChip()
{
}

void ioChip::run(){
    if (mm.GetMemoryLocation(ACIA_DATA_ADDR) != 0x00){
        print();
    }
    sleep(.4);
}

void ioChip::sendkey(uint8_t keycode){
    *(mm.GetMemoryLocation(ACIA_STATUS_ADDR)) = 0x08;
    *(mm.GetMemoryLocation(ACIA_DATA_ADDR)) = keycode;
}

void ioChip::print(){
    std::cout << mm.GetMemoryLocation(ACIA_DATA_ADDR);
    *mm.GetMemoryLocation(ACIA_DATA_ADDR) = 0x00;
}