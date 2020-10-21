#pragma once
#include <immintrin.h>
namespace mat
{
	class vec4
	{
	public:
		vec4(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {};
		float x, y, z, w;
		mat::vec4 operator +(mat::vec4 other)
		{
			return vec4({ x + other.x,y + other.y,z + other.z,w + other.w });
		}

		mat::vec4 operator -()
		{
			return vec4(-x, -y, -z, -w);
		}
		mat::vec4 operator -(mat::vec4 other)
		{
			return *this + (-other);
		}


	};
}