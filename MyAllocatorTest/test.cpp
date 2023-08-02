#include "pch.h"

#include "../MyAllocator/MyAllocator.h"

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