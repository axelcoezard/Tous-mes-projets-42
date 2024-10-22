/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CameraHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:39:12 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/01 14:35:39 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CameraHandler.h"
#include "WindowHandler.h"
#include "ShaderProgram.h"

#include "Vector3.h"
#include "Matrix.h"

CameraHandler* CameraHandler::instance = nullptr;

CameraHandler::CameraHandler(Vector3 position)
	: position(position), front(Vector3::Backward), up(Vector3::Up) {}

CameraHandler::~CameraHandler(void) {}

void CameraHandler::SetPerspectiveProjection(float fov, float zNear, float zFar) {
	this->fov = fov;
	this->zNear = zNear;
	this->zFar = zFar;
}

Matrix CameraHandler::GetProjection(void) {
	return Matrix::GetPerspective(this->fov, WindowHandler::GetRatio(), this->zNear, this->zFar);
}

Matrix CameraHandler::GetView(void) {
	Vector3 cameraPos = Vector3(position.x, position.y, position.z);
	Vector3 cameraTarget = cameraPos + front;
	return Matrix::LookAt(cameraPos, cameraTarget, up);
}

CameraHandler* CameraHandler::GetInstance(void) {
	if (instance == nullptr) {
		instance = new CameraHandler(Vector3(0.0f, 0.0f, -10.0f));
	}
	return instance;
}

