/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureLoader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:37:39 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/05 12:32:40 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TextureLoader.h"
#include "Texture.h"

#include <iostream>

Texture* TextureLoader::FromPath(const char* path) {
	Texture* texture = new Texture();

	stbi_set_flip_vertically_on_load(true);
	stbi_uc* data = stbi_load(path, &texture->width, &texture->height, &texture->channels, 0);

	if (!data) {
		std::cerr << "Failed to load texture: " << path << std::endl;
	}

	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);

	unsigned int format = texture->channels > 3 ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, texture->width, texture->height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}
