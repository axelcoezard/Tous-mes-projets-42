#include "Map.hpp"
#include "PerlinNoise.hpp"

#define MIN_PERCENT 28
#define MAX_PERCENT 72

Map::Map(int32_t width, int32_t height): m_Width(width), m_Height(height)
{
	m_Tiles = new Tile[width * height];
	std::memset((void *)m_Tiles, 0, width * height * sizeof(Tile));
}

Map::~Map()
{
	delete[] m_Tiles;
}

void Map::Initialize()
{
	ResetMap();
	for (int32_t i = 0; i < RESSOURCES_COUNT; i++)
	{
		PerlinNoise Perlin(m_Width, m_Height);
		float *noise = Perlin.Generate();
		for (int32_t y = 0; y < m_Height; y++)
		{
			for (int32_t x = 0; x < m_Width; x++)
			{
				float n = noise[x + y * m_Width];
				int32_t p = (int)(n * 100);
				int32_t r = (rand() % 50) + 100;
				if (RessourcePercent(p, i) && (Get(x, y).quantity == 0 || Get(x, y).type == 0))
					SetResource(x, y, i, r);
			}
		}
		delete[] noise;
	}
}

bool Map::RessourcePercent(int32_t p, int32_t i)
{
	if (i == 0)
		return (p < 48 || p > 52);
	else if (i == 1)
		return (p < MIN_PERCENT || p > MAX_PERCENT);
	else if (i == 2)
		return (p < MIN_PERCENT || p > MAX_PERCENT);
	else if (i == 3)
		return (p < MIN_PERCENT || p > MAX_PERCENT);
	else if (i == 4)
		return (p < MIN_PERCENT || p > MAX_PERCENT);
	else if (i == 5)
		return (p < MIN_PERCENT || p > MAX_PERCENT);
	else if (i == 6)
		return (p < MIN_PERCENT || p > MAX_PERCENT);
	return false;
}

int32_t Map::GetRessourceCount(int32_t i)
{
	int32_t count = 0;
	for (int32_t y = 0; y < m_Height; y++)
	{
		for (int32_t x = 0; x < m_Width; x++)
		{
			if (Get(x, y).type == i)
				count++;
		}
	}
	return count;
}

void Map::ResetMap()
{
	for (int32_t y = 0; y < m_Height; y++)
	{
		for (int32_t x = 0; x < m_Width; x++)
		{
			for (int32_t i = 0; i < RESSOURCES_COUNT; i++)
			{
				SetResource(x, y, i, 0);
			}
		}
	}
}

void Map::Update()
{

}

Tile& Map::Get(int32_t index)
{
	int32_t size = m_Width * m_Height;
	if (index < 0)
		index = (index + size) % size;
	else if (index >= size)
		index = index % size;
	return m_Tiles[index];
}

Tile& Map::Get(int32_t x, int32_t y)
{
	if (x < 0)
		x = (x + m_Width) % m_Width;
	else if (x >= m_Width)
		x = x % m_Width;
	if (y < 0)
		y = (y + m_Height) % m_Height;
	else if (y >= m_Height)
		y = y % m_Height;
	return m_Tiles[x + y * m_Width];
}

Tile& Map::operator[](int32_t index)
{
	return Get(index);
}

std::string Map::SerializeTile(int32_t x, int32_t y)
{
	Tile& tile = Get(x, y);

	std::stringstream ss;
	ss << std::to_string(x) << " " << std::to_string(y) << " ";
	for (int i = 0; i < RESSOURCES_COUNT; i++)
	{
		if (i == tile.type)	ss << std::to_string(tile.quantity);
		else			ss << "0";
		ss << " ";
	}
	return ss.str();
}

Tile& Map::PickResource(int32_t x, int32_t y, std::string resourceType)
{
	if (x >= m_Width || y >= m_Height)
		throw std::out_of_range("Map::PickResource: index out of range");

	int32_t index = x + y * m_Width;
	if (GetResourceTypeId(resourceType) == m_Tiles[index].type && m_Tiles[index].quantity > 0)
	{
		m_Tiles[index].quantity--;
		return m_Tiles[index];
	}
	throw std::out_of_range("Map::PickResource: no resource to pick");
}

void Map::SetResource(int32_t x, int32_t y, int32_t resourceType, int32_t quantity)
{
	if (x >= m_Width || y >= m_Height)
		throw std::out_of_range("Map::SetResource: index out of range");

	int32_t index = x + y * m_Width;
	m_Tiles[index].x = x;
	m_Tiles[index].y = y;
	m_Tiles[index].type = resourceType;
	m_Tiles[index].quantity = quantity;
}


bool Map::IncreaseResource(int32_t x, int32_t y, int32_t resourceId, int32_t quantity)
{
	if (x >= m_Width || y >= m_Height)
		throw std::out_of_range("Map::IncreaseResource: index out of range");

	int32_t index = x + y * m_Width;

	if (m_Tiles[index].type != resourceId)
		return false;

	m_Tiles[index].quantity += quantity;
	return true;
}

bool Map::DecreaseResource(int32_t x, int32_t y, int32_t resourceId, int32_t quantity)
{
	if (x >= m_Width || y >= m_Height)
		throw std::out_of_range("Map::DecreaseResource: index out of range");

	int32_t index = x + y * m_Width;

	if (m_Tiles[index].type != resourceId)
		return false;

	m_Tiles[index].quantity += quantity;

	if (m_Tiles[index].quantity < 0)
		m_Tiles[index].quantity = 0;

	return true;
}

bool Map::IsResourceExhausted(int32_t x, int32_t y, std::string resourceType)
{
	if (x >= m_Width || y >= m_Height)
		throw std::out_of_range("Map::IsResourceExhausted: index out of range");

	int32_t index = x + y * m_Width;
	return GetResourceTypeId(resourceType) == m_Tiles[index].type && m_Tiles[index].quantity < 0;
}

int32_t Map::GetWidth() const
{
	return m_Width;
}

int32_t Map::GetHeight() const
{
	return m_Height;
}

int32_t Map::GetResourceTypeId(std::string type)
{
	std::string resourceTypeNames[] = {
		"nourriture",
		"linemate",
		"deraumere",
		"sibur",
		"mendiane",
		"phiras",
		"thystame"
	};

	for (int32_t i = 0; i < RESSOURCES_COUNT; i++)
	{
		if (resourceTypeNames[i] == type)
			return i;
	}
	return -1;
}

