/*
 * Released into the public domain.
 *
 * Written by Anders Bergh <anders1@gmail.com> in 2013.
 */

#ifndef SFPASSWORDASSISTANT_H
#define SFPASSWORDASSISTANT_H

#include <CoreFoundation/CoreFoundation.h>

typedef struct SFPWAContext *SFPWAContextRef;

typedef enum {
  kSFPWAAlgorithmMemorable = 0,
  kSFPWAAlgorithmRandom = 1,
  kSFPWAAlgorithmLetters = 2, /* FIPS-181 compliant */
  kSFPWAAlgorithmAlphanumeric = 3,
  kSFPWAAlgorithmNumbers = 4
} SFPWAAlgorithm;

bool SFPWACStringInDictionary(SFPWAContextRef ctx, const char *string);
SFPWAContextRef SFPWAContextCreate(void);
SFPWAContextRef SFPWAContextCreateWithDefaults(void);
void SFPWAContextLoadDictionaries(SFPWAContextRef ctx, CFArrayRef langs,
                                  bool unknown);
void SFPWAContextRelease(SFPWAContextRef ctx);

/* Example:
 *
 * SFPWAPasswordEvaluator(ctx, CFSTR("password"), 0, policy) ->
 * {
 *   "Entropy": "123.4567",
 *   "Quality": 80,
 *   "Variety": 3,
 *   "Errors": [
 *     { "Value": "-27099", "Message": "Mix upper and lower case, punctuation,
 * and numbers" }
 *   ]
 * }
 */
CFDictionaryRef SFPWAPasswordEvaluator(SFPWAContextRef ctx,
                                       CFStringRef password, int unknown,
                                       CFDictionaryRef policy);

CFMutableArrayRef SFPWAPasswordSuggest(SFPWAContextRef ctx,
                                       CFDictionaryRef policy, int length,
                                       int unknown, int count,
                                       SFPWAAlgorithm algorithm);
CFDictionaryRef SFPWAPolicyCopyDefault(void);
CFPropertyListRef SFPWAPolicyCopyFromFile(const char *path);
CFArrayRef SFPWAPolicyLanguages(CFDictionaryRef policy);
void SFPWAPolicyParse(SFPWAContextRef ctx, CFDictionaryRef policy);
CFStringRef SFPWARandomWord(SFPWAContextRef ctx, unsigned int length);

#endif /* SFPASSWORDASSISTANT_H */
