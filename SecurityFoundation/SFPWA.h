// Link with SecurityFoundation.framework
#include <CoreFoundation/CoreFoundation.h>

typedef void *SFPWAContextRef;

typedef enum {
    SFPWAAlgorithmMemorable = 0, // Memorable
    SFPWAAlgorithmRandom = 1, // Random
    SFPWAAlgorithmLetters = 2, // FIPS-181 compliant
    SFPWAAlgorithmAlphanumeric = 3, // Letters & Numbers
    SFPWAAlgorithmNumbers = 4 // Numbers Only

    // These do nothing:
    // SFPWAAlgorithmUnknown = 5,
    // SFPWAAlgorithmManual = 6
} SFPWAAlgorithm;

SFPWAContextRef SFPWAContextCreate(void);
SFPWAContextRef SFPWAContextCreateWithDefaults(void);
CFDictionaryRef SFPWAPolicyCopyDefault(void);
CFMutableArrayRef SFPWAPasswordSuggest(SFPWAContextRef ctx, CFDictionaryRef policy, int length, int unknown, int count, SFPWAAlgorithm algorithm);
void SFPWAContextRelease(SFPWAContextRef ctx);
