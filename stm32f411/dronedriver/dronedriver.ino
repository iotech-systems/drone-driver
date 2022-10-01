
/* #include <EEPROM.h> */
#include <Servo.h>
/* system */
#include "config.h"
#include "threads.h"


Thread runtimeThread = Thread();
Thread utilsThread = Thread();

extern Servo _lftFront, _lftRead, _rgtFront, _rgtRead;
HardwareSerial HCSerial = Serial1;


void setup() {
   /* -- core -- */
   Serial.begin(BAUDRATE);
   while (!Serial);
   Serial.println(F("SetupInit"));
   /* -- */
   HCSerial.begin(BAUDRATE);
   while (!HCSerial);
   HCSerial.println(F("HCSerialInit"));
   /* -- threads -- */
   runtimeThread.onRun(runtimeThreadCall);
   runtimeThread.setInterval(RUNTIME_THREAD_INTV_MS);
   utilsThread.onRun(utilsThreadCall);
   utilsThread.setInterval(UTILS_THREAD_INTV_MS);
   /* init servos */
   /* _lftFront, _lftRead, _rgtFront, _rgtRead */
   _lftFront.attach(5, 90, 180);
   _lftRead.attach(6, 90, 180);
   _rgtFront.attach(9, 90, 180);
   _rgtRead.attach(10, 90, 180);
}


void loop() {
   /* -- */
   if (runtimeThread.shouldRun())
      runtimeThread.run();
   /* -- */
   if (utilsThread.shouldRun())
      utilsThread.run();
   /* -- */   
}
