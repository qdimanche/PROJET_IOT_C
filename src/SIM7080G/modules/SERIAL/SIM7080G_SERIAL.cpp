#include <Arduino.h>
#include "SIM7080G/modules/SERIAL/SIM7080G_SERIAL.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

String send_AT(String message, unsigned long timeout)
{
    unsigned long start_time = millis();
    char byte_recv = 'A';
    String uart_buffer = "";

    SIM7080G.println(message);

    while (((millis() - start_time) < timeout) && (uart_buffer.endsWith("OK") == false && uart_buffer.endsWith("VALID") == false && uart_buffer.endsWith(">") == false ))
    {
        if (SIM7080G.available())
        {
            byte_recv = SIM7080G.read();
            uart_buffer += byte_recv;
        }
    }

    Serial.println(uart_buffer);

    return uart_buffer;
}

String display_Battery()
{
    String battery = send_AT("AT+CBC"); // Sends the AT command and receives the response

    // Checks that the response is valid and not empty
    if (battery.length() > 0)
    {
        return "Succès durant la récupération de l'état de la batterie";
    }
    else
    {
        return "Échec de la récupération de l'état de la batterie.";
    }
}
