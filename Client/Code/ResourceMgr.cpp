#include "stdafx.h"
#include "ResourceMgr.h"

#include "Functor.h"

//#include "ShaderColor.h"
//#include "ShaderTexture.h"
#include "ShaderSkyBox.h"
//#include "ShaderAni.h"

//#include "BufferCube.h"
//#include "BufferPlan.h"
#include "BufferSkyBox.h"
//#include "BufferUI.h"

//#include "ModelStatic.h"
//#include "ModelDynamic.h"

#include "Texture.h"
#include "Font.h"

IMPLEMENT_SINGLETON(CResourceMgr)


CResourceMgr::CResourceMgr()
{

}

CResourceMgr::~CResourceMgr()
{
	Release_All();
}

CResource* CResourceMgr::FindResource(const ResourceAttri _eResourceAtrri,
										const ResourceType _eResourceType,
										const wstring& _wstrKey)
{
	map<wstring, CResource*>::iterator iter
		= m_mapResource[_eResourceAtrri][_eResourceType].find(_wstrKey);

	if (iter == m_mapResource[_eResourceAtrri][_eResourceType].end())
	{
		TAGMSG_BOX(_wstrKey.c_str(), L"리소스 원형이 존재하지 않습니다.");
		return NULL;
	}

	return iter->second;
}

CResource* CResourceMgr::CloneResource(const ResourceAttri _eResourceAtrri,
										const ResourceType _eResourceType,
										const wstring& _wstrKey)
{
	map<wstring, CResource*>::iterator iter
		= m_mapResource[_eResourceAtrri][_eResourceType].find(_wstrKey);

	if (iter == m_mapResource[_eResourceAtrri][_eResourceType].end())
	{
		TAGMSG_BOX(_wstrKey.c_str(), L"리소스 원형이 존재하지 않습니다.");
		return NULL;
	}

	return iter->second->Clone();
}

HRESULT CResourceMgr::Add_Shader(CDevice* _pDevice,
								const ResourceAttri _eResourceAtrri,
								const ShaderType _eShaderType,
								const wstring& _wstrKey)
{
	map<wstring, CResource*>::iterator iter
		= m_mapResource[_eResourceAtrri][RESOURCE_TYPE_SHADER].find(_wstrKey);

	if (iter != m_mapResource[_eResourceAtrri][RESOURCE_TYPE_SHADER].end())
		return S_OK;


	CResource*		pResource = NULL;

	switch (_eShaderType)
	{
	//case SHADER_TYPE_COLOR :	pResource = CColorShader::Create(_pDevice);		break;
	//case SHADER_TYPE_TEXTURE :	pResource = CTextureShader::Create(_pDevice);	break;
	case SHADER_TYPE_SKYBOX:	pResource = CShaderSkyBox::Create(_pDevice);	break;
	//case SHADER_TYPE_ANI:		pResource = CAniShader::Create(_pDevice);	break;
	default:
		return E_FAIL;
	}

	NULL_CHECK_RETURN(pResource, E_FAIL);

	m_mapResource[_eResourceAtrri][RESOURCE_TYPE_SHADER].insert(make_pair(_wstrKey, pResource));
	return S_OK;
}

HRESULT CResourceMgr::Add_Buffer(CDevice* _pDevice,
								const ResourceAttri _eResourceAtrri,
								const BufferType _eBufferType,
								const wstring& _wstrKey)
{
	map<wstring, CResource*>::iterator iter
		= m_mapResource[_eResourceAtrri][RESOURCE_TYPE_BUFFER].find(_wstrKey);

	if (iter != m_mapResource[_eResourceAtrri][RESOURCE_TYPE_BUFFER].end())
		return S_OK;


	CResource*		pResource = NULL;

	switch (_eBufferType)
	{
		//case BUFFER_TYPE_CUBE :	pResource = CufferCubeB::Create(_pDevice);		break;
		//case BUFFER_TYPE_PLAN : pResource = CBufferPlan::Create(_pDevice);		break;
		case BUFFER_TYPE_SKYBOX: pResource = CBufferSkyBox::Create(_pDevice);	break;
		//case BUFFER_TYPE_UI: pResource = CBufferUI::Create(_pDevice);			break;

		default:
			return E_FAIL;
	}

	NULL_CHECK_RETURN(pResource, E_FAIL);

	m_mapResource[_eResourceAtrri][RESOURCE_TYPE_BUFFER].insert(make_pair(_wstrKey, pResource));
	return S_OK;
}

HRESULT CResourceMgr::Add_Texture(CDevice* _pDevice,
								const ResourceAttri _eResourceAtrri,
								const CTexture::TextureType& _eTextureType,
								const wstring& _wstrKey,
								const wstring& _wstrPath)
{
	map<wstring, CResource*>::iterator iter
		= m_mapResource[_eResourceAtrri][RESOURCE_TYPE_TEXTURE].find(_wstrKey);

	if (iter != m_mapResource[_eResourceAtrri][RESOURCE_TYPE_TEXTURE].end())
		return S_OK;

	CResource* pResource = CTexture::Create(_pDevice, _wstrPath, _eTextureType);
	NULL_CHECK_RETURN(pResource, E_FAIL);

	m_mapResource[_eResourceAtrri][RESOURCE_TYPE_TEXTURE].insert(make_pair(_wstrKey, pResource));
	return S_OK;
}

HRESULT CResourceMgr::Add_Model(CDevice* _pDevice,
								const ResourceAttri _eResourceAtrri,
								const ModelType _eModelType,
								const wstring& _wstrKey,
								const char* _pPath,
								vector<string> _vecAniName /*= vector<string>()*/)
{
	map<wstring, CResource*>::iterator iter
		= m_mapResource[_eResourceAtrri][RESOURCE_TYPE_MODEL].find(_wstrKey);

	if (iter != m_mapResource[_eResourceAtrri][RESOURCE_TYPE_MODEL].end())
		return S_OK;


	CResource*		pResource = NULL;

	switch (_eModelType)
	{
	//case CResourceMgr::MODEL_TYPE_DYNAMIC:	pResource = CModelDynamic::Create(_pDevice, _pPath, _vecAniName); break;
	//case CResourceMgr::MODEL_TYPE_STATIC :	pResource = CModelStatic::Create(_pDevice, _pPath);	break;

	default:
		return E_FAIL;
	}

	NULL_CHECK_RETURN(pResource, E_FAIL);

	m_mapResource[_eResourceAtrri][RESOURCE_TYPE_MODEL].insert(make_pair(_wstrKey, pResource));
	return S_OK;
}

HRESULT CResourceMgr::Add_Font(CDevice* _pDevice,
								ResourceAttri _eResourceAtrri,
								const wstring& _wstrKey,
								const wstring& _wstrPath)
{
	map<wstring, CResource*>::iterator iter
		= m_mapResource[_eResourceAtrri][RESOURCE_TYPE_FONT].find(_wstrKey);

	if (iter != m_mapResource[_eResourceAtrri][RESOURCE_TYPE_FONT].end())
		return S_OK;

	CResource* pResource = CFont::Create(_pDevice, _wstrPath);
	NULL_CHECK_RETURN(pResource, E_FAIL);

	m_mapResource[_eResourceAtrri][RESOURCE_TYPE_FONT].insert(make_pair(_wstrKey, pResource));
	return E_FAIL;
}


void CResourceMgr::Release_Dynamic()
{
	for (int i = 0; i < RESOURCE_TYPE_END; ++i)
	{
		for_each(m_mapResource[RESOURCE_ATTRI_DYNAMIC][i].begin(),
			m_mapResource[RESOURCE_ATTRI_DYNAMIC][i].end(), ::DeleteMap());
		m_mapResource[RESOURCE_ATTRI_DYNAMIC][i].clear();
	}
}

void CResourceMgr::Release_All()
{
	for (int i = 0; i < RESOURCE_ATTRI_END; ++i)
	{
		for (int j = 0; j < RESOURCE_TYPE_END; ++j)
		{
			for_each(m_mapResource[i][j].begin(),
				m_mapResource[i][j].end(), ::DeleteMap());
			m_mapResource[i][j].clear();
		}
	}
}
