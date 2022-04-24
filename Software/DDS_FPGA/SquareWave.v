module SquareWave
       (
           input clk,
           input rst_n,

           output reg squareWave
       );

reg[31: 0]count;

always@(posedge clk or negedge rst_n)
begin
    if (!rst_n)
    begin
        count <= 0;
        squareWave <= 0;
    end
    else
    begin
        count <= (count < 2499) ? count + 1 : 0;
        if (count == 2499)
        begin
            squareWave <= ~squareWave;
        end
    end
end

endmodule