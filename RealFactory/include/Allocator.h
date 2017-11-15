#pragma once

#include <new>
#include <memory.h>
#include "Platform.h"


#ifdef DEBUG_CLIENTBLOCK
#undef DEBUG_CLIENTBLOCK
#define DEBUG_CLIENTBLOCK new
#endif
template<typename T>
class FAllocator
{
public:
	FAllocator() {};
	virtual ~FAllocator() {};

	// ����һ��������ڴ�
	T* FAllocator(size_t cnt)
	{
		return (T*)internal_new(cnt * sizeof(T));
	}

	// �ͷ�һ��������ڴ�
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

#ifdef DEBUG_CLIENTBLOCK
#undef DEBUG_CLIENTBLOCK
#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif