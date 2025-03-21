#include <Arduino.h>
#include "SIM7080G/modules/POWER/SIM7080G_POWER.hpp"
#include "SIM7080G/modules/SERIAL/SIM7080G_SERIAL.hpp"
#include "SIM7080G/modules/GNSS/SIM7080G_GNSS.hpp"
#include "SIM7080G/modules/CATM1/SIM7080G_CATM1.hpp"
#include "SIM7080G/modules/TCP/SIM7080G_TCP.hpp"
#include "SIM7080G/modules/CATM1/StateMachine/States.hpp"

void execute_SIM7080G_CATM1_state()
{
  switch (SIM7080G_CATM1_currentState)
  {
  case CatM1TurnOn:
    Serial.println("State: GNSS TurnOn - Turning on GNSS");
    turn_on_GNSS();
    SIM7080G_CATM1_currentState = CatM1TurnOff; // Transition to GNSS TurnOff state
    Serial.println("State: Transitioning to GNSS TurnOff");
    break;
  case CatM1TurnOff:
    Serial.println("State: GNSS TurnOff - Turning off GNSS");
    turn_off_GNSS();
    // SIM7080G_currentState = CatM1TurnOn; // Transition to CatM1 TurnOn state
    Serial.println("State: Transitioning to CatM1 TurnOn");
    break;

  default:
    Serial.print("State: Unknown state encountered - currentState value: ");
    Serial.println(static_cast<int>(SIM7080G_CATM1_currentState));
    break;
  }
}