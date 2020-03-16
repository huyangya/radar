#pragma once
#ifndef RADAR_H
#define RADAR_H
 
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/shader.h>
#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <cmath>
using namespace std;
//以后轮轴中心为原点 车前雷达 （732， 778+2674），（295， 942+2674）（-732， 778+2674），（-295， 942+2674）
// 车后（757， -838） （244， -947）（-757， -838） （-244， -947）
// 车侧（923， 479 + 2674） （910，-496）（-923， 479 + 2674） （-910，-496）
/*            .
			  .
			  .
	1   2	  .    3   4
			  .
  5		      .          6
			  .
			  .
			  .
			  .
			  .
。。。。。。。.。。。。。。。。。
  7			  .          8
	9    10	  .  11    12
			  .
			  .
			  .
			  .
			  .
*/
struct Ra {
	unsigned int id;
	float value;
};

struct RaDe {
	glm::vec2 rc[12];
	float mins[12];
	float maxs[12];
	glm::vec2 dir[12];
	float sangle[12];
	float eangle[12];
};

const float PI = 3.1415926;
float scale = 0.0001333333;
float minDR = 180.0;
float maxFBDR = 2500.0;
float maxLRDR = 4500.0;
//探测范围前后0.25 - 2.5m 左右 0.25 - 4.5m
glm::vec2 raCenter[12] = {
	//雷达在屏幕上的坐标 从后轮轴中心坐标系 变为 车中心坐标系 ×缩放比例
	glm::vec2	(-732 , 778 + 2674	- 1351) * scale,
	glm::vec2	(-295 , 942 + 2674	- 1351) * scale,
	glm::vec2	(295  , 942 + 2674	- 1351) * scale,
	glm::vec2	(732  , 778 + 2674	- 1351) * scale,
	glm::vec2	(-923 , 479 + 2674	- 1351) * scale,
	glm::vec2	(923  , 479 + 2674	- 1351) * scale,
	glm::vec2	(-910 , -496		- 1351)		* scale,
	glm::vec2	(910  , -496		- 1351)		* scale,
	glm::vec2	(-757 , -838		- 1351)		* scale,
	glm::vec2	(-244 ,	-947		- 1351)		* scale,
	glm::vec2	(244  , -947		- 1351)		* scale,
	glm::vec2	(757  , -838		- 1351)		* scale,
};
glm::vec2 FC1 = glm::vec2(0.0, 778 + 2674 - 1351)* scale;
glm::vec2 FC2 = glm::vec2(0.0, 942 + 2674 - 1351)* scale;
glm::vec2 BC1 = glm::vec2(0.0, -838 - 1351)* scale;
glm::vec2 BC2 = glm::vec2(0.0, -947 - 1351)* scale;
//RaDe RD1 = { 1, raCenter[0],0.0f, 0.0f, glm::vec2(0,0), 0.0f, 0.0f };
RaDe RD = {
		{
		//雷达在屏幕上的坐标 从后轮轴中心坐标系 变为 车中心坐标系 ×缩放比例
		glm::vec2(-732 , 778 + 2674 - 1351) * scale,
		glm::vec2(-295 , 942 + 2674 - 1351) * scale,
		glm::vec2(295  , 942 + 2674 - 1351) * scale,
		glm::vec2(732  , 778 + 2674 - 1351) * scale,
		glm::vec2(-923 , 479 + 2674 - 1351) * scale,
		glm::vec2(923  , 479 + 2674 - 1351) * scale,
		glm::vec2(-910 , -496 - 1351)		* scale,
		glm::vec2(910  , -496 - 1351)		* scale,
		glm::vec2(-757 , -838 - 1351)		* scale,
		glm::vec2(-244 ,	-947 - 1351)		* scale,
		glm::vec2(244  , -947 - 1351)		* scale,
		glm::vec2(757  , -838 - 1351)		* scale,
	},
		{minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR},
		{minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR},
		{
			//雷达在屏幕上的坐标 从后轮轴中心坐标系 变为 车中心坐标系 ×缩放比例
			glm::vec2(glm::cos(glm::radians(130.0)) , glm::sin(glm::radians(130.0))),
			glm::vec2(glm::cos(glm::radians(90.0)) ,  glm::sin(glm::radians(90.0))),
			glm::vec2(glm::cos(glm::radians(90.0)) ,  glm::sin(glm::radians(90.0))),
			glm::vec2(glm::cos(glm::radians(50.0)) ,  glm::sin(glm::radians(50.0))),
			glm::vec2(glm::cos(glm::radians(180.0)) , glm::sin(glm::radians(180.0))),
			glm::vec2(glm::cos(glm::radians(0.0)) ,   glm::sin(glm::radians(0.0))),
			glm::vec2(glm::cos(glm::radians(200.0)) , glm::sin(glm::radians(200.0))),
			glm::vec2(glm::cos(glm::radians(340.0)) , glm::sin(glm::radians(340.0))),
			glm::vec2(glm::cos(glm::radians(240.0)) , glm::sin(glm::radians(240.0))),
			glm::vec2(glm::cos(glm::radians(270.0)) , glm::sin(glm::radians(270.0))),
			glm::vec2(glm::cos(glm::radians(270.0)) , glm::sin(glm::radians(270.0))),
			glm::vec2(glm::cos(glm::radians(300.0)) , glm::sin(glm::radians(300.0))),
		},
		{70,30,30,-10,150,330,140,280,180,210,210,240},
		{190,150,150,110,210,390,260,400 ,300,330,330,360},
};
class Radar
{
public:
	Ra r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12;
	glm::vec2 woco;
	float angle;
	//static const RaDe RD = {
	//	raCenter,
	//	{minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR},
	//	{minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR},
	//	raCenter,
	//	{minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR},
	//	{minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR,minDR},
	//};
	void Init() 
	{
		r1.id = 1;		r1.value = maxFBDR * scale;
		r2.id = 2;		r2.value = maxFBDR * scale;
		r3.id = 3;		r3.value = maxFBDR * scale;
		r4.id = 4;		r4.value = maxFBDR * scale;
		r5.id = 5;		r5.value = maxLRDR * scale;
		r6.id = 6;		r6.value = maxLRDR * scale;
		r7.id = 7;		r7.value = maxLRDR * scale;
		r8.id = 8;		r8.value = maxLRDR * scale;
		r9.id = 9;		r9.value = maxFBDR * scale;
		r10.id = 10;	r10.value = maxFBDR * scale;
		r11.id = 11;	r11.value = maxFBDR * scale;
		r12.id = 12;	r12.value = maxFBDR * scale;
		woco = glm::vec2(0.0, 0.0);
	}
	void getwc(glm::vec2 v)
	{
		woco = v;
	}
	void save(Ra r)
	{
		
		glm::vec2 b;
		switch (r.id)
		{
		case 1:
			b = raCenter[0] + r.value * RD.dir[0] - woco;
			break;
		case 2:
			b = raCenter[1] + r.value * RD.dir[1] - woco;
			break;
		case 3:
			b = raCenter[2] + r.value * RD.dir[2] - woco;
			break;
		case 4:
			b = raCenter[3] + r.value * RD.dir[3] - woco;
			break;
		case 5:
			b = raCenter[4] + r.value * RD.dir[4] - woco;
			break;
		case 6:
			b = raCenter[5] + r.value * RD.dir[5] - woco;
			break;
		case 7:
			b = raCenter[6] + r.value * RD.dir[6] - woco;
			break;
		case 8:
			b = raCenter[7] + r.value * RD.dir[7] - woco;
			break;
		case  9:
			b = raCenter[8] + r.value * RD.dir[8] - woco;
			break;
		case 10:
			b = raCenter[9] + r.value * RD.dir[9] - woco;
			break;
		case 11:
			b = raCenter[10] + r.value * RD.dir[10] - woco;
			break;
		case 12:
			b = raCenter[11] + r.value * RD.dir[11] - woco;
			break;
		default:
			break;
		}
		ofstream out("E:/1.txt");
		if (out.is_open())
		{
			out << b.x << "\t" << b.y  << "\t";
		}
		out.close();
	}

	int hex2int(const std::string &hex) {
		std::string::const_reverse_iterator rit = hex.rbegin();
		int i = 0, ret = 0;
		for (; rit != hex.rend(); ++rit) {
			if (*rit >= '0' && *rit <= '9') {
				ret += (*rit - '0') * pow(16, i);
			}
			else if (*rit >= 'a' && *rit <= 'f') {
				ret += (*rit - 'a' + 10) * pow(16, i);
			}
			else {
				ret += (*rit - 'A' + 10) * pow(16, i);
			}
			i++;
		}

		return ret;
	}

	int hex2intM(const std::string &hex) {
		
		int i = 0, ret = 0;
		for (; i < hex.length(); ) {
			char n = hex.at(i);
			if (n >= '0' && n <= '9') {
				ret += (n - '0') * pow(16, i);
			}
			else {
				ret += (n - 'A' + 10) * pow(16, i);
			}
			i++;
		}

		return ret;
	}

	vector <float> readTxt(string file)
	{
		vector <float> v;

		ifstream infile;
		infile.open(file.data());
		assert(infile.is_open());
		ofstream out("E:/1.txt");
		string s;
		getline(infile, s);
		
		while (getline(infile, s))
		{
			
			getline(infile, s);
			istringstream is(s);
			//cout << s << endl;
			string s1, s2, t, s4, s5, s6, s7, d1, d2, d3, d4, d5, d6, d7, d8;
			is >> s1 >> s2 >> t >> s4 >> s5 >> s6 >> s7 >> d1 >> d2 >> d3 >> d4 >> d5 >> d6 >> d7 >> d8;

			if (s4 == "0x00000736")//侧边雷达值
			{
				cout << s4 << "侧边雷达值占两个字节" << "\n" << d1 << " " << d2 << " " << d3 << " " << d4 << " " << d5 << " " << d6 << " " << d7 << " " << d8 << endl;
				cout << hex2int(d1.append(d2)) << " " << hex2int(d3.append(d4)) << " " << hex2int(d5.append(d6)) << " " << hex2int(d7.append(d8)) << endl;
				v.push_back((float)hex2int(d2.append(d1)));
				v.push_back((float)hex2int(d4.append(d3)));
				v.push_back((float)hex2int(d6.append(d5)));
				v.push_back((float)hex2int(d8.append(d7)));
			}
			else if (s4 == "0x00000739")//前后8个雷达值
			{
				if (out.is_open())
				{
					out << s.c_str() << "\n";
				}
				cout << s4 << "前后8个雷达值" << "\n" << d1 << " " << d2 << " " << d3 << " " << d4 << " " << d5 << " " << d6 << " " << d7 << " " << d8 << endl;
				cout << hex2int(d1) << " " << hex2int(d2) << " " << hex2int(d3) << " " << hex2int(d4) << " " << hex2int(d5) << 
					" " << hex2int(d6) << " " << hex2int(d7) << " " << hex2int(d8) << endl;
				v.push_back((float)hex2int(d1));
				v.push_back((float)hex2int(d2));
				v.push_back((float)hex2int(d3));
				v.push_back((float)hex2int(d4));
				v.push_back((float)hex2int(d5));
				v.push_back((float)hex2int(d6));
				v.push_back((float)hex2int(d7));
				v.push_back((float)hex2int(d8));
			}
			if (s4 == "0x00000707") //车的实时坐标 x y各占4个字节
			{
				
				//cout << s4 << "车的实时坐标 x y各占4个字节" << "\n" << d1 << " " << d2 << " " << d3 << " " << d4 << " " << d5 << " " << d6 << " " << d7 << " " << d8 << endl;
				// << hex2intM(d1.append(d2).append(d3).append(d4)) << " " << hex2intM(d5.append(d6).append(d7).append(d8)) << endl;
			}
			//else if (s4.substr(s4.length() - 3, s4.length()) == "701")//表示车辆的姿态角度
			//{
			//	if (out.is_open())
			//	{
			//		out << s.c_str() << "\n";
			//	}
			//	/*cout << s4 << "车辆的姿态角度" << "\n" << d1 << " " << d2 << " " << d3 << " " << d4 << " " << d5 << " " << d6 << " " << d7 << " " << d8 << endl;
			//	cout << hex2int(d5) << endl;*/
			//}
			
			
			//v.push_back(atof(d1.c_str()));
			/*std::cout << v.back() << endl;
			v.push_back(atof(d2.c_str()));
			v.push_back(atof(d3.c_str()));
			v.push_back(atof(d4.c_str()));
			v.push_back(atof(d5.c_str()));
			v.push_back(atof(d6.c_str()));
			v.push_back(atof(d7.c_str()));
			v.push_back(atof(d8.c_str()));
			std::cout << v.back() << "  "<< atof(d8.c_str()) << " " <<d8 <<  endl;*/
		}
		infile.close();
		out.close();
		cout << v.size() << endl;
		cout << v[0] << endl;
		return v;
	}
	//void getV(vector<Ra> data)
	//{
	//	r1 = data[0];
	//	r2 = data[1];
	//	r3 = data[2];
	//	r4 = data[3];
	//	r5 = data[4];
	//	r6 = data[5];
	//	r7 = data[6];
	//	r8 = data[7];
	//	r9 = data[8];
	//	r10 = data[9];
	//	r11 = data[10];
	//	r12 = data[11];
	//	//ofstream out("E:/1.txt",ios::app);
	//	//if (out.is_open())
	//	//{
	//		//	for (int i = 0; i < 12; i++)
	//		//	{
	//		//		out << data[i].value << "\t";
	//		//	}
	//		//	out << "\n";
	//		//	out.close();
	//	//}
	//}
	
	void DrawRad(Ra r)
	{
		
		vector<glm::vec2> vertices;
		if (r.value > minDR * scale)
		{
			if (r.value > maxLRDR * scale)
			{
				r.value = maxLRDR * scale;
			}
			
			int degreeRange = 120;//雷达探测的角度范围
			int startDegree = 0;//雷达探测角度范围的起始角度 逆时针
			switch (r.id)
			{
			case 1:
				startDegree = 70;
				degreeRange = 120;
				break;
			case 2:
				startDegree = 30;
				degreeRange = 120;
				break;
			case 3:
				startDegree = 30;
				degreeRange = 120;
				break;
			case 4:
				startDegree = -10;
				degreeRange = 120;
				break;
			case 5:
				startDegree = 150;
				degreeRange = 60;
				break;
			case 6:
				startDegree = 330;
				degreeRange = 60;
				break;
			case 7:
				startDegree = 140;
				break;
			case 8:
				startDegree = 280;
				break;
			case  9:
				startDegree = 180;
				break;
			case 10:
				startDegree = 210;
				break;
			case 11:
				startDegree = 210;
				break;
			case 12:
				startDegree = 240;
				break;
			default:
				break;
			}

			vertices.push_back(raCenter[r.id - 1]);
			for (int i = startDegree; i < degreeRange + startDegree; i++) {
				vertices.push_back(glm::vec2(r.value * glm::cos(glm::radians((float)i)), r.value * glm::sin(glm::radians((float)i))) + raCenter[r.id - 1]);
			}
			unsigned int VAO, VBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

			glEnable(GL_LINE_SMOOTH);
			//glEnable(GL_BLEND);
			//glLineWidth(5.0f);
			//glLineStipple(1, 0x3F07);
			//glLineStipple(1, 0x1111); //dashed
			//glLineStipple(0, 0x00ff);
			glBindVertexArray(VAO);

			glDrawArrays(GL_LINE_LOOP, 0, vertices.size());

			glBindVertexArray(0);
		}
	}
	
	void DrawBlock(Ra r)
	{
		if (r.value > minDR * scale)
		{
			if (r.value > maxLRDR * scale)
			{
				r.value = maxLRDR * scale;
			}
			vector<glm::vec2> vertices;
			//glm::vec2 s = glm::vec2(RD.dir[r.id - 1]) * r.value;
			int degreeRange = 1;//雷达探测的角度范围
			int startDegree = 0;//雷达探测角度范围的起始角度 逆时针
			glm::vec2 a, b, c, d;
			float width = 0.01333333 * 2;
			switch (r.id)
			{
			case 1:
				//startDegree = 12;
				startDegree = RD.sangle[0] / 10 + 6;
				degreeRange = 1;
				//s = glm::vec2(glm::cos(glm::radians((float)(90 + 45 + 45 /2))), glm::sin(glm::radians((float)(90 + 45 + 45 / 2)))) * r.value;
				a = glm::vec2(-r.value, 0);
				b = glm::vec2(-r.value +width, 0);
				c = glm::vec2(-0.5 * r.value, r.value * glm::sin(glm::radians(60.0f)));
				d = glm::vec2(-0.5 * (r.value - width), (r.value - width) * glm::sin(glm::radians(60.0f)));
				break;
			case 2:
				//startDegree = 9;
				startDegree = RD.sangle[1] / 10 + 6;
				degreeRange = 1;
				//s = glm::vec2(glm::cos(glm::radians((float)(90 + 45 / 2))), glm::sin(glm::radians((float)(90 + 45 / 2)))) * r.value;
				a = glm::vec2(-437 * scale - r.value* glm::sin(glm::radians(30.0f)), r.value* glm::cos(glm::radians(30.0f)));
				b = glm::vec2(-437 * scale - (r.value - width)* glm::sin(glm::radians(30.0f)), (r.value - width) * glm::cos(glm::radians(30.0f)));
				c = glm::vec2(295 * scale -width/2, r.value);
				d = glm::vec2(295 * scale - width/2, r.value - width);
				break;
			case 3:
				//startDegree = 6;
				startDegree = RD.sangle[2] / 10 + 6;
				degreeRange = 1;
				//s = glm::vec2(glm::cos(glm::radians((float)( 45 + 45 / 2))), glm::sin(glm::radians((float)( 45 + 45 / 2)))) * r.value;
				a = glm::vec2(-295 * scale + width/2, r.value);
				b = glm::vec2(-295 * scale + width/2, r.value - width);
				c = glm::vec2(437 * scale + r.value* glm::sin(glm::radians(30.0f)), r.value* glm::cos(glm::radians(30.0f)));
				d = glm::vec2(437 * scale +(r.value - width)* glm::sin(glm::radians(30.0f)), (r.value - width) * glm::cos(glm::radians(30.0f)));
				break;
			case 4:
				//startDegree = 3;
				startDegree = RD.sangle[3] / 10 + 6;
				degreeRange = 1;
				//s = glm::vec2(glm::cos(glm::radians((float)( 45 / 2))), glm::sin(glm::radians((float)( 45 / 2)))) * r.value;

				a = glm::vec2(0.5 * r.value, r.value * glm::sin(glm::radians(60.0f)));
				b = glm::vec2(0.5 * (r.value - width), (r.value - width) * glm::sin(glm::radians(60.0f)));
				c = glm::vec2(r.value, 0);
				d = glm::vec2(r.value - width, 0);
				break;
			case 5:
				//startDegree = 15;
				startDegree = RD.sangle[4] / 10 + 3;
				degreeRange = 1;
				a = glm::vec2(-r.value, 299 * scale);
				b = glm::vec2(-r.value+width, 299 * scale);
				c = glm::vec2(-r.value, -916 *scale);
				d = glm::vec2(-r.value + width, -916 * scale);
				break;
			case 6:
				//startDegree = 33;
				startDegree = RD.sangle[5] / 10 + 3;
				degreeRange = 1;
				a = glm::vec2(r.value, 299 * scale);
				b = glm::vec2(r.value + width, 299 * scale);
				c = glm::vec2(r.value, -916 * scale);
				d = glm::vec2(r.value + width, -916 * scale);
				break;
			case 7:
				//startDegree = 16;
				startDegree = 18;
				degreeRange = 2;
				//s = glm::vec2(-1, 0) * r.value;
				a = glm::vec2(-r.value, -342 * scale);
				b = glm::vec2(-r.value + width, -342 * scale);
				c = glm::vec2(-r.value, 916 * scale);
				d = glm::vec2(-r.value + width, 916 * scale);
				break;
			case 8:
				//startDegree = 30;
				startDegree = 0;
				degreeRange = 2;
				//s = glm::vec2(1, 0) * r.value;
				//s = glm::vec2(-1, 0) * r.value;
				a = glm::vec2(r.value, -342 * scale);
				b = glm::vec2(r.value + width, -342 * scale);
				c = glm::vec2(r.value, 916 * scale);
				d = glm::vec2(r.value + width, 916 * scale);
				break;
			case  9:
				//startDegree = 21;
				startDegree = RD.sangle[8] / 10 + 6;
				degreeRange = 1;
				a = glm::vec2(-r.value, 0);
				b = glm::vec2(-r.value + width, 0);
				c = glm::vec2(-0.5 * r.value, -r.value * glm::sin(glm::radians(60.0f)));
				d = glm::vec2(-0.5 * (r.value - width), -(r.value - width) * glm::sin(glm::radians(60.0f)));
				break;
			case 10:
				//startDegree = 24;
				startDegree = RD.sangle[9] / 10 + 6;
				degreeRange = 1;
				a = glm::vec2(-437 * scale - r.value* glm::sin(glm::radians(30.0f)), -r.value* glm::cos(glm::radians(30.0f)));
				b = glm::vec2(-437 * scale - (r.value - width)* glm::sin(glm::radians(30.0f)), -(r.value - width) * glm::cos(glm::radians(30.0f)));
				c = glm::vec2(295 * scale - width / 2, -r.value);
				d = glm::vec2(295 * scale - width / 2, -r.value + width);
				break;
			case 11:
				//startDegree = 27;
				startDegree = RD.sangle[10] / 10 + 6;
				degreeRange = 1;
				a = glm::vec2(-295 * scale + width/2, -r.value);
				b = glm::vec2(-295 * scale + width/2, -r.value + width);
				c = glm::vec2(437 * scale + r.value* glm::sin(glm::radians(30.0f)), -r.value* glm::cos(glm::radians(30.0f)));
				d = glm::vec2(437 * scale +(r.value - width)* glm::sin(glm::radians(30.0f)), -(r.value - width) * glm::cos(glm::radians(30.0f)));
				break;
			case 12:
				//startDegree = 30;
				startDegree = RD.sangle[11] / 10 + 6;
				degreeRange = 1;
				a = glm::vec2(0.5 * r.value, -r.value * glm::sin(glm::radians(60.0f)));
				b = glm::vec2(0.5 * (r.value - width), -(r.value - width) * glm::sin(glm::radians(60.0f)));
				c = glm::vec2(r.value, 0);
				d = glm::vec2(r.value - width, 0);
				break;
			default:
				break;
			}
			
			float t1 = r.value * PI / 8 * degreeRange;
			float t2 = (r.value - 0.01333333) * PI / 8 * degreeRange;
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians((RD.sangle[r.id-1] + RD.eangle[r.id - 1])/2), glm::vec3(0.0, 0.0, 1.0));
			glm::vec2 f[4] =
			{
				glm::vec2(0.01333333/2,  t1),
				glm::vec2(0.01333333/2, -t2),
				glm::vec2(-0.01333333/2, -t2),
				glm::vec2(-0.01333333/2,  t1),
			};
			for (int i = 0; i < 4; i++)
			{
				f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
			}
			/*vertices.push_back(glm::vec2(f[0] + raCenter[r.id - 1] + s));

			vertices.push_back(glm::vec2(f[1] + raCenter[r.id - 1] + s));

			vertices.push_back(glm::vec2(f[3] + raCenter[r.id - 1] + s));

			vertices.push_back(glm::vec2(f[1] + raCenter[r.id - 1] + s));

			vertices.push_back(glm::vec2(f[2] + raCenter[r.id - 1] + s));

			vertices.push_back(glm::vec2(f[3] + raCenter[r.id - 1] + s));*/
			vertices.push_back(glm::vec2(a + raCenter[r.id - 1]));

			vertices.push_back(glm::vec2(b + raCenter[r.id - 1]));

			vertices.push_back(glm::vec2(c + raCenter[r.id - 1]));

			vertices.push_back(glm::vec2(b + raCenter[r.id - 1]));

			vertices.push_back(glm::vec2(c + raCenter[r.id - 1]));

			vertices.push_back(glm::vec2(d + raCenter[r.id - 1]));

			unsigned int VAO, VBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

			/*glEnable(GL_LINE_SMOOTH);
			glLineWidth(5)*/;
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, vertices.size());

			glBindVertexArray(0);
		}
	}

	//void DrawBS(int id, float value)
	//{
	//		if (value > maxLRDR * scale)
	//		{
	//			value = maxLRDR * scale;
	//		}
	//	//value = 2000 * scale;
	//	glm::vec2 rcs = glm::vec2(930, 916) * scale;
	//		vector<glm::vec2> vertices;
	//		glm::vec2 a, b, c, d;
	//		float width = 0.01333333 * 2;
	//		switch (id)
	//		{
	//		case 5:
	//			a = glm::vec2(-value, 0);
	//			b = glm::vec2(-value + width, 0);
	//			c = glm::vec2(-value, -916 * scale +width);
	//			d = glm::vec2(-value + width, -916 * scale + width);
	//			rcs = glm::vec2(-rcs.x, rcs.y);
	//			break;
	//		case 6:
	//			a = glm::vec2(value, 0);
	//			b = glm::vec2(value - width,0);
	//			c = glm::vec2(value, -916 * scale + width);
	//			d = glm::vec2(value - width, -916 * scale + width);
	//			rcs = glm::vec2(rcs.x, rcs.y);
	//			break;
	//		case 7:
	//			a = glm::vec2(-value, 0);
	//			b = glm::vec2(-value + width, 0);
	//			c = glm::vec2(-value, 916 * scale);
	//			d = glm::vec2(-value + width, 916 * scale );
	//			rcs = glm::vec2(-rcs.x, -rcs.y);
	//			break;
	//		case 8:
	//			a = glm::vec2(value,0);
	//			b = glm::vec2(value - width, 0);
	//			c = glm::vec2(value, 916 * scale);
	//			d = glm::vec2(value - width, 916 * scale);
	//			rcs = glm::vec2(rcs.x, -rcs.y);
	//			break;
	//		}
	//		vertices.push_back(glm::vec2(a + rcs));
	//		vertices.push_back(glm::vec2(b + rcs));
	//		vertices.push_back(glm::vec2(c + rcs));
	//		vertices.push_back(glm::vec2(b + rcs));
	//		vertices.push_back(glm::vec2(c + rcs));
	//		vertices.push_back(glm::vec2(d + rcs));
	//		unsigned int VAO, VBO;
	//		glGenVertexArrays(1, &VAO);
	//		glGenBuffers(1, &VBO);
	//		glBindVertexArray(VAO);
	//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	//		glEnableVertexAttribArray(0);
	//		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
	//		glBindVertexArray(VAO);
	//		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	//		glBindVertexArray(0);
	//	
	//}

	//void DrawB()
	//{
	//	ifstream infile;
	//	infile.open("E:/2.txt");
	//	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行
	//	while (infile) {
	//		string str;
	//		getline(infile, str);
	//		istringstream is(str);
	//		string v1, v2, v3, v4;
	//		Ra r1, r2, r3, r4;
	//		is >> v1 >> v2 >> v3 >> v4;
	//		r1.id = 5;
	//		r1.value = atof(v1.c_str()) * scale * 10;
	//		r2.id = 6;
	//		r2.value = atof(v2.c_str()) * scale * 10;
	//		r3.id = 7;
	//		r3.value = atof(v3.c_str()) * scale * 10;
	//		r4.id = 8;
	//		r4.value = atof(v4.c_str()) * scale * 10;
	//		DrawBlock(r1);
	//		DrawBlock(r2);
	//		DrawBlock(r3);
	//		DrawBlock(r4);
	//		save(r1);
	//		save(r2);
	//		save(r3);
	//		save(r4);
	//		str.clear();
	//		Sleep(100);
	//	}
	//	
	//	infile.close();
	//}

	/*void DV(vector<float> v)
	{
		for (int i = 0; i < v.size()/12; i++)
		{ 
			r1.value = v[4 + i *12] * scale * 10;
			r2.value = v[5 + i * 12] * scale * 10;
			r3.value = v[6+ i *12] * scale * 10;
			r4.value = v[7+ i *12] * scale * 10;
			r5.value = v[8+ i *12] * scale * 10;
			r6.value = v[9+ i *12] * scale * 10;
			r7.value = v[10 + i * 12] * scale * 10;
			r8.value = v[11 + i * 12] * scale * 10;
			r9.value = v[0 + i * 12] * scale;
			r10.value = v[1 + i * 12] * scale;
			r11.value = v[2 + i * 12] * scale;
			r12.value = v[3 + i * 12] * scale;
			DrawBlock(r1);
			DrawBlock(r2);
			DrawBlock(r3);
			DrawBlock(r4);
			DrawBlock(r5);
			DrawBlock(r6);
			DrawBlock(r7);
			DrawBlock(r8);
			DrawBlock(r9);
			DrawBlock(r10);
			DrawBlock(r11);
			DrawBlock(r12);
			if (i != 0)
			{
				DrawBS(5, v[0 + (i - 1) * 12] * scale);
				DrawBS(6, v[1 + (i - 1) * 12] * scale);
				DrawBS(7, v[2 + (i - 1) * 12] * scale);
				DrawBS(8, v[3 + (i - 1) * 12] * scale);
			}
			else
			{
				DrawBS(5, v[0] * scale);
				DrawBS(6, v[1] * scale);
				DrawBS(7, v[2] * scale);
				DrawBS(8, v[3] * scale);
			}
			Sleep(200);
		}
	}*/

	void Draw()
	{
		//Init();
		DrawRad(r1);
		DrawRad(r2);
		DrawRad(r3);    
		DrawRad(r4);
		DrawRad(r5);
		DrawRad(r6);
		DrawRad(r7);
		DrawRad(r8);
		DrawRad(r9);
		DrawRad(r10);
		DrawRad(r11);
		DrawRad(r12);
		//DrawBlock(r1);
		//DrawBlock(r2);
		//DrawBlock(r3);
		//DrawBlock(r4);
		//DrawBlock(r5);
		//DrawBlock(r6);
		//DrawBlock(r7); 
		//DrawBlock(r8);
		//DrawBlock(r9);
		//DrawBlock(r10);
		//DrawBlock(r11);
		//DrawBlock(r12);

		//DrawBS(5, 500);
		//DrawBS(6, 8);
		//DrawBS(7,50);
		//DrawBS(8, 77);
		//save(r2);
	}

	glm::vec2 CrossPointOfCircle(glm::vec2 c1, float r1, glm::vec2 c2, float r2)
	{
		float d = glm::length(c1 - c2);
		if (d >=  r1 + r2)
		{
			return c1;
		}
		else 
		{
			glm::vec2 P1, P2;
			float a1, b1, R1, a2, b2, R2;
			a1 = c1.x;
			b1 = c1.y;
			R1 = r1;

			a2 = c2.x;
			b2 = c2.y;
			R2 = r2;

			//
			float R1R1 = R1 * R1;
			float a1a1 = a1 * a1;
			float b1b1 = b1 * b1;

			float a2a2 = a2 * a2;
			float b2b2 = b2 * b2;
			float R2R2 = R2 * R2;

			float subs1 = a1a1 - 2 * a1*a2 + a2a2 + b1b1 - 2 * b1*b2 + b2b2;
			float subs2 = -R1R1 * a1 + R1R1 * a2 + R2R2 * a1 - R2R2 * a2 + a1a1 * a1 - a1a1 * a2 - a1 * a2a2 + a1 * b1b1 - 2 * a1*b1*b2 + a1 * b2b2 + a2a2 * a2 + a2 * b1b1 - 2 * a2*b1*b2 + a2 * b2b2;
			float subs3 = -R1R1 * b1 + R1R1 * b2 + R2R2 * b1 - R2R2 * b2 + a1a1 * b1 + a1a1 * b2 - 2 * a1*a2*b1 - 2 * a1*a2*b2 + a2a2 * b1 + a2a2 * b2 + b1b1 * b1 - b1b1 * b2 - b1 * b2b2 + b2b2 * b2;
			float sigma = sqrt((R1R1 + 2 * R1*R2 + R2R2 - a1a1 + 2 * a1*a2 - a2a2 - b1b1 + 2 * b1*b2 - b2b2)*(-R1R1 + 2 * R1*R2 - R2R2 + subs1));
			if (abs(subs1) > 0.0000001)//分母不为0
			{
				P1.x = (subs2 - sigma * b1 + sigma * b2) / (2 * subs1);
				P2.x = (subs2 + sigma * b1 - sigma * b2) / (2 * subs1);

				P1.y = (subs3 + sigma * a1 - sigma * a2) / (2 * subs1);
				P2.y = (subs3 - sigma * a1 + sigma * a2) / (2 * subs1);
			}
		}
	}

	glm::vec2 circleLine(float angle, glm::vec2 circle, float r)
	{
		float k = glm::tan(glm::radians(angle));
		circle.x = circle.x > 0 ?  circle.x : -circle.x;
		k = k > 0 ? k : -k;
		float a, b, c, x, y;
		a = 1 + glm::pow(k, 2);
		c = glm::pow(circle.x, 2) - glm::pow(r, 2);
		b =  -2 * circle.x;
		float result;
		result = glm::pow(b, 2) - 4 * a * c;
		if (result > 0)
		{
			x = ((-b + glm::sqrt(result)) / (2 * a));
			//x = ((-b - glm::sqrt(result)) / (2 * a));*/
			//x = circle.y > 0 ? ((-b + glm::sqrt(result)) / (2 * a)) : ((-b - glm::sqrt(result)) / (2 * a));
		}
		else
		{
			x = -b / (2 * a);
		}
		x = x > 0 ? x : -x;
		
		return (glm::vec2(x, k * x));
	}
	void Db(float test)
	{
		if (test < 200 || test > 2500)
		{
			test = 0.0f;
		}
		else
		{
			Ra r;
			vector<glm::vec2> vertices;
			for (int j = 0; j < 28; j++)
			{
				r.id = j + 1;
				r.value = test * scale;

				//块的形状
				float t1 = r.value * PI / 8 ;
				float side = 740 * scale;
				float wide = 100 * scale;
				float t2 = (r.value - wide) * PI / 8 ;
				float interval = 1 * scale;
				glm::mat4 model = glm::mat4(1.0f);
				glm::vec2 zz;

				glm::vec2 f[4] =
				{
					glm::vec2(wide / 2,  t1 / 2),
					glm::vec2(wide / 2, -t2 / 2),
					glm::vec2(-wide / 2, -t2 / 2),
					glm::vec2(-wide / 2,  t1 / 2),
				};

				glm::vec2 a, b, c, d;
				float width = 0.01333333 * 2;

				switch (r.id)
				{
				case 1:
					model = glm::rotate(model, glm::radians(70.0f + 90.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(11.25f, raCenter[0], r.value);

					zz = glm::vec2(-zz.x, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[2] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));

					break;
				case 13:
					model = glm::rotate(model, glm::radians(50.0f + 90.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(33.75f, raCenter[0], r.value);

					zz = glm::vec2(-zz.x, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[2] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));
					break;
				case 2:
					model = glm::rotate(model, glm::radians(30.0f + 90.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(56.25f, raCenter[1], r.value);

					zz = glm::vec2(-zz.x - wide, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[2] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));
					break;
				case 14:
					model = glm::rotate(model, glm::radians(10.0f + 90.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(78.75f, raCenter[1], r.value);

					zz = glm::vec2(-zz.x - wide, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[2] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));
					break;
				case 3:
					model = glm::rotate(model, glm::radians(80.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(78.75f, raCenter[2], r.value);

					zz = glm::vec2(zz.x+wide, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[2] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));
					break;
				case 15:
					model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(56.25f, raCenter[2], r.value);

					zz = glm::vec2(zz.x + wide, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[2] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));
					break;
				case 4:
					model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(33.75f, raCenter[3], r.value);

					zz = glm::vec2(zz.x, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[2] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));
					break;
				case 16:
					model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(11.25f, raCenter[3], r.value);
					zz = glm::vec2(zz.x, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[2] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));
					break;
				case 5:
					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 2 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, 2 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 3 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, 2 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 3 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, 3 * side + (10 + 20 + 20)*scale));
					break;
				case 17:
					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 1 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, 1 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 2 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, 1 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 2 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, 2 * side + (10 + 20)*scale));
					break;
				case 25:
					vertices.push_back(glm::vec2(raCenter[4].x - r.value, (10)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, (10)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 1 * side + (10)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, (10)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 1 * side + (10)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, 1 * side + (10)*scale));
					break;
				case 6:
					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 2 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, 2 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 3 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, 2 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 3 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, 3 * side + (10 + 20 + 20)*scale));
					break;
				case 18:
					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 1 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, 1 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 2 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, 1 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 2 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, 2 * side + (10 + 20)*scale));
					break;
				case 26:
					vertices.push_back(glm::vec2(raCenter[5].x + r.value, (10)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, (10)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 1 * side + (10)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, (10)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 1 * side + (10)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, 1 * side + (10)*scale));
					break;
				case 7:
					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -2 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -2 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -3 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -2 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -3 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -3 * side - (10 + 20 + 20)*scale));
					break;
				case 19:
					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -2 * side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -2 * side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -2 * side - (10 + 20)*scale));
					break;
				case 27:
					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -(10)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -(10)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -side - (10)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -(10)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -side - (10)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -side - (10)*scale));
					break;
				case 8:
					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -2 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -2 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -3 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -2 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -3 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -3 * side - (10 + 20 + 20)*scale));
					break;
				case 20:
					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -2 * side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -2 * side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -2 * side - (10 + 20)*scale));
					break;
				case 28:
					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -(10)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -(10)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -side - (10)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -(10)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -side - (10)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -side - (10)*scale));
					break;
				case  9:
					model = glm::rotate(model, glm::radians(20.0f + 180.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(11.25f, raCenter[8], r.value);

					zz = glm::vec2(-zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[2] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));
					break;
				case 21:
					model = glm::rotate(model, glm::radians(40.0f + 180.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(33.75f, raCenter[8], r.value);

					zz = glm::vec2(-zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[2] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));
					break;
				case 10:
					model = glm::rotate(model, glm::radians(60.0f + 180.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(56.25f, raCenter[9], r.value);

					zz = glm::vec2(-zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[2] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));
					break;
				case 22:
					model = glm::rotate(model, glm::radians(80.0f + 180.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(78.75f, raCenter[9], r.value);

					zz = glm::vec2(-zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[2] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));
					break;
				case 11:
					model = glm::rotate(model, glm::radians(10.0f + 270.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(78.75f, raCenter[10], r.value);

					zz = glm::vec2(zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[2] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));
					break;
				case 23:
					model = glm::rotate(model, glm::radians(30.0f + 270.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(56.25f, raCenter[10], r.value);

					zz = glm::vec2(zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[2] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));
					break;
				case 12:
					model = glm::rotate(model, glm::radians(50.0f + 270.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(33.75f, raCenter[11], r.value);

					zz = glm::vec2(zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[2] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));
					break;
				case 24:
					model = glm::rotate(model, glm::radians(70.0f + 270.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(11.25f, raCenter[11], r.value);

					zz = glm::vec2(zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[2] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));
					break;
				default:
					break;
				}
			}
			/*model = glm::rotate(model, glm::radians((RD.sangle[r.id - 1] + RD.eangle[r.id - 1]) / 2), glm::vec3(0.0, 0.0, 1.0));
			for (int i = 0; i < 4; i++)
			{
				f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
			}
			vertices.push_back(glm::vec2(a + raCenter[r.id - 1]));

			vertices.push_back(glm::vec2(b + raCenter[r.id - 1]));

			vertices.push_back(glm::vec2(c + raCenter[r.id - 1]));

			vertices.push_back(glm::vec2(b + raCenter[r.id - 1]));

			vertices.push_back(glm::vec2(c + raCenter[r.id - 1]));

			vertices.push_back(glm::vec2(d + raCenter[r.id - 1]));*/

			unsigned int VAO, VBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

			/*glEnable(GL_LINE_SMOOTH);
			glLineWidth(5)*/;
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, vertices.size());

			glBindVertexArray(0);
		}
	}
	void Db(Ra r)
	{
			vector<glm::vec2> vertices;


				//块的形状
				float t1 = r.value * PI / 8;
				float side = 740 * scale;
				float wide = 100 * scale;
				float t2 = (r.value - wide) * PI / 8;
				float interval = 1 * scale;
				glm::mat4 model = glm::mat4(1.0f);
				glm::vec2 zz;

				glm::vec2 f[4] =
				{
					glm::vec2(wide / 2,  t1 / 2),
					glm::vec2(wide / 2, -t2 / 2),
					glm::vec2(-wide / 2, -t2 / 2),
					glm::vec2(-wide / 2,  t1 / 2),
				};

				glm::vec2 a, b, c, d;
				float width = 0.01333333 * 2;

				switch (r.id)
				{
				case 1:
					model = glm::rotate(model, glm::radians(70.0f + 90.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(11.25f, raCenter[0], r.value);

					zz = glm::vec2(-zz.x, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[2] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));

					break;
				case 13:
					model = glm::rotate(model, glm::radians(50.0f + 90.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(33.75f, raCenter[0], r.value);

					zz = glm::vec2(-zz.x, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[2] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));
					break;
				case 2:
					model = glm::rotate(model, glm::radians(30.0f + 90.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(56.25f, raCenter[1], r.value);

					zz = glm::vec2(-zz.x, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[2] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));
					break;
				case 14:
					model = glm::rotate(model, glm::radians(10.0f + 90.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(78.75f, raCenter[1], r.value);

					zz = glm::vec2(-zz.x, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[2] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));
					break;
				case 3:
					model = glm::rotate(model, glm::radians(80.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(78.75f, raCenter[2], r.value);

					zz = glm::vec2(zz.x, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[2] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));
					break;
				case 15:
					model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(56.25f, raCenter[2], r.value);

					zz = glm::vec2(zz.x, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));

					vertices.push_back(glm::vec2(f[1] + FC2 + zz));

					vertices.push_back(glm::vec2(f[2] + FC2 + zz));

					vertices.push_back(glm::vec2(f[3] + FC2 + zz));
					break;
				case 4:
					model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(33.75f, raCenter[3], r.value);

					zz = glm::vec2(zz.x, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[2] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));
					break;
				case 16:
					model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(11.25f, raCenter[3], r.value);
					zz = glm::vec2(zz.x, zz.y);
					vertices.push_back(glm::vec2(f[0] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));

					vertices.push_back(glm::vec2(f[1] + FC1 + zz));

					vertices.push_back(glm::vec2(f[2] + FC1 + zz));

					vertices.push_back(glm::vec2(f[3] + FC1 + zz));
					break;
				case 5:
					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 2 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, 2 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 3 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, 2 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 3 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, 3 * side + (10 + 20 + 20)*scale));
					break;
				case 17:
					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 1 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, 1 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 2 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, 1 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 2 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, 2 * side + (10 + 20)*scale));
					break;
				case 25:
					vertices.push_back(glm::vec2(raCenter[4].x - r.value, (10)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, (10)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 1 * side + (10)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, (10)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - r.value, 1 * side + (10)*scale));

					vertices.push_back(glm::vec2(raCenter[4].x - wide - r.value, 1 * side + (10)*scale));
					break;
				case 6:
					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 2 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, 2 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 3 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, 2 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 3 * side + (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, 3 * side + (10 + 20 + 20)*scale));
					break;
				case 18:
					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 1 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, 1 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 2 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, 1 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 2 * side + (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, 2 * side + (10 + 20)*scale));
					break;
				case 26:
					vertices.push_back(glm::vec2(raCenter[5].x + r.value, (10)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, (10)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 1 * side + (10)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, (10)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + r.value, 1 * side + (10)*scale));

					vertices.push_back(glm::vec2(raCenter[5].x + wide + r.value, 1 * side + (10)*scale));
					break;
				case 7:
					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -2 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -2 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -3 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -2 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -3 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -3 * side - (10 + 20 + 20)*scale));
					break;
				case 19:
					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -2 * side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -2 * side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -2 * side - (10 + 20)*scale));
					break;
				case 27:
					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -(10)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -(10)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -side - (10)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -(10)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - r.value, -side - (10)*scale));

					vertices.push_back(glm::vec2(raCenter[6].x - wide - r.value, -side - (10)*scale));
					break;
				case 8:
					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -2 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -2 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -3 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -2 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -3 * side - (10 + 20 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -3 * side - (10 + 20 + 20)*scale));
					break;
				case 20:
					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -2 * side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -2 * side - (10 + 20)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -2 * side - (10 + 20)*scale));
					break;
				case 28:
					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -(10)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -(10)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -side - (10)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -(10)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + r.value, -side - (10)*scale));

					vertices.push_back(glm::vec2(raCenter[7].x + wide + r.value, -side - (10)*scale));
					break;
				case  9:
					model = glm::rotate(model, glm::radians(20.0f + 180.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(11.25f, raCenter[8], r.value);

					zz = glm::vec2(-zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[2] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));
					break;
				case 21:
					model = glm::rotate(model, glm::radians(40.0f + 180.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(33.75f, raCenter[8], r.value);

					zz = glm::vec2(-zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[2] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));
					break;
				case 10:
					model = glm::rotate(model, glm::radians(60.0f + 180.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(56.25f, raCenter[9], r.value);

					zz = glm::vec2(-zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[2] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));
					break;
				case 22:
					model = glm::rotate(model, glm::radians(80.0f + 180.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(78.75f, raCenter[9], r.value);

					zz = glm::vec2(-zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[2] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));
					break;
				case 11:
					model = glm::rotate(model, glm::radians(10.0f + 270.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(78.75f, raCenter[10], r.value);

					zz = glm::vec2(zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[2] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));
					break;
				case 23:
					model = glm::rotate(model, glm::radians(30.0f + 270.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(56.25f, raCenter[10], r.value);

					zz = glm::vec2(zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));

					vertices.push_back(glm::vec2(f[1] + BC2 + zz));

					vertices.push_back(glm::vec2(f[2] + BC2 + zz));

					vertices.push_back(glm::vec2(f[3] + BC2 + zz));
					break;
				case 12:
					model = glm::rotate(model, glm::radians(50.0f + 270.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(33.75f, raCenter[11], r.value);

					zz = glm::vec2(zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[2] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));
					break;
				case 24:
					model = glm::rotate(model, glm::radians(70.0f + 270.0f), glm::vec3(0.0, 0.0, 1.0));
					for (int i = 0; i < 4; i++)
					{
						f[i] = glm::vec2(model * glm::vec4(f[i], 0.0, 0.0));
					}

					zz = circleLine(11.25f, raCenter[11], r.value);

					zz = glm::vec2(zz.x, -zz.y);
					vertices.push_back(glm::vec2(f[0] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));

					vertices.push_back(glm::vec2(f[1] + BC1 + zz));

					vertices.push_back(glm::vec2(f[2] + BC1 + zz));

					vertices.push_back(glm::vec2(f[3] + BC1 + zz));
					break;
				default:
					break;
				}

			unsigned int VAO, VBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

			/*glEnable(GL_LINE_SMOOTH);
			glLineWidth(5)*/;
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, vertices.size());

			glBindVertexArray(0);
		
	}
};
#endif // !RADAR_H
