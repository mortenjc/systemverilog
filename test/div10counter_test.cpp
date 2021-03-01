// Copyright (C) 2021 Morten Jagd Christensen, see LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief unit test for clockdiv.sv
//===----------------------------------------------------------------------===//

#include <div10counter.h>
#include <verilated.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

class Div10CounterTest: public ::testing::Test {
protected:
  div10counter * cntr10;
  const uint32_t Clocks10M = 10'000'000;

  void clock_ticks(int N) {
    for (int i = 1; i <= N; i++) {
      cntr10->clk = 1;
      cntr10->eval();
      cntr10->clk = 0;
      cntr10->eval();
    }
  }

  void SetUp( ) {
    cntr10 = new div10counter;
    cntr10->eval();
  }

  void TearDown( ) {
    cntr10->final();
    delete cntr10;
  }
};

//
TEST_F(Div10CounterTest, CountUp10MPlus) {
  ASSERT_EQ(cntr10->value, 0);
  cntr10->updn = 1;
  clock_ticks(Clocks10M);
  ASSERT_EQ(cntr10->value, Clocks10M/10);
}

//
TEST_F(Div10CounterTest, CountDown10MPlus) {
  cntr10->value = Clocks10M/10;
  cntr10->updn = 0;
  clock_ticks(Clocks10M);
  ASSERT_EQ(cntr10->value, 0);
}

TEST_F(Div10CounterTest, Negative1) {
  ASSERT_EQ(cntr10->value, 0);
  cntr10->updn = 0;
  clock_ticks(10);
  ASSERT_EQ(cntr10->value, 0xFFFFFFFF);
}

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
