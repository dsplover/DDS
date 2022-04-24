module DDS_generate
       (
           input clk_100M,            // 100MHz
           input rst_n,

           input[2: 0]mode,            // 0Sin / 1AM / 2FM / 3PM / 4ASK / 5FSK / 6PSK
           input[23: 0]fc,            // 载波频率
           input[23: 0]fs,            // 调制频率
           input[3: 0]ma,            // 调制度
           input[15: 0]fd,            // 最大频偏
           input[15: 0]pd,             // 最大相移
           input[15: 0]sequenceCode,   // 序列码
           output [13: 0]sig_out // 输出
       );

reg [23: 0]fre;
reg [23: 0]fre2;
wire [15: 0]SIN_sig;
wire [15: 0]SIN_sig2;

reg [15: 0]carrier;
reg [15: 0]modulated;

wire [15: 0]AM_sig;
wire [23: 0]freFM;
reg [15: 0]FM_sig;
wire [11: 0]phasePM;
reg [15: 0]PM_sig;

wire [15: 0]ASK_sig;
wire [15: 0]FSK_sig;
wire [15: 0]PSK_sig;

always@(posedge clk_100M or negedge rst_n)
begin
    if (!rst_n)
    begin
        fre <= 0;
        fre2 <= 0;
        carrier <= 0;
        modulated <= 0;
        FM_sig <= 0;
        PM_sig <= 0;
    end
    else
    begin
        case (mode)
            3'b000:   //Sin
            begin
                fre <= fc;
                fre2 <= 0;
                carrier <= SIN_sig;
                modulated <= 0;
                FM_sig <= 0;
                PM_sig <= 0;
            end
            3'b001:   //AM
            begin
                fre <= fc;
                fre2 <= fs;
                carrier <= SIN_sig;
                modulated <= SIN_sig2;
                FM_sig <= 0;
                PM_sig <= 0;
            end
            3'b010:   //FM
            begin
                fre <= freFM;
                fre2 <= fs;
                carrier <= 0;
                modulated <= SIN_sig2;
                FM_sig <= SIN_sig;
                PM_sig <= 0;
            end
            3'b011:   //PM
            begin
                fre <= fc;
                fre2 <= fs;
                carrier <= 0;
                modulated <= SIN_sig2;
                FM_sig <= 0;
                PM_sig <= SIN_sig;
            end
            3'b100:   //ASK
            begin
                fre <= fc;
                fre2 <= 0;
                carrier <= SIN_sig;
                modulated <= 0;
                FM_sig <= 0;
                PM_sig <= 0;
            end
            3'b101:   //FSK
            begin
                fre <= fc;
                fre2 <= fs;
                carrier <= SIN_sig;
                modulated <= SIN_sig2;
                FM_sig <= 0;
                PM_sig <= 0;
            end
            3'b110:   //PSK
            begin
                fre <= fc;
                fre2 <= 0;
                carrier <= SIN_sig;
                modulated <= 0;
                FM_sig <= 0;
                PM_sig <= 0;
            end
            default:
            begin
                fre <= 0;
                fre2 <= 0;
                carrier <= 0;
                modulated <= 0;
                FM_sig <= 0;
                PM_sig <= 0;
            end
        endcase
    end
end	

//MODE切换模块
MODE MODE_inst
     (
         .clk_100M(clk_100M) , 	// input  clk_100M_sig
         .rst_n(rst_n) , 	// input  rst_n_sig
         .mode(mode) , 	// input [2:0] mode_sig
         .sin_sig(carrier) , 	// input [15:0] sin_sig_sig
         .AM_sig(AM_sig) , 	// input [15:0] AM_sig_sig
         .FM_sig(FM_sig) , 	// input [15:0] FM_sig_sig
         .PM_sig(PM_sig) , 	// input [15:0] PM_sig_sig
         .ASK_sig(ASK_sig) , 	// input [15:0] ASK_sig_sig
         .FSK_sig(FSK_sig) , 	// input [15:0] FSK_sig_sig
         .PSK_sig(PSK_sig) , 	// input [15:0] PSK_sig_sig
         .sig_out(sig_out) 	// output [13:0] sig_out_sig
     );

//SIN波输出模块
SIN SIN_inst
    (
        .clk_100M(clk_100M) , 	// input  clk_100M_sig
        .rst_n(rst_n) , 	// input  rst_n_sig
        .fre(fre) , 	// input [23:0] fre_sig
        .fre2(fre2) , 	// input [23:0] fre2_sig
        .phasePM(phasePM) , 	// input [11:0] phasePM_sig
        .SIN_sig(SIN_sig) , 	// output [15:0] SIN_sig_sig
        .SIN_sig2(SIN_sig2) 	// output [15:0] SIN_sig2_sig
    );

//AM波输出模块
AM AM_inst
   (
       .carrier(carrier) , 	// input [15:0] carrier_sig
       .modulated(modulated) , 	// input [15:0] modulated_sig
       .ma(ma) , 	// input [3:0] ma_sig
       .AM_sig(AM_sig) 	// output [15:0] AM_sig_sig
   );

//FM波输出模块
FM FM_inst
   (
       .fc(fc) , 	// input [23:0] fc_sig
       .modulated(modulated) , 	// input [15:0] modulated_sig
       .fd(fd) , 	// input [15:0] fd_sig
       .freFM(freFM) 	// output [23:0] freFM_sig
   );

//PM波输出模块
PM PM_inst
   (
       .clk_100M(clk_100M) , 	// input  clk_100M_sig
       .rst_n(rst_n) , 	// input  rst_n_sig
       .mode(mode) , 	// input [2:0] mode_sig
       .modulated(modulated) , 	// input [15:0] modulated_sig
       .pd(pd) , 	// input [15:0] pd_sig
       .phasePM(phasePM) 	// output [11:0] phasePM_sig
   );

//ASK波输出模块
ASK ASK_inst
    (
        .clk_100M(clk_100M) , 	// input  clk_100M_sig
        .rst_n(rst_n) , 	// input  rst_n_sig
        .carrier(carrier) , 	// input [15:0] carrier_sig
        .sequenceCode(sequenceCode) , 	// input [15:0] sequenceCode_sig
        .ASK_sig(ASK_sig) 	// output [15:0] ASK_sig_sig
    );

//FSK波输出模块
FSK FSK_inst
    (
        .clk_100M(clk_100M) , 	// input  clk_100M_sig
        .rst_n(rst_n) , 	// input  rst_n_sig
        .carrier(carrier) , 	// input [15:0] carrier_sig
        .modulated(modulated) , 	// input [15:0] modulated_sig
        .sequenceCode(sequenceCode) , 	// input [15:0] sequenceCode_sig
        .FSK_sig(FSK_sig) 	// output [15:0] FSK_sig_sig
    );

//PSK波输出模块
PSK PSK_inst
    (
        .clk_100M(clk_100M) , 	// input  clk_100M_sig
        .rst_n(rst_n) , 	// input  rst_n_sig
        .carrier(carrier) , 	// input [15:0] carrier_sig
        .sequenceCode(sequenceCode) , 	// input [15:0] sequenceCode_sig
        .PSK_sig(PSK_sig) 	// output [15:0] PSK_sig_sig
    );

endmodule