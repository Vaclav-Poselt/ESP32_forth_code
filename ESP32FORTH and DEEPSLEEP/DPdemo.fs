        \ DPdemo.fs with subs words of some real program
cr ." OK, here I am after restart of ESP32forth." 1000 ms cr
: first ." measuring no 1" cr 1000 ms ;
: second ." measuring no 2" cr 1000 ms ;
: third ." meauring no 3" cr 1000 ms ;
: save-send ." now sending/saving measurements" cr 1000 ms ;
esp
: mainprg \ ( --- ) program to run
    first second third
    save-send
    ." going to Deep Sleep for 5 secs" 
    5000000  deepsleep
    ;
mainprg
      
