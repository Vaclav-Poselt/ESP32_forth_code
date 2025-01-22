#include <HTTPClient.h>
#include <ArduinoJson.h>

HTTPClient http;
JsonDocument doc;       // doc variable for ArduinoJSON
JsonDocument filter;    // filter variable for deserialization filtering

/* 
HTTP.begin ( z-url---error-t/f) open connection with url, returns t/f
http.get ( ---n) send GET , return negative as f/code, code is 200 as OK, 404 ...
http.getString ( payloadbufer size--- payloadbuffer ) reads respond max size bytes 
    into z-payloadbuf
http.end ( --- ) ends connection with url    
JSON.filter ( z-filter errorbuf ---z-errorbuf ) create filter for deserialization
JSON.deserialize ( z-payload errorbuf---z-errorbuf ) create deserialized doc
    from z-payload, in z-errorbuf is "OK" or error text )
JSON.Fdeserialize ( z-payload errorbuf---z-errorbuf ) create deserialized 
    filtered doc from z-payload and filter, in z-errorbuf is "OK" or error text ),
    use only after JSON.filter 
JSON.serialize ( size buffer---n z-buffer ) create new z-buffer string from doc, 
    primary for test of result after JSON.Fdeserialize, size is size of buffer,
    n is no of written bytes into buffer, if n>size there is error-too big for stringbuf      
JSON.getString ( stringbuf stringbuffersize z-key---z-stringbuf ) retrive string key value
    to stringbuf
JSON.getNum ( z-key--- n) retrive integer key value, also for bool as 1/0
JSON.get2String ( stringbuf stringbuffersize z-key1 z-key2---z-stringbuf ) retrive
     string from 2 keys object to stringbuf
JSON.get2Num (z-key1 z-key2---n ) retrive integer value from 2 keys
    object, also for bool as 1/0
JSON.size ( ---n ) return no of elements in the JSON doc after deserialization
JSON.getFNum ( z-key---<fp>) retrive float key value to floating point stack
JSON.get2FNum (z-key1 z-key2---<fp>) retrive float value from 2 keys
    object to fp stack
JSON.get3String ( stringbuf stringbuffersize z-key1 index z-key2---z-stringbuf )   
JSON.get3Num (z-key1 index z-key2---n )
JSON.get2FNum (z-key1 index z-key2---<fp>)
JSON.get4FNum (z-key1 index z-key2 key3---<fp>)
JSON.get4Num (z-key1 index z-key2 key3---n)
JSON.get5Num (z-key1 index1 z-key2 index 2 key3---n)
JSON.get5String (stringbuf stringbufsize z-key1 index1 z-key2 index2 key3---z-stringbuf)

note: this JSON.getxxxs  have simple error checking  for errors from doc[] with not existent
keys: returned string "NOTFOUND", returned number 0, 0.00 on f-stack

for forecast I need
- key->string                                    getString
- key->number                                    getNum
- key key->string ( city name)                   get2String
- key key->number ( city sunrise)                get2Num
- key n key->num ( list 0 visibility)            get3Num
- key n key key ->float ( list 0 main temp)      get4FNum
- key n key->string ( list 0 dt_txt)             get3String
- key n key key ->num ( list 0 main pressure)    get4Num
- key n key n key->num ( list 0 weather 0 id)    get5Num
- key n key n key->string ( list 0 weather 0 description) get5String


*/

#define USER_WORDS \
X("HTTP.begin", httpbegin, n0=http.begin(c0); ) \
X("HTTP.get", httpget, PUSH http.GET(); ) \
X("HTTP.getString", httpgetstring, const char* zpay=http.getString().c_str(); \
    strlcpy(c1, zpay, n0); DROP;) \
X("HTTP.end", httpend, http.end(); ) \
X("JSON.filter", jsonfiltr,  DeserializationError error = deserializeJson(filter, c1); \ 
    strcpy(c0, error.c_str()) ; NIP; ) \
X("JSON.Fdeserialize", jsonfdeser, \
    DeserializationError error = deserializeJson(doc, c1, DeserializationOption::Filter(filter)); \ 
    strcpy(c0, error.c_str()) ; NIP; ) \
X("JSON.deserialize", jsondeser, DeserializationError error = deserializeJson(doc, c1); \ 
    strcpy(c0, error.c_str()) ; NIP; ) \
X("JSON.serialize", jsonser, n1=serializeJson(doc, c0, n1); ) \        
X("JSON.getString", jsongetstr, const char* retrievedValue=doc[c0].as<const char*>(); \
     if (retrievedValue){strlcpy(c2, retrievedValue, n1);} \
    else {strlcpy(c2,"NOTFOUND", n1);} ; DROPn(2); ) \
X("JSON.getNum", jsongetnum, n0=doc[c0].as<int>(); ) \
X("JSON.get2String", jsonget2str, const char* retrievedValue=doc[c1][c0].as<const char*>(); \
    if (retrievedValue){strlcpy(c3, retrievedValue, n2);} \
    else {strlcpy(c3,"NOTFOUND", n2);} ; DROPn(3); ) \
X("JSON.get2Num", jsonget2num, n0=doc[c1][c0].as<int>(); NIP; ) \
X("JSON.size", jsonsize,  PUSH doc.size(); ) \
X("JSON.getFNum", jsongetfnum, *++fp = doc[c0].as<float>(); DROP; ) \
X("JSON.get2FNum", jsonget2fnum, *++fp= doc[c1][c0].as<float>(); DROPn(2); ) \
X("JSON.get3String", jsonget3str, const char* retrievedValue=doc[c2][n1][c0].as<const char*>(); \
     if (retrievedValue){strlcpy(c4, retrievedValue, n3);} \
    else {strlcpy(c4,"NOTFOUND", n3);} ; DROPn(4); ) \
X("JSON.get3Num", jsonget3num, n0=doc[c2][n1][c0].as<int>(); NIPn(2); ) \
X("JSON.get3FNum", jsonget3fnum, *++fp= doc[c2][n1][c0].as<float>(); DROPn(3); ) \
X("JSON.get4FNum", jsonget4fnum, *++fp= doc[c3][n2][c1][c0].as<float>(); DROPn(4); ) \
X("JSON.get4Num", jsonget4num, n0=doc[c3][n2][c1][c0].as<int>(); NIPn(3); ) \
X("JSON.get5Num", jsonget5num, n0=doc[c4][n3][c2][n1][c0].as<int>(); NIPn(4); ) \
X("JSON.get5String", jsonget5str, const char* retrievedValue=doc[c4][n3][c2][n1][c0].as<const char*>(); \
    if (retrievedValue){strlcpy(c6, retrievedValue, n5);} \
    else {strlcpy(c6,"NOTFOUND", n5);} ; DROPn(6); ) 

