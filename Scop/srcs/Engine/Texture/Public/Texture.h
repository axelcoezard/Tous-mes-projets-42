/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:28:36 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/05 01:07:08 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

struct Texture {
	unsigned int id;

	int height, width;
	int channels;

	void Bind(void);
};
