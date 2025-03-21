#include <Arduino.h>
#include "SIM7080G/modules/POWER/SIM7080G_POWER.hpp"
#include "SIM7080G/modules/SERIAL/SIM7080G_SERIAL.hpp"
#include "SIM7080G/ARGALI_PINOUT.hpp"
#include "SIM7080G/modules/GNSS/SIM7080G_GNSS.hpp"
#include "SIM7080G/modules/CATM1/SIM7080G_CATM1.hpp"
#include "SIM7080G/modules/TCP/SIM7080G_TCP.hpp"
/* #include "SIM7080G/StateMachine/SIM7080G_FSM.hpp"
#include "SIM7080G/StateMachine/States.hpp" */

unsigned long period1;

void setup()
{
  pinMode(PIN_PWRKEY, OUTPUT);
  Serial.begin(115200); // Initialize serial port
  SIM7080G.begin(SIM7080G_BAUDRATE, SERIAL_8N1, PIN_RX, PIN_TX);

  reboot_SIM7080G();

  // CAT-M1 network activation
  turn_On_CATM1();

  TCP_send(); // Now, we can open TCP Connection
}

void loop()
{
  // execute_SIM7080G_State();
}
