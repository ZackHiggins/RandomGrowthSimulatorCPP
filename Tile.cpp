#include "Tile.h"
#include <math.h>
#include <iostream>

using namespace std;

RGB::RGB() {
    red = 0.0f;
    green = 0.0f;
    blue = 0.0f;
}
RGB::RGB(int red, int green, int blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}
HSV::HSV() {
    hue = 0.0f;
    saturation = 0.0f;
    value = 0.0f;
}
HSV::HSV(float hue, float saturation, float value) {
    this->hue = hue;
    this->saturation = saturation;
    this->value = value;
}

// Converts given RGB to HSV.
HSV RGBtoHSV(RGB rgb) {
    HSV hsv;
    
    rgb.red /= 255.0f;
    rgb.green /= 255.0f;
    rgb.blue /= 255.0f;

    float max = fmax(rgb.red, rgb.green);
    max = fmax(max, rgb.blue);
    float min = fmin(rgb.red, rgb.green);
    min = fmin(min, rgb.blue);

    float difference = max - min;

    if (!difference) {
        hsv.hue = 0;
    }
    else {
        if (max == rgb.red) {
            hsv.hue = 60 * fmod(((rgb.green-rgb.blue)/difference), 6);
        }
        if (max == rgb.green) {
            hsv.hue = 60 * (((rgb.blue - rgb.red)/difference) + 2);
        }
        if (max == rgb.blue) {
            hsv.hue = 60 * (((rgb.red - rgb.green)/difference) + 4);
        }
    }

    if (!max) {
        hsv.saturation = 0;
    }
    else {
        hsv.saturation = difference / max;
    }

    hsv.value = max;
    return hsv;
}
// Converts given HSV to RGB.
RGB HSVtoRGB(HSV hsv) {
    RGB rgb;

    float chroma = hsv.saturation * hsv.value; // 1
    float x = chroma * (1 - fabs(fmod((hsv.hue/60.0f), 2) - 1)); // 0
    float m = hsv.value - chroma; // 0

    if (0 <= hsv.hue && hsv.hue <= 60) {
        rgb.red = chroma;
        rgb.green = x;
        rgb.blue = 0;
    } else if (60 <= hsv.hue && hsv.hue < 120) {
        rgb.red = x;
        rgb.green = chroma;
        rgb.blue = 0;
    } else if (120 <= hsv.hue && hsv.hue < 180) {
        rgb.red = 0;
        rgb.green = chroma;
        rgb.blue = x;
    } else if (180 <= hsv.hue && hsv.hue < 240) {
        rgb.red = 0;
        rgb.green = x;
        rgb.blue = chroma;
    } else if (240 <= hsv.hue && hsv.hue < 300) {
        rgb.red = x;
        rgb.green = 0;
        rgb.blue = chroma;
    } else if (300 <= hsv.hue && hsv.hue < 360) {
        rgb.red = chroma;
        rgb.green = 0;
        rgb.blue = x;
    } else {
        std::cerr << "Hue out of bounds." << std::endl;
    }

    rgb.red = 255 * (rgb.red + m);
    rgb.green = 255 * (rgb.green + m);
    rgb.blue = 255 * (rgb.blue + m);

    return rgb;
}

Tile::Tile(SDL_Rect rect) {
    this->tileWeight = 1;
    this->rect = rect;
    this->rgb = {60, 60, 60};
}
float Tile::getTileWeight() {
    return tileWeight;
}
SDL_Rect Tile::getRect() {
    return rect;
}
RGB Tile::getRGB() {
    return rgb;
}
void Tile::setTileWeight(float tileWeight) {
    this->tileWeight = tileWeight;
}
void Tile::setRect(SDL_Rect rect) {
    this->rect = rect;
}
void Tile::setRGB(RGB rgb) {
    this->rgb = rgb;
}
// Increments tile hue by colorChangeAmount.
void Tile::changeTileHue(int colorChangeAmount) {
    HSV hsv = RGBtoHSV(rgb);
    hsv.hue = fmod((hsv.hue + colorChangeAmount), 360.0f);
    rgb = HSVtoRGB(hsv);
}

Row::Row(int rowNumber, int sideLength) {
    row.reserve(sideLength);
    for (int i = 0; i < sideLength; ++i) {
        row.push_back(Tile({rowNumber, i, 1, 1}));
    }
    rowWeight = sideLength;
}
std::vector<Tile> Row::getRow() {
    return row;
}
float Row::getRowWeight() {
    return rowWeight;
}
void Row::setRowWeight(float rowWeight) {
    this->rowWeight = rowWeight;
}

Board::Board(int sideLength) {
    board.reserve(sideLength);
    for (int i = 0; i < sideLength; ++i) {
        board.push_back(Row(i, sideLength));
    }
}
std::vector<Row> Board::getBoard() {
    return board;
}
int Board::getSideLength(){
    return sideLength;
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