#include "Matrix4D.h"

Matrix4D::Matrix4D()
{
	this->matrix.resize(4);
	for (int i = 0; i < 4; i++) {
		this->matrix[i].resize(4);
	}
}

Matrix4D::Matrix4D(double value)
{
	this->matrix.resize(4);
	for (int i = 0; i < 4; i++) {
		this->matrix[i].resize(4,value);
	}
}

bool Matrix4D::operator== (const Matrix4D& that) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (this->matrix[row][col] != that.matrix[row][col])
				return false;
		}
	}
	return true;
}

bool Matrix4D::operator!= (const Matrix4D& that) {
	return !(*this == that);
}

double& Matrix4D::operator()(const unsigned& row, const unsigned& col)
{
	return this->matrix[row][col];
}

void Matrix4D::print()
{
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			printf("[%f]", (*this)(row, col));
		}
		printf("\n");
	}
}


Matrix4D Matrix4D::Identity()
{
	Matrix4D identity = Matrix4D();
	int row, col;
	for (row = 0;row < 4;row++) {
		for (col = 0;col < 4;col++) {
			if (row == col)
				identity.matrix[row][col] = 1;
			else
				identity.matrix[row][col] = 0;
		}		
	}

	return identity;
}

Matrix4D Matrix4D::Transpose()
{
	Matrix4D transpose = Matrix4D();
	for (int col = 0; col < 4;col++) {
		for (int row = 0; row < 4; row++) {
			transpose.matrix[col][row] = this->matrix[row][col];
		}
	}
	return transpose;
}

double Matrix3D_Determinent(Matrix4D mat)
{	
	int add = 0;
	int sub = 0;
	for (int col = 0; col < 3; col++) {
		printf("add %i: %f\n", col, mat(0, col) * mat(1, (col + 1) % 3) * mat(2, (col + 2) % 3));
		add += mat(0, col) * mat(1, (col + 1) % 3) * mat(2, (col + 2) % 3);
		printf("sub %i: %f\n", col, mat(0, col) * mat(1, (col + 2) % 3) * mat(2, (col + 1) % 3));
		sub -= mat(0, col) * mat(1, (col + 2) % 3) * mat(2, (col + 1) % 3);
	}
	return add + sub;
}

double Matrix3D_findValue(Matrix4D mat,int xrow, int xcol) {
	vector<double> values(4, 0);
	int count = 0;
	for (int row = 0; row < 3; row++)
	{
		if (row == xrow) continue;
		for (int col = 0; col < 3; col++)
		{
			if (col == xcol) continue;
			values[count] = mat(row, col);
			count++;
		}
	}

	return (values[0] * values[3]) - (values[2] * values[1]);

}

Matrix4D Matrix3D_Cofactor(Matrix4D mat) {
	int addOrSubtract = 1;
	Matrix4D newMat = Matrix4D();
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			newMat(row, col) = Matrix3D_findValue(mat,row,col) * addOrSubtract;
			printf("(%i,%i): %i\n", row, col, addOrSubtract);
			addOrSubtract *= -1;
		}
	}
	return newMat.Transpose();
}
/*
Matrix4D createDeterminantMatrix(Matrix4D mat,int removed_row)
{
	Matrix4D newMat = Matrix4D();
	int row_adjustment = 0;
	for (int row = 0; row < 4; row++)
	{
		if (removed_row == row)
		{
			row_adjustment = 1;
			continue;
		}
		for (int col = 0; col < 3; col++)
		{
			newMat(row - row_adjustment, col) = mat(row + row_adjustment, col + 1);
		}
	}
	return newMat;
}

Matrix4D Matrix4D::Inverse4D()
{
	int addOrSubtract = 1;
	double determinant_4D = 0;
	for (int row = 0; row < 4; row++)
	{
		Matrix4D det_Matrix = createDeterminantMatrix(*this, row);
		double determinant_3D = Matrix3D_Determinent(det_Matrix);
		
		determinant_4D += (*this)(row,0) * addOrSubtract * determinant_3D;

	}
	return Matrix4D();
}*/

Matrix4D Matrix4D::Inverse3D()
{
	printf("test_inverse\n");
	double determinant = Matrix3D_Determinent(*this);
	printf("determinant: %f\n", determinant);
	Matrix4D adjunct = Matrix3D_Cofactor(*this);
	printf("adjunct\n");
	adjunct.print();

	return adjunct / determinant;

}

Matrix4D Matrix4D::operator+(Matrix4D& that)
{
	Matrix4D addition = Matrix4D();
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			addition.matrix[row][col] = this->matrix[row][col] + that.matrix[row][col];
		}

	}
	return addition;
}

Matrix4D Matrix4D::operator-(Matrix4D& that)
{
	Matrix4D subtraction = Matrix4D();
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			subtraction.matrix[row][col] = this->matrix[row][col] - that.matrix[row][col];
		}

	}
	return subtraction;
}

Matrix4D Matrix4D::operator*(double scalar)
{
	Matrix4D multiply = Matrix4D();
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			multiply.matrix[row][col] = this->matrix[row][col] * scalar;
		}

	}
	return multiply;
}

Matrix4D Matrix4D::operator*(Matrix4D that)
{
	Matrix4D multiply = Matrix4D();
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			double temp = 0;
			for (int col2 = 0; col2 < 4; col2++) {
				temp += this->matrix[row][col2] * that.matrix[col2][col];
			}
			multiply.matrix[row][col] = temp;
		}
	}
	return multiply;
}

vector<double> Matrix4D::operator*(vector<double> that)
{
	vector<double> multiply (4,0);
	for (int row = 0; row < 4; row++) {
		double temp = 0;
		for (int col = 0; col < 4; col++) {
				temp += this->matrix[row][col] * that[col];
		}
		multiply[row] = temp;
	}
	return multiply;
}

Matrix4D Matrix4D::operator/(double scalar)
{
	scalar = pow(scalar, -1);
	return *this * scalar;
}

