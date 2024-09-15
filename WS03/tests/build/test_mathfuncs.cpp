#include <gtest/gtest.h>
extern "C" {
    #include "mathfuncs.h"
}

// Test for non-empty string input
TEST(GetNonEmptyStringTest, NoEmptyString) {
    char input[MAX_LENGTH] = "John";
    char prompt[] = "Enter your first name: ";
    getNonEmptyString(prompt, input, MAX_LENGTH);
    EXPECT_STRNE(input, "");
}

// Test for valid postal code
TEST(IsValidPostalCodeTest, ValidPostalCode) {
    char validCode1[] = "A1A 1A1";
    char validCode2[] = "B2B 2B2";
    EXPECT_TRUE(isValidPostalCode(validCode1));
    EXPECT_TRUE(isValidPostalCode(validCode2));
}

// Test for invalid postal code
TEST(IsValidPostalCodeTest, InvalidPostalCode) {
    char invalidCode1[] = "123456";
    char invalidCode2[] = "A1A1A1";
    char invalidCode3[] = "A1A-1A1";
    EXPECT_FALSE(isValidPostalCode(invalidCode1));
    EXPECT_FALSE(isValidPostalCode(invalidCode2));
    EXPECT_FALSE(isValidPostalCode(invalidCode3));
}

// Test for postal code formatting
TEST(FormatPostalCodeTest, FormatPostalCode) {
    char postalCode1[] = "a1a1a1";
    char postalCode2[] = "b2b 2b2";
    formatPostalCode(postalCode1);
    formatPostalCode(postalCode2);
    EXPECT_STREQ(postalCode1, "A1A 1A1");
    EXPECT_STREQ(postalCode2, "B2B 2B2");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
