#include "pch.h"
#include "../MyVector/MyVector.h"

using MyContainer::MyVector;

TEST(MyVectorTest, Size1) 
{
	MyVector<int> vector;

	EXPECT_EQ(vector.size(), 0);
}

TEST(MyVectorTest, Empty1)
{
	MyVector<int> vector;

	EXPECT_TRUE(vector.empty());
}

TEST(MyVectorTest, Construct1)
{
	MyVector<int> vector(2, 1);

	EXPECT_EQ(vector.size(), 2);

	EXPECT_FALSE(vector.empty());
}

TEST(MyVectorTest, Construct2)
{
	MyVector<int> vector(5, 3);

	EXPECT_EQ(vector.size(), 5);

	EXPECT_FALSE(vector.empty());
}

TEST(MyVectorTest, Operator1)
{
	MyVector<int> vector(5, 3);

	for (size_t i = 0; i < 5; ++i)
	{
		EXPECT_EQ(vector[i], 3);
	}
}