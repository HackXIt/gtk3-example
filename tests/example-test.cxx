#include <gtest/gtest.h>

extern "C"
{
// Include necessary C-headers for the application/functions here
#include "gui.h"
}

// This is a dummy-test, which will always be passed. It serves as a template for other testcases
TEST(gtk3_example_unit_tests, DUMMY)
{
	EXPECT_EQ(1, 1);
}