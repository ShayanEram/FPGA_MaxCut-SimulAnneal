-- ==============================================================
-- File generated on Tue Dec 03 21:07:26 -0500 2024
-- Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
-- SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
-- IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
-- Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity maxCut_urem_29ns_cud_div_u is
    generic (
        in0_WIDTH   : INTEGER :=32;
        in1_WIDTH   : INTEGER :=32;
        out_WIDTH   : INTEGER :=32);
    port (
        clk         : in  STD_LOGIC;
        reset       : in  STD_LOGIC;
        ce          : in  STD_LOGIC;
        start       : in  STD_LOGIC;
        dividend    : in  STD_LOGIC_VECTOR(in0_WIDTH-1 downto 0);
        divisor     : in  STD_LOGIC_VECTOR(in1_WIDTH-1 downto 0);
        done        : out STD_LOGIC;
        quot        : out STD_LOGIC_VECTOR(out_WIDTH-1 downto 0);
        remd        : out STD_LOGIC_VECTOR(out_WIDTH-1 downto 0));

    function max (left, right : INTEGER) return INTEGER is
    begin
        if left > right then return left;
        else return right;
        end if;
    end max;

end entity;

architecture rtl of maxCut_urem_29ns_cud_div_u is
    constant cal_WIDTH      : INTEGER := max(in0_WIDTH, in1_WIDTH);

    signal dividend0        : UNSIGNED(in0_WIDTH-1 downto 0);
    signal divisor0         : UNSIGNED(in1_WIDTH-1 downto 0);
    signal dividend_tmp     : UNSIGNED(in0_WIDTH-1 downto 0);
    signal remd_tmp         : UNSIGNED(in0_WIDTH-1 downto 0);
    signal dividend_tmp_mux : UNSIGNED(in0_WIDTH-1 downto 0);
    signal remd_tmp_mux     : UNSIGNED(in0_WIDTH-1 downto 0);
    signal comb_tmp         : UNSIGNED(in0_WIDTH-1 downto 0);
    signal cal_tmp          : UNSIGNED(cal_WIDTH downto 0);
    signal r_stage          : UNSIGNED(in0_WIDTH downto 0);
begin
  quot     <= STD_LOGIC_VECTOR(RESIZE(dividend_tmp, out_WIDTH));
  remd     <= STD_LOGIC_VECTOR(RESIZE(remd_tmp, out_WIDTH));

  tran0_proc : process (clk)
  begin
      if (clk'event and clk='1') then
          if (start = '1') then
              dividend0 <= UNSIGNED(dividend);
              divisor0  <= UNSIGNED(divisor);
          end if;
      end if;
  end process;

  -- r_stage(0)=1:accept input; r_stage(in0_WIDTH)=1:done
  done <= r_stage(in0_WIDTH);
  one_hot : process (clk)
  begin
      if clk'event and clk = '1' then
          if reset = '1' then
              r_stage <= (others => '0'); 
          elsif (ce = '1') then
              r_stage <= r_stage(in0_WIDTH-1 downto 0) & start;
          end if;
      end if;
  end process;

  -- MUXs
  dividend_tmp_mux  <=  dividend_tmp when (r_stage(0) = '0') else
                        dividend0;
  remd_tmp_mux      <=  remd_tmp when (r_stage(0) = '0') else
                        (others => '0');

  comb_tmp <= remd_tmp_mux(in0_WIDTH-2 downto 0) & dividend_tmp_mux(in0_WIDTH-1);
  cal_tmp  <= ('0' & comb_tmp) - ('0' & divisor0);

  process (clk)
  begin
      if (clk'event and clk='1') then
          if (ce = '1') then
              dividend_tmp <= dividend_tmp_mux(in0_WIDTH-2 downto 0) & (not cal_tmp(cal_WIDTH));
              if cal_tmp(cal_WIDTH) = '1' then
                  remd_tmp <= comb_tmp;
              else
                  remd_tmp <= cal_tmp(in0_WIDTH-1 downto 0);
              end if;
          end if;
      end if;
  end process;

end architecture;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity maxCut_urem_29ns_cud_div is
    generic (
        in0_WIDTH   : INTEGER :=32;
        in1_WIDTH   : INTEGER :=32;
        out_WIDTH   : INTEGER :=32);
    port (
        clk         : in  STD_LOGIC;
        reset       : in  STD_LOGIC;
        ce          : in  STD_LOGIC;
        start       : in  STD_LOGIC;
        done        : out STD_LOGIC;
        dividend    : in  STD_LOGIC_VECTOR(in0_WIDTH-1 downto 0);
        divisor     : in  STD_LOGIC_VECTOR(in1_WIDTH-1 downto 0);
        quot        : out STD_LOGIC_VECTOR(out_WIDTH-1 downto 0);
        remd        : out STD_LOGIC_VECTOR(out_WIDTH-1 downto 0));
end entity;

architecture rtl of maxCut_urem_29ns_cud_div is
    component maxCut_urem_29ns_cud_div_u is
        generic (
            in0_WIDTH   : INTEGER :=32;
            in1_WIDTH   : INTEGER :=32;
            out_WIDTH   : INTEGER :=32);
        port (
            reset       : in  STD_LOGIC;
            clk         : in  STD_LOGIC;
            ce          : in  STD_LOGIC;
            start       : in  STD_LOGIC;
            done        : out STD_LOGIC;
            dividend    : in  STD_LOGIC_VECTOR(in0_WIDTH-1 downto 0);
            divisor     : in  STD_LOGIC_VECTOR(in1_WIDTH-1 downto 0);
            quot        : out STD_LOGIC_VECTOR(out_WIDTH-1 downto 0);
            remd        : out STD_LOGIC_VECTOR(out_WIDTH-1 downto 0));
    end component;

    signal start0     : STD_LOGIC := '0';
    signal done0      : STD_LOGIC;
    signal dividend0  : STD_LOGIC_VECTOR(in0_WIDTH-1 downto 0);
    signal divisor0   : STD_LOGIC_VECTOR(in1_WIDTH-1 downto 0);
    signal dividend_u : STD_LOGIC_VECTOR(in0_WIDTH-1 downto 0);
    signal divisor_u  : STD_LOGIC_VECTOR(in1_WIDTH-1 downto 0);
    signal quot_u     : STD_LOGIC_VECTOR(out_WIDTH-1 downto 0);
    signal remd_u     : STD_LOGIC_VECTOR(out_WIDTH-1 downto 0);
begin
    maxCut_urem_29ns_cud_div_u_0 : maxCut_urem_29ns_cud_div_u
        generic map(
            in0_WIDTH   => in0_WIDTH,
            in1_WIDTH   => in1_WIDTH,
            out_WIDTH   => out_WIDTH)
        port map(
            clk         => clk,
            reset       => reset,
            ce          => ce,
            start       => start0,
            done        => done0,
            dividend    => dividend_u,
            divisor     => divisor_u,
            quot        => quot_u,
            remd        => remd_u);

    dividend_u  <= dividend0;
    divisor_u   <= divisor0;

process (clk)
begin
    if (clk'event and clk = '1') then
        if (ce = '1') then
            dividend0 <= dividend;
            divisor0 <= divisor;
            start0 <= start;
        end if;
    end if;
end process;

process (clk)
begin
    if (clk'event and clk = '1') then
        done <= done0;
    end if;
end process;

process (clk)
begin
    if (clk'event and clk = '1') then
        if (done0 = '1') then
            quot <= quot_u;
            remd <= remd_u;
        end if;
    end if;
end process;

end architecture;


Library IEEE;
use IEEE.std_logic_1164.all;

entity maxCut_urem_29ns_cud is
    generic (
        ID : INTEGER;
        NUM_STAGE : INTEGER;
        din0_WIDTH : INTEGER;
        din1_WIDTH : INTEGER;
        dout_WIDTH : INTEGER);
    port (
        clk : IN STD_LOGIC;
        reset : IN STD_LOGIC;
        ce : IN STD_LOGIC;
        start : IN STD_LOGIC;
        done : OUT STD_LOGIC;
        din0 : IN STD_LOGIC_VECTOR(din0_WIDTH - 1 DOWNTO 0);
        din1 : IN STD_LOGIC_VECTOR(din1_WIDTH - 1 DOWNTO 0);
        dout : OUT STD_LOGIC_VECTOR(dout_WIDTH - 1 DOWNTO 0));
end entity;

architecture arch of maxCut_urem_29ns_cud is
    component maxCut_urem_29ns_cud_div is
        generic (
            in0_WIDTH : INTEGER;
            in1_WIDTH : INTEGER;
            out_WIDTH : INTEGER);
        port (
            dividend : IN STD_LOGIC_VECTOR;
            divisor : IN STD_LOGIC_VECTOR;
            remd : OUT STD_LOGIC_VECTOR;
            quot : OUT STD_LOGIC_VECTOR;
            clk : IN STD_LOGIC;
            ce : IN STD_LOGIC;
            reset : IN STD_LOGIC;
            start : IN STD_LOGIC;
            done : OUT STD_LOGIC);
    end component;

    signal sig_quot : STD_LOGIC_VECTOR(dout_WIDTH - 1 DOWNTO 0);
    signal sig_remd : STD_LOGIC_VECTOR(dout_WIDTH - 1 DOWNTO 0);


begin
    maxCut_urem_29ns_cud_div_U :  component maxCut_urem_29ns_cud_div
    generic map (
        in0_WIDTH => din0_WIDTH,
        in1_WIDTH => din1_WIDTH,
        out_WIDTH => dout_WIDTH)
    port map (
        dividend => din0,
        divisor => din1,
        remd => dout,
        quot => sig_quot,
        clk => clk,
        ce => ce,
        reset => reset,
        start => start,
        done => done);

end architecture;


