#ifndef METALSLUG_TEXTBOX_H
#define METALSLUG_TEXTBOX_H

#include <SDL2/SDL_system.h>
#include <SDL2/SDL_ttf.h>
#include "string"

using namespace std;
class TextBox {
public:
    TextBox(char *text, SDL_Renderer* mainRenderer, SDL_Color color);
    void changeText(char *text);
    void changeText(int number);
    void renderize(int x, int y);
    void renderize();

private:
    TTF_Font *font;
    SDL_Color color;
    SDL_Texture *text;
    SDL_Renderer* mainRenderer;
    SDL_Rect textRect;

    TTF_Font *loadfont(char *file, int ptsize);
};


#endif //METALSLUG_TEXTBOX_H
