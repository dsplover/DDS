module FSK
       (
           input clk_100M,
           input rst_n,
           input [15: 0]carrier,
           input [15: 0]modulated,

           input [15: 0]sequenceCode,

           output reg[15: 0]FSK_sig
       );

reg[31: 0]count;
reg [3: 0]sequence;
reg [1: 0]state;

always@(posedge clk_100M or negedge rst_n)
begin
    if (!rst_n)
    begin
        count <= 0;
        sequence <= 15;
        state = 0;
        FSK_sig <= 0;
    end
    else
    begin
        count <= (count < 9765) ? count + 1 : 0; //10239.6Hz

        case (state)
            0:
            begin
                if (count == 9765)
                begin
                    if (carrier - modulated <= 50)
                    begin
                        state <= 2;
                    end
                    else if (modulated - carrier <= 50)
                    begin
                        state <= 2;
                    end
                    else
                    begin
                        state <= 1;
                    end
                end
            end
            1:
            begin
                if (carrier - modulated <= 50)
                begin
                    state <= 2;
                end
                else if (modulated - carrier <= 50)
                begin
                    state <= 2;
                end
            end
            2:
            begin
                sequence <= sequence - 1;
                state <= 0;
            end
            default:
            begin
                count <= 0;
                sequence <= 15;
                state = 0;
                FSK_sig <= 0;
            end
        endcase

        FSK_sig <= (sequenceCode[sequence] == 1) ? carrier : modulated;
    end
end
endmodule