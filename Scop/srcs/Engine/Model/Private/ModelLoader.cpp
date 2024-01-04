/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModelLoader.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:52:21 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/07 12:30:02 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <string>
#include <cstdlib>
#include <iostream>

#include "ModelLoader.h"
#include "TextureLoader.h"
#include "StringUtils.h"
#include "Vector3.h"

ModelLoader::ModelLoader(const char* path) {
	this->path = path;
}

ModelLoader* ModelLoader::WithFile(const char* path) {
	return new ModelLoader(path);
}

ModelLoader* ModelLoader::WithVertexShader(const char* vsPath) {
	this->vsPath = vsPath;
	return this;
}

ModelLoader* ModelLoader::WithFragmentShader(const char* fsPath) {
	this->fsPath = fsPath;
	return this;
}

ModelLoader* ModelLoader::WithTexture(const char* texturePath) {
	this->texturePath = texturePath;
	return this;
}

Model* ModelLoader::Load(void) {
	Model* model = new Model();
	model->path = this->path;

	if (this->vsPath != nullptr && this->fsPath != nullptr) {
		model->shaderProgram = ShaderLoader::GetInstance()
			->LoadFromFiles(this->vsPath, this->fsPath);
	}

	if (this->texturePath != nullptr) {
		model->texture = TextureLoader::FromPath(this->texturePath);
	}

	std::ifstream modelFile;
	modelFile.open(model->path);
	if (modelFile.is_open()) {
		std::vector<Vector3> positions;
		std::vector<Vector2> textures;
		std::vector<Vector3> normals;

		GLfloat min_x, max_x, min_y, max_y, min_z, max_z;
		bool firstVertex = true;

		std::string line;
		while (std::getline(modelFile, line)) {
			std::vector<std::string> data = StringUtils::Split(line, ' ');

			if (line[0] == '#' || line[0] == 'o') {
				continue;
			// it is a vertex position
			} else if (line[0] == 'v' && line[1] == ' ') {
				Vector3 position(stof(data.at(1)), stof(data.at(2)), stof(data.at(3)));
				positions.push_back(position);
			// it is a texture position
			} else if (line[0] == 'v' && line[1] == 't') {
				Vector2 texture(stof(data.at(1)), stof(data.at(2)));
				textures.push_back(texture);
			// it is a normal position
			} else if (line[0] == 'v' && line[1] == 'n') {
				Vector3 normal(stof(data.at(1)), stof(data.at(2)), stof(data.at(3)));
				normals.push_back(normal);
			// it is an index
			} else if (line[0] == 'f' && line[1] == ' ') {
				for (size_t i = 1; i < data.size(); i++) {
					std::vector<std::string> parts = StringUtils::Split(data[i], '/');

					Vertex vertex = (Vertex) {
						.position = positions[stoi(parts.at(0)) - 1],
						.texture = textures[stoi(parts.at(1)) - 1],
						.normal = normals[stoi(parts.at(2)) - 1]
					};

					Vector3 position = vertex.position;
					if (firstVertex) {
						min_x = max_x = position.x;
						min_y = max_y = position.y;
						min_z = max_z = position.z;
						firstVertex = false;
					} else {
						if (position.x < min_x) min_x = position.x;
						if (position.x > max_x) max_x = position.x;
						if (position.y < min_y) min_y = position.y;
						if (position.y > max_y) max_y = position.y;
						if (position.z < min_z) min_z = position.z;
						if (position.z > max_z) max_z = position.z;
					}

					model->vertices.push_back(vertex);
				}
			}
		}

		float verticesSize = model->vertices.size();
		model->boundingBox = Vector3(max_x - min_x, max_y - min_y, max_z - min_z);
		Vector3 size(model->boundingBox.x / 2.0 + min_x,
					model->boundingBox.y / 2.0 + min_y,
					model->boundingBox.z / 2.0 + min_z);
		for (size_t i = 0; i < verticesSize; i++) {
			Vertex vertex = model->vertices[i];
			model->vertices[i].position.x = (vertex.position.x - size.x);
			model->vertices[i].position.y = (vertex.position.y - size.y);
			model->vertices[i].position.z = (vertex.position.z - size.z);
		}
		modelFile.close();
	}
	return model;
}
