library verilog;
use verilog.vl_types.all;
entity \BUS\ is
    port(
        clk             : in     vl_logic;
        rst_n           : in     vl_logic;
        ADDR            : in     vl_logic_vector(11 downto 0);
        RD              : in     vl_logic;
        WR              : in     vl_logic;
        DATA            : inout  vl_logic_vector(15 downto 0);
        cs0             : out    vl_logic;
        cs1             : out    vl_logic;
        cs2             : out    vl_logic;
        cs3             : out    vl_logic;
        rddat0          : in     vl_logic_vector(15 downto 0);
        rddat1          : in     vl_logic_vector(15 downto 0);
        rddat2          : in     vl_logic_vector(15 downto 0);
        rddat3          : in     vl_logic_vector(15 downto 0);
        otdata0         : out    vl_logic_vector(15 downto 0);
        otdata1         : out    vl_logic_vector(15 downto 0);
        otdata2         : out    vl_logic_vector(15 downto 0);
        otdata3         : out    vl_logic_vector(15 downto 0)
    );
end \BUS\;
