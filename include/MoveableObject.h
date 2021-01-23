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
    // TODO: create a bounding box alongside the object, and update it as the object moves
    MoveableObject(glm::vec3 pos, glm::vec3 moveDir, float width, float height);
    virtual ~MoveableObject();
    virtual void move();
    void draw(glm::mat4 projection, glm::mat4 view);
    void setShow(bool value);

    BoundingBox* hitbox;
    bool shouldDelete;
private:
    glm::vec3 currentPosition;
    glm::vec3 movementDir;
};


#endif //DOOMSDAY_MOVEABLEOBJECT_H
