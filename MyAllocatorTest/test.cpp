#include "pch.h"

#include "../MyAllocator/MyAllocator.h"

using namespace MyContainer;
Version1_BEGIN
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

TEST(Allocate, Test1) 
{
	MyAllocator<int> allocator;
	int* x = allocator.allocate(1);

	allocator.deallocate(x, 1);
}

TEST(TestConstruct, Test1)
{
	MyAllocator<int> allocator;
	int* ptr = allocator.allocate(1);
	allocator.construct(ptr, 2);
	EXPECT_EQ(*ptr, 2);
	allocator.destroy(ptr);
	allocator.deallocate(ptr, 1);
}

TEST(Construct, Test1)
{
	MyAllocator<MyClass> allocator;

	MyClass* object = allocator.allocate(1);

	allocator.construct(object, 0);

	EXPECT_EQ(a, 1);

	allocator.destroy(object);

	allocator.deallocate(object, 1);
}

TEST(Construct, Test2)
{
	MyAllocator<MyClass> allocator;

	MyClass* object = allocator.allocate(2);

	allocator.construct(object, 0);

	allocator.construct(object + 1, 0);

	EXPECT_EQ(a, 2);

	allocator.destroy(object);
	allocator.destroy(object + 1);

	allocator.deallocate(object, 2);
}

Version1_END

class LeakChecker : public ::testing::EmptyTestEventListener
{
private:
	// Called before a test starts.
	void OnTestStart(const ::testing::TestInfo& test_info) override
	{
		_CrtMemCheckpoint(&mem_state_before_);
	}

	// Called after a test ends.
	void OnTestEnd(const ::testing::TestInfo& test_info) override
	{
		_CrtMemCheckpoint(&mem_state_after_);
		EXPECT_FALSE(_CrtMemDifference(&mem_state_diff_, &mem_state_before_, &mem_state_after_));
	}

	_CrtMemState mem_state_before_, mem_state_after_, mem_state_diff_;
};

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

	listeners.Append(new LeakChecker);

	return RUN_ALL_TESTS();
}