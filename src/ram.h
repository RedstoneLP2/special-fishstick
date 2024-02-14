#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
class Ram
{
private:
    void* memory;
public:
    Ram(int);
    Ram();
    ~Ram();

    void* getMemory();
};



