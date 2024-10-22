/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CameraHandler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:34:12 by acoezard          #+#    #+#             */
/*   Updated: 2023/02/28 12:35:46 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "ShaderProgram.h"
#include "WindowHandler.h"
#include "Vector3.h"

struct CameraHandler {
private:
	static CameraHandler* instance;

public:
	float fov;
	float zNear;
	float zFar;

	Vector3 position;
	Vector3 front;
	Vector3 up;

	CameraHandler(Vector3 position);
	~CameraHandler(void);

	CameraHandler(CameraHandler&) = delete;
	void operator=(const CameraHandler&) = delete;

	void SetPerspectiveProjection(float fov, float zNear, float zFar);

	Matrix GetProjection(void);
	Matrix GetView(void);

	static CameraHandler* GetInstance(void);
};
