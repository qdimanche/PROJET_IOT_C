#include <Arduino.h>
#include "SIM7080G/modules/SERIAL/SIM7080G_SERIAL.hpp"
#include "utils/DateUtils.hpp"

struct lat_lon
{
    uint8_t partEnt;
    uint32_t partDec;
};

struct coordGNSS
{
    uint64_t timestamp;
    lat_lon latitude;
    lat_lon longitude;
};

// Function to turn on the GNSS
void turn_on_GNSS()
{
    send_AT("AT+CGNSPWR=1");         // Turn on the GNSS
    send_AT("AT+CGNSMOD=1,0,0,1,0"); // Configure GNSS mode
}

// Function to turn off the GNSS
void turn_off_GNSS()
{
    send_AT("AT+CGNSPWR=0"); // Turn off the GNSS
    delay(1000);
}

void reboot_GNSS() {
    turn_off_GNSS();
    turn_on_GNSS();
}

// Function to extract latitude and longitude from a string
lat_lon get_lat_lon(String stringValue)
{
    lat_lon value;
    int decimalIndex = stringValue.indexOf('.');

    if (decimalIndex == -1)
    {
        // Handle case where there is no decimal part
        value.partEnt = stringValue.toInt();
        value.partDec = 0;
    }
    else
    {
        // Extract the integer part
        String ent = stringValue.substring(0, decimalIndex);
        value.partEnt = ent.toInt(); // Convert the integer part

        // Extract the decimal part
        String decimal = stringValue.substring(decimalIndex + 1);

        value.partDec = decimal.toInt(); // Convert the decimal part
    }

    return value;
}

// Function to parse GNSS position from a string and store it in the provided coordinates structure
void parse_GNSS_position(String gnss_data, coordGNSS *coordinates)
{
    if (coordinates == nullptr)
    {
        Serial.println("Error: null pointer passed to parse_GNSS_Position");
        return;
    }

    if (gnss_data.indexOf("+CGNSINF:") == -1)
    {
        Serial.println("Invalid GNSS data");
        return;
    }

    int start_index = gnss_data.indexOf(":") + 1;
    String data = gnss_data.substring(start_index);

    int start_pos = 0;
    int end_pos = data.indexOf(",");

    String values[15];
    int index = 0;

    // Extract comma-separated values
    while (end_pos != -1 && index < 15)
    {
        values[index] = data.substring(start_pos, end_pos);
        start_pos = end_pos + 1;
        end_pos = data.indexOf(",", start_pos);
        index++;
    }

    // If too many values are extracted, ensure not to exceed the array limit
    if (index > 15)
    {
        Serial.println("Warning: too many values extracted! " + String(index));
        return;
    }

    // Check if the necessary values are available
    if (index < 5)
    {
        Serial.println("Error: insufficient GNSS data");
        return;
    }

    // Check the extracted values before using them
    String timestamp_str = values[2];
    String latitude = values[3];
    String longitude = values[4];

    // Display the extracted values for debugging
    Serial.println("Extracted values:");
    Serial.println("Timestamp: " + timestamp_str);
    Serial.println("Latitude: " + latitude);
    Serial.println("Longitude: " + longitude);

    uint64_t timestamp = convert_to_unix_timestamp(timestamp_str);

    lat_lon multiple_parts_latitude = get_lat_lon(latitude);
    lat_lon multiple_parts_longitude = get_lat_lon(longitude);

    // Correct the initialization of the coordGNSS structure
    coordinates->timestamp = timestamp;
    coordinates->latitude = multiple_parts_latitude;
    coordinates->longitude = multiple_parts_longitude;
}

// Function to get GNSS position and store it in the provided coordinates structure
void get_position_GNSS(coordGNSS *coordinates)
{
    if (coordinates == nullptr)
    {
        Serial.println("Error: null pointer passed to get_Position_GNSS");
        return;
    }

    String response = send_AT("AT+CGNSINF");

    if (response.indexOf("+CGNSINF:") != -1)
    {
        Serial.println("GNSS response: " + response);
        parse_GNSS_position(response, coordinates);

        // Check the coordinates before displaying them
        if (coordinates->latitude.partEnt != 0 || coordinates->longitude.partEnt != 0)
        {
            Serial.print("Latitude: " + String(coordinates->latitude.partEnt) + "." + String(coordinates->latitude.partDec));
            Serial.print(" Longitude: " + String(coordinates->longitude.partEnt) + "." + String(coordinates->longitude.partDec));
            Serial.print(" Timestamp: " + String(coordinates->timestamp));
        }
        else
        {
            Serial.println("Error: invalid coordinates after parsing.");
        }
    }
}
