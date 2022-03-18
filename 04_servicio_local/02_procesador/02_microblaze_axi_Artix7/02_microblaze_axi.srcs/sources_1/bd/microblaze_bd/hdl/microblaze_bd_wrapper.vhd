--Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2019.2 (lin64) Build 2708876 Wed Nov  6 21:39:14 MST 2019
--Date        : Thu Jun  4 22:05:40 2020
--Host        : debian running 64-bit Debian GNU/Linux 10 (buster)
--Command     : generate_target microblaze_bd_wrapper.bd
--Design      : microblaze_bd_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity microblaze_bd_wrapper is
  port (
    clk : in STD_LOGIC;
    leds_tri_o : out STD_LOGIC_VECTOR ( 3 downto 0 );
    pushs_tri_i : in STD_LOGIC_VECTOR ( 3 downto 0 );
    reset : in STD_LOGIC;
    uart_rtl_0_rxd : in STD_LOGIC;
    uart_rtl_0_txd : out STD_LOGIC;
    uart_rxd : in STD_LOGIC;
    uart_txd : out STD_LOGIC
  );
end microblaze_bd_wrapper;

architecture STRUCTURE of microblaze_bd_wrapper is
  component microblaze_bd is
  port (
    reset : in STD_LOGIC;
    clk : in STD_LOGIC;
    uart_rxd : in STD_LOGIC;
    uart_txd : out STD_LOGIC;
    pushs_tri_i : in STD_LOGIC_VECTOR ( 3 downto 0 );
    leds_tri_o : out STD_LOGIC_VECTOR ( 3 downto 0 );
    uart_rtl_0_rxd : in STD_LOGIC;
    uart_rtl_0_txd : out STD_LOGIC
  );
  end component microblaze_bd;
begin
microblaze_bd_i: component microblaze_bd
     port map (
      clk => clk,
      leds_tri_o(3 downto 0) => leds_tri_o(3 downto 0),
      pushs_tri_i(3 downto 0) => pushs_tri_i(3 downto 0),
      reset => reset,
      uart_rtl_0_rxd => uart_rtl_0_rxd,
      uart_rtl_0_txd => uart_rtl_0_txd,
      uart_rxd => uart_rxd,
      uart_txd => uart_txd
    );
end STRUCTURE;
