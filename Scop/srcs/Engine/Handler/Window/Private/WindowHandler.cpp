/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WindowHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:30:22 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/07 09:41:34 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WindowHandler.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"

WindowHandler* WindowHandler::instance = nullptr;
const char* WindowHandler::title = nullptr;
unsigned int WindowHandler::width = 0;
unsigned int WindowHandler::height = 0;

WindowHandler::WindowHandler(void) {}
WindowHandler::~WindowHandler(void) {
	if (this->glWindow != NULL) {
		glfwDestroyWindow(this->glWindow);
		glfwTerminate();
	}
	exit(EXIT_SUCCESS);
}

void WindowHandler::SetTitle(const char* title) {
	WindowHandler::title = title;
}

void WindowHandler::SetDimensions(unsigned int width, unsigned int height) {
	WindowHandler::width = width;
	WindowHandler::height = height;
}

float WindowHandler::GetRatio(void) {
	return (float) WindowHandler::width / (float) WindowHandler::height;
}

void WindowHandler::Open(void) {
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit()) exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); // 2 on mac perhaps
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0); // 0 on mac perhaps
#if __APPLE__
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	glfwWindowHint(GLFW_SAMPLES, 16);
	glfwWindowHint(GLFW_DEPTH_BITS, 16);
	glfwWindowHint(GLFW_RESIZABLE, true);

	this->glWindow = glfwCreateWindow(
		WindowHandler::width, WindowHandler::height, WindowHandler::title,
		NULL, NULL);

	if (!this->glWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->glWindow);

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(this->glWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	//glfwSetInputMode(this->glWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(this->glWindow, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetInputMode(this->glWindow, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

    glfwSetFramebufferSizeCallback(this->glWindow, ViewportCallback);
	glfwSetCursorPosCallback(this->glWindow, MouseCursorCallback);
	glfwSetScrollCallback(this->glWindow, MouseScrollCallback);
	glfwSetMouseButtonCallback(this->glWindow, MouseButtonCallback);
	glfwSetKeyCallback(this->glWindow, KeyCallback);
	glfwSetJoystickCallback(JoystickCallback);
	glfwSetDropCallback(this->glWindow, DropCallback);

	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDisable(GL_CULL_FACE);

	glDepthFunc(GL_LESS);
	glfwSwapInterval(1);
}

void WindowHandler::ErrorCallback(int error, const char* description) {
	(void) error;
	fprintf(stderr, "Error: %s\n", description);
}

void WindowHandler::ViewportCallback(GLFWwindow* window, int width, int height) {
	(void) window;
	glViewport(0, 0, width, height);
	WindowHandler::width = width;
	WindowHandler::height = height;
}


void WindowHandler::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	(void) scancode;
	(void) mods;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	KeyboardHandler::GetInstance()->UpdateKey(key, action);
}

void WindowHandler::MouseCursorCallback(GLFWwindow* window, double xpos, double ypos) {
	(void) window;
	MouseHandler::GetInstance()->UpdatePosition((float) xpos, (float) ypos);
}

void WindowHandler::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	(void) window;
	(void) xoffset;
	MouseHandler::GetInstance()->UpdateScroll((float) yoffset);
}

void WindowHandler::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	(void) window;
	(void) mods;
	MouseHandler::GetInstance()->UpdateButton(button, action);
}

void WindowHandler::JoystickCallback(int joystickId, int event) {
	(void) joystickId;
	(void) event;
}

void WindowHandler::DropCallback(GLFWwindow* window, int count, const char** paths) {
	(void) window;
	for (int i = 0;  i < count;  i++)
		std::cout << paths[i] << std::endl;
}


WindowHandler* WindowHandler::GetInstance(void) {
	if (instance == nullptr) {
		instance = new WindowHandler();
	}
	return instance;
}
