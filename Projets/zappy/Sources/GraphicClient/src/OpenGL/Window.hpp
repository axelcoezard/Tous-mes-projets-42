/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:36:25 by acoezard          #+#    #+#             */
/*   Updated: 2024/05/07 12:13:12 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Image.hpp"

#define MIN_FONT_SIZE 8
#define MAX_FONT_SIZE 200

#define MAX_KEYS 8
#define MAX_MOUSE 8

class Window
{
private:
	int m_Width;
	int m_Height;
	std::string m_Title;

	bool shouldClose = false;
	uint32_t m_keys[MAX_KEYS];
	uint32_t m_mouse[MAX_MOUSE];

	std::map<int, uint32_t> m_keyMap = {
		{SDLK_a, 0},
		{SDLK_d, 1},
		{SDLK_q, 0},
		{SDLK_s, 2},
		{SDLK_w, 3},
		{SDLK_z, 3},
		{SDLK_UP, 3},
		{SDLK_DOWN, 2},
		{SDLK_RIGHT, 1},
		{SDLK_LEFT, 0},
	};

	std::map<int, uint32_t> m_mouseMap = {
		{SDL_BUTTON_LEFT, 0},
		{SDL_BUTTON_RIGHT, 1},
		{SDL_BUTTON_MIDDLE, 2},
	};

public:
	SDL_Renderer* m_renderer;
	SDL_Window* m_window;

	TTF_Font** m_fonts;
private:

	std::map<std::string, Image*> m_Images;

public:
	Window(int width, int height, std::string title);
	~Window();

	void Clear();
	void Close();

	void ClearInputs()
	{
		shouldClose = false;
		for (uint32_t i = 0; i < MAX_KEYS; i++)
			m_keys[i] = SDL_KEYUP;
		for (uint32_t i = 0; i < MAX_MOUSE; i++)
			m_mouse[i] = 0;
	}

	void Render();

	bool ShouldClose()
	{
		return shouldClose;
	}

	bool IsKeyDown(uint32_t key)
	{
		return m_keyMap.find(key) != m_keyMap.end() && m_keys[m_keyMap[key]] == SDL_KEYDOWN;
	}

	bool IsKeyUp(uint32_t key)
	{
		return m_keyMap.find(key) != m_keyMap.end() && m_keys[m_keyMap[key]] == SDL_KEYUP;
	}

	bool IsMouseDown(uint32_t button)
	{
		return m_mouseMap.find(button) != m_mouseMap.end() && m_mouse[m_mouseMap[button]] == SDL_MOUSEBUTTONDOWN;
	}

	bool IsMouseUp(uint32_t button)
	{
		return m_mouseMap.find(button) != m_mouseMap.end() && m_mouse[m_mouseMap[button]] == SDL_MOUSEBUTTONUP;
	}

	void SetShouldClose(bool value)
	{
		shouldClose = value;
	}

	void SetKey(uint32_t key, uint32_t state)
	{
		if (m_keyMap.find(key) != m_keyMap.end())
			m_keys[m_keyMap[key]] = state;
	}

	void SetMouse(uint32_t button, uint32_t state)
	{
		if (m_mouseMap.find(button) != m_mouseMap.end())
			m_mouse[m_mouseMap[button]] = state;
	}

	std::pair<int, int> GetMousePosition();
	bool IsMouseCaptured();

	void DrawImage(int32_t x, int32_t y, int32_t width, int32_t height, std::string path);
	void DrawLine(int32_t fromX, int32_t fromY, int32_t toX, int32_t toY, int32_t color);
	int WriteText(int32_t x, int32_t y,  const std::string& text, int32_t color, int32_t size);
};
