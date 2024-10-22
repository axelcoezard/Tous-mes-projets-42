/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:42:55 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/05 16:47:56 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Vector3.h"

struct Light {
	Vector3 position;
	Vector3 color;

	Light(float x, float y, float z, float r, float g, float b);
	~Light(void);

	void SetPosition(float x, float y, float z);
	void SetColor(float r, float g, float b);
};
