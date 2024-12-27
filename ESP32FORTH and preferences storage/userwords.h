#include <Preferences.h>
Preferences preferences; // global instance of Preferences
#define USER_WORDS \
X("preferences.begin", pre_begin, { n0 = preferences.begin(c1, b0); NIP;} ) \
X("preferences.end", pre_end, preferences.end();) \
X("preferences.clear", pre_clear, { PUSH preferences.clear(); } ) \
X("preferences.isKey", pre_isKey, { n0 = preferences.isKey(c0); } ) \
X("preferences.remove", pre_remove, { n0 = preferences.remove(c0);} ) \
X("preferences.putInt", pre_putInt, { n0 = preferences.putInt(c1, n0); NIP;} ) \
X("preferences.getInt", pre_getInt, { n0 = preferences.getInt(c0);} ) \
X("preferences.putString", pre_putString, { n0 = preferences.putString(c1, c0); NIP; } ) \
X("preferences.getString", pre_getString, { n0 = preferences.getString(c2, c1, n0); NIPn(2);} ) \
X("preferences.putBytes", pre_putBytes, { n0= preferences.putBytes(c2, b1, n0); NIPn(2);} ) \
X("preferences.getBytes", pre_getBytes, { n0= preferences.getBytes(c2, b1, n0); NIPn(2);} ) \
X("preferences.getBytesLength", pre_getBytesLength, { n0= preferences.getBytesLength(c0);} )

