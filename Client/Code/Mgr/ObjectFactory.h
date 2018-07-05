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
	//template<class T> 이걸로 하면 CreateObject 를 사용하는 곳에서도
	// #include "T.h" 를 해야해서 기존 팩토리 패턴을 따르겠다.
	class Engine::Object* CreateObject(const EObjectID& _eObjectID);

	// 이건 위 주석 내용에 반하는 메소드
	//template<typename T, typename = typename std::enable_if<std::is_same<Engine::Object, T>::value>::type>
	// is_same 이 부모클래스를 검사하진 않는다. 당연한 얘기겠지만
	// 그렇다면 이건 사용하지 않겠다!!
	//T* CreateObject();
};