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

CONTAINER_NAMESPACE_BEGIN

Version1_BEGIN

template<typename ValPtr>
class MyIterator
{
	ValPtr* pointer;
	const ValPtr* first;
	const ValPtr* last;
	bool valid;
public:
	MyIterator(ValPtr* pointer, const ValPtr* first, const ValPtr* last) : pointer(pointer), first(first), last(last), valid(true) {}

	ValPtr operator*()
	{
		return *this->pointer;
	}

	MyIterator& operator++()
	{
		++this->pointer;
		return *this;
	}

	MyIterator operator++(int)
	{
		++this->pointer;
		return *this;
	}

	MyIterator& operator--()
	{
		--this->pointer;
		return *this;
	}

	MyIterator operator--(int)
	{
		--this->pointer;
		return *this;
	}

	MyIterator& operator+(int num)
	{
		this->pointer += num;
		return *this;
	}

	MyIterator& operator-(int num)
	{
		this->pointer -= num;
		return *this;
	}

	bool operator==(const MyIterator& rhs)
	{
		return this->pointer == rhs.pointer;
	}

	bool operator!=(const MyIterator& rhs)
	{
		return !(*this == rhs);
	}

	ValPtr* operator->() const noexcept
	{
		return this->pointer;
	}
};

Version1_END

CONTAINER_NAMESPACE_END