/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:46:03 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/05 16:48:03 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Light.h"

Light::Light(float x, float y, float z, float r, float g, float b) {
	this->position = Vector3(x, y, z);
	this->color = Vector3(r, g, b);
}

Light::~Light(void) {}

void Light::SetPosition(float x, float y, float z) {
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
}

void Light::SetColor(float r, float g, float b) {
	this->position.x = r;
	this->position.y = g;
	this->position.z = b;
}
