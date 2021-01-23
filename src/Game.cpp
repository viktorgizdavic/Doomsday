//
// Created by logan on 21.1.21..
//

#include <iostream>
#include "Game.h"

void Game::gameTick(float dt, glm::mat4 projection, glm::mat4 view) {
    timeElapsed += dt;
    bool tickUpdate = (timeElapsed-previousTick) >= tickSec;
    for(auto p = objArray.begin(); p != objArray.end(); ++p) {
        // tick the movement and check for collisions
        // TODO: complexity is O(n^2) at the moment, find a better way to do this
        if(tickUpdate) {
            (*p)->move();
            auto other = objArray.begin();
            while(other != objArray.end()) {
                if(p != other) {
                    if(BoundingBox::boxesIntersect(*(*p)->hitbox, *(*other)->hitbox)) {
                        std::cout << "object collision" << std::endl;
                        /*delete *other;
                        objArray.erase(other);*/
                    }
                }
                other++;
            }
        }

        // we have to redraw them every render loop iteration
        (*p)->draw(projection, view);
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
