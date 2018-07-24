#pragma once


namespace Math
{

	class Color;

	class Vector4
	{
	public:

		Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
		~Vector4() {}

		static Vector4 Zero() { return Vector4(); }
		static Vector4 One() { return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }
		static Vector4 Black() { return Vector4(0.0f, 0.0f, 0.0f, 1.0f); }
		static Vector4 Gray() { return Vector4(0.5f, 0.5f, 0.5f, 1.0f); }
		static Vector4 DarkGray() { return Vector4(0.25f, 0.25f, 0.25f, 1.0f); }
		static Vector4 White() { return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }
		static Vector4 LightRed() { return Vector4(1.0f, 0.5f, 0.5f, 1.0f); }
		static Vector4 Red() { return Vector4(1.0f, 0.0f, 0.0f, 1.0f); }
		static Vector4 Green() { return Vector4(0.0f, 1.0f, 0.0f, 1.0f); }
		static Vector4 Blue() { return Vector4(0.0f, 0.0f, 1.0f, 1.0f); }
		static Vector4 Yellow() { return Vector4(1.0f, 1.0f, 0.0f, 1.0f); }
		static Vector4 Orange() { return Vector4(1.0f, 0.5f, 0.0f, 1.0f); }
		static Vector4 Cyan() { return Vector4(0.0f, 1.0f, 1.0f, 1.0f); }
		static Vector4 Magenta() { return Vector4(1.0f, 0.0f, 1.0f, 1.0f); }

		//member variables
		float x;
		float y;
		float z;
		float w;
		//end of member variables

	public:

		Vector4& operator=(const Vector4& other);
		
		float Length() const;
		float LengthSquared() const;

		//comparison
		bool operator==(Vector4 other) const;
		bool operator!=(Vector4 other) const;
		bool IsZero() const;
		bool IsUnit() const;

		//manipulators
		void SetVector(float x, float y, float z, float w);
		void Clean(); //sets near-zero elements to zero
		void SetZero(); //sets all elements to zero
		void Normalize(); //sets to unit vector

						  //operators

						  //addition and subtraction

		Vector4 operator+(const Vector4& other) const;
		Vector4& operator+=(const Vector4& other);
		Vector4 operator-(const Vector4& other) const;
		Vector4& operator-=(const Vector4& other);

		//scalar multiplication
		Vector4 operator*(const float scalar) const;
		Vector4& operator*=(const float scalar);
		Vector4 operator/(const float scalar) const;
		Vector4& operator/=(const float scalar);

		//dot product
		float Dot(const Vector4& other) const;

		//useful defaults

		static Vector4 xAxis;
		static Vector4 yAxis;
		static Vector4 zAxis;
		static Vector4 wAxis;
		static Vector4 origin;
	};


}