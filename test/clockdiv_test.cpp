// Copyright (C) 2021 Morten Jagd Christensen, see LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief test harness for ALU logic
//===----------------------------------------------------------------------===//

#include <clockdiv.h>
#include <verilated.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

class ClockDivTest: public ::testing::Test {
protected:
clockdiv * clock_i;

  void clock_ticks(int N) {
    for (int i = 1; i <= N; i++) {
      clock_i->clk_in = 1;
      clock_i->eval();
      clock_i->clk_in = 0;
      clock_i->eval();
    }
  }

  void SetUp( ) {
    clock_i = new clockdiv;
    clock_i->eval();
  }

  void TearDown( ) {
    clock_i->final();
    delete clock_i;
  }
};


TEST_F(ClockDivTest, PulsesInASecond) {
  uint32_t ctr_slow{0};
  uint32_t ctr_fast{0};
  ASSERT_EQ(clock_i->clk_slow, 0);
  ASSERT_EQ(clock_i->clk_fast, 0);
  for (int i = 0; i < 50000000; i++) {
    clock_ticks(1);
    if (clock_i->clk_slow)
      ctr_slow++;
    if (clock_i->clk_fast)
      ctr_fast++;
  }
  ASSERT_EQ(ctr_fast, 5'000'000);
  ASSERT_EQ(ctr_slow, 100);
}

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
