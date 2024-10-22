/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyboardHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:02:21 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/07 12:57:32 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KeyboardHandler.h"

KeyboardHandler* KeyboardHandler::instance = nullptr;

KeyboardHandler::KeyboardHandler(void) {
	for (int i = 0; i < KEYBOARD_KEY_COUNT; i++) {
		this->keys[i] = GLFW_RELEASE;
	}
}

KeyboardHandler::~KeyboardHandler(void) {}

void KeyboardHandler::UpdateKey(int key, int action) {
	this->keys[key] = action;
}

void KeyboardHandler::PressKey(int key) {
	this->keys[key] = GLFW_PRESS;
}

void KeyboardHandler::ReleaseKey(int key) {
	this->keys[key] = GLFW_RELEASE;
}

bool KeyboardHandler::IsKeyPressed(int key) const {
	return this->keys[key] == GLFW_PRESS || this->keys[key] == GLFW_REPEAT;
}

KeyboardHandler* KeyboardHandler::GetInstance(void) {
	if (instance == nullptr) {
		instance = new KeyboardHandler();
	}
	return instance;
}
