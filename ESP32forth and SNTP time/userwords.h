/* 
configTime ( gmtoffset daylightoffset z-ntp ---) synchronize ESP32 time with 
    ntp server, needs internet connection running
getLocalTime ( tmstructure---t/f ) fill tm structure with actual time from 
    ESP32 internal timer
asctime ( tmstructure timestring---z-timestring)  create z-string with date time info
    from tm structure       

*/

#define USER_WORDS \
Y(configTime, configTime( n2, n1, c0); DROPn(3); ) \
Y(getLocalTime, n0=getLocalTime((tm *) a0); ) \
Y(asctime, const char* atime=asctime((tm *) a1); strcpy(c0, atime); NIP; )



