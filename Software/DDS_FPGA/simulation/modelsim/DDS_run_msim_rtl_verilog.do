transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/KEY.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/BUS.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/DDS.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/DDS_generate.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/MODE.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/SIN.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/AM.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/FM.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/DIVIDE_s.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/MULT_s.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/PLL_100M.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/ROM_Sin.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/ASK.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/PSK.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/WaveData.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/PM.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/FSK.v}
vlog -vlog01compat -work work +incdir+F:/Users/Fu\ Yuhao/Desktop/Quartus/DDS {F:/Users/Fu Yuhao/Desktop/Quartus/DDS/SquareWave.v}

