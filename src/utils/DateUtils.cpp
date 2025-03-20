#include <Arduino.h>

// Function to convert a "YYYYMMDDHHMMSS" timestamp to a Unix timestamp
uint64_t convertToUnixTimestamp(String timestamp)
{
    struct tm t = {0}; // Initialize to 0

    Serial.println("Retrieved timestamp " + timestamp);

    // Extract values from the timestamp
    t.tm_year = timestamp.substring(0, 4).toInt() - 1900; // Year since 1900
    t.tm_mon = timestamp.substring(4, 6).toInt() - 1;     // Month (0-11)
    t.tm_mday = timestamp.substring(6, 8).toInt();        // Day of the month
    t.tm_hour = timestamp.substring(8, 10).toInt();       // Hours
    t.tm_min = timestamp.substring(10, 12).toInt();       // Minutes
    t.tm_sec = timestamp.substring(12, 14).toInt();       // Seconds

    return static_cast<uint64_t>(mktime(&t)); // Cast to uint64_t
}
