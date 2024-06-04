/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLThread.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:14:58 by acoezard          #+#    #+#             */
/*   Updated: 2024/06/03 21:30:37 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "OpenGL/Window.hpp"
#include "Thread.hpp"
#include "PanelBuilder.hpp"

struct GlobalContext;

class OpenGLThread : public Thread
{
private:
	int32_t m_Width;
	int32_t m_Height;

	int32_t m_boardWidth = 300;

	int32_t m_gameHeight;
	int32_t m_gameWidth;

	Window* m_Window;
	Panel::PanelBuilder* m_PanelBuilder;
public:
	OpenGLThread(GlobalContext* data, int32_t width, int32_t height);
	~OpenGLThread();

	void Update() override;
	std::string GetTileTypeName(int16_t type);
	std::string GetOrientationName(int16_t orientation);
	int AverageTeamLevel(std::string teamName);

	std::thread* GetThread() override;
};
