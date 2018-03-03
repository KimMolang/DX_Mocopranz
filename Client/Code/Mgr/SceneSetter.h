#pragma once

class  SceneSetter
{
	DECLARE_SINGLETON(SceneSetter)

private:
	SceneSetter();
	~SceneSetter();

public:
	enum ESceneID
	{
		SCENE_ID_NONE,

		SCENE_ID_TOWN,
	};


public :
	HRESULT		SetScene(const ESceneID& _eSceneID);

private:
	ESceneID		m_eCurScene;
};