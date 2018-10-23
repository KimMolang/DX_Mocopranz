#include "stdafx.h"
#include "VIBufferTerrain.h"

#include "Engine_Define_Buffer_Index.h"

BEGIN(Engine)


VIBufferTerrain::VIBufferTerrain()
	: m_iHeighMapImgWidth(0)
	, m_iHeighMapImgHeight(0)

	, m_pHeightMapTypeInfoArray(nullptr)
	//, m_iBoxSizeX(1)
	//, m_iBoxSizeZ(1)
	, m_iBoxNumX(0)
	, m_iBoxNumZ(0)

	, m_pLightBuffer(nullptr)
{

}

VIBufferTerrain::~VIBufferTerrain()
{
	Release();
}

VIBufferTerrain* VIBufferTerrain::Create
(
	const int _iCntX
	, const int _iCntY
	, const char* _Path /*= nullptr*/
)
{
	VIBufferTerrain* pComponent = new VIBufferTerrain();
	if (FAILED(pComponent->Init(_iCntX, _iCntY, _Path)))
		::Safe_Delete(pComponent);

	return pComponent;
}

HRESULT VIBufferTerrain::Init
(
	const int _iCntX
	, const int _iCntY
	, const char* _Path /*= nullptr*/
)
{
	//VIBuffer::Init();
	//SetShader(ResourceMgr::EResourceAttribute::RESOURCE_ATTRI_STATIC, L"Test_Shader_Terrain"); 

	if (_Path)
	{
		CHECK_FAILED_MSG_RETURN(LoadHeightMap(_Path)
			, L"Failed Function of VITerrain::LoadHeightMap", E_FAIL);
		NormalizeHeightMap();
	}

	CHECK_FAILED_MSG_RETURN(Init_Buffer(_iCntX, _iCntY)
		, L"Failed Function of VITerrainInit_Buffer", E_FAIL);

	CreateRasterizerState();

	return S_OK;
}

void VIBufferTerrain::Update()
{
}

void VIBufferTerrain::Render()
{
	if (nullptr == m_pVtxBuffer)
		return;


	// Light
	if (m_pLightBuffer)
	{
		D3D11_MAPPED_SUBRESOURCE tSubreResource;
		GraphicDevice::GetInstance()->GetDeviceContext()->Map(m_pLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSubreResource);

		// (Need the Modify)
		// Need the Light Object
		LightBuffer* pLightData = (LightBuffer*)tSubreResource.pData;
		pLightData->colorEmbient	= D3DXVECTOR4(0.7f, 0.1f, 0.3f, 1.0f);
		pLightData->colorDiffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		D3DXVECTOR3 dirLight
			= D3DXVECTOR3(-5.0f, -1.0f, 0.0f);
		D3DXVec3Normalize(&dirLight, &dirLight);

		pLightData->dirLight		= dirLight;
		pLightData->padding			= 0.0f;

		GraphicDevice::GetInstance()->GetDeviceContext()->Unmap(m_pLightBuffer, 0);
		//GraphicDevice::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(VS_SLOT_LIGHT_VALUE, 1, &m_pLightBuffer);
		GraphicDevice::GetInstance()->GetDeviceContext()->PSSetConstantBuffers(VS_SLOT_LIGHT_VALUE, 1, &m_pLightBuffer);
	}
	

	//if (m_pShader)
	//	m_pShader->Render();

	ID3D11DeviceContext* pDeviceContext = GraphicDevice::GetInstance()->GetDeviceContext();
	pDeviceContext->IASetVertexBuffers(0, 1, &m_pVtxBuffer, &m_nVtxStride, &m_nVtxOffset);
	pDeviceContext->IASetIndexBuffer(m_pIdxBuffer, DXGI_FORMAT_R32_UINT, 0);
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (m_pRasterizerState)
		pDeviceContext->RSSetState(m_pRasterizerState);

	pDeviceContext->DrawIndexed(m_nIdxNum, m_nIdxStart, m_nIdxPlus);
}

void VIBufferTerrain::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC tRasterizerDesc;
	ZeroMemory(&tRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	tRasterizerDesc.CullMode = D3D11_CULL_NONE;
	tRasterizerDesc.FillMode = D3D11_FILL_SOLID;
	GraphicDevice::GetInstance()->GetDevice()->CreateRasterizerState(&tRasterizerDesc, &m_pRasterizerState);
}

void VIBufferTerrain::Release()
{
	if (m_pRefCnt == nullptr)
	{
		::Safe_Delete_Array(m_pHeightMapTypeInfoArray);
		::Safe_Release(m_pLightBuffer);
	}
}

HRESULT VIBufferTerrain::LoadHeightMap(const char* _Path)
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
	m_iHeighMapImgWidth = bitmapInfoHeader.biWidth;
	m_iHeighMapImgHeight = bitmapInfoHeader.biHeight;

	// Calculate the size of the bitmap image data.
	int iImageSize = m_iHeighMapImgWidth * m_iHeighMapImgHeight * 3; // 3 : Components num -> RGB

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
		= new D3DXVECTOR3[m_iHeighMapImgWidth * m_iHeighMapImgHeight];

	// Initialize the position in the image data buffer.
	int k = 0;

	for (int j = 0; j < m_iHeighMapImgHeight; ++j)
	{
		for (int i = 0; i < m_iHeighMapImgWidth; ++i)
		{
			unsigned __int8 height = pBitMapImageDataArray[k];

			int iIndex = (m_iHeighMapImgHeight * j) + i;

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

void VIBufferTerrain::NormalizeHeightMap()
{
	// The next new function is NormalizeHeightMap.
	// All it does is it goes through the terrain
	// and divides each height value by 15
	// so that the terrain doesn't look too spikey.
	// Generally its better just to do this work
	// on the height map before loading it in.

	for (int j = 0; j < m_iHeighMapImgHeight; ++j)
	{
		for (int i = 0; i < m_iHeighMapImgWidth; ++i)
		{
			// (Need To Modify)
			m_pHeightMapTypeInfoArray[(m_iHeighMapImgHeight * j) + i].y /= 15.0f;
		}
	}
}

HRESULT VIBufferTerrain::Init_Buffer(const int _iCntX, const int _iCntZ)
{
	m_iBoxNumX = (_iCntX - 1);
	m_iBoxNumZ = (_iCntZ - 1);

	m_nVtxNum = _iCntX * _iCntZ;
	m_nVtxStride = sizeof(VertexTexture);
	m_nVtxOffset = 0;
	m_nVtxStart = 1;

	m_nIdxNum = m_iBoxNumX * m_iBoxNumZ * 6; // * 2(TriNum) * 3(VertexNum);
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

	Index32* pIndexInfoArray = new Index32[m_nIdxNum];
	m_pVertexInfoArray = new VertexTexture[m_nVtxNum];

	const int TEXTURE_REPEAT_U = 3;
	const int TEXTURE_REPEAT_V = 3;

	for (int j = 0; j < _iCntZ; ++j /*+= m_iBoxSizeZ*/)
	{
		for (int i = 0; i < _iCntX; ++i /*+= m_iBoxSizeX*/)
		{
			// Vertex
			int iVtxIndex = (j * _iCntX) + i;

			float fHeght = 0.0f;
			if (m_pHeightMapTypeInfoArray)
			{
				fHeght = m_pHeightMapTypeInfoArray[(int)
					(((m_iHeighMapImgHeight / m_iBoxNumZ) * j) * m_iHeighMapImgWidth) + ((m_iHeighMapImgWidth / m_iBoxNumX) * i)].y;
			}

			m_pVertexInfoArray[iVtxIndex].vPos
				= D3DXVECTOR3((float)i, fHeght, (float)j);
			m_pVertexInfoArray[iVtxIndex].vNormal
				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);


			float fTextureU = (float)i / (float)m_iBoxNumX;
			float fTextureV = 1.0f - ((float)j / (float)m_iBoxNumZ);

			fTextureU *= TEXTURE_REPEAT_U;
			fTextureV *= TEXTURE_REPEAT_V;


			m_pVertexInfoArray[iVtxIndex].vTextureUV = D3DXVECTOR2(fTextureU, fTextureV);
		}
	}


	int iTriCnt = 0;
	for (int j = 0; j < _iCntZ - 1; ++j)
	{
		for (int i = 0; i < _iCntX - 1; ++i)
		{
			// Index
			int iVtxIndex = (j * _iCntX) + i;
			//int iIdxIndex = (j * (_iCntX - 1)) + i;
			//int iTriCnt = (iIdxIndex * 2);

			pIndexInfoArray[iTriCnt]._1 = iVtxIndex + _iCntX;
			pIndexInfoArray[iTriCnt]._2 = iVtxIndex + _iCntX + 1;
			pIndexInfoArray[iTriCnt]._3 = iVtxIndex + 1;

			D3DXVECTOR3	vDest, vSour, vNormal;
			vDest = m_pVertexInfoArray[pIndexInfoArray[iTriCnt]._2].vPos
				- m_pVertexInfoArray[pIndexInfoArray[iTriCnt]._1].vPos;
			vSour = m_pVertexInfoArray[pIndexInfoArray[iTriCnt]._3].vPos
				- m_pVertexInfoArray[pIndexInfoArray[iTriCnt]._2].vPos;
			D3DXVec3Cross(&vNormal, &vDest, &vSour);

			m_pVertexInfoArray[pIndexInfoArray[iTriCnt]._1].vNormal += vNormal;
			m_pVertexInfoArray[pIndexInfoArray[iTriCnt]._2].vNormal += vNormal;
			m_pVertexInfoArray[pIndexInfoArray[iTriCnt]._3].vNormal += vNormal;

			++iTriCnt;

			//
			pIndexInfoArray[iTriCnt /*+ 1*/]._1 = iVtxIndex + _iCntX;
			pIndexInfoArray[iTriCnt /*+ 1*/]._2 = iVtxIndex + 1;
			pIndexInfoArray[iTriCnt /*+ 1*/]._3 = iVtxIndex;

			vDest = m_pVertexInfoArray[pIndexInfoArray[iTriCnt]._2].vPos
				- m_pVertexInfoArray[pIndexInfoArray[iTriCnt]._1].vPos;
			vSour = m_pVertexInfoArray[pIndexInfoArray[iTriCnt]._3].vPos
				- m_pVertexInfoArray[pIndexInfoArray[iTriCnt]._2].vPos;
			D3DXVec3Cross(&vNormal, &vDest, &vSour);

			m_pVertexInfoArray[pIndexInfoArray[iTriCnt]._1].vNormal += vNormal;
			m_pVertexInfoArray[pIndexInfoArray[iTriCnt]._2].vNormal += vNormal;
			m_pVertexInfoArray[pIndexInfoArray[iTriCnt]._3].vNormal += vNormal;

			++iTriCnt;
		}
	}

	// Do this in VS & PS
	//for (UINT i = 0; i < m_nVtxNum; ++i)
	//{
	//	//D3DXVec3Normalize(&pVertexInfoArray[i].vNormal, &pVertexInfoArray[i].vNormal);
	//}


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
	tData.pSysMem = m_pVertexInfoArray;
	tData.SysMemPitch = 0;
	tData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	CHECK_FAILED(
		GraphicDevice::GetInstance()->GetDevice()->CreateBuffer(&bufferDesc, &tData, &m_pVtxBuffer));

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
	//::Safe_Delete_Array(pVertexInfoArray); // -> m_pVertexInfoArray
	::Safe_Delete_Array(pIndexInfoArray);


	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	// Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
	D3D11_BUFFER_DESC lightBufferDesc;
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBuffer);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0; 

	CHECK_FAILED(
		GraphicDevice::GetInstance()->GetDevice()->CreateBuffer(&lightBufferDesc, nullptr, &m_pLightBuffer));


	return S_OK;
}


END