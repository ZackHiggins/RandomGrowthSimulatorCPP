#include <iostream>
#include <SDL2/SDL.h>
#include "Tile.h"
#include <vector>

const int WIDTH = 1920, HEIGHT = 1080;

using namespace std;

void colorConversionTest();
Board makeBoard(int sideLength);

int main (int argc, char* argv[]) {
    int sideLength;
    cout << "Enter matrix side length: ";
    cin >> sideLength;

    makeBoard(sideLength);

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

    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_Rect rect({(1920-sideLength)/2, (1080-sideLength)/2, sideLength, sideLength});
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    rect = {540, 0, 100, 100};
    SDL_RenderFillRect(renderer, &rect);


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

void colorConversionTest() {
    RGB
        black(0, 0, 0),
        white(255, 255, 255),
        red(255, 0, 0),
        lime(0, 255, 0),
        blue(0, 0, 255),
        yellow(255, 255, 0),
        cyan(0, 255, 255),
        magenta(255, 0, 255),
        silver(191, 191, 191),
        grey(128, 128, 128),
        maroon(128, 0, 0),
        olive(128, 128, 0),
        green(0, 128, 0),
        purple(128, 0, 128),
        teal(0, 128, 128),
        navy(0, 0, 128);

    HSV
        hblack = RGBtoHSV(black),
        hwhite = RGBtoHSV(white),
        hred = RGBtoHSV(red), 
        hlime = RGBtoHSV(lime),
        hblue = RGBtoHSV(blue),
        hyellow = RGBtoHSV(yellow),
        hcyan = RGBtoHSV(cyan),
        hmagenta = RGBtoHSV(magenta),
        hsilver = RGBtoHSV(silver),
        hgrey = RGBtoHSV(grey),
        hmaroon = RGBtoHSV(maroon),
        holive = RGBtoHSV(olive),
        hgreen = RGBtoHSV(green),
        hpurple = RGBtoHSV(purple),
        hteal = RGBtoHSV(teal),
        hnavy = RGBtoHSV(navy);

    RGB
        rblack = HSVtoRGB(hblack),
        rwhite = HSVtoRGB(hwhite),
        rred = HSVtoRGB(hred), 
        rlime = HSVtoRGB(hlime),
        rblue = HSVtoRGB(hblue),
        ryellow = HSVtoRGB(hyellow),
        rcyan = HSVtoRGB(hcyan),
        rmagenta = HSVtoRGB(hmagenta),
        rsilver = HSVtoRGB(hsilver),
        rgrey = HSVtoRGB(hgrey),
        rmaroon = HSVtoRGB(hmaroon),
        rolive = HSVtoRGB(holive),
        rgreen = HSVtoRGB(hgreen),
        rpurple = HSVtoRGB(hpurple),
        rteal = HSVtoRGB(hteal),
        rnavy = HSVtoRGB(hnavy);
    
    cout << "RGBtoHSV: " << endl;
    cout << "Black: " << hblack.hue << " " << hblack.saturation << " " << hblack.value << endl;
    cout << "White: " << hwhite.hue << " " << hwhite.saturation << " " << hwhite.value << endl;
    cout << "Red: " << hred.hue << " " << hred.saturation << " " << hred.value << endl;
    cout << "Lime: " << hlime.hue << " " << hlime.saturation << " " << hlime.value << endl;
    cout << "Blue: " << hblue.hue << " " << hblue.saturation << " " << hblue.value << endl;
    cout << "Yellow: " << hyellow.hue << " " << hyellow.saturation << " " << hyellow.value << endl;
    cout << "Cyan: " << hcyan.hue << " " << hcyan.saturation << " " << hcyan.value << endl;
    cout << "Magenta: " << hmagenta.hue << " " << hmagenta.saturation << " " << hmagenta.value << endl;
    cout << "Silver: " << hsilver.hue << " " << hsilver.saturation << " " << hsilver.value << endl;
    cout << "Grey: " << hgrey.hue << " " << hgrey.saturation << " " << hgrey.value << endl;
    cout << "Maroon: " << hmaroon.hue << " " << hmaroon.saturation << " " << hmaroon.value << endl;
    cout << "Olive: " << holive.hue << " " << holive.saturation << " " << holive.value << endl;
    cout << "Green: " << hgreen.hue << " " << hgreen.saturation << " " << hgreen.value << endl;
    cout << "Purple: " << hpurple.hue << " " << hpurple.saturation << " " << hpurple.value << endl;
    cout << "Teal: " << hteal.hue << " " << hteal.saturation << " " << hteal.value << endl;
    cout << "Navy: " << hnavy.hue << " " << hnavy.saturation << " " << hnavy.value << endl;

    cout << endl << "HSVtoRGB: " << endl;
    cout << "Black: " << rblack.red << " " << rblack.green << " " << rblack.blue << endl;
    cout << "Write: " << rwhite.red << " " << rwhite.green << " " << rwhite.blue << endl;
    cout << "Red: " << rred.red << " " << rred.green << " " << rred.blue << endl;
    cout << "Lime: " << rlime.red << " " << rlime.green << " " << rlime.blue << endl;
    cout << "Blue: " << rblue.red << " " << rblue.green << " " << rblue.blue << endl;
    cout << "Yellow: " << ryellow.red << " " << ryellow.green << " " << ryellow.blue << endl;
    cout << "Cyan: " << rcyan.red << " " << rcyan.green << " " << rcyan.blue << endl;
    cout << "Magenta: " << rmagenta.red << " " << rmagenta.green << " " << rmagenta.blue << endl;
    cout << "Silver: " << rsilver.red << " " << rsilver.green << " " << rsilver.blue << endl;
    cout << "Grey: " << rgrey.red << " " << rgrey.green << " " << rgrey.blue << endl;
    cout << "Maroon: " << rmaroon.red << " " << rmaroon.green << " " << rmaroon.blue << endl;
    cout << "Olive: " << rolive.red << " " << rolive.green << " " << rolive.blue << endl;
    cout << "Green: " << rgreen.red << " " << rgreen.green << " " << rgreen.blue << endl;
    cout << "Purple: " << rpurple.red << " " << rpurple.green << " " << rpurple.blue << endl;
    cout << "Teal: " << rteal.red << " " << rteal.green << " " << rteal.blue << endl;
    cout << "Navy: " << rnavy.red << " " << rnavy.green << " " << rnavy.blue << endl;
}

Board boardManager(int sideLength) {

    
}