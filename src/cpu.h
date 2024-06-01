#include "common.h"

class Cpu
{

private:

    Registers cpuRegisters;
    MemoryManager* systemRam;
    uint16_t getOperantBytes(uint16_t);
    uint16_t Opcode_Length;
    ioHandler* iohandler;

public: // instruction reference: https://feertech.com/legion/reference65c02.html
    Cpu(MemoryManager*, ioHandler*);
    ~Cpu();
    void resetStatusRegisters();
    void setStatusFlag(unsigned);
    void unSetStatusFlag(unsigned);
    void adc(uint8_t*);
    void and_(uint8_t);
    void asl(uint8_t*);
    void bbr(int8_t);
    void bbs(int8_t);
    void bcc(int8_t);
    void bcs(int8_t);
    void beq(int8_t);
    void bit(uint8_t*);
    void bmi(int8_t);
    void bne(int8_t);
    void bpl(int8_t);
    void bra(int8_t);
    void brk();
    void bvc(int8_t);
    void bvs(int8_t);
    void clc();
    void cld();
    void cli();
    void clv();
    void cmp(uint8_t*);
    void cpx(uint8_t*);
    void cpy(uint8_t*);
    void dec(uint8_t*);
    void dex();
    void dey();
    void eor_(uint8_t);
    void inc(uint8_t*);
    void inx();
    void iny();
    void jmp(uint16_t);
    void jmp(int8_t);
    void jsr(uint16_t);
    void lda(uint8_t);
    void ldx(uint8_t);
    void ldy(uint8_t);
    void lsr(uint8_t*);
    void nop();
    void ora(uint8_t*);
    void pha();
    void php();
    void phx();
    void phy();
    void pla();
    void plp();
    void plx();
    void ply();
    void rmb();
    void rol(uint8_t*);
    void ror(uint8_t*);
    void rti();
    void rts();
    void sbc(uint8_t*);
    void sec();
    void sed();
    void sei();
    void smb();
    void sta(uint16_t);
    void stp();
    void stx(uint16_t);
    void sty(uint16_t);
    void stz();
    void tax();
    void tay();
    void trb();
    void tsb();
    void tsx();
    void txa();
    void txs();
    void tya();
    void wai();

    void printRegisters();
    void printMemoryLocation(int);
    void reset();
    void run();

};
