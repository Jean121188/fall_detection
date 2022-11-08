#include "sensor.h"

ADXL345 adxl;

void Init_ADXL345(void){
    adxl.powerOn();
    //set activity/ inactivity thresholds (0-255)
    adxl.setActivityThreshold(75); //62.5mg per increment
    adxl.setInactivityThreshold(75); //62.5mg per increment
    adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?
    //look of activity movement on this axes - 1 == on; 0 == off
    adxl.setActivityX(1);
    adxl.setActivityY(1);
    adxl.setActivityZ(1);
    //look of inactivity movement on this axes - 1 == on; 0 == off
    adxl.setInactivityX(1);
    adxl.setInactivityY(1);
    adxl.setInactivityZ(1);
    //look of tap movement on this axes - 1 == on; 0 == off
    adxl.setTapDetectionOnX(0);
    adxl.setTapDetectionOnY(0);
    adxl.setTapDetectionOnZ(1);
    //set values for what is a tap, and what is a double tap (0-255)
    adxl.setTapThreshold(50); //62.5mg per increment
    adxl.setTapDuration(15); //625us per increment
    adxl.setDoubleTapLatency(80); //1.25ms per increment
    adxl.setDoubleTapWindow(200); //1.25ms per increment
    //set values for what is considered freefall (0-255)
    adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
    adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment
    //setting all interrupts to take place on int pin 1
    //I had issues with int pin 2, was unable to reset it
    adxl.setInterruptMapping(ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN);
    adxl.setInterruptMapping(ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN);
    adxl.setInterruptMapping(ADXL345_INT_FREE_FALL_BIT,    ADXL345_INT1_PIN);
    adxl.setInterruptMapping(ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN);
    adxl.setInterruptMapping(ADXL345_INT_INACTIVITY_BIT,   ADXL345_INT1_PIN);
    //register interrupt actions - 1 == on; 0 == off
    adxl.setInterrupt(ADXL345_INT_SINGLE_TAP_BIT, 1);
    adxl.setInterrupt(ADXL345_INT_DOUBLE_TAP_BIT, 1);
    adxl.setInterrupt(ADXL345_INT_FREE_FALL_BIT,  1);
    adxl.setInterrupt(ADXL345_INT_ACTIVITY_BIT,   1);
    adxl.setInterrupt(ADXL345_INT_INACTIVITY_BIT, 1);
}

int* Sample(int buffer){
    
    int x, y, z, cont = 0;
    int xyzBuffer[buffer +1];
    Serial.print("aqui\n");

    while(cont <= buffer)
    {
        adxl.readXYZ(&x, &y, &z);
        xyzBuffer[cont] =  z;
        cont ++;

        while (cont <= buffer)
        {
            adxl.readXYZ(&x, &y, &z);
            xyzBuffer[cont] =  y;
            cont ++;

            while (cont <= buffer)
            {
                adxl.readXYZ(&x, &y, &z);
                xyzBuffer[cont] =  x;
                cont ++;
            }
        }
        delayMicroseconds(16); // 62.5Hz
    }
    return (int*)&xyzBuffer;
}

lista PrintDados(int *listDat){
    List<String> lista(BUFFER_SIZE);
    for(int j = 0; j <= BUFFER_SIZE; j++)
    {
        for (size_t i = 0; i < 2; i++)
        {
            String value = String(listDat[i]);
            lista.add(value); 
        }
        String separator = ";";
        lista.add(separator);
    }
    return lista;
}