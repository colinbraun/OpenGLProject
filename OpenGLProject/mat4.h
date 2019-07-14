#pragma once
#include "vec4.h"

template <typename T = float>
struct mat4 {
	vec4<T> values[4];

public:
	mat4() {
		values[0][0] = 1;
		values[1][1] = 1;
		values[2][2] = 1;
		values[3][3] = 1;
	}

	mat4(const T& x0, const T& x1, const T& x2, const T& x3,
		const T& y0, const T& y1, const T& y2, const T& y3,
		const T& z0, const T& z1, const T& z2, const T& z3,
		const T& w0, const T& w1, const T& w2, const T& w3) {
		values[0] = vec4<T>(x0, y0, z0, w0);
		values[1] = vec4<T>(x1, y1, z1, w1);
		values[2] = vec4<T>(x2, y2, z2, w2);
		values[3] = vec4<T>(x3, y3, z3, w3);
	}

	vec4<T>& operator[](const int i) {
		return values[i];
	}

	float* ptr() {
		return &values[0][0];
	}
};