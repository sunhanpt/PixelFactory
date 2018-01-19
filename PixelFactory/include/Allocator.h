#pragma once

#include <new>
#include <memory.h>
#include "Platform.h"

template<typename T>
class FAllocator
{
public:
	FAllocator() {};
	virtual ~FAllocator() {};

	// 分配一个数组的内存
	T* allocate(size_t cnt)
	{
		return (T*)internal_new(cnt * sizeof(T));
	}

	// 释放一个数组的内存
	void deallocate(T* ptr)
	{
		internal_delete(ptr);
	}

	// construct an element
	void construct(T* ptr, const T& e)
	{
		new ((void*)ptr) T(e);
	}

	// destruct an element
	void destruct(T * ptr)
	{
		ptr->~T();
	}

protected:
	virtual void* internal_new(size_t cnt)
	{
		return operator new(cnt);
	}
	virtual void internal_delete(void * ptr)
	{
		operator delete(ptr);
	}
};
