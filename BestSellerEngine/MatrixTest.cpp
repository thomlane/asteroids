#include "Matrix4D.h"
#include "MatrixTest.h"


void RunMatrixTests() {
	int pass = 0;
	int fail = 0;

	MatrixTest_Identity() ? pass++ : fail++;
	MatrixTest_Transpose() ? pass++ : fail++;
	MatrixTest_Inverse() ? pass++ : fail++;
	MatrixTest_Addition() ? pass++ : fail++;
	MatrixTest_Subtraction() ? pass++ : fail++;
	MatrixTest_Scalar_Multiplication() ? pass++ : fail++;
	MatrixTest_Matrix_Multiplication() ? pass++ : fail++;
	MatrixTest_Vector_Multiplication() ? pass++ : fail++;


	fprintf(stderr, "Matrix Passed: %i\t Failed: %i\n", pass, fail);
}

bool MatrixTest_Identity() {
	Matrix4D identity = Matrix4D();

	identity = identity.Identity();

	bool check = true;
	if (identity(0, 0) != 1 || identity(1,1) != 1 || identity(2,2) != 1 || identity(3,3) != 1) {
		check = false;
	}

	printf("MatrixTest_Identity: check=%s\n", check?"true":"false");
	identity.print();
	return check;
}

bool MatrixTest_Transpose() {
	Matrix4D transpose = Matrix4D();
	transpose(3, 0) = 3;
	transpose(1, 2) = 6;
	transpose = transpose.Transpose();

	bool check = true;
	if (transpose(0, 3) != 3 || transpose(2, 1) != 6) {
		check = false;
	}

	printf("MatrixTest_Transpose: check=%s\n", check ? "true" : "false");
	transpose.print();
	return check;
}

bool MatrixTest_Inverse() {
	Matrix4D input = Matrix4D();
	Matrix4D inverse = Matrix4D();
	Matrix4D result = Matrix4D();

	input(0, 0) = 1;
	input(0, 1) = 2;
	input(0, 2) = -1;

	input(1, 0) = 2;
	input(1, 1) = 1;
	input(1, 2) = 2;

	input(2, 0) = -1;
	input(2, 1) = 2;
	input(2, 2) = 1;

	inverse(0, 0) = 3. / 16.;
	inverse(0, 1) = 1. / 4.;
	inverse(0, 2) = -5. / 16.;

	inverse(1, 0) = 1. / 4.;
	inverse(1, 1) = -0.;
	inverse(1, 2) = 1. / 4.;

	inverse(2, 0) = -5. / 16.;
	inverse(2, 1) = 1. / 4.;
	inverse(2, 2) = 3. / 16.;

	result = input.Inverse3D();

	bool check = true;
	if (result != inverse) {
		check = false;
	}

	printf("MatrixTest_Inverse: check=%s\n", check ? "true" : "false");
	inverse.print();
	printf("Test\n");
	result.print();
	return check;
}

bool MatrixTest_Addition() {
	Matrix4D addition1 = Matrix4D();
	Matrix4D addition2 = Matrix4D();
	addition1(3, 0) = 3;
	addition1(1, 2) = 6;

	addition2(3, 0) = 5;
	addition2(2, 1) = 4;
	addition1 = addition1 + addition2;

	bool check = true;
	if (addition1(3, 0) != 8 || addition1(2, 1) != 4 || addition1(1,2) != 6) {
		check = false;
	}

	printf("MatrixTest_Addition: check=%s\n", check ? "true" : "false");
	addition1.print();
	return check;
}

bool MatrixTest_Subtraction() {
	Matrix4D subtraction1 = Matrix4D();
	Matrix4D subtraction2 = Matrix4D();
	subtraction1(3, 0) = 3;
	subtraction1(1, 2) = 6;

	subtraction2(3, 0) = 5;
	subtraction2(2, 1) = 4;
	subtraction1 = subtraction1 - subtraction2;

	bool check = true;
	if (subtraction1(3, 0) != -2 || subtraction1(2, 1) != -4 || subtraction1(1, 2) != 6) {
		check = false;
	}

	printf("MatrixTest_Subtraction: check=%s\n", check ? "true" : "false");
	subtraction1.print();
	return check;
}

bool MatrixTest_Scalar_Multiplication() {
	Matrix4D mult1 = Matrix4D();
	Matrix4D mult2 = Matrix4D();
	int scalar = 5;

	mult1(3, 0) = 3;
	mult1(1, 2) = 6;


	mult2 = mult1 * scalar;
	bool check = true;
	if (mult2(3, 0) != 15 || mult2(1, 2) != 30) {
		check = false;
	}

	printf("MatrixTest_Scalar_Multiplication: check=%s\n", check ? "true" : "false");
	mult2.print();
	return check;
}

bool MatrixTest_Matrix_Multiplication() {
	Matrix4D mult1 = Matrix4D();
	Matrix4D mult2 = Matrix4D();
	Matrix4D mult3 = Matrix4D();
	Matrix4D mult4 = Matrix4D();

	mult1(0, 0) = 5;
	mult1(0, 2) = 9;
	mult1(0, 3) = 10;
	mult1(1, 3) = 8;
	mult1(2, 0) = 8;
	mult1(2, 1) = 10;
	mult1(2, 3) = 3;
	mult1(3, 0) = 3;
	mult1(3, 1) = 3;
	mult1(3, 3) = 8;


	mult2(0, 0) = 3;
	mult2(0, 1) = 10;
	mult2(1, 1) = 1;
	mult2(2, 1) = 10;
	mult2(2, 2) = 12;
	mult2(3, 0) = 3;
	mult2(3, 3) = 10;

	mult3(0, 0) = 45;
	mult3(0, 1) = 140;
	mult3(0, 2) = 108;
	mult3(0, 3) = 100;
	mult3(1, 0) = 24;
	mult3(1, 3) = 80;
	mult3(2, 0) = 33;
	mult3(2, 1) = 90;
	mult3(2, 3) = 30;
	mult3(3, 0) = 33;
	mult3(3, 1) = 33;
	mult3(3, 3) = 80;


	mult4 = mult1 * mult2;
	bool check = true;
	if (mult3 != mult4) {
		check = false;
	}

	printf("MatrixTest_Matrix_Multiplication: check=%s\n", check ? "true" : "false");
	mult3.print();
	printf("\n");
	mult4.print();
	return check;
}

bool MatrixTest_Vector_Multiplication() {
	Matrix4D mult1 = Matrix4D();
	vector<double> vect1{ 10,20,5,8 };
	vector<double> vect2(4,0);
	vector<double> vect_result{ 175,64,304,154 };

	mult1(0, 0) = 5;
	mult1(0, 2) = 9;
	mult1(0, 3) = 10;
	mult1(1, 3) = 8;
	mult1(2, 0) = 8;
	mult1(2, 1) = 10;
	mult1(2, 3) = 3;
	mult1(3, 0) = 3;
	mult1(3, 1) = 3;
	mult1(3, 3) = 8;


	vect2 = mult1 * vect1;
	bool check = true;
	if (vect2 != vect_result) {
		check = false;
	}

	printf("MatrixTest_Vector_Multiplication: check=%s\n", check ? "true" : "false");

	return check;
}

