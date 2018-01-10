#ifndef __FVECTOR_H__
#define __FVECTOR_H__

#include "Platform.h"
#include "FMathUtility.h"
#include "CoreDefines.h"

struct FVector
{
public:
	/** Vector's X component. */
	float X;

	/** Vector's Y component. */
	float Y;

	/** Vector's Z component. */
	float Z;

public:
	/** A zero vector (0,0,0) */
	static const FVector ZeroVector;

	/** One vector (1,1,1) */
	static const FVector OneVector;

	/** World up vector (0,0,1) */
	static const FVector UpVector;

	/** Unreal forward vector (1,0,0) */
	static const FVector ForwardVector;

	/** Unreal right vector (0,1,0) */
	static const FVector RightVector;

public:
	FORCEINLINE FVector();

	FORCEINLINE FVector(float InF);

	FORCEINLINE FVector(float x, float y, float z);

	//explicit FORCEINLINE FVector(const FVector2D V, float InZ);

	//FORCEINLINE FVector(const FVector4& V);

	/**
	* Calculate cross product between this and another vector.
	*
	* @param V The other vector.
	* @return The cross product.
	*/
	FORCEINLINE FVector operator^(const FVector& V) const;

	/**
	* Calculate the cross product of two vectors.
	*
	* @param A The first vector.
	* @param B The second vector.
	* @return The cross product.
	*/
	FORCEINLINE static FVector CrossProduct(const FVector& A, const FVector& B);

	/**
	* Calculate the dot product between this and another vector.
	*
	* @param V The other vector.
	* @return The dot product.
	*/
	FORCEINLINE float operator|(const FVector& V) const;

	/**
	* Calculate the dot product of two vectors.
	*
	* @param A The first vector.
	* @param B The second vector.
	* @return The dot product.
	*/
	FORCEINLINE static float DotProduct(const FVector& A, const FVector& B);

	/**
	* Gets the result of component-wise addition of this and another vector.
	*
	* @param V The vector to add to this.
	* @return The result of vector addition.
	*/
	FORCEINLINE FVector operator+(const FVector& V) const;

	/**
	* Gets the result of component-wise subtraction of this by another vector.
	*
	* @param V The vector to subtract from this.
	* @return The result of vector subtraction.
	*/
	FORCEINLINE FVector operator-(const FVector& V) const;

	/**
	* Gets the result of subtracting from each component of the vector.
	*
	* @param Bias How much to subtract from each component.
	* @return The result of subtraction.
	*/
	FORCEINLINE FVector operator-(float Bias) const;

	/**
	* Gets the result of adding to each component of the vector.
	*
	* @param Bias How much to add to each component.
	* @return The result of addition.
	*/
	FORCEINLINE FVector operator+(float Bias) const;

	/**
	* Gets the result of scaling the vector (multiplying each component by a value).
	*
	* @param Scale What to multiply each component by.
	* @return The result of multiplication.
	*/
	FORCEINLINE FVector operator*(float Scale) const;

	/**
	* Gets the result of dividing each component of the vector by a value.
	*
	* @param Scale What to divide each component by.
	* @return The result of division.
	*/
	FVector operator/(float Scale) const;

	/**
	* Gets the result of component-wise multiplication of this vector by another.
	*
	* @param V The vector to multiply with.
	* @return The result of multiplication.
	*/
	FORCEINLINE FVector operator*(const FVector& V) const;

	/**
	* Gets the result of component-wise division of this vector by another.
	*
	* @param V The vector to divide by.
	* @return The result of division.
	*/
	FORCEINLINE FVector operator/(const FVector& V) const;

	// Binary comparison operators.

	/**
	* Check against another vector for equality.
	*
	* @param V The vector to check against.
	* @return true if the vectors are equal, false otherwise.
	*/
	bool operator==(const FVector& V) const;

	/**
	* Check against another vector for inequality.
	*
	* @param V The vector to check against.
	* @return true if the vectors are not equal, false otherwise.
	*/
	bool operator!=(const FVector& V) const;

	/**
	* Check against another vector for equality, within specified error limits.
	*
	* @param V The vector to check against.
	* @param Tolerance Error tolerance.
	* @return true if the vectors are equal within tolerance limits, false otherwise.
	*/
	bool Equals(const FVector& V, float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	* Checks whether all components of this vector are the same, within a tolerance.
	*
	* @param Tolerance Error tolerance.
	* @return true if the vectors are equal within tolerance limits, false otherwise.
	*/
	bool AllComponentsEqual(float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	* Get a negated copy of the vector.
	*
	* @return A negated copy of the vector.
	*/
	FORCEINLINE FVector operator-() const;

	/**
	* Adds another vector to this.
	* Uses component-wise addition.
	*
	* @param V Vector to add to this.
	* @return Copy of the vector after addition.
	*/
	FORCEINLINE FVector operator+=(const FVector& V);

	/**
	* Subtracts another vector from this.
	* Uses component-wise subtraction.
	*
	* @param V Vector to subtract from this.
	* @return Copy of the vector after subtraction.
	*/
	FORCEINLINE FVector operator-=(const FVector& V);

	/**
	* Scales the vector.
	*
	* @param Scale Amount to scale this vector by.
	* @return Copy of the vector after scaling.
	*/
	FORCEINLINE FVector operator*=(float Scale);

	/**
	* Divides the vector by a number.
	*
	* @param V What to divide this vector by.
	* @return Copy of the vector after division.
	*/
	FVector operator/=(float V);

	/**
	* Multiplies the vector with another vector, using component-wise multiplication.
	*
	* @param V What to multiply this vector with.
	* @return Copy of the vector after multiplication.
	*/
	FVector operator*=(const FVector& V);

	/**
	* Divides the vector by another vector, using component-wise division.
	*
	* @param V What to divide vector by.
	* @return Copy of the vector after division.
	*/
	FVector operator/=(const FVector& V);

	/**
	* Gets specific component of the vector.
	*
	* @param Index the index of vector component
	* @return reference to component.
	*/
	float& operator[](int32 Index);

	/**
	* Gets specific component of the vector.
	*
	* @param Index the index of vector component
	* @return Copy of the component.
	*/
	float operator[](int32 Index)const;

	/**
	* Gets a specific component of the vector.
	*
	* @param Index The index of the component required.
	*
	* @return Reference to the specified component.
	*/
	float& Component(int32 Index);

	/**
	* Gets a specific component of the vector.
	*
	* @param Index The index of the component required.
	* @return Copy of the specified component.
	*/
	float Component(int32 Index) const;
};

FORCEINLINE FVector::FVector()
	: X(0.0f), Y(0.0f), Z(0.0f)
{}

FORCEINLINE FVector::FVector(float InF)
	: X(InF), Y(InF), Z(InF)
{}

FORCEINLINE FVector::FVector(float x, float y, float z)
	: X(x), Y(y), Z(z)
{}

FORCEINLINE FVector FVector::operator^(const FVector& V) const
{
	return FVector
	(
		Y * V.Z - Z * V.Y,
		Z * V.X - X * V.Z,
		X * V.Y - Y * V.X
	);
}

FORCEINLINE FVector FVector::CrossProduct(const FVector& A, const FVector& B)
{
	return A ^ B;
}

FORCEINLINE float FVector::operator|(const FVector& V) const
{
	return X * V.X + Y * V.Y + Z * V.Z;
}

FORCEINLINE float FVector::DotProduct(const FVector& A, const FVector& B)
{
	return A | B;
}

FORCEINLINE FVector FVector::operator+(const FVector& V) const
{
	return FVector(X + V.X, Y + V.Y, Z + V.Z);
}

FORCEINLINE FVector FVector::operator-(const FVector& V) const
{
	return FVector(X - V.X, Y - V.Y, Z - V.Z);
}

FORCEINLINE FVector FVector::operator-(float Bias) const
{
	return FVector(X - Bias, Y - Bias, Z - Bias);
}

FORCEINLINE FVector FVector::operator+(float Bias) const
{
	return FVector(X + Bias, Y + Bias, Z + Bias);
}

FORCEINLINE FVector FVector::operator*(float Scale) const
{
	return FVector(X * Scale, Y * Scale, Z * Scale);
}

FORCEINLINE FVector FVector::operator/(float Scale) const
{
	const float RScale = 1.f / Scale;
	return FVector(X * RScale, Y * RScale, Z * RScale);
}

FORCEINLINE FVector FVector::operator*(const FVector& V) const
{
	return FVector(X * V.X, Y * V.Y, Z * V.Z);
}

FORCEINLINE FVector FVector::operator/(const FVector& V) const
{
	return FVector(X / V.X, Y / V.Y, Z / V.Z);
}

FORCEINLINE bool FVector::operator==(const FVector& V) const
{
	return X == V.X && Y == V.Y && Z == V.Z;
}

FORCEINLINE bool FVector::operator!=(const FVector& V) const
{
	return X != V.X || Y != V.Y || Z != V.Z;
}

FORCEINLINE bool FVector::Equals(const FVector& V, float Tolerance) const
{
	return FMath::Abs(X - V.X) <= Tolerance && FMath::Abs(Y - V.Y) <= Tolerance && FMath::Abs(Z - V.Z) <= Tolerance;
}

FORCEINLINE bool FVector::AllComponentsEqual(float Tolerance) const
{
	return FMath::Abs(X - Y) <= Tolerance && FMath::Abs(X - Z) <= Tolerance && FMath::Abs(Y - Z) <= Tolerance;
}


FORCEINLINE FVector FVector::operator-() const
{
	return FVector(-X, -Y, -Z);
}


FORCEINLINE FVector FVector::operator+=(const FVector& V)
{
	X += V.X; Y += V.Y; Z += V.Z;
	return *this;
}

FORCEINLINE FVector FVector::operator-=(const FVector& V)
{
	X -= V.X; Y -= V.Y; Z -= V.Z;
	return *this;
}

FORCEINLINE FVector FVector::operator*=(float Scale)
{
	X *= Scale; Y *= Scale; Z *= Scale;
	return *this;
}

FORCEINLINE FVector FVector::operator/=(float V)
{
	const float RV = 1.f / V;
	X *= RV; Y *= RV; Z *= RV;
	return *this;
}

FORCEINLINE FVector FVector::operator*=(const FVector& V)
{
	X *= V.X; Y *= V.Y; Z *= V.Z;
	return *this;
}

FORCEINLINE FVector FVector::operator/=(const FVector& V)
{
	X /= V.X; Y /= V.Y; Z /= V.Z;
	return *this;
}

FORCEINLINE float& FVector::operator[](int32 Index)
{
	check(Index >= 0 && Index < 3);
	if (Index == 0)
	{
		return X;
	}
	else if (Index == 1)
	{
		return Y;
	}
	else
	{
		return Z;
	}
}

FORCEINLINE float FVector::operator[](int32 Index)const
{
	check(Index >= 0 && Index < 3);
	if (Index == 0)
	{
		return X;
	}
	else if (Index == 1)
	{
		return Y;
	}
	else
	{
		return Z;
	}
}

FORCEINLINE float & FVector::Component(int32 Index)
{
	return (&X)[Index];
}

FORCEINLINE float FVector::Component(int32 Index) const
{
	return (&X)[Index];
}

#endif
