//
// Created by mfp on 10/11/16.
//


#include "MscHandler.h"

MscHandler::MscHandler(SDL_Renderer *mainRenderer) {
    this->mainRenderer = mainRenderer;
}


SDL_Texture* MscHandler::createTexture(string imageTexturePath){
    /* The loading of the background layer. since SDL_LoadBMP() returns
     * a surface, we convert it to a layer afterwards for fast accelerated
     * blitting, handdling hardware. (Surface works with software) */

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
    cout<<"ENTROOOOO";
    return backgroundTexture;
}


void MscHandler::newMscType(int ancho, int alto, Entity id, char *imagePath) {
    miscelaneaType newType;

    SDL_Texture* layer = this->createTexture(imagePath);
    SDL_QueryTexture(layer, NULL, NULL, &newType.frameWidth, &newType.frameHeigth);

    newType.ancho = ancho;
    newType.alto = alto;
    newType.id = id;
    newType.layer = layer;
    this->miscelaneasTypes.push_back(newType);
}

miscelaneaType MscHandler::getMscType(Entity id) {
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
    }
    events.clear();
}