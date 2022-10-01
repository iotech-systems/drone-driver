
#include <SoftwareSerial.h>
#include "config.h"

#ifndef THREADS_H
#define THREADS_H

void utilsThreadCall();
void runtimeThreadCall();

/* helper functions */
void loadCmdBuffer();
void runCommand();
void clearInBuffer();
bool isCmdLoaded();
bool setServoPWMs(int lf, int lb, int rf, int rb);
bool setServoInit(int lf, int lb, int rf, int rb);

#endif
