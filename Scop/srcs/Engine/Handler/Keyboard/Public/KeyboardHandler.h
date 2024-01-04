/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyboardHandler.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:00:01 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/07 12:56:58 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stdlib.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define KEYBOARD_KEY_COUNT 1024

struct KeyboardHandler {
private:
	static KeyboardHandler* instance;
	int keys[KEYBOARD_KEY_COUNT];

public:
	KeyboardHandler(void);
	~KeyboardHandler(void);

	KeyboardHandler(KeyboardHandler&) = delete;
    void operator=(const KeyboardHandler&) = delete;

	void UpdateKey(int key, int action);
	void PressKey(int key);
	void ReleaseKey(int key);

	bool IsKeyPressed(int key) const;

	static KeyboardHandler* GetInstance(void);
};
