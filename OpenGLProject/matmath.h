#pragma once

#include "mat4.h"
#include <corecrt_math_defines.h>
#include "vec3.h"
#include "vec4.h"

double deg2Rad = 2 * M_PI / 360;

// Generate a matrix that will apply a translation to any given vertex.
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

// Generate a matrix that will apply a scale to any given vertex.
// Note that the vertex should first be translated to the origin before this operation (else it will be centered somewhere else), and then translated back afterwards.
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

// TODO: implement rotation (decisions still to be made).
template <typename T = float>
mat4<T> rotate(T xDegrees, T yDegrees, T zDegrees, bool deg = true) {
	return mat4<T>();
}

template <typename T = float>
mat4<T> rotateAboutArbitraryAxis(vec3<T> p1, vec3<T> p2, T degrees) {
	T val = (T)(degrees * deg2Rad);
	vec3<T> direction = p2 - p1;
	// If Y direction.y and direction.z are 0, it will produce NaN - This would be bad.
	T theta = direction.y == direction.z ? 0 : atan(direction.y / direction.z);
	T phi = atan(direction.x / sqrt(direction.y * direction.y + direction.z * direction.z));
	// Translate such that the axis passes through the origin.
	mat4<T> retValue = translate(-p1);
	// Rotate space about the x-axis so that the rotation axis lies in the xz-plane.
	// Note the order the matrices are multipled in. Matrix multiplication is not commutative, so the order matters.
	retValue = mat4<T>(1, 0, 0, 0,
							 0, cos(theta), -sin(theta), 0,
							 0, sin(theta), cos(theta), 0,
							 0, 0, 0, 1) * retValue;
	// Rotate space about the y-axis so that the rotation axis lies on the z-axis.
	retValue = mat4<T>(cos(phi), 0, sin(phi), 0,
							 0, 1, 0, 0,
							 -sin(phi), 0, cos(phi), 0,
							 0, 0, 0, 1) * retValue;
	// Perform the desired rotation by theta about the z axis.
	retValue = mat4<T>(cos(val), -sin(val), 0, 0,
							 sin(val), cos(val), 0, 0,
							 0, 0, 1, 0,
							 0, 0, 0, 1) * retValue;
	// Undo rotatation about y-axis.
	retValue = mat4<T>(cos(-phi), 0, sin(-phi), 0,
							 0, 1, 0, 0,
							 -sin(-phi), 0, cos(-phi), 0,
							 0, 0, 0, 1) * retValue;
	// Undo rotation about x-axis.
	retValue = mat4<T>(1, 0, 0, 0,
							 0, cos(-theta), -sin(-theta), 0,
							 0, sin(-theta), cos(-theta), 0,
							 0, 0, 0, 1) * retValue;
	// Translate back to where it started.
	retValue = translate(p1) * retValue;
	return retValue;
}

// Return a view matrix that will position the camera at pos, pointed at target
// For an understanding of how this works mathematically, see:
// https://www.geertarien.com/blog/2017/07/30/breakdown-of-the-lookAt-function-in-OpenGL/
template <typename T = float>
mat4<T> lookAt(vec3<T> pos, vec3<T> target, vec3<T> up) {
	vec3<T> zaxis = (pos - target).normalize();
	vec3<T> xaxis = zaxis.cross(up).normalize();
	vec3<T> yaxis = xaxis.cross(zaxis);

	zaxis = -zaxis;

	mat4<T> viewMatrix = mat4<T>(
	  vec4<T>(xaxis.x, xaxis.y, xaxis.z, -xaxis.dot(pos)),
	  vec4<T>(yaxis.x, yaxis.y, yaxis.z, -yaxis.dot(pos)),
	  vec4<T>(zaxis.x, zaxis.y, zaxis.z, -zaxis.dot(pos)),
	  vec4<T>(0, 0, 0, 1), false
	);

	return viewMatrix;
}

template <typename T = float>
mat4<T> rotateAboutZAxis(T degrees) {
	double val = degrees * deg2Rad;
	return mat4<T>((T)cos(val), (T)(-sin(val)), 0, 0,
				   (T)sin(val), (T)cos(val), 0, 0,
				   0, 0, 1, 0,
				   0, 0, 0, 1);
}

// TODO: implement perspective projection (will need some thinking).
template <typename T = float>
mat4<T> perspective(T fov, T ratio, T near, T far, bool areDegrees = true) {
	T tanValDiv2 = (T)(areDegrees ? tan(fov * deg2Rad / 2) : tan(fov / 2));
	return mat4<T>(ratio * near / (near * tanValDiv2), 0, 0, 0,
				   0, near / (near * tanValDiv2), 0, 0,
				   0, 0, (-(far + near)) / (far - near), -2 * far * near / (far - near),
				   0, 0, -1, 0);
}

// Create and return matrix that will do orthographic projection.
template <typename T = float>
mat4<T> orthographic() {
	mat4<T> m = mat4<T>();
	m[2][2] = 0;
	return m;
}