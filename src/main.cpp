/**
 * @file main.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-06-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "factory_test/factory_test.h"
#include "sensesp/net/discovery.h"
#include "sensesp/sensors/sensor.h"
#include "sensesp/system/lambda_consumer.h"
#include "sensesp/system/system_status_led.h"
#include "sensesp/transforms/lambda_transform.h"
#include "sensesp_app_builder.h"
#define BUILDER_CLASS SensESPAppBuilder
#include "sensesp/net/http_server.h"
#include "sensesp/net/networking.h"

using namespace sensesp;
// WiFi captive portal password
constexpr char kWiFiCaptivePortalPassword[] = "abcdabcd";

reactesp::ReactESP app;


static FactoryTest ft;

void view_create(FactoryTest* ft);
void view_update();



void setup()
{
    #ifndef SERIAL_DEBUG_DISABLED
    SetupSerialDebug(115200);
    #endif
    String hostname = "M5miniDisplay-1";
    BUILDER_CLASS builder;
    sensesp_app = (&builder)
                    ->set_hostname(hostname)
                    ->set_wifi("Paikea-Network", "2001BestesBootderWelt!")
                    ->set_sk_server("10.42.0.1", 3000)
                    ->get_app();


    ft.init();
    view_create(&ft);
    app.onRepeat(50, []() { view_update(); });
    printf("Hallo");
    printf("Connected to WiFi. IP address: %s", WiFi.localIP().toString().c_str());
    
    sensesp_app->start();
}

void loop() {app.tick();  }

//void loop() {view_update();  }