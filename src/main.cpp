#include "program.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main()
{
    Program program;
    program.loop();
    program.close();
    return 0;
}