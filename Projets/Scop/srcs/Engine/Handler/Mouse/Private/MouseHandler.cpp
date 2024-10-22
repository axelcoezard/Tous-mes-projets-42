/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MouseHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:02:21 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/07 10:02:13 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MouseHandler.h"

MouseHandler* MouseHandler::instance = nullptr;

MouseHandler::MouseHandler(void) {
	for (unsigned int i = 0; i < MOUSE_BUTTON_COUNT; i++) {
		this->buttons[i] = false;
	}
	this->x = 0;
	this->y = 0;
	this->scroll = 0;
}

MouseHandler::~MouseHandler(void) {}

void MouseHandler::UpdateButton(int button, int action) {
	this->buttons[button] = action == GLFW_PRESS;
}

void MouseHandler::UpdatePosition(float xpos, float ypos) {
	this->x = xpos;
	this->y = ypos;
}

void MouseHandler::UpdateScroll(float ypos) {
	this->scroll = ypos;
}

bool MouseHandler::IsButtonPressed(int button) const {
	return this->buttons[button];
}

MouseHandler* MouseHandler::GetInstance(void) {
	if (instance == nullptr) {
		instance = new MouseHandler();
	}
	return instance;
}
