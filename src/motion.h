#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/shader.h>

const float PI = 3.1415926;
const float CAR_L = 2.825;
const float CAR_W = 1.840;
const float CAR_H = 1.455;
const float WB = 2.825;
glm::vec2 fw = glm::vec2(0.0f, 1.4125f);
glm::vec2 bw = glm::vec2(0.0f, -1.4125f);
class Motion{
public:
    float theta;//弧度 角度
    float speed;
    float radius;
    float angleSp;
    Motion(float theta, float speed)
    {
        this->theta = theta;
        this->speed = speed;
        radius = theta ? WB / glm::sin(glm::radians(theta)) : 0.0f;
        angleSp = theta ? speed / radius : 0.0f;
    }

    float getdis( float t)
    {
        return theta ? angleSp * t * radius : speed * t;
    }

    glm::vec2 getFw(float t)
    {
        //安半径radius旋转弧度（angleSp)
        return glm::vec2(radius * glm::cos(angleSp), radius * glm::sin(angleSp));
    }

};