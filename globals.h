
#include "./match.cpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TILE_SIZE 80
#define TILE_MARGIN 10
#define GRID_ROWS 4
#define GRID_COLS 4
#define TOTAL_TILES (GRID_ROWS * GRID_COLS)
#define TOTAL_COLORS (TOTAL_TILES / 2)
#define FORBIDDEN_TILE TILE_TEAL 

typedef enum {
    TILE_EMPTY,
    TILE_RED,
    TILE_GREEN,
    TILE_BLUE,
    TILE_YELLOW,
    TILE_MAGENTA,
    TILE_CYAN,
    TILE_MAROON,
    TILE_TEAL,
} TileColor;

typedef struct {
    int x, y;
    TileColor color;
    bool flipped;
} Tile;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* backgroundTexture = NULL;
SDL_Texture* unflippedTileTexture = NULL;
SDL_Texture* tileTextures[TOTAL_COLORS];

Tile grid[GRID_ROWS][GRID_COLS];
Tile* flippedTiles[2];
int numFlipped = 0;
bool quit = false;

// Function declarations
void init();
void close();
void handleEvent(SDL_Event* e);
bool checkWin();
void drawGrid();
void drawTile(SDL_Rect rect, TileColor color);
void initializeGrid();
void shuffleArray(TileColor array[], int size);
void savePlayerName(const char* playerName);
int countMismatches(int totalMatches, int *mismatchCount, Tile *flippedTiles[2]);
char* readPlayerName();


SDL_Event e;

int mismatchCount = 0;
// int matchedPairs = 0;
int totalMismatches = 0;
int forbiddenPairMatches = 0;
char player[] = {"tazkia"};