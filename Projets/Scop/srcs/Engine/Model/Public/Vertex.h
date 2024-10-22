/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vertex.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:52:43 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/05 01:22:40 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Vector3.h"
#include "Vector2.h"

struct Vertex {
	Vector3 position;
	Vector2	texture;
	Vector3	normal;
};
