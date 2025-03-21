#include <Arduino.h>

#include <Arduino.h>

#define SIM7080G_PowerOn 1
#define SIM7080G_PowerOff 2
#define SIM7080G_SleepMode 3

// Déclaration de la variable d'état globale (définie dans States.cpp)
extern uint8_t SIM7080G_currentState;
