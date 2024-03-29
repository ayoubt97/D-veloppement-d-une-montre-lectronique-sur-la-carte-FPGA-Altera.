
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity CS2E is

-------------------------------------------------------------------------------
--                             Port Declarations                             --
-------------------------------------------------------------------------------
port (
	-- Inputs
	CLOCK_50            : in std_logic;
	CLOCK_27            : in std_logic;
	KEY                 : in std_logic_vector (3 downto 0);
	SW                  : in std_logic_vector (9 downto 0);

	--  Communication
	UART_RXD            : in std_logic;

	--  Audio
	AUD_ADCDAT			: in std_logic;

	-- Bidirectionals
	GPIO_0              : inout std_logic_vector (36 downto 0);
	GPIO_1              : inout std_logic_vector (36 downto 0);

	--  Memory (SRAM)
	SRAM_DQ             : inout std_logic_vector (15 downto 0);
	
	--  Memory (SDRAM)
	DRAM_DQ				: inout std_logic_vector (15 downto 0);

	--  PS2 Port
	PS2_CLK				: inout std_logic;
	PS2_DAT				: inout std_logic;
	
	--  Audio
	AUD_BCLK			: inout std_logic;
	AUD_ADCLRCK			: inout std_logic;
	AUD_DACLRCK			: inout std_logic;

	--  AV Config
	I2C_SDAT			: inout std_logic;
	
	-- Outputs
	TD_RESET			: out std_logic;

	--  Simple
	LEDG                : out std_logic_vector (7 downto 0);
	LEDR                : out std_logic_vector (9 downto 0);
	HEX0                : out std_logic_vector (6 downto 0);
	HEX1                : out std_logic_vector (6 downto 0);
	HEX2                : out std_logic_vector (6 downto 0);
	HEX3                : out std_logic_vector (6 downto 0);

	--  Memory (SRAM)
	SRAM_ADDR           : out std_logic_vector (17 downto 0);
	SRAM_CE_N           : out std_logic;
	SRAM_WE_N           : out std_logic;
	SRAM_OE_N           : out std_logic;
	SRAM_UB_N           : out std_logic;
	SRAM_LB_N           : out std_logic;

	--  Communication
	UART_TXD            : out std_logic;
	
	-- Memory (SDRAM)
	DRAM_ADDR			: out std_logic_vector (11 downto 0);
	DRAM_BA_1			: buffer std_logic;
	DRAM_BA_0			: buffer std_logic;
	DRAM_CAS_N			: out std_logic;
	DRAM_RAS_N			: out std_logic;
	DRAM_CLK			: out std_logic;
	DRAM_CKE			: out std_logic;
	DRAM_CS_N			: out std_logic;
	DRAM_WE_N			: out std_logic;
	DRAM_UDQM			: buffer std_logic;
	DRAM_LDQM			: buffer std_logic;

	--  Audio
	AUD_XCK				: out std_logic;
	AUD_DACDAT			: out std_logic;
	
	--  VGA
	VGA_CLK				: out std_logic;
	VGA_HS				: out std_logic;
	VGA_VS				: out std_logic;
	VGA_R				: out std_logic_vector (3 downto 0);
	VGA_G				: out std_logic_vector (3 downto 0);
	VGA_B				: out std_logic_vector (3 downto 0);
	
	--  AV Config
	I2C_SCLK			: out std_logic
	);
end CS2E;


architecture sys of CS2E is

-------------------------------------------------------------------------------
--                           Subentity Declarations                          --
-------------------------------------------------------------------------------
    component tp2 is
        port (
            clk_clk       : in    std_logic                     := 'X';             -- clk
            reset_reset_n : in    std_logic                     := 'X';             -- reset_n
            sdram_addr    : out   std_logic_vector(11 downto 0);                    -- addr
            sdram_ba      : out   std_logic_vector(1 downto 0);                     -- ba
            sdram_cas_n   : out   std_logic;                                        -- cas_n
            sdram_cke     : out   std_logic;                                        -- cke
            sdram_cs_n    : out   std_logic;                                        -- cs_n
            sdram_dq      : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
            sdram_dqm     : out   std_logic_vector(1 downto 0);                     -- dqm
            sdram_ras_n   : out   std_logic;                                        -- ras_n
            sdram_we_n    : out   std_logic                                         -- we_n
        );

signal BA : std_logic_vector(1 downto 0);
signal DQM : std_logic_vector(1 downto 0);
begin

DRAM_BA_0 <= BA(0);
DRAM_BA_1 <= BA(1);
DRAM_LDQM <= DQM(0);
DRAM_UDQM <= DQM(1);


u0 : component tp2
        port map (
            clk_clk       => CONNECTED_TO_clk_clk,       --   clk.clk
            reset_reset_n => CONNECTED_TO_reset_reset_n, -- reset.reset_n
            sdram_addr    => CONNECTED_TO_sdram_addr,    -- sdram.addr
            sdram_ba      => CONNECTED_TO_sdram_ba,      --      .ba
            sdram_cas_n   => CONNECTED_TO_sdram_cas_n,   --      .cas_n
            sdram_cke     => CONNECTED_TO_sdram_cke,     --      .cke
            sdram_cs_n    => CONNECTED_TO_sdram_cs_n,    --      .cs_n
            sdram_dq      => CONNECTED_TO_sdram_dq,      --      .dq
            sdram_dqm     => CONNECTED_TO_sdram_dqm,     --      .dqm
            sdram_ras_n   => CONNECTED_TO_sdram_ras_n,   --      .ras_n
            sdram_we_n    => CONNECTED_TO_sdram_we_n     --      .we_n
        );


end sys;

