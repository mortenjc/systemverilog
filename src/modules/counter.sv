// Copyright (C) 2021 Morten Jagd Christensen, see LICENSE file
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief a 32 bit up/down counter
//===----------------------------------------------------------------------===//

module counter(
	input bit clk,
	input bit updn,
	output [31:0] value
	);

  always_ff @(posedge clk) begin
	  if (updn) begin
		  value <= value + 1;
		end else begin
		  value <= value - 1;
		end
  end

endmodule
