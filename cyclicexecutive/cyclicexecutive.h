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
#define T1_PIN        1   // blah
#define T2_PIN        2   // blah
#define T3_PIN        3   // blah
#define T4_ANIN_PIN   4   // blah
#define T4_LED_PIN    0   // blah

// Schedule
#define TASK2_P       10  // blah
#define TASK2_POFF1   1   // blah
#define TASK2_POFF2   7   // blah
#define TASK3_P       2   // blah
#define TASK4_P       5   // blah
#define TASK5_P       25  // blah

// Unique parameters
#define BAUD_RATE       9600  // baud reate
#define TICK_LENGTH     4     // Period
#define NUM_FRAMES      50    // blah

#define TASK2_TIMEOUT   3100  // bah
#define TASK2_MINFREQ   333   // blah
#define TASK2_MAXFREQ   1000  // blah

#define TASK3_TIMEOUT   2100  // bah
#define TASK3_MINFREQ   500   // blah
#define TASK3_MAXFREQ   1000  // blah

#define NUM_PARAMS      4     // thingy
#define TASK4_THRESH    2048  // blah

#define TASK5_MIN       0     // blah
#define TASK5_MAX       99    // blah

// Helpful typedefs
typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;

#endif  // __CYCLICEXECUTIVE_H__
