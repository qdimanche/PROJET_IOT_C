#include <Arduino.h>
#include "SIM7080G/modules/POWER/SIM7080G_POWER.hpp"
#include "SIM7080G/ARGALI_PINOUT.hpp"
#include "SIM7080G/modules/SERIAL/SIM7080G_SERIAL.hpp"

void turn_On_SIM7080G()
{
    digitalWrite(PIN_PWRKEY, LOW);
    delay(200);
    digitalWrite(PIN_PWRKEY, OUTPUT_OPEN_DRAIN);
    delay(3000);
}

void turn_Off_SIM7080G()
{
    String response = send_AT("AT+CPOWD=1");

    if (response.length() > 0)
    {
        response.trim();
    }

    if (response.endsWith("DOWN"))
    {
        Serial.println("Le module SIM7080G s'est éteint avec succès.");
    }
    else
    {
        Serial.println("Échec de l'extinction du module SIM7080G.");
    }

    delay(1000);
}

void reboot_SIM7080G()
{
    turn_Off_SIM7080G();
    turn_On_SIM7080G();
}

void hard_Reset_SIM7080G()
{
    digitalWrite(PIN_PWRKEY, LOW);
    delay(15000);
    digitalWrite(PIN_PWRKEY, OUTPUT_OPEN_DRAIN);
    delay(3000);
}
