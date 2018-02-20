/*
원형 리소스가 담겨져 있는 클래스입니다.
로딩을 할 때 해당씬에 필요한 리소스 원형을 m_mapResource 에 Add 해주시고,
해당 리소스를 클론하고 싶을 경우 m_mapResource 에서 리소스를 Find 한 후
리턴 되는 원형 리소스의 클론함수를 호출하면 됩니다.
*/

#pragma once

#include "Texture.h"

BEGIN(Engine)


class Resource;
class ENGINE_DLL ResourceMgr
{
	DECLARE_SINGLETON(ResourceMgr)

private:
	ResourceMgr();
	~ResourceMgr();


public:
	enum EResourceAttribute
	{
		RESOURCE_ATTRI_STATIC,
		RESOURCE_ATTRI_DYNAMIC,

		RESOURCE_ATTRI_END
	};
	enum EResourceType
	{
		RESOURCE_TYPE_SHADER,
		RESOURCE_TYPE_BUFFER,
		RESOURCE_TYPE_TEXTURE,
		RESOURCE_TYPE_MODEL,
		RESOURCE_TYPE_FONT,

		RESOURCE_TYPE_END
	};

	enum EShaderType
	{
		SHADER_TYPE_COLOR,
		SHADER_TYPE_TEXTURE,
		SHADER_TYPE_SKYBOX,
		SHADER_TYPE_ANI
	};
	enum EBufferType
	{
		BUFFER_TYPE_CUBE,
		BUFFER_TYPE_PLAN,
		BUFFER_TYPE_SKYBOX,
		BUFFER_TYPE_UI
	};

	enum EModelType { MODEL_TYPE_DYNAMIC, MODEL_TYPE_STATIC };


public:
	Resource*		FindResource(const EResourceAttribute _eResourceAtrri,
		const EResourceType _eEResourceType, const std::wstring& _wstrKey);
	Resource*		CloneResource(const EResourceAttribute _eResourceAtrri,
		const EResourceType _eEResourceType, const std::wstring& _wstrKey);

	HRESULT			Add_Shader(const EResourceAttribute _eResourceAtrri,
		const EShaderType _eEShaderType, const std::wstring& _wstrKey);
	HRESULT			Add_Buffer(const EResourceAttribute _eResourceAtrri,
		const EBufferType _eEBufferType, const std::wstring& _wstrKey);
	HRESULT			Add_Texture(const EResourceAttribute _eResourceAtrri,
		const Texture::ETextureType& _eTextureType, const std::wstring& _wstrKey, const std::wstring& _wstrPath);
	HRESULT			Add_Model(EResourceAttribute _eResourceAtrri,
		const EModelType _eModelType, const std::wstring& _wstrKey,
		const char* _pPath, std::vector<std::string> _vecAniName = std::vector<std::string>());
	HRESULT			Add_Font(EResourceAttribute _eResourceAtrri,
		const std::wstring& _wstrKey, const std::wstring& _wstrPath);

public:
	void	Release_Dynamic();
	void	Release_All();


private:
	std::map<std::wstring, Resource*>		m_mapResource[RESOURCE_ATTRI_END][RESOURCE_TYPE_END];
};


END