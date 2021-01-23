//
// Created by logan on 21.1.21..
//

#include "BoundingBox.h"

BoundingBox::BoundingBox(float x, float y, float z, float width, float height)
        : shouldShow(false), x(x), y(y), z(z), width(width), height(height)
{
    boxVisual = new LightCube(glm::vec3(1.0f, 0.0f, 0.0f));
    minX = x - width/2;
    maxX = x + width/2;
    minY = y - height/2;
    maxY = y + height/2;
    minZ = z - width/2;
    maxZ = z + width/2;
}

BoundingBox::~BoundingBox() {
    delete boxVisual;
}

void BoundingBox::updateBox(float xDt, float yDt, float zDt) {
    minX += xDt;
    maxX += xDt;
    minY += yDt;
    maxY += yDt;
    minZ += zDt;
    maxZ += zDt;
}

bool BoundingBox::boxesIntersect(BoundingBox &box1, BoundingBox &box2) {
    return (box1.minX <= box2.maxX && box1.maxX >= box2.minX) &&
           (box1.minY <= box2.maxY && box1.maxY >= box2.minY) &&
           (box1.minZ <= box2.maxZ && box1.maxZ >= box2.minZ);
}

bool BoundingBox::pointBoxIntersect(float pointX, float pointY, float pointZ, BoundingBox &box) {
    return (pointX >= box.minX && pointX <= box.maxX) &&
           (pointY >= box.minY && pointY <= box.maxY) &&
           (pointZ >= box.minZ && pointZ <= box.maxZ);
}

LightCube *BoundingBox::getVisual() {
    return boxVisual;
}


