// Copyright (C) 2021 Morten Jagd Christensen, see LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief a 50MHz to 100Hz and 5MHz divider
//===----------------------------------------------------------------------===//

module clockdiv(
	input bit clk_in,
	output bit clk_slow,
	output bit clk_fast
	);

  parameter CLK_HZ = 50000000;  // 50MHz
  parameter FAST_HZ = 5000000;  // 5MHz
  parameter SLOW_HZ = 100;
  parameter TICKS_FAST = CLK_HZ / FAST_HZ;
  parameter TICKS_SLOW = CLK_HZ / SLOW_HZ;

	parameter FAST_MAX = TICKS_FAST - 1;
	bit [31:0] cnt_fast;
	bit new_fast;

	parameter SLOW_MAX = TICKS_SLOW - 1;
	bit [31:0] cnt_slow;
	bit new_slow;

  /* verilator lint_off BLKSEQ */
  always_ff @(posedge clk_in) begin
	  if (cnt_fast == FAST_MAX) begin
			cnt_fast = 0;
			new_fast = 1;
	  end else begin
			cnt_fast++;
			new_fast = 0;
	  end

	  if (cnt_slow == SLOW_MAX) begin
			cnt_slow = 0;
			new_slow = 1;
	  end else begin
			cnt_slow++;
			new_slow = 0;
	  end

		clk_slow <= new_slow;
		clk_fast <= new_fast;
  end
  /* verilator lint_on BLKSEQ */
endmodule
