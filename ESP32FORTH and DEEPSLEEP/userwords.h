#include <cstring>

RTC_DATA_ATTR int RTCvar1 =0 ;    // variable in RTC memory
RTC_DATA_ATTR int RTCvar2 =0 ;    // variable in RTC memory
RTC_DATA_ATTR char RTCstr[32];    // char variable in RTC memory
void savetoRTC1(int value1)          // save value to  RTC 
    { RTCvar1= value1; }
void savetoRTC2(int value1)          // save value to  RTC 
    { RTCvar2= value1; }
void savetoRTCstr(char value3[32])
    { strcpy(RTCstr,value3);}    
    
#define USER_WORDS \
X("RTC1!", savetoRTC1, savetoRTC1(n0); DROP; ) \
X("RTC1@", fromRTC1, PUSH RTCvar1; ) \
X("RTC1addr", RTC1addr, PUSH (uintptr_t)&RTCvar1; ) \
X("RTC2!", savetoRTC2, savetoRTC2(n0); DROP; ) \
X("RTC2@", fromRTC2, PUSH RTCvar2; ) \
X("RTC2addr", RTC2addr, PUSH (uintptr_t)&RTCvar2; ) \
X("RTCstr!", savetoRTCstr, savetoRTCstr(c0); DROP; ) \
X("RTCstr@", fromRTCstr, PUSH RTCstr; ) \
X("RTCstraddr", RTCstraddr, PUSH (uintptr_t)&RTCstr; )


    
 
