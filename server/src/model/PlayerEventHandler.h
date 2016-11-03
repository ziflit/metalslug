
#ifndef SERVER_KEYHANDLER_H
#define SERVER_KEYHANDLER_H


#include "../utils/Protocol.h"
#include "game/Player.h"
#include "EventHandler.h"

class PlayerEventHandler : public EventHandler {
public:
    virtual void handle(EventCode eventCode, AnimatedObject *animatedObject) override;

private:
    void handleRealeasedKey(EventCode eventCode, AnimatedObject *animatedObject);

    void handlePressedKey(EventCode eventCode, AnimatedObject *animatedObject);

    bool isKeyPressed(EventCode eventCode);

    bool isKeyRealeased(EventCode eventCode);

public:
    PlayerEventHandler();
};


#endif //SERVER_KEYHANDLER_H
