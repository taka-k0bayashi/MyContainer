#include "pch.h"
#include "../MyIterator/MyIterator.h"

using namespace MyContainer;

Version1_BEGIN

class TestArrow
{
public:
	int return_2_function()
	{
		return 2;
	}
};

TEST(Star, Test1) 
{
	int* pointer = new int[5];
	pointer[0] = 2;
	MyIterator<int> itr(pointer, pointer, &pointer[5]);

	EXPECT_EQ(*itr, 2);

	delete[] pointer;
}

TEST(PlusPlus, Test1)
{
	int* pointer = new int[5];
	pointer[0] = 2;
	pointer[1] = 3;
	MyIterator<int> itr(pointer, pointer, &pointer[5]);

	EXPECT_EQ(*itr, 2);

	++itr;

	EXPECT_EQ(*itr, 3);

	delete[] pointer;
}

TEST(PlusPlus, Test2)
{
	int* pointer = new int[5];
	pointer[0] = 2;
	pointer[1] = 3;
	MyIterator<int> itr(pointer, pointer, &pointer[5]);

	EXPECT_EQ(*itr, 2);

	itr++;

	EXPECT_EQ(*itr, 3);

	delete[] pointer;
}

TEST(MinusMinus, Test1)
{
	int* pointer = new int[5];
	pointer[0] = 2;
	pointer[1] = 3;
	MyIterator<int> itr(&pointer[1], pointer, &pointer[5]);

	EXPECT_EQ(*itr, 3);

	--itr;

	EXPECT_EQ(*itr, 2);

	delete[] pointer;
}

TEST(MinusMinus, Test2)
{
	int* pointer = new int[5];
	pointer[0] = 2;
	pointer[1] = 3;
	MyIterator<int> itr(&pointer[1], pointer, &pointer[5]);

	EXPECT_EQ(*itr, 3);

	itr--;

	EXPECT_EQ(*itr, 2);

	delete[] pointer;
}

TEST(Plus, Test1)
{
	int* pointer = new int[5];
	for (int i = 0; i < 5; ++i)
	{
		pointer[i] = i + 2;
	}

	MyIterator<int> itr(pointer, pointer, &pointer[5]);

	EXPECT_EQ(*itr, 2);

	itr = itr + 1;

	EXPECT_EQ(*itr, 3);

	itr = itr + 2;

	EXPECT_EQ(*itr, 5);

	delete[] pointer;
}

TEST(Minus, Test1)
{
	int* pointer = new int[5];
	for (int i = 0; i < 5; ++i)
	{
		pointer[i] = i + 2;
	}

	MyIterator<int> itr(&pointer[3], pointer, &pointer[5]);

	EXPECT_EQ(*itr, 5);

	itr = itr - 1;

	EXPECT_EQ(*itr, 4);

	itr = itr - 2;

	EXPECT_EQ(*itr, 2);

	delete[] pointer;
}

TEST(Equal, Test1)
{
	int* pointer = new int[5];
	pointer[0] = 2;
	pointer[1] = 3;
	MyIterator<int> itr(pointer, pointer, &pointer[5]);
	MyIterator<int> itr2(pointer, pointer, &pointer[5]);

	EXPECT_TRUE(itr == itr2);

	++itr;
	++itr2;

	EXPECT_TRUE(itr == itr2);

	MyIterator<int> itr3(&pointer[1], pointer, &pointer[5]);

	EXPECT_TRUE(itr == itr3);

	delete[] pointer;
}

TEST(NotEqual, Test1)
{
	int* pointer = new int[5];
	pointer[0] = 2;
	pointer[1] = 3;
	MyIterator<int> itr(pointer, pointer, &pointer[5]);
	MyIterator<int> itr2(pointer, pointer, &pointer[5]);

	EXPECT_FALSE(itr != itr2);

	++itr;
	++itr2;

	EXPECT_FALSE(itr != itr2);

	MyIterator<int> itr3(&pointer[1], pointer, &pointer[5]);

	EXPECT_FALSE(itr != itr3);

	delete[] pointer;
}

TEST(Arrow, Test1)
{
	TestArrow* objects = new TestArrow[6]();

	MyIterator<TestArrow> itr(objects, objects, &objects[6]);

	EXPECT_EQ(itr->return_2_function(), 2);

	delete[] objects;
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