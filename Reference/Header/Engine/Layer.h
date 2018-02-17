#pragma once

BEGIN(Engine)


class Object;
class ENGINE_DLL Layer
{
private:
	explicit Layer();
public:
	~Layer();

	// Scene 으로 이동
//public:
//	enum class EType
//	{
//		TYPE_BACK,
//		TYPE_GAMELOGIC,
//		TYPE_UI,
//
//		TYPE_MAX
//	};


public:
	HRESULT			AddObj(Object* _pObj);

public:
	void	Update_Obj();
	void	Render_Obj();
private:
	void	Release_Obj();

private:
	std::forward_list<Object*>		m_listObject;
};


END