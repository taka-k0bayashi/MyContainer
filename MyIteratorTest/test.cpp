#include "pch.h"
#include "../MyIterator/MyIterator.h"

using namespace MyContainer;

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