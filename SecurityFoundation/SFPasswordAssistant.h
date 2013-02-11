// Link with SecurityFoundation.framework
#include <CoreFoundation/CoreFoundation.h>

typedef struct SFPWAContext * SFPWAContextRef;

typedef enum {
    kSFPWAAlgorithmMemorable = 0, // Memorable
    kSFPWAAlgorithmRandom = 1, // Random
    kSFPWAAlgorithmLetters = 2, // FIPS-181 compliant
    kSFPWAAlgorithmAlphanumeric = 3, // Letters & Numbers
    kSFPWAAlgorithmNumbers = 4 // Numbers Only
} SFPWAAlgorithm;

bool SFPWACStringInDictionary(SFPWAContextRef ctx, const char *string);
SFPWAContextRef SFPWAContextCreate(void);
SFPWAContextRef SFPWAContextCreateWithDefaults(void);
void SFPWAContextLoadDictionaries(SFPWAContextRef ctx, CFArrayRef langs, bool unknown);
void SFPWAContextRelease(SFPWAContextRef ctx);
CFDictionaryRef SFPWAPasswordEvaluator(SFPWAContextRef ctx, CFStringRef password, int unknown, CFDictionaryRef policy);
/*
 * Example result:
 * {
 *     "Entropy": "136.9465151388981",
 *     "Quality": 80,
 *     "Variety": 3,
 *     "Errors": [
 *         {
 *             "Message": "Mix upper and lower case, punctuation, and numbers",
 *             "Value": "-27099"
 *         }
 *     ]
 * }
 */

CFMutableArrayRef SFPWAPasswordSuggest(SFPWAContextRef ctx, CFDictionaryRef policy, int length, int unknown, int count, SFPWAAlgorithm algorithm);
CFDictionaryRef SFPWAPolicyCopyDefault(void);
CFPropertyListRef SFPWAPolicyCopyFromFile(const char *path);
CFArrayRef SFPWAPolicyLanguages(CFDictionaryRef policy);
void SFPWAPolicyParse(SFPWAContextRef ctx, CFDictionaryRef policy);
CFStringRef SFPWARandomWord(SFPWAContextRef ctx, unsigned int length);
