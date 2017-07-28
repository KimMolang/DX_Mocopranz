/*!
* \file ResourceMgr.h
* \date 2016/01/31 6:16
*
* \author �����
* Contact: bluevill04@gmail.com
*
* \brief
*
* TODO: long description
*
* \note
*/

/*
���� ���ҽ��� ����� �ִ� Ŭ�����Դϴ�.
�ε��� �� �� �ش���� �ʿ��� ���ҽ� ������ m_mapResource �� Add ���ֽð�,
�ش� ���ҽ��� Ŭ���ϰ� ���� ��� m_mapResource ���� ���ҽ��� Find �� ��
���� �Ǵ� ���� ���ҽ��� Ŭ���Լ��� ȣ���ϸ� �˴ϴ�.
*/

#pragma once

#ifndef ResourceMgr_h__
#define ResourceMgr_h__

#include "Texture.h"


class CResource;
class CDevice;
class CResourceMgr
{
	DECLARE_SINGLETON(CResourceMgr)

public:
	enum ResourceAttri
	{
		RESOURCE_ATTRI_STATIC,
		RESOURCE_ATTRI_DYNAMIC,

		RESOURCE_ATTRI_END
	};
	enum ResourceType
	{
		RESOURCE_TYPE_SHADER,
		RESOURCE_TYPE_BUFFER,
		RESOURCE_TYPE_TEXTURE,
		RESOURCE_TYPE_MODEL,
		RESOURCE_TYPE_FONT,

		RESOURCE_TYPE_END
	};

	enum ShaderType
	{
		SHADER_TYPE_COLOR,
		SHADER_TYPE_TEXTURE,
		SHADER_TYPE_SKYBOX,
		SHADER_TYPE_ANI
	};
	enum BufferType
	{
		BUFFER_TYPE_CUBE,
		BUFFER_TYPE_PLAN,
		BUFFER_TYPE_SKYBOX,
		BUFFER_TYPE_UI
	};

	enum ModelType	{ MODEL_TYPE_DYNAMIC, MODEL_TYPE_STATIC };


private:
	map<wstring, CResource*>		m_mapResource[RESOURCE_ATTRI_END][RESOURCE_TYPE_END];


public:
	CResource*		FindResource(const ResourceAttri _eResourceAtrri,
								const ResourceType _eResourceType, const wstring& _wstrKey);
	CResource*		CloneResource(const ResourceAttri _eResourceAtrri,
								const ResourceType _eResourceType, const wstring& _wstrKey);

	HRESULT			Add_Shader(CDevice* _pDevice, const ResourceAttri _eResourceAtrri,
						const ShaderType _eShaderType, const wstring& _wstrKey);
	HRESULT			Add_Buffer(CDevice* _pDevice, const ResourceAttri _eResourceAtrri,
						const BufferType _eBufferType, const wstring& _wstrKey);
	HRESULT			Add_Texture(CDevice* _pDevice, const ResourceAttri _eResourceAtrri,
						const CTexture::TextureType& _eTextureType, const wstring& _wstrKey, const wstring& _wstrPath);
	HRESULT			Add_Model(CDevice* _pDevice, ResourceAttri _eResourceAtrri,
								const ModelType _eModelType, const wstring& _wstrKey,
								const char* _pPath, vector<string> _vecAniName = vector<string>());
	HRESULT			Add_Font(CDevice* _pDevice, ResourceAttri _eResourceAtrri,
								const wstring& _wstrKey, const wstring& _wstrPath);


public :
	void	Release_Dynamic();
	void	Release_All();


private:
	CResourceMgr();
	~CResourceMgr();
};

#endif // ResourceMgr_h__
