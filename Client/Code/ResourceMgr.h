/*!
* \file ResourceMgr.h
* \date 2016/01/31 6:16
*
* \author 김명지
* Contact: bluevill04@gmail.com
*
* \brief
*
* TODO: long description
*
* \note
*/

/*
원형 리소스가 담겨져 있는 클래스입니다.
로딩을 할 때 해당씬에 필요한 리소스 원형을 m_mapResource 에 Add 해주시고,
해당 리소스를 클론하고 싶을 경우 m_mapResource 에서 리소스를 Find 한 후
리턴 되는 원형 리소스의 클론함수를 호출하면 됩니다.
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
