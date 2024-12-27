#include <HTTPClient.h>
#include <ArduinoJson.h>

HTTPClient http;
JsonDocument doc;   // doc variable for ArduinoJSON

/* 
HTTP.begin ( z-url---error-t/f) open connection with url, returns t/f
http.get ( ---n) send GET , return negative as f/code, code is 200 as OK, 404 ...
http.getString ( payloadbufer size--- payloadbuffer ) reads respond max size bytes 
    into z-payloadbuf[size-1], must erase to 0 payloadbuf after each use!
http.end ( --- ) ends connection with url    
JSON.deserialize ( z-payload errorbuf---z-errorbuf ) create deserialized doc
    from z-payload, in z-errorbuf is "OK" or error text 
JSON.getString ( stringbuf z-key---z-stringbuf ) retrive string key value
    to stringbuf
JSON.getNum ( z-key--- n) retrive numerical key value, also for bool as 1/0
*/

#define USER_WORDS \
X("HTTP.begin", httpbegin, n0=http.begin(c0); ) \
X("HTTP.get", httpget, PUSH http.GET(); ) \
X("HTTP.getString", httpgetstring, const char* zpay=http.getString().c_str(); \
    strlcpy(c1, zpay, strlen(c1)); DROP;) \
X("HTTP.end", httpend, http.end(); ) \
X("JSON.deserialize", jsondeserialize, DeserializationError error = deserializeJson(doc, c1); \ 
    strcpy(c0, error.c_str()) ; NIP ) \
X("JSON.getString", jsongetstring, const char* retrievedValue=doc[c0].as<const char*>(); \
     strlcpy(c1, retrievedValue, strlen(c1)); DROP; ) \
X("JSON.getNum", jsongetnum, n0=doc[c0]; )    

