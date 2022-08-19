#include "Matrix.h"

Vector Matrix::GetForward()
{
	return { M[2][0], M[2][1],M[2][2] };
}

Vector Matrix::GetUp()
{
	return { M[1][0], M[1][1],M[1][2] };
}

Vector Matrix::GetRight()
{
	return { M[0][0], M[0][1],M[0][2] };
}

Vector Matrix::GetPos()
{
	return { M[3][0], M[3][1],M[3][2] };
}
