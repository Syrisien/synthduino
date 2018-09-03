#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <tables/saw2048_int8.h> // saw table for oscillator
#include <tables/triangle2048_int8.h> // triangle table for oscillator
#include <tables/smoothsquare8192_int8.h> // square table for oscillator
#include <mozzi_midi.h>
#include <EventDelay.h>

// essetially the speed the program works at. Powers of 2 only for bit value conversion.
#define CONTROL_RATE 128

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above

// Square wave oscilator tables.
Oscil <SMOOTHSQUARE8192_NUM_CELLS, AUDIO_RATE> SqrC(SMOOTHSQUARE8192_DATA);
Oscil <SMOOTHSQUARE8192_NUM_CELLS, AUDIO_RATE> SqrD(SMOOTHSQUARE8192_DATA);
Oscil <SMOOTHSQUARE8192_NUM_CELLS, AUDIO_RATE> SqrE(SMOOTHSQUARE8192_DATA);
Oscil <SMOOTHSQUARE8192_NUM_CELLS, AUDIO_RATE> SqrF(SMOOTHSQUARE8192_DATA);
Oscil <SMOOTHSQUARE8192_NUM_CELLS, AUDIO_RATE> SqrG(SMOOTHSQUARE8192_DATA);
Oscil <SMOOTHSQUARE8192_NUM_CELLS, AUDIO_RATE> SqrA(SMOOTHSQUARE8192_DATA);
Oscil <SMOOTHSQUARE8192_NUM_CELLS, AUDIO_RATE> SqrB(SMOOTHSQUARE8192_DATA);
Oscil <SMOOTHSQUARE8192_NUM_CELLS, AUDIO_RATE> SqrC2(SMOOTHSQUARE8192_DATA);
Oscil <SMOOTHSQUARE8192_NUM_CELLS, AUDIO_RATE> SqrCsharp(SMOOTHSQUARE8192_DATA);
Oscil <SMOOTHSQUARE8192_NUM_CELLS, AUDIO_RATE> SqrDsharp(SMOOTHSQUARE8192_DATA);
Oscil <SMOOTHSQUARE8192_NUM_CELLS, AUDIO_RATE> SqrFsharp(SMOOTHSQUARE8192_DATA);
Oscil <SMOOTHSQUARE8192_NUM_CELLS, AUDIO_RATE> SqrGsharp(SMOOTHSQUARE8192_DATA);
Oscil <SMOOTHSQUARE8192_NUM_CELLS, AUDIO_RATE> SqrCsharp2(SMOOTHSQUARE8192_DATA);

// audio sinewave oscillators
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> SinC(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> SinD(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> SinE(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> SinF(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> SinG(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> SinA(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> SinB(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> SinC2(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> SinCsharp(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> SinDsharp(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> SinFsharp(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> SinGsharp(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> SinCsharp2(SIN2048_DATA);

// audio trianglewave oscillators
Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> TriC(TRIANGLE2048_DATA);
Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> TriD(TRIANGLE2048_DATA);
Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> TriE(TRIANGLE2048_DATA);
Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> TriF(TRIANGLE2048_DATA);
Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> TriG(TRIANGLE2048_DATA);
Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> TriA(TRIANGLE2048_DATA);
Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> TriB(TRIANGLE2048_DATA);
Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> TriC2(TRIANGLE2048_DATA);
Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> TriCsharp(TRIANGLE2048_DATA);
Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> TriDsharp(TRIANGLE2048_DATA);
Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> TriFsharp(TRIANGLE2048_DATA);
Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> TriGsharp(TRIANGLE2048_DATA);
Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> TriCsharp2(TRIANGLE2048_DATA);

// audio sawwave oscillators
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawC(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawD(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawE(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawF(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawG(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawA(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawB(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawC2(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawCsharp(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawDsharp(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawFsharp(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawGsharp(SAW2048_DATA);
Oscil <SAW2048_NUM_CELLS, AUDIO_RATE> SawCsharp2(SAW2048_DATA);

// set the input for the volume knob to analog pin 0
const char VOLUME = A0; 

// initialize buttons, keys.
const int C_PIN = 0;
const int D_PIN = 1;
const int E_PIN = 2;
const int F_PIN = 4;
const int G_PIN = 5;
const int A_PIN = 6;
const int B_PIN = 7;
const int C2_PIN = 8;

const int CSHARP_PIN = 11;
const int DSHARP_PIN = 12;
const int FSHARP_PIN = 13;
const int GSHARP_PIN = 27;
const int CSHARP2_PIN = 28;

const int OCTAVE_UP = A1;
const int OCTAVE_DOWN = A2;
const int WAVE_CHANGE = A3;
const int VIBRATO = A4;

// value that stores octave, in midi note form. Use steps of 12, 2 each direction.
int octave = 0;

// wave chooser integer, betweeen 1 and 4.
int waveChoice = 1;

// note frequency conversion from midi note.
int noteC = mtof(24 + octave);
int noteD = mtof(26 + octave);
int noteE = mtof(28 + octave);
int noteF = mtof(29 + octave);
int noteG = mtof(31 + octave);
int noteA = mtof(33 + octave);
int noteB = mtof(35 + octave);
int noteC2 = mtof(24 + octave);
int noteCsharp = mtof(25 + octave);
int noteDsharp = mtof(27 + octave);
int noteFsharp = mtof(24 + octave);
int noteGsharp = mtof(32 + octave);
int noteCsharp2 = mtof(34 + octave);

// set default key state to unpressed.
int keyCState = 0;
int keyDState = 0;
int keyEState = 0;
int keyFState = 0;
int keyGState = 0;
int keyAState = 0;
int keyBState = 0;
int keyC2State = 0;
int keyCsharpState = 0;
int keyDsharpState = 0;
int keyFsharpState = 0;
int keyGsharpState = 0;
int keyCsharp2State = 0;

// WIP, envelopes for attack/decay etc.
int key1Envelope = 0;
int key2Envelope = 0;
int key3Envelope = 0;
int key4Envelope = 0;

// to convey the volume level from updateControl() to updateAudio()
byte volume;

// to convey vibrato frequency from upradeControl to updateAudio()
byte vibrato;


void setup(){
  // sets button modes.
  pinMode(C_PIN, INPUT);
  pinMode(D_PIN, INPUT);
  pinMode(E_PIN, INPUT);
  pinMode(F_PIN, INPUT);
  pinMode(OCTAVE_UP, INPUT);
  pinMode(OCTAVE_DOWN, INPUT);
  pinMode(WAVE_CHANGE, INPUT);  

  // sets frequency of wave tables.
  SqrC.setFreq(noteC);
  SqrD.setFreq(noteD);
  SqrE.setFreq(noteE);
  SqrF.setFreq(noteF);
  SqrG.setFreq(noteG);
  SqrA.setFreq(noteA);
  SqrD.setFreq(noteB);
  SqrC2.setFreq(noteC2);
  SqrCsharp.setFreq(noteCsharp);
  SqrDsharp.setFreq(noteDsharp);
  SqrFsharp.setFreq(noteFsharp);
  SqrGsharp.setFreq(noteGsharp);
  SqrCsharp2.setFreq(noteCsharp2);

  SinC.setFreq(noteC);
  SinD.setFreq(noteD);
  SinE.setFreq(noteE);
  SinF.setFreq(noteF);
  SinG.setFreq(noteG);
  SinA.setFreq(noteA);
  SinD.setFreq(noteB);
  SinC2.setFreq(noteC2);
  SinCsharp.setFreq(noteCsharp);
  SinDsharp.setFreq(noteDsharp);
  SinFsharp.setFreq(noteFsharp);
  SinGsharp.setFreq(noteGsharp);
  SinCsharp2.setFreq(noteCsharp2);

  TriC.setFreq(noteC);
  TriD.setFreq(noteD);
  TriE.setFreq(noteE);
  TriF.setFreq(noteF);
  TriG.setFreq(noteG);
  TriA.setFreq(noteA);
  TriD.setFreq(noteB);
  TriC2.setFreq(noteC2);
  TriCsharp.setFreq(noteCsharp);
  TriDsharp.setFreq(noteDsharp);
  TriFsharp.setFreq(noteFsharp);
  TriGsharp.setFreq(noteGsharp);
  TriCsharp2.setFreq(noteCsharp2);

  SawC.setFreq(noteC);
  SawD.setFreq(noteD);
  SawE.setFreq(noteE);
  SawF.setFreq(noteF);
  SawG.setFreq(noteG);
  SawA.setFreq(noteA);
  SawD.setFreq(noteB);
  SawC2.setFreq(noteC2);
  SawCsharp.setFreq(noteCsharp);
  SawDsharp.setFreq(noteDsharp);
  SawFsharp.setFreq(noteFsharp);
  SawGsharp.setFreq(noteGsharp);
  SawCsharp2.setFreq(noteCsharp2);

  // starts Mozzi.
  startMozzi(CONTROL_RATE); // :))
}


void updateControl(){
  // read the variable resistor for volume
  int volume_value = mozziAnalogRead(VOLUME); // value is 0-1023
    // map it to an 8 bit range for efficient calculations in updateAudio
  volume = map(volume_value, 0, 1023, 0, 255);  

  // read the variable resistor for vibrato
  int vibrato_value = mozziAnalogRead(VIBRATO); // value is 0-1023
    // map it to an 8 bit range for efficient calculations in updateAudio
  vibrato = map(vibrato_value, 0, 1023, 1, 500);  
  vibrato = vibrato / 250;

  // change wave type   
  if (digitalRead(WAVE_CHANGE) == HIGH) {
    if (waveChoice < 4)
    waveChoice = waveChoice + 1;
    EventDelay(1000);
  }
    else {
    waveChoice = 1;
    EventDelay(1000);
  }

  //octave changer 
  if (digitalRead(OCTAVE_UP) == HIGH) {
    if (octave < 24)
    octave = octave + 12;
    EventDelay(1000);
  }
    else {
    octave = octave;
  }

  if (digitalRead(OCTAVE_DOWN) == HIGH) {
    if (octave > -24)
    octave = octave - 12;
    delay(1000);
  }
    else {
    octave = octave;
  }

  // key control. multiplies total output by 0 if unpressed, but by 1 if pressed.
  if (digitalRead(C_PIN) == HIGH) {    keyCState = 1;  }  else {    keyCState = 0;  }
  if (digitalRead(D_PIN) == HIGH) {    keyDState = 1;  }  else {    keyDState = 0;  }
  if (digitalRead(E_PIN) == HIGH) {    keyEState = 1;  }  else {    keyEState = 0;  }
  if (digitalRead(F_PIN) == HIGH) {    keyFState = 1;  }  else {    keyFState = 0;  }
  if (digitalRead(G_PIN) == HIGH) {    keyGState = 1;  }  else {    keyGState = 0;  }
  if (digitalRead(A_PIN) == HIGH) {    keyAState = 1;  }  else {    keyAState = 0;  }
  if (digitalRead(B_PIN) == HIGH) {    keyBState = 1;  }  else {    keyBState = 0;  }
  if (digitalRead(C2_PIN) == HIGH) {    keyC2State = 1;  }  else {    keyC2State = 0;  }
  if (digitalRead(CSHARP_PIN) == HIGH) {    keyCsharpState = 1;  }  else {    keyCsharpState = 0;  }
  if (digitalRead(DSHARP_PIN) == HIGH) {    keyDsharpState = 1;  }  else {    keyDsharpState = 0;  }
  if (digitalRead(FSHARP_PIN) == HIGH) {    keyFsharpState = 1;  }  else {    keyFsharpState = 0;  }
  if (digitalRead(GSHARP_PIN) == HIGH) {    keyGsharpState = 1;  }  else {    keyGsharpState = 0;  }
  if (digitalRead(CSHARP2_PIN) == HIGH) {    keyCsharp2State = 1;  }  else {    keyCsharp2State = 0;  }
 
}


int updateAudio(){
  // combines played waves into single output, and multiplies by volume level; then returns to range of 8 bit value.
  // the ifs change between the 4 wave types.
  
  if (waveChoice == 1) {
      return ((int)(SqrC.next() * keyCState) + (SqrD.next() * keyDState) + (SqrE.next() * keyEState)) * volume>> 8; 
  }
  else if (waveChoice == 2) {
      return ((int)(SinC.next() * keyCState) + (SinD.next() * keyDState) + (SinE.next() * keyEState)) * volume>> 8; 
  }
  else if (waveChoice == 3) {
      return ((int)(SawC.next() * keyCState) + (SawD.next() * keyDState) + (SawE.next() * keyEState)) * volume>> 8;
  }
    else if (waveChoice == 4) {
      return ((int)(TriC.next() * keyCState) + (TriD.next() * keyDState) + (TriE.next() * keyEState)) * volume>> 8; 
  }
}


void loop(){
  audioHook(); // required here
}
