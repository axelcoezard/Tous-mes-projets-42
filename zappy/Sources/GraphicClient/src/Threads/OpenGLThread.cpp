/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGLThread.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:28:33 by acoezard          #+#    #+#             */
/*   Updated: 2024/06/04 09:55:48 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Thread.hpp"
#include "OpenGL/Window.hpp"
#include "OpenGLThread.hpp"
#include "GlobalContext.hpp"
#include "PanelBuilder.hpp"
#include "Console.hpp"
#include <algorithm>

OpenGLThread::OpenGLThread(GlobalContext* data, int32_t width, int32_t height): Thread(data)
{
	m_Width = width;
	m_Height = height;
}

OpenGLThread::~OpenGLThread()
{
	m_GlobalContext->appRunning = false;
}

void OpenGLThread::Update()
{
	m_Window = new Window(m_Width, m_Height, "Zappy - Graphic Client");

	m_boardWidth = 300;

	m_gameHeight = m_Height;
	m_gameWidth = m_Width - m_boardWidth;

	int32_t xOffset = 0;
	int32_t yOffset = 0;

	m_PanelBuilder = new Panel::PanelBuilder();
	m_PanelBuilder->SetWidth(m_boardWidth);
	m_PanelBuilder->SetHeight(m_Height);
	m_PanelBuilder->SetX(m_Width - m_boardWidth);
	m_PanelBuilder->SetY(0);
	m_PanelBuilder->SetPadding(10, 10, 10, 10);

	while (m_GlobalContext->appRunning)
	{
		m_Window->ClearInputs();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				m_Window->SetShouldClose(true);
			if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
				m_Window->SetKey(event.key.keysym.sym, event.type);
			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
				m_Window->SetMouse(event.button.button, event.type);
		}

		// update sounds
		for (size_t i = 0; i < m_GlobalContext->sounds.size(); i++) {
			if (m_GlobalContext->sounds[i].tickElapsed >= m_GlobalContext->tickRate) {
				m_GlobalContext->sounds.erase(m_GlobalContext->sounds.begin() + i);
			}
		}

		// update team average level
		for (int32_t i = 0; i < m_GlobalContext->teamCount; i++) {
			int32_t averageLevel = AverageTeamLevel(m_GlobalContext->teams[i].name);

			m_GlobalContext->teams[i].averageLevel = averageLevel;

			if (averageLevel > m_GlobalContext->teams[i].maxLevel)
				m_GlobalContext->teams[i].maxLevel = averageLevel;
		}

		// sort teams by average level
		std::sort(m_GlobalContext->teams.begin(), m_GlobalContext->teams.end(), [](const TeamContext& a, const TeamContext& b) {
			return a.maxLevel > b.maxLevel;
		});

		m_Window->Clear();

		if (m_GlobalContext->hasMapSize)
		{
			int cellWidth = 40;
			int cellHeight = 40;
			int cellCountWidth = m_gameWidth / cellWidth; // max number of cell that can fit in the window
			int cellCountHeight = m_gameHeight / cellHeight;

			int cellOffsetX = std::round(xOffset / cellWidth); // offset in cell
			int cellOffsetY = std::round(yOffset / cellHeight);

			if (m_GlobalContext->playerCount == 0 || m_GlobalContext->followedUserId == -1) {
				if (m_Window->IsKeyDown(SDLK_UP))
					yOffset -= cellHeight;
				if (m_Window->IsKeyDown(SDLK_DOWN))
					yOffset += cellHeight;
				if (m_Window->IsKeyDown(SDLK_LEFT))
					xOffset -= cellWidth;
				if (m_Window->IsKeyDown(SDLK_RIGHT))
					xOffset += cellWidth;
			} else {
				PlayerContext player = m_GlobalContext->players[m_GlobalContext->followedUserId];
				xOffset = - player.x * cellWidth + m_gameWidth / 2;
				yOffset = - player.y * cellHeight + m_gameHeight / 2;
			}

			// dessine les ressources
			for (int32_t x = 0; x < m_GlobalContext->width; x++)
			{
				for (int32_t y = 0; y < m_GlobalContext->height; y++)
				{
					if (x + cellOffsetX < 0
						|| x + cellOffsetX >= cellCountWidth
						|| y + cellOffsetY < 0
						|| y + cellOffsetY >= cellCountHeight)
						continue ; // skip if the cell is not visible (out of the window

					Tile tile = m_GlobalContext->map[x + y * m_GlobalContext->width];
					if (tile.dirty == false)
						continue ;

					m_Window->DrawImage(x * cellWidth + xOffset, y * cellHeight + yOffset, cellWidth, cellHeight, "Assets/grass.jpg");

					if (tile.quantity == 0)
						continue ;

					if (tile.type == static_cast<int32_t>(ResourceType::Nourriture))
					{
						m_Window->DrawImage(x * cellWidth + xOffset, y * cellHeight + yOffset, cellWidth, cellHeight, "Assets/farm_1.png");
					}
					else if (tile.type == static_cast<int32_t>(ResourceType::Linemate))
					{
						m_Window->DrawImage(x * cellWidth + xOffset, y * cellHeight + yOffset, cellWidth, cellHeight, "Assets/ore_1.png");
					}
					else if (tile.type == static_cast<int32_t>(ResourceType::Deraumere))
					{
						m_Window->DrawImage(x * cellWidth + xOffset, y * cellHeight + yOffset, cellWidth, cellHeight, "Assets/ore_2.png");
					}
					else if (tile.type == static_cast<int32_t>(ResourceType::Sibur))
					{
						m_Window->DrawImage(x * cellWidth + xOffset, y * cellHeight + yOffset, cellWidth, cellHeight, "Assets/ore_3.png");
					}
					else if (tile.type == static_cast<int32_t>(ResourceType::Mendiane))
					{
						m_Window->DrawImage(x * cellWidth + xOffset, y * cellHeight + yOffset, cellWidth, cellHeight, "Assets/ore_4.png");
					}
					else if (tile.type == static_cast<int32_t>(ResourceType::Phiras))
					{
						m_Window->DrawImage(x * cellWidth + xOffset, y * cellHeight + yOffset, cellWidth, cellHeight, "Assets/ore_5.png");
					}
					else if (tile.type == static_cast<int32_t>(ResourceType::Thystame))
					{
						m_Window->DrawImage(x * cellWidth + xOffset, y * cellHeight + yOffset, cellWidth, cellHeight, "Assets/ore_6.png");
					}
				}
			}

			// dessiner une ligne pour chaque case
			for (int32_t x = 0; x < m_GlobalContext->width / 3; x++)
			{
				m_Window->DrawLine(x * cellWidth * 3 + xOffset, 0, x * cellWidth * 3 + xOffset, m_gameHeight, 0x000000);
			}

			// dessiner une ligne pour chaque case
			for (int32_t y = 0; y < m_GlobalContext->height / 3; y++)
			{
				m_Window->DrawLine(0, y * cellHeight * 3 + yOffset, m_gameWidth, y * cellHeight * 3 + yOffset, 0x000000);
			}

			// dessine les oeufs
			for (int32_t i = 0; i < m_GlobalContext->eggCount; i++)
			{
				EggContext egg = m_GlobalContext->eggs[i];

				if (egg.x + cellOffsetX < 0
					|| egg.x + cellOffsetX >= cellCountWidth
					|| egg.y + cellOffsetY < 0
					|| egg.y + cellOffsetY >= cellCountHeight)
					continue ; // skip if the egg is not visible (out of the window)

				if (egg.hasHatched)
					m_Window->DrawImage(egg.x * cellWidth + xOffset, egg.y * cellHeight + yOffset, cellWidth, cellHeight, "Assets/egg_hatched.png");
				else
					m_Window->DrawImage(egg.x * cellWidth + xOffset, egg.y * cellHeight + yOffset, cellWidth, cellHeight, "Assets/egg.png");
			}

			// dessine les joueurs
			for (int32_t i = 0; i < m_GlobalContext->playerCount; i++)
			{
				PlayerContext player = m_GlobalContext->players[i];

				if (player.x + cellOffsetX < 0
					|| player.x + cellOffsetX >= cellCountWidth
					|| player.y + cellOffsetY < 0
					|| player.y + cellOffsetY >= cellCountHeight)
					continue ; // skip if the player is not visible (out of the window)

				std::string filePath = "Assets/personnage_1_" + std::to_string(player.orientation) + ".png";
				// change skin depending on orientation and team color
				m_Window->DrawImage(player.x * cellWidth  + xOffset, player.y * cellHeight + yOffset, cellWidth, cellHeight, filePath);
			}

			// dessine les sons
			for (size_t i = 0; i < m_GlobalContext->sounds.size(); i++)
			{
				SoundContext& sound = m_GlobalContext->sounds[i];

				if (sound.message.empty())
					continue;

				if (sound.fromX + cellOffsetX < 0
					|| sound.fromX + cellOffsetX >= cellCountWidth
					|| sound.fromY + cellOffsetY < 0
					|| sound.fromY + cellOffsetY >= cellCountHeight)
					continue ; // skip if the sound is not visible (out of the window)

				for (int32_t j = 0; j < m_GlobalContext->playerCount; j++)
				{
					PlayerContext& player = m_GlobalContext->players[j];

					if (player.x + cellOffsetX < 0
						|| player.x + cellOffsetX >= cellCountWidth
						|| player.y + cellOffsetY < 0
						|| player.y + cellOffsetY >= cellCountHeight)
						continue ; // skip if the player is not visible (out of the window

					if (sound.fromId == player.id)
						continue;

					m_Window->DrawLine(sound.fromX * cellWidth  + xOffset + (cellWidth / 2),
									sound.fromY * cellHeight + yOffset + (cellHeight / 2),
									player.x * cellWidth  + xOffset + (cellWidth / 2),
									player.y * cellHeight + yOffset + (cellHeight / 2), 0xff0000);
				}

				sound.tickElapsed++;
			}

			// dessine la selection du curseur
			auto [xpos, ypos] = m_Window->GetMousePosition();
			int cell_x = std::max(0.0, std::floor(xpos - xOffset) / cellWidth);
			int cell_y = std::max(0.0, std::floor(ypos - yOffset) / cellHeight);
			int rect_x = static_cast<int>(xpos / cellWidth * cellWidth);
			int rect_y = static_cast<int>(ypos / cellHeight * cellHeight);

			m_PanelBuilder->AddTitleComponent("Zappy", 0x27ae60);
			m_PanelBuilder->AddSeparatorComponent(0x000000);

			if (m_Window->IsMouseCaptured()
				&& xpos < m_gameWidth // in the game, not in the panel
				&& xpos - xOffset >= 0 // if the mouse is in the map
				&& xpos - xOffset < m_GlobalContext->width * cellWidth // if the mouse is in the map
				&& ypos - yOffset >= 0 // if the mouse is in the map
				&& ypos - yOffset < m_GlobalContext->height * cellHeight) // if the mouse is in the map
			{
				SDL_Rect rect = {rect_x, rect_y, cellWidth, cellHeight};
				SDL_SetRenderDrawColor(m_Window->m_renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(m_Window->m_renderer, &rect);

				int32_t index = cell_x + cell_y * m_GlobalContext->width;

				if (index > 0 && index < m_GlobalContext->width * m_GlobalContext->height) {
					Tile tile = m_GlobalContext->map[index];

					m_PanelBuilder->AddTextComponent("Selected tile:", 0x34495e);
					m_PanelBuilder->AddTextComponent("- Type: " + GetTileTypeName(tile.type), 0x34495e);
					m_PanelBuilder->AddTextComponent("- Coords: " + std::to_string(cell_x) + ", " + std::to_string(cell_y), 0x34495e);
					if (tile.quantity > 0) {
						m_PanelBuilder->AddTextComponent("- Quantity: " + std::to_string(tile.quantity), 0x34495e);
					}
				} else {
					m_PanelBuilder->AddTextComponent("Selected tile: None", 0x34495e);
				}
			} else {
				m_PanelBuilder->AddTextComponent("Selected tile: None", 0x34495e);
			}

			m_PanelBuilder->AddSeparatorComponent(0x000000);

			m_PanelBuilder->AddTextComponent("Players:", 0x34495e);
			m_PanelBuilder->AddTextComponent("- Count: " + std::to_string(m_GlobalContext->playerCount), 0x34495e);

			m_PanelBuilder->AddSeparatorComponent(0x000000);

			m_PanelBuilder->AddTextComponent("Teams Ranking:", 0x34495e);
			for (int32_t i = 0; i < m_GlobalContext->teamCount; i++) {
				auto team = m_GlobalContext->teams[i];
				m_PanelBuilder->AddTextComponent(
					std::to_string(i + 1) + " - " + team.name + " (lvl: ~" + std::to_string(team.maxLevel) + ")", 0x34495e);
			}

			m_PanelBuilder->AddSeparatorComponent(0x000000);

			if (m_GlobalContext->playerCount > 0) {
				m_PanelBuilder->AddTextComponent("Follow player:", 0x34495e);

				m_PanelBuilder->AddButtonGridComponent(m_GlobalContext->playerCount, 0x27ae60, 0x27ae60, [&](int index) {
					int i = 0;
					for (PlayerContext& p : m_GlobalContext->players)
					{
						if (i != index)
							p.selected = false;
						i++;
					}
					m_GlobalContext->players[index].selected = !m_GlobalContext->players[index].selected;
					m_GlobalContext->followedUserId = m_GlobalContext->players[index].selected ? index : -1;
				}, [&](int index) {
					return m_GlobalContext->players[index].selected;
				});

				if (m_GlobalContext->followedUserId != -1) {
					m_PanelBuilder->AddSeparatorComponent(0x000000);

					m_PanelBuilder->AddTextComponent("Following: " +  std::to_string(m_GlobalContext->players[m_GlobalContext->followedUserId].id), 0x34495e);

					m_PanelBuilder->AddSeparatorComponent(0x000000);

					m_PanelBuilder->AddTextComponent("Player info:", 0x34495e);
					m_PanelBuilder->AddTextComponent("- Level: " + std::to_string(m_GlobalContext->players[m_GlobalContext->followedUserId].level), 0x34495e);
					m_PanelBuilder->AddTextComponent("- Orientation: " + GetOrientationName(m_GlobalContext->players[m_GlobalContext->followedUserId].orientation), 0x34495e);
					m_PanelBuilder->AddTextComponent("- Team: " + m_GlobalContext->players[m_GlobalContext->followedUserId].team, 0x34495e);
				}
			}

			m_PanelBuilder->Render(m_Window);
		}

		if (m_GlobalContext->hasGameOver)
		{
			// un carre noir translucide
			SDL_Rect rect = {0, 0, static_cast<int>(m_Width - m_boardWidth), static_cast<int>(m_Height)};
			SDL_SetRenderDrawBlendMode(m_Window->m_renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(m_Window->m_renderer, 0, 0, 0, 128);
			SDL_RenderFillRect(m_Window->m_renderer, &rect);

			// ecrire "Game over a l'ecran"
			m_Window->WriteText(60, m_Height / 2 - 100, "Game Over", 0xecf0f1, 125);

			if (m_GlobalContext->hasWinner) {
				m_Window->WriteText(150, m_Height / 2 + 35, "The team " + m_GlobalContext->winner + " has won the game !", 0x2ecc71, 30);
			} else {
				m_Window->WriteText(250, m_Height / 2 + 35, "Everybody is dead...", 0x2ecc71, 30);
			}
		}

		m_Window->Render();

		if (m_Window->ShouldClose())
			m_GlobalContext->appRunning = false;

		if (m_GlobalContext->hasTickRate)
			std::this_thread::sleep_for(std::chrono::milliseconds(1000 / m_GlobalContext->tickRate));
	}

	delete m_Window;
	exit(EXIT_SUCCESS);
}

int OpenGLThread::AverageTeamLevel(std::string teamName)
{
	int averageLevel = 0;
	int playerCount = 0;
	for (int32_t i = 0; i < m_GlobalContext->playerCount; i++)
	{
		PlayerContext player = m_GlobalContext->players[i];
		if (player.team == teamName) {
			averageLevel += player.level;
			playerCount++;
		}
	}
	if (playerCount == 0)
		return 0;
	return static_cast<int>((float) averageLevel / (float) playerCount);
}

std::string OpenGLThread::GetTileTypeName(int16_t type)
{
	if (type == static_cast<int32_t>(ResourceType::Nourriture))
	{
		return "Nourriture";
	}
	else if (type == static_cast<int32_t>(ResourceType::Linemate))
	{
		return "Linemate";
	}
	else if (type == static_cast<int32_t>(ResourceType::Deraumere))
	{
		return "Deraumere";
	}
	else if (type == static_cast<int32_t>(ResourceType::Sibur))
	{
		return "Sibur";
	}
	else if (type == static_cast<int32_t>(ResourceType::Mendiane))
	{
		return "Mendiane";
	}
	else if (type == static_cast<int32_t>(ResourceType::Phiras))
	{
		return "Phiras";
	}
	else if (type == static_cast<int32_t>(ResourceType::Thystame))
	{
		return "Thystame";
	}
	return "Vide";
}


std::string OpenGLThread::GetOrientationName(int16_t orientation)
{
	if (orientation == 4)
	{
		return "Nord";
	}
	else if (orientation == 1)
	{
		return "Est";
	}
	else if (orientation == 2)
	{
		return "Sud";
	}
	else if (orientation == 3)
	{
		return "Ouest";
	}
	return "Inconnu";
}

std::thread* OpenGLThread::GetThread()
{
	return new std::thread(&OpenGLThread::Update, this);
}
