// Copyright (C) 2021 Morten Jagd Christensen, see LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief a 10:1 clock divider
//===----------------------------------------------------------------------===//

module clockdiv(
	input bit clk_in,
	output bit clk_out
	);

  parameter DIVIDER = 10;
  parameter MAX_COUNT = DIVIDER - 1;

  bit [3:0] counter;

  always_ff @(posedge clk_in) begin
		if (counter >= MAX_COUNT) begin
		  counter <= 0;
		end else begin
		  counter <= counter + 1;
		end
		clk_out <= (counter < DIVIDER/2) ? 1 : 0;
  end
endmodule
