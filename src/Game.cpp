//
// Created by logan on 21.1.21..
//

#include <iostream>
#include "Game.h"

void Game::gameTick(float dt, glm::mat4 projection, glm::mat4 view, glm::vec3& cameraPosition) {
    timeElapsed += dt;
    previousFire -= dt;
    bool tickUpdate = (timeElapsed-previousTick) >= tickSec;
    auto p = objArray.begin();
    for(; p != objArray.end(); ++p) {
        if((*p)->shouldDelete)
            continue;
        // tick the movement and check for collisions
        // TODO: complexity is O(n^2) at the moment, find a better way to do this
        if(tickUpdate && (*p)->checkMove()) {
            MoveableObject* bumpedObj = moveLookahead(*p);
            if(bumpedObj == nullptr) {
                (*p)->move();
            }
            else {
                if((*p)->priorityLevel == 0) {
                    (*p)->shouldDelete = true;
                    if(bumpedObj->priorityLevel == 2) {
                        bumpedObj->health -= 40;
                        if(bumpedObj->health <= 0) {
                            bumpedObj->shouldDelete = true;
                            std::cout << "Killed zombie" << std::endl;
                        }
                    }
                }
            }
        }

        // we have to redraw them every render loop iteration
        (*p)->draw(*savedShader, projection, view, cameraPosition, savedDirLight, savedPointLights, savedSpotLight);
        if((*p)->life) {
            if((*p)->lifespan <= 0) {
                (*p)->shouldDelete = true;
                continue;
            } else {
                (*p)->lifespan -= dt;
            }
        }
    }

    for(; p!= objArray.end(); ++p) {
        if((*p)->shouldDelete) {
            objArray.erase(p);
            delete *p;
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
    if(secondsCounter == 5) {
        auto testZombie = new MoveableObject(glm::vec3 (0.0f, -15.0f, -150.0f), glm::vec3 (0.0f, 0.0f, 0.0f), 15.0f, 50.0f, 15.0f, 2, "green");
        testZombie->model = zombieModel;
        //testZombie->setShow(true);
        addMoveable(testZombie);
    }
    if(secondsCounter == 10) {
        auto testZombie = new MoveableObject(glm::vec3 (0.0f, -15.0f, -150.0f), glm::vec3 (0.0f, 0.0f, 0.0f), 15.0f, 50.0f, 15.0f, 2, "blue");
        testZombie->model = zombieModel;
        //testZombie->setShow(true);
        addMoveable(testZombie);
    }
    for(auto &p: objArray) {
        if(p->priorityLevel == 2) {
            if (!p->shouldDelete) {
                // TODO: rotate the zombie model to face player as it chases them
                /*glm::vec3 currDir = glm::normalize(
                        glm::vec3(playerObj->currentPosition - p->currentPosition)
                );
                glm::vec3 oldDir = glm::normalize(
                        glm::vec3(playerObj->currentPosition - p->oldPosition)
                );
                p->movementDir = 0.1f * currDir;
                float cos = glm::dot(-currDir, -oldDir);
                p->model->setRotateVect(glm::degrees(glm::acos(cos)), glm::vec3(1.0f, 0.0f, 0.0f));*/

                glm::vec3 currDir = glm::normalize(
                        glm::vec3(playerObj->currentPosition - p->currentPosition)
                );
                p->movementDir = 0.1f * currDir;
            }
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

    delete bullet;
}

void Game::shoot(glm::vec3 position, glm::vec3 direction) {
    if(previousFire <= 0) {
        float speed = 1;
        auto testBullet = new MoveableObject(position + 5.0f*direction, speed*direction, 0.2f, 0.2f, 0.2f, 0, "red");
        testBullet->model = bullet;
        testBullet->setShow(true);
        testBullet->life = true;
        previousFire = fireRate;
        addMoveable(testBullet);
    }
}

MoveableObject* Game::moveLookahead(MoveableObject * o) {
    if(o->shouldDelete) return nullptr;

    // by default it didn't collide with anything
    MoveableObject* retVal = nullptr;
    float dx = o->movementDir.x;
    float dy = o->movementDir.y;
    float dz = o->movementDir.z;

    // lookahead
    o->hitbox->updateBox(dx, dy, dz);

    // test for potential collisions
    for (auto p: objArray) {
        if(p->shouldDelete) continue;
        if(p == o) continue;
        if((o->priorityLevel == 0 && p->priorityLevel == 0) ||
            (o->priorityLevel == 0 && p->priorityLevel == 1)) continue;
        //if(o->priorityLevel > p->priorityLevel) continue;
        if(BoundingBox::boxesIntersect(*(p->hitbox), *(o->hitbox))) {
            retVal = p;
            break;
        }
    }

    // reset to old values
    o->hitbox->updateBox(-dx, -dy, -dz);
    return retVal;
}
