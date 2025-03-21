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
void turn_on_GNSS();
void turn_off_GNSS();
void reboot_GNSS();
void get_position_GNSS(coordGNSS *coordinates);
void parse_GNSS_position(String gnss_data, coordGNSS *coordinates);
lat_lon get_lat_lon(String stringValue);
