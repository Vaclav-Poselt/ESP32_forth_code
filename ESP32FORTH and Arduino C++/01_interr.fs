\ program for simple interrupt possibility test
\ case unsensitive code
\ from esp32-hal-gpio.h :
\ GPIO FUNCTIONS
\ #define INPUT             0x01
\ Changed OUTPUT from 0x02 to behave the same as Arduino pinMode(pin,OUTPUT) 
\ where you can read the state of pin even when it is set as OUTPUT
\ #define OUTPUT            0x03 
\ #define PULLUP            0x04
\ #define INPUT_PULLUP      0x05
\ #define PULLDOWN          0x08
\ #define INPUT_PULLDOWN    0x09

\ Interrupt Modes
\ #define DISABLED  0x00
\ #define RISING    0x01
\ #define FALLING   0x02
\ #define CHANGE    0x03
\ #define ONLOW     0x04
\ #define ONHIGH    0x05
\ #define ONLOW_WE  0x0C
\ #define ONHIGH_WE 0x0D

defined? MARKER 0<> [if] forget MARKER [then]   
create MARKER

only Forth definitions also interrupts
\ attach words in interrupts vocabulary

decimal
33 constant ButtonPin
32 constant LEDPin
3 constant OUT_IN
5 constant INPUT_PULLUP

: pinIntHandle ( xt pin intMode -- ) \ attach xt isr word + mode to pin
    over >r gpio_set_intr_type throw    \ pin type--0/err
    r> swap 0 gpio_isr_handler_add throw    \ pin xt 0--0/err
    ;

: manLED    ( -- ) \ word for interrupt action reversing LED
    LEDpin digitalRead  0= \ reverse LED light
    if  1 else 0 then       \ possible read and write from GPIO32 LEDpin
        LEDpin swap digitalWrite
    ;

: setup ( -- ) \ 
    LEDPin OUT_IN pinMode   \ with out_in is possible to write and read
    ButtonPin INPUT_PULLUP  pinMode  \ input with pull_up resistor
    LEDPin HIGH digitalWrite
    ;
setup   \ make setup    
' manLED ButtonPin #GPIO_INTR_NEGEDGE pinIntHandle \ attach interrupt on hi->lo
            \ with action word manLED  
    
: mainLoop ( --) \ main program loop for test only
    begin
    ." ESP32forth goes" cr
    ." Input 32: " LEDPin digitalRead . cr
    1000 ms
    key? until 
    ;    
    
    



