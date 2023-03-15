
/*
*   cyclicexecutive.ino
*   
*   Sketch for assignment 2 for ESP32C3 Dev Module
*   Nikolaus Scherwitzel (H00298068)
*   Created: 13/03/23
*/

#include "cyclicexecutive.h"
#include <B31DGMonitor.h>
#include <Ticker.h>

#define periodToFreq_us(T) (1 / (T / 1000000))

// Globals
B31DGCyclicExecutiveMonitor monitor;

uint8 tCount;
Ticker ticker;

double freqT2;
double freqT3;

uint16 anIn[NUM_PARAMS];
uint8 currInd;

void setup() {
  Serial.begin(BAUD_RATE);

  pinMode(T1_PIN, OUTPUT); 
  pinMode(T2_PIN, INPUT);
  pinMode(T3_PIN, INPUT); 
  pinMode(T4_ANIN_PIN, INPUT); 
  pinMode(T4_LED_PIN, OUTPUT); 

  currInd = 0;
  for (uint8 i = 0; i < NUM_PARAMS; i++) {
    anIn[i] = 0;
  }

  tCount = 0;
  monitor.startMonitoring();
  ticker.attach_ms(TICK_LENGTH, cycle);
  cycle();
}

void cycle() {
  task1();
  if (((tCount - TASK2_POFF1) % TASK2_P) == 0) task2();
  if (((tCount - TASK2_POFF2) % TASK2_P) == 0) task2();
  if ((tCount % TASK3_P) == 0)  task3();
  if ((tCount % TASK4_P) == 0)  task4();
  if ((tCount % TASK5_P) == 0)  task5();
  
  tCount++;
  if (tCount > NUM_FRAMES)  tCount = 1;
}

void task1() {
  monitor.jobStarted(1);
  
  digitalWrite(T1_PIN, HIGH);
  delayMicroseconds(200);
  digitalWrite(T1_PIN, LOW);
  delayMicroseconds(50);
  digitalWrite(T1_PIN, HIGH);
  delayMicroseconds(30);
  digitalWrite(T1_PIN, LOW);

  monitor.jobEnded(1);
}

void task2() {
  monitor.jobStarted(2);
  
  double period = (double) pulseIn(T2_PIN, HIGH, TASK2_TIMEOUT) * 2;
  freqT2 = periodToFreq_us(period);

  monitor.jobEnded(2);
}

void task3() {
  monitor.jobStarted(3);
  
  double period = (double) pulseIn(T3_PIN, HIGH, TASK3_TIMEOUT) * 2;
  freqT3 = periodToFreq_us(period);

  monitor.jobEnded(3);
}

void task4() {
  monitor.jobStarted(4);
  
  anIn[currInd] = analogRead(T4_ANIN_PIN);
  currInd = (currInd + 1) % NUM_PARAMS;
  
  double filtAnIn = 0;
  for (uint8 i = 0; i < NUM_PARAMS; i++) {
    filtAnIn += anIn[i];
  }
  filtAnIn /= NUM_PARAMS;

  digitalWrite(T4_LED_PIN, (filtAnIn > TASK4_THRESH));

  monitor.jobEnded(4);
}

void task5() {
  monitor.jobStarted(5);
  
  uint8 normFreqT2 = map(freqT2, TASK2_MINFREQ, TASK2_MAXFREQ, TASK5_MIN, TASK5_MAX);
  normFreqT2 = constrain(normFreqT2, TASK5_MIN, TASK5_MAX);
  uint8 normFreqT3 = map(freqT3, TASK3_MINFREQ, TASK3_MAXFREQ, TASK5_MIN, TASK5_MAX);
  normFreqT3 = constrain(normFreqT3, TASK5_MIN, TASK5_MAX);
  Serial.print(normFreqT2);
  Serial.print(",");
  Serial.println(normFreqT3);

  monitor.jobEnded(5);
}

void loop() {
  // Debug Timing
  /*
  int ITERS = 100;
  long int avg = 0;
  for (int i = 0; i < ITERS; i++) {
    long int start = micros();
    task5();
    avg += micros() - start;
    delay(30);
  }
  avg /= ITERS;
  Serial.println();
  Serial.print(avg);
  Serial.println("us");
  */
}
