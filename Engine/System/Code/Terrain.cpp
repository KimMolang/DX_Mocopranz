#include "stdafx.h"
#include "Terrain.h"

BEGIN(Engine)


Terrain::Terrain()
	: m_iWidth(0)
	, m_iHeight(0)

	, m_pHeightMapTypeInfoArray(nullptr)
{

}


Terrain::~Terrain()
{
	Release();
}

Terrain* Terrain::Create
(
	const int _iCntX
	, const int _iCntY
	, const char* _Path /*= nullptr*/
)
{
	Terrain* pComponent = new Terrain();
	if (FAILED(pComponent->Init(_iCntX, _iCntY, _Path)))
		::Safe_Delete(pComponent);

	return pComponent;
}

HRESULT Terrain::Init
(
	const int _iCntX
	, const int _iCntY
	, const char* _Path /*= nullptr*/
)
{
	if (_Path)
	{
		CHECK_FAILED_RETURN(LoadHeightMap(_Path), E_FAIL);
		NormalizeHeightMap();
	}

	CHECK_FAILED_RETURN(Init_Buffer(_iCntX, _iCntY), E_FAIL);

	CreateRasterizerState();

	return S_OK;
}

void Terrain::Update()
{
}

void Terrain::Render()
{
	if (nullptr == m_pVtxBuffer)
		return;

	ID3D11DeviceContext* pDeviceContext = GraphicDevice::GetInstance()->GetDeviceContext();
	pDeviceContext->IASetVertexBuffers(0, 1, &m_pVtxBuffer, &m_nVtxStride, &m_nVtxOffset);
	pDeviceContext->IASetIndexBuffer(m_pIdxBuffer, DXGI_FORMAT_R32_UINT, 0);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (m_pRasterizerState)
		pDeviceContext->RSSetState(m_pRasterizerState);

	pDeviceContext->DrawIndexed(m_nIdxNum, m_nIdxStart, m_nIdxPlus);
}

void Terrain::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC tRasterizerDesc;
	ZeroMemory(&tRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	tRasterizerDesc.CullMode = D3D11_CULL_NONE;
	tRasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
	GraphicDevice::GetInstance()->GetDevice()->CreateRasterizerState(&tRasterizerDesc, &m_pRasterizerState);
}

void Terrain::Release()
{
	VIBuffer::Release();
	::Safe_Delete_Array(m_pHeightMapTypeInfoArray);
}

HRESULT Terrain::LoadHeightMap(const char* _Path)
{
	// Open the height map file in binary.
	// Only-Read & Birary 모드로 높이맵 파일을 엽니다.
	FILE* pFile = nullptr;
	if (fopen_s(&pFile, _Path, "rb") != 0)
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
	// 비트맵 데이터의 시작 부분으로 이동합니다.
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
	// 높이 맵 데이터를 저장할 구조체를 만듧니다.
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

HRESULT Terrain::Init_Buffer(const int _iCntX, const int _iCntZ)
{
	m_nVtxNum = _iCntX * _iCntZ;
	m_nVtxStride = sizeof(VertexColor);
	m_nVtxOffset = 0;
	m_nVtxStart = 1;

	m_nIdxNum = (_iCntX - 1) * (_iCntZ - 1) * 6; // * 2(TriNum) * 3(VertexNum);
	m_nIdxStart = 0;
	m_nIdxPlus = 0;

	/*
	-----------------
	|	|	|	|	|
	-----------------
	|	|	|	|	|
	-----------------
	|	|	|	|	|
	-----------------
	| \	|	|	|	|
	.---.---.---.---.
	*/

	/*
	iIndex	+ _iCntX ---  iIndex + _iCntX + 1
							|\|
					iIndex	---	 iIndex	+ 1
	*/

	VertexColor* pVertexColorInfoArray = new VertexColor[m_nVtxNum];
	Index32* pIndexInfoArray = new Index32[m_nIdxNum];

	int iTriIndex = 0;
	for (int j = 0; j < _iCntZ; ++j)
	{
		for (int i = 0; i < _iCntX; ++i)
		{
			// Vertex
			int iVtxIndex = (j * _iCntX) + i;

			pVertexColorInfoArray[iVtxIndex].vPos
				= D3DXVECTOR3((float)i, /*m_pHeightMapTypeInfoArray*/0.0f, (float)j);
			pVertexColorInfoArray[iVtxIndex].vColor
				= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);


			if (i == _iCntX - 1 || j == _iCntZ - 1)
				continue;

			// Index
			//int iIdxIndex = (j * (_iCntX - 1)) + i;
			//int iTriIndex = (iIdxIndex * 2);

			pIndexInfoArray[iTriIndex]._1 = iVtxIndex + _iCntX;
			pIndexInfoArray[iTriIndex]._2 = iVtxIndex + _iCntX + 1;
			pIndexInfoArray[iTriIndex]._3 = iVtxIndex + 1;
			++iTriIndex;

			pIndexInfoArray[iTriIndex /*+ 1*/]._1 = iVtxIndex + _iCntX;
			pIndexInfoArray[iTriIndex /*+ 1*/]._2 = iVtxIndex + 1;
			pIndexInfoArray[iTriIndex /*+ 1*/]._3 = iVtxIndex;
			++iTriIndex;
		}
	}

	// Set up the description of the static vertex buffer.
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = m_nVtxStride * m_nVtxNum;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	D3D11_SUBRESOURCE_DATA tData;
	ZeroMemory(&tData, sizeof(D3D11_SUBRESOURCE_DATA));
	tData.pSysMem = pVertexColorInfoArray;
	tData.SysMemPitch = 0;
	tData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	CHECK_FAILED(
		GraphicDevice::GetInstance()->GetDevice()->CreateBuffer(&bufferDesc, &tData, &m_pVtxBuffer));


	//int iTriIndex = 0;
	//for (int j = 0; j < _iCntZ - 1; ++j)
	//{
	//	for (int i = 0; i < _iCntX - 1; ++i)
	//	{
	//		// Index
	//		int iVtxIndex = (j * _iCntX) + i;
	//		//int iIdxIndex = (j * (_iCntX - 1)) + i;
	//		//int iTriIndex = (iIdxIndex * 2);

	//		pIndexInfoArray[iTriIndex]._1 = iVtxIndex + _iCntX;
	//		pIndexInfoArray[iTriIndex]._2 = iVtxIndex + _iCntX + 1;
	//		pIndexInfoArray[iTriIndex]._3 = iVtxIndex + 1;
	//		++iTriIndex;

	//		pIndexInfoArray[iTriIndex /*+ 1*/]._1 = iVtxIndex + _iCntX;
	//		pIndexInfoArray[iTriIndex /*+ 1*/]._2 = iVtxIndex + 1;
	//		pIndexInfoArray[iTriIndex /*+ 1*/]._3 = iVtxIndex;
	//		++iTriIndex;
	//	}
	//}


	// Set up the description of the static index buffer.
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(DWORD)* m_nIdxNum;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	ZeroMemory(&tData, sizeof(D3D11_SUBRESOURCE_DATA));
	tData.pSysMem = pIndexInfoArray;
	tData.SysMemPitch = 0;
	tData.SysMemSlicePitch = 0;

	// Create the index buffer.
	CHECK_FAILED(
		GraphicDevice::GetInstance()->GetDevice()->CreateBuffer(&bufferDesc, &tData, &m_pIdxBuffer));

	// Release the arrays now that the buffers have been created and loaded.
	::Safe_Delete_Array(pVertexColorInfoArray);
	::Safe_Delete_Array(pIndexInfoArray);


	return S_OK;
}


END