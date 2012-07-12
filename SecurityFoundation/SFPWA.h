/* Link with SecurityFoundation.framework */
#include <CoreFoundation/CoreFoundation.h>

typedef struct SFPWAContext SFPWAContext;

typedef enum {
    SFPWAAlgorithmMemorable = 0,
    SFPWAAlgorithmRandom = 1,
    SFPWAAlgorithmLetters = 2,
    SFPWAAlgorithmAlphanumeric = 3,
    SFPWAAlgorithmNumbers = 4
    // These do nothing:
    // SFPWAAlgorithmUnknown = 5,
    // SFPWAAlgorithmManual = 6
} SFPWAAlgorithm;

SFPWAContext *SFPWAContextCreate(void);
SFPWAContext *SFPWAContextCreateWithDefaults(void);
CFDictionaryRef SFPWAPolicyCopyDefault(void);
CFMutableArrayRef SFPWAPasswordSuggest(SFPWAContext *ctx, CFDictionaryRef policy, int desiredLength, int unknown, int count, SFPWAAlgorithm algorithm);
void *SFPWAContextRelease(SFPWAContext *ctx);