#include "common.h"

bool running = false;

void RunCpu(Cpu core){
    while(running)
    //for (int i = 0; i < 5000; i++)
    {
        //core.printRegisters();
        core.run();
        //std::cout << "-------------------"<<std::endl;
    }
}

void RunACIA(ioChip core){
    while(running)
    //for (int i = 0; i < 5000; i++)
    {
        //core.printRegisters();
        core.run();
        //std::cout << "-------------------"<<std::endl;
    }
}

int main(int argc, char const *argv[])
{
    MemoryManager memory = MemoryManager(65535);
    running = true;
    Cpu core = Cpu(memory);
    ioChip ACIA = ioChip(memory);
    loadfile("./sample/tmp/eater.bin",memory.getMemory());
    core.reset();
    std::thread cpu (RunCpu,core);
    std::thread acia (RunACIA,ACIA);

    sleep(2);
    running = false;
    cpu.join();
    acia.join();

    //hello_World(core);
    return 0;
}
