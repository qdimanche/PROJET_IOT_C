#include <Arduino.h>
#include "SIM7080G/modules/POWER/SIM7080G_POWER.hpp"
#include "SIM7080G/modules/SERIAL/SIM7080G_SERIAL.hpp"
#include "SIM7080G/modules/GNSS/SIM7080G_GNSS.hpp"
#include "SIM7080G/modules/CATM1/SIM7080G_CATM1.hpp"
#include "SIM7080G/modules/TCP/SIM7080G_TCP.hpp"
#include "SIM7080G/StateMachine/States.hpp"
#include "SIM7080G/modules/GNSS/StateMachine/States.hpp"
#include "SIM7080G/modules/GNSS/StateMachine/GNSS_FSM.hpp"


void execute_SIM7080G_state()
{
  switch (SIM7080G_currentState)
  {
  case SIM7080G_PowerOn:
    Serial.println("State: PowerOn - Turning on SIM7080G");
    turn_on_SIM7080G();
    
    execute_SIM7080G_GNSS_state();
    break;

  case SIM7080G_PowerOff:
    Serial.println("State: PowerOff - Turning off SIM7080G");
    turn_off_SIM7080G();
    Serial.println("State: Transitioning to GNSS TurnOn");
    break;

  case SIM7080G_SleepMode:
    Serial.println("State: SleepMode");
    break;

    /*   case GnssTurnOn:
        Serial.println("State: GNSS TurnOn - Turning on GNSS");
        turn_On_GNSS();
        SIM7080G_currentState = GnssTurnOff; // Transition to GNSS TurnOff state
        Serial.println("State: Transitioning to GNSS TurnOff");
        break;

      case GnssTurnOff:
        Serial.println("State: GNSS TurnOff - Turning off GNSS");
        turn_Off_GNSS();
        SIM7080G_currentState = CatM1TurnOn; // Transition to CatM1 TurnOn state
        Serial.println("State: Transitioning to CatM1 TurnOn");
        break;

      case CatM1TurnOn:
        Serial.println("State: CatM1 TurnOn - Turning on CatM1");
        turn_On_CATM1();
        Serial.println("End of turn_On_CATM1");
        // SIM7080G_currentState = TcpTurnOn; // Transition to TCP TurnOn state
        // Serial.println("State: Transitioning to TCP TurnOn");
        break;

      case TcpTurnOn:
        Serial.println("State: TCP TurnOn - Turning on TCP");
        SIM7080G_currentState = SIM7080G_SleepMode; // Transition to SleepMode state
        Serial.println("State: Transitioning to SleepMode");
        break; */

  default:
    Serial.print("State: Unknown state encountered - currentState value: ");
    Serial.println(static_cast<int>(SIM7080G_currentState));
    break;
  }
}