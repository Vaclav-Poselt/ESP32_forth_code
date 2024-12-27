2/* 
* analogReadMilliVolts ( pin--mV)
* analogReadResolution ( n-- ) adjust A/D convertor resolution 9-12bits.
*   Default is 12.
* analogSetAttenuation ( n-- ) adjust attenuation for all A/D measurements.
*   Range 0-3. Default 11dB.
* attenuation is defined:
* typedef enum {
*    ADC_0db,
*    ADC_2_5db,
*    ADC_6db,
*    ADC_11db,
*    ADC_ATTENDB_MAX
* } adc_attenuation_t;
*/ 

/* Task Watchdog Timer (TWDT)
* !! works with Arduino libs 2.x, in 3.x there are changes in esp_task_wdt_init
* so this does not work , change explained in 
* https://iotassistant.io/esp32/fixing-error-hardware-wdt-arduino-esp32/ !!
* WDinit ( timeout panic-- err ) timeout in seconds, panic 0 is log output, 
* -1 is fireing reset, err 0 is OK, other err codes according  esp_err.h, this
* initializes TWDT to run
* WDdeinit ( --err ) this ends TWDT, can be used after tasks unsubscribed
* WDtaskAdd ( --err )  subscribes current running task to TWDT
* WDreset ( --err )  resets TWDT to not fire
* WDtaskRemove ( --err ) unsubscribe current task from TWDT
*/

#include <esp_task_wdt.h>
#define USER_WORDS \
     Y(analogReadMilliVolts, n0 = analogReadMilliVolts(n0)) \
     Y(analogReadResolution, analogReadResolution(n0); DROP) \
     Y(analogSetAttenuation, analogSetAttenuation((adc_attenuation_t) n0); DROP) \
     X("WDinit", watchdoginit, n0=esp_task_wdt_init(n1, b0); NIP ) \
     X("WDdeinit", watchdogdeinit, PUSH esp_task_wdt_deinit()) \
     X("WDtaskAdd", wdtaskadd, PUSH esp_task_wdt_add(NULL)) \
     X("WDreset", watchdogreset, PUSH esp_task_wdt_reset()) \
     X("WDtaskRemove", wdtaskremove, PUSH esp_task_wdt_delete(NULL)) 


     
     
     
     
     
     
     
     
