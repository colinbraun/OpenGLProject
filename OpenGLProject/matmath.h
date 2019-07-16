#pragma once

#include "mat4.h"
#include <corecrt_math_defines.h>
#include "vec3.h"

double deg2Rad = 2 * M_PI / 360;

// Generate a matrix that will apply a translation to any given vertex
template <typename T = float>
mat4<T> translate(T x, T y, T z) {
	return mat4<T>(1, 0, 0, x,
				   0, 1, 0, y,
				   0, 0, 1, z,
				   0, 0, 0, 1);
}

// Translate overload for vec3
template <typename T = float>
mat4<T> translate(vec3<T> d) {
	return mat4<T>(1, 0, 0, d.x,
				   0, 1, 0, d.y,
				   0, 0, 1, d.z,
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

// Scale overload for vec3
template <typename T = float>
mat4<T> scale(vec3<T> s) {
	return mat4<T>(s.x, 0, 0, 0,
				   0, s.y, 0, 0,
				   0, 0, s.z, 0,
				   0, 0, 0, 1);
}

// TODO: implement rotation (decisions still to be made)
template <typename T = float>
mat4<T> rotate(T xDegrees, T yDegrees, T zDegrees, bool deg = true) {
	return mat4<T>(cos(xDegrees * deg2Rad), 3);
}

template <typename T = float>
mat4<T> rotateAboutArbitraryAxis(vec3<T> p1, vec3<T> p2, T degrees) {
	T val = (T)(degrees * deg2Rad);
	vec3<T> direction = p2 - p1;
	T theta = atan(direction.y / direction.z);
	T phi = atan(direction.x / sqrt(direction.y * direction.y + direction.z * direction.z));
	// Translate such that the axis passes through the origin
	mat4<T> retValue = translate(-p1);
	// Rotate space about the x-axis so that the rotation axis lies in the xz-plane
	retValue = mat4<T>(1, 0, 0, 0,
							 0, cos(theta), -sin(theta), 0,
							 0, sin(theta), cos(theta), 0,
							 0, 0, 0, 1) * retValue;
	// Rotate space about the y-axis so that the rotation axis lies on the z-axis
	retValue = mat4<T>(cos(phi), 0, sin(phi), 0,
							 0, 1, 0, 0,
							 -sin(phi), 0, cos(phi), 0,
							 0, 0, 0, 1) * retValue;
	// Perform the desired rotation by theta about the z axis
	retValue = mat4<T>(cos(val), -sin(val), 0, 0,
							 sin(val), cos(val), 0, 0,
							 0, 0, 1, 0,
							 0, 0, 0, 1) * retValue;
	// Undo rotatation about y-axis
	retValue = mat4<T>(cos(-phi), 0, sin(-phi), 0,
							 0, 1, 0, 0,
							 -sin(-phi), 0, cos(-phi), 0,
							 0, 0, 0, 1) * retValue;
	// Undo rotation about x-axis
	retValue = mat4<T>(1, 0, 0, 0,
							 0, cos(-theta), -sin(-theta), 0,
							 0, sin(-theta), cos(-theta), 0,
							 0, 0, 0, 1) * retValue;
	// Translate back to where it started
	retValue = translate(p1) * retValue;
	return retValue;
}

template <typename T = float>
mat4<T> rotateAboutZAxis(T degrees) {
	double val = degrees * deg2Rad;
	return mat4<T>((T)cos(val), (T)(-sin(val)), 0, 0,
				   (T)sin(val), (T)cos(val), 0, 0,
				   0, 0, 1, 0,
				   0, 0, 0, 1);
}

// TODO: implement projection (will need some thinking)
template <typename T = float>
mat4<T> projection() {
	
}