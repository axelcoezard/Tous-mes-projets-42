#pragma once

#include <ResourceType.hpp>
#include <Tile.hpp>

class Map
{
	private:
		int32_t m_Width;
		int32_t m_Height;
		Tile* m_Tiles;

	public:
		Map(int32_t width, int32_t height);
		~Map();

		void Initialize();
		void Update();

		Tile& Get(int32_t index);
		Tile& Get(int32_t x, int32_t y);
		Tile& operator[](int32_t index);
		std::string SerializeTile(int32_t x, int32_t y);

		Tile& PickResource(int32_t x, int32_t y, std::string resourceType);
		void SetResource(int32_t x, int32_t y, int32_t resourceType, int32_t quantity);
		bool IncreaseResource(int32_t x, int32_t y, int32_t resourceId, int32_t quantity);
		bool DecreaseResource(int32_t x, int32_t y, int32_t resourceId, int32_t quantity);
		bool IsResourceExhausted(int32_t x, int32_t y, std::string resourceType);
		int32_t GetResourceTypeId(std::string type);

		int32_t GetWidth() const;
		int32_t GetHeight() const;

		bool RessourcePercent(int32_t p, int32_t i);
		int32_t GetRessourceCount(int32_t i);
		void ResetMap();
};
