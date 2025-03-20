#include <Arduino.h>
#include "SIM7080G/modules/CATM1/SIM7080G_CATM1.hpp"
#include "SIM7080G/modules/SERIAL/SIM7080G_SERIAL.hpp"

// Function to fetch the CEREG status
boolean check_CEREG_Status_Validity()
{
    String CEREG_Response = send_AT("AT+CEREG?");
    uint8_t commaPosition = CEREG_Response.indexOf(",");
    boolean CEREG_Status_Is_Valid = false; // Default value

    if (commaPosition != -1)
    {
        uint8_t CEREG_Status = CEREG_Response.substring(commaPosition + 1).toInt();

        switch (CEREG_Status)
        {
        case 0:
            Serial.println("4G module not registered");
            break;
        case 1:
            Serial.println("4G module registered");
            break;
        case 2:
            Serial.println("4G module not registered, but MT is currently searching for a new operator to register to");
            break;
        case 3:
            Serial.println("4G module registration denied");
            break;
        case 4:
            Serial.println("4G module unknown");
            break;
        case 5:
            Serial.println("4G module registered");
            break;
        default:
            Serial.println("Unknown CEREG state");
            break;
        }
    }
    else
    {
        Serial.println("Error: CEREG response invalid or unexpected.");
    }

    return CEREG_Status_Is_Valid;
}

// Function to check if CNACT contains a valid IP address
boolean check_CNACT_IP_Validity()
{
    String CNACT_Response = send_AT("AT+CNACT?", 10000);
    uint8_t quotePosition = CNACT_Response.indexOf('"');
    boolean isCNACTValid = false; // Default value

    Serial.println("CNACT_Response: " + CNACT_Response);

    if (quotePosition != -1)
    {
        uint8_t firstIpNumber = CNACT_Response.substring(quotePosition + 1).toInt();

        Serial.println("First IP number: " + String(firstIpNumber));

        if (firstIpNumber != 0)
        {
            Serial.println("CNACT contains a valid IP");
            isCNACTValid = true;
        }
        else
        {
            Serial.println("CNACT contains an invalid IP");
        }
    }
    else
    {
        Serial.println("Error: CNACT response invalid or unexpected.");
    }

    return isCNACTValid;
}

// Function to activate the PDP context and ensure the module is active
void activate_PDP_Context()
{
    String CNACT_Activation_Response = send_AT("AT+CNACT=0,1", 10000);

    if (CNACT_Activation_Response.indexOf("ACTIVE") != -1)
    {
        Serial.println("CNACT is active");
    }
    else
    {
        Serial.println("Timeout reached, CNACT is not active.");
    }
}

// Function to initialize the CAT-M1 module and configure it
void setup_CATM1()
{
    // Disable GNSS before enabling CAT-M1 (refer to the datasheet)
    send_AT("AT+CNMP=38");

    // Enable CAT-M1 and disable NB-IOT
    send_AT("AT+CMNB=1"); // 1 -> CAT-M1, 2 -> NB-IOT

    // Disable the APP Network (PDP context)
    send_AT("AT+CNACT=0,0");

    // Configure the APN for the network connection
    send_AT("AT+CGDCONT=1,\"IP\",\"iot.1nce.net\"");
    send_AT("AT+CGNAPN");
    send_AT("AT+CNCFG=0,1,iot.1nce.net");

    activate_PDP_Context();

    check_CEREG_Status_Validity();

    // Retrieve additional information about the CAT-M1 connection
    check_CNACT_IP_Validity();
    send_AT("AT+GSN");   // Retrieve the model information
    send_AT("AT+CCID");  // Retrieve the SIM card ID
    send_AT("AT+COPS?"); // Check the network operator
    send_AT("AT+CSQ");   // Check the signal quality
}

// Function to monitor the CAT-M1 module's status
void loop_CATM1()
{
    // Check the CEREG status to verify if the 4G module is registered
    send_AT("AT+CEREG?");

    // Check the signal quality
    send_AT("AT+CSQ");
}
