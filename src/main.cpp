#include <iostream>

#include "core/core.h"

int main()
{
    std::cout<<"Main\n";
    gbox::Core core;
    core.register_SDL_handler();
    core.start_main_loop();
    return EXIT_SUCCESS;
}
