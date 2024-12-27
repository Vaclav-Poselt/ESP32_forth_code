\ program for Task Watchdog Timer TWDT
\ case unsensitive code
\ info from esp_task_wdt.h
\ needs ESP32forth compiled with USERWORDS.h with new words:
\  WDinit ( timeout panic-- err ) timeout in seconds, panic 0 is log output, 
\ -1 is fireing reset, err 0 is OK, other err codes according  esp_err.h, this
\ word initializes TWDT to run
\ WDdeinit ( --err ) this ends TWDT, can be used after tasks unsubscribed
\ WDtaskAdd ( --err )  subscribes current running task to TWDT
\ WDreset ( --err )  resets TWDT to not fire, feeding watchdog
\ WDtaskRemove ( --err ) unsubscribe current task from TWDT

defined? MARKER 0<> [if] forget MARKER [then]   
create MARKER

only Forth
decimal

10 value WDT_TIMEOUT \ 10 seconds time-out
0 constant logTWDT   \ watchdog activates log or hard reset
-1 constant resetTWDT

\ 1st test with user manualy reseting TWDT by pressing key
: WDlogTest ( -- ) \ test watchdog generating log only
    WDT_timeout logTWDT WDinit drop \ adjusts TWDT time and action
    WDtaskAdd drop  \ loose watchdog from chain
    5 for           \ loop giving 6 times chance to press key
        begin
        ." Watchdog running, press button to feed it!" cr
        ms-ticks . ."  ms" cr
        500 ms
        key? until key drop
    WDreset drop \ food for wd activated by key press
    cr ." great, food accepted by WD " cr cr
    ." loop no: " i . cr
    next
    WDtaskRemove drop \ unsubscribe
    \ WDdeinit drop   \ ends TWDT, but it generates error 0x103 ??
    ." TWDT  deactivated by unsubscribing"  cr
    ;

\ 2nd test with 2 tasks reseting periodicaly timer     
tasks
defer hi1 \ defered action word for task
defer hi2
: noop ; \ does nothing, prepared to "deactivate" tasks
\ next 2 tasks with WDT reseting command
: action1  ." Time 1sttask is: " ms-ticks . cr 2000 ms 
    WDreset drop  ;    \ food for wd - reset counter
: action2  ." Time 2ndtask is: " ms-ticks . cr 3000 ms
    WDreset drop  ;
' action1 is hi1        \ fill defered action words
' action2 is hi2     
' hi1 100 100 task 1sttask \ create 2 tasks
' hi2 100 100 task 2ndtask

: WDresetTest ( -- ) \ test watchdog generating ESP32 reset
    WDT_timeout resetTWDT WDinit drop \ adjusts TWDT time and action
    WDtaskAdd drop  \ loose watchdog from chain
    1sttask start-task 2ndtask start-task \ and activate tasks
    ;
\ ' noop is hi1 \ this command removes reseting in task1
\ ' noop is hi2 \ this command removes reseting in task2
\ with resulting reseting ESP32 after 10 sec timeout
    
    



