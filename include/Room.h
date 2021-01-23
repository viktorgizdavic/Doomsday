//
// Created by bajaks on 1/21/21.
//

#ifndef DOOMSDAY_ROOM_H
#define DOOMSDAY_ROOM_H
#include <RectangleObject.h>

class Room {
private:
    RectangleObject rect;
    RectangleObject door;
    float xTranslate=0.0f;
    float yTranslate=0.0f;
    float zTranslate=20.0f;
    float xScaling=4.0f;
    float yScaling=2.0f;
    float zScaling=4.0f;
public:
    Room(std::string texturePath,std::string specularMapPath,std::string doorTexturePath,std::string doorSpecularMapPath):rect(texturePath,specularMapPath),door(doorTexturePath,doorSpecularMapPath)
    {}

    void setup(glm::mat4 projection,glm::mat4 view,glm::vec3 viewPos,DirLight& dirLight,std::vector<PointLight>& pointLights,SpotLight& spotLight)
    {
        rect.setup(projection,view,viewPos,dirLight,pointLights,spotLight);
        door.setup(projection,view,viewPos,dirLight,pointLights,spotLight);
    }

    void draw()
    {

        glm::vec3 roomScaling(xScaling,yScaling,zScaling);
        glm::vec3 roomScalingVertical(xScaling,zScaling,yScaling);
        glm::vec3 roomTranslate(xTranslate,yTranslate,zTranslate);


        //wall with door
        rect.translate(roomScaling*(glm::vec3(-60.0f*1/2*1/2,0.0f,-60.0f)+roomTranslate));
        rect.scale(roomScaling*glm::vec3(60.0f*1/2,30.0f,1.0f));
        rect.draw();

        door.translate(roomScaling*(glm::vec3(30.0f*1/4*1/2,-30.0f*2/3*1/4,-60.0f)+roomTranslate));
        door.scale(roomScaling*glm::vec3(30.0f*1/4,30.0f*2/3,1.0f));
        door.draw();

        rect.translate(roomScaling*(glm::vec3(30.0f*1/4*1/2,30.0f*1/3,-60.0f)+roomTranslate));
        rect.scale(roomScaling*glm::vec3(30.0f*1/4,30.0f*1/3,1.0f));
        rect.draw();

        rect.translate(roomScaling*(glm::vec3(60.0f*5/12*3/4,0.0f,-60.0f)+roomTranslate));
        rect.scale(roomScaling*glm::vec3(60.0f*9/24,30.0f,1.0f));
        rect.draw();


        //side wall
        rect.translate(roomScaling*(glm::vec3(30.0f,0.0f,-30.0f)+roomTranslate));
        rect.rotate(90.0f,glm::vec3(0.0f,1.0f,0.0f));
        rect.scale(roomScaling*glm::vec3(60.0f,30.0f,1.0f));
        rect.draw();

        //side wall
        rect.translate(roomScaling*(glm::vec3(-30.0f,0.0f,-30.0f)+roomTranslate));
        rect.rotate(90.0f,glm::vec3(0.0f,1.0f,0.0f));
        rect.scale(roomScaling*glm::vec3(60.0f,30.0f,1.0f));
        rect.draw();

        //rear wall
        rect.translate(roomScaling*(glm::vec3(0.0f,0.0f,0.0f)+roomTranslate));
        rect.scale(roomScaling*glm::vec3(60.0f,30.0f,1.0f));
        rect.draw();

        //floor
        rect.translate(roomScaling*(glm::vec3(0.0f,-15.0f,-30.0f)+roomTranslate));
        rect.rotate(90.0f,glm::vec3(1.0f,0.0f,0.0f));
        rect.scale(roomScalingVertical*glm::vec3(60.0f,60.0f,1.0f));
        rect.draw();


        //ceiling

//        rect.translate(roomScaling*(glm::vec3(0.0f,15.0f,-30.0f)+roomTranslate));
//        rect.rotate(90.0f,glm::vec3(1.0f,0.0f,0.0f));
//        rect.scale(roomScalingVertical*glm::vec3(60.0f,60.0f,1.0f));
//        rect.draw();

        rect.translate(roomScaling*(glm::vec3(-60.0f*1/3,15.0f,-30.0f)+roomTranslate));
        rect.rotate(90.0f,glm::vec3(1.0f,0.0f,0.0f));
        rect.scale(roomScalingVertical*glm::vec3(60.0f*1/3,60.0f,1.0f));
        rect.draw();

        rect.translate(roomScaling*(glm::vec3(0.0f,15.0f,-30.0f-(60.0f*1/3))+roomTranslate));
        rect.rotate(90.0f,glm::vec3(1.0f,0.0f,0.0f));
        rect.scale(roomScalingVertical*glm::vec3(60.0f*1/3,60.0f*1/3,1.0f));
        rect.draw();

        rect.translate(roomScaling*(glm::vec3(-60.0f*1/6*1/2,15.0f,-30.0f)+roomTranslate));
        rect.rotate(90.0f,glm::vec3(1.0f,0.0f,0.0f));
        rect.scale(roomScalingVertical*glm::vec3(60.0f*1/6,60.0f*1/3,1.0f));
        rect.draw();

        door.translate(roomScaling*(glm::vec3(60.0f*1/6*1/2,15.0f,-30.0f-(60.0f*1/6*1/2))+roomTranslate));
        door.rotate(90.0f,glm::vec3(1.0f,0.0f,0.0f));
        door.scale(roomScalingVertical*glm::vec3(60.0f*1/6,60.0f*1/6,1.0f));
        door.draw();

        rect.translate(roomScaling*(glm::vec3(60.0f*1/6*1/2,15.0f,-30.0f+(60.0f*1/6*1/2))+roomTranslate));
        rect.rotate(90.0f,glm::vec3(1.0f,0.0f,0.0f));
        rect.scale(roomScalingVertical*glm::vec3(60.0f*1/6,60.0f*1/6,1.0f));
        rect.draw();

        rect.translate(roomScaling*(glm::vec3(0.0f,15.0f,-30.0f+(60.0f*1/3))+roomTranslate));
        rect.rotate(90.0f,glm::vec3(1.0f,0.0f,0.0f));
        rect.scale(roomScalingVertical*glm::vec3(60.0f*1/3,60.0f*1/3,1.0f));
        rect.draw();


        rect.translate(roomScaling*(glm::vec3(60.0f*1/3,15.0f,-30.0f)+roomTranslate));
        rect.rotate(90.0f,glm::vec3(1.0f,0.0f,0.0f));
        rect.scale(roomScalingVertical*glm::vec3(60.0f*1/3,60.0f,1.0f));
        rect.draw();

    }

};

#endif //DOOMSDAY_ROOM_H
