#ifndef __FMATRIX_H__
#define __FMATRIX_H__

#include "FVector.h"

struct FMatrix
{
public:
	union
	{
		float M[4][4];
	};

public:
	FORCEINLINE FMatrix();
	FORCEINLINE FMatrix(const FVector& InX, const FVector& InY, const FVector& InZ, const FVector& InW);

	FORCEINLINE void SetIndentiy();
};

FORCEINLINE FMatrix::FMatrix()
{
}

FORCEINLINE FMatrix::FMatrix(const FVector& InX, const FVector& InY, const FVector& InZ, const FVector& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = InX.W;
	M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = InY.W;
	M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = InZ.W;
	M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = InW.W;
}

FORCEINLINE void FMatrix::SetIndentiy()
{
	M[0][0] = 1.0;	M[0][1] = 0.0;  M[0][2] = 0.0;  M[0][3] = 0.0;
	M[1][0] = 0.0;	M[1][1] = 1.0;  M[1][2] = 0.0;  M[1][3] = 0.0;
	M[2][0] = 0.0;	M[2][1] = 0.0;  M[2][2] = 1.0;  M[2][3] = 0.0;
	M[3][0] = 0.0;	M[3][1] = 0.0;  M[3][2] = 0.0;  M[3][3] = 1.0;
}

#endif
