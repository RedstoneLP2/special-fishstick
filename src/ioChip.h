#include "common.h"

class ioChip
{
private:
    MemoryManager mm;
    ioHandler* iohandler;
    uint16_t ACIA_DATA_ADDR;
    uint16_t ACIA_STATUS_ADDR;
    uint16_t ACIA_CMD_ADDR;
    uint16_t ACIA_CTRL_ADDR;

    void print();
public:
    ioChip(MemoryManager,ioHandler*);
    ~ioChip();
    void run();
    void sendkey(uint8_t);
};