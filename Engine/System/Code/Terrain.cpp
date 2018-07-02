#include "stdafx.h"
#include "Terrain.h"


BEGIN(Engine)


Terrain::Terrain()
	: m_pVtxBuf(nullptr)
	, m_pIdxBuf(nullptr)

	, m_pHeightMapTypeInfoArray(nullptr)
{

}

Terrain::Terrain(const Terrain &)
{

}


Terrain::~Terrain()
{
	Release();
}

HRESULT Terrain::Init(const std::wstring& _wstrPath)
{
	CHECK_FAILED_RETURN(LoadHeightMap(_wstrPath));
	NormalizeHeightMap();

	CHECK_FAILED_RETURN(Init_Vtx());
	CHECK_FAILED_RETURN(Init_Idx());

	return S_OK;
}

void Terrain::Update()
{
}

void Terrain::Render()
{
}

void Terrain::Release()
{
	::Safe_Delete_Array(m_pHeightMapTypeInfoArray);
}

HRESULT Terrain::LoadHeightMap(const std::wstring & _wstrPath)
{
	// Open the height map file in binary.
	// Only-Read & Birary ���� ���̸� ������ ���ϴ�.
	FILE* pFile = nullptr;
	if (fopen_s(&pFile, _wstrPath.c_str, "rb") != 0)
	{
		return E_FAIL;
	}

	// Read in the file header.
	BITMAPFILEHEADER bitmapFileHeader;
	if (fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, pFile) != 1)
	{
		return E_FAIL;
	}

	// Read in the bitmap info header.
	BITMAPINFOHEADER bitmapInfoHeader;
	if (fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile) != 1)
	{
		return E_FAIL;
	}

	// Save the dimensions of the terrain.
	m_iWidth = bitmapInfoHeader.biWidth;
	m_iHeight = bitmapInfoHeader.biHeight;

	// Calculate the size of the bitmap image data.
	int iImageSize = m_iWidth * m_iHeight * 3; // 3 : Components num -> RGB

	// Allocate memory for the bitmap image data.
	unsigned __int8* pBitMapImageDataArray
		= new unsigned __int8[iImageSize];

	// Move to the beginning of the bitmap data.
	// ��Ʈ�� �������� ���� �κ����� �̵��մϴ�.
	fseek(pFile, bitmapFileHeader.bfOffBits, SEEK_SET);

	// Read in the bitmap image data.
	if (fread(pBitMapImageDataArray, 1, iImageSize, pFile) != iImageSize)
	{
		return E_FAIL;
	}

	// Close the file.
	if (fclose(pFile) != 0)
	{
		return E_FAIL;
	}

	// Create the structure to hold the height map data.
	// ���� �� �����͸� ������ ����ü�� ���Ҵϴ�.
	m_pHeightMapTypeInfoArray
		= new HeightMapType[m_iWidth * m_iHeight];

	// Initialize the position in the image data buffer.
	int k = 0;

	for (int j = 0; j < m_iHeight; ++j)
	{
		for (int i = 0; i < m_iWidth; ++i)
		{
			unsigned __int8 height = pBitMapImageDataArray[k];

			int iIndex = (m_iHeight * j) + i;

			m_pHeightMapTypeInfoArray[iIndex].x = (float)i;
			m_pHeightMapTypeInfoArray[iIndex].y = (float)height;
			m_pHeightMapTypeInfoArray[iIndex].z = (float)j;

			// Increment the index into the bitmap(k) by three
			// since we only need one of the color values(red, green, or blue) to be used as the grey scale value.
			k += 3;
		}
	}

	// Release the bitmap image data.
	::Safe_Delete_Array(pBitMapImageDataArray);


	return S_OK;
}

void Terrain::NormalizeHeightMap()
{
	// The next new function is NormalizeHeightMap.
	// All it does is it goes through the terrain
	// and divides each height value by 15
	// so that the terrain doesn't look too spikey.
	// Generally its better just to do this work
	// on the height map before loading it in.

	for (int j = 0; j < m_iHeight; ++j)
	{
		for (int i = 0; i < m_iWidth; ++i)
		{
			m_pHeightMapTypeInfoArray[(m_iHeight * j) + 1].y /= 15.0f;
		}
	}
}

HRESULT Terrain::Init_Vtx()
{
	// http://www.rastertek.com/tertut01.html

	return S_OK;
}

HRESULT Terrain::Init_Idx()
{
	return S_OK;
}


END