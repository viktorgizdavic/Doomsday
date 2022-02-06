//
// Created by bajaks on 1/23/21.
//

#ifndef DOOMSDAY_CROSSHAIR_H
#define DOOMSDAY_CROSSHAIR_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include <learnopengl/filesystem.h>
#include <learnopengl/camera.h>
#include <learnopengl/shader.h>

#include <iostream>
#include <string>

class Crosshair {
	    private:
	    float vertices[12] = {0.0f, 0.5f, 0.0f, 0.0f,  -0.5f, 0.0f,
				  0.5f, 0.0f, 0.0f, -0.5f, 0.0f,  0.0f};
	    unsigned int VAO, VBO;
	    Shader crosshairShader;

	    public:
	    Crosshair(glm::vec3 color)
		: crosshairShader("resources/shaders/crosshairShader.vs",
				  "resources/shaders/crosshairShader.fs") {
			glGenBuffers(1, &VBO);
			glGenVertexArrays(1, &VAO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
				     vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
					      3 * sizeof(float), (void *)0);
			glEnableVertexAttribArray(0);

			crosshairShader.use();
			crosshairShader.setVec3("color", color);
	    }
	    void draw() {
			glm::mat4 model(1.0f);
			//        model=glm::translate(model,cameraFront);
			model = glm::scale(model, glm::vec3(0.05f));
			crosshairShader.use();
			crosshairShader.setMat4("model", model);
			glBindVertexArray(VAO);
			glDrawArrays(GL_LINES, 0, 4);
			glBindVertexArray(0);
	    }
};

#endif // DOOMSDAY_CROSSHAIR_H
