//
// Created by bajaks on 1/22/21.
//

#ifndef DOOMSDAY_CUBE_H
#define DOOMSDAY_CUBE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb_image.h>

//#include <learnopengl/filesystem.h>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

#define attrCount 6*8*6

#include <vector>
#include <iostream>
#include <string>
class Cube {
private:
    float cubeVertices[attrCount] = {
            // positions          // normals           // texture coords
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,      // FRONT FACE
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,

            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,      // BACK FACE
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,      // LEFT FACE
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,


            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,      // RIGHT FACE
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,     // BOTTOM FACE
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,      // TOP FACE
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f
    };

    unsigned int VBO, VAO;
    unsigned int diffuse;
    unsigned int specular;
    Shader cubeShader;
    glm::mat4 position=glm::mat4(1.0f);
    unsigned int loadTexture(char const * path)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }

public:
    Cube(std::string diffusePath,std::string specularPath):cubeShader("resources/shaders/rectangleObjectShader.vs","resources/shaders/rectangleObjectShader.fs")
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

        //positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        //normals
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        //texture coords
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // load and create a texture
        // -------------------------
        //FileSystem::getPath(specularPath).c_str()
        diffuse=loadTexture(diffusePath.c_str());
        specular=loadTexture(specularPath.c_str());
        cubeShader.use();
        cubeShader.setInt("material.diffuse",0);
        cubeShader.setInt("material.specular",1);
    }
    void setup(glm::mat4 projection,glm::mat4 view,glm::vec3 viewPos)
    {
        cubeShader.use();
        cubeShader.setMat4("view",view);
        cubeShader.setMat4("projection",projection);
        cubeShader.setMat4("model",position);

        cubeShader.setVec3("viewPosition",viewPos);
        cubeShader.setFloat("material.shininess",32.0f);


        //dim directional light
        cubeShader.setVec3("dirLight.direction",glm::vec3(0.0f,0.0f,-1.0f));
        cubeShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3("dirLight.diffuse", 0.0f, 0.0f, 0.0f);
        cubeShader.setVec3("dirLight.specular", 0.0f, 0.0f, 0.0f);

        //point lights
        //point lights
        cubeShader.setVec3("pointLights[0].position", glm::vec3(xScaling1,yScaling1,zScaling1)*(glm::vec3(30.0f,0.0f,-30.0f)+glm::vec3(xTranslate1,yTranslate1,zTranslate1)));
        cubeShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        cubeShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        cubeShader.setFloat("pointLights[0].constant", 1.0f);
        cubeShader.setFloat("pointLights[0].linear", 0.009);
        cubeShader.setFloat("pointLights[0].quadratic", 0.0032);
        // point light 2
        cubeShader.setVec3("pointLights[1].position", glm::vec3(xScaling1,yScaling1,zScaling1)*(glm::vec3(0.0f,15.0f,-30.0f+(60.0f*1/3))+glm::vec3(xTranslate1,yTranslate1,zTranslate1)));
        cubeShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        cubeShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        cubeShader.setFloat("pointLights[1].constant", 1.0f);
        cubeShader.setFloat("pointLights[1].linear", 0.006);
        cubeShader.setFloat("pointLights[1].quadratic", 0.0016);

        //point light 3
        cubeShader.setVec3("pointLights[2].position", glm::vec3(xScaling1,yScaling1,zScaling1)*(glm::vec3(-60.0f*1/3,15.0f,-30.0f)+glm::vec3(xTranslate1,yTranslate1,zTranslate1)));
        cubeShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        cubeShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        cubeShader.setFloat("pointLights[2].constant", 1.0f);
        cubeShader.setFloat("pointLights[2].linear", 0.006);
        cubeShader.setFloat("pointLights[2].quadratic", 0.0016);

        //point light 4
        cubeShader.setVec3("pointLights[3].position", glm::vec3(xScaling1,yScaling1,zScaling1)*(glm::vec3(60.0f*1/6*1/2-15.0f,15.0f,-50.0f)+glm::vec3(xTranslate1,yTranslate1,zTranslate1)));
        cubeShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        cubeShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        cubeShader.setFloat("pointLights[3].constant", 1.0f);
        cubeShader.setFloat("pointLights[3].linear", 0.006);
        cubeShader.setFloat("pointLights[3].quadratic", 0.0016);

        //point light 4
        cubeShader.setVec3("pointLights[4].position", glm::vec3(xScaling1,yScaling1,zScaling1)*(glm::vec3(60.0f*1/6*1/2+15.0f,15.0f,-50.0f)+glm::vec3(xTranslate1,yTranslate1,zTranslate1)));
        cubeShader.setVec3("pointLights[4].ambient", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3("pointLights[4].diffuse", 0.8f, 0.8f, 0.8f);
        cubeShader.setVec3("pointLights[4].specular", 1.0f, 1.0f, 1.0f);
        cubeShader.setFloat("pointLights[4].constant", 1.0f);
        cubeShader.setFloat("pointLights[4].linear", 0.006);
        cubeShader.setFloat("pointLights[4].quadratic", 0.0016);

        //ceiling glass spotlight
        cubeShader.setVec3("spotLight.position",glm::vec3(4.0f,2.0f,4.0f)*(glm::vec3(60.0f*1/6*1/2,15.0f,-30.0f-(60.0f*1/6*1/2))+glm::vec3(0.0f,0.0f,20.0f)));
        cubeShader.setVec3("spotLight.direction",glm::vec3(0.0f,-1.0f,0.0f));
//        rectShader.setVec3("spotLight.position",viewPos);
//        rectShader.setVec3("spotLight.direction",front);
        cubeShader.setVec3("spotLight.ambient", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        cubeShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        cubeShader.setFloat("spotLight.constant", 1.0f);
        cubeShader.setFloat("spotLight.linear", 0.002);
        cubeShader.setFloat("spotLight.quadratic", 0.0008);
        cubeShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(30.0f)));
        cubeShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(45.0f)));
    }

    void resetTransformation()
    {
        position=glm::mat4(1.0f);
    }
    void applyTransformation()
    {
        cubeShader.use();
        cubeShader.setMat4("model",position);
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

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuse);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,specular);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,36);
        glBindVertexArray(0);


        resetTransformation();
    }

};

#endif //DOOMSDAY_CUBE_H
