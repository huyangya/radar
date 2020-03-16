#pragma once
#ifndef BARRIER_H
#define BARRIER_H
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <radar.h>
using namespace std;

class Barrier
{
public:
	vector <glm::vec2> bars;
	glm::vec2 carCoordinate1;
	glm::vec2 carCoordinate2;

	glm::mat4 getTransferMatrix()
	{
		carCoordinate1 = glm::vec2(0.0f, 0.0f); //glm::vec2(4.157876f, 4.527652f);
		carCoordinate2 = glm::vec2(1.0f, 0.0f);//glm::vec2(1.842124f, 5.864652f)
		glm::vec2 carLCenter = carCoordinate1 + carCoordinate2;
		carLCenter = glm::vec2(carLCenter.x / 2, carLCenter.y / 2);
		glm::vec2 direction = carCoordinate1 - carCoordinate2;
		direction = glm::normalize(direction);

		float angle = glm::acos(glm::dot(direction, glm::normalize(glm::vec2(0.0f, 1.0f))));
		std::cout << angle << std::endl;
		if (direction.x > 0)
		{
			angle = angle;
		}
		else
		{
			angle = -angle;
		}
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(carLCenter, 0.0f));
		model = glm::rotate(model, angle, glm::vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, glm::vec3(0.1333333));
		return model;
	}

	void get()
	{
		ifstream infile;
		infile.open("E:/2.txt");
		string str;
		ofstream out("E:/1.txt");
		
		while (infile) {
			getline(infile, str);
			istringstream is(str);
			string v1, v2, v3, v4;
			Ra r1, r2, r3, r4;
			is >> v1 >> v2 >> v3 >> v4;
			r1.id = 5;
			r1.value = atof(v1.c_str()) * scale * 10;

			r2.id = 6;
			r2.value = atof(v2.c_str()) * scale * 10;

			r3.id = 7;
			r3.value = atof(v3.c_str()) * scale * 10;

			r4.id = 8;
			r4.value = atof(v4.c_str()) * scale * 10;
			if (out.is_open())
			{
				out << r3.value << "\t" << r4.value << "\t";
			}
			out << "\n";
			str.clear();
		}

		infile.close();
		out.close();
	}
	
	void Draw()
	{
		//glm::vec2(2.5f, 6.0f);
		glm::mat4 mm = getTransferMatrix();//4.157876f, 4.527652f
		glm::vec4 ss = mm * glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		glm::vec2 b = glm::vec2(ss.x, ss.y);
		Radar r;
		Ra a;
		a.id = 2;
		a.value =  glm::length(glm::vec2(raCenter[1] - b));
		r.DrawRad(a);
	}

};
#endif // !BARRIER_H
