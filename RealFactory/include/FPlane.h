#ifndef __FPLANE_H__
#define __FPLANE_H__

#include "FVector.h"
#include "FVector4.h"

struct FPlane : public FVector
{
public:
	float W;

public:
	/** Default constructor (no initialization). */
	FORCEINLINE FPlane();

	/**
	* Copy Constructor.
	*
	* @param P Plane to copy from.
	*/
	FORCEINLINE FPlane(const FPlane& P);

	/**
	* Constructor.
	*
	* @param V 4D vector to set up plane.
	*/
	FORCEINLINE FPlane(const FVector4& V);

	/**
	* Constructor.
	*
	* @param InX X-coefficient.
	* @param InY Y-coefficient.
	* @param InZ Z-coefficient.
	* @param InW W-coefficient.
	*/
	FORCEINLINE FPlane(float InX, float InY, float InZ, float InW);

	/**
	* Constructor.
	*
	* @param InNormal Plane Normal Vector.
	* @param InW Plane W-coefficient.
	*/
	FORCEINLINE FPlane(FVector InNormal, float InW);

	/**
	* Constructor.
	*
	* @param InBase Base point in plane.
	* @param InNormal Plane Normal Vector.
	*/
	FORCEINLINE FPlane(FVector InBase, const FVector &InNormal);

	/**
	* Constructor.
	*
	* @param A First point in the plane.
	* @param B Second point in the plane.
	* @param C Third point in the plane.
	*/
	FORCEINLINE FPlane(FVector A, FVector B, FVector C);
};

inline FPlane::FPlane(): FVector(0.0, 0.0, 0.0), W(0.0)
{
}

inline FPlane::FPlane(const FPlane& P)
{
	X = P.X; Y = P.Y; Z = P.Z; W = P.W;
}

inline FPlane::FPlane(const FVector4& V)
{
	X = V.X; Y = V.Y; Z = V.Z; W = V.W;
}

FORCEINLINE FPlane::FPlane(float InX, float InY, float InZ, float InW)
	: FVector(InX, InY, InZ)
	, W(InW)
{}


FORCEINLINE FPlane::FPlane(FVector InNormal, float InW)
	: FVector(InNormal), W(InW)
{}

FORCEINLINE FPlane::FPlane(FVector InBase, const FVector &InNormal)
	: FVector(InNormal)
	, W(InBase | InNormal)
{}

FORCEINLINE FPlane::FPlane(FVector A, FVector B, FVector C)
	: FVector(((B - A) ^ (C - A)).GetSafeNormal())
{
	W = A | (FVector)(*this);
}

#endif
