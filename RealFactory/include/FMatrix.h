#ifndef __FMATRIX_H__
#define __FMATRIX_H__
/************************************************************************/
/* Matrix结构及相关操作
** 后期考虑使用sse指令加速计算
*/
/************************************************************************/
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
	FORCEINLINE FMatrix operator* (const FMatrix& Other) const;
	FORCEINLINE void operator*=(const FMatrix& Other);
	FORCEINLINE FMatrix operator+ (const FMatrix& Other) const;
	FORCEINLINE void operator+=(const FMatrix& Other);
	FORCEINLINE FMatrix operator* (float Other) const;
	FORCEINLINE void operator*=(float Other);
	FORCEINLINE bool operator==(const FMatrix& Other) const;
	inline bool Equals(const FMatrix& Other, float Tolerance = KINDA_SMALL_NUMBER) const;
	inline bool operator!=(const FMatrix& Other) const;
	FORCEINLINE FVector4 TransformFVector4(const FVector4& V) const; // vector4 * matrix
};

FORCEINLINE FMatrix::FMatrix()
{
	memset(M, 0, sizeof(float) * 4 * 4);
}

FORCEINLINE FMatrix::FMatrix(const FVector& InX, const FVector& InY, const FVector& InZ, const FVector& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = 0.0;
	M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = 0.0;
	M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = 0.0;
	M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = 1.0;
}

FORCEINLINE void FMatrix::SetIndentiy()
{
	M[0][0] = 1.0;	M[0][1] = 0.0;  M[0][2] = 0.0;  M[0][3] = 0.0;
	M[1][0] = 0.0;	M[1][1] = 1.0;  M[1][2] = 0.0;  M[1][3] = 0.0;
	M[2][0] = 0.0;	M[2][1] = 0.0;  M[2][2] = 1.0;  M[2][3] = 0.0;
	M[3][0] = 0.0;	M[3][1] = 0.0;  M[3][2] = 0.0;  M[3][3] = 1.0;
}

inline FMatrix FMatrix::operator*(const FMatrix & Other) const
{
	FMatrix Reslut;
	for(int i = 0; i < 4; i++)
		for(int k = 0; k < 4; k++)
			for (int j = 0; j < 4; j++)
			{
				Reslut.M[i][j] += M[i][k] * Other.M[k][j];
			}
	return Reslut;
}

inline void FMatrix::operator*=(const FMatrix & Other)
{
	*this = *this * Other;

}

inline FMatrix FMatrix::operator+(const FMatrix & Other) const
{
	FMatrix Reslut;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			Reslut.M[i][j] = M[i][j] + Other.M[i][j];
	return Reslut;
}

inline void FMatrix::operator+=(const FMatrix & Other)
{
	*this = *this + Other;
}

inline FMatrix FMatrix::operator*(float Other) const
{
	FMatrix Reslut;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			Reslut.M[i][j] = M[i][j] * Other;
	return Reslut;
}

inline void FMatrix::operator*=(float Other)
{
	*this = *this * Other;
}

inline bool FMatrix::operator==(const FMatrix & Other) const
{
	for (int32 X = 0; X < 4; X++)
		for (int32 Y = 0; Y < 4; Y++)
			if (M[X][Y] != Other.M[X][Y]){
				return false;
			}
	return true;
}

inline bool FMatrix::Equals(const FMatrix & Other, float Tolerance) const
{
	for (int32 X = 0; X < 4; X++)
	{
		for (int32 Y = 0; Y < 4; Y++)
		{
			if (FMath::Abs(M[X][Y] - Other.M[X][Y]) > Tolerance)
			{
				return false;
			}
		}
	}

	return true;
}

inline bool FMatrix::operator!=(const FMatrix & Other) const
{
	return !(*this == Other);
}



#endif
