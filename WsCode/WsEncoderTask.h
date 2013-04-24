
#define NUM_WHEELS 4
#define MAX_ENCODER_ADDRESS 8
#define ENCODER_DATA_SIZE (MAX_ENCODER_ADDRESS + 1)
#define ENCODER_SLOT_NUM 4


typedef struct
{
  bool  valid;
  int   readCount; // set to 0 when written, incremented when read
  INT16 drivenWheelSpeed;
  INT16 idlerWheelSpeed;
  INT16 speedDiff;
  INT16 slipRatio;
} EncoderDataT;

typedef struct
{
  INT8 calibratedAddresses[NUM_WHEELS];
  bool validConfig;
  EncoderDataT encoderData[ENCODER_DATA_SIZE];
} SharedEncoderDataT;


extern SEM_ID g_encoderSemaphore;
extern SharedEncoderDataT g_encoderData;

extern int encoder_task_main();

