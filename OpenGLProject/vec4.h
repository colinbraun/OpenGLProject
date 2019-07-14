#pragma once

template <typename T>
struct vec4 {
	T x;
	T y;
	T z;
	T w;

public:
	vec4() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}

	vec4(T x, T y, T z, T w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	vec4 operator+(vec4 v) {
		return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	vec4 operator-(vec4 v) {
		return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	T dot(vec4 v) {
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}

	T& operator[](int i) {
		switch (i) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			return w;
		}
	}

};