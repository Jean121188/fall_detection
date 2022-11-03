#ifndef SENSOR_H
#define SENSOR_H
#include <string.h>
#include <Arduino.h>
#include "List.hpp"
#include <Wire.h>
#include <ADXL345.h>

typedef List<String> lista;

#define BUFFER_SIZE     3000
void Init_ADXL345(void);
lista Sample(int buffer);
void PrintDados(lista listDat);

#endif