\ ESP32forth program for HTTP weather request
\ used with userwords.h for missing functions for http and arduinoJson

defined? --ESPweatherfore 0<> [if] forget --ESPweatherfore [then]
create --ESPweatherfore

s" /spiffs/strings.fs" included \ strings functions
 
decimal forth only wifi

create payload 16384 allot       \ buffer for getString and deserialize
    payload 16384 erase
create errorbuf 120 allot       \ buffer for deserialize error
    errorbuf 120 erase
create stringbuf 120 allot      \ buffer for getString
    stringbuf 120 erase 
120 string serverPath           \ variable for HTTP.begin
6 string City                   \ city variable
40 string OWMapApiKey           \ variable for API key
20 string units                 \ variable for units
                                \ next fill string variables for serverPath
s" http://api.openweathermap.org/data/2.5/forecast?q=" serverPath $!
s" Prague" City $!
s" &APPID=YOURAPIKEY" OWMapApiKey $!
s" &units=metric&cnt=3" units $!   \ cnt=3 timestamps for first testing

City serverPath append$
OWmapApiKey serverPath append$
units serverPath append$        \ construct full serverPath

: ztype ( c-addr---)            \ helping word to type z-string
    z>s type
;    
: s120  ( ---stringbuf 120 )        \ helping word 
    stringbuf 120
;     
: wificonnection    ( -- )          \ connect to my wifi
    z" SSID" z" PSW" login

;  

: retriveFORE   ( z-serverPath--- z-payload) \ retrive 5 days forecast from OWMap
    HTTP.begin
    if cr ." connected to OpenWeatherMapAPI"
        else
        cr ." no connection to OWMAPI"
    then
    begin
    200 ms
    HTTP.get    \ send GET
        dup cr ." GET response: " .
    0 > until
    payload 16384 erase      \ clear payload buffer
    payload 16384 HTTP.getString ( --- z-payload) \ read weather forecast JSON
    dup cr ." obtained payload:" cr ztype
    http.end                \ close connection
    wifi.disconnect         \ end wifi connection
; 

: retriveJSONdata ( z-payload--- )  \ create json doc from received data
    errorbuf JSON.deserialize       
    cr ." deserialization error: " ztype \ if correctly created doc shows OK
;    
: printnForecast { n1 }        \ print n1th 3h forecast from 0-39 5days forecast
    2 set-precision            \ set 2 decimal places for f.
    s120 z" city" z" name" JSON.get2String
    cr ." Weather forecast for city: " ztype
    s120 z" list" n1 z" dt_txt" JSON.get3String
    cr ." Forecast for date time: " ztype
    z" list" n1 z" main" z" temp" JSON.get4FNum
    cr ." temperature deg C: " f.
    z" list" n1 z" main" z" pressure" JSON.get4Num
    cr ." air pressure hPa: " .
    z" list" n1 z" main" z" humidity" JSON.get4Num
    cr ." humidity %: " .
    s120 z" list" n1 z" weather" 0 z" description" JSON.get5String
    cr ." weather description: " ztype
    z" list" n1 z" wind" z" speed" JSON.get4FNum
    cr ." wind speed m/sec: " f.
    z" list" n1 z" rain" z" 3h" JSON.get4FNum
    cr ." rain mm for last 3h: " f.
    z" list" n1 z" snow" z" 3h" JSON.get4FNum
    cr ." snow mm for last 3h: " f. cr
;    

\ to create smaller json doc it can be used filter for desired only data
\ here possible testing sequence for use from command line    
120 string filter   \ variable for JSON filter
r| {"list":[{"main":{"temp":true},"dt_txt":true}]}| filter $! \ desired keys
filter s>z errorbuf JSON.filter \ create json filter
serverpath s>z retriveFORE      \ retrive data from OWMap
errorbuf JSON.fdeserialize ztype \ Fdeserialize and print error
16384 payload JSON.serialize ztype ( ---n z-payload) \ type content of filtered
                                    \ doc, n is lenght of created data 
    
                                 

          
           
