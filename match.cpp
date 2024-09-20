#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./globals.h"
#include "./init.c"
#include "./engine.c"
#include "./draw.c"

int main(int argc, char *argv[])
{
    init();
    start();
    close();
    return 0;
}
