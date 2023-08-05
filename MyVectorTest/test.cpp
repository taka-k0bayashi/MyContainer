#include "pch.h"
#include "../MyVector/MyVector.h"
#include <vector>

using MyContainer::MyVector;

class MyClass
{
	int num;
public:
	explicit MyClass(int num) : num(num){}
	MyClass() : MyClass(0){}
};

class TestDestructor
{
	int& count;
public:
	explicit TestDestructor(int& count) : count(count) 
	{ 
	}
	~TestDestructor() 
	{
		++this->count; 
	}
};

class TestConstructor
{
	int& count;
public:
	explicit TestConstructor(int& count) : count(count)
	{
	}

	TestConstructor(const TestConstructor& value) : count(value.count)
	{
		++this->count;
	}
};
TEST(Size, Test1) 
{
	MyVector<int> vector;

	EXPECT_EQ(vector.size(), 0);
}

TEST(Empty, Test1)
{
	MyVector<int> vector;

	EXPECT_TRUE(vector.empty());
}

TEST(Capacity, Test1)
{
	MyVector<int> vector;

	EXPECT_EQ(vector.capacity(), 0);
}

TEST(Construct, Test1)
{
	MyVector<int> vector(2, 1);

	EXPECT_EQ(vector.size(), 2);

	EXPECT_EQ(vector.capacity(), 2);

	EXPECT_FALSE(vector.empty());
}

TEST(Construct, Test2)
{
	MyVector<int> vector(5, 3);

	EXPECT_EQ(vector.size(), 5);

	EXPECT_EQ(vector.capacity(), 5);

	EXPECT_FALSE(vector.empty());
}

TEST(Construct, Test3)
{
	MyVector<int> vector(5);

	EXPECT_EQ(vector.size(), 5);

	EXPECT_EQ(vector.capacity(), 5);

	EXPECT_FALSE(vector.empty());
}

// T = size_t
TEST(Construct, Test4)
{
	MyVector<size_t> vector(5);

	EXPECT_EQ(vector.size(), 5);

	EXPECT_EQ(vector.capacity(), 5);

	EXPECT_FALSE(vector.empty());
}

TEST(Construct, Test5)
{
	std::allocator<int> allocator;

	MyVector<int, std::allocator<int>> vector(allocator);

	EXPECT_EQ(vector.size(), 0);

	EXPECT_EQ(vector.capacity(), 0);

	EXPECT_TRUE(vector.empty());
}

TEST(Construct, Test6)
{
	MyVector<MyClass> vector(5, MyClass(2));

	EXPECT_EQ(vector.size(), 5);

	EXPECT_EQ(vector.capacity(), 5);

	EXPECT_FALSE(vector.empty());
}

TEST(Construct, Test7)
{
	std::allocator<MyClass> allocator;

	MyVector<MyClass, std::allocator<MyClass>> vector(11, MyClass(2), allocator);

	EXPECT_EQ(vector.size(), 11);

	EXPECT_EQ(vector.capacity(), 11);

	EXPECT_FALSE(vector.empty());
}

TEST(Construct, Test8)
{
	int count = 0;
	TestConstructor value(count);

	{
		MyVector<TestConstructor> vector(5, value);
	}


	EXPECT_EQ(count, 5);
}

TEST(Construct, Test9)
{
	std::allocator<TestConstructor> allocator;

	int count = 0;
	TestConstructor value(count);

	{
		MyVector<TestConstructor, std::allocator<TestConstructor>> vector(11, value, allocator);
	}


	EXPECT_EQ(count, 11);
}

TEST(Destruct, Test1)
{
	int count = 0;
	TestDestructor value(count);

	{
		MyVector<TestDestructor> vector(5, value);
	}


	EXPECT_EQ(count, 5);
}

TEST(Destruct, Test2)
{
	std::allocator<TestDestructor> allocator;

	int count = 0;
	TestDestructor value(count);

	{
		MyVector<TestDestructor, std::allocator<TestDestructor>> vector(11, value, allocator);
	}


	EXPECT_EQ(count, 11);
}
TEST(Operator, Test1)
{
	MyVector<int> vector(5, 3);

	for (size_t i = 0; i < 5; ++i)
	{
		EXPECT_EQ(vector[i], 3);
	}
}

TEST(Push_back, Test1)
{
	MyVector<int> vector;

	EXPECT_EQ(vector.size(), 0);

	EXPECT_EQ(vector.capacity(), 0);

	EXPECT_TRUE(vector.empty());

	vector.push_back(2);

	EXPECT_EQ(vector.size(), 1);

	EXPECT_TRUE(vector.capacity() >= 1);

	EXPECT_FALSE(vector.empty());

	EXPECT_EQ(vector[0], 2);
}

// push_back(&&)
TEST(Push_back, Test2)
{
	MyVector<int> vector;

	int num = 2;

	vector.push_back(num);

	EXPECT_EQ(vector.size(), 1);

	EXPECT_TRUE(vector.capacity() >= 1);

	EXPECT_FALSE(vector.empty());

	EXPECT_EQ(vector[0], 2);
}

TEST(Push_back, Test3)
{
	MyVector<int> vector;

	vector.push_back(2);

	vector.push_back(5);

	EXPECT_EQ(vector.size(), 2);

	EXPECT_TRUE(vector.capacity() >= 2);

	EXPECT_FALSE(vector.empty());

	EXPECT_EQ(vector[0], 2);

	EXPECT_EQ(vector[1], 5);
}

TEST(Push_back, Test4)
{
	MyVector<int> vector;

	size_t size = 1000;

	for (size_t i = 0; i < size; ++i)
	{
		vector.push_back(i);
	}

	EXPECT_EQ(vector.size(), size);

	EXPECT_TRUE(vector.capacity() >= size);

	EXPECT_FALSE(vector.empty());

	for (size_t i = 0; i < size; ++i)
	{
		EXPECT_EQ(vector[i], i);
	}
}

TEST(Data, Test1)
{
	MyVector<int> vector;
	int num = 100;

	for (int i = 0; i < num; ++i)
	{
		vector.push_back(i);
	}
	
	int* pointer = vector.data();

	for (int i = 0; i < num; ++i)
	{
		EXPECT_EQ(*pointer, i);
		++pointer;
	}
}


TEST(Pop_back, Test1)
{
	MyVector<int> vector;
}

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