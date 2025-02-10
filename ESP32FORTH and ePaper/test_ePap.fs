\ program for simple test of ePaper display
defined? --test_ePap 0<> [if] forget --test_ePap [then]
create --test_ePap

\ \include /spiffs/bitmapGR.fs  \  load of graphics symbols for graphTest
0 constant BLACK
1 constant WHITE

: EPinit    ( --- )     \ show white clear screen
    D.init 0 D.setrotation WHITE D.fillscreen
    D.display
;
: rectTest  ( --- )
    50 0 do
        i 10 + dup 200 i 2 * - 100 i 2 * - 5 BLACK D.drawroundrect
    2 +loop  D.display
;
: textTest  ( --- )
    D.freesans18 BLACK D.settextcolor 2 D.settextsize
    210 100 D.setcursor
    z" Hello ESP32forth" D.println
    D.freesansbold18 1 D.settextsize
    z"             Hello ESP32forth" D.println D.display
;
: graphTest ( --- )
    10 300 01d BLACK D.drawbitmap
    60 300 02d BLACK d.drawbitmap
    D.display
;           

epinit recttest texttest graphtest D.hibernate
     
