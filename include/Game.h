//
// Created by logan on 21.1.21..
//

#ifndef DOOMSDAY_GAME_H
#define DOOMSDAY_GAME_H

#include <vector>
#include "MoveableObject.h"

class Game {
public:
    Game() = default;
    ~Game();

    void gameTick(float dt);
    void levelLogic();
    void addMoveable(MoveableObject*);
private:
    // an array of all objects which update over time
    // for example: bullets, zombies
    std::vector<MoveableObject*> objArray;

    float timeElapsed = 0;
    float logicTick = 0;
    float previousTick = 0;
    float tickSec = 0.016; // update every 16 ms
    unsigned secondsCounter = 0;
};


#endif //DOOMSDAY_GAME_H
