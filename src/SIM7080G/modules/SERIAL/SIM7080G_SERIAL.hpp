#include <Arduino.h>

#define SIM7080G Serial1
#define SIM7080G_BAUDRATE 57600

String send_AT(String message, unsigned long timeout = 1000);

String display_Battery();