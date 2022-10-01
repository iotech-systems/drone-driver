
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <Servo.h>
#include "threads.h"

const short BUFF_SIZE = 32;

short CHAR_IDX = 0;
char CMD_IN_BUFFER[BUFF_SIZE];
Servo _lftFront, _lftRead, _rgtFront, _rgtRead;
extern HardwareSerial HCSerial;


void runtimeThreadCall() {
   if (HCSerial.available() > 0) {   
      loadCmdBuffer();
      if (isCmdLoaded()) {
         runCommand();
         clearInBuffer();
      }
   }
};

void runCommand() {
   char sep = ',';
   String CMDBUFF = String(CMD_IN_BUFFER);
   if (CMDBUFF.startsWith(F("##SRVO:PWMS"))) {
      CMDBUFF.replace(F("##SRVO:PWMS"), "");
      CMDBUFF.replace(F("&"), "");
      /* check for () */
      if (!(CMDBUFF.startsWith(F("(")) && CMDBUFF.endsWith(F(")")))) {
         Serial.println(F("No()"));
         return;
      }
      /* -- */
      String args = CMDBUFF.substring(1, (CMDBUFF.length() - 1));
      Serial.println(args);
      /* int fl, int rl, int fr, int rr
         front left */
      int pos = args.indexOf(sep, 0);
      String tmp = args.substring(0, pos);
      int fl = tmp.toInt();
      /* rear left */
      int npos = args.indexOf(sep, ++pos);
      tmp = args.substring(pos, npos);
      int rl = tmp.toInt();
      /* front right */
      pos = args.indexOf(sep, ++npos);
      tmp = args.substring(npos, pos);
      int fr = tmp.toInt();
      /* rear right */
      npos = args.indexOf(sep, ++pos);
      tmp = args.substring(pos, npos);
      int rr = tmp.toInt();
      /* call function */
      bool rv = setServoPWMs(fl, rl, fr, rr);
   } else if (CMDBUFF.startsWith(F("##SRVO:INIT"))) {
      CMDBUFF.replace(F("##SRVO:INIT"), "");
      CMDBUFF.replace(F("&"), "");
      /* check for () */
      if (!(CMDBUFF.startsWith(F("(")) && CMDBUFF.endsWith(F(")")))) {
         Serial.println(F("No()"));
         return;
      }
      /* -- */
      String args = CMDBUFF.substring(1, (CMDBUFF.length() - 1));
      Serial.println(args);
      /* int fl, int rl, int fr, int rr
         front left */
      int pos = args.indexOf(sep, 0);
      String tmp = args.substring(0, pos);
      int fl = tmp.toInt();
      /* rear left */
      int npos = args.indexOf(sep, ++pos);
      tmp = args.substring(pos, npos);
      int rl = tmp.toInt();
      /* front right */
      pos = args.indexOf(sep, ++npos);
      tmp = args.substring(npos, pos);
      int fr = tmp.toInt();
      /* rear right */
      npos = args.indexOf(sep, ++pos);
      tmp = args.substring(pos, npos);
      int rr = tmp.toInt();
      /* call function */
      bool rv = setServoInit(fl, rl, fr, rr);
   } else {
      Serial.println(CMDBUFF);
   }
}

void loadCmdBuffer() {
   while (HCSerial.peek() != -1) {
      CMD_IN_BUFFER[CHAR_IDX] = HCSerial.read();
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

bool setServoPWMs(int lftF, int lftR, int rgtF, int rgtR) {
   char sbuff[32];
   int s = sizeof(sbuff);
   snprintf(sbuff, s, "setServoPWMs: %i | %i | %i | %i", lftF, lftR, rgtF, rgtR);
   Serial.println(sbuff);
   /* _lftFront, _lftRead, _rgtFront, _rgtRead */
   _lftFront.write(lftF);
   _lftRead.write(lftR);
   _rgtFront.write(rgtF);
   _rgtRead.write(rgtR);
};

bool setServoInit(int lftF, int lftR, int rgtF, int rgtR) {
   char sbuff[32];
   int s = sizeof(sbuff);
   snprintf(sbuff, s, "setServoInit: %i | %i | %i | %i", lftF, lftR, rgtF, rgtR);
   Serial.println(sbuff);
    /* _lftFront, _lftRead, _rgtFront, _rgtRead */
   _lftFront.write(lftF);
   _lftRead.write(lftR);
   _rgtFront.write(rgtF);
   _rgtRead.write(rgtR);
};
