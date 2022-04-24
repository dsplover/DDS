module PSK
       (
           input clk_100M,
           input rst_n,
           input [15: 0]carrier,
           input [15: 0]sequenceCode,

           output [15: 0]PSK_sig
       );

reg[31: 0]count;
reg [3: 0]sequence;
reg [1: 0]state;

wire [15: 0]carrier_s = {!carrier[15], carrier[14: 0]};
reg [15: 0]PSK_sig_s;

assign PSK_sig = {!PSK_sig_s[15], PSK_sig_s[14: 0]};

always@(posedge clk_100M or negedge rst_n)
begin
    if (!rst_n)
    begin
        count <= 0;
        sequence <= 15;
        state = 0;
        PSK_sig_s <= 0;
    end
    else
    begin
        count <= (count < 9765) ? count + 1 : 0; //10239.6Hz

        case (state)
            0:
            begin
                if (count == 9765)
                begin
                    if (carrier - 32767 <= 50)
                    begin
                        state <= 2;
                    end
                    else if (32767 - carrier <= 50)
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
                if (carrier - 32767 <= 50)
                begin
                    state <= 2;
                end
                else if (32767 - carrier <= 50)
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
                PSK_sig_s <= 0;
            end
        endcase

        PSK_sig_s <= (sequenceCode[sequence] == 1) ? ~carrier_s : carrier_s;
    end
end
endmodule