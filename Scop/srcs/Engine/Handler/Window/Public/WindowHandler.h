/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WindowHandler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:35:10 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/07 09:26:50 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

struct WindowHandler {
private:
	static WindowHandler* instance;

public:
	GLFWwindow* glWindow;

	static const char* title;
	static unsigned int width;
	static unsigned int height;

	WindowHandler(void);
	~WindowHandler(void);

	WindowHandler(WindowHandler&) = delete;
	void operator=(const WindowHandler&) = delete;

	static void SetTitle(const char* title);
	static void SetDimensions(unsigned int width, unsigned int height);\
	static float GetRatio(void);

	void Open(void);

	static void ErrorCallback(int error, const char* description);
	static void ViewportCallback(GLFWwindow* window, int width, int height);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseCursorCallback(GLFWwindow* window, double xpos, double ypos);
	static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void JoystickCallback(int joystickId, int event);
	static void DropCallback(GLFWwindow* window, int count, const char** paths);

	static WindowHandler* GetInstance(void);
};
