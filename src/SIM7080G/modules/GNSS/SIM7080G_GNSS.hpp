#include <Arduino.h>

// Complete definition of the lat_lon structure
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

// Function declarations
void turn_On_GNSS();
void turn_Off_GNSS();
void get_Position_GNSS(coordGNSS *coordinates);
void parse_GNSS_Position(String gnss_data, coordGNSS *coordinates);
lat_lon get_Lat_Lon(String stringValue);
