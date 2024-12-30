\ ESP32forth program for HTTP time request
\ used with userwords.h for missing functions

defined? --http 0<> [if] forget --http [then]
create --http
decimal forth only wifi

create payload 1024 allot       \ buffer for getString and deserialize
    payload 1024 erase
create errorbuf 120 allot       \ buffer for deserialize error
    errorbuf 120 erase
create stringbuf 120 allot      \ buffer for getString
    stringbuf 120 erase    

: wificonnection    ( -- )          \ connect to my wifi
    z" TUKKUK1" z" SHX3U21a" login 
;

: retriveJSON   ( --- z-payload) \ retrive payload from WorldTime
    z" http://worldtimeapi.org/api/timezone/Europe/Prague" HTTP.begin
    if cr ." connected to WorldTime"
        else
        cr ." no connection to WorldTime"
    then
    begin
    200 ms
    HTTP.get    \ send GET
        dup cr ." GET response: " .
    0 > until
    payload 1024 erase      \ clear payload buffer
    payload 1024 HTTP.getString ( --- z-payload) 
    dup cr ." obtained payload:" cr z>s type
; 
: retriveJSONdata ( z-payload--- )
    errorbuf JSON.deserialize
    cr ." JSON deserialize error: " z>s type
    stringbuf 120 z" datetime" JSON.getString
    cr ." retrived datetime: " z>s type
    stringbuf 120 z" timezone" JSON.getString
    cr ." retrived timezone: " z>s type
    stringbuf 120 z" client_ip" JSON.getString
    cr ." my IP address: " z>s type
    z" day_of_week" JSON.getNum 
    cr ." day of week: " .
;
    


          
           
