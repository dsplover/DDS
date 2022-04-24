module AM
       (
           input [15: 0]carrier,     //载波
           input [15: 0]modulated,     //调制波
           input [3: 0]ma,     //调制度

           output [15: 0]AM_sig
       );

//无符号转为有符号
wire[15: 0]carrier_s = {!carrier[15], carrier[14: 0]};
wire[15: 0]modulated_s = {!modulated[15], modulated[14: 0]};

wire[15: 0]ma_102 = ma * 102;
wire[31: 0]result;

MULT_s	MULT_s_inst //乘ma
       (
           .dataa (modulated_s),
           .datab (ma_102),
           .result (result)
       );

wire[16: 0]sum = {result[31], result[25: 10]} + 17'd32767; //可能进位，因此使用17位有符号数
wire[31: 0]result2;

MULT_s	MULT_s_inst2
       (
           .dataa (sum[16: 1]),     //除2得到16位有符号数
           .datab ( carrier_s),
           .result (result2)
       );

wire [15: 0]temp = {result2[31], result2[29: 15]}; //除以32767,化为有符号数
assign AM_sig = {~temp[15], temp[14: 0]}; //化为无符号数

endmodule