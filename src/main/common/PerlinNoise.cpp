#include "PerlinNoise.h"

PerlinNoise::PerlinNoise(unsigned int num_of_octaves, float persistence, int seed) :
	_num_of_octaves(num_of_octaves),
	_persistence(persistence) {
	_permutation_table = std::vector<int>(1024);
	srand(seed);
	for (unsigned int i = 0; i < 1024; ++i) {
		_permutation_table[i] = rand() % 256;
	}
}

float PerlinNoise::cosine_interpolation(float a, float b, float x) {
	float ft = x * 3.1415927f;
	float f = (1.f - cos(ft)) * .5f;
	return a * (1.f - f) + b * f;
}

Vector2D PerlinNoise::get_pseudo_random_grad_vector(int x, int y) {
	int v = (int)(((x * 1836311903) ^ (y * 2971215073) + 4807526976) & 1023);
	v = _permutation_table[v] & 3;
	switch (v) {
	case 0: return Vector2D(1.f, 0.f);
	case 1: return Vector2D(-1.f, 0.f);
	case 2: return Vector2D(0.f, 1.f);
	default: return Vector2D(0.f, -1.f);
	}
}

float PerlinNoise::dot(const Vector2D& x, const Vector2D& y) {
	return x.x * y.x + x.x * y.y;
}

float PerlinNoise::noise(float fx, float fy) {
	int left = floor(fx);
	int top = floor(fy);
	float frac_x = fx - left;
	float frac_y = fy - top;

	Vector2D top_left_grad = get_pseudo_random_grad_vector(left, top);
	Vector2D top_right_grad = get_pseudo_random_grad_vector(left + 1, top);
	Vector2D bottom_left_grad = get_pseudo_random_grad_vector(left, top + 1);
	Vector2D bottom_right_grad = get_pseudo_random_grad_vector(left + 1, top + 1);

	Vector2D distance_to_top_left = Vector2D(frac_x, frac_y);
	Vector2D distance_to_top_right = Vector2D(frac_x - 1, frac_y);
	Vector2D distance_to_bottom_left = Vector2D(frac_x, frac_y - 1);
	Vector2D distance_to_bottom_right = Vector2D(frac_x - 1, frac_y - 1);

	float tx1 = dot(distance_to_top_left, top_left_grad);
	float tx2 = dot(distance_to_top_right, top_right_grad);
	float bx1 = dot(distance_to_bottom_left, bottom_left_grad);
	float bx2 = dot(distance_to_bottom_right, bottom_right_grad);

	float tx = cosine_interpolation(tx1, tx2, frac_x);
	float bx = cosine_interpolation(bx1, bx2, frac_x);
	return cosine_interpolation(tx, bx, frac_y);
}

float PerlinNoise::perlin_noise_2D(float fx, float fy) {
	float amplitude = 1.f;
	float max = 0.f;
	float result = 0.f;

	for (int i = _num_of_octaves; i > 0; i--) {
		max += amplitude;
		result += noise(fx, fy) * amplitude;
		amplitude *= _persistence;
		fx *= 2;
		fy *= 2;
	}
	return result / max;
}