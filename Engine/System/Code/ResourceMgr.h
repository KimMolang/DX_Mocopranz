/*
���� ���ҽ��� ����� �ִ� Ŭ�����Դϴ�.
�ε��� �� �� �ش���� �ʿ��� ���ҽ� ������ m_mapResource �� Add ���ֽð�,
�ش� ���ҽ��� Ŭ���ϰ� ���� ��� m_mapResource ���� ���ҽ��� Find �� ��
���� �Ǵ� ���� ���ҽ��� Ŭ���Լ��� ȣ���ϸ� �˴ϴ�.
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
	enum EVIBufferType
	{
		VIBUFFER_TYPE_CUBE,
		VIBUFFER_TYPE_PLAN,
		VIBUFFER_TYPE_SKYBOX,
		VIBUFFER_TYPE_UI
	};

	enum EModelType { MODEL_TYPE_DYNAMIC, MODEL_TYPE_STATIC };


public:
	HRESULT		AddResource
	(
		const EResourceAttribute& _eResourceAtrri
		, const EResourceType& _eEResourceType
		, const std::wstring& _wstrKey
		, Resource* _pResource
	);

	Resource*	FindResource
	(
		const EResourceAttribute& _eResourceAtrri
		, const EResourceType& _eEResourceType
		, const std::wstring& _wstrKey
	);
	Resource*	CloneResource
	(
		const EResourceAttribute& _eResourceAtrri
		, const EResourceType& _eEResourceType
		, const std::wstring& _wstrKey
	);


public:
	void	Release_Dynamic();
	void	Release_All();


private:
	std::map<std::wstring, Resource*>		m_mapResource[RESOURCE_ATTRI_END][RESOURCE_TYPE_END];
};


END