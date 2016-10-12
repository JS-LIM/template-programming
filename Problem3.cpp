#include<GLFW/glfw3.h>
#include<iostream>
#include<string.h>
#include<vector>

const int width = 600;
const int height = 600;

float* pixels = new float[width*height * 3];


void drawOnePixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawOnePixel(i, j, red, green, blue);
	}
}

class Box // NO PARENT
{
public: 
	void draw()
	{
		std::cout << "Box" << std::endl;
	}
};

class Circle // NO PARENT
{
public:
	void draw()
	{
		std::cout << "Circle" << std::endl;
	}
};

class GeometricObjectInterface
{
public:
	virtual void draw() = 0;
	// implement here
};

template<class T_OPERATION>
class GeometricObject : public GeometricObjectInterface
{
public:
	void draw()
	{
		T_OPERATION operation;
		operation.draw();
	}
};


void drawOnPixelBuffer()
{
//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
std::fill_n(pixels, width*height * 3, 1.0f);	// white background

//for (int i = 0; i<width*height; i++) {
//	pixels[i * 3 + 0] = 1.0f; // red
//	pixels[i * 3 + 1] = 1.0f; // green
//	pixels[i * 3 + 2] = 1.0f; // blue
//}

const int i = rand() % width, j = rand() % height;
//drawPixel(i, j, 0.0f, 0.0f, 0.0f);

// drawing a line
//TODO: anti-aliasing
const int i0 = 100, i1 = 200;
const int j0 = 50, j1 = 80;
drawLine(i0, j0, i1, j1, 1.0f, 0.0f, 0.0f);

//TODO: try moving object
}

// And implement an templatized GeometricObject class.
int main()
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "My window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		//const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		//std::fill_n(pixels, width*height * 3, 1.0f);	// white background

		//white background color (1.0f 1.0f 1.0f)
		for (int j = 0; j <height; j++)
			for (int i = 0; i < width; i++)
			{
				pixels[(i + width*j) * 3 + 0] = 1.0f;
				pixels[(i + width*j) * 3 + 1] = 1.0f;
				pixels[(i + width*j) * 3 + 2] = 1.0f;
			}

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Make the window's context current */
		glfwMakeContextCurrent(window);
		glClearColor(1, 1, 1, 1); // while background

		std::vector<GeometricObjectInterface*> obj_list;

		obj_list.push_back(new GeometricObject<Box>);
		obj_list.push_back(new GeometricObject<Circle>);
		for (auto itr : obj_list)
			itr->draw();

		//drawOnPixelBuffer();

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();


		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}