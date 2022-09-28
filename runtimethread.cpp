
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <Servo.h>
#include "threads.h"


const short BUFF_SIZE = 32;

short CHAR_IDX = 0;
char CMD_IN_BUFFER[BUFF_SIZE];
Servo _fl, _fr, rl, rr;
SoftwareSerial SoftSerial(pinRX, pinTX);


void runtimeThreadCall() {
   if (SoftSerial.available() > 0) {   
      loadCmdBuffer();
      if (isCmdLoaded()) {
         runCommand();
         clearInBuffer();
      }
   }
};

void runCommand() {
   String CMDBUFF = String(CMD_IN_BUFFER);
   if (CMDBUFF.startsWith(F("##SRVO:PWMS"))) {
      Serial.println(F("SET SERVEO PWMS"));
      CMDBUFF.replace(F("##SRVO:PWMS"), "");
      CMDBUFF.replace(F("&"), "");
      /* -- */
      Serial.println(CMDBUFF);
   } else if (CMDBUFF.startsWith(F("##SRVO:INIT"))) {
      Serial.println(F("SET SERVO INIT"));
   } else {
      Serial.println(CMDBUFF);
   }
}

void loadCmdBuffer() {
   while (SoftSerial.peek() != -1) {
      CMD_IN_BUFFER[CHAR_IDX] = SoftSerial.read();
      CHAR_IDX++;
   }
};

void clearInBuffer() {
   CHAR_IDX = 0;
   for (short i = 0; i < BUFF_SIZE; i++)
      CMD_IN_BUFFER[i] = NULL;
};

bool isCmdLoaded() {
   /* -- */
   char charA = CMD_IN_BUFFER[0];
   char charB = CMD_IN_BUFFER[1];
   char charZ = CMD_IN_BUFFER[(CHAR_IDX - 1)];
   /* -- */
   if (charA == '#' && charB == '#' && charZ == '&')
      return true;
   else 
      return false;
   /* -- */
};

bool setServoPWMs(int lf, int lb, int rf, int rb) {

};

bool setServoInit(int lf, int lb, int rf, int rb) {

};
