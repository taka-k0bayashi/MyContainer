#pragma once

#define CONTAINER_NAMESPACE_BEGIN namespace MyContainer{
#define CONTAINER_NAMESPACE_END }
#define Version1_BEGIN inline namespace ver1{
#define Version1_END }

#include <new.h>
#include <type_traits>

CONTAINER_NAMESPACE_BEGIN

Version1_BEGIN

template<typename T>
class MyAllocator
{
	using value_type = T;
public:
	value_type* allocate(size_t size)
	{
		if (size == 0) return nullptr;
		return reinterpret_cast<value_type*>(::operator new(size * sizeof(value_type)));
	}

	void deallocate(value_type* ptr, size_t size)
	{
		::operator delete(ptr);
	}

	template<typename... Args>
	void construct(value_type* ptr, Args&&... args)
	{
		::new (ptr) value_type(std::forward<Args>(args)...);
	}

	void destroy(value_type* ptr)
	{
		((value_type*)ptr)->~value_type();
	}

	template<typename U>
	struct rebind
	{
		using other = MyAllocator<U>;
	};

	MyAllocator() noexcept{}
	MyAllocator(const MyAllocator<T>&) noexcept{}
	template<typename U>
	MyAllocator(const MyAllocator<U>&) noexcept{}
	~MyAllocator() noexcept{}


};

Version1_END

CONTAINER_NAMESPACE_END