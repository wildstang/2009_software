//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang
//  @ File Name : WsI2cEncoder.h
//  @ Date : 2/13/2009
//  @ Author : 
//
//


#if !defined(_WSI2CENCODER_H)
#define _WSI2CENCODER_H

#include <stdio.h>
#include "WsEncoder.h"

class I2C;

class WsI2cEncoder : public WsEncoder {
public:
    WsI2cEncoder(UINT32 slot, UINT8 i2c_addr);
    virtual ~WsI2cEncoder();
    virtual INT16 getDrivenWheelSpeed(void );
    virtual INT16 getIdlerWheelSpeed(void );
    virtual INT16 getSpeedDiff(void );
    virtual INT16 getSlipRatio(void );
protected:
    static const UINT8 kManufacturerBaseRegister = 0x08;
    static const UINT8 kManufacturerSize = 0x08;
    static const UINT8 kSensorTypeBaseRegister = 0x10;
    static const UINT8 kSensorTypeSize = 0x08;
    static const UINT8 kIdlerWheelSpeedRegister = 24;
    static const UINT8 kDrivenWheelSpeedRegister = 26;
    static const UINT8 kSpeedDiffRegister = 28;
    static const UINT8 kSlipRatioRegister = 30;
    I2C* ap_i2c;
};

#endif  //_WSI2CENCODER_H
