#include "Tile.h"
#include <math.h>
#include <iostream>

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

// Increments tile hue by colorChangeAmount.
void Tile::changeTileHue(int colorChangeAmount) {

}