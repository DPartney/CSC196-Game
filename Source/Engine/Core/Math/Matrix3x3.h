#pragma once
#include "Vector3.h"
#include "Vector2.h"

namespace kiko {
	class Matrix3x3
	{
	public:
		vec3 rows[3];
		// [row][column]
		// rows[0] = vec3{ 0, 0 }
		// rows[1] = vec3{ 0, 0 }

		Matrix3x3() = default;
		Matrix3x3(const vec3& row1, const vec3& row2, const vec3 row3)
		{
			rows[0] = row1;
			rows[1] = row2;
			rows[2] = row3;
		}

		vec3  operator [] (size_t index) const { return rows[index]; }
		vec3& operator [] (size_t index) { return rows[index]; }

		vec3 operator * (const vec3& v);
		Matrix3x3 operator * (const Matrix3x3& mx);

		static Matrix3x3 CreateScale(const vec2& scale);
		static Matrix3x3 CreateScale(float scale);
		static Matrix3x3 CreateRotation(float radians);

		static Matrix3x3 CreateIdentity();
	};

	inline vec3 Matrix3x3::operator*(const vec3& v)
	{
		vec3 result;
		result.x = rows[0][0] * v.x + rows[0][1] * v.y;
		result.x = rows[1][0] * v.x + rows[1][1] * v.y;

		return result;
	}

	inline Matrix3x3 Matrix3x3::operator*(const Matrix3x3& mx)
	{
		Matrix3x3 result;
		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0];
		result[0][1] = rows[0][0] * mx[0][1] + rows[0][1] * mx[1][1];
		result[1][0] = rows[1][0] * mx[0][0] + rows[1][1] * mx[1][0];
		result[1][1] = rows[1][0] * mx[0][1] + rows[1][1] * mx[1][1];

		return result;
	}

	inline Matrix3x3 Matrix3x3::CreateIdentity()
	{
		return
		{
			{ 1, 0, 0 },
			{ 0, 1, 0},
			{ 0, 0, 1}
		};
	}

	inline Matrix3x3 Matrix3x3::CreateScale(const vec2& scale)
	{
		Matrix3x3 mx = CreateIdentity();
		mx[0][0] = scale.x;
		mx[1][1] = scale.y;

		return mx;
	}

	inline Matrix3x3 Matrix3x3::CreateScale(float scale)
	{
		Matrix3x3 mx = CreateIdentity();
		mx[0][0] = scale;
		mx[1][1] = scale;

		return mx;
	}

	inline Matrix3x3 Matrix3x3::CreateRotation(float radians)
	{
		Matrix3x3 mx = CreateIdentity();
		float c = cos(radians);
		float s = sin(radians);

		mx[0][0] = c; mx[0][1] = -s;
		mx[1][0] = s; mx[1][1] = c;

		return mx;
	}

	using mat3 = Matrix3x3;
}