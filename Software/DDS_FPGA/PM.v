module PM
       (
           input clk_100M,
           input rst_n,
           input [2: 0]mode,
           input [15: 0]modulated,
           input [15: 0]pd,

           output reg[11: 0]phasePM
       );

wire [15: 0]modulated_s = {!modulated[15], modulated[14: 0]};

wire [31: 0]result;
MULT_s	MULT_s_inst
       (
           .dataa (pd),
           .datab (modulated_s),
           .result (result)
       );

always@(posedge clk_100M or negedge rst_n)
    if (!rst_n)
    begin
        phasePM <= 0;
    end
    else
    begin
        if (mode == 3'b011)
        begin
            phasePM <= {result[31], result[25: 15]}; //除以32767
        end
        else
        begin
            phasePM <= 0;
        end
    end


endmodule