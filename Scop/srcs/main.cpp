/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 23:07:57 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/07 13:04:10 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WindowHandler.h"
#include "CameraHandler.h"
#include "MouseHandler.h"
#include "KeyboardHandler.h"
#include "ModelLoader.h"
#include "StringUtils.h"
#include "TextureLoader.h"
#include <cstdlib>

Model* model;

float yaw = 0;
float pitch = 0;
float lastxpos = 0;
float lastypos = 0;
void Update(void) {
	CameraHandler* camera = CameraHandler::GetInstance();
	MouseHandler* mouse = MouseHandler::GetInstance();
	WindowHandler* window = WindowHandler::GetInstance();
	KeyboardHandler* keyboard = KeyboardHandler::GetInstance();

	if (keyboard->IsKeyPressed(GLFW_KEY_W))
		camera->position -= Vector3(camera->front).Scale(0.25f);
	if (keyboard->IsKeyPressed(GLFW_KEY_S))
		camera->position += Vector3(camera->front).Scale(0.25f);
	if (keyboard->IsKeyPressed(GLFW_KEY_A))
		camera->position += Vector3::Cross(camera->front, camera->up).GetNormalized().Scale(0.25f);
	if (keyboard->IsKeyPressed(GLFW_KEY_D))
		camera->position -= Vector3::Cross(camera->front, camera->up).GetNormalized().Scale(0.25f);
	if (keyboard->IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
		camera->position -= Vector3(camera->up).Scale(0.25f);
	if (keyboard->IsKeyPressed(GLFW_KEY_SPACE))
		camera->position += Vector3(camera->up).Scale(0.25f);

	if (keyboard->IsKeyPressed(GLFW_KEY_H) && model->textureOpacity == 1.0) {
		model->textureOpacity = 0;
	} if (keyboard->IsKeyPressed(GLFW_KEY_T) && model->textureOpacity == 0.0) {
		model->textureOpacity = 1;
	}

	if (mouse->IsButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
		double xpos, ypos;
		glfwGetCursorPos(window->glWindow, &xpos, &ypos);

		float xoffset = xpos - lastxpos;
		float yoffset = lastypos - ypos;
		lastxpos = xpos;
		lastypos = ypos;

		yaw   += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		float rYaw = yaw / 180 * M_PI;
		float rPitch = pitch / 180 * M_PI;

		camera->front = Vector3(cos(rYaw) * cos(rPitch), sin(rPitch), sin(rYaw) * cos(rPitch)).GetNormalized();
	}
	model->Rotate(0, glfwGetTime(), 0);
	model->Scale(10.0f / Vector3::Magnitude(model->boundingBox));
	model->Update();
}

std::string objectFile = "./resources/Models/42.obj";
std::string textureFile = "./resources/Models/poney.jpg";

void UpdateModel(GLFWwindow* window, int count, const char** paths) {
	(void) window;
	if (paths != nullptr && count > 0) {
		char* path = strdup(paths[0]);
		if (StringUtils::EndsWith(std::string(path), ".obj")) {
			ModelLoader* modelLoader = ModelLoader::WithFile((objectFile = std::string(path)).c_str())
				->WithTexture(textureFile.c_str())
				->WithVertexShader("./resources/Shaders/default.vert")
				->WithFragmentShader("./resources/Shaders/default.frag");
			Model* tmp = modelLoader->Load();

			delete modelLoader;
			if (model != nullptr) {
				delete model;
			}

			model = tmp;
			model->Initialize();
		}
		else if (StringUtils::EndsWith(std::string(path), ".jpg")
			|| StringUtils::EndsWith(std::string(path), ".png")) {
			Texture* texture = TextureLoader::FromPath((textureFile = std::string(path)).c_str());
			Texture* tmp = model->texture;
			model->texture = texture;
			delete tmp;
		} else {
			std::cerr << "Unknown file type" << std::endl;
		}
		free(path);
	}
}

int main(void) {
	WindowHandler::SetTitle("Scop");
	WindowHandler::SetDimensions(720, 720);
	WindowHandler::GetInstance()->Open();

	CameraHandler::GetInstance()->SetPerspectiveProjection(70.0f / 180.0f * M_PI, 0.1f, 1000000.0f);

	glfwSetDropCallback(WindowHandler::GetInstance()->glWindow, UpdateModel);

	ModelLoader* modelLoader = ModelLoader::WithFile(objectFile.c_str())
		->WithTexture(textureFile.c_str())
		->WithVertexShader("./resources/Shaders/default.vert")
		->WithFragmentShader("./resources/Shaders/default.frag");

	model = modelLoader->Load();
	model->Initialize();
	delete modelLoader;

	while (!glfwWindowShouldClose(WindowHandler::GetInstance()->glWindow))
	{
		glfwPollEvents();

		int w, h;
		glfwGetFramebufferSize(WindowHandler::GetInstance()->glWindow, &w, &h);
		glViewport(0, 0, WindowHandler::width, WindowHandler::height);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (model != nullptr) {
			Update();
		}

		glfwSwapBuffers(WindowHandler::GetInstance()->glWindow);
	}

	delete model;
	delete CameraHandler::GetInstance();
}
