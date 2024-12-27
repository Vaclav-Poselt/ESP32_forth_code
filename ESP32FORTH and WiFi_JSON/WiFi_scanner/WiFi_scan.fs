\ ESP32forth program to scan available WiFi networks
\ used with userwords.h for missing WiFi functions

defined? --WIFIsc 0<> [if] forget --WIFIsc [then]
create --WIFIsc
decimal forth only wifi

: setup WIFI_MODE_STA WiFi.Mode         \ adjust station mode of wifi
WiFi.Disconnect                 \ and disconnect  for sure
cr ." Basic setup done" 500 ms
; 
: printHeader                   \ print header of table
." No.  SSID                               RSSI   Ch   Encryption" cr
;
: .r ( n1 n2-- )                \ print n1 justified to n2 places
    >r str r> over - spaces type \ not ANSI
;

create SSIDbuf 32 allot SSIDbuf 32 0 fill \ 32 bytes for SSID z-string

: scanNetworks ( ---n ) \ search for wifi networks, return no of networks 
    cr ." Now start wifi scanning"
    WiFi.scanNetworks cr ." Scanning finished"
    dup                             \ no of found networks
    0= if cr ." No networks found" drop
        else dup cr . ." Networks found." cr
        then
;    

: mainloop ( --- )
    setup
    begin                           \ start repeating scanning loop
        scanNetworks                \ (--n) no of found netw
        printHeader
         0 do                     \ print results of scanning from 0!
            i 2 .r ."  | "          \ nr.
            SSIDbuf i WiFi.SSID     \ ( ---ssidbuf ) read SSID into buf
            z>s dup >r type \ print SSID
            32 r> - spaces          \ adjust to lenght 32
            ."  | " 
            i WiFi.RSSI 4 .r        \ print RSSI
            ."  | "
            i WiFi.channel 2 .r     \ print channel
            ."  | "
            i WiFi.encryptionType   \ returns ordinal no of enumeration
                                    \ type wifi_auth_mode_t print encryption
            case
                0 of s" open"       endof
                1 of s" WEP"        endof
                2 of s" WPA"        endof
                3 of s" WPA2"       endof
                4 of s" WPA+WPA2"   endof
                5 of s" WPA2-EAP"   endof
                6 of s" WPA3"       endof
                7 of s" WPA2+WPA3"  endof
                8 of s" WAPI"       endof
            endcase
            type cr 10 ms     
            loop
    WiFi.scanDelete                 \ clear scan results
    2000 ms
    key? until
    ;
       
