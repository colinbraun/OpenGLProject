#pragma once
#include "vec4.h"

// A 4x4 matrix struct
template <typename T = float>
struct mat4 {
	
	// Note that each vec4 represents a COLUMN, NOT A ROW. This is simply a design choice. OpenGL expects a matrix in COLUMN MAJOR ORDER.
	// The same thing could be accomplished by letting each vec4 represent a ROW and telling OpenGL to transpose the matrix.
	vec4<T> values[4];

public:
	mat4() {
		values[0][0] = 1;
		values[1][1] = 1;
		values[2][2] = 1;
		values[3][3] = 1;
	}

	/* Construct a 4x4 matrix, passing the elements by row.
	 * If parameters are placed on seperate lines, the result will look like the actual 4x4 matrix.
	*/
	mat4(const T& x0, const T& x1, const T& x2, const T& x3,
		const T& y0, const T& y1, const T& y2, const T& y3,
		const T& z0, const T& z1, const T& z2, const T& z3,
		const T& w0, const T& w1, const T& w2, const T& w3) {
		values[0] = vec4<T>(x0, y0, z0, w0);
		values[1] = vec4<T>(x1, y1, z1, w1);
		values[2] = vec4<T>(x2, y2, z2, w2);
		values[3] = vec4<T>(x3, y3, z3, w3);
	}

	// This constructor has not been tested for the !areColumnVectors case
	mat4(vec4<T> v1, vec4<T> v2, vec4<T> v3, vec4<T> v4, bool areColumnVectors = true) {
		if (areColumnVectors) {
			values[0] = v1;
			values[1] = v2;
			values[2] = v3;
			values[3] = v4;
		}
		else {
			mat4 trans = transpose();
			values[0] = trans[0];
			values[1] = trans[1];
			values[2] = trans[2];
			values[3] = trans[3];
		}
	}

	// Create a mat4 that is the transposed version of this one. Does NOT modify this mat4.
	mat4 transpose() {
		mat4 result = mat4();
		for (unsigned int col = 0; col < 4; col++) {
			for (unsigned int row = 0; row < 4; row++) {
				result[row][col] = values[col][row];
			}
		}
		return result;
	}

	// Multiply this mat4 with another. Does NOT modify this mat4.
	// Considering implementing this in a more brute force way, since this way uses transposing (more processing).
	mat4 operator*(mat4 m) {
		mat4 m1 = this->transpose();
		mat4 result = mat4();
		for (unsigned int row = 0; row < 4; row++) {
			for (unsigned int col = 0; col < 4; col++) {
				result[col][row] = m1[row].dot(m[col]);
			}
		}
		return result;
	}

	vec4<T>& operator[](const unsigned int i) {
		return values[i];
	}

	float* ptr() {
		return &values[0][0];
	}

	void printMat() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << values[j][i] << ",";
			}
			std::cout << std::endl;
		}
	}
};

typedef mat4<float> mat4f;