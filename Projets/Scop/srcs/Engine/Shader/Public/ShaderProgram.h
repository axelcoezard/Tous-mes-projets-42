/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderProgram.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:40:27 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/06 13:00:17 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Matrix.h"
#include "Vector3.h"

struct ShaderProgram {
	unsigned int id;

	const char* vertexSource;
	const char* fragmentSource;

	unsigned int vertexShader;
	unsigned int fragmentShader;

	~ShaderProgram(void);

	void Prepare(void);
	void Link(void);
	void Use(void);

	void BindAttribLocation(unsigned int position, const char* name) const;
	int GetUniformLocation(const char* name) const;
	int GetAttribLocation(const char* name) const;

	void SetBool(const char* name, bool value) const;
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;
	void SetPointer(const char* name, GLint size, GLsizei stride, const void* pointer) const;
	void SetVector3(const char* name, const Vector3& vector) const;
	void SetMatrix(const char* name, const Matrix& matrix) const;
};
