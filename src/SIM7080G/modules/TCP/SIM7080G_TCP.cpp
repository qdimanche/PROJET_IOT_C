#include "SIM7080G_TCP.hpp"
#include "SIM7080G/modules/SERIAL/SIM7080G_SERIAL.hpp"

void TCP_send()
{
    send_AT("AT+CAOPEN=0,0,\"TCP\",\"rnsgp-2a04-cec0-115b-37ed-392d-81be-5e94-59f4.a.free.pinggy.link\",33777", 10000);

    // cf datasheet
    send_AT("AT+CASEND=0,6", 10000);
    // attendre le charactère '>' avant d'envoyer la data
    send_AT("bonjour", 10000);

    // send_TCP_packet_data(&j);

    send_AT("AT+CACLOSE=0", 10000);
    // send_AT(AT+CARECV,1460);
}
