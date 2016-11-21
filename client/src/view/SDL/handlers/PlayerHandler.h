#ifndef METALSLUG_PLAYERHANDLER_H
#define METALSLUG_PLAYERHANDLER_H


#include <SDL2/SDL_system.h>
#include "../spriteClasses/PlayerSprite.h"

class PlayerHandler {
private:
    SDL_Renderer *mainRenderer;
    vector<PlayerSprite*> playersSprites;
public:

    PlayerHandler(SDL_Renderer *mainRenderer);

    void addNewPlayer(PlayerSprite *newPlayer);

    bool isPlayerId(Entity id);

    void handle(event newEvent);

    void updatePlayersSprites();

    virtual ~PlayerHandler();

    void deletePlayer(vector<PlayerSprite *>::iterator it);

    vector<PlayerSprite *> getPlayers();
};
#endif //METALSLUG_PLAYERHANDLER_H