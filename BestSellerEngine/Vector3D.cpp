#include "Vector3D.h"
#include "math.h"

/*double x;
double y;
double z;
*/
Vector3D::Vector3D()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}				

Vector3D::Vector3D(double x,double y,double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D::Vector3D(const Vector3D& original) {
	this->x = original.x;
	this->y = original.y;
	this->z = original.z;
}

Vector3D& Vector3D::operator +=(Vector3D right) {
	this->x += right.x;
	this->y += right.y;
	this->z += right.z;
	return *this;
}

Vector3D Vector3D::operator + (Vector3D right) {
	Vector3D result = *this;
	result += right;
	return result;
}

//Vector3D Vector3D::Addition(Vector3D that)
//{
//	double x = this->x + that.x;
//	double y = this->y + that.y;
//	double z = this->z + that.z;
//	return Vector3D(x, y, z);
//}

Vector3D& Vector3D::operator -=(Vector3D right) {
	this->x -= right.x;
	this->y -= right.y;
	this->z -= right.z;
	return *this;
}

Vector3D Vector3D::operator - (Vector3D right) {
	Vector3D result = *this;
	result -= right;
	return result;
}

//Vector3D Vector3D::Subtraction(Vector3D that)
//{
//	double x = this->x - that.x;
//	double y = this->y - that.y;
//	double z = this->z - that.z;
//	return Vector3D(x,y,z);
//}
//
//Vector3D Vector3D::Subtraction(Vector3D left, Vector3D right) {
//	double x = left.x - right.x;
//	double y = left.y - right.y;
//	double z = left.z - right.z;
//
//	return Vector3D(x, y, z);
//}

Vector3D Vector3D::Scale(double scaleFactor)
{
	double x = this->x * scaleFactor;
	double y = this->y * scaleFactor;
	double z = this->z * scaleFactor;
	return Vector3D(x, y, z);
}


Vector3D& Vector3D::operator *=(double right) {
	x *= right;
	y *= right;
	z *= right;
	return *this;
}

Vector3D Vector3D::operator * (double right) {
	Vector3D result = *this;
	result *= right;
	return result;
}

Vector3D& Vector3D::operator *=(Vector3D right) {
	x *= right.x;
	y *= right.y;
	z *= right.z;
	return *this;
}

Vector3D Vector3D::operator * (Vector3D right) {
	Vector3D result = *this;
	result *= right;
	return result;
}


/// <summary>Returns the length of this Vector3D squard.</summary>
/// <returns>The length for of this Vector3D squared.</returns>
double Vector3D::Magnitude()
{
	double x = this->x * this->x;
	double y = this->y * this->y;
	double z = this->z * this->z;
	return pow(x + y + z,.5);
}

/// <summary>Returns the length of this Vector3D squard.</summary>
/// <returns>The length for of this Vector3D squared.</returns>
double Vector3D::LengthSquared()
{
	double x = this->x * this->x;
	double y = this->y * this->y;
	double z = this->z * this->z;	
	return x + y + z;
}

/// <summary>Returns a unit vector with the same direction as this Vector3D.</summary>
/// <returns>A unit vector.</returns>
Vector3D Vector3D::Normalize()
{
	Vector3D result = *this * (1 / this->Magnitude());
	return result;
}

Vector3D Vector3D::Linear_Interpolation(Vector3D destination, double interpolationValue)
{
	// a + (b - a) * t 
	Vector3D vectorBetween = destination - *this;	// b-a
	vectorBetween = vectorBetween.Scale(interpolationValue);	// result * t

	vectorBetween += *this;	// result + a

	return vectorBetween;
}

double Vector3D::DotProduct(Vector3D right)
{
	double result = (this->x * right.x) + (this->y * right.y) + (this->z * right.z);
	return result;
}

Vector3D Vector3D::CrossProduct(Vector3D that)
{
	Vector3D result = Vector3D();

	result.x = (this->y * that.z) - (this->z * that.y);
	result.y = (this->z * that.x) - (this->x * that.z);
	result.z = (this->x * that.y) - (this->y * that.x);

	return result;
}
