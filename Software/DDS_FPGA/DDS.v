module DDS
       (
           input CLK_50M,
           input rst_n,
           input [11: 0]ADDR,
           input RD, WR,
           inout [15: 0]DATA,
           inout [3: 0]KEY_H, KEY_V,

           output [13: 0]sig_out,
           output clk_100M,
           output squareWave,
			  output Code
       ) ;

wire cs0, cs1, cs2, cs3; //keyboard and 8688
wire [15: 0] rddat0, rddat1, rddat2, rddat3;
wire [15: 0] otdata0, otdata1, otdata2, otdata3;

reg [23: 0]fc;
reg [23: 0]fs;
reg [3: 0]ma;
reg [15: 0]fd;
reg [15: 0]pd;
reg [15: 0]sequenceCode;

wire [15: 0]sigChose;
wire [15: 0]dataChose;
wire [15: 0]dataIn;

reg[31: 0]count;
reg [3: 0]sequence;
always@(posedge clk_100M or negedge rst_n)
begin
    if (!rst_n)
    begin
        count <= 0;
        sequence <= 0;
    end
    else
    begin
        count <= (count < 9765) ? count + 1 : 0; //10239.6Hz
		  if(count==9765)
		  begin
		      sequence <= sequence - 1;	
		  end
    end
end

assign Code = sequenceCode[sequence];

SquareWave SquareWave_inst
           (
               .clk(CLK_50M) , 	// input  clk_sig
               .rst_n(rst_n) , 	// input  rst_n_sig
               .squareWave(squareWave) 	// output  squareWave_sig
           );

always@(posedge CLK_50M or negedge rst_n)
begin
    if (!rst_n)
    begin
        fc <= 0;
        fs <= 0;
        ma <= 0;
        fd <= 0;
        pd <= 0;
        sequenceCode <= 0;
    end
    else
    begin
        case (dataChose)
            0:
            begin
                if (dataIn[15: 8] == 0)
                begin
                    fc[23: 16] <= dataIn[7: 0];
                end
                else
                begin
                    fc[15: 0] <= dataIn;
                end
            end
            1:
            begin
                if (dataIn[15: 8] == 0)
                begin
                    fs[23: 16] <= dataIn[7: 0];
                end
                else
                begin
                    fs[15: 0] <= dataIn;
                end
            end
            2:
            begin
                ma <= dataIn[3: 0];
            end
            3:
            begin
                fd <= dataIn;
            end
            4:
            begin
                pd <= dataIn;
            end
            5:
            begin
                sequenceCode <= dataIn;
            end
            default:
            begin
                fc <= 0;
                fs <= 0;
                ma <= 0;
                fd <= 0;
                pd <= 0;
                sequenceCode <= 0;
            end
        endcase
    end
end

PLL_100M	PLL_100M_inst
         (
             .inclk0 ( CLK_50M ),
             .c0 ( clk_100M ),
         );

DDS_generate DDS_generate_inst
             (
                 .clk_100M(clk_100M) , 	// input  clk_100M_sig
                 .rst_n(rst_n) , 	// input  rst_n_sig
                 .mode(sigChose[2: 0]) , 	// input [2:0] mode_sig
                 .fc(fc) , 	// input [23:0] fc_sig
                 .fs(fs) , 	// input [23:0] fs_sig
                 .ma(ma) , 	// input [3:0] ma_sig
                 .fd(fd) , 	// input [15:0] fd_sig
                 .pd(pd) , 	// input [15:0] pd_sig
                 .sequenceCode(sequenceCode) , 	// input [15:0] sequenceCode_sig
                 .sig_out(sig_out) 	// output [13:0] sig_out_sig
             );

BUS BUS_inst
    (
        .clk(CLK_50M) , 	// input  clk_sig
        .rst_n(rst_n) , 	// input  rst_n_sig
        .ADDR(ADDR) , 	// input [11:0] ADDR_sig
        .RD(RD) , 	// input  RD_sig
        .WR(WR) , 	// input  WR_sig
        .DATA(DATA) , 	// inout [15:0] DATA_sig

        .cs0(cs0) , 	// output  cs0_sig
        .cs1(cs1) , 	// output  cs1_sig
        .cs2(cs2) , 	// output  cs2_sig
        .cs3(cs3) , 	// output  cs3_sig

        .rddat0(rddat0) , 	// input [15:0] rddat0_sig
        .rddat1(rddat1) , 	// input [15:0] rddat1_sig
        .rddat2(rddat2) , 	// input [15:0] rddat2_sig
        .rddat3(rddat3) , 	// input [15:0] rddat3_sig

        .otdata0(otdata0) , 	// output [15:0] otdata0_sig
        .otdata1(otdata1) , 	// output [15:0] otdata1_sig
        .otdata2(otdata2) , 	// output [15:0] otdata2_sig
        .otdata3(otdata3) 	// output [15:0] otdata3_sig
    );

KEY KEY_inst
    (
        .clk(CLK_50M) , 	// input  clk_sig
        .rst_n(rst_n) , 	// input  rst_n_sig
        .rddat(rddat0) , 	// output [15:0] rddat_sig
        .irq() , 	// output  irq_sig
        .cs(cs0) , 	// input  cs_sig
        .KEY_H(KEY_H) , 	// inout [3:0] KEY_H_sig
        .KEY_V(KEY_V) 	// inout [3:0] KEY_V_sig
    );

WaveData WaveData_inst
         (
             .clk(CLK_50M) , 	// input  clk_sig
             .rst_n(rst_n) , 	// input  rst_n_sig
             .otdata(otdata1) , 	// input [15:0] otdata_sig
             .cs(cs1) , 	// input  cs_sig
             .waveData(sigChose) 	// output [16:0] waveData_sig
         );
WaveData WaveData_inst2
         (
             .clk(CLK_50M) , 	// input  clk_sig
             .rst_n(rst_n) , 	// input  rst_n_sig
             .otdata(otdata2) , 	// input [15:0] otdata_sig
             .cs(cs2) , 	// input  cs_sig
             .waveData(dataChose) 	// output [16:0] waveData_sig
         );
WaveData WaveData_inst3
         (
             .clk(CLK_50M) , 	// input  clk_sig
             .rst_n(rst_n) , 	// input  rst_n_sig
             .otdata(otdata3) , 	// input [15:0] otdata_sig
             .cs(cs3) , 	// input  cs_sig
             .waveData(dataIn) 	// output [16:0] waveData_sig
         );

endmodule