#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>
#include <radar.h>
#include <CANAnalysis.h>

#include "barrier.h"
#include <iostream>

#include<fstream>
#include<stdlib.h>
#include<vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void testTXT();
void testCanA();
vector <Ra> Read_TXT(string str_Path);
// settings
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("shader.vs", "shader.fs"); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions         // colors
		 0.124f,  0.3083f, 0.0f,  0.0f, 0.0f, 1.0f,   // top 

		-0.124f,  0.3083f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.124f, -0.3083f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.124f, -0.3083f, 0.0f,  0.0f, 0.0f, 1.0f,  // top 
		 
    };


    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Radar ra;
	ra.Init();
	//vector <float> v = ra.readTxt("E:/hh.txt");
	ifstream infile;
	//int ii = 0;
	/*infile.open("E:/hh.txt");
	string str;
	getline(infile, str);
	Ra r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12;
	r1.id = 1;
	r2.id = 2;
	r3.id = 3;
	r4.id = 4;
	r5.id = 5;
	r6.id = 6;
	r7.id = 7;
	r8.id = 8;
	r9.id = 9;
	r10.id = 10;
	r11.id = 11;
	r12.id = 12;
	r1.value = 0.0f;
	r2.value = 0.0f;
	r3.value = 0.0f;
	r4.value = 0.0f;
	r5.value = 0.0f;
	r6.value = 0.0f;
	r7.value = 0.0f;
	r8.value = 0.0f;
	r9.value = 0.0f;
	r10.value = 0.0f;
	r11.value = 0.0f;
	r12.value = 0.0f;*/
	//float test = 200.0f;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))//&& ii < (v.size() / 12 - 1)
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        ourShader.use();
		ourShader.setVec3("color", glm::vec3(0.0, 0.0, 0.0));
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
		ourShader.use();
		ourShader.setVec3("color", glm::vec3(1.0, 0.0, 0.0));
		


		//assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行
		//
		//getline(infile, str);
		//istringstream is(str);
		//
		//r1.id = 1;
		//r2.id = 2;
		//r3.id = 3;
		//r4.id = 4;
		//r5.id = 5;
		//r6.id = 6;
		//r7.id = 7;
		//r8.id = 8;
		//r9.id = 9;
		//r10.id = 10;
		//r11.id = 11;
		//r12.id = 12;
		//string s1, s2, t, s4, s5, s6, s7;
		//unsigned int d1, d2, d3, d4, d5, d6, d7, d8;
		//is >> s1 >> s2 >> t >> s4 >> s5 >> s6 >> s7 >> std::hex>> d1 >> d2 >> d3 >> d4 >> d5 >> d6 >> d7 >> d8;

		//if (s4 == "0x00000736")//侧边雷达值
		//{
		//	cout << str << endl;
		//	cout << s4 << "侧边雷达值占两个字节" << "\n" << d1 << " " << d2 << " " << d3 << " " << d4 << " " << d5 << " " << d6 << " " << d7 << " " << d8 << endl;
		//	int l1, l2, l3, l4;
		//	l1 = d1 * 16 * 16 + d2;
		//	l2 = d3 * 16 * 16 + d4;
		//	l3 = d5 * 16 * 16 + d6;
		//	l4 = d7 * 16 * 16 + d8;
		//	l1 = l1 > 200 && l1 < 5000 ? l1 : 0;
		//	l2 = l2 > 200 && l2 < 5000 ? l2 : 0;
		//	l3 = l3 > 200 && l3 < 5000 ? l3 : 0;
		//	l4 = l4 > 200 && l4 < 5000 ? l4 : 0;
		//	cout << l1 << " " << l2 << " " << l3 << " " << l4 << endl;
		//	r5.value = l1 * scale;
		//	r6.value = l2 * scale;
		//	r7.value = l3 * scale;
		//	r8.value = l4 * scale;
		//	/*ra.DrawBlock(r9);
		//	ra.DrawBlock(r10);
		//	ra.DrawBlock(r11);
		//	ra.DrawBlock(r12);*/
		//}
		//else if (s4 == "0x00000739")//前后8个雷达值
		//{
		//	cout << str << endl;
		//	cout << s4 << "前后8个雷达值" << "\n" << d1 << " " << d2 << " " << d3 << " " << d4 << " " << d5 << " " << d6 << " " << d7 << " " << d8 << endl;
		//	d1 = d1 > 20 && d1 < 250 ? d1 : 0;
		//	d2 = d2 > 20 && d2 < 250 ? d2 : 0;
		//	d3 = d3 > 20 && d3 < 250 ? d3 : 0;
		//	d4 = d4 > 20 && d4 < 250 ? d4 : 0;
		//	d5 = d5 > 20 && d5 < 250 ? d5 : 0;
		//	d6 = d6 > 20 && d6 < 250 ? d6 : 0;
		//	d7 = d7 > 20 && d7 < 250 ? d7 : 0;
		//	d8 = d8 > 20 && d8 < 250 ? d8 : 0;
		//	r1.value = d1 * scale * 10;
		//	r2.value = d2 * scale * 10;
		//	r3.value = d3 * scale * 10;
		//	r4.value = d4 * scale * 10;

		//	r9.value = d5 * scale * 10;
		//	r10.value = d6 * scale * 10;
		//	r11.value = d7 * scale * 10;
		//	r12.value = d8 * 0.0001333333f * 10;
		//	/*ra.DrawBlock(r1);
		//	ra.DrawBlock(r2);
		//	ra.DrawBlock(r3);
		//	ra.DrawBlock(r4);
		//	ra.DrawBlock(r5);
		//	ra.DrawBlock(r6);
		//	ra.DrawBlock(r7);
		//	ra.DrawBlock(r8);*/
		//}
		//else
		//{
		//	continue;
		//}
		/*ra.DrawBlock(r1);
		ra.DrawBlock(r2);
		ra.DrawBlock(r3);
		ra.DrawBlock(r4);
		ra.DrawBlock(r5);
		ra.DrawBlock(r6);
		ra.DrawBlock(r7);
		ra.DrawBlock(r8);
		ra.DrawBlock(r9);
		ra.DrawBlock(r10);
		ra.DrawBlock(r11);
		ra.DrawBlock(r12);*/
		/*ra.Db(r1);
		ra.Db(r2);
		ra.Db(r3);
		ra.Db(r4);
		ra.Db(r5);
		ra.Db(r6);
		ra.Db(r7);
		ra.Db(r8);
		ra.Db(r9);
		ra.Db(r10);
		ra.Db(r11);
		ra.Db(r12);
		r1.id = r1.id + 12;
		r2.id = r2.id + 12;
		r3.id = r3.id + 12;
		r4.id = r4.id + 12;
		r5.id = r5.id + 12;
		r6.id = r6.id + 12;
		r7.id = r7.id + 12;
		r8.id = r8.id + 12;
		r9.id = r9.id + 12;
		r10.id = r10.id + 12;
		r11.id = r11.id + 12;
		r12.id = r12.id + 12;
		ra.Db(r1);
		ra.Db(r2);
		ra.Db(r3);
		ra.Db(r4);
		ra.Db(r5);
		ra.Db(r6);
		ra.Db(r7);
		ra.Db(r8);
		ra.Db(r9);
		ra.Db(r10);
		ra.Db(r11);
		ra.Db(r12);
		
		Sleep(60);*/
		//ra.Db(800.0f);
		//}
		/*ra.Db(test);
		test++;
		Sleep(10);*/
		ra.Draw();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
	infile.close();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void testCanA()
{
	ifstream infile;
	char filename[256] = "E:/hh.txt";
	infile.open(filename);
	if (!infile)
	{
		cout << "error" << endl;
		system("pause");
	}
	else
	{
		cout << filename << " open success" << endl;
	}

	string str;
	getline(infile, str);
	CANRadarMessage RadarMessage = {};
	CANRadarMessage707 Message707 = {};
	while (getline(infile, str))
	{
		
		Str2StructData(str, RadarMessage);
		switch (RadarMessage.iFrameID)
		{
		case 0x707:
			StrctData707(RadarMessage, Message707);
			cout << str << endl;
			cout << RadarMessage.cFrameData[0]  << "hhh "<< endl;
			cout << "x" << " " << Message707.X << " y " << Message707.Y << endl;
			break;
		}
	}
}

void testTXT()
{
	vector <Ra> data;
	data = Read_TXT("E:/1.txt");
}

vector<Ra> Read_TXT(string str_Path)
{
	ifstream infile;
	infile.open(str_Path);
	vector<Ra> data;
	if (!infile)
	{
		cout << "error" << endl;
		system("pause");
		return data;
	}
	string str;
	float v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12;
	Ra r;
	r.id = 1;
	r.value = v1 * scale;
	data.push_back(r);
	r.id = 2;
	r.value = v2 * scale;
	data.push_back(r);
	r.id = 3;
	r.value = v3 * scale;
	data.push_back(r);
	r.id = 4;
	r.value = v4 * scale;
	data.push_back(r);

	/*while (infile >> v1 >> v2 >> v3 >> v4 >> v5 >> v6 >> v7 >> v8 >> v9 >> v10 >> v11 >> v12)
	{
		r.id = 1;
		r.value = v1 * scale;
		data.push_back(r);
		r.id = 2;
		r.value = v2 * scale;
		data.push_back(r);
		r.id = 3;
		r.value = v3 * scale;
		data.push_back(r);
		r.id = 4;
		r.value = v4 * scale;
		data.push_back(r);
		r.id = 5;
		r.value = v5 * scale;
		data.push_back(r);
		r.id = 6;
		r.value = v6 * scale;
		data.push_back(r);
		r.id = 7;
		r.value = v7 * scale;
		data.push_back(r);
		r.id = 8;
		r.value = v8 * scale;
		data.push_back(r);
		r.id = 9;
		r.value = v9 * scale;
		data.push_back(r);
		r.id = 10;
		r.value = v10 * scale;
		data.push_back(r);
		r.id = 11;
		r.value = v11 * scale;
		data.push_back(r);
		r.id = 12;
		r.value = v12 * scale;
		data.push_back(r);
	}*/
	return data;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

