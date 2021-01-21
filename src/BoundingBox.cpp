//
// Created by logan on 21.1.21..
//

#include "BoundingBox.h"

BoundingBox::BoundingBox(int minX, int maxX, int minY, int maxY, int minZ, int maxZ)
    : minX(minX), maxX(maxX), minY(minY), maxY(maxY), minZ(minZ), maxZ(maxZ)
{}

void BoundingBox::updateBox(int xDt, int yDt, int zDt) {
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

bool BoundingBox::pointBoxIntersect(int pointX, int pointY, int pointZ, BoundingBox &box) {
    return (pointX >= box.minX && pointX <= box.maxX) &&
           (pointY >= box.minY && pointY <= box.maxY) &&
           (pointZ >= box.minZ && pointZ <= box.maxZ);
}


