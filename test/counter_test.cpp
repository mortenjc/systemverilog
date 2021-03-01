// Copyright (C) 2021 Morten Jagd Christensen, see LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief unit test for clockdiv.sv
//===----------------------------------------------------------------------===//

#include <counter.h>
#include <verilated.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

class CounterTest: public ::testing::Test {
protected:
counter * cntr;

  void clock_ticks(int N) {
    for (int i = 1; i <= N; i++) {
      cntr->clk = 1;
      cntr->eval();
      cntr->clk = 0;
      cntr->eval();
    }
  }

  void SetUp( ) {
    cntr = new counter;
    cntr->eval();
  }

  void TearDown( ) {
    cntr->final();
    delete cntr;
  }
};

//
TEST_F(CounterTest, CountUp10MPlus) {
  ASSERT_EQ(cntr->value, 0);
  const uint32_t Clocks10M = 10'000'000;
  cntr->updn = 1;
  for (int i = 0; i < Clocks10M; i++) {
    clock_ticks(1);
    ASSERT_EQ(cntr->value, i + 1);
  }
  ASSERT_EQ(cntr->value, Clocks10M);
}

TEST_F(CounterTest, CountDown10MPlus) {
  const uint32_t Clocks10M = 10'000'000;
  cntr->value = Clocks10M;
  cntr->updn = 0;
  for (int i = 0; i < Clocks10M; i++) {
    clock_ticks(1);
    ASSERT_EQ(cntr->value, Clocks10M - (i + 1));
  }
  ASSERT_EQ(cntr->value, 0);
}

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
