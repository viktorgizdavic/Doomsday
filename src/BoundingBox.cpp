//
// Created by logan on 21.1.21..
//

#include "BoundingBox.h"

BoundingBox::BoundingBox(float x, float y, float z, float width, float height, float length, const std::string& color)
        : shouldShow(false), x(x), y(y), z(z), width(width), height(height), length(length)
{
    glm::vec3 c = glm::vec3(0.5f, 0.0f, 0.0f);
    if(color == "green")
        c = glm::vec3(0.0f, 0.5f, 0.0f);
    else if (color == "blue")
        c = glm::vec3(0.0f, 0.0f, 0.5f);
    boxVisual = new LightCube(c);
    minX = x - width/4;
    maxX = x + width/4;
    minY = y - height/4;
    maxY = y + height/4;
    minZ = z - length/4;
    maxZ = z + length/4;
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

auto BoundingBox::boxesIntersect(BoundingBox &box1, BoundingBox &box2) -> bool {
    return (box1.minX <= box2.maxX && box1.maxX >= box2.minX) &&
           (box1.minY <= box2.maxY && box1.maxY >= box2.minY) &&
           (box1.minZ <= box2.maxZ && box1.maxZ >= box2.minZ);
}

auto BoundingBox::pointBoxIntersect(float pointX, float pointY, float pointZ, BoundingBox &box) -> bool {
    return (pointX >= box.minX && pointX <= box.maxX) &&
           (pointY >= box.minY && pointY <= box.maxY) &&
           (pointZ >= box.minZ && pointZ <= box.maxZ);
}

auto BoundingBox::getVisual() -> LightCube * {
    return boxVisual;
}


