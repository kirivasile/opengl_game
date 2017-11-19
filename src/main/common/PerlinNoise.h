#pragma once

#include <cmath>
#include <random>
#include <vector>

struct Vector2D {
	float x;
	float y;

	Vector2D(float xx, float yy) : x(xx), y(yy)
	{}
};

class PerlinNoise {
public:
	PerlinNoise(unsigned int num_of_octaves=1, float persistence=0.5f, int seed=0);
	float perlin_noise_2D(float fx, float fy);
private:
	float cosine_interpolation(float a, float b, float x);
	Vector2D get_pseudo_random_grad_vector(int x,int y);
	float dot(const Vector2D& x, const Vector2D& y);
	float noise(float fx, float fy);

	std::vector<int> _permutation_table;
	unsigned int _num_of_octaves;
	float _persistence;
};