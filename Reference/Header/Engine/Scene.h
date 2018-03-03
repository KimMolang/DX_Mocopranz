#pragma once

BEGIN(Engine)


class Camera;
class Layer;
class ENGINE_DLL Scene abstract
{
public:
	explicit Scene();
	virtual ~Scene() PURE;

public:
	enum ELayerType
	{
		LAYER_TYPE_BACK,
		LAYER_TYPE_GAMELOGIC,
		LAYER_TYPE_UI,

		LAYER_TYPE_MAX
	};


public:
	virtual HRESULT		Init()			PURE;
	virtual void		Update()		PURE;
	virtual void		Render()		PURE;
	virtual void		Release()		PURE;

private:
	void Update_Layer();
	void Render_Layer();
private:
	void Release_Layer();


protected:
	Layer *			m_pLayer[ELayerType::LAYER_TYPE_MAX];
	Camera*			m_pMainCamera;
};


END