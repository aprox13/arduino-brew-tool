#define SERIAL_SPEED 9600

#ifdef __LOGS

#define LOG(msg) (Serial.println(msg));
#else
#define LOG(msg)
#endif

#ifdef __LOGS
#define INIT_LOGS() Serial.begin(SERAIL_SPEED)
#else
#define INIT_LOGS()
#endif
