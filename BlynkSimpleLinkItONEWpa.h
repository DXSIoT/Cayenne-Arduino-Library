/**
 * @file       BlynkSimpleLinkItONE.h
 * @author     Volodymyr Shymanskyy
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2015 Volodymyr Shymanskyy
 * @date       Jul 2015
 * @brief
 *
 */

#ifndef BlynkSimpleLinkItONEWpa_h
#define BlynkSimpleLinkItONEWpa_h

#ifndef BLYNK_INFO_DEVICE
#define BLYNK_INFO_DEVICE  "LinkIt ONE"
#endif

// cause this causes crashes...
#define BLYNK_NO_YIELD

#include <BlynkApiArduino.h>
#include <Blynk/BlynkProtocol.h>
#include <Adapters/BlynkArduinoClient.h>
#include <LWiFi.h>
#include <LWiFiClient.h>

class BlynkLinkItOneWifi
    : public BlynkProtocol<BlynkArduinoClient>
{
    typedef BlynkProtocol<BlynkArduinoClient> Base;
public:
    BlynkLinkItOneWifi(BlynkArduinoClient& transp)
        : Base(transp)
    {}

    void connectWiFi(const char* ssid, const char* pass)
    {
        BLYNK_LOG("Connecting to %s ...", ssid);
        LWiFi.begin();
        while( !LWiFi.connectWPA(ssid,pass) ){
            ::delay(1000);
        }
    }

    void config(const char* auth,
                const char* domain = BLYNK_DEFAULT_DOMAIN,
                uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
        Base::begin(auth);
        this->conn.begin(domain, port);
    }

    void config(const char* auth,
            	IPAddress   ip,
                uint16_t    port   = BLYNK_DEFAULT_PORT)
    {
    	Base::begin(auth);
    	this->conn.begin(ip, port);
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
               //int         wifi_auth,
               const char* domain = BLYNK_DEFAULT_DOMAIN,
               uint16_t port      = BLYNK_DEFAULT_PORT)
    {
        connectWiFi(ssid, pass);
        config(auth, domain, port);
    }

    void begin(const char* auth,
               const char* ssid,
               const char* pass,
			   //int         wifi_auth,
               IPAddress   ip,
               uint16_t    port = BLYNK_DEFAULT_PORT)
    {
        connectWiFi(ssid, pass);
    	config(auth, ip, port);
    }

};


static LWiFiClient _blynkWifiClient;
static BlynkArduinoClient _blynkTransport(_blynkWifiClient);
BlynkLinkItOneWifi Blynk(_blynkTransport);

#include <BlynkWidgets.h>

#endif
