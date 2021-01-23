//
// Created by logan on 21.1.21..
//

#ifndef DOOMSDAY_BOUNDINGBOX_H
#define DOOMSDAY_BOUNDINGBOX_H

#include "LightCube.h"


class BoundingBox {
public:
    BoundingBox(float x, float y, float z, float width, float height, float length, const std::string& color);
    ~BoundingBox();
    void updateBox(float xDt, float yDt, float zDt);
    LightCube* getVisual();

    // checks if two boxes intersect
    static bool boxesIntersect(BoundingBox& box1, BoundingBox& box2);
    // checks if a point with (x,y,z) coords is inside a box
    static bool pointBoxIntersect(float pointX, float pointY, float pointZ, BoundingBox& box);

    bool shouldShow;
    float width, height, length;
private:
    float minX, maxX;
    float minY, maxY;
    float minZ, maxZ;
    float x, y, z;

    LightCube* boxVisual;
};


#endif //DOOMSDAY_BOUNDINGBOX_H