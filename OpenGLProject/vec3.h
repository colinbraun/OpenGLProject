#pragma once

template <typename T = float>
struct vec3 {
	T x;
	T y;
	T z;

public:
	vec3() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	vec3(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3 operator+(vec3 v) const {
		return vec3(x + v.x, y + v.y, z + v.z);
	}

	vec3 operator-(vec3& v) const {
		return vec3(x - v.x, y - v.y, z - v.z);
	}

	vec3 operator-() const {
		return vec3(-x, -y, -z);
	}

	T dot(vec3 v) const {
		return x * v.x + y * v.y + z * v.z;
	}

	vec3 cross(vec3 v) {
		// TODO Implement
		return vec3();
	}

	T& operator[](int i) {
		switch (i) {
		case 0:
			return x;
		case 1:
			return y;
		default:
			return z;
		}
	}

	vec3 normalize() {
		T mag = magnitude();
		return vec3(x / mag, y / mag, z / mag);
	}

	T magnitude() {
		return sqrt(x * x + y * y + z * z);
	}
};