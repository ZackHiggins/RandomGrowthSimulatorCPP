#include <iostream>
#include <SDL2/SDL.h>
#include "Tile.h"
#include <vector>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

const int WIDTH = 1920, HEIGHT = 1080;
const int SQUARE_SIZE = 900;
const int HORIZONTAL_BORDER_SIZE = (WIDTH - 2*SQUARE_SIZE)/3;
const int VERTICAL_BORDER_SIZE = (HEIGHT - SQUARE_SIZE)/2;

using namespace std;

int main (int argc, char* argv[]) {
    /*
    int sideLength;
    cout << "Enter matrix side length: ";
    cin >> sideLength; */

    srand (time(NULL));

    vector<RGB> RGBLeft;
    vector<RGB> RGBRight;
    vector<int> RowRangeEndsLeft;
    vector<int> RowRangeEndsRight;
    vector<vector<int>> ColumnRangeEndsLeft;
    vector<vector<int>> ColumnRangeEndsRight;

    RGBLeft.resize(SQUARE_SIZE*SQUARE_SIZE);
    RGBRight.resize(SQUARE_SIZE*SQUARE_SIZE);
    RowRangeEndsLeft.resize(SQUARE_SIZE);
    RowRangeEndsRight.resize(SQUARE_SIZE);
    ColumnRangeEndsLeft.resize(SQUARE_SIZE);
    ColumnRangeEndsRight.resize(SQUARE_SIZE);

    for (int i = 0; i < SQUARE_SIZE; ++i) {
        RowRangeEndsLeft[i] = i*SQUARE_SIZE;
        RowRangeEndsRight[i] = i*SQUARE_SIZE;
        ColumnRangeEndsLeft[i].resize(SQUARE_SIZE);
        ColumnRangeEndsRight[i].resize(SQUARE_SIZE);
    }

    // Initialize SDL.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL could not initialize. SDL Error: " << SDL_GetError() << endl;
    }

    // Create window.
    SDL_Window *appWindow = SDL_CreateWindow("Random Growth Matrix", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (!appWindow) {
        cout << "Could not create window: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    // Enable fullscreen. Causes weird resizing error on alt-tab.
    SDL_SetWindowFullscreen(appWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);

    // Initialize renderer. Set black background.
    SDL_Renderer* renderer = SDL_CreateRenderer(appWindow, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    auto start = chrono::steady_clock::now();
    SDL_Rect rect;
    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
    for (int i = 0; i < SQUARE_SIZE*SQUARE_SIZE; ++i) {
        RGB rgb(0, 0, 0);
        RGBLeft[i] = rgb;
        ColumnRangeEndsLeft[i/SQUARE_SIZE][i%SQUARE_SIZE] = i%900;
        rect = {(i/SQUARE_SIZE), (i%SQUARE_SIZE)+VERTICAL_BORDER_SIZE, 1, 1}; 
        SDL_RenderFillRect(renderer, &rect);
    }
    for (int i = 0; i < SQUARE_SIZE*SQUARE_SIZE; ++i) {
        RGB rgb(0, 0, 0);
        RGBRight[i] = rgb;
        ColumnRangeEndsRight[i/SQUARE_SIZE][i%SQUARE_SIZE] = i%900;
        rect = {(i/SQUARE_SIZE)+HORIZONTAL_BORDER_SIZE*2+SQUARE_SIZE, (i%SQUARE_SIZE)+VERTICAL_BORDER_SIZE, 1, 1}; 
        SDL_RenderFillRect(renderer, &rect);
    }
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << chrono::duration <double> (diff).count() << " s" << endl;

    SDL_RenderPresent(renderer);

    SDL_Event windowEvent;

    while(1) {
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT) {
                break;
            }
        }
        for (int i = 0; i < SQUARE_SIZE; ++i) {
            int randomTarget = rand() % RowRangeEndsLeft[SQUARE_SIZE-1];
            vector<int>::iterator targetRow = upper_bound(RowRangeEndsLeft.begin(), RowRangeEndsLeft.end(), randomTarget);
            int rowIndex = targetRow - RowRangeEndsLeft.begin();
            randomTarget -= RowRangeEndsLeft[rowIndex-1];
            vector<int>::iterator targetColumn = upper_bound(ColumnRangeEndsLeft[rowIndex].begin(), ColumnRangeEndsLeft[rowIndex].end(), randomTarget);
            int columnIndex = targetColumn - ColumnRangeEndsLeft[rowIndex].begin();

            if (i == 0) cout << rowIndex << " " << columnIndex << endl;
        }
        
    }

    SDL_DestroyWindow(appWindow);
    SDL_Quit();

    return EXIT_SUCCESS;
}