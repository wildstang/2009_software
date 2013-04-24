#if !defined(_WSDASHBOARD_H)
#define _WSDASHBOARD_H

#include <stdio.h>
#include "WsDriveVector.h"

typedef enum
{
    IDX_IN_DRIVE_X,
    IDX_IN_DRIVE_Y,
    IDX_IN_DRIVE_RADIUS,
    IDX_IN_DRIVE_ANGLE,
    IDX_IN_DRIVE_TURBO,
    IDX_IN_DRIVE_TRACTION,
    IDX_IN_CRAB_X,
    IDX_IN_CRAB_Y,
    IDX_IN_CRAB_RADIUS,
    IDX_IN_CRAB_ANGLE,
    IDX_DES_CRAB_STATE,
    IDX_DES_DRIVE_SPEED,
    IDX_DES_DRIVE_ANGLE,
    IDX_DES_CRAB_ANGLE,
    IDX_DES_CRAB_MANUAL_SPEED,
    IDX_OUT_DRIVE_FL,
    IDX_OUT_DRIVE_FR,
    IDX_OUT_DRIVE_BL,
    IDX_OUT_DRIVE_BR,
    IDX_OUT_CRAB_SPEED_L,
    IDX_OUT_CRAB_SPEED_R,
    IDX_POT_CRAB_CUR,
    IDX_POT_CRAB_CALIB_L,
    IDX_POT_CRAB_CALIB_M,
    IDX_POT_CRAB_CALIB_R,
    IDX_POT_CRAB_CALIB_ACTIVE,
    IDX_PID_CRAB_P,
    IDX_PID_CRAB_I,
    IDX_PID_CRAB_D,
    IDX_PID_CRAB_EPS,
    IDX_PID_CRAB_TARGET,
    IDX_CALIBRATION_MODE,
    IDX_IN_ACCUM_IN,
    IDX_IN_ACCUM_OUT,
    IDX_IN_SHOOT_OUT,
    IDX_IN_SHOOT_OUT_SLOW,
    IDX_IN_SHOOT_IN,
    IDX_IN_ACCUM_LOAD,
    IDX_IN_DOWN_OUT,
    IDX_IN_RAISE_SHOOT_LEFT,
    IDX_IN_RAISE_SHOOT_BOTH,
    IDX_IN_RAISE_SHOOT_RIGHT,
    IDX_IN_STICKY_ENABLE,
    IDX_IN_STICKY_STOP,
    IDX_IN_ESC_X,
    IDX_IN_ESC_Y,
    IDX_IN_ESC_RADIUS,
    IDX_IN_ESC_ANGLE,
    IDX_IN_ELEV_X,
    IDX_IN_ELEV_Y,
    IDX_IN_ELEV_RADIUS,
    IDX_IN_ELEV_ANGLE,
    IDX_SW_ELEV_L_TOP,
    IDX_SW_ELEV_L_BOT,
    IDX_SW_ELEV_R_TOP,
    IDX_SW_ELEV_R_BOT,
    IDX_OUT_ACCUM,
    IDX_OUT_ESC_FRONT,
    IDX_OUT_ESC_BACK,
    IDX_OUT_ELEV_LEFT,
    IDX_OUT_ELEV_RIGHT,
    IDX_OUT_SHOOTER,
    IDX_STICKY_ACCUM,
    IDX_STICKY_ESC_FRONT,
    IDX_STICKY_ESC_BACK,
    IDX_STICKY_ELEV_LEFT,
    IDX_STICKY_ELEV_RIGHT,
    IDX_STICKY_SHOOTER,
    IDX_AUTO_PROGNUM,
    IDX_AUTO_POSITION,
    IDX_AUTO_LOCKIN,
    IDX_AUTO_PROGSTATE,
    IDX_AUTO_PROG_SUBSTATE,
    IDX_AUTO_DATA1,
    IDX_AUTO_DATA2,
    IDX_AUTO_DATA3,
    IDX_AUTO_DATA4,
    IDX_AUTO_DATA5,
    IDX_AUTO_BOOL_DATA1,
    IDX_AUTO_BOOL_DATA2,
    IDX_AUTO_BOOL_DATA3,
    IDX_AUTO_BOOL_DATA4,
    IDX_AUTO_BOOL_DATA5,
    IDX_CONTINUOUS_LOOP_COUNT,
    IDX_TRACTION_ENABLE_STATE,
    IDX_TRACTION_WHEELSPEED_FL,
    IDX_TRACTION_GROUNDSPEED_FL,
    IDX_TRACTION_SLIPRATIO_FL,
    IDX_TRACTION_DES_OUTPUT_FL,
    IDX_TRACTION_ACT_OUTPUT_FL,
    IDX_TRACTION_WHEELSPEED_FR,
    IDX_TRACTION_GROUNDSPEED_FR,
    IDX_TRACTION_SLIPRATIO_FR,
    IDX_TRACTION_DES_OUTPUT_FR,
    IDX_TRACTION_ACT_OUTPUT_FR,
    IDX_TRACTION_WHEELSPEED_BL,
    IDX_TRACTION_GROUNDSPEED_BL,
    IDX_TRACTION_SLIPRATIO_BL,
    IDX_TRACTION_DES_OUTPUT_BL,
    IDX_TRACTION_ACT_OUTPUT_BL,
    IDX_TRACTION_WHEELSPEED_BR,
    IDX_TRACTION_GROUNDSPEED_BR,
    IDX_TRACTION_SLIPRATIO_BR,
    IDX_TRACTION_DES_OUTPUT_BR,
    IDX_TRACTION_ACT_OUTPUT_BR,
    IDX_ENCODER_MODULE_FL,
    IDX_ENCODER_MODULE_FR,
    IDX_ENCODER_MODULE_BL,
    IDX_ENCODER_MODULE_BR,

    // All indicies go above here
    MAX_NUM_DATA_IDX
} DashboardIndexT;

typedef enum
{
    DATA_TYPE_BOOL,
    DATA_TYPE_UINT32,
    DATA_TYPE_FLOAT,
} DashboardDataTypeT;

class DriverStation;

class DashboardDataBase
{
    public:
        virtual void reset(void) = 0;
        virtual void get(bool* value)
        {
            *value = false;
        }
        virtual void get(UINT32* value)
        {
            *value = 0;
        }
        virtual void get(float* value)
        {
            *value = 0;
        }
        virtual void set(bool value)
        {
        }
        virtual void set(UINT32 value)
        {
        }
        virtual void set(float value)
        {
        }
        
        DashboardDataTypeT a_dataType;
        
};
class DashboardDataBool : public DashboardDataBase
{
    public:
        DashboardDataBool()
        {
            a_dataType = DATA_TYPE_BOOL;
        }
        virtual void reset(void)
        {
            a_value = false;
        }
        virtual void set(bool value)
        {
            a_value = value;
        }
        virtual void get(bool* value)
        {
            *value = a_value;
        }
    protected:
        bool a_value;

};
class DashboardDataUINT32 : public DashboardDataBase
{
    public:
        DashboardDataUINT32()
        {
            a_dataType = DATA_TYPE_UINT32;
        }
        virtual void reset(void)
        {
            a_value = 0;
        }
        virtual void set(UINT32 value)
        {
            a_value = value;
        }
        virtual void get(UINT32* value)
        {
            *value = a_value;
        }
    protected:
        UINT32 a_value;
};
class DashboardDataFloat : public DashboardDataBase
{
    public:
        DashboardDataFloat()
        {
            a_dataType = DATA_TYPE_FLOAT;
        }
        virtual void reset(void)
        {
            a_value = 0;
        }
        virtual void set(float value)
        {
            a_value = value;
        }
        virtual void get(float *value)
        {
            *value = a_value;
        }
    protected:
        float a_value;
};


class WsDashboard
{
public:
    virtual ~WsDashboard();
    // This should be called by the robot to assign the DS
    static WsDashboard* getInstance(DriverStation* p_ds);
    // This should be called by classes that will update data
    static WsDashboard* getInstance();
    void resetValues(void);
    void update(void);

    void setValue(DashboardIndexT index, bool value);
    void setValue(DashboardIndexT index, UINT32 value);
    void setValue(DashboardIndexT index, float value);

    void getValue(DashboardIndexT index, bool* value);
    void getValue(DashboardIndexT index, UINT32* value);
    void getValue(DashboardIndexT index, float* value);

protected:
    WsDashboard(DriverStation* p_ds);
    static WsDashboard* ap_instance;

    DriverStation* ap_ds;
    DashboardDataBase* a_data[MAX_NUM_DATA_IDX];
};

#endif  //_WSDASHBOARD_H

