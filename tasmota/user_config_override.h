/*
Отключение температуры CPU ESP32 SetSensor127 0

Подключение счетчика модбас
https://blog.sitefreeman.com/2020/04/03/%D1%82%D1%80%D0%B5%D1%85%D1%84%D0%B0%D0%B7%D0%BD%D1%8B%D0%B9-wi-fi-%D1%81%D1%87%D0%B5%D1%82%D1%87%D0%B8%D0%BA-dds6619-016-017-sinotimer-rs485-tx-rx-modbus-sonoff-basic-majordomo/

tasmota dicovery
https://github.com/joba-1/Tasmoticz.git

50:0F:F5:C0:2A:C0	 192.168.1.40	 TENDA-REPEATER	
04:95:E6:E0:5E:40	 192.168.1.41	 IoT-MM

04:95:E6:E0:94:20	 192.168.1.42	 IoT-00	
04:95:E6:E0:EF:D0   192.168.1.43	 IoT-01 
04:95:E6:15:F8:98	 192.168.1.44	 IoT-02	

04:95:E6:15:02:F8	 192.168.1.45	 IoT-10

D3-3Way-2	C8:2B:96:C7:7D:BC	
D3-3Way-3	48:3F:DA:49:21:31	
D3-WaterHeater15KW	E8:68:E7:43:91:11	
D3-3WAY1	C8:2B:96:C6:EC:8E	
D3-WaterPumpPOW	DC:4F:22:99:C8:BF	
D3-WaterHeater	E8:68:E7:4B:6E:D2	
D3-WellPump	E8:68:E7:4A:18:72	
D3-WaterHeater12KW	E8:68:E7:4B:67:77
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

/*
SONOFF_BASIC, SONOFF_RF, SONOFF_SV, SONOFF_TH, SONOFF_DUAL, SONOFF_POW, SONOFF_4CH, SONOFF_S2X, SLAMPHER, SONOFF_TOUCH,
  SONOFF_LED, CH1, CH4, MOTOR, ELECTRODRAGON, EXS_RELAY, WION, WEMOS, SONOFF_DEV, H801,
  SONOFF_SC, SONOFF_BN, SONOFF_4CHPRO, HUAFAN_SS, SONOFF_BRIDGE, SONOFF_B1, AILIGHT, SONOFF_T11, SONOFF_T12, SONOFF_T13,
  SUPLA1, WITTY, YUNSHAN, MAGICHOME, LUANIHVIO, KMC_70011, ARILUX_LC01, ARILUX_LC11, SONOFF_DUAL_R2, ARILUX_LC06,
  SONOFF_S31, ZENGGE_ZF_WF017, SONOFF_POW_R2, SONOFF_IFAN02, BLITZWOLF_BWSHP, SHELLY1, SHELLY2, PHILIPS, NEO_COOLCAM, ESP_SWITCH,
  OBI, TECKIN, APLIC_WDP303075, TUYA_DIMMER, GOSUND, ARMTRONIX_DIMMERS, SK03_TUYA, PS_16_DZ, TECKIN_US, MANZOKU_EU_4,
  OBI2, YTF_IR_BRIDGE, DIGOO, KA10, ZX2820, MI_DESK_LAMP, SP10, WAGA, SYF05, SONOFF_L1,
  SONOFF_IFAN03, EXS_DIMMER, PWM_DIMMER, SONOFF_D1, SONOFF_ZB_BRIDGE,
  MAXMODULE
*/

//#define MY_USE_SONOFF_DUAL_R2        // used for heating water pipe temp sensors simple(CT) power managemet

//#define MY_USE_PID                   // used for 3way valve (water controller)

//#define MY_USE_RELAY_SONOFF_TH       // used for any relays based on SONOFF_TH (DIN rail relays, Sonoff TH16 ets)

//#define MY_USE_RELAY_SONOFF_GENERIC  // used for ESP-01 module with Relay (pin0) DS18B20 (pin2) https://templates.blakadder.com/ESP-01S-Relay-v4.html 

//#define MY_USE_RELAY_SONOFF_BASIC    // used for basic module with DHT22 (Pin3) 

//#define MY_USE_GREE 
// https://tasmota.github.io/docs/Tasmota-IR/
// IrSend(LED) -GPIO 4(D2)  DS18B20- GPIO 2(D4)
// IRHVAC {"Vendor":"GREE","Model":1,"Mode":"heat","Power":"on","Celsius":"On","Temp":25,"FanSpeed":"Auto","SwingV":"Auto","SwingH":"Off","Quiet":"Off","Turbo":"Off","Econo":"Off","Light":"On","Filter":"Off","Clean":"Off","Beep":"Off","Sleep":-1}
// IRHVAC {"Vendor":"GREE","Mode":"heat","Power":"on","Celsius":"On","Temp":25,"FanSpeed":"Low","SwingV":"Auto","Light":"On"}

// Вариант 2 ELUX
// #define MY_USE_ELUX 
// IrSend(LED) - GPIO14 (D5)  HTU21: GPIO4(D2):I2C-SCL GPIO5(D1):I2C-SDA  GPIO 2(D4):DS18B20 
// IRHVAC {"Vendor":"ELUX","Model":1,"Mode":"heat","Power":"on","Celsius":"On","Temp":25,"FanSpeed":"Auto","SwingV":"Auto","SwingH":"Off","Quiet":"Off","Turbo":"Off","Econo":"Off","Light":"On","Filter":"Off","Clean":"Off","Beep":"Off","Sleep":-1}
// IRHVAC {"Vendor":"ELUX","Mode":"heat","Power":"on","Celsius":"On","Temp":25,"FanSpeed":"Low","SwingV":"Auto","Light":"On"}
// Mode: Auto, Cool, Heat, Dry, Fun
// FanSpeed: High, Medium, Low, Auto
// Temp: 18-32

#if defined(MY_USE_GREE)  || defined(MY_USE_ELUX)
#define MY_USE_IR_REMOTE
#define MAX_DOMOTICZ_TEMPS 2
#endif

//#define MY_USE_PLUG_POW              // used for any relays based on Tuya POW PLug upgraded with ESP8285 
/* 
GPIO0  Button 1
GPIO2  HLWBL SEL_i
GPIO4	 HLW8012 CF
GPIO12 Relay
GPIO14 HLWBL CF1
GPIO16 Led
*/

//#define MY_USE_POW_R2 // used for any relays based on CSE7759 and CSE7766 - Energy (Sonoff S31 and Sonoff Pow R2)
/* непонятное реагирование на кнопки, реле работает от led1, поэтому место подключения не имеет значения, подключи к GPIO2 
GPIO12	Led2
GPIO13	Led1
GPIO0	  Button
GPIO1   CSE7766 TX
GPIO2   Relay
GPIO3   CSE7766 RX

в такой конфигурации на кнопку реагирует с некоторым запоздание приблизительно 10 сек
SetOption21 1 - всегда показывать напряжение
*/
#undef MODULE
//#define MY_USE_MIRTEK

//#define MY_USE_MODBUS
#ifdef  MY_USE_MODBUS
// GPIO1 as ModBR Tx and GPIO3 as ModBR Rx
#define MODULE WEMOS
#define MAX_DOMOTICZ_TEMPS 2
#define USE_MODBUS_BRIDGE
#define USE_THERMOSTAT
#define THERMOSTAT_SENSOR_NAME                "DS18B20"
#endif


#ifdef  MY_USE_POW_R2
//#define MODULE SONOFF_POW_R2
#define MAX_DOMOTICZ_TEMPS 2
#endif

#ifdef  MY_USE_RELAY_SONOFF_BASIC
 #define MODULE SONOFF_BASIC
#define MAX_DOMOTICZ_TEMPS 2
#endif

#ifdef  MY_USE_RELAY_SONOFF_TH
#define MODULE SONOFF_TH
#define MAX_DOMOTICZ_TEMPS 2
#endif

#ifdef  MY_USE_SONOFF_DUAL_R2
//#define MODULE SONOFF_DUAL_R2
// https://templates.blakadder.com/sonoff_dual_R2.html
// https://tasmota.github.io/docs/devices/Sonoff-Dual-R2/
// Relay1..2 GPIO 12 (D6)- 1  GPIO 5(D1)
// DS18D20 - GPIO 2(D4)
// CT -Analog
#define MAX_DOMOTICZ_TEMPS 2
#endif

//#define MY_SONOFF_4CH
// ESP8266 (Wemos):
// Key1..4 - button1..4 как у SONOFF_4CH, GPOI0 - 1, GPOI9 - 2, GPIO10 - 3, GPIO14 - 4
// Relay1..4 GPIO12 (D6)- 1  GPIO5(D1) - 2 GPIO4(D2) - 3 GPIO15(D8) - 4
// DS18D20 -GPIO 2(D4)

// ESP32S2:
// AdcParam1 7,0,700,0.22 GPIO3 - фаза на котел
// AdcParam2 7,0,700,0.22 GPIO5 - фаза на котел
// AdcParam3 7,0,700,0.22 GPIO7 - фаза на котел
// AdcParam4 7,0,450,0.22 GPIO1 - переливной и дренажный насос
// AdcParam5 6,770,8191,0,500 GPIO2 - ADCRange - датчик давления от 0 до 5(500) атмосфер
// Prwssue  GPIO3 
// Relay1..4 GPIO9 - 1 GPIO35 - 2 GPIO33 - 3 GPIO12 - 4
// DS18D20 - GPIO16
// https://tasmota.github.io/docs/ADC/ Pressure "ADC Range" mode
// use command AdcParamX to calibrate
// The best devider 4.7/3 ком, -ref ~1,262v probably ADC_ATTEN_DB_11 150 mV ~ 2450 mV

/* TODO processing ANALOG SENSOR
MQT: tele/D3_H12KW/SENSOR =
 {"Time":"2022-11-12T12:49:58",
 "ANALOG":{
  "CTEnergy1":{"Energy":0.000,"Power":3,"Voltage":220,"Current":0.015},
  "CTEnergy2":{"Energy":0.000,"Power":2,"Voltage":220,"Current":0.008},
  "CTEnergy3":{"Energy":0.000,"Power":2,"Voltage":220,"Current":0.007},
  "A4":0
  },
  "DS18B20":  {"Id":"1DA15B1E64FF","Temperature":22.8},"TempUnit":"C"
}

Tasmota AD: tasmota::updateSensorDevices: message {
'Time': '2022-11-12T13:26:18',
'ANALOG': {
	'CTEnergy1': {'Energy': 0.0, 'Power': 1, 'Voltage': 220, 'Current': 0.007}, 
	'CTEnergy2': {'Energy': 0.0, 'Power': 2, 'Voltage': 220, 'Current': 0.01}, 
	'CTEnergy3': {'Energy': 0.0, 'Power': 2, 'Voltage': 220, 'Current': 0.009},
	'A4': 0
}, 
'DS18B20': {'Id': '1DA15B1E64FF', 'Temperature': 22.4}, 'TempUnit': 'C'}
Tasmota AD: tasmota::getSensorDevices:
 states [('DS18B20', 'Temperature', 22.4, {'Name': 'Temperatur', 'Unit': '°C', 'DomoType': 'Temperature', 'Sensor': 'DS18B20'})]
*/

#define MY_VL53L                     // enable: lib/lib_i2c
#ifdef  MY_VL53L
// https://tasmota.github.io/docs/VL53Lxx
//#define USE_VL53L0X                  //  [I2cDriver31] Enable VL53L0x time of flight sensor (I2C address 0x29) (+4k code)
#define USE_VL53L1X                    //  [I2cDriver54] Enable VL53L1X time of flight sensor (I2C address 0x29) using Pololu VL53L1X library (+2k9 code)
//  #define VL53L1X_XSHUT_ADDRESS 0x78 //  VL53L1X base address when used with XSHUT control
//  #define VL53L1X_DISTANCE_MODE Long    
#define MODULE WEMOS
#endif

#undef  MQTT_NO_RETAIN
#define MQTT_NO_RETAIN         true  // [SetOption104] No Retain - disable all MQTT retained messages,


#undef  CFG_HOLDER
#define CFG_HOLDER        4617       // [Reset 1] Change this value to load SECTION1 configuration parameters to flash

#undef  WIFI_IP_ADDRESS
#define WIFI_IP_ADDRESS        "0.0.0.0"         // [IpAddress1] Set to 0.0.0.0 for using DHCP or enter a static IP address
#undef  WIFI_GATEWAY
#define WIFI_GATEWAY           "0.0.0.0"     // [IpAddress2] If not using DHCP set Gateway IP address
#undef  WIFI_SUBNETMASK
#define WIFI_SUBNETMASK        "0.0.0.0"   // [IpAddress3] If not using DHCP set Network mask
#undef  WIFI_DNS
#define WIFI_DNS               "0.0.0.0"     // [IpAddress4] If not using DHCP set DNS IP address (might be equal to WIFI_GATEWAY)

#undef  STA_SSID1
//#define STA_SSID1              "IoT-Repeater"
//#define STA_SSID1              "IoT-MM"              // [Ssid1] Wifi SSID
#define STA_SSID1              "IoT-01"              // [Ssid1] Wifi SSID
//#define STA_SSID1              "IoT-02"              // [Ssid1] Wifi SSID
//#define STA_SSID1              "Elvis"              // [Ssid1] Wifi SSID
#undef  STA_PASS1
#define STA_PASS1              "abc1221def"                // [Password1] Wifi password
//#define STA_PASS1              "yandex.ru2010"                // [Password1] Wifi password
#undef  STA_SSID2
#define STA_SSID2              "PandoraBox1"                // [Ssid2] Optional alternate AP Wifi SSID
#undef  STA_PASS2
#define STA_PASS2              "abc1221def"                // [Password2] Optional alternate AP Wifi password

#undef WIFI_ARP_INTERVAL
#define WIFI_ARP_INTERVAL      105                         // [SetOption41] Send gratuitous ARP interval

#undef  MQTT_HOST
#define MQTT_HOST              "192.168.1.20"                // [MqttHost]

#undef  MQTT_USER
#define MQTT_USER              "mqtusr"       // [MqttUser] MQTT user
#undef  MQTT_PASS
#define MQTT_PASS              "mqtusr"       // [MqttPassword] MQTT password


// -- Location ------------------------------------
#undef LATITUDE
#define LATITUDE               56.128061         // [Latitude] Your location to be used with sunrise and sunset
#undef LONGITUDE
#define LONGITUDE              37.221792         // [Longitude] Your location to be used with sunrise and sunset

// -- Application ---------------------------------
#undef APP_TIMEZONE
#define APP_TIMEZONE           3                 // [Timezone] +1 hour (Amsterdam) (-13 .. 14 = hours from UTC, 99 = use TIME_DST/TIME_STD)

#undef MQTT_KEEPALIVE
#define MQTT_KEEPALIVE         60                // [MqttKeepAlive] Number of seconds between KeepAlive messages

#undef MQTT_SOCKET_TIMEOUT
#define MQTT_SOCKET_TIMEOUT    15                // [MqttTimeout] Number of seconds before Mqtt connection timeout

#undef MQTT_WIFI_CLIENT_TIMEOUT
#define MQTT_WIFI_CLIENT_TIMEOUT  5000           // [MqttWifiTimeout] Number of milliseconds before Mqtt Wi-Fi timeout

#undef  TELE_PERIOD
#define TELE_PERIOD            60                // [TelePeriod] Telemetry (0 = disable, 10 - 3600 seconds)

#undef  USE_ARDUINO_OTA
#undef  USE_HOME_ASSISTANT
#define  USE_HOME_ASSISTANT

#define USE_WEBSERVER                            // Enable web server and Wi-Fi Manager (+66k code, +8k mem)
  #define WEB_PORT             80                // Web server Port for User and Admin mode
  #define WEB_USERNAME         "admin"           // Web server Admin mode user name
  #define USE_JAVASCRIPT_ES6                     // Enable ECMAScript6 syntax using less JavaScript code bytes (fails on IE11)
  #define USE_ENHANCED_GUI_WIFI_SCAN             // Enable Wi-Fi scan output with BSSID (+0k5 code)
//  #define USE_WEBSEND_RESPONSE                   // Enable command WebSend response message (+1k code)
  #undef USE_EMULATION_HUE                      // Enable Hue Bridge emulation for Alexa (+14k code, +2k mem common)
  #undef USE_EMULATION_WEMO                     // Enable Belkin WeMo emulation for Alexa (+6k code, +2k mem common)
  // #define USE_CCLOADER                           // Enable CCLoader FW upgrade tool (for CC25xx devices)

#undef DISABLE_REFERER_CHK
#define DISABLE_REFERER_CHK                     // [SetOption128] Disable HTTP API

#undef APP_DISABLE_POWERCYCLE
#define APP_DISABLE_POWERCYCLE true             // [SetOption65] Disable fast power cycle detection for device reset

#undef USE_TIMERS

// -- Optional modules ----------------------------
#undef ROTARY_V1                                // Add support for Rotary Encoder as used in MI Desk Lamp (+0k8 code)
#undef USE_SONOFF_RF                            // Add support for Sonoff Rf Bridge (+3k2 code)
#undef USE_SONOFF_SC                            // Add support for Sonoff Sc (+1k1 code)
#undef USE_TUYA_MCU                             // Add support for Tuya Serial MCU
#undef USE_ARMTRONIX_DIMMERS                    // Add support for Armtronix Dimmers (+1k4 code)
#undef USE_PS_16_DZ                             // Add support for PS-16-DZ Dimmer (+2k code)
#undef USE_SONOFF_IFAN                          // Add support for Sonoff iFan02 and iFan03 (+2k code)
#undef USE_BUZZER                               // Add support for a buzzer (+0k6 code)
#undef USE_ARILUX_RF                            // Add support for Arilux RF remote controller (+0k8 code, 252 iram (non 2.3.0))
#undef USE_SHUTTER                              // Add Shutter support for up to 4 shutter with different motortypes (+11k code)
#undef USE_DEEPSLEEP                            // Add support for deepsleep (+1k code)
#undef USE_EXS_DIMMER                           // Add support for ES-Store Wi-Fi Dimmer (+1k5 code)
#undef USE_DEVICE_GROUPS                        // Add support for device groups (+5k5 code)
#undef USE_PWM_DIMMER                           // Add support for MJ-SD01/acenx/NTONPOWER PWM dimmers (+2k3 code, DGR=0k7)
#undef USE_SONOFF_D1                            // Add support for Sonoff D1 Dimmer (+0k7 code)
#undef USE_SHELLY_DIMMER                        // Add support for Shelly Dimmer (+3k code)

// -- Optional light modules ----------------------
#undef USE_LIGHT                                // Add support for light control
#undef USE_WS2812                               // WS2812 Led string using library NeoPixelBus (+5k code, +1k mem, 232 iram) - Disable by //
#undef USE_MY92X1                               // Add support for MY92X1 RGBCW led controller as used in Sonoff B1, Ailight and Lohas
#undef USE_SM16716                              // Add support for SM16716 RGB LED controller (+0k7 code)
#undef USE_SM2135                               // Add support for SM2135 RGBCW led control as used in Action LSC (+0k6 code)
#undef USE_SONOFF_L1                            // Add support for Sonoff L1 led control
#undef USE_ELECTRIQ_MOODL                       // Add support for ElectriQ iQ-wifiMOODL RGBW LED controller (+0k3 code)
#undef USE_LIGHT_PALETTE                        // Add support for color palette (+0k7 code)
#undef USE_LIGHT_VIRTUAL_CT                     // Add support for Virtual White Color Temperature (+1.1k code)
#undef USE_DGR_LIGHT_SEQUENCE                   // Add support for device group light sequencing (requires USE_DEVICE_GROUPS) (+0k2 code)
#undef USE_AC_ZERO_CROSS_DIMMER

// -- Counter input -------------------------------
#undef USE_COUNTER                              // Enable inputs as counter (+0k8 code)

// -- One wire sensors ----------------------------
#if defined(MY_USE_RELAY_SONOFF_TH) || \
    defined(MY_USE_RELAY_SONOFF_GENERIC) || \
    defined(MY_USE_GREE) || \
    defined(MY_USE_ELUX) || \
    defined(MY_USE_SONOFF_DUAL_R2)
#define USE_DS18x20                              // Add support for DS18x20 sensors with id sort, single scan and read retry (+2k6 code)
#endif
//  #define W1_PARASITE_POWER   // Optimize for parasite powered sensors
#undef USE_I2C                                  // I2C using library wire (+10k code, 0k2 mem, 124 iram)

// -- I2C sensors ---------------------------------
//#ifdef  MY_USE_RELAY_SONOFF_BASIC
#ifdef MY_USE_ELUX
//#define USE_I2C                                  // I2C using library wire (+10k code, 0k2 mem, 124 iram)
//#define USE_HTU                                  // [I2cDriver9] Enable HTU21/SI7013/SI7020/SI7021 sensor (I2C address 0x40) (+1k5 code)
//#define USE_SHT3X                              // [I2cDriver15] Enable SHT3x
#endif



// -- SPI sensors ---------------------------------
#undef USE_SPI                                  // Hardware SPI using GPIO12(MISO), GPIO13(MOSI) and GPIO14(CLK) in addition to two user selectable GPIOs(CS and DC)
#undef USE_SERIAL_BRIDGE                        // Add support for software Serial Bridge (+0k8 code)

#undef USE_AUTOCONF                             // Enable Esp32 autoconf feature, requires USE_BERRY and USE_WEBCLIENT_HTTPS (12KB Flash)
#undef USE_BERRY                                // Enable Berry scripting language

//#define OMIT_LETS_ENCRYPT_CERT
//#define OMIT_AWS_CERT

#undef USE_CSE7761                              // Add support for CSE7761 Energy monitor as used in Sonoff Dual R3

// -- Power monitoring sensors --------------------
#undef USE_ENERGY_SENSOR                        // Add support for Energy Monitors (+14k code)
  #undef USE_ENERGY_MARGIN_DETECTION              // Add support for Energy Margin detection (+1k6 code)
  #undef USE_ENERGY_POWER_LIMIT                 // Add additional support for Energy Power Limit detection (+1k2 code)
#undef USE_ENERGY_DUMMY                         // Add support for dummy Energy monitor allowing user values (+0k7 code)
#undef USE_HLW8012                              // Add support for HLW8012, BL0937 or HJL-01 Energy Monitor for Sonoff Pow and WolfBlitz
#ifdef MY_USE_PLUG_POW
  #ifdef ENERGY_VOLTAGE_ALWAYS
    #undef ENERGY_VOLTAGE_ALWAYS
  #endif
  #define ENERGY_VOLTAGE_ALWAYS  true              // [SetOption21] Enable show 

  #define USE_ENERGY_SENSOR                        // Add support for Energy Monitors (+14k code)
  #define USE_ENERGY_MARGIN_DETECTION              // Add support for Energy Margin detection (+1k6 code)
  #define USE_HLW8012                              // Add support for HLW8012, BL0937 or HJL-01 Energy Monitor for Sonoff Pow and WolfBlitz
#endif

#ifdef MY_USE_MIRTEK
  #define USE_ENERGY_SENSOR                        // Add support for Energy Monitors (+14k code)
  #define USE_MIRTEK
#endif

#undef USE_CSE7766                              // Add support for CSE7766 Energy Monitor for Sonoff S31 and Pow R2
#ifdef MY_USE_POW_R2
  #ifdef ENERGY_VOLTAGE_ALWAYS
    #undef ENERGY_VOLTAGE_ALWAYS
  #endif
  #define ENERGY_VOLTAGE_ALWAYS  true              // [SetOption21] Enable show 
  #define USE_ENERGY_SENSOR                        // Add support for Energy Monitors (+14k code)
  #define USE_ENERGY_MARGIN_DETECTION              // Add support for Energy Margin detection (+1k6 code)
  #define USE_CSE7766                              // Add support for CSE7766 Energy Monitor for Sonoff S31 and Pow R2
#endif

#undef USE_PZEM004T                             // Add support for PZEM004T Energy monitor (+2k code)
#undef USE_PZEM_AC                              // Add support for PZEM014,016 Energy monitor (+1k1 code)
#undef USE_PZEM_DC                              // Add support for PZEM003,017 Energy monitor (+1k1 code)
#undef USE_MCP39F501                            // Add support for MCP39F501 Energy monitor as used in Shelly 2 (+3k1 code)
#undef USE_BL09XX                               // Add support for BL0940 Energy monitor as used in Blitzwolf SHP-10 (+1k6 code)
#undef USE_TELEINFO                             // Add support for Teleinfo via serial RX interface (+5k2 code, +168 RAM + SmartMeter LinkedList Values RAM)
#undef USE_IEM3000                              // Add support for Schneider Electric iEM3000-Modbus series energy monitor (+0k8 code)
#undef USE_WE517                                // Add support for Orno WE517-Modbus energy monitor (+1k code)

// -- Low level interface devices -----------------
#undef USE_DHT                                  // Add support for DHT11, AM2301 (DHT21, DHT22, AM2302, AM2321) and SI7021 Temperature and Humidity sensor (1k6 code)
#ifdef  MY_USE_RELAY_SONOFF_BASIC
#define USE_DHT                                  // Add support for DHT11, AM2301 (DHT21, DHT22, AM2302, AM2321) and SI7021 Temperature and Humidity sensor (1k6 code)
#endif

// -- IR Remote features - subset of IR protocols --------------------------
#undef USE_IR_REMOTE                            // Send IR remote commands using library IRremoteESP8266 and ArduinoJson (+4k3 code, 0k3 mem, 48 iram)
#ifdef MY_USE_IR_REMOTE
#define MODULE WEMOS
#define USE_IR_REMOTE_FULL                           // Support all IR protocols from IRremoteESP8266
#endif
// -- Zigbee interface ----------------------------
#undef USE_ZIGBEE                               // Enable serial communication with Zigbee CC2530 flashed with ZNP (+49k code, +3k mem)

// -- Other sensors/drivers -----------------------
#undef USE_RC_SWITCH                            // Add support for RF transceiver using library RcSwitch (+2k7 code, 460 iram)
#undef USE_RF_SENSOR                            // Add support for RF sensor receiver (434MHz or 868MHz) (+0k8 code)

#ifdef MY_USE_PID

#define USE_PID
#define MAX_DOMOTICZ_TEMPS 2
// https://connect.smartliving.ru/profile/2920/blog167.html
#define MODULE SONOFF_4CH
// https://tasmota.github.io/docs/devices/Sonoff-4CH-DIY/ 
//// backlog Interlock 1,2; Interlock 1; SetOption80 1
// Exec Command
// backlog ShutterOpenDuration1 120;ShutterCloseDuration1 120
// for HomeAssistant set SetOption59 https://tasmota.github.io/docs/Home-Assistant/#lights
// SetOption59 1
#undef APP_INTERLOCK_MODE
#define APP_INTERLOCK_MODE     true             // [Interlock] Relay interlock mode
#undef APP_INTERLOCK_GROUP_1
#define APP_INTERLOCK_GROUP_1  0x03             // [Interlock] Relay bitmask for 
#define USE_SHUTTER                             // Add Shutter support for up to 4 shutter with different motortypes (+11k code)
#undef SHUTTER_SUPPORT
#define SHUTTER_SUPPORT        true           // [SetOption80] Enable shutter support

#if 0 // Полотенцесушитель
#define PID_SETPOINT                 40
#define PID_PROPBAND                 10
#define PID_INTEGRAL_TIME            300
#define PID_DERIVATIVE_TIME          0
#define PID_INITIAL_INT              0.2
#define PID_MAX_INTERVAL             300
#define PID_DERIV_SMOOTH_FACTOR      3 
#define PID_AUTO                     1
#define PID_MANUAL_POWER             0
#define PID_UPDATE_SECS              0 
#define PID_USE_LOCAL_SENSOR 
#define PID_USE_TIMPROP              0
#define PID_SHUTTER                  1
#define PID_REPORT_MORE_SETTINGS     1
#endif

#if 0 // Теплый пол
#define PID_SETPOINT                 25
#define PID_PROPBAND                 25
#define PID_INTEGRAL_TIME            1200
#define PID_DERIVATIVE_TIME          0
#define PID_INITIAL_INT              0.2
#define PID_MAX_INTERVAL             300
#define PID_DERIV_SMOOTH_FACTOR      5 
#define PID_AUTO                     1
#define PID_MANUAL_POWER             0
#define PID_UPDATE_SECS              0 
#define PID_USE_LOCAL_SENSOR 
#define PID_USE_TIMPROP              0
#define PID_SHUTTER                  1
#define PID_REPORT_MORE_SETTINGS     1
#endif

#if 0 // Батареи
#define PID_SETPOINT                 40
#define PID_PROPBAND                 25
#define PID_INTEGRAL_TIME            1200
#define PID_DERIVATIVE_TIME          0
#define PID_INITIAL_INT              0.2
#define PID_MAX_INTERVAL             300
#define PID_DERIV_SMOOTH_FACTOR      5 
#define PID_AUTO                     1
#define PID_MANUAL_POWER             0
#define PID_UPDATE_SECS              0 
#define PID_USE_LOCAL_SENSOR 
#define PID_USE_TIMPROP              0
#define PID_SHUTTER                  1
#define PID_REPORT_MORE_SETTINGS     1
#endif

#if 1 // 15KW3WAY Relay3 (Pump) give power to relay4 (Heater) to protect heater work without the pump!
#define PID_SETPOINT                 0
#define PID_PROPBAND                 25
#define PID_INTEGRAL_TIME            1200
#define PID_DERIVATIVE_TIME          0
#define PID_INITIAL_INT              0
#define PID_MAX_INTERVAL             300
#define PID_DERIV_SMOOTH_FACTOR      5 
#define PID_AUTO                     1
#define PID_MANUAL_POWER             0
#define PID_UPDATE_SECS              0
#define PID_USE_LOCAL_SENSOR 
#define PID_USE_TIMPROP              0
#define PID_SHUTTER                  1
#define PID_REPORT_MORE_SETTINGS     1
#endif

#endif  //MY_USE_PID 

#endif  // _USER_CONFIG_OVERRIDE_H_
