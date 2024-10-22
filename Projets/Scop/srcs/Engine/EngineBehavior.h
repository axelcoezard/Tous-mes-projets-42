/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EngineBehavior.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:54:55 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/02 09:23:26 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

struct EngineBehavior {
	virtual ~EngineBehavior(void) {}

	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
};
