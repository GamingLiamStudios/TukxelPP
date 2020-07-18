#pragma once
#ifndef FMATH
#define FMATH
#define PI  3.141592653589793
#define PI2 6.283185307179586
#define PIS 9.869604401089357
#define TAU 1.570796326794897

struct FMath {
public:
	//Thx Digi
	static float mod(float a, float b) {
		a /= b;
		a -= (int32_t)a;
		return a * b;
	}

	static float cos(float t) {
		float x = -mod(t + TAU, PI) + TAU;
		x *= x;
		float m = (PIS - 4 * x) / (PIS + x);
		return -m * (mod(t + TAU, PI2) > PI) * 2 + m;
	}

	static float sin(float t) {
		return cos(TAU - t);
	}
};
#endif