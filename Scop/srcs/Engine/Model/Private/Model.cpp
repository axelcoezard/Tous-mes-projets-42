/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:10:04 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/07 11:13:55 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Model.h"
#include "Light.h"
#include "Matrix.h"
#include "CameraHandler.h"

void Model::Initialize(void) {
	textureOpacity = 1.0f;

#ifndef __APPLE__
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(VAO);
#endif

	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_STATIC_DRAW);

	if (this->indices.size() > 0) {
		glGenBuffers(1, &this->IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);
	}

	this->shaderProgram->Prepare();

#if __APPLE__
	this->shaderProgram->BindAttribLocation(0, "vPosition");
	this->shaderProgram->BindAttribLocation(1, "vTexture");
	this->shaderProgram->BindAttribLocation(2, "vNormal");
#endif

	this->shaderProgram->Link();
	this->shaderProgram->SetPointer("vPosition", 3, sizeof(Vertex), (void*) offsetof(Vertex, position));
	this->shaderProgram->SetPointer("vTexture", 2, sizeof(Vertex), (void*) offsetof(Vertex, texture));
	this->shaderProgram->SetPointer("vNormal", 3, sizeof(Vertex), (void*) offsetof(Vertex, normal));
	this->shaderProgram->Use();

#ifndef __APPLE__
	glBindVertexArray(0);
#endif
}

Light* light = new Light(0, 0, 20, 1.0, 1.0, 1.0);

void Model::Update(void) {
	this->shaderProgram->SetMatrix("projection", CameraHandler::GetInstance()->GetProjection());
	this->shaderProgram->SetMatrix("view", CameraHandler::GetInstance()->GetView());
	this->shaderProgram->SetMatrix("model", modelMatrix);

	this->shaderProgram->SetVector3("lightPosition", light->position);
	this->shaderProgram->SetVector3("lightColor", light->color);
	this->shaderProgram->SetFloat("textureOpacity", textureOpacity);

	this->texture->Bind();
#ifndef __APPLE__
	glBindVertexArray(VAO);
	if (this->indices.size() > 0) {
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(this->indices.size()), GL_UNSIGNED_INT, 0);
	} else {
#endif
		glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
#ifndef __APPLE__
	}
	glBindVertexArray(0);
#endif
	Matrix::Identity(modelMatrix);
}

void Model::Rotate(float angleX, float angleY, float angleZ) {
	if (angleX != 0.0f) { Matrix::RotateX(modelMatrix, angleX); }
	if (angleY != 0.0f) { Matrix::RotateY(modelMatrix, angleY); }
	if (angleZ != 0.0f) { Matrix::RotateZ(modelMatrix, angleZ); }
}

void Model::Translate(float offsetX, float offsetY, float offsetZ) {
	Matrix::Translate(modelMatrix, offsetX, offsetY, offsetZ);
}

void Model::Scale(float scale) {
	Matrix::Scale(modelMatrix, scale);
}

Model::~Model(void) {
	delete this->shaderProgram;
	glDeleteTextures(1, &this->texture->id);
	delete this->texture;
#ifndef __APPLE__
	glDeleteVertexArrays(1, &this->VAO);
#endif
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->IBO);
}
