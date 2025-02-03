#pragma once
class Vector3D
{
	private:
	public:
		double x;
		double y;
		double z;

		Vector3D();
		Vector3D(double, double, double);
		Vector3D(const Vector3D& original);;
		Vector3D operator+(Vector3D right);
		Vector3D& operator+=(Vector3D right);
		//Vector3D Addition (Vector3D);
		Vector3D& operator-=(Vector3D right);
		Vector3D operator-(Vector3D right);
		//Vector3D Subtraction (Vector3D);
		//static Vector3D Subtraction(Vector3D left, Vector3D right);
		Vector3D Scale (double);
		Vector3D& operator*=(double right);
		Vector3D operator*(double right);
		Vector3D& operator*=(Vector3D right);
		Vector3D operator*(Vector3D right);
		double Magnitude();
		double LengthSquared ();
		Vector3D Normalize ();
		Vector3D Linear_Interpolation (Vector3D,double);
		double DotProduct (Vector3D);
		Vector3D CrossProduct (Vector3D);
};

