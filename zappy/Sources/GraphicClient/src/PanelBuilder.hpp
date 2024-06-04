/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PanelBuilder.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:03:00 by acoezard          #+#    #+#             */
/*   Updated: 2024/05/07 11:45:15 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "OpenGL/Window.hpp"
#include <functional>

namespace Panel
{
	class IDrawablePanelComponent
	{
	public:
		virtual int Render(Window* window, int x, int y, int maxWidth, int maxHeight) = 0;
		virtual ~IDrawablePanelComponent() {}
	};

	class PanelSeparator: public IDrawablePanelComponent
	{
	private:
		int m_color;

	public:
		PanelSeparator(int color = 0x000000): m_color(color) {}

		int Render(Window* window, int x, int y, int maxWidth, int maxHeight) override
		{
			(void) maxHeight;

			uint8_t r = static_cast<uint8_t>(((m_color >> 16) & 0xFF) * 255);
			uint8_t g = static_cast<uint8_t>(((m_color >> 8) & 0xFF) * 255);
			uint8_t b = static_cast<uint8_t>((m_color & 0xFF) * 255);

			SDL_Rect rect = {x, y, static_cast<int>(maxWidth), 3}; // Position et taille du carré
			SDL_SetRenderDrawColor(window->m_renderer, r, g, b, 255); // Couleur blanche pour les bordures
			SDL_RenderDrawRect(window->m_renderer, &rect);

			return 3;
		}
	};

	class PanelTitle: public IDrawablePanelComponent
	{
	private:
		std::string m_title;
		int m_color;

	public:
		PanelTitle(std::string title, int color): m_title(title), m_color(color) {}

		int Render(Window* window, int x, int y, int maxWidth, int maxHeight) override
		{
			(void) maxWidth;
			(void) maxHeight;
			return window->WriteText(x, y, m_title.c_str(), m_color,  40) + 10;
		}
	};

	class PanelButtonGrid: public IDrawablePanelComponent
	{
	private:
		int m_size;
		int m_color;
		int m_hoverColor;
		std::function<void(int)> m_callback;
		std::function<bool(int)> m_isSelected;

		int m_buttonWidth = 40;
		int m_buttonHeight = 30;

	public:
		PanelButtonGrid(int size, int color, int hoverColor, std::function<void(int)> callback, std::function<bool(int)> isSelected)
			: m_size(size), m_color(color), m_hoverColor(hoverColor), m_callback(callback), m_isSelected(isSelected) {}

		int Render(Window* window, int x, int y, int maxWidth, int maxHeight) override
		{
			(void) maxHeight;

			uint8_t r1 = static_cast<uint8_t>(((m_color >> 16) & 0xFF) * 255);
			uint8_t g1 = static_cast<uint8_t>(((m_color >> 8) & 0xFF) * 255);
			uint8_t b1 = static_cast<uint8_t>((m_color & 0xFF) * 255);

			uint8_t r2 = static_cast<uint8_t>(((m_hoverColor >> 16) & 0xFF) * 255);
			uint8_t g2 = static_cast<uint8_t>(((m_hoverColor >> 8) & 0xFF) * 255);
			uint8_t b2 = static_cast<uint8_t>((m_hoverColor & 0xFF) * 255);

			for (int i = 0; i < m_size; i++) //columns
			{
				int buttonX = x + (m_buttonWidth * i) % maxWidth;
				int buttonY = y + (m_buttonWidth * i) / maxWidth * m_buttonHeight;

				bool isSelected = m_isSelected(i);
				auto [mouseX, mouseY] = window->GetMousePosition();

				SDL_Rect rect = {buttonX, buttonY, m_buttonWidth, m_buttonHeight}; // Position et taille du carré

				if (isSelected) {
					SDL_SetRenderDrawColor(window->m_renderer, r2, g2, b2, 255);
					SDL_RenderFillRect(window->m_renderer, &rect);
				} else {
					SDL_SetRenderDrawColor(window->m_renderer, r1, g1, b1, 255); // Couleur blanche pour les bordures
					SDL_RenderDrawRect(window->m_renderer, &rect);
				}

				if (window->IsMouseDown(SDL_BUTTON_LEFT)
					&& !(mouseX < buttonX || mouseX > buttonX + m_buttonWidth || mouseY < buttonY || mouseY > buttonY + m_buttonHeight))
				{
					SDL_SetRenderDrawColor(window->m_renderer, r2, g2, b2, 255);
					SDL_RenderFillRect(window->m_renderer, &rect);

					m_callback(i);
				}

				if (isSelected) {
					window->WriteText(buttonX, buttonY, std::to_string(i).c_str(), 0xffffff,  30);
				} else {
					window->WriteText(buttonX, buttonY, std::to_string(i).c_str(), 0x000000,  30);
				}
			}

			float buttonsPerRow = (float) maxWidth / (float) m_buttonWidth;
			float rows = std::max(std::ceil((float) m_size / buttonsPerRow), 1.0f);
			return std::ceil(m_buttonHeight * rows);
		}
	};

	class PanelText: public IDrawablePanelComponent
	{
	private:
		std::string m_text;
		int m_color;

	public:
		PanelText(std::string text, int color): m_text(text), m_color(color) {}

		int Render(Window* window, int x, int y, int maxWidth, int maxHeight) override
		{
			(void) maxWidth;
			(void) maxHeight;
			return window->WriteText(x, y, m_text.c_str(), m_color,  20);
		}
	};

	class PanelBuilder
	{
	private:
		int32_t m_width;
		int32_t m_height;
		int32_t m_x;
		int32_t m_y;

		int32_t m_paddingLeft, m_paddingRight, m_paddingTop, m_paddingBottom;

		std::vector<IDrawablePanelComponent*> m_components;

	public:
		void SetWidth(int32_t width) { m_width = width; }

		void SetHeight(int32_t height) { m_height = height; }

		void SetX(int32_t x) { m_x = x; }

		void SetY(int32_t y) { m_y = y; }

		void SetPadding(int32_t paddingLeft, int32_t paddingRight, int32_t paddingTop, int32_t paddingBottom)
		{
			m_paddingLeft = paddingLeft;
			m_paddingRight = paddingRight;
			m_paddingTop = paddingTop;
			m_paddingBottom = paddingBottom;
		}

		void AddComponent(IDrawablePanelComponent* component)
		{
			m_components.push_back(component);
		}

		void AddTitleComponent(std::string title, int color)
		{
			m_components.push_back(new PanelTitle(title, color));
		}

		void AddTextComponent(std::string text, int color)
		{
			m_components.push_back(new PanelText(text, color));
		}

		void AddSeparatorComponent(int color)
		{
			m_components.push_back(new PanelSeparator(color));
		}

		void AddButtonGridComponent(int size, int color, int hoverColor, std::function<void(int)> callback, std::function<bool(int)> isSelected)
		{
			m_components.push_back(new PanelButtonGrid(size, color, hoverColor, callback, isSelected));
		}

		void Render(Window* window)
		{
			// Render white rect
			SDL_Rect background = {static_cast<int>(m_x), static_cast<int>(m_y), static_cast<int>(m_width), static_cast<int>(m_height)};
			SDL_SetRenderDrawColor(window->m_renderer, 240, 240, 210, 255);
			SDL_RenderFillRect(window->m_renderer, &background);

			// Render left border
			SDL_Rect border = {static_cast<int>(m_x), static_cast<int>(m_y), 3, static_cast<int>(m_height)}; // Position et taille du carré
			SDL_SetRenderDrawColor(window->m_renderer, 0, 0, 0, 255); // Couleur blanche pour les bordures
			SDL_RenderDrawRect(window->m_renderer, &border);

			int totalPaddingTop = m_paddingTop;
			for (auto component: m_components)
			{
				int lineHeight = component->Render(
					window,
					m_x + m_paddingLeft,
					m_y + totalPaddingTop,
					m_width - m_paddingRight - m_paddingLeft,
					m_height - m_paddingBottom - m_paddingTop);

				totalPaddingTop += lineHeight + 10;

				delete component;
			}

			m_components.clear();
		}
	};
};
