#pragma once

namespace Engine
{
	class Object;
}

class  ObjectFactory
{
	DECLARE_SINGLETON(ObjectFactory)

private:
	ObjectFactory();
	~ObjectFactory();

public:
	enum class EObjectID
	{
		OBJECT_ID_TEST,
		OBJECT_ID_CAMERA_DYNAMIC,
		OBJECT_ID_TERRAIN,

		OBJECT_ID_MAX,
	};

public :
	//template<class T> �̰ɷ� �ϸ� CreateObject �� ����ϴ� ��������
	// #include "T.h" �� �ؾ��ؼ� ���� ���丮 ������ �����ڴ�.
	class Engine::Object* CreateObject(const EObjectID& _eObjectID);

	// �̰� �� �ּ� ���뿡 ���ϴ� �޼ҵ�
	//template<typename T, typename = typename std::enable_if<std::is_same<Engine::Object, T>::value>::type>
	// is_same �� �θ�Ŭ������ �˻����� �ʴ´�. �翬�� ��������
	// �׷��ٸ� �̰� ������� �ʰڴ�!!
	//T* CreateObject();
};