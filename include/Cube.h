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
    void setup(glm::mat4 projection,glm::mat4 view,glm::vec3 viewPos,DirLight& dirLight,std::vector<PointLight>& pointLights,SpotLight& spotLight)
    {
        cubeShader.use();
        cubeShader.setMat4("view",view);
        cubeShader.setMat4("projection",projection);
        cubeShader.setMat4("model",position);

        cubeShader.setVec3("viewPosition",viewPos);
        cubeShader.setFloat("material.shininess",32.0f);


        //dim directional light
        cubeShader.setVec3("dirLight.direction",dirLight.direction);
        cubeShader.setVec3("dirLight.ambient", dirLight.ambient);
        cubeShader.setVec3("dirLight.diffuse", dirLight.diffuse);
        cubeShader.setVec3("dirLight.specular", dirLight.specular);

        //point lights
        for (int i = 0; i < pointLights.size(); ++i) {
            std::string iStr=std::to_string(i);
            cubeShader.setVec3("pointLights["+iStr+"].position", pointLights[i].position);
            cubeShader.setVec3("pointLights["+iStr+"].ambient", pointLights[i].ambient);
            cubeShader.setVec3("pointLights["+iStr+"].diffuse", pointLights[i].diffuse);
            cubeShader.setVec3("pointLights["+iStr+"].specular", pointLights[i].specular);
            cubeShader.setFloat("pointLights["+iStr+"].constant", pointLights[i].constant);
            cubeShader.setFloat("pointLights["+iStr+"].linear", pointLights[i].linear);
            cubeShader.setFloat("pointLights["+iStr+"].quadratic", pointLights[i].quadratic);
        }


        //ceiling glass spotlight
        cubeShader.setVec3("spotLight.position",spotLight.position);
        cubeShader.setVec3("spotLight.direction",spotLight.direction);
//        rectShader.setVec3("spotLight.position",viewPos);
//        rectShader.setVec3("spotLight.direction",front);
        cubeShader.setVec3("spotLight.ambient", spotLight.ambient);
        cubeShader.setVec3("spotLight.diffuse", spotLight.diffuse);
        cubeShader.setVec3("spotLight.specular", spotLight.specular);
        cubeShader.setFloat("spotLight.constant", spotLight.constant);
        cubeShader.setFloat("spotLight.linear", spotLight.linear);
        cubeShader.setFloat("spotLight.quadratic", spotLight.quadratic);
        cubeShader.setFloat("spotLight.cutOff", spotLight.cutOff);
        cubeShader.setFloat("spotLight.outerCutOff", spotLight.outerCutOff);

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
