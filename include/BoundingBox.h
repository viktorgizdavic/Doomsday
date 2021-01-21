//
// Created by logan on 21.1.21..
//

#ifndef DOOMSDAY_BOUNDINGBOX_H
#define DOOMSDAY_BOUNDINGBOX_H


class BoundingBox {
public:
    BoundingBox(int minX, int maxX, int minY, int maxY, int minZ, int maxZ);
    void updateBox(int xDt, int yDt, int zDt);

    // checks if two boxes intersect
    static bool boxesIntersect(BoundingBox& box1, BoundingBox& box2);
    // checks if a point with (x,y,z) coords is inside a box
    static bool pointBoxIntersect(int pointX, int pointY, int pointZ, BoundingBox& box);
private:
    int minX, maxX;
    int minY, maxY;
    int minZ, maxZ;
};


#endif //DOOMSDAY_BOUNDINGBOX_H