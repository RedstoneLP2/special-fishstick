#include "registers.h"
#include "ram.h"

class Cpu
{

private:

    Registers cpuRegisters;
    Ram systemRam;

public:
    Cpu();
    ~Cpu();
    void setStatusFlag(unsigned);
    void lda(char);
    void ldx(char);
    void ldy(char);
    void sta(uint);
    void stx(uint);
    void sty(uint);
    void clc();
    void cld();
    void cli();
    void clv();
    void printRegisters();
    void printDisplayMemory();

};
