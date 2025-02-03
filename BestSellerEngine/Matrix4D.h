#pragma once

#include <vector>
using std::vector;

class Matrix4D
{
	public:
		vector<vector<double>> matrix;

		Matrix4D();
		Matrix4D(double value);
		bool operator==(const Matrix4D& that);
		bool operator!=(const Matrix4D& that);
		double& operator()(const unsigned& row, const unsigned& col);
		void print();

		Matrix4D Identity();
		Matrix4D Transpose();
		Matrix4D Inverse3D();
		Matrix4D operator+(Matrix4D&);
		Matrix4D operator-(Matrix4D&);
		Matrix4D operator*(double);
		Matrix4D operator*(Matrix4D);
		vector<double> operator*(vector<double>);
		Matrix4D operator/(double);
};

