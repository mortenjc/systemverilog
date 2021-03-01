// Copyright (C) 2021 Morten Jagd Christensen, see LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief unit test for clockdiv.sv
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

//
TEST_F(ClockDivTest, Divide50MClocks) {
  const uint32_t Clocks50M = 50'000'000;
  uint32_t ctr_clk_high{0};
  uint32_t ctr_clk_low{0};
  ASSERT_EQ(clock_i->clk_out, 0);
  for (int i = 0; i < Clocks50M; i++) {
    clock_ticks(1);
    if (clock_i->clk_out)
      ctr_clk_high++;
    else
      ctr_clk_low++;
  }
  ASSERT_EQ(ctr_clk_high, Clocks50M/2);
  ASSERT_EQ(ctr_clk_low, Clocks50M/2);
}

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
