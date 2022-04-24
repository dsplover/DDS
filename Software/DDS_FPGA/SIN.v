module SIN
       (
           input clk_100M,
           input rst_n,

           input [23: 0]fre,    // fc / fs
           input [23: 0]fre2,    // fs / freFM
           input [11: 0]phasePM,

           output[15: 0]SIN_sig,    // carrier / modulated
           output[15: 0]SIN_sig2 // modulated / FM
       );

wire [47: 0]temp = fre * 24'd11258999;
wire [47: 0]temp2 = fre2 * 24'd11258999;

wire [31: 0]K_12_20 = temp[47: 18];
wire [31: 0]K_12_20_2 = temp2[47: 18];

reg [31: 0]phase;
reg [31: 0]phase2;

always@(posedge clk_100M or negedge rst_n)
begin
    if (!rst_n)
    begin
        phase <= 0;
        phase2 <= 0;
    end
    else
    begin
        phase <= phase + K_12_20;
        phase2 <= phase2 + K_12_20_2;
    end
end

ROM_Sin	ROM_Sin_inst (
            .address_a ( phase[31: 20] + phasePM),
            .address_b ( phase2[31: 20] ),
            .clock ( clk_100M ),
            .q_a ( SIN_sig ),
            .q_b ( SIN_sig2 )
        );

endmodule