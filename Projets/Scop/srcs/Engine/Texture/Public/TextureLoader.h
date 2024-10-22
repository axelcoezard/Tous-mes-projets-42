/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TextureLoader.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:29:14 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/04 18:37:53 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Texture.h"

struct TextureLoader {
private:
	const char* path = nullptr;

protected:
	TextureLoader(const char* path);

public:
	TextureLoader(TextureLoader&) = delete;
	void operator=(const TextureLoader&) = delete;

	static Texture* FromPath(const char* path);
};
