#include <cmath>
class Vec2
{
public:
	float x;
	float y;
	float w;
	float h;
	Vec2()
	{
		x = 0.0f;
		y = 0.0f;
		w = 0.0f;
		h = 0.0f;
	}

	Vec2(float a, float b)
	{
		x = a;
		y = b;
		w = 0.0f;
		h = 0.0f;
	}

	Vec2 operator+(const Vec2& v)
	{
		return Vec2(x + v.x, y + v.y);
	}

	Vec2 operator-(const Vec2& v)
	{
		return Vec2(x - v.x, y - v.y);
	}

	friend Vec2 operator*(float scaleFactor, const Vec2& other)
	{
		Vec2 result;

		result.x = scaleFactor * other.x;
		result.y = scaleFactor * other.y;

		return result;
	}

	friend Vec2 operator*(const Vec2& other, float scaleFactor)
	{
		Vec2 result;

		result.x = scaleFactor * other.x;
		result.y = scaleFactor * other.y;

		return result;
	}

	Vec2 operator/(const Vec2& other)
	{
		Vec2 result;

		result.x = x / other.x;
		result.y = y / other.y;

		return result;
	}

	Vec2 operator+=(const Vec2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vec2 operator-=(const Vec2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	float Dot(const Vec2& v)
	{
		return (x*v.x + y * v.y);
	}

	float Magnitude()
	{
		return sqrt(x*x + y * y);
	}

	void Normalize()
	{
		float Length = Magnitude();

		if (Length == 0)
			y = 1.f;

		x /= Length;
		y /= Length;
	}

};