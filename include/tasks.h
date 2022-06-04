#define LED_BUILTIN 2
#define ENABLE_A 16
#define ENABLE_B 17
#define IN_1 5
#define IN_2 18
#define IN_3 19
#define IN_4 21
#define TEMP 27
#define ADC_VREF_mV    3300.0 
#define ADC_RESOLUTION 40960.0
#define FREQ 5000
#define CHANNEL 0
#define RES 8
#define STANDARD_TEMPERATURE 20

void tempHandler(void *arg);
void comHandler(void *arg);
void motorHandler(void *arg);