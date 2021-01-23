//
// Created by logan on 21.1.21..
//

#ifndef DOOMSDAY_MOVEABLEOBJECT_H
#define DOOMSDAY_MOVEABLEOBJECT_H

// this class is to be extended by all updateable objects
// example: bullets

#include "BoundingBox.h"

class MoveableObject {
public:
    MoveableObject(glm::vec3 pos, glm::vec3 moveDir, float width, float height, float length, unsigned int priority, const std::string& color);
    virtual ~MoveableObject();
    virtual void move();
    void draw(glm::mat4 projection, glm::mat4 view);
    void setShow(bool value) const;
    void setMove(bool value);
    bool checkMove() const;

    BoundingBox* hitbox;
    bool shouldDelete;
    bool life = false;
    unsigned int priorityLevel;
    float lifespan = 2.0f;
    float health = 100;
    glm::vec3 currentPosition;
    glm::vec3 movementDir;
private:
    bool canMove = true;
};


#endif //DOOMSDAY_MOVEABLEOBJECT_H
