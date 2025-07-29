#include <gtest/gtest.h>
#include "purgatory.h"

#ifdef PURGATORY_X86_64

TEST(X86_64Test, BasicCheck) {
	EXPECT_EQ(1 + 1, 2);
}

TEST(X86_64Test, increasingTripletCheck) {

        purgatory::Purgatory solutions;

	// Basic case:
	vector<int> nums = {1, 2, 3, 4, 5};

        bool output = solutions.increasingTriplet(nums);

        bool expected = true;

	EXPECT_EQ(output, expected);
}

#elif PURGATORY_ARM64LE

TEST(ARM64LETest, BasicCheck) {
	EXPECT_EQ(1 + 1, 2);
}
#elif PURGATORY_I386

TEST(I386Test, BasicCheck) {
	EXPECT_EQ(1 + 1, 2);
}
#endif
