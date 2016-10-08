#ifndef SDLBASE_SDLRUNNINGGAME_H
#define SDLBASE_SDLRUNNINGGAME_H

#define window_width 1200
#define window_height 700
#define backgroundTransparentPath "sprites/backgroundTransparent.bmp"
#define fps  30 //tasa de refrescamiento, fotogramas por segundo
#define speedSprite 10
#define gameMusicPath "audios/circuit.wav"

#include "PlayerSprite.h"
#include "AudioToolsForRunningGame.h"

using namespace std;

class SDLRunningGame {
private:
    SDL_Window* mainWindow;
    SDL_Renderer* mainRenderer;
    Mix_Music* music;
    SDL_Texture *backgroundLayer0, *backgroundLayer1, *playersLayer, *cloudLayer;
    BackgroundSprite *backgroundSprite0,*backgroundSprite1, *backgroundPlayersSprite, *cloudSprite;
    PlayerSprite *player0Sprite;
    //,*player1Sprite,*player2Sprite,*player3Sprite;


public:
    SDLRunningGame();

    SDL_Window* createWindow(const char* windowName);

    SDL_Renderer* createRenderer(SDL_Window* window);

    void initialWindow();

    void initializeMixer();

    void initializeSDL();
    void audioInitialization();
    SDL_Texture* createTransparentTexture(SDL_Renderer *renderer);
    SDL_Texture* loadTexture(SDL_Renderer* renderer,string imageTexturePath);

    void layersBuilding();

    void spritesBuilding();

    void updateWindowSprites();

    PlayerSprite* getPlayerSprite(){ return SDLRunningGame::player0Sprite;}

    BackgroundSprite* getBackgroundPlayerSprite(){ return SDLRunningGame::backgroundPlayersSprite;}

    SDL_Window* getMainWindow(){return SDLRunningGame::mainWindow;}

    SDL_Renderer* getMainRenderer(){ return SDLRunningGame::mainRenderer;}

    ~SDLRunningGame();

};


#endif //SDLBASE_SDLRUNNINGGAME_H
