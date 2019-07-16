#pragma once
#include "mat4.h"
using namespace std;
// This has been run and verified to work (as of 7/15/2019 @9:58PM EST)
void testMat4() {
	mat4<> mat = mat4<>(3, 0, 7, -1,
		-4, 8, 18, 8, 
		-3, 2, 1, -29,
		6, 0, 12, 5);
	mat4<> mat2 = mat4<>(4, -2, 0, 7,
		6, 9, 24, 1,
		-3, 2, 8, 6,
		5, 4, 3, 2);

	mat.printMat();
	mat2.printMat();
	(mat * mat2).printMat();
	mat.transpose().printMat();
}
