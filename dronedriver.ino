
#include <Thread.h>
#include <Servo.h>
#include <SoftwareSerial.h>
/* system */
#include "config.h"
#include "threads.h"


Thread runtimeThread = Thread();
Thread utilsThread = Thread();

extern Servo _fl, _fr, rl, rr;
extern SoftwareSerial SoftSerial;


void setup() {
   /* -- core -- */
   Serial.begin(BAUDRATE);
   while (!Serial);
   Serial.println(F("SetupInit"));
   /* -- */
   SoftSerial.begin(BAUDRATE);
   while (!SoftSerial);
   SoftSerial.listen();
   SoftSerial.println(F("SoftSerialInit"));
   /* -- threads -- */
   runtimeThread.onRun(runtimeThreadCall);
   runtimeThread.setInterval(RUNTIME_THREAD_INTV_MS);
   utilsThread.onRun(utilsThreadCall);
   utilsThread.setInterval(UTILS_THREAD_INTV_MS);
   /* init servos */
   //_fl.attach(pwmLF);
   //_fr.attach()
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
