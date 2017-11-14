#pragma once
struct Vector {
	float x, y, z;
	Vector(float x = 0, float y = 0, float z = 0)
		: x(x), y(y), z(z)
	{

	}

	Vector operator+(const Vector& other) {
		float resX = x + other.x, resY = y + other.y, resZ = z + other.z;
		return Vector(resX, resY, resZ);
	}


	Vector operator-(const Vector& other) {
		float resX = x - other.x, resY = y - other.y, resZ = z - other.z;
		return Vector(resX, resY, resZ);
	}

	Vector operator/(const float& factor) {
		if (factor == 0)
			return Vector(x, y, z);
		float resX = x / factor, resY = y / factor, resZ = z / factor;
		return Vector(resX, resY, resZ);
	}

	float Vector::Dot(const Vector& b) const
	{
		return (x*b.x + y*b.y + z*b.z);
	}

	float LengthSqr(void) const
	{
		return (x*x + y*y + z*z);
	}

	bool IsEmpty() {
		return x == 0 && y == 0 && z == 0;
	}

};