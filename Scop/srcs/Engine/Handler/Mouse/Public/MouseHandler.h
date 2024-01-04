/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MouseHandler.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:00:01 by acoezard          #+#    #+#             */
/*   Updated: 2023/02/26 12:10:39 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stdlib.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define MOUSE_BUTTON_COUNT 1024

struct MouseHandler {
private:
	static MouseHandler* instance;

	bool buttons[MOUSE_BUTTON_COUNT];

public:
	float x, y;

	float scroll;

	MouseHandler(void);
	~MouseHandler(void);

	MouseHandler(MouseHandler&) = delete;
    void operator=(const MouseHandler&) = delete;

	void UpdateButton(int button, int action);
	void UpdatePosition(float xpos, float ypos);
	void UpdateScroll(float ypos);
	bool IsButtonPressed(int button) const;

	static MouseHandler* GetInstance(void);
};
