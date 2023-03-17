
/*
*   cyclicexecutive.ino
*   
*   Sketch for assignment 2 for ESP32C3 Dev Module
*   Nikolaus Scherwitzel (H00298068)
*   Created: 13/03/23
*/

// NOTE: frame == tick, used interchangeably in comments

// Libraries
#include "cyclicexecutive.h"
#include <B31DGMonitor.h>
#include <Ticker.h>

// Convert period in us to frequency in Hz
#define periodToFreq_us(T) (1 / (T / 1000000))

// Globals
B31DGCyclicExecutiveMonitor monitor;

uint8 tCount;   // Tick counter, is reset after 50 frames
Ticker ticker;  // Ticker object

double freqT2;  // Calculated frequency for task 2 waveform
double freqT3;  // Calculated frequency for task 3 waveform

uint16 anIn[NUM_PARAMS];  // Array for storing previous analogue measurements
uint8 currInd;            // Current index to overwrite in anIn[]

void setup() {
  Serial.begin(BAUD_RATE);

  // Define pin inputs/outputs
  pinMode(T1_PIN, OUTPUT); 
  pinMode(T2_PIN, INPUT);
  pinMode(T3_PIN, INPUT); 
  pinMode(T4_ANIN_PIN, INPUT); 
  pinMode(T4_LED_PIN, OUTPUT); 

  // Initialise task 4 analogue input array with 0's
  currInd = 0;
  for (uint8 i = 0; i < NUM_PARAMS; i++) {
    anIn[i] = 0;
  }

  // Start monitoring and ticking
  tCount = 0;
  monitor.startMonitoring();
  ticker.attach_ms(TICK_LENGTH, cycle);
  cycle();  // Ran as first call of cycle from ticker is after TICK_LENGTH ms
}

void cycle() {
  // Schedule, run tasks periodically according to TASKX_P in frames
  task1();
  // Task 2 doesn't start execution at frame 0, so offset needed
  if (((tCount - TASK2_POFF1) % TASK2_P) == 0) task2();
  if (((tCount - TASK2_POFF2) % TASK2_P) == 0) task2();
  if ((tCount % TASK3_P) == 0)  task3();
  if ((tCount % TASK4_P) == 0)  task4();
  if ((tCount % TASK5_P) == 0)  task5();
  
  // Increment tick and reset if hyper period reached (frame 50)
  tCount++;
  if (tCount > NUM_FRAMES)  tCount = 1;
}

// Period = 4ms / Rate = 250Hz
void task1() {
  monitor.jobStarted(1);
  
  // Generate waveform
  digitalWrite(T1_PIN, HIGH);
  delayMicroseconds(200);
  digitalWrite(T1_PIN, LOW);
  delayMicroseconds(50);
  digitalWrite(T1_PIN, HIGH);
  delayMicroseconds(30);
  digitalWrite(T1_PIN, LOW);

  monitor.jobEnded(1);
}

// Period = 20ms / Rate = 50Hz
void task2() {
  monitor.jobStarted(2);

  // Measure period when signal is HIGH
  // Multiply by 2 because 50% duty cycle
  double period = (double) pulseIn(T2_PIN, HIGH) * 2;
  freqT2 = periodToFreq_us(period); // Convert to frequency using T = 1/f

  monitor.jobEnded(2);
}

// Period = 8ms / Rate = 125Hz
void task3() {
  monitor.jobStarted(3);
  
  // Measure period when signal is HIGH
  // Multiply by 2 because 50% duty cycle
  double period = (double) pulseIn(T3_PIN, HIGH) * 2;
  freqT3 = periodToFreq_us(period); // Convert to frequency using T = 1/f

  monitor.jobEnded(3);
}

// Period = 20ms / Rate = 50Hz
void task4() {
  monitor.jobStarted(4);
  
  // Read analogue signal and increment index for next reading
  // Analogue signal converted to 12 bit integer
  anIn[currInd] = analogRead(T4_ANIN_PIN);
  currInd = (currInd + 1) % NUM_PARAMS;
  
  // Sum array and divide to get average
  double filtAnIn = 0;
  for (uint8 i = 0; i < NUM_PARAMS; i++) {
    filtAnIn += anIn[i];
  }
  filtAnIn /= NUM_PARAMS;

  // Turn on LED if average is above half maximium of 12 bit integer (4096 / 2 = THRESH)
  digitalWrite(T4_LED_PIN, (filtAnIn > TASK4_THRESH));

  monitor.jobEnded(4);
}

// Period = 100ms / Rate = 10Hz
void task5() {
  monitor.jobStarted(5);
  
  // Map frequencies from 333Hz & 500Hz - 1000Hz to 0 - 99
  // Constrain to 0 - 99 as map() only creates gradient
  int normFreqT2 = map(freqT2, TASK2_MINFREQ, TASK2_MAXFREQ, TASK5_MIN, TASK5_MAX);
  normFreqT2 = constrain(normFreqT2, TASK5_MIN, TASK5_MAX);
  int normFreqT3 = map(freqT3, TASK3_MINFREQ, TASK3_MAXFREQ, TASK5_MIN, TASK5_MAX);
  normFreqT3 = constrain(normFreqT3, TASK5_MIN, TASK5_MAX);

  // Print to serial monitor
  Serial.print(normFreqT2);
  Serial.print(",");
  Serial.println(normFreqT3);

  monitor.jobEnded(5);
}

void loop() {
  // Debug Timing
  /*
  uint16 ITERS = 100;
  uint32 avg = 0;
  for (uint16 i = 0; i < ITERS; i++) {
    uint32 start = micros();
    task1();
    avg += micros() - start;
  }
  avg /= ITERS;
  Serial.print(avg);
  Serial.println("us");
  */
}
