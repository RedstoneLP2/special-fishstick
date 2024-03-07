#include "common.h"

ioChip::ioChip(MemoryManager mem,ioHandler* io)
{
    mm = mem;
    iohandler = io;
    //(*iohandler).printHeader();
    ACIA_DATA_ADDR      = 0x5000;
    ACIA_STATUS_ADDR    = 0x5001;
    ACIA_CMD_ADDR       = 0x5002;
    ACIA_CTRL_ADDR      = 0x5003;

}

ioChip::~ioChip()
{
}

void ioChip::run(){
    char ch;
    uint8_t test = *mm.GetMemoryLocation(ACIA_DATA_ADDR);
    if (*mm.GetMemoryLocation(ACIA_DATA_ADDR) != uint8_t(0x00)){
        print();
    }
    if ((ch = (*iohandler).handleInput())!=ERR){
        sendkey(ch);
    }
    sleep(SPEED);
}

void ioChip::sendkey(uint8_t keycode){
    mm.writeMem(ACIA_STATUS_ADDR,uint8_t(0x08));
    mm.writeMem(ACIA_DATA_ADDR,keycode);
}

void ioChip::print(){
    (*iohandler).printIoChar(*mm.GetMemoryLocation(ACIA_DATA_ADDR));
    mm.writeMem(ACIA_DATA_ADDR, uint8_t(0x00));
}