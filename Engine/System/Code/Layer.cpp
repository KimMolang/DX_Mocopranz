#include "stdafx.h"
#include "Layer.h"

#include "Object.h"

BEGIN(Engine)


Layer::Layer()
{

}

Layer::~Layer()
{
	Release_Obj();
}

HRESULT Layer::AddObj(Object* _pObj)
{
	if (_pObj)
	{
		m_listObject.push_front(_pObj);
	}
	else return E_FAIL;

	return S_OK;
}

void Layer::Update_Obj()
{
	std::forward_list<Object*>::iterator	iter		= m_listObject.begin();
	std::forward_list<Object*>::iterator	iter_end	= m_listObject.end();

	for (; iter != iter_end;)
	{
		if ((*iter)->Update() == Object::EState::STATE_DIE)
		{
			::Safe_Delete(*iter);
			m_listObject.erase_after(iter++);
		}
		else ++iter;
	}
}

void Layer::Render_Obj()
{
	for (auto& iter : m_listObject)
	{
		//(*iter)->Render();
		iter->Render();
	}
}

void Layer::Release_Obj()
{
	for (auto& iter : m_listObject)
	{
		::Safe_Delete(iter);
	}

	m_listObject.clear();
}


END