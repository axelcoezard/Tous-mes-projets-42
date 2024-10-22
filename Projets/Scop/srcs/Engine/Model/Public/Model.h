/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:41:13 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/07 12:29:06 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include "EngineBehavior.h"
#include "ShaderProgram.h"
#include "Vertex.h"
#include "Texture.h"

struct Model: public EngineBehavior {
	ShaderProgram* shaderProgram;
	Texture* texture;

	const char* path;

	unsigned int VAO, VBO, IBO;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Matrix modelMatrix;
	float textureOpacity;
	Vector3 boundingBox;

	void Initialize(void);
	void Update(void);

	void Rotate(float angleX, float angleY, float angleZ);
	void Translate(float offsetX, float offsetY, float offsetZ);
	void Scale(float scale);

	~Model(void);
};
