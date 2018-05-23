#pragma once

/*!
* \file TSingleTon.h
* \date 2016/01/25 3:17
*
* \author 오현규
* Contact: sita0106@gmail.com
*
* \brief
*
* TODO: long description
*
* \note
*/

#include <assert.h>

//assert 는 false때 진단메세지와 함께 프로그램을 중지한다.
// class ... values [C++11] Variadic template
namespace Engie { 
	template <class T>
	class TSingleTon
	{
		static T* m_pInstance;

	public :
		TSingleTon() {
			assert(!m_pInstance);
			m_pInstance = static_cast<T*>(this);
		}
		~TSingleTon() {
			assert(m_pInstance) m_pInstance = nullptr;
		}

		//접근을 못하게 막는다. 복사생성자 막기.
		TSingleTon(const TSingleTon&) = delete;
		TSingleTon& operator = (const TSingleTon) = delete;

		static T& Instance() { return *m_pInstance; }
		static T* InstancePtr() { return m_pInstance; }

		//상속이 아닌 직접 생성해서 사용할 때 사용한다.
		template <class ... InitValues>
		static void CreateInstance(InitValues&& ... initValues) { m_pInstance = new T(std::forward(initValues)); }
		static void DestroyInstance() { delete InstancePtr(); m_pInstance = nullptr; }
	};

	template<class T>
	T* TSingleTon<T>::m_pInstance = nullptr;
}