module MODE
       (
           input clk_100M,
           input rst_n,
           input[2: 0]mode,
           input[15: 0]sin_sig,
           input[15: 0]AM_sig,
           input[15: 0]FM_sig,
           input[15: 0]PM_sig,
           input[15: 0]ASK_sig,
           input[15: 0]FSK_sig,
           input[15: 0]PSK_sig,

           output reg[13: 0]sig_out
       );

reg [13:0]sig_out_reg;
always@(posedge clk_100M or negedge rst_n)
begin
    if (!rst_n)
    begin
        sig_out_reg <= 0;
    end
    else
    begin
        case (mode)
            3'b000:
                sig_out_reg <= sin_sig[15: 2];
            3'b001:
                sig_out_reg <= AM_sig[15: 2];
            3'b010:
                sig_out_reg <= FM_sig[15: 2];
            3'b011:
                sig_out_reg <= PM_sig[15: 2];
            3'b100:
                sig_out_reg <= ASK_sig[15: 2];
            3'b101:
                sig_out_reg <= FSK_sig[15: 2];
            3'b110:
                sig_out_reg <= PSK_sig[15: 2];
            default:
                sig_out_reg <= 0;
        endcase
    end
end

always@(negedge clk_100M or negedge rst_n)
begin
    if (!rst_n)
    begin
        sig_out <= 0;
    end
    else
    begin
        case (mode)
            3'b000:
                sig_out <= sig_out_reg;
            3'b001:
                sig_out <= sig_out_reg;
            3'b010:
                sig_out <= sig_out_reg;
            3'b011:
                sig_out <= sig_out_reg;
            3'b100:
                sig_out <= sig_out_reg;
            3'b101:
                sig_out <= sig_out_reg;
            3'b110:
                sig_out <= sig_out_reg;
            default:
                sig_out <= 0;
        endcase
    end
end

endmodule