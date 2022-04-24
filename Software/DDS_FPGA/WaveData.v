module WaveData
       (
           input clk, rst_n,
           input [15: 0]otdata,
           input cs,
           output reg[16: 0]waveData
       );

always @(posedge clk or negedge rst_n)
begin
    if (!rst_n)
    begin
        waveData <= 0;
    end
    else
    begin
        if (cs == 1)
        begin
            waveData <= otdata;
        end
        else
        begin
            waveData <= waveData;
        end
    end
end

endmodule