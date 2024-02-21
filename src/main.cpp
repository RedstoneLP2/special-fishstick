#include "common.h"

bool running = false;

void RunCpu(Cpu core, ioChip ACIA){
    while(running)
    //for (int i = 0; i < 5000; i++)
    {
        //core.printRegisters();
        core.run();
        ACIA.run();
        //std::cout << "-------------------"<<std::endl;
    }
}

void timer(int seconds){
    sleep(seconds);
    running=false;
}

int main(int argc, char const *argv[])
{
    MemoryManager memory = MemoryManager(65535);
    running = true;
    ioHandler io = ioHandler();
    ioChip ACIA = ioChip(memory,&io);
    Cpu core = Cpu(memory,&io);
    loadfile("./sample/tmp/eater.bin",memory.getMemory());
    core.reset();
    //std::thread cpu (RunCpu,core,ACIA);

    std::thread Timer(timer,10);
    while(running)
    //for (int i = 0; i < 5000; i++)
    {
        //core.printRegisters();
        core.run();
        ACIA.run();
        //std::cout << "-------------------"<<std::endl;
    }

    sleep(10);
    core.printRegisters();
    io.printString("TEST FROM MAIN");
    sleep(2);
    running = false;
    //cpu.join();
    Timer.join();

    //hello_World(core);
    return 0;
}
