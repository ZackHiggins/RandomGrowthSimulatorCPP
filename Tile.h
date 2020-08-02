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
        RGB rgb;

    public:
        Tile(SDL_Rect rect);

        float getTileWeight();
        SDL_Rect getRect();
        RGB getRGB();

        void setTileWeight(float tileWeight);
        void setRect(SDL_Rect rect);
        void setRGB(RGB rgb);

        void changeTileHue(int colorChangeAmount);
};

class Row {
    private:
        std::vector<Tile> row;
        float rowWeight;

    public:
        Row(int rowNumber, int sideLength);

        std::vector<Tile> getRow();
        float getRowWeight();

        void setRowWeight(float rowWeight);
};

class Board {
    private:
        std::vector<Row> board;
        int sideLength;
    
    public:
        Board(int sideLength);

        std::vector<Row> getBoard();
        int getSideLength();
};

void colorConversionTest();