#include "VectorTest.h"

void RunVectorTests() {
	int pass = 0;
	int fail = 0;

	VectorTest_Addition()		? pass++ : fail++;
	VectorTest_Subtraction()	? pass++ : fail++;
	VectorTest_Scale()			? pass++ : fail++;
	VectorTest_LengthSquared()	? pass++ : fail++;
	VectorTest_DotProduct()		? pass++ : fail++;
	VectorTest_CrossProduct()		? pass++ : fail++;


	fprintf(stderr,"Vector Passed: %i\t Failed: %i\n", pass, fail);
}


bool VectorTest_Addition() {
	Vector3D v1 = Vector3D(1., 1., 1.);
	Vector3D v2 = Vector3D(1., 1., 1.);

	Vector3D v3 = v1 + v2;

	printf("VectorTest_Addition: x=%f y=%f z=%f\n", v3.x, v3.y, v3.z);
	if (v3.x == 2. && v3.y == 2. && v3.z == 2)
		return true;
	else
		return false;
}

bool VectorTest_Subtraction() {
	Vector3D v1 = Vector3D(1., 1., 1.);
	Vector3D v2 = Vector3D(1., 1., 1.);

	Vector3D v3 = v1 - v2;
	printf("VectorTest_Subtraction: x=%f y=%f z=%f\n", v3.x, v3.y, v3.z);
	if (v3.x == 0. && v3.y == 0. && v3.z == 0.)
		return true;
	else
		return false;
}

bool VectorTest_Scale() {
	Vector3D v1 = Vector3D(1., 1., 1.);
	double scaleFactor = 51;

	Vector3D v3 = v1 * scaleFactor;

	printf("VectorTest_Scale: x=%f y=%f z=%f\n", v3.x, v3.y, v3.z);

	if (v3.x == scaleFactor && v3.y == scaleFactor && v3.z == scaleFactor)
		return true;
	else
		return false;
}

bool VectorTest_LengthSquared() {
	Vector3D vect = Vector3D(1., 2., 3.);

	double l = vect.LengthSquared();

	printf("VectorTest_LengthSquared: l=%f\n", l);

	if (l == 14)
		return true;
	else
		return false;
}

bool VectorTest_DotProduct()
{
	Vector3D v1 = Vector3D(1., 2., 3.);
	Vector3D v2 = Vector3D(6., 7., 8.);

	double dot = v1.DotProduct(v2);

	printf("VectorTest_DotProduct: dot=%f\n", dot);
	if (dot == 44)
		return true;
	else
		return false;
}

bool VectorTest_CrossProduct()
{
	Vector3D v1 = Vector3D(1., 2., 3.);
	Vector3D v2 = Vector3D(4., 5., 6.);

	Vector3D cross = v1.CrossProduct(v2);

	printf("VectorTest_CrossProduct: x=%f y=%f z=%f\n", cross.x, cross.y, cross.z);
	if (cross.x == -3. && cross.y == 6. && cross.z == -3.)
		return true;
	else
		return false;
}
