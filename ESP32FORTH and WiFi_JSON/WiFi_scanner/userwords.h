#include <string.h>

#define USER_WORDS \
X("WiFi.scanNetworks", wifi_scan, PUSH WiFi.scanNetworks();) \
X("WiFi.scanDelete", wifi_scdel, WiFi.scanDelete();) \
X("WiFi.SSID", wifi_ssid, strcpy(c1, WiFi.SSID(n0).c_str()); DROP; ) \
X("WiFi.RSSI", wifi_rssi, n0= WiFi.RSSI(n0);) \
X("WiFi.RSSI1", wifi_rssi1, PUSH  WiFi.RSSI();) \
X("WiFi.channel", wifi_chan, n0= WiFi.channel(n0);) \
X("WiFi.channel1", wifi_chan1, PUSH WiFi.channel();) \
X("WiFi.encryptionType", wifi_encrypt, n0= static_cast<int>(WiFi.encryptionType(n0));) 
