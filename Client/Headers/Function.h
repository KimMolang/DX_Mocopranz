/*!
 * \file Function.h
 * \date 2015/12/06 2:44
 *
 * \author ±è¸íÁö
 * Contact: bluevill04@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#pragma once

#ifndef Function_h__
#define Function_h__

template<typename T>
static void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = NULL;
	}
}

template <typename T>
void Safe_Delete_Array(T& pointer)
{
	if (NULL != pointer)
	{
		delete[] pointer;
		pointer = NULL;
	}
}

template <typename T>
void Safe_Release(T& pointer)
{
	if (NULL != pointer)
	{
		pointer->Release();
		pointer = NULL;
	}
}

static D3DXVECTOR3 Change3DCoordTo2DCoord(const D3DXVECTOR3& _vCoordValue,
	const D3DXMATRIX* _matView,
	const D3DXMATRIX* _matProj)
{
	D3DXVECTOR3		v2DCoordValue;
	D3DXVECTOR3		vCoordValue = _vCoordValue;
	D3DXMATRIX		matView = *_matView;
	D3DXMATRIX		matProj = *_matProj;

	D3DXMATRIX	matResult = matView * matProj;

	D3DXVec3TransformCoord(&vCoordValue, &vCoordValue, &matResult);
	v2DCoordValue.x = ((vCoordValue.x * matProj._11) + 1.f) * (CLIENT_WINCX >> 1);
	v2DCoordValue.y = -(((vCoordValue.y * matProj._22) - 1.f) * (CLIENT_WINCY >> 1));
	v2DCoordValue.z = 0.f;

	return v2DCoordValue;
}

static D3DXVECTOR3 Change3DCoordTo2DCoord(const D3DXVECTOR3& _vCoordValue,
	const D3DXMATRIX& _matView,
	const D3DXMATRIX& _matProj)
{
	D3DXVECTOR3		v2DCoordValue;
	D3DXVECTOR3		vCoordValue = _vCoordValue;
	D3DXMATRIX		matView = _matView;
	D3DXMATRIX		matProj = _matProj;

	D3DXMATRIX	matResult = matView * matProj;

	D3DXVec3TransformCoord(&vCoordValue, &vCoordValue, &matResult);
	//v2DCoordValue.x = ((vCoordValue.x * matProj._11) + 1.f) * (CLIENT_WINCX >> 1);
	//v2DCoordValue.y = -(((vCoordValue.y * matProj._22) - 1.f) * (CLIENT_WINCY >> 1));
	v2DCoordValue.x = CLIENT_WINCX * (vCoordValue.x + 1.f) / 2.0f;
	v2DCoordValue.y = CLIENT_WINCY * (1.0f - ((vCoordValue.y + 1.f) / 2.f));
	v2DCoordValue.z = 0.f;

	return v2DCoordValue;
}

static float MakeDiagonalLine(const float _fFirst, const float _fSecond)
{
	return sqrt((_fFirst * _fFirst) + (_fSecond * _fSecond));
}

static float MakeDiagonalLine(const float _fFirst, const float _fSecond, const float _fThird)
{
	return sqrt((_fFirst * _fFirst)
		+ (_fSecond * _fSecond) + (_fThird * _fThird));
}

static float MakeDiagonalLine(D3DXVECTOR3 _vScale)
{
	return sqrt((_vScale.x * _vScale.x)
		+ (_vScale.y * _vScale.y) + (_vScale.z * _vScale.z));
}

#endif // Function_h__
