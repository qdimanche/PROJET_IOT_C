#include <Arduino.h>
#include "SIM7080G_TCP.hpp"
#include "SIM7080G/modules/SERIAL/SIM7080G_SERIAL.hpp"
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

// Opens a TCP connection with the SIM7080G module.
bool open_tcp_connection()
{
    String response = send_AT("AT+CAOPEN=0,0,\"TCP\",\"rnnwd-185-223-151-250.a.free.pinggy.link\",41473", 5000);
    if (response.indexOf("ERROR") != -1)
    {
        Serial.println("Failed to open TCP connection.");
        return false;
    }
    return true;
}

// Sends CBOR data over the TCP connection.

bool send_cbor_data(const std::vector<uint8_t> &cbor_data)
{
    int data_length = cbor_data.size();

    // Send command to start data transmission
    String response = send_AT("AT+CASEND=0," + String(data_length), 5000);
    if (response.indexOf(">") == -1)
    {
        Serial.println("Error: Module is not ready to receive data.");
        return false;
    }

    // Send the CBOR data byte by byte
    for (uint8_t byte : cbor_data)
    {
        SIM7080G.write(byte);
    }

    Serial.println("CBOR data sent successfully.");
    return true;
}

// Closes the TCP connection.
void close_tcp_connection()
{
    send_AT("AT+CACLOSE=0", 5000);
}

void TCP_send()
{
    // Create JSON data
    json j;
    j["pi"] = 3.141;
    j["happy"] = true;
    j["name"] = "Niels";
    j["nothing"] = nullptr;
    j["answer"]["everything"] = 42;
    j["list"] = {1, 0, 2};
    j["object"] = {{"currency", "USD"}, {"value", 42.99}};
    j;

    // Convert JSON to CBOR
    std::vector<uint8_t> cbor_data = json::to_cbor(j);

    // Open TCP connection
    if (!open_tcp_connection())
    {
        return;
    }

    // Send CBOR data
    if (!send_cbor_data(cbor_data))
    {
        close_tcp_connection();
        return;
    }

    // Close TCP connection
    close_tcp_connection();
}
