#pragma once
#include "vec4.h"

template <typename T>
struct mat4 {
	vec4<T> values[4];

public:
	mat4() {
		values[0][0] = 1;
		values[1][1] = 1;
		values[2][2] = 1;
		values[3][3] = 1;
	}

	vec4<T>& operator[](int i) {
		return values[i];
	}

	float* ptr() {
		return &(values[0][0]);
	}
};