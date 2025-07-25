// ==============================================================
// File generated on Tue Dec 03 21:07:26 -0500 2024
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================

#ifndef AESL_PKG_HH
#define AESL_PKG_HH

#include "systemc.h"

namespace ap_rtl {

    
////////////////////////////////////////////////////////////////
// Comparisons
////////////////////////////////////////////////////////////////
    
template <int T, int W0, int W1>
bool esl_seteq(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    assert(W0>=1 && W1>=1);
    if (W0 > W1)
        return (i0.range(W1-1, 0) == i1);
    else
        return (i1.range(W0-1, 0) == i0);
    
    assert(W0 == W1);
    return (i0 == i1);
}

template <int T, int W0, int W1>
bool esl_setne(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    assert(W0>=1 && W1>=1);
    if (W0 > W1)
        return (i0.range(W1-1, 0) != i1);
    else
        return (i1.range(W0-1, 0) != i0);

    assert(W0 == W1);
    return (i0 != i1);
}

template <int T, int W0, int W1>
bool esl_seteq(const sc_logic& i0, const sc_logic& i1) {
    assert(W0 == W1);
    return (i0 == i1);
}

template <int T, int W0, int W1>
bool esl_setne(const sc_logic& i0, const sc_logic& i1) {
    assert(W0 == W1);
    return (i0 != i1);
}

template <int T, int W0>
bool esl_not(bool i0) {
    return (!i0);
}

template <int T, int W0>
sc_logic esl_not(const sc_logic& i0) {
    return (~i0);
}

template <int T, int W0, int W1>
bool esl_setle(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return false;
    return (sc_biguint<W0>(i0) <= sc_biguint<W1>(i1));
}

template <int T, int W0, int W1>
bool esl_setge(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return false;
    return (sc_biguint<W0>(i0) >= sc_biguint<W1>(i1));
}

template <int T, int W0, int W1>
bool esl_setlt(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return false;
    return (sc_biguint<W0>(i0) < sc_biguint<W1>(i1));
}

template <int T, int W0, int W1>
bool esl_setgt(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return false;
    return (sc_biguint<W0>(i0) > sc_biguint<W1>(i1));
}

template <int T, int W0, int W1>
sc_lv<1> esl_icmp_eq(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    assert(W0 == W1);
    if (!i0.is_01() || !i1.is_01()) return sc_lv<1>();
    return sc_lv<1>(i0 == i1);
}

template <int T, int W0, int W1>
sc_lv<1> esl_icmp_ne(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    assert(W0 == W1);
    if (!i0.is_01() || !i1.is_01()) return sc_lv<1>();
    return sc_lv<1>(i0 != i1);
}

template <int T, int W0, int W1>
sc_lv<1> esl_icmp_ugt(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<1>();
    return (sc_biguint<W0>(i0) > sc_biguint<W1>(i1));
}

template <int T, int W0, int W1>
sc_lv<1> esl_icmp_uge(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<1>();
    return (sc_biguint<W0>(i0) >= sc_biguint<W1>(i1));
}

template <int T, int W0, int W1>
sc_lv<1> esl_icmp_ult(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<1>();
    return (sc_biguint<W0>(i0) < sc_biguint<W1>(i1));
}

template <int T, int W0, int W1>
sc_lv<1> esl_icmp_ule(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<1>();
    return (sc_biguint<W0>(i0) <= sc_biguint<W1>(i1));
}

template <int T, int W0, int W1>
sc_lv<1> esl_icmp_sgt(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<1>();
    return (sc_bigint<W0>(i0) > sc_bigint<W1>(i1));
}

template <int T, int W0, int W1>
sc_lv<1> esl_icmp_sge(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<1>();
    return (sc_bigint<W0>(i0) >= sc_bigint<W1>(i1));
}

template <int T, int W0, int W1>
sc_lv<1> esl_icmp_slt(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<1>();
    return (sc_bigint<W0>(i0) < sc_bigint<W1>(i1));
}

template <int T, int W0, int W1>
sc_lv<1> esl_icmp_sle(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<1>();
    return (sc_bigint<W0>(i0) <= sc_bigint<W1>(i1));
}


template <int T, int W0>
sc_lv<T> esl_trunc(const sc_lv<W0>& i0) {
    assert(T <= W0);
    return (i0.range(T-1, 0));
}

template <int T, int W0>
sc_lv<T> esl_sext(const sc_lv<W0>& i0) {
    assert(T >= W0);
    if (!i0.is_01()) return sc_lv<T>();
    return ((sc_lv<T>)(sc_bigint<W0>(i0)));
}

template <int T, int W0>
sc_lv<T> esl_zext(const sc_lv<W0>& i0) {
    assert(T >= W0);
    if (!i0.is_01()) return sc_lv<T>();
    return ((sc_lv<T>)(sc_biguint<W0>(i0)));
}

template <int T, int W0>
sc_lv<T> esl_bitcast(const sc_lv<W0>& i0) {
    assert(T == W0);
    return i0;
}

////////////////////////////////////////////////////////////////
// Conversions
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
// Logic/Arithmatic operations
////////////////////////////////////////////////////////////////

template <int T, int W0, int W1>
sc_lv<T> esl_and(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    assert(W0 == W1);
    return (i0 & i1);
}

template <int T, int W0, int W1>
sc_lv<T> esl_or(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    assert(W0 == W1);
    return (i0 | i1);
}
template <int T, int W0, int W1>
sc_lv<T> esl_xor(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    assert(W0 == W1);
    return (i0 ^ i1);
}
template <int T, int W0, int W1>
sc_lv<T> esl_shl(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    //assert(W1 <= 32);
    if (!i1.is_01()) return sc_lv<T>();
    return (i0 << (unsigned short)i1.to_uint());
}

template <int T, int W0, int W1>
sc_lv<T> esl_lshr(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    //assert(W1 <= 32);
    if (!i1.is_01()) return sc_lv<T>();
    return (i0 >> (unsigned short)i1.to_uint());
}
    
template <int T, int W0, int W1>
sc_lv<T> esl_ashr(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    //assert(W1 <= 32);
    if (!i0.is_01() || !i1.is_01()) return sc_lv<T>();
    return (sc_bigint<W0>(i0) >> (unsigned short)i1.to_uint());
}


template <int T, int W0, int W1>
sc_lv<T> esl_add(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<T>();
    return (sc_bigint<W0>(i0) + sc_biguint<W1>(i1));
}

template <int T, int W0, int W1>
sc_lv<T> esl_sub(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<T>();
    return (sc_bigint<W0>(i0) - sc_biguint<W1>(i1));
}

template <int T, int W0, int W1>
sc_lv<T> esl_mul_UU(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<T>();
    return (sc_biguint<W0>(i0) * sc_biguint<W1>(i1));
}

template <int T, int W0, int W1>
sc_lv<T> esl_mul_SU(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<T>();
    return (sc_bigint<W0>(i0) * sc_biguint<W1>(i1));
}

template <int T, int W0, int W1>
sc_lv<T> esl_mul_US(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<T>();
    return (sc_biguint<W0>(i0) * sc_bigint<W1>(i1));
}

template <int T, int W0, int W1>
sc_lv<T> esl_mul_SS(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<T>();
    return (sc_bigint<W0>(i0) * sc_bigint<W1>(i1));
}

template <int T, int W0, int W1>
sc_lv<T> esl_udiv(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<T>();
    sc_biguint<W1> v1(i1);
    if (v1.to_uint() == 0) return sc_lv<T>();
    return (sc_biguint<W0>(i0) / v1);
}

template <int T, int W0, int W1>
sc_lv<T> esl_sdiv(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<T>();
    sc_bigint<W1> v1(i1);
    if (v1.to_uint() == 0) return sc_lv<T>();
    return (sc_bigint<W0>(i0) / v1);
}

template <int T, int W0, int W1>
sc_lv<T> esl_urem(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<T>();
    sc_biguint<W1> v1(i1);
    if (v1.to_uint() == 0) return sc_lv<T>();
    return (sc_biguint<W0>(i0) % v1);
}
    
template <int T, int W0, int W1>
sc_lv<T> esl_srem(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    if (!i0.is_01() || !i1.is_01()) return sc_lv<T>();
    sc_bigint<W1> v1(i1);
    if (v1.to_uint() == 0) return sc_lv<T>();
    return (sc_bigint<W0>(i0) % v1);
}

template <int T, int W0>
sc_lv<T> esl_ctlz(const sc_lv<W0>& i0) {
    int count = 0;
    for (unsigned i = W0-1; i >= 0; --i) {
        if (i0[i] == SC_LOGIC_0) count ++;
        else break;
    }
    return count;
}

template <int T, int W0>
sc_lv<T> esl_cttz(const sc_lv<W0>& i0) {
    int count = 0;
    for (unsigned i = 0; i < W0; ++i) {
        if (i0[i] == SC_LOGIC_0) count ++;
        else break;
    }
    return count;
}


////////////////////////////////////////////////////////////////
// Other operations
////////////////////////////////////////////////////////////////
template <int T, int W0, int W1, int W2>
sc_lv<T> esl_select(const sc_lv<W0>& i0,
                    const sc_lv<W1>& i1, const sc_lv<W2>& i2) {
    assert((W0 == 1) && (W1 == W2));
    if (!i0[0].is_01()) return sc_lv<T>();
    bool flag = (i0[0].to_bool());
    return (flag ? i1 : i2);
}


template <int W0, int W1>
inline sc_lv<W0+W1> esl_concat(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    return (i0, i1);
}

template <int T, int W0, int W1>
inline sc_lv<T> esl_bitselect(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    assert(T == 1);
    if (!i1.is_01()) return sc_lv<T>();
    unsigned int loc = (sc_biguint<W1>(i1)).to_uint();
    //assert(W0 >= loc);
    if (W0 <= loc)
        return sc_lv<T>();
    return i0.range(loc, loc);
}
    
template <int T, int W0, int W1, int W2>
inline sc_lv<T> esl_bitset(const sc_lv<W0>& i0,
                           const sc_lv<W1>& i1, const sc_lv<W2>& i2) {
    assert(T == W0);
    if (!i1.is_01()) return sc_lv<T>();
    unsigned int loc = (sc_biguint<W1>(i1)).to_uint();
    //assert(W0 >= loc);
    if (W0 <= loc)
        return sc_lv<T>();
    sc_lv<W0> res = i0;
    res[loc] = i2.or_reduce();
    return res;
}

template <int T, int W0, int W1, int W2>
inline sc_lv<T> esl_partselect(const sc_lv<W0>& i0,
                               const sc_lv<W1>& iLo, const sc_lv<W2>& iHi) {
    if (!iLo.is_01() || !iHi.is_01()) return sc_lv<T>();
    unsigned int Lo = (sc_biguint<W1>(iLo)).to_uint();
    unsigned int Hi = (sc_biguint<W2>(iHi)).to_uint();
    unsigned int rsize = abs((int)(Hi-Lo)) + 1;
    // Warning out the dont-care situation.
    if (Lo >= W0 || Hi >= W0)  {
//        std::cout << "Warning: partselect out of range!\n";
        return sc_lv<T>();
    }
    assert(W0 >= rsize);
    return i0.range(Hi, Lo);
}

template <int T, int W0, int W1, int WLo, int WHi>
inline sc_lv<T> esl_partset(const sc_lv<W0>& i0,
                            const sc_lv<W1>& i1,
                            const sc_lv<WLo>& iLo, const sc_lv<WHi>& iHi) {
    if (!iLo.is_01() || !iHi.is_01()) return sc_lv<T>();
    assert(W0 == T);
    unsigned int Lo = (sc_biguint<WLo>(iLo)).to_uint();
    unsigned int Hi = (sc_biguint<WHi>(iHi)).to_uint();
    unsigned int rsize = abs((int)(Lo-Hi)) + 1;
    // Warning out the dont-care situation.
    if (Hi >= T || Lo >= T) {
//        std::cout << "Warning: partset out of range!\n";
        return sc_lv<T>();
    }
    assert(W0 >= rsize);
    sc_lv<T> res = i0;
    res.range(Hi, Lo) = ((sc_lv<T>)i1).range(rsize-1, 0);
    return res;
}

template <int T, int W0>
sc_lv<T> esl_orreduce(const sc_lv<W0>& i0) {
    assert(T == 1);
    sc_lv<1> res;
    res[0] = i0.or_reduce();
    return res;
}

template <int T, int W0>
inline sc_lv<T> esl_andreduce(const sc_lv<W0>& i0) {
    assert(T == 1);
    sc_lv<1> res;
    res[0] = i0.and_reduce();
    return res;
}

template <int T, int W0>
inline sc_lv<T> esl_xorreduce(const sc_lv<W0>& i0) {
    assert(T == 1);
    sc_lv<1> res;
    res[0] = i0.xor_reduce();
    return res;
}

template <int T, int W0>
inline sc_lv<T> esl_nandreduce(const sc_lv<W0>& i0) {
    assert(T == 1);
    sc_lv<1> res;
    res[0] = i0.nand_reduce();
    return res;
}

template <int T, int W0>
inline sc_lv<T> esl_xnorreduce(const sc_lv<W0>& i0) {
    assert(T == 1);
    sc_lv<1> res;
    res[0] = i0.xnor_reduce();
    return res;
}

template <int T, int W0>
inline sc_lv<T> esl_norreduce(const sc_lv<W0>& i0) {
    assert(T == 1);
    sc_lv<1> res;
    res[0] = i0.nor_reduce();
    return res;
}

    
////////////////////////////////////////////////////////////////
// Floating point operations
////////////////////////////////////////////////////////////////
struct esl_FP {
static float esl_INTSP(unsigned int x) { return (*(float*)(&(x))); }
static double esl_INTDP(unsigned long long x) { return (*(double*)(&(x))); }

static unsigned int esl_SPINT(float x) { return (*(unsigned int*)(&(x))); }
static unsigned long long esl_DPINT(double x) { return (*(unsigned long long*)(&(x))); }
};

#define esl_LVSP(x) esl_FP::esl_INTSP((x).to_uint())
#define esl_LVDP(x) esl_FP::esl_INTDP((x).to_uint64())

#define esl_sitodp(lv) esl_FP::esl_DPINT(double((lv).to_int()))
#define esl_dptosi(lv) (int(esl_LVDP(lv)))

#define esl_dadd(x, y) \
esl_FP::esl_DPINT(esl_LVDP(x) + esl_LVDP(y))
#define esl_fadd(x, y) \
esl_FP::esl_SPINT(esl_LVSP(x) + esl_LVSP(y))

#define esl_dsub(x, y) \
esl_FP::esl_DPINT(esl_LVDP(x) - esl_LVDP(y))
#define esl_fsub(x, y) \
esl_FP::esl_SPINT(esl_LVSP(x) - esl_LVSP(y))

#define esl_dmul(x, y) \
esl_FP::esl_DPINT(esl_LVDP(x) * esl_LVDP(y))
#define esl_fmul(x, y) \
esl_FP::esl_SPINT(esl_LVSP(x) * esl_LVSP(y))

#define esl_ddiv(x, y) \
esl_FP::esl_DPINT(esl_LVDP(x) / esl_LVDP(y))
#define esl_fdiv(x, y) \
esl_FP::esl_SPINT(esl_LVSP(x) / esl_LVSP(y))

#define esl_drem(x, y) \
esl_FP::esl_DPINT(esl_LVDP(x) % esl_LVDP(y))
#define esl_frem(x, y) \
esl_FP::esl_SPINT(esl_LVSP(x) % esl_LVSP(y))

//#define esl_dsqrt(x) esl_FP::esl_DPINT(sqrt(esl_LVDP(x)))
//#define esl_fsqrt(x) esl_FP::esl_SPINT(sqrt(esl_LVSP(x)))


#define esl_DFCMP_FALSE(x, y) \
(false)

#define esl_DFCMP_ORD(x, y) \
(!isnan(esl_LVDP(x)) & !isnan(esl_LVDP(y)))
#define esl_DFCMP_OEQ(x, y) \
(esl_DFCMP_ORD(x, y) & (esl_LVDP(x) == esl_LVDP(y)))
#define esl_DFCMP_OGT(x, y) \
(esl_DFCMP_ORD(x, y) & (esl_LVDP(x) > esl_LVDP(y)))
#define esl_DFCMP_OGE(x, y) \
(esl_DFCMP_ORD(x, y) & (esl_LVDP(x) >= esl_LVDP(y)))
#define esl_DFCMP_OLT(x, y) \
(esl_DFCMP_ORD(x, y) & (esl_LVDP(x) < esl_LVDP(y)))
#define esl_DFCMP_OLE(x, y) \
(esl_DFCMP_ORD(x, y) & (esl_LVDP(x) <= esl_LVDP(y)))
#define esl_DFCMP_ONE(x, y) \
(esl_DFCMP_UNO(x, y) & (esl_LVDP(x) != esl_LVDP(y)))

#define esl_DFCMP_UNO(x, y) \
(isnan(esl_LVDP(x)) | isnan(esl_LVDP(y)))
#define esl_DFCMP_UEQ(x, y) \
(esl_DFCMP_UNO(x, y) | (esl_LVDP(x) == esl_LVDP(y)))
#define esl_DFCMP_UGT(x, y) \
(esl_DFCMP_UNO(x, y) | (esl_LVDP(x) > esl_LVDP(y)))
#define esl_DFCMP_UGE(x, y) \
(esl_DFCMP_UNO(x, y) | (esl_LVDP(x) >= esl_LVDP(y)))
#define esl_DFCMP_ULT(x, y) \
(esl_DFCMP_UNO(x, y) | (esl_LVDP(x) < esl_LVDP(y)))
#define esl_DFCMP_ULE(x, y) \
(esl_DFCMP_UNO(x, y) | (esl_LVDP(x) <= esl_LVDP(y)))
#define esl_DFCMP_UNE(x, y) \
(esl_DFCMP_UNO(x, y) | (esl_LVDP(x) != esl_LVDP(y)))

#define esl_DFCMP_TRUE(x, y) \
(true)

template <int T, int W0>
sc_lv<T> esl_dsqrt(const sc_lv<W0>& x) {
    sc_lv<T> ret = esl_FP::esl_DPINT(sqrt(esl_LVDP(x)));
    return ret;
}

template <int T, int W0>
sc_lv<T> esl_fsqrt(const sc_lv<W0>& x) {
    sc_lv<T> ret = esl_FP::esl_SPINT(sqrt(esl_LVSP(x)));
    return ret;
}

template <int T, int W0, int W1>
sc_lv<T> esl_getelementptr(const sc_lv<W0>& i0, const sc_lv<W1>& i1) {
    return esl_add<T, W0, W1>(i0, i1);
}

}


#endif





