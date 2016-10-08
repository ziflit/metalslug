#include "SDLRunningGame.h"

void SDLRunningGame::initializeSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) ==
        -1) { //inicializa TIMER, VIDEO, AUDIO, JOISTICK, HAPTIC,GAMECONTROLLER, EVENTS...
        cout<<"There was error initializing SDL: "<< endl
            <<SDL_GetError() << endl;
    }
}

void SDLRunningGame::initializeMixer() {
    if( ( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096 ) ) == -1 ){
        //2-> set for stereo or 1 for mono, 4096->magia negra
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
    };
}

SDL_Renderer* SDLRunningGame::createRenderer(SDL_Window* window){
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(renderer == NULL){
        cout<<"There was error creating renderer: "<<SDL_GetError()<<endl;
    }
    return renderer;
}

SDL_Window* SDLRunningGame::createWindow(const char* windowName){
    SDL_Window *window = SDL_CreateWindow(windowName,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          window_width,
                                          window_height,
                                          SDL_WINDOW_RESIZABLE);


    if(window == NULL){
        cout<<"There was error initializing the window: "<< endl
            <<SDL_GetError() << endl;
    }

    return window;

}


SDL_Texture* SDLRunningGame::loadTexture(SDL_Renderer* renderer,string imageTexturePath){
    /* The loading of the background layer. since SDL_LoadBMP() returns
     * a surface, we convert it to a layer afterwards for fast accelerated
     * blitting, handdling hardware. (Surface works with software) */

    SDL_Texture* backgroundTexture = NULL;
    SDL_Surface* loadingSurface = IMG_Load(imageTexturePath.c_str());

    if(loadingSurface == NULL)
        cout<<"Error loading surface image for background layer: "<<SDL_GetError()<<endl;

    else {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
        if(backgroundTexture == NULL){
            cout<<"Error creating background layer: "<<SDL_GetError()<<endl;

        }

        SDL_FreeSurface(loadingSurface);    //get rid of old loaded surface
        return backgroundTexture;
    }
}

SDL_Texture* SDLRunningGame::createTransparentTexture(SDL_Renderer *renderer){
    return loadTexture(renderer,backgroundTransparentPath);
}

void SDLRunningGame::initialWindow () {
    SDLRunningGame::initializeMixer();
    SDLRunningGame::initializeSDL();

    SDLRunningGame::mainWindow = SDLRunningGame::createWindow("METAL SLUG");
    SDLRunningGame::mainRenderer = SDLRunningGame::createRenderer(SDLRunningGame::mainWindow);


}

void SDLRunningGame::audioInitialization () {
    //Audio Initialization

    SDLRunningGame::music = createMusic((char *) gameMusicPath);
    playMusicForever(SDLRunningGame::music);

}
void SDLRunningGame::layersBuilding (){
    //Layers Building
    SDLRunningGame::backgroundLayer0 = SDLRunningGame::createTransparentTexture(SDLRunningGame::mainRenderer);
    SDLRunningGame::backgroundLayer1 = SDLRunningGame::createTransparentTexture(SDLRunningGame::mainRenderer);
    SDLRunningGame::cloudLayer = SDLRunningGame::createTransparentTexture(SDLRunningGame::mainRenderer);
    SDLRunningGame::playersLayer = SDLRunningGame::createTransparentTexture(SDLRunningGame::mainRenderer);
}
void SDLRunningGame::spritesBuilding () {
    //Sprites Building
    SDLRunningGame::backgroundSprite0 = new BackgroundSprite(SDLRunningGame::backgroundLayer0,
                                                         SDLRunningGame::mainRenderer);
    SDLRunningGame::backgroundSprite0->setUpImage("sprites/backgrounds/backgroundMetal1.png");

    SDLRunningGame::backgroundSprite1 = new BackgroundSprite(SDLRunningGame::backgroundLayer1,
                                                         SDLRunningGame::mainRenderer);
    backgroundSprite1->setUpImage("sprites/backgrounds/backgroundMetal2.png");
    backgroundSprite1->set_position(0, window_height / 2);
    backgroundSprite1->setHeight(window_height / 2);

    SDLRunningGame::cloudSprite = new BackgroundSprite(SDLRunningGame::cloudLayer, SDLRunningGame::mainRenderer);
    SDLRunningGame::cloudSprite->setUpImage("sprites/backgrounds/nube.png");
    SDLRunningGame::cloudSprite->setWidth(200);
    SDLRunningGame::cloudSprite->setHeight(80);
    SDLRunningGame::cloudSprite->set_position(0, 100);

    SDLRunningGame::player0Sprite = new PlayerSprite(SDLRunningGame::playersLayer, SDLRunningGame::mainRenderer);
    SDLRunningGame::player0Sprite->setUpImage("sprites/examplePlayerSprite.png", 3, 4);
}

SDLRunningGame::SDLRunningGame () {

    SDLRunningGame::initialWindow();
//_______________________________________________________________________________________
    SDLRunningGame::layersBuilding();
//_______________________________________________________________________________________
    SDLRunningGame::spritesBuilding();
//_______________________________________________________________________________________
    SDLRunningGame::audioInitialization();
//____________________________________________________________________________________________

}


void SDLRunningGame::updateWindowSprites () {
    SDL_RenderClear(SDLRunningGame::mainRenderer);

    SDLRunningGame::backgroundSprite0->update();
    SDLRunningGame::backgroundSprite1->update();
    SDLRunningGame::player0Sprite->update();
    SDLRunningGame::cloudSprite->update();

    SDL_RenderPresent(SDLRunningGame::mainRenderer);
}

//DESTRUCTOR
SDLRunningGame::~SDLRunningGame () {
    SDL_DestroyTexture(SDLRunningGame::backgroundLayer0);
    SDL_DestroyTexture(SDLRunningGame::backgroundLayer1);
    SDL_DestroyTexture(SDLRunningGame::cloudLayer);
    SDL_DestroyTexture(SDLRunningGame::playersLayer);
//____________________________________________________________________________________________
    Mix_CloseAudio();   //Shutdown and cleanup the mixer API
    SDL_DestroyRenderer(SDLRunningGame::mainRenderer);
    SDL_DestroyWindow(SDLRunningGame::mainWindow);
    SDL_Quit();
}


