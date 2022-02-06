//
// Created by logan on 21.1.21..
//

#ifndef DOOMSDAY_GAME_H
#define DOOMSDAY_GAME_H

#include "MoveableObject.h"
#include <RectangleObject.h>
#include <vector>

class Game {
	    public:
	    Game() = default;
	    ~Game();

	    void gameTick(float dt, glm::mat4 projection, glm::mat4 view,
			  glm::vec3 &viewPosition);
	    void levelLogic();
	    void addMoveable(MoveableObject *);
	    void shoot(glm::vec3 position, glm::vec3 direction);
	    MoveableObject *moveLookahead(MoveableObject *);

	    MoveableObject *playerObj;
	    Shader *savedShader;
	    glm::vec3 *viewPosition;
	    DirLight *savedDirLight;
	    std::vector<PointLight> *savedPointLights;
	    SpotLight *savedSpotLight;

	    ModelObject *bullet;
	    ModelObject *zombieModel;

	    private:
	    void dealDamage(float damage);
	    // an array of all objects which update over time
	    // for example: bullets, zombies
	    std::vector<MoveableObject *> objArray;

	    float timeElapsed = 0;
	    float logicTick = 0;
	    float previousTick = 0;
	    float tickSec = 0.016; // update every 16 ms
	    unsigned secondsCounter = 0;

	    float fireRate = 0.2;
	    float previousFire = 0;

	    float playerHp = 100;

	    // level settings
	    unsigned int enemyCountPerLevel = 2;
	    unsigned enemyCountIncreasePerLevel = 1;

	    unsigned delayBetweenLevels = 1;	      // seconds
	    unsigned delayBetweenLevelsIncrease = 10; // seconds

	    float enemySpeedFactor = 2.0;
	    float enemySpeedFactorIncrease = 1.0;
};

#endif // DOOMSDAY_GAME_H
