#include "WsDashboard.h"
#include "WPILib.h"
#include "DriverStation.h"
#include "WsDriveVector.h"

WsDashboard* WsDashboard::ap_instance = NULL;

WsDashboard::WsDashboard(DriverStation* p_ds)
{
    int i;
    ap_ds = p_ds;

    a_data[IDX_IN_DRIVE_X] = new DashboardDataFloat();
    a_data[IDX_IN_DRIVE_Y] = new DashboardDataFloat();
    a_data[IDX_IN_DRIVE_RADIUS] = new DashboardDataFloat();
    a_data[IDX_IN_DRIVE_ANGLE] = new DashboardDataFloat();
    a_data[IDX_IN_DRIVE_TURBO] = new DashboardDataBool();
    a_data[IDX_IN_DRIVE_TRACTION] = new DashboardDataBool();

    a_data[IDX_IN_CRAB_X] = new DashboardDataFloat();
    a_data[IDX_IN_CRAB_Y] = new DashboardDataFloat();
    a_data[IDX_IN_CRAB_RADIUS] = new DashboardDataFloat();
    a_data[IDX_IN_CRAB_ANGLE] = new DashboardDataFloat();
    a_data[IDX_DES_CRAB_STATE] = new DashboardDataBool();

    a_data[IDX_DES_DRIVE_SPEED] = new DashboardDataFloat();
    a_data[IDX_DES_DRIVE_ANGLE] = new DashboardDataFloat();
    a_data[IDX_DES_CRAB_ANGLE] = new DashboardDataFloat();
    a_data[IDX_DES_CRAB_MANUAL_SPEED] = new DashboardDataFloat();

    a_data[IDX_OUT_DRIVE_FL] = new DashboardDataFloat();
    a_data[IDX_OUT_DRIVE_FR] = new DashboardDataFloat();
    a_data[IDX_OUT_DRIVE_BL] = new DashboardDataFloat();
    a_data[IDX_OUT_DRIVE_BR] = new DashboardDataFloat();
    a_data[IDX_OUT_CRAB_SPEED_L] = new DashboardDataFloat();
    a_data[IDX_OUT_CRAB_SPEED_R] = new DashboardDataFloat();

    a_data[IDX_POT_CRAB_CUR] = new DashboardDataUINT32();
    a_data[IDX_POT_CRAB_CALIB_L] = new DashboardDataUINT32();
    a_data[IDX_POT_CRAB_CALIB_M] = new DashboardDataUINT32();
    a_data[IDX_POT_CRAB_CALIB_R] = new DashboardDataUINT32();
    a_data[IDX_POT_CRAB_CALIB_ACTIVE] = new DashboardDataBool();

    a_data[IDX_PID_CRAB_P] = new DashboardDataFloat();
    a_data[IDX_PID_CRAB_I] = new DashboardDataFloat();
    a_data[IDX_PID_CRAB_D] = new DashboardDataFloat();
    a_data[IDX_PID_CRAB_EPS] = new DashboardDataFloat();

    a_data[IDX_PID_CRAB_TARGET] = new DashboardDataUINT32();
    a_data[IDX_CALIBRATION_MODE] = new DashboardDataBool();

    a_data[IDX_IN_ACCUM_IN] = new DashboardDataBool();
    a_data[IDX_IN_ACCUM_OUT] = new DashboardDataBool();
    a_data[IDX_IN_SHOOT_OUT] = new DashboardDataBool();
    a_data[IDX_IN_SHOOT_OUT_SLOW] = new DashboardDataBool();
    a_data[IDX_IN_SHOOT_IN] = new DashboardDataBool();
    a_data[IDX_IN_ACCUM_LOAD] = new DashboardDataBool();
    a_data[IDX_IN_DOWN_OUT] = new DashboardDataBool();
    a_data[IDX_IN_RAISE_SHOOT_LEFT] = new DashboardDataBool();
    a_data[IDX_IN_RAISE_SHOOT_BOTH] = new DashboardDataBool();
    a_data[IDX_IN_RAISE_SHOOT_RIGHT] = new DashboardDataBool();

    a_data[IDX_IN_STICKY_ENABLE] = new DashboardDataBool();
    a_data[IDX_IN_STICKY_STOP] = new DashboardDataBool();

    a_data[IDX_IN_ESC_X] = new DashboardDataFloat();
    a_data[IDX_IN_ESC_Y] = new DashboardDataFloat();
    a_data[IDX_IN_ESC_RADIUS] = new DashboardDataFloat();
    a_data[IDX_IN_ESC_ANGLE] = new DashboardDataFloat();

    a_data[IDX_IN_ELEV_X] = new DashboardDataFloat();
    a_data[IDX_IN_ELEV_Y] = new DashboardDataFloat();
    a_data[IDX_IN_ELEV_RADIUS] = new DashboardDataFloat();
    a_data[IDX_IN_ELEV_ANGLE] = new DashboardDataFloat();

    a_data[IDX_SW_ELEV_L_TOP] = new DashboardDataBool();
    a_data[IDX_SW_ELEV_L_BOT] = new DashboardDataBool();
    a_data[IDX_SW_ELEV_R_TOP] = new DashboardDataBool();
    a_data[IDX_SW_ELEV_R_BOT] = new DashboardDataBool();

    a_data[IDX_OUT_ACCUM] = new DashboardDataFloat();
    a_data[IDX_OUT_ESC_FRONT] = new DashboardDataFloat();
    a_data[IDX_OUT_ESC_BACK] = new DashboardDataFloat();
    a_data[IDX_OUT_ELEV_LEFT] = new DashboardDataFloat();
    a_data[IDX_OUT_ELEV_RIGHT] = new DashboardDataFloat();
    a_data[IDX_OUT_SHOOTER] = new DashboardDataFloat();

    a_data[IDX_STICKY_ACCUM] = new DashboardDataBool();
    a_data[IDX_STICKY_ESC_FRONT] = new DashboardDataBool();
    a_data[IDX_STICKY_ESC_BACK] = new DashboardDataBool();
    a_data[IDX_STICKY_ELEV_LEFT] = new DashboardDataBool();
    a_data[IDX_STICKY_ELEV_RIGHT] = new DashboardDataBool();
    a_data[IDX_STICKY_SHOOTER] = new DashboardDataBool();

    a_data[IDX_AUTO_PROGNUM] = new DashboardDataUINT32();
    a_data[IDX_AUTO_POSITION] = new DashboardDataUINT32();
    a_data[IDX_AUTO_LOCKIN] = new DashboardDataBool();

    a_data[IDX_AUTO_PROGSTATE] = new DashboardDataUINT32();
    a_data[IDX_AUTO_PROG_SUBSTATE] = new DashboardDataUINT32();

    a_data[IDX_AUTO_DATA1] = new DashboardDataFloat();
    a_data[IDX_AUTO_DATA2] = new DashboardDataFloat();
    a_data[IDX_AUTO_DATA3] = new DashboardDataFloat();
    a_data[IDX_AUTO_DATA4] = new DashboardDataFloat();
    a_data[IDX_AUTO_DATA5] = new DashboardDataFloat();

    a_data[IDX_AUTO_BOOL_DATA1] = new DashboardDataBool();
    a_data[IDX_AUTO_BOOL_DATA2] = new DashboardDataBool();
    a_data[IDX_AUTO_BOOL_DATA3] = new DashboardDataBool();
    a_data[IDX_AUTO_BOOL_DATA4] = new DashboardDataBool();
    a_data[IDX_AUTO_BOOL_DATA5] = new DashboardDataBool();

    a_data[IDX_CONTINUOUS_LOOP_COUNT] = new DashboardDataUINT32();

    a_data[IDX_TRACTION_ENABLE_STATE] = new DashboardDataBool();
    a_data[IDX_TRACTION_WHEELSPEED_FL] = new DashboardDataFloat();
    a_data[IDX_TRACTION_GROUNDSPEED_FL] = new DashboardDataFloat();
    a_data[IDX_TRACTION_SLIPRATIO_FL] = new DashboardDataFloat();
    a_data[IDX_TRACTION_DES_OUTPUT_FL] = new DashboardDataFloat();
    a_data[IDX_TRACTION_ACT_OUTPUT_FL] = new DashboardDataFloat();
    a_data[IDX_TRACTION_WHEELSPEED_FR] = new DashboardDataFloat();
    a_data[IDX_TRACTION_GROUNDSPEED_FR] = new DashboardDataFloat();
    a_data[IDX_TRACTION_SLIPRATIO_FR] = new DashboardDataFloat();
    a_data[IDX_TRACTION_DES_OUTPUT_FR] = new DashboardDataFloat();
    a_data[IDX_TRACTION_ACT_OUTPUT_FR] = new DashboardDataFloat();
    a_data[IDX_TRACTION_WHEELSPEED_BL] = new DashboardDataFloat();
    a_data[IDX_TRACTION_GROUNDSPEED_BL] = new DashboardDataFloat();
    a_data[IDX_TRACTION_SLIPRATIO_BL] = new DashboardDataFloat();
    a_data[IDX_TRACTION_DES_OUTPUT_BL] = new DashboardDataFloat();
    a_data[IDX_TRACTION_ACT_OUTPUT_BL] = new DashboardDataFloat();
    a_data[IDX_TRACTION_WHEELSPEED_BR] = new DashboardDataFloat();
    a_data[IDX_TRACTION_GROUNDSPEED_BR] = new DashboardDataFloat();
    a_data[IDX_TRACTION_SLIPRATIO_BR] = new DashboardDataFloat();
    a_data[IDX_TRACTION_DES_OUTPUT_BR] = new DashboardDataFloat();
    a_data[IDX_TRACTION_ACT_OUTPUT_BR] = new DashboardDataFloat();

    a_data[IDX_ENCODER_MODULE_FL] = new DashboardDataUINT32();
    a_data[IDX_ENCODER_MODULE_FR] = new DashboardDataUINT32();
    a_data[IDX_ENCODER_MODULE_BL] = new DashboardDataUINT32();
    a_data[IDX_ENCODER_MODULE_BR] = new DashboardDataUINT32();

    for(i = 0; i < MAX_NUM_DATA_IDX; i++)
    {
        a_data[i]->reset();
    }
}

WsDashboard::~WsDashboard()
{
    int i;
    for(i = 0; i < MAX_NUM_DATA_IDX; i++)
    {
        if(a_data[i] != NULL)
        {
            delete a_data[i];
            a_data[i] = NULL;
        }
    }

    if(ap_instance != NULL)
    {
        delete ap_instance;
    }

    ap_instance = NULL;

}

WsDashboard* WsDashboard::getInstance()
{
   return ap_instance;
}

WsDashboard* WsDashboard::getInstance(DriverStation* p_ds)
{
    if(ap_instance == NULL)
    {
        ap_instance = new WsDashboard(p_ds);
    }
    return ap_instance;
}

void WsDashboard::setValue(DashboardIndexT index, bool value)
{
    a_data[index]->set(value);
}

void WsDashboard::setValue(DashboardIndexT index, UINT32 value)
{
    a_data[index]->set(value);
}

void WsDashboard::setValue(DashboardIndexT index, float value)
{
    a_data[index]->set(value);
}

void WsDashboard::getValue(DashboardIndexT index, bool* value)
{
    a_data[index]->get(value);
}

void WsDashboard::getValue(DashboardIndexT index, UINT32* value)
{
    a_data[index]->get(value);
}

void WsDashboard::getValue(DashboardIndexT index, float* value)
{
    a_data[index]->get(value);
}

void WsDashboard::resetValues()
{
    int i;
    for(i = 0; i < MAX_NUM_DATA_IDX; i++)
    {
        a_data[i]->reset();
    }
}

void WsDashboard::update()
{
    Dashboard &dashboardPacker = ap_ds->GetLowPriorityDashboardPacker();
    int i;
    bool valueBool;
    UINT32 valueUINT32;
    float valueFloat;

    for(i = 0; i < MAX_NUM_DATA_IDX; i++)
    {
        switch(a_data[i]->a_dataType)
        {
            case DATA_TYPE_BOOL:
                a_data[i]->get(&valueBool);
                dashboardPacker.AddBoolean(valueBool);
                break;
            case DATA_TYPE_UINT32:
                a_data[i]->get(&valueUINT32);
                dashboardPacker.AddU32(valueUINT32);
                break;
            case DATA_TYPE_FLOAT:
                a_data[i]->get(&valueFloat);
                dashboardPacker.AddFloat(valueFloat);
                break;
            default:
                break;
        }
    }

    // Flush the data to the driver station
    dashboardPacker.Finalize();
}

