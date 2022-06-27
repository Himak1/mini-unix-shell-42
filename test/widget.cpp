#include "gtest/gtest.h"

extern "C" {
#include "widget.h"
}

TEST(widget, ok) {
  ASSERT_EQ(sum(1, 1), 2);
}