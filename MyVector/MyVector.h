#pragma once
#define CONTAINER_NAMESPACE_BEGIN namespace MyContainer{
#define CONTAINER_NAMESPACE_END }
#define Version1_BEGIN inline namespace ver1{
#define Version1_END }

CONTAINER_NAMESPACE_BEGIN

Version1_BEGIN 

template<typename T, typename Alloc>
class MyVector
{
public:
	void push_back(const T& t)
	{

	}

	void pop_back()
	{

	}
	
	constexpr size_t size() const noexcept
	{

	}


};

Version1_END

CONTAINER_NAMESPACE_END