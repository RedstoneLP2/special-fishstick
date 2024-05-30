#include "common.h"

ioChip::ioChip(MemoryManager* mem,ioHandler* io)
{
    mm = mem;
    iohandler = io;
    //(*iohandler).printHeader();
}

ioChip::~ioChip()
{
}

void ioChip::run(){
    char ch;
    if (mm->readDevMem(ACIA_DATA_ADDR) != uint8_t(0x00)){
        print();
    }
    if ((ch = iohandler->handleInput())!=ERR){
        std::string cha = std::format("INPUT: {:x}",ch);
        iohandler->printDebugString(cha);
        if (ch == char(0x0a)){
            ch = char(0x0d);
        }else if (ch == char(0x07)){
            ch = char(0x08);
        }
        sendkey(ch);
    }
}

void ioChip::sendkey(uint8_t keycode){
    mm->writeDevMem(ACIA_STATUS_ADDR,uint8_t(0x08));
    mm->writeDevMem(ACIA_DATA_ADDR,keycode);
}

void ioChip::print(){
    char ch = mm->readDevMem(ACIA_DATA_ADDR);
    iohandler->printIoChar(mm->readDevMem(ACIA_DATA_ADDR));
    mm->writeMem(ACIA_DATA_ADDR, uint8_t(0x00));
}
