#include "pch.h"

#include "../MyAllocator/MyAllocator.h"
#include <iostream>

int a = 0;

class MyClass
{
public:
	explicit MyClass(int b) 
	{
		++a;
	}

	~MyClass() { --a; }
};

TEST(TestAllocate, Test1) 
{
	MyContainer::MyAllocator<int> allocator;
	int* x = allocator.allocate(1);

	allocator.deallocate(x, 1);
}

TEST(TestConstruct, Test1)
{
	MyContainer::MyAllocator<int> allocator;
	int* ptr = allocator.allocate(1);
	allocator.construct(ptr, 2);
	EXPECT_EQ(*ptr, 2);
	allocator.destroy(ptr);
	allocator.deallocate(ptr, 1);
}

TEST(Construct, Test1)
{
	MyContainer::MyAllocator<MyClass> allocator;

	MyClass* object = allocator.allocate(1);

	allocator.construct(object, 0);

	EXPECT_EQ(a, 1);
}

TEST(Construct, Test2)
{
	MyContainer::MyAllocator<MyClass> allocator;

	MyClass* object = allocator.allocate(2);

	allocator.construct(object, 0);

	allocator.construct(object + 1, 0);

	EXPECT_EQ(a, 3);
}