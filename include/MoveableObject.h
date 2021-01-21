//
// Created by logan on 21.1.21..
//

#ifndef DOOMSDAY_MOVEABLEOBJECT_H
#define DOOMSDAY_MOVEABLEOBJECT_H

// this class is to be extended by all updateable objects
// example: bullets

class MoveableObject {
public:
    // TODO: create a bounding box alongside the object, and update it as the object moves
    MoveableObject();
    void update();
};


#endif //DOOMSDAY_MOVEABLEOBJECT_H
