#pragma once

#include "./match.cpp"

void drawGrid() {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            SDL_Rect rect = {j * (TILE_SIZE + TILE_MARGIN), i * (TILE_SIZE + TILE_MARGIN), TILE_SIZE, TILE_SIZE};
            if (grid[i][j].flipped) {
                drawTile(rect, grid[i][j].color);
            } else {
                SDL_RenderCopy(renderer, unflippedTileTexture, NULL, &rect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void drawTile(SDL_Rect rect, TileColor color) {
    SDL_RenderCopy(renderer, tileTextures[color - 1], NULL, &rect);
}