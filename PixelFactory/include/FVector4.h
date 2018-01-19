#ifndef __FVECTOR4_H__
#define __FVECTOR4_H__

#include "Platform.h"
#include "FMathUtility.h"
#include "CoreDefines.h"

struct FVector4
{
public:
	/** Vector's X component. */
	float X;

	/** Vector's Y component. */
	float Y;

	/** Vector's Z component. */
	float Z;

	/** Vector's W component. */
	float W;

public:
	FORCEINLINE FVector4();

	FORCEINLINE FVector4(float InF);

	FORCEINLINE FVector4(float x, float y, float z, float w);


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

FORCEINLINE FVector4::FVector4()
	: X(0.0f), Y(0.0f), Z(0.0f), W(0.0)
{}

FORCEINLINE FVector4::FVector4(float InF)
	: X(InF), Y(InF), Z(InF), W(InF)
{}

FORCEINLINE FVector4::FVector4(float x, float y, float z, float w)
	: X(x), Y(y), Z(z), W(w)
{}



FORCEINLINE float& FVector4::operator[](int32 Index)
{
	check(Index >= 0 && Index < 4);
	if (Index == 0)
	{
		return X;
	}
	else if (Index == 1)
	{
		return Y;
	}
	else if (Index == 2)
	{
		return Z;
	}
	else
		return W;
}

FORCEINLINE float FVector4::operator[](int32 Index)const
{
	check(Index >= 0 && Index < 4);
	if (Index == 0)
	{
		return X;
	}
	else if (Index == 1)
	{
		return Y;
	}
	else if (Index == 2)
	{
		return Z;
	}
	else
		return W;
}

FORCEINLINE float & FVector4::Component(int32 Index)
{
	return (&X)[Index];
}

FORCEINLINE float FVector4::Component(int32 Index) const
{
	return (&X)[Index];
}

#endif
