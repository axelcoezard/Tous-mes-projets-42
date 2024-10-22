/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:36:36 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/05 02:04:50 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Texture.h"

void Texture::Bind(void) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->id);
}
