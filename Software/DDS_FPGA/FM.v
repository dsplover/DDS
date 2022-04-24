module FM
       (
           input [23: 0]fc,      //载波频率
           input [15: 0]modulated,      //调制波
           input [15: 0]fd,      //最大频偏

           output [23: 0]freFM
       );

//无符号转为有符号
wire[15: 0]modulated_s = {!modulated[15], modulated[14: 0]};

wire[31: 0]result;

MULT_s	MULT_s_inst
       (
           .dataa ( fd ),
           .datab ( modulated_s ),
           .result ( result )
       );

wire[24: 0]temp = {{8{result[31]}}, result[31: 15]}; //除以32767,化为有符号数

wire [24: 0]freFM_s = {1'b0, fc} + temp; //频率(有符号)

assign freFM = freFM_s[23: 0];

endmodule