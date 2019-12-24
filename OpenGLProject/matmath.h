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

/* Create a matrix that will rotate all points about an arbitrary axis
 * p1 - the first point defining the axis
 * p2 - The second point defining the axis
 * degrees - 
*/
template <typename T = float>
mat4<T> rotateAboutArbitraryAxis(vec3<T> p1, vec3<T> p2, T angle, bool isRadians = true) {
	T val = (T)(isRadians ? angle : angle * deg2Rad);
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

// Create a matrix that will rotate points counterclockwise about the z-axis
// when looking down the positive z-axis to the origin
template <typename T = float>
mat4<T> rotateAboutZAxis(T angle, bool isRadians = true) {
	double val = isRadians ? angle : angle * deg2Rad;
	return mat4<T>((T)cos(val), (T)(-sin(val)), 0, 0,
		(T)sin(val), (T)cos(val), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

// Create a matrix that will rotate points counterclockwise about the x-axis
// when looking down the positive x-axis to the origin
template <typename T = float>
mat4<T> rotateAboutXAxis(T angle, bool isRadians = true) {
	double val = isRadians ? angle : angle * deg2Rad;
	return mat4<T>(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, (T)cos(val), (T)(-sin(val)), 0.0f,
		0.0f, (T)sin(val), (T)cos(val), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

// Create a matrix that will rotate points counterclockwise about the y-axis
// when looking down the positive y-axis to the origin
template <typename T = float>
mat4<T> rotateAboutYAxis(T angle, bool isRadians = true) {
	double val = isRadians ? angle : angle * deg2Rad;
	return mat4<T>((T)cos(val), 0, (T)sin(val), 0,
		0, 1, 0, 0,
		(T)(-sin(val)), 0, (T)cos(val), 1,
		0.0f, 0.0f, 0.0f, 1.0f);
}

// Return a view matrix that will position the camera at pos, pointed at target
// For an understanding of how this works mathematically, see:
// https://www.geertarien.com/blog/2017/07/30/breakdown-of-the-lookAt-function-in-OpenGL/
template <typename T = float>
mat4<T> lookAt(vec3<T> pos, vec3<T> target, vec3<T> up) {
	vec3<T> direction = target - pos;
	mat4<T> retValue = translate(-pos);
	T divNum = direction.z / direction.y;
	if (divNum != NAN) {
		T theta = atan(divNum) + M_PI_2;
		retValue = rotateAboutXAxis(theta) * retValue;
	} 
	divNum = sqrt(direction.z * direction.z + direction.y * direction.y) / direction.x;
	if (divNum != NAN) {
		T theta = -atan(divNum);
		retValue = rotateAboutYAxis(theta) * retValue;
	}
	
	return retValue;
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