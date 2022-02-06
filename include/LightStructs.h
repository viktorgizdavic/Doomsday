//
// Created by bajaks on 1/23/21.
//

#ifndef DOOMSDAY_LIGHTSTRUCTS_H
#define DOOMSDAY_LIGHTSTRUCTS_H
struct PointLight {
	    glm::vec3 position;
	    glm::vec3 ambient;
	    glm::vec3 diffuse;
	    glm::vec3 specular;

	    float constant;
	    float linear;
	    float quadratic;
};
struct DirLight {
	    glm::vec3 direction;

	    glm::vec3 ambient;
	    glm::vec3 diffuse;
	    glm::vec3 specular;
};
struct SpotLight {
	    glm::vec3 position;
	    glm::vec3 direction;
	    float cutOff;
	    float outerCutOff;

	    float constant;
	    float linear;
	    float quadratic;

	    glm::vec3 ambient;
	    glm::vec3 diffuse;
	    glm::vec3 specular;
};
#endif // DOOMSDAY_LIGHTSTRUCTS_H
