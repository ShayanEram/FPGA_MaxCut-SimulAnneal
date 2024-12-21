// ==============================================================
// File generated on Tue Dec 03 21:07:26 -0500 2024
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xmaxcut.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XMaxcut_CfgInitialize(XMaxcut *InstancePtr, XMaxcut_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Axilites_BaseAddress = ConfigPtr->Axilites_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XMaxcut_Start(XMaxcut *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMaxcut_ReadReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_AP_CTRL) & 0x80;
    XMaxcut_WriteReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_AP_CTRL, Data | 0x01);
}

u32 XMaxcut_IsDone(XMaxcut *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMaxcut_ReadReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XMaxcut_IsIdle(XMaxcut *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMaxcut_ReadReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XMaxcut_IsReady(XMaxcut *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMaxcut_ReadReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XMaxcut_EnableAutoRestart(XMaxcut *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMaxcut_WriteReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_AP_CTRL, 0x80);
}

void XMaxcut_DisableAutoRestart(XMaxcut *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMaxcut_WriteReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_AP_CTRL, 0);
}

void XMaxcut_InterruptGlobalEnable(XMaxcut *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMaxcut_WriteReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_GIE, 1);
}

void XMaxcut_InterruptGlobalDisable(XMaxcut *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMaxcut_WriteReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_GIE, 0);
}

void XMaxcut_InterruptEnable(XMaxcut *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMaxcut_ReadReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_IER);
    XMaxcut_WriteReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_IER, Register | Mask);
}

void XMaxcut_InterruptDisable(XMaxcut *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMaxcut_ReadReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_IER);
    XMaxcut_WriteReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_IER, Register & (~Mask));
}

void XMaxcut_InterruptClear(XMaxcut *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMaxcut_WriteReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_ISR, Mask);
}

u32 XMaxcut_InterruptGetEnabled(XMaxcut *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMaxcut_ReadReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_IER);
}

u32 XMaxcut_InterruptGetStatus(XMaxcut *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMaxcut_ReadReg(InstancePtr->Axilites_BaseAddress, XMAXCUT_AXILITES_ADDR_ISR);
}

