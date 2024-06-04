/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:50:48 by acoezard          #+#    #+#             */
/*   Updated: 2024/03/26 16:17:31 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

struct Image
{
	int32_t width;
	int32_t height;
	SDL_Surface* surface;
	SDL_Texture* texture;
};
