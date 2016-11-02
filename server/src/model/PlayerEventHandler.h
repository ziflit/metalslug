
#ifndef SERVER_KEYHANDLER_H
#define SERVER_KEYHANDLER_H


#include "../utils/Protocol.h"
#include "game/Player.h"
#include "EventHandler.h"

class PlayerEventHandler : public EventHandler {
public:
    virtual void handle(EventCode eventCode, GameObject *gameObject) override;

private:
    void handleRealeasedKey(EventCode eventCode, Player *player);

    void handlePressedKey(EventCode eventCode, Player *player);

    bool isKeyPressed(EventCode eventCode);

    bool isKeyRealeased(EventCode eventCode);

public:
    PlayerEventHandler();
};


#endif //SERVER_KEYHANDLER_H
