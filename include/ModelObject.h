//
// Created by bajaks on 1/23/21.
//

#ifndef DOOMSDAY_MODELOBJECT_H
#define DOOMSDAY_MODELOBJECT_H
#include <LightStructs.h>
#include <learnopengl/model.h>
class ModelObject : public Model {
private:
    glm::mat4 position=glm::mat4(1.0f);
public:
    ModelObject(string const &path, bool gamma = false):Model(path,gamma)
    {}
    void setup(Shader& shader,glm::mat4 projection,glm::mat4 view,glm::vec3 viewPos,DirLight& dirLight,std::vector<PointLight>& pointLights,SpotLight& spotLight)
    {
        shader.use();
        shader.setMat4("view",view);
        shader.setMat4("projection",projection);
        glm::mat4 model(1.0f);

        shader.setMat4("model",position);

        shader.setVec3("viewPosition",viewPos);
        shader.setFloat("material.shininess",32.0f);

        shader.setVec3("dirLight.direction",dirLight.direction);
        shader.setVec3("dirLight.ambient", dirLight.ambient);
        shader.setVec3("dirLight.diffuse", dirLight.diffuse);
        shader.setVec3("dirLight.specular", dirLight.specular);

        //point lights
//        rectShader.setVec3("pointLights[0].position", glm::vec3(xScaling1,yScaling1,zScaling1)*(glm::vec3(30.0f,0.0f,-30.0f)+glm::vec3(xTranslate1,yTranslate1,zTranslate1)));
//        rectShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
//        rectShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
//        rectShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
//        rectShader.setFloat("pointLights[0].constant", 1.0f);
//        rectShader.setFloat("pointLights[0].linear", 0.009);
//        rectShader.setFloat("pointLights[0].quadratic", 0.0032);

        for (int i = 0; i < pointLights.size(); ++i) {
            std::string iStr=std::to_string(i);
            shader.setVec3("pointLights["+iStr+"].position", pointLights[i].position);
            shader.setVec3("pointLights["+iStr+"].ambient", pointLights[i].ambient);
            shader.setVec3("pointLights["+iStr+"].diffuse", pointLights[i].diffuse);
            shader.setVec3("pointLights["+iStr+"].specular", pointLights[i].specular);
            shader.setFloat("pointLights["+iStr+"].constant", pointLights[i].constant);
            shader.setFloat("pointLights["+iStr+"].linear", pointLights[i].linear);
            shader.setFloat("pointLights["+iStr+"].quadratic", pointLights[i].quadratic);
        }


        //ceiling glass spotlight
        shader.setVec3("spotLight.position",spotLight.position);
        shader.setVec3("spotLight.direction",spotLight.direction);
//        rectShader.setVec3("spotLight.position",viewPos);
//        rectShader.setVec3("spotLight.direction",front);
        shader.setVec3("spotLight.ambient", spotLight.ambient);
        shader.setVec3("spotLight.diffuse", spotLight.diffuse);
        shader.setVec3("spotLight.specular", spotLight.specular);
        shader.setFloat("spotLight.constant", spotLight.constant);
        shader.setFloat("spotLight.linear", spotLight.linear);
        shader.setFloat("spotLight.quadratic", spotLight.quadratic);
        shader.setFloat("spotLight.cutOff", spotLight.cutOff);
        shader.setFloat("spotLight.outerCutOff", spotLight.outerCutOff);
    }
    void resetTransformation()
    {
        position=glm::mat4(1.0f);
    }
    void applyTransformation(Shader &shader)
    {
        shader.use();
        shader.setMat4("model",position);
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

    void draw(Shader& shader)
    {
        applyTransformation(shader);
        Draw(shader);
        resetTransformation();
    }
};

#endif //DOOMSDAY_MODELOBJECT_H
