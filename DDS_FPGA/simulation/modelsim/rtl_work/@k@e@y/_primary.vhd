library verilog;
use verilog.vl_types.all;
entity KEY is
    port(
        clk             : in     vl_logic;
        rst_n           : in     vl_logic;
        rddat           : out    vl_logic_vector(15 downto 0);
        irq             : out    vl_logic;
        cs              : in     vl_logic;
        KEY_H           : inout  vl_logic_vector(3 downto 0);
        KEY_V           : inout  vl_logic_vector(3 downto 0)
    );
end KEY;
