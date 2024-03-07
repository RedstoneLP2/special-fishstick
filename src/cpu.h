#include "common.h"

class Cpu
{

private:

    Registers cpuRegisters;
    MemoryManager systemRam;
    uint16_t getOperantBytes();
    uint16_t Opcode_Length;
    ioHandler* iohandler;

public:
    Cpu(MemoryManager, ioHandler*);
    ~Cpu();
    void setStatusFlag(unsigned);
    void unSetStatusFlag(unsigned);
    void cmp(uint8_t*);
    void and_(uint8_t);
    void eor_(uint8_t);
    void lda(uint8_t);
    void ldx(uint8_t);
    void ldy(uint8_t);
    void bit(uint8_t*);
    void sta(uint16_t);
    void stx(uint16_t);
    void sty(uint16_t);
    void jsr(uint16_t);
    void bne(int8_t);
    void bcc(int8_t);
    void beq(int8_t);
    void bpl(int8_t);
    void bmi(int8_t);
    void jmp(uint16_t);
    void jmp(int8_t);
    void ora(uint8_t*);
    void adc(uint8_t*);
    void sbc(uint8_t*);
    void dec(uint8_t*);
    void inc(uint8_t*);
    void asl(uint8_t*);
    void rol(uint8_t*);
    void ror(uint8_t*);
    void lsr(uint8_t*);
    void cpy(uint8_t*);
    void cpx(uint8_t*);
    void clc();
    void cld();
    void cli();
    void clv();
    void pha();
    void pla();
    void rts();
    void dey();
    void iny();
    void tax();
    void printRegisters();
    void printMemoryLocation(int);
    void reset();
    void run();

};
