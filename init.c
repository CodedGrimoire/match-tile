#pragma once

#include "./match.cpp"


void init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Memory Matching Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        exit(1);
    }

    backgroundTexture = IMG_LoadTexture(renderer, "background.png");
    if (backgroundTexture == NULL) {
        printf("Failed to load background image! SDL_image Error: %s\n", IMG_GetError());
        exit(1);
    }

    unflippedTileTexture = IMG_LoadTexture(renderer, "tiles/cat.png");
    if (unflippedTileTexture == NULL) {
        printf("Failed to load unflipped tile image! SDL_image Error: %s\n", IMG_GetError());
        exit(1);
    }

    for (int i = 0; i < TOTAL_COLORS; i++) {
        char filename[50];
        sprintf(filename, "tiles/image%d.png", i + 1);
        tileTextures[i] = IMG_LoadTexture(renderer, filename);
        if (tileTextures[i] == NULL) {
            printf("Failed to load image %d! SDL_image Error: %s\n", i + 1, IMG_GetError());
            exit(1);
        }
    }

    srand(time(NULL));
    initializeGrid();
}

void close() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(unflippedTileTexture);

    for (int i = 0; i < TOTAL_COLORS; i++) {
        SDL_DestroyTexture(tileTextures[i]);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}


void handleEvent(SDL_Event* e) {
    if (e->type == SDL_QUIT) {
        quit = true;
    } else if (e->type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        int clickedRow = mouseY / (TILE_SIZE + TILE_MARGIN);
        int clickedCol = mouseX / (TILE_SIZE + TILE_MARGIN);

        if (clickedRow >= 0 && clickedRow < GRID_ROWS && clickedCol >= 0 && clickedCol < GRID_COLS) {
            if (!grid[clickedRow][clickedCol].flipped && numFlipped < 2) {
                grid[clickedRow][clickedCol].flipped = true;
                flippedTiles[numFlipped] = &grid[clickedRow][clickedCol];
                numFlipped++;
            }
        }
    }
}