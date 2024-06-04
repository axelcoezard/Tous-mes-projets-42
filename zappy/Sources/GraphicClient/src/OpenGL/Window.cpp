/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:38:32 by acoezard          #+#    #+#             */
/*   Updated: 2024/05/13 10:25:55 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Window.hpp"
#include <Console.hpp>

#include <SDL.h>
#include <SDL2_rotozoom.h>

Window::Window(int width, int height, std::string title)
{
	m_Width = width;
	m_Height = height;
	m_Title = title;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	m_window = SDL_CreateWindow(
		m_Title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_Width,
		m_Height,
		SDL_WINDOW_OPENGL
	);

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	m_fonts = (TTF_Font**) malloc(sizeof(TTF_Font*) * (MAX_FONT_SIZE - MIN_FONT_SIZE + 1));
	for (int32_t i = MIN_FONT_SIZE; i < MAX_FONT_SIZE; i++)
		m_fonts[i] = TTF_OpenFont("./Assets/fonts/arial.ttf", i);

	ClearInputs();
}

Window::~Window()
{
	for (auto& [key, value] : m_Images)
	{
		SDL_FreeSurface(value->surface);
		SDL_DestroyTexture(value->texture);
		delete value;
	}
	IMG_Quit();

	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

void Window::Clear()
{
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_renderer);
}

void Window::Render()
{
	SDL_RenderPresent(m_renderer);
}

std::pair<int, int> Window::GetMousePosition()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	return {x, y};
}

bool Window::IsMouseCaptured()
{
	return SDL_GetWindowFlags(m_window) & SDL_WINDOW_MOUSE_CAPTURE;
}

void Window::DrawLine(int32_t fromX, int32_t fromY, int32_t toX, int32_t toY, int32_t color)
{
	float r = static_cast<float>((color >> 16) & 0xFF);
	float g = static_cast<float>((color >> 8) & 0xFF);
	float b = static_cast<float>((color >> 0) & 0xFF);

	SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), 255);
	SDL_RenderDrawLine(m_renderer, fromX, fromY, toX, toY);
}

void Window::DrawImage(int32_t x, int32_t y, int32_t width, int32_t height, std::string path)
{
	std::string fullPath = path + "-" + std::to_string(width) + "x" + std::to_string(height);

	if (m_Images.find(fullPath) == m_Images.end())
	{
		SDL_Surface* surface = IMG_Load(path.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

		SDL_Surface* resizedSurface = rotozoomSurfaceXY(surface, 0,
			static_cast<double>(width / surface->w),
			static_cast<double>(height / surface->h), 0);

		SDL_FreeSurface(surface);

		m_Images[fullPath] = new Image();
		m_Images[fullPath]->width = width;
		m_Images[fullPath]->height = height;
		m_Images[fullPath]->surface = resizedSurface;
		m_Images[fullPath]->texture = texture;

		Console::Log("Loaded image " + fullPath);
	}

	Image* image = m_Images[fullPath];

	SDL_Rect newRect = {
		static_cast<int>(x),
		static_cast<int>(y),
		static_cast<int>(width),
		static_cast<int>(height)
	};

	SDL_RenderCopy(m_renderer, image->texture, NULL, &newRect);
}

int Window::WriteText(int32_t x, int32_t y, const std::string& text, int32_t color, int32_t size)
{
	if (size < MIN_FONT_SIZE)
		size = MIN_FONT_SIZE;
	if (size > MAX_FONT_SIZE)
		size = MAX_FONT_SIZE - 1;

	float r = static_cast<float>((color >> 16) & 0xFF);
	float g = static_cast<float>((color >> 8) & 0xFF);
	float b = static_cast<float>((color >> 0) & 0xFF);

	SDL_Color rgbaColor = { static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), 255 };

	SDL_Surface* surface = TTF_RenderText_Blended(m_fonts[size], text.c_str(), rgbaColor);
	if (surface == nullptr)
		return 0;

	SDL_Rect rect = { static_cast<int>(x), static_cast<int>(y), surface->w, surface->h };

	SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
	SDL_FreeSurface(surface);

	if (texture == nullptr)
		return 0;

	SDL_RenderCopy(m_renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);

	return static_cast<int>(size);
}

