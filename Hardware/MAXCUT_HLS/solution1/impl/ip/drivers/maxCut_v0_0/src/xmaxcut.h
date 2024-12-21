// ==============================================================
// File generated on Tue Dec 03 21:07:26 -0500 2024
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XMAXCUT_H
#define XMAXCUT_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xmaxcut_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Axilites_BaseAddress;
} XMaxcut_Config;
#endif

typedef struct {
    u32 Axilites_BaseAddress;
    u32 IsReady;
} XMaxcut;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XMaxcut_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XMaxcut_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XMaxcut_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XMaxcut_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XMaxcut_Initialize(XMaxcut *InstancePtr, u16 DeviceId);
XMaxcut_Config* XMaxcut_LookupConfig(u16 DeviceId);
int XMaxcut_CfgInitialize(XMaxcut *InstancePtr, XMaxcut_Config *ConfigPtr);
#else
int XMaxcut_Initialize(XMaxcut *InstancePtr, const char* InstanceName);
int XMaxcut_Release(XMaxcut *InstancePtr);
#endif

void XMaxcut_Start(XMaxcut *InstancePtr);
u32 XMaxcut_IsDone(XMaxcut *InstancePtr);
u32 XMaxcut_IsIdle(XMaxcut *InstancePtr);
u32 XMaxcut_IsReady(XMaxcut *InstancePtr);
void XMaxcut_EnableAutoRestart(XMaxcut *InstancePtr);
void XMaxcut_DisableAutoRestart(XMaxcut *InstancePtr);


void XMaxcut_InterruptGlobalEnable(XMaxcut *InstancePtr);
void XMaxcut_InterruptGlobalDisable(XMaxcut *InstancePtr);
void XMaxcut_InterruptEnable(XMaxcut *InstancePtr, u32 Mask);
void XMaxcut_InterruptDisable(XMaxcut *InstancePtr, u32 Mask);
void XMaxcut_InterruptClear(XMaxcut *InstancePtr, u32 Mask);
u32 XMaxcut_InterruptGetEnabled(XMaxcut *InstancePtr);
u32 XMaxcut_InterruptGetStatus(XMaxcut *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
