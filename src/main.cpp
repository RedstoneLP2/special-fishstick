#include "cpu.h"

int main(int argc, char const *argv[])
{
    Cpu core = Cpu();
    core.printRegisters();
    core.lda('H');
    core.sta(0x5000);
    core.lda('e');
    core.sta(0x5001);
    core.lda('l');
    core.sta(0x5002);
    core.lda('l');
    core.sta(0x5003);
    core.lda('o');
    core.sta(0x5004);
    core.lda(' ');
    core.sta(0x5005);
    core.lda('W');
    core.sta(0x5006);
    core.lda('o');
    core.sta(0x5007);
    core.lda('r');
    core.sta(0x5008);
    core.lda('l');
    core.sta(0x5009);
    core.lda('d');
    core.sta(0x500a);
    core.lda('!');
    core.sta(0x500b);
    core.lda('\n');
    core.sta(0x500c);
    std::cout << "------------"<<std::endl;
    core.printDisplayMemory();

    core.printRegisters();
    return 0;
}
