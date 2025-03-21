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
  // reboot_GNSS();

  // turn_off_GNSS();

  // CAT-M1 network activation
  turn_on_CATM1();

  TCP_send();
}

void everyXs()
{
  // Check GNSS position every 5 seconds
  if (millis() - period1 > 5000)
  {

    struct coordGNSS coordinates;

    get_position_GNSS(&coordinates);

    // loop_CATM1();

    // Update the time counter
    period1 = millis();
  }
}

void loop()
{
  // everyXs();
  // execute_SIM7080G_State();
}
