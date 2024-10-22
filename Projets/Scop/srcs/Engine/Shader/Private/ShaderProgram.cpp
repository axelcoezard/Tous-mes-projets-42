/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderProgram.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 00:32:05 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/06 13:46:38 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShaderProgram.h"

ShaderProgram::~ShaderProgram(void) {}

void ShaderProgram::Prepare(void) {
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &this->vertexSource, NULL);
	glCompileShader(vertexShader);
	free((char *) vertexSource);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &this->fragmentSource, NULL);
	glCompileShader(fragmentShader);
	free((char *) fragmentSource);

	this->id = glCreateProgram();
	glAttachShader(this->id, vertexShader);
	glAttachShader(this->id, fragmentShader);
}

void ShaderProgram::Link(void) {
	glLinkProgram(this->id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::Use(void) {
	glUseProgram(this->id);
}

void ShaderProgram::BindAttribLocation(unsigned int position, const char* name) const {
	glBindAttribLocation(this->id, position, name);
}

int ShaderProgram::GetUniformLocation(const char* name) const {
	return glGetUniformLocation(this->id, name);
}

int ShaderProgram::GetAttribLocation(const char* name) const {
	return glGetAttribLocation(this->id, name);
}

void ShaderProgram::SetBool(const char* name, bool value) const {
	glUniform1i(GetUniformLocation(name), (int) value);
}

void ShaderProgram::SetInt(const char* name, int value) const {
	glUniform1i(GetUniformLocation(name), value);
}

void ShaderProgram::SetFloat(const char* name, float value) const {
	glUniform1f(GetUniformLocation(name), value);
}

void ShaderProgram::SetPointer(const char* name, GLint size, GLsizei stride, const void* pointer) const {
	int location = glGetAttribLocation(this->id, name);
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, pointer);
	glEnableVertexAttribArray(location);
}

void ShaderProgram::SetVector3(const char* name, const Vector3& vector) const {
	glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
}

void ShaderProgram::SetMatrix(const char* name, const Matrix& matrix) const {
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, (const GLfloat*) matrix.values);
}
