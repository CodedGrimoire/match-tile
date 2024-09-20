#pragma once

#include "./match.cpp"
#include "./init.c"
#include "./draw.c"main

void initializeGrid() {
    TileColor colors[TOTAL_COLORS];
    for (int i = 0; i < TOTAL_COLORS; i++) {
        colors[i] = (TileColor)(i + 1);
    }

    shuffleArray(colors, TOTAL_COLORS);

    int colorCounts[TOTAL_COLORS];
    for (int i = 0; i < TOTAL_COLORS; i++) {
        colorCounts[i] = 0;
    }

    int totalTiles = GRID_ROWS * GRID_COLS;
    TileColor shuffledTiles[totalTiles];

    for (int i = 0; i < totalTiles; i++) {
        int randomColor;
        do {
            randomColor = rand() % TOTAL_COLORS;
        } while (colorCounts[randomColor] >= 2);

        colorCounts[randomColor]++;
        shuffledTiles[i] = colors[randomColor];
    }

    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            grid[i][j].color = shuffledTiles[i * GRID_COLS + j];
            grid[i][j].flipped = false;
        }
    }
}


// Shuffle an array using the Fisher-Yates algorithm
void shuffleArray(TileColor array[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Swap array[i] and array[j]
        TileColor temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

bool checkWin() {
    int matchedPairs = 0;
    for (int i = 1; i <= TOTAL_COLORS; i++) {
        for (int j = 0; j < GRID_ROWS; j++) {
            for (int k = 0; k < GRID_COLS; k++) {
                if (grid[j][k].flipped && grid[j][k].color == i) {
                    if (i != FORBIDDEN_TILE) {
                        matchedPairs++;
                    }
                }
            }
        }
    }
    // If all non-forbidden pairs are matched, the player wins
    return (matchedPairs == 7);
}


int countMismatches(int totalMatches, int *mismatchCount, Tile *flippedTiles[2]) {
    if (flippedTiles[0]->color != flippedTiles[1]->color) {
        (*mismatchCount)++;
    }

    // Limit the mismatches to the total possible matches
    if (*mismatchCount > totalMatches) {
        *mismatchCount = totalMatches;
    }

    return *mismatchCount;
}


void start() {
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            handleEvent(&e);
        }

        drawGrid();

        if (numFlipped == 2)
        {

            int totalMatches = TOTAL_TILES / 2;
            int mismatches = countMismatches(totalMatches, &mismatchCount, flippedTiles); // Checking for number of mismatches
            SDL_Delay(500);

            // Inside the section where you check for a match after two tiles are flipped
            if (numFlipped == 2)
            {
                SDL_Delay(500);

                if (flippedTiles[0]->color == FORBIDDEN_TILE && flippedTiles[1]->color == FORBIDDEN_TILE)
                {
                    printf("Oops %s! You matched the forbidden pair. Game over!\n", player);
                    quit = true; // Closing the game when the forbidden pair is matched
                }
                else
                {
                    if (flippedTiles[0]->color == flippedTiles[1]->color)
                    {
                        int matchedPairs = 0;
                        for (int i = 1; i <= TOTAL_COLORS; i++)
                        {
                            if (i != FORBIDDEN_TILE)
                            {
                                int pairCount = 0;
                                for (int j = 0; j < GRID_ROWS; j++)
                                {
                                    for (int k = 0; k < GRID_COLS; k++)
                                    {
                                        if (grid[j][k].flipped && grid[j][k].color == i)
                                        {
                                            pairCount++;
                                        }
                                    }
                                }
                                if (pairCount == 2)
                                {
                                    matchedPairs++;
                                }
                            }
                        }

                        if (matchedPairs == 7 && mismatches < 8)
                        {
                            printf("Congratulations %s! You matched all pairs except the forbidden one. Proceed to Next Level!\n", player);
                            quit = true; // Closing the game when 7 other pair is matched except for forbidden pair
                        }
                        if (matchedPairs == 7 && mismatches >= 8)
                        {
                            printf("sorry %s! Too Many Mismatches. Try Again\n", player);
                            quit = true;
                        }
                    }
                    else
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            flippedTiles[i]->flipped = false;
                        }
                    }
                    numFlipped = 0;
                }
            }
        }
    }
}