#pragma once


template<typename T>
static void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
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

template <typename T>
void Safe_Release(T& pointer)
{
	if (nullptr != pointer)
	{
		pointer->Release();
		pointer = nullptr;
	}
}