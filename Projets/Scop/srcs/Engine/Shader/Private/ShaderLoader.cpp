/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderLoader.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:52:10 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/05 00:16:21 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShaderLoader.h"

ShaderLoader* ShaderLoader::instance = nullptr;

ShaderLoader::ShaderLoader(void) {}
ShaderLoader::~ShaderLoader(void) {}

std::string ShaderLoader::LoadFromFile(const char* shaderPath) {
	std::ifstream shaderFile;
	std::string shaderSource;
	shaderFile.open(shaderPath);
	if (shaderFile.is_open()) {
		shaderSource.assign(
			std::istreambuf_iterator<char>(shaderFile),
			std::istreambuf_iterator<char>());
		shaderFile.close();
	}
	return shaderSource;
}

ShaderProgram* ShaderLoader::LoadFromFiles(const char* vertexPath, const char* fragmentPath) {
	ShaderProgram* shaderProgram = new ShaderProgram();
	shaderProgram->vertexSource = strdup(this->LoadFromFile(vertexPath).c_str());
	shaderProgram->fragmentSource = strdup(this->LoadFromFile(fragmentPath).c_str());
	return shaderProgram;
}

ShaderLoader* ShaderLoader::GetInstance(void) {
	if (instance == nullptr) {
		instance = new ShaderLoader();
	}
	return instance;
}
