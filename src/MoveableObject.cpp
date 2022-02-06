//
// Created by logan on 21.1.21..
//
#include <iostream>
#include "MoveableObject.h"

MoveableObject::MoveableObject(glm::vec3 pos, glm::vec3 moveDir, float width, float height, float length, unsigned int priority, const std::string& color)
    : shouldDelete(false), priorityLevel(priority), currentPosition(pos), movementDir(moveDir)
{
    hitbox = new BoundingBox(pos.x, pos.y, pos.z, width, height, length, color);
}

MoveableObject::~MoveableObject() {
    delete hitbox;
}

void MoveableObject::draw(Shader& shader, glm::mat4& projection, glm::mat4& view,glm::vec3& cameraPos, DirLight *savedDirLight,
                          std::vector<PointLight> *savedPointLights, SpotLight *savedSpotLight) {
    if(hitbox->shouldShow) {
        hitbox->getVisual()->setup(projection, view);
        hitbox->getVisual()->translate(currentPosition);
        hitbox->getVisual()->scale(glm::vec3(hitbox->width/2, hitbox->height/2, hitbox->length/2));
        hitbox->getVisual()->draw();
    }
    if(model) {
        model->setup(shader,projection,view,cameraPos,*savedDirLight,*savedPointLights,*savedSpotLight);
        model->translate(currentPosition + model->getTranslateVect());
        // TODO: rotate the model to match camera.Front vector for bullets (?)

        model->rotate();
        model->scale();
        model->draw(shader);
    }
}

void MoveableObject::setShow(bool value) const {
    hitbox->shouldShow = value;
}

void MoveableObject::move() {
    glm::vec3 newPos = glm::vec3(currentPosition + movementDir);
    hitbox->updateBox(
            newPos.x - currentPosition.x,
            newPos.y - currentPosition.y,
            newPos.z - currentPosition.z
    );
    oldPosition = currentPosition;
    currentPosition = newPos;
}

void MoveableObject::setMove(bool value) {
    canMove = value;
}

auto MoveableObject::checkMove() const -> bool {
    return canMove;
}

