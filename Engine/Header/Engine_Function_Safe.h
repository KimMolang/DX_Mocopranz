#pragma once


template<typename T>
static void Safe_Delete(T& pointer)
{
	if (pointer)
	{
		delete pointer;
		pointer = nullptr;
	}
}

template <typename T>
void Safe_Delete_Array(T& pointer)
{
	if (nullptr != pointer)
	{
		delete[] pointer;
		pointer = nullptr;
	}
}

struct Safe_Delete_map
{
	template<class T>
	void operator()(T& pointer)
	{
		if (pointer.second)
		{
			delete pointer.second;
			pointer.second = nullptr;
		}
	}
};

template <typename T>
void Safe_Release(T& pointer)
{
	if (nullptr != pointer)
	{
		pointer->Release();
		pointer = nullptr;
	}
}