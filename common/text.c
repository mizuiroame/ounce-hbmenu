#include "text.h"

static u64 s_textLanguageCode = 0;

#ifdef __SWITCH__
static int s_textLang = SetLanguage_ENUS;
#else
static int s_textLang = 1;
#endif

Result textInit(void) {
    #ifdef __SWITCH__
    // The menu's strings are English only (language.c does not cover the
    // other languages yet), so the system language is not looked up. The
    // lookup, setMakeLanguage, also failed with 2345-0011 on consoles whose
    // language is not in the settings service's list for applications, and
    // the menu then did not start.
    s_textLang = SetLanguage_ENUS;

    // The language code selects the system's shared fonts.
    Result rc = setInitialize();
    if (R_SUCCEEDED(rc)) rc = setGetSystemLanguage(&s_textLanguageCode);
    setExit();
    if (R_FAILED(rc)) return rc;
    #else
    s_textLang = 1;
    #endif

    return 0;
}

int textGetLang(void) {
    return s_textLang;
}

const char* textGetString(StrId id) {
    const char* str = g_strings[id][s_textLang];
    #ifdef __SWITCH__
    if (!str) str = g_strings[id][SetLanguage_ENUS];
    #else                              
    if (!str) str = g_strings[id][1];
    #endif
    return str;
}

u64 textGetLanguageCode(void) {
    return s_textLanguageCode;
}
