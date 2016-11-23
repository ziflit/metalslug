#include "MscHandler.h"

MscHandler::MscHandler(SDL_Renderer *mainRenderer) {
    this->mainRenderer = mainRenderer;
}


SDL_Texture* MscHandler::createTexture(string imageTexturePath){
    SDL_Texture* backgroundTexture = NULL;
    SDL_Surface* loadingSurface = IMG_Load(imageTexturePath.c_str());
    if(loadingSurface == NULL){
        cout<<"Error loading surface image for background layer: "<<SDL_GetError()<<endl;
        loadingSurface = IMG_Load("sprites/defaultImage.png");
    }
    backgroundTexture = SDL_CreateTextureFromSurface(this->mainRenderer, loadingSurface);
    if(backgroundTexture == NULL){
        cout<<"Error creating background layer: "<<SDL_GetError()<<endl;
    }
    SDL_FreeSurface(loadingSurface);    //get rid of old loaded surface
    return backgroundTexture;
}


void MscHandler::newMscType(xmlMiscelanea miscConfig) {
    simpleSpriteType newType;

    SDL_Texture* layer = this->createTexture(miscConfig.path);
    SDL_QueryTexture(layer, NULL, NULL, &newType.frameWidth, &newType.frameHeigth);

    newType.ancho = miscConfig.ancho;
    newType.alto = miscConfig.alto;
    newType.id = miscConfig.id;
    newType.layer = layer;
    this->miscelaneasTypes.push_back(newType);
}

simpleSpriteType MscHandler::getMscType(Entity id) {
    for (auto type : miscelaneasTypes) {
        if (id == type.id) {
            return type;
        }
    }
}

MiscelaneaSprite *MscHandler::createMiscelaneaType(Entity id) {
    return (new MiscelaneaSprite(mainRenderer, getMscType(id)));
}

bool MscHandler::isMscType(Entity id) {
    for (auto type : miscelaneasTypes) {
        if (id == type.id) {
            return true;
        }
    }
    return false;
}

void MscHandler::handle(event newEvent) {
    this->events.push_back(newEvent);
}

void MscHandler::updateMiscelaneaSprites() {
    for (auto event : events ) {
        MiscelaneaSprite* misc = createMiscelaneaType(event.data.id);
        misc->handle(event);
        misc->actualizarDibujo();
        delete misc;
    }
    events.clear();
}