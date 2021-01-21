//
// Created by logan on 21.1.21..
//

#include <iostream>
#include "Game.h"

void Game::gameTick(float dt) {
    timeElapsed += dt;
    if((timeElapsed-previousTick) >= tickSec) {
        previousTick = timeElapsed;

        //every tick, call update for all objects in objArray
        for(auto &p: objArray) {
            p->update();
        }
    }
    if((timeElapsed - logicTick) >= 1) {
        logicTick = timeElapsed;
        levelLogic();
    }
}

void Game::levelLogic() {
    // this function ticks every second, easier to work with for spawning etc
    secondsCounter++;
    std::cout << "seconds: " << secondsCounter << std::endl;
    switch(secondsCounter) {
        case 5: {
            // spawn a zombie or something
            // don't forget to add it to objArray
        }
    }

}

void Game::addMoveable(MoveableObject* mo) {
    objArray.push_back(mo);
}

Game::~Game() {
    for(auto &p: objArray) {
        delete p;
    }
}
