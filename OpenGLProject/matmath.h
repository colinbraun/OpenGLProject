#pragma once

#include "mat4.h"

// Generate a matrix that will apply a translation to any given vertex
template <typename T = float>
mat4<T> translate(T x, T y, T z) {
	return mat4<T>(1, 0, 0, x,
				   0, 1, 0, y,
				   0, 0, 1, z,
				   0, 0, 0, 1);
}

// Generate a matrix that will apply a scale to any given vertex
// Note that the vertex should first be translated to the origin before this operation (else it will be centered somewhere else), and then translated back afterwards
template <typename T = float>
mat4<T> scale(T x, T y, T z) {
	return mat4<T>(x, 0, 0, 0,
				   0, y, 0, 0,
				   0, 0, z, 0,
				   0, 0, 0, 1);
}

// TODO: implement rotation (decisions still to be made)
template <typename T = float>
mat4<T> rotate() {

}

// TODO: implement projection (will need some thinking)
template <typename T = float>
mat4<T> projection() {

}