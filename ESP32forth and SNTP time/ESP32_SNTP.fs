\ ESP32forth program for time request with SNP frm NTP server
\ based on Arduino C code from 
\ https://techtutorialsx.com/2021/09/01/esp32-system-time-and-sntp/

also structures decimal
struct tm ( --|-- size of struct) \ definition of structure tm
    i32 field tm_sec    \ int seconds after the minute 0-61
    i32 field tm_min    \ int minutes after the hour 0-59
    i32 field tm_hour   \ int hours since midnight 0-23
    i32 field tm_mday    \ int day of the month 1-31
    i32 field tm_mon    \ int months since January 0-11
    i32 field tm_year   \ int years since 1900	
    i32 field tm_wday   \ int days since Sunday 0-6
    i32 field tm_yday   \ int days since January 1 0-365
    i32 field tm_isdst  \ int Daylight Saving Time flag

create time tm allot    \ creation of structure time with tm content
    time tm erase       \ erase new structure time
create atime 80 allot   \ buffer for time string
    atime 80 erase         
: ntpServer ( ---z-addr )
    z" time.google.com"
;   
    
: wificonnection    ( -- )          \ connect to my wifi
    z" yourSSID" z" yourPSW" login 
;
: syncTime  ( --- )     \ synchronize ESP32 time with SNTP
    3600 3600 ntpServer configTime
;
: createTime ( --- )     \ fill time structure with time data
    time getLocalTime
    if cr ." Time info obtained"
        else cr ." Time info error"
    then     
;

: printTime ( ---)          \ print current date time info line
    createTime              \ fill time structure with actual time
    time atime asctime      \ fill atime buffer and print
    cr z>s type cr      
;
: year? ( --- year_number)         \ return year from time struct
    time tm_year @ 1900 +
;
: month? ( ---month_number)
    time tm_mon @ 1+
;
: day? ( ---day_number)
    time tm_mday @ 
;           
