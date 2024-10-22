#pragma once

#include <random>
#include <algorithm>

class PerlinNoise
{

public:
	PerlinNoise(int x, int y) {
		m_Width = x;
		m_Height = y;
		for (int i = 0; i < 256; i++)
			P[i] = i;
		shuffleArray(P, 256);
	}
	~PerlinNoise() {}

	float *Generate() {
		float *values = new float[m_Width * m_Height];
		for (int32_t y = 0; y < m_Height; y++)
		{
			for (int32_t x = 0; x < m_Width; x++)
			{
				float perlinValue = (Noise(x, y, 8));
				values[y + x + y * (m_Width - 1)] = perlinValue;
			}
		}
		return values;
	}

private:
	#define interpolation(t) (6 * t * t * t * t * t - 15 * t * t * t * t + 10 * t * t * t)

	int m_Width;
	int m_Height;
	int P[256];
	int G[8][2] = {
	{1,1},    {-1,1},   {1,-1},   {-1,-1},
	{1,0},    {-1,0},   {0,1},    {0,-1}};

	float randomFloat()
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_real_distribution<float> dis(-1.0f, 1.0f);
		return dis(gen);
	}

	void shuffleArray(int *arr, int N) {
		std::random_device rd;
		std::mt19937 gen(rd());

		for (size_t i = N - 1; i > 0; --i) {
			std::uniform_int_distribution<size_t> dist(0, i);
			size_t j = dist(gen);
			std::swap(arr[i], arr[j]);
		}
	}

	float Noise(float x, float y, unsigned int scale)
	{
		int G1,G2,G3,G4;

		double s,t,u,v;

		int Q1[2], Q2[2], Q3[2], Q4[2];
		double p[2];

		double iX,iY,tmp;

		double iST;
		double iUV;

		p[0] = (double) x / scale;
		p[1] = (double) y / scale;

		Q1[0] = (int) p[0];
		Q1[1] = (int) p[1];

		Q2[0] = Q1[0] + 1;
		Q2[1] = Q1[1];

		Q3[0] = Q2[0];
		Q3[1] = Q1[1] + 1;

		Q4[0] = Q1[0];
		Q4[1] = Q3[1];

		G1 = P[ (Q1[0] + P[ Q1[1] & 255] + scale) & 255 ] & 7;
		G2 = P[ (Q2[0] + P[ Q2[1] & 255] + scale) & 255 ] & 7;
		G3 = P[ (Q3[0] + P[ Q3[1] & 255] + scale) & 255 ] & 7;
		G4 = P[ (Q4[0] + P[ Q4[1] & 255] + scale) & 255 ] & 7;

		s = G[G1][0] * (p[0]-Q1[0]) + G[G1][1] * (p[1]-Q1[1]);
		t = G[G2][0] * (p[0]-Q2[0]) + G[G2][1] * (p[1]-Q2[1]);
		u = G[G3][0] * (p[0]-Q3[0]) + G[G3][1] * (p[1]-Q3[1]);
		v = G[G4][0] * (p[0]-Q4[0]) + G[G4][1] * (p[1]-Q4[1]);


		tmp = p[0]-Q1[0];
		iX = interpolation(tmp);

		iST = s + iX * (t-s);
		iUV = v + iX * (u-v);

		tmp = p[1]-Q1[1];

		iY = interpolation(tmp);

		return (1 + iST + iY * (iUV - iST)) * 0.5;
	}
};
