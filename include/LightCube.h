//
// Created by bajaks on 1/22/21.
//

#ifndef DOOMSDAY_LIGHTCUBE_H
#define DOOMSDAY_LIGHTCUBE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb_image.h>

//#include <learnopengl/filesystem.h>
#include <learnopengl/shader.h>
//#include <learnopengl/camera.h>

#define attrCount 6*3*6

#include <vector>
#include <iostream>
#include <string>
class LightCube {
private:
    float lightCubeVertices[attrCount] = {
            // positions
            0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,       // FRONT FACE
            -0.5f, -0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,

            0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,       // BACK FACE
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f,  0.5f,  0.5f,       // LEFT FACE
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,


            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f, -0.5f, -0.5f,       // RIGHT FACE
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,

            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,      // BOTTOM FACE
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,       // TOP FACE
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f,  0.5f,
    };
    unsigned int VBO, VAO;
    Shader lightCubeShader;
    glm::mat4 position=glm::mat4(1.0f);
public:
//    glm::vec3 ambient;
//    glm::vec3 diffuse;
//    glm::vec3 specular;
    LightCube(glm::vec3 color): lightCubeShader("resources/shaders/lightCubeShader.vs", "resources/shaders/lightCubeShader.fs")
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(lightCubeVertices), lightCubeVertices, GL_STATIC_DRAW);

        //positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        lightCubeShader.use();
        lightCubeShader.setVec3("color",color);
    }

    void setup(glm::mat4 projection,glm::mat4 view)
    {
        lightCubeShader.use();
        lightCubeShader.setMat4("view",view);
        lightCubeShader.setMat4("projection",projection);
        lightCubeShader.setMat4("model",position);
    }

    void resetTransformation()
    {
        position=glm::mat4(1.0f);
    }
    void applyTransformation()
    {
        lightCubeShader.use();
        lightCubeShader.setMat4("model",position);
    }
    void translate(glm::vec3 vector)
    {
        position=glm::translate(position,vector);
    }
    void rotate(float angle,glm::vec3 vector)
    {
        position=glm::rotate(position,glm::radians(angle),vector);
    }
    void scale(glm::vec3 vector)
    {
        position=glm::scale(position,vector);
    }
    void draw()
    {
        applyTransformation();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,36);
        glBindVertexArray(0);

        resetTransformation();
    }

};

#endif //DOOMSDAY_LIGHTCUBE_H
