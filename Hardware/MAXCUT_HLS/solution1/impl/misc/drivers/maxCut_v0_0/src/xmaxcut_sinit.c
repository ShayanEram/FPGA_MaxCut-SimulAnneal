// ==============================================================
// File generated on Tue Dec 03 21:07:26 -0500 2024
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xmaxcut.h"

extern XMaxcut_Config XMaxcut_ConfigTable[];

XMaxcut_Config *XMaxcut_LookupConfig(u16 DeviceId) {
	XMaxcut_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XMAXCUT_NUM_INSTANCES; Index++) {
		if (XMaxcut_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XMaxcut_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XMaxcut_Initialize(XMaxcut *InstancePtr, u16 DeviceId) {
	XMaxcut_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XMaxcut_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XMaxcut_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

