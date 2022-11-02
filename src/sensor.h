#ifndef SENSOR_H
#define SENSOR_H
#include <string.h>
#include <Arduino.h>
#include <Wire.h>
#include <ADXL345.h>

#define BUFFER_SIZE     3000
void Init_ADXL345(void);
char* Sample(int buffer);

#endif