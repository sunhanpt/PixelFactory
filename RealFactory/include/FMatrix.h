#ifndef __FMATRIX_H__
#define __FMATRIX_H__
/************************************************************************/
/* Matrix结构及相关操作
** 后期考虑使用sse指令加速计算
*/
/************************************************************************/
#include "FPlane.h"
#include "Axis.h"

struct FMatrix
{
public:
	union
	{
		float M[4][4];
	};

public:
	static const FMatrix Identity;

public:
	FORCEINLINE FMatrix();
	FORCEINLINE FMatrix(const FVector& InX, const FVector& InY, const FVector& InZ, const FVector& InW);
	FORCEINLINE FMatrix(const FPlane& InX, const FPlane& InY, const FPlane& InZ, const FPlane& InW);

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
	FORCEINLINE FVector4 TransformPosition(const FVector &V) const;

	// Transpose.

	FORCEINLINE FMatrix GetTransposed() const;

	// @return determinant of this matrix.

	inline float Determinant() const;

	/** Fast path, doesn't check for nil matrices in final release builds */
	inline FMatrix InverseFast() const;

	/** Fast path, and handles nil matrices. */
	inline FMatrix Inverse() const;

	/**
	* get axis of this matrix scaled by the scale of the matrix
	*
	* @param i index into the axis of the matrix
	* @ return vector of the axis
	*/
	inline FVector GetScaledAxis(EAxis::Type Axis) const;

	/**
	* get axes of this matrix scaled by the scale of the matrix
	*
	* @param X axes returned to this param
	* @param Y axes returned to this param
	* @param Z axes returned to this param
	*/
	inline void GetScaledAxes(FVector &X, FVector &Y, FVector &Z) const;

	// Frustum plane extraction.
	/** @param OutPlane the near plane of the Frustum of this matrix */
	FORCEINLINE bool GetFrustumNearPlane(FPlane& OutPlane) const;

	/** @param OutPlane the far plane of the Frustum of this matrix */
	FORCEINLINE bool GetFrustumFarPlane(FPlane& OutPlane) const;

	/** @param OutPlane the left plane of the Frustum of this matrix */
	FORCEINLINE bool GetFrustumLeftPlane(FPlane& OutPlane) const;

	/** @param OutPlane the right plane of the Frustum of this matrix */
	FORCEINLINE bool GetFrustumRightPlane(FPlane& OutPlane) const;

	/** @param OutPlane the top plane of the Frustum of this matrix */
	FORCEINLINE bool GetFrustumTopPlane(FPlane& OutPlane) const;

	/** @param OutPlane the bottom plane of the Frustum of this matrix */
	FORCEINLINE bool GetFrustumBottomPlane(FPlane& OutPlane) const;

	/**
	* Utility for mirroring this transform across a certain plane, and flipping one of the axis as well.
	*/
	inline void Mirror(EAxis::Type MirrorAxis, EAxis::Type FlipAxis);
};

struct FLookAtMatrix : FMatrix
{
	/**
	* Creates a view matrix given an eye position, a position to look at, and an up vector.
	* This does the same thing as D3DXMatrixLookAtLH.
	*/
	FLookAtMatrix(const FVector& EyePosition, const FVector& LookAtPosition, const FVector& UpVector);
};

// very high quality 4x4 matrix inverse
static inline void Inverse4x4(double* dst, const float* src)
{
	const double s0 = (double)(src[0]); const double s1 = (double)(src[1]); const double s2 = (double)(src[2]); const double s3 = (double)(src[3]);
	const double s4 = (double)(src[4]); const double s5 = (double)(src[5]); const double s6 = (double)(src[6]); const double s7 = (double)(src[7]);
	const double s8 = (double)(src[8]); const double s9 = (double)(src[9]); const double s10 = (double)(src[10]); const double s11 = (double)(src[11]);
	const double s12 = (double)(src[12]); const double s13 = (double)(src[13]); const double s14 = (double)(src[14]); const double s15 = (double)(src[15]);

	double inv[16];
	inv[0] = s5 * s10 * s15 - s5 * s11 * s14 - s9 * s6 * s15 + s9 * s7 * s14 + s13 * s6 * s11 - s13 * s7 * s10;
	inv[1] = -s1 * s10 * s15 + s1 * s11 * s14 + s9 * s2 * s15 - s9 * s3 * s14 - s13 * s2 * s11 + s13 * s3 * s10;
	inv[2] = s1 * s6  * s15 - s1 * s7  * s14 - s5 * s2 * s15 + s5 * s3 * s14 + s13 * s2 * s7 - s13 * s3 * s6;
	inv[3] = -s1 * s6  * s11 + s1 * s7  * s10 + s5 * s2 * s11 - s5 * s3 * s10 - s9  * s2 * s7 + s9  * s3 * s6;
	inv[4] = -s4 * s10 * s15 + s4 * s11 * s14 + s8 * s6 * s15 - s8 * s7 * s14 - s12 * s6 * s11 + s12 * s7 * s10;
	inv[5] = s0 * s10 * s15 - s0 * s11 * s14 - s8 * s2 * s15 + s8 * s3 * s14 + s12 * s2 * s11 - s12 * s3 * s10;
	inv[6] = -s0 * s6  * s15 + s0 * s7  * s14 + s4 * s2 * s15 - s4 * s3 * s14 - s12 * s2 * s7 + s12 * s3 * s6;
	inv[7] = s0 * s6  * s11 - s0 * s7  * s10 - s4 * s2 * s11 + s4 * s3 * s10 + s8  * s2 * s7 - s8  * s3 * s6;
	inv[8] = s4 * s9  * s15 - s4 * s11 * s13 - s8 * s5 * s15 + s8 * s7 * s13 + s12 * s5 * s11 - s12 * s7 * s9;
	inv[9] = -s0 * s9  * s15 + s0 * s11 * s13 + s8 * s1 * s15 - s8 * s3 * s13 - s12 * s1 * s11 + s12 * s3 * s9;
	inv[10] = s0 * s5  * s15 - s0 * s7  * s13 - s4 * s1 * s15 + s4 * s3 * s13 + s12 * s1 * s7 - s12 * s3 * s5;
	inv[11] = -s0 * s5  * s11 + s0 * s7  * s9 + s4 * s1 * s11 - s4 * s3 * s9 - s8  * s1 * s7 + s8  * s3 * s5;
	inv[12] = -s4 * s9  * s14 + s4 * s10 * s13 + s8 * s5 * s14 - s8 * s6 * s13 - s12 * s5 * s10 + s12 * s6 * s9;
	inv[13] = s0 * s9  * s14 - s0 * s10 * s13 - s8 * s1 * s14 + s8 * s2 * s13 + s12 * s1 * s10 - s12 * s2 * s9;
	inv[14] = -s0 * s5  * s14 + s0 * s6  * s13 + s4 * s1 * s14 - s4 * s2 * s13 - s12 * s1 * s6 + s12 * s2 * s5;
	inv[15] = s0 * s5  * s10 - s0 * s6  * s9 - s4 * s1 * s10 + s4 * s2 * s9 + s8  * s1 * s6 - s8  * s2 * s5;

	double det = s0 * inv[0] + s1 * inv[4] + s2 * inv[8] + s3 * inv[12];
	if (det != 0.0)
	{
		det = 1.0 / det;
	}
	for (int i = 0; i < 16; i++)
	{
		dst[i] = inv[i] * det;
	}
}


#include "FMatrix.inl"

#endif
