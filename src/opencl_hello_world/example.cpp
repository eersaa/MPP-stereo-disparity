#include "hello-world.h"

int main()
{
    OCL_HelloWorld helloWorld;
    helloWorld.CreateProgramFromFile("hello-world.cl");
    helloWorld.Run();
    return 0;
}
