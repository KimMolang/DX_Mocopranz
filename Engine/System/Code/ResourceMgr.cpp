#include "stdafx.h"
#include "ResourceMgr.h"

#include "ShaderColor.h"
//#include "TextureShader.h"
//#include "SkyBoxShader.h"
//#include "AniShader.h"
//
#include "VIBufferCube.h"
//#include "PlanBuffer.h"
//#include "SkyBoxBuffer.h"
//#include "UIBuffer.h"
//
//#include "StaticModel.h"
//#include "DynamicModel.h"
//
//#include "Texture.h"
//#include "Font.h"

BEGIN(Engine)


IMPLEMENT_SINGLETON(ResourceMgr)


ResourceMgr::ResourceMgr()
{

}

ResourceMgr::~ResourceMgr()
{
	Release_All();
}

Resource* ResourceMgr::FindResource(const EResourceAttribute _eResourceAtrri,
	const EResourceType _eResourceType,
	const std::wstring& _wstrKey)
{
	std::map<std::wstring, Resource*>::iterator iter
		= m_mapResource[_eResourceAtrri][_eResourceType].find(_wstrKey);

	if (iter == m_mapResource[_eResourceAtrri][_eResourceType].end())
	{
		MSG_BOX_TAG(_wstrKey.c_str(), L"리소스 원형이 존재하지 않습니다.");
		return NULL;
	}

	return iter->second;
}

Resource* ResourceMgr::CloneResource(const EResourceAttribute _eResourceAtrri,
	const EResourceType _eResourceType,
	const std::wstring& _wstrKey)
{
	std::map<std::wstring, Resource*>::iterator iter
		= m_mapResource[_eResourceAtrri][_eResourceType].find(_wstrKey);

	if (iter == m_mapResource[_eResourceAtrri][_eResourceType].end())
	{
		MSG_BOX_TAG(_wstrKey.c_str(), L"리소스 원형이 존재하지 않습니다.");
		return NULL;
	}

	return iter->second->Clone();
}

HRESULT ResourceMgr::Add_Shader
(
	const EResourceAttribute _eResourceAtrri
	, const EShaderType _eShaderType
	, const std::wstring& _wstrKey
)
{
	std::map<std::wstring, Resource*>::iterator iter
		= m_mapResource[_eResourceAtrri][RESOURCE_TYPE_SHADER].find(_wstrKey);

	if (iter != m_mapResource[_eResourceAtrri][RESOURCE_TYPE_SHADER].end())
		return S_OK;


	Resource*		pResource = NULL;

	switch (_eShaderType)
	{
	case SHADER_TYPE_COLOR:		pResource = new ShaderColor();		break;
	//case SHADER_TYPE_TEXTURE:	pResource = TextureShader::Create(_pDevice);	break;
	//case SHADER_TYPE_SKYBOX:	pResource = CSkyBoxShader::Create(_pDevice);	break;
	//case SHADER_TYPE_ANI:		pResource = CAniShader::Create(_pDevice);	break;
	default:
		return E_FAIL;
	}

	CHECK_NULLPTR_RETURN(pResource, E_FAIL);

	m_mapResource[_eResourceAtrri][RESOURCE_TYPE_SHADER].insert(make_pair(_wstrKey, pResource));
	return S_OK;
}

HRESULT ResourceMgr::Add_Buffer(const EResourceAttribute _eResourceAtrri,
	const EVIBufferType _eBufferType,
	const std::wstring& _wstrKey)
{
	std::map<std::wstring, Resource*>::iterator iter
		= m_mapResource[_eResourceAtrri][RESOURCE_TYPE_BUFFER].find(_wstrKey);

	if (iter != m_mapResource[_eResourceAtrri][RESOURCE_TYPE_BUFFER].end())
		return S_OK;


	Resource*		pResource = NULL;

	switch (_eBufferType)
	{
	case VIBUFFER_TYPE_CUBE:	pResource = new VIBufferCube();		break;
	//case VIBUFFER_TYPE_PLAN: pResource = CPlanBuffer::Create(_pDevice);		break;
	//case VIBUFFER_TYPE_SKYBOX: pResource = CSkyBoxBuffer::Create(_pDevice);	break;
	//case VIBUFFER_TYPE_UI: pResource = CUIBuffer::Create(_pDevice);			break;

	default:
		return E_FAIL;
	}

	CHECK_NULLPTR_RETURN(pResource, E_FAIL);

	m_mapResource[_eResourceAtrri][RESOURCE_TYPE_BUFFER].insert(make_pair(_wstrKey, pResource));
	return S_OK;
}

HRESULT ResourceMgr::Add_Texture(const EResourceAttribute _eResourceAtrri,
	const Texture::ETextureType& _eTextureType,
	const std::wstring& _wstrKey,
	const std::wstring& _wstrPath)
{
	//std::map<std::wstring, Resource*>::iterator iter
	//	= m_mapResource[_eResourceAtrri][RESOURCE_TYPE_TEXTURE].find(_wstrKey);

	//if (iter != m_mapResource[_eResourceAtrri][RESOURCE_TYPE_TEXTURE].end())
	//	return S_OK;

	//Resource* pResource = Texture::Create(_pDevice, _wstrPath, _eTextureType);
	//CHECK_NULLPTR_RETURN(pResource, E_FAIL);

	//m_mapResource[_eResourceAtrri][RESOURCE_TYPE_TEXTURE].insert(make_pair(_wstrKey, pResource));
	return S_OK;
}

HRESULT ResourceMgr::Add_Model(const EResourceAttribute _eResourceAtrri,
	const EModelType _eModelType,
	const std::wstring& _wstrKey,
	const char* _pPath,
	std::vector<std::string> _vecAniName /*= vector<string>()*/)
{
	//std::map<std::wstring, Resource*>::iterator iter
	//	= m_mapResource[_eResourceAtrri][RESOURCE_TYPE_MODEL].find(_wstrKey);

	//if (iter != m_mapResource[_eResourceAtrri][RESOURCE_TYPE_MODEL].end())
	//	return S_OK;


	//Resource*		pResource = NULL;

	//switch (_eModelType)
	//{
	//case ResourceMgr::MODEL_TYPE_DYNAMIC:	pResource = CDynamicModel::Create(_pDevice, _pPath, _vecAniName); break;
	//case ResourceMgr::MODEL_TYPE_STATIC:	pResource = CStaticModel::Create(_pDevice, _pPath);	break;

	//default:
	//	return E_FAIL;
	//}

	//CHECK_NULLPTR_RETURN(pResource, E_FAIL);

	//m_mapResource[_eResourceAtrri][RESOURCE_TYPE_MODEL].insert(make_pair(_wstrKey, pResource));
	return S_OK;
}

HRESULT ResourceMgr::Add_Font(EResourceAttribute _eResourceAtrri,
	const std::wstring& _wstrKey,
	const std::wstring& _wstrPath)
{
	//std::map<std::wstring, Resource*>::iterator iter
	//	= m_mapResource[_eResourceAtrri][RESOURCE_TYPE_FONT].find(_wstrKey);

	//if (iter != m_mapResource[_eResourceAtrri][RESOURCE_TYPE_FONT].end())
	//	return S_OK;

	//Resource* pResource = CFont::Create(_pDevice, _wstrPath);
	//CHECK_NULLPTR_RETURN(pResource, E_FAIL);

	//m_mapResource[_eResourceAtrri][RESOURCE_TYPE_FONT].insert(make_pair(_wstrKey, pResource));
	return E_FAIL;
}


void ResourceMgr::Release_Dynamic()
{
	for (int i = 0; i < RESOURCE_TYPE_END; ++i)
	{
		for_each(m_mapResource[RESOURCE_ATTRI_DYNAMIC][i].begin(),
			m_mapResource[RESOURCE_ATTRI_DYNAMIC][i].end(), ::Safe_Delete_map());
		m_mapResource[RESOURCE_ATTRI_DYNAMIC][i].clear();
	}
}

void ResourceMgr::Release_All()
{
	for (int i = 0; i < RESOURCE_ATTRI_END; ++i)
	{
		for (int j = 0; j < RESOURCE_TYPE_END; ++j)
		{
			for_each(m_mapResource[i][j].begin(),
				m_mapResource[i][j].end(), ::Safe_Delete_map());
			m_mapResource[i][j].clear();
		}
	}
}


END