#pragma once

BEGIN(Engine)


class Object;
class ENGINE_DLL Layer
{
private:
	explicit Layer();
public:
	~Layer();

public:
	HRESULT			AddObj(Object* _pObj);

public:
	void	Update_Obj();
	void	Render_Obj();
private:
	void	Release_Obj();

private:
	std::forward_list<Object*>		m_listObject;

	friend class Scene;
};


END