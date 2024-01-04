 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModelLoader.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:46:28 by acoezard          #+#    #+#             */
/*   Updated: 2023/02/26 12:46:28 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Model.h"
#include "ShaderLoader.h"
#include "ShaderProgram.h"

struct ModelLoader {
private:
	const char* path;
	const char* vsPath = nullptr;
	const char* fsPath = nullptr;
	const char* texturePath = nullptr;

protected:
	ModelLoader(const char* path);

public:
	ModelLoader(ModelLoader&) = delete;
	void operator=(const ModelLoader&) = delete;

	static ModelLoader* WithFile(const char* path);
	ModelLoader* WithVertexShader(const char* vsPath);
	ModelLoader* WithFragmentShader(const char* fsPath);
	ModelLoader* WithTexture(const char* texturePath);

	Model* Load(void);
};
