/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShaderLoader.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:43:11 by acoezard          #+#    #+#             */
/*   Updated: 2023/02/26 00:28:06 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iterator>
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>

#include "ShaderProgram.h"

struct ShaderLoader {
private:
	static ShaderLoader* instance;

	std::string LoadFromFile(const char* shaderPath);

public:
	ShaderLoader(void);
	~ShaderLoader(void);

	ShaderLoader(ShaderLoader&) = delete;
    void operator=(const ShaderLoader&) = delete;

	ShaderProgram* LoadFromFiles(const char* vertexShaderPath, const char* fragmentShaderPath);

	static ShaderLoader* GetInstance(void);
};
