#pragma once

#include "Scene.h"

BEGIN(Engine)


class ENGINE_DLL SceneNull : public Scene
{
public:
	explicit SceneNull() {};
	virtual ~SceneNull() {};

public:
	virtual HRESULT		Init() { return S_OK; };
	virtual void		Update() {};
	virtual void		Render() {};
	virtual void		Release() {};

public:
	void Update_Layer() {};
	void Render_Layer() {};
private:
	void Release_Layer() {};
};


END