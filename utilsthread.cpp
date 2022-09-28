
#include <Arduino.h>
#include "threads.h"


void utilsThreadCall() {
   digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));   
};

