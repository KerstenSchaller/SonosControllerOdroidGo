#include <Arduino.h>
#include <HTTPClient.h>

struct sonos_parameters_t 
{
    std::string UID = "";
    std::string PlayState = "not set";
    int Volume = 0;
};
extern sonos_parameters_t sonos_parameters;

#define HTTP_TIMEOUT 2000
#define SONOS_PORT 1400
#define ENO_CANTCONNECT 11;

int sonosOperation(int (*operation)(HTTPClient *http, IPAddress target), IPAddress targetSonos);
void doSonos(int (*operation)(HTTPClient *http, IPAddress targetSonos));
int volumeUp(HTTPClient *http, IPAddress targetSonos);
int volumeDown(HTTPClient *http, IPAddress targetSonos);
int sonosNext(HTTPClient *http, IPAddress targetSonos);
int sonosPlay(HTTPClient *http, IPAddress targetSonos);
int getVolume(HTTPClient *http, IPAddress targetSonos);

IPAddress discoverSonos(std::string uid);
