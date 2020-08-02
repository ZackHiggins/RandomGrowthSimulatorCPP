#include <iostream>
#include <SDL2/SDL.h>
#include "Tile.h"
#include <vector>
#include <time.h>
#include <chrono>

const int WIDTH = 1920, HEIGHT = 1080;

using namespace std;

int main (int argc, char* argv[]) {
    int sideLength;
    cout << "Enter matrix side length: ";
    cin >> sideLength;

    Board board(sideLength);



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
    //SDL_SetWindowFullscreen(appWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);

    // Initialize renderer. Set black background.
    SDL_Renderer* renderer = SDL_CreateRenderer(appWindow, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

/*
    auto start = chrono::steady_clock::now();
    SDL_Rect rect;
    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
    for (int i = 0; i < sideLength*sideLength; ++i) {
        //cout << "i: " << i << " | row: " << i/sideLength << " | column: " << i%sideLength << endl;
        Tile tile = board.getBoard()[i/sideLength].getRow()[i%sideLength];
        rect = tile.getRect();
        SDL_RenderFillRect(renderer, &rect);
    }
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << chrono::duration <double, milli> (diff).count()/1000 << " s" << endl;*/

    /*
    
    
    SDL isn't slow. Your board/row/tile data structures are.



    */

    auto start = chrono::steady_clock::now();
    SDL_Rect rect;
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < 1080*1080; ++i) {
        SDL_SetRenderDrawColor(renderer, i%32, i%32, i%32, 255);
        rect = {420+i/1080, i%1080, 1, 1};
        SDL_RenderFillRect(renderer, &rect);
    }
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << chrono::duration <double, milli> (diff).count()/1000 << " s" << endl;

    /*
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    rect = {960, 500, 1, 1}; SDL_RenderFillRect(renderer, &rect);
    rect = {1060, 500, 2, 2}; SDL_RenderFillRect(renderer, &rect);
    rect = {1160, 500, 3, 3}; SDL_RenderFillRect(renderer, &rect);
    rect = {1260, 500, 4, 4}; SDL_RenderFillRect(renderer, &rect);
    rect = {1360, 500, 5, 5}; SDL_RenderFillRect(renderer, &rect);
    rect = {960, 600, 6, 6}; SDL_RenderFillRect(renderer, &rect);
    rect = {1060, 600, 7, 7}; SDL_RenderFillRect(renderer, &rect);
    rect = {1160, 600, 8, 8}; SDL_RenderFillRect(renderer, &rect);
    rect = {1260, 600, 9, 9}; SDL_RenderFillRect(renderer, &rect);
    rect = {1360, 600, 10, 10}; SDL_RenderFillRect(renderer, &rect);
    */
             

    SDL_RenderPresent(renderer);

    SDL_Event windowEvent;

    while(1) {
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT) {
                break;
            }
        }
    }

    SDL_DestroyWindow(appWindow);
    SDL_Quit();

    return EXIT_SUCCESS;
}