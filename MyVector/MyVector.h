#pragma once

#ifndef CONTAINER_NAMESPACE_BEGIN
#define CONTAINER_NAMESPACE_BEGIN namespace MyContainer{
#endif

#ifndef CONTAINER_NAMESPACE_END
#define CONTAINER_NAMESPACE_END }
#endif

#ifndef Version1_BEGIN
#define Version1_BEGIN inline namespace ver1{
#endif

#ifndef Version1_END
#define Version1_END }
#endif

#include "../MyAllocator/MyAllocator.h"

CONTAINER_NAMESPACE_BEGIN

Version1_BEGIN 

template<typename T, typename Alloc = MyContainer::MyAllocator<T>>
class MyVector
{
	struct MyPair
	{
		T* first;
		T* last;
		T* end;
		MyPair() : first(nullptr), last(nullptr), end(nullptr){}
	};
	MyPair _MyPair;
	Alloc allocator;
public:
	MyVector(size_t size = 0, const T& value = T(), const Alloc& allocator = Alloc()) : _MyPair(), allocator(allocator)
	{
		this->_MyPair.first = this->allocator.allocate(size);

		T* pointer = this->_MyPair.first;
		for (size_t i = 0; i < size; ++i)
		{
			this->allocator.construct(pointer, value);
			++pointer;
		}

		this->_MyPair.last = this->_MyPair.first + size;
		this->_MyPair.end = this->_MyPair.first + size;
	}

	using value_type = T;

	void push_back(const T& t)
	{

	}

	void push_back(T&& value)
	{

	}

	void pop_back()
	{

	}
	
	constexpr size_t size() const noexcept
	{
		return this->_MyPair.last - this->_MyPair.first;
	}

	bool empty() const noexcept
	{
		return this->size() == 0;
	}

	T& operator[](const size_t index)
	{
		if (index >= this->size() || index < 0) throw;
		return *(this->_MyPair.first + index);
	}

	const T& operator[](const size_t index) const
	{
		if (index >= this->size()) throw;
		return *(this->_MyPair.first + index);
	}
};

Version1_END

CONTAINER_NAMESPACE_END