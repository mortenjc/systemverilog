// Copyright (C) 2021 Morten Jagd Christensen, see LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief a 32 bit up/down counter
//===----------------------------------------------------------------------===//

module div10counter(
	input bit clk,
	input bit updn,
	output [31:0] value
	);

  // derive counter_clk
  bit counter_clk;
  clockdiv clockdiv_i(
		.clk_in(clk),
		.clk_out(counter_clk)
    );

  // Use counter_clk
  counter counter_i(
		.clk(counter_clk),
		.updn(updn),
		.value(value)
		);

endmodule
