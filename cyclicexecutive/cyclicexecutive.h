/*
*   cyclicexecutive.h
*   
*   Header file for assignment 2 for ESP32C3 Dev Module
*   Nikolaus Scherwitzel (H00298068)
*   Created: 13/03/23
*/

#ifndef __CYCLICEXECUTIVE_H__
#define __CYCLICEXECUTIVE_H__

// Pin numbers
#define T1_PIN        1   // Task 1 output signal pin
#define T2_PIN        2   // Task 2 input measure signal pin
#define T3_PIN        3   // Task 3 input measure signal pin
#define T4_ANIN_PIN   4   // Task 4 analogue input pin
#define T4_LED_PIN    0   // Task 4 LED output pin

// Schedule
#define TASK2_P       10  // Task 2 period: repeats every 10 frames
#define TASK2_POFF1   1   // Task 2 offset from frame 0
#define TASK2_POFF2   7   // Another task 2 offset from frame 0
#define TASK3_P       2   // Task 3 period: repeats every 2 frames
#define TASK4_P       5   // Task 4 period: repeats every 5 frames
#define TASK5_P       25  // Task 5 period: repeats every 25 frames

// Task parameters
#define BAUD_RATE       9600  // Baud rate
#define TICK_LENGTH     4     // Length of time per tick (frame) in ms
#define NUM_FRAMES      50    // Number of frames before schedule is repeated

#define TASK2_TIMEOUT   3100  // Timeout for pulseIn = worst case in us
#define TASK2_MINFREQ   333   // Task 2 minimium frequency of waveform in Hz
#define TASK2_MAXFREQ   1000  // Task 2 maximium frequency of waveform in Hz

#define TASK3_TIMEOUT   2100  // Timeout for pulseIn = worst case in us
#define TASK3_MINFREQ   500   // Task 3 minimium frequency of waveform in Hz
#define TASK3_MAXFREQ   1000  // Task 3 maximium frequency of waveform in Hz

#define NUM_PARAMS      4     // Task 4 length of array for storing past measurements
#define TASK4_THRESH    2048  // Task 4 threshold for turning LED on

#define TASK5_MIN       0     // Task 5 lower bound of range
#define TASK5_MAX       99    // Task 5 upper bound of range

// Helpful typedefs
typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;

#endif  // __CYCLICEXECUTIVE_H__
