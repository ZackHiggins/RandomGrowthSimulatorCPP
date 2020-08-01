#include <SDL2/SDL.h>
#include <vector>

typedef struct RGB {
    float red, green, blue;

    RGB();
    RGB(int red, int green, int blue);
} RGB;

typedef struct HSV {
    float hue, saturation, value;

    HSV();
    HSV(float hue, float saturation, float value);
} HSV;

HSV RGBtoHSV(RGB rgb);
RGB HSVtoRGB(HSV hsv);

class Tile {
    private:
        float tileWeight;
        SDL_Rect rect;

    public:
        Tile();
        Tile(SDL_Rect rect);

        float getTileWeight();
        void changeTileHue(int colorChangeAmount);
};

class Row {
    private:
        vector<Tile> row;
        float rowWeight;

    public:
        Row();
        float getRowWeight();
};

class Board {
    private:
        vector<Row> board;
        int sideLength;
    
    public:
        Board();
        Board(int sideLength);

        int getSideLength();
};