/*
 * sf-pwgen.m -- OS X command line password generator
 * Copyright (c) 2014 Anders Bergh <anders1@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must
 *   not be misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>

#import <Foundation/Foundation.h>
#import "SFPasswordAssistant.h"

#define PROJECT "sf-pwgen"
#define VERSION "1.2"

#define PASS_MIN_LENGTH 8
#define PASS_MAX_LENGTH 31
#define PASS_DEFAULT_LENGTH 12
#define PASS_DEFAULT_COUNT 5

static void usage(const char *argv0) {
  // to get the available languages
  NSDictionary *policy =
      (NSDictionary *)CFBridgingRelease(SFPWAPolicyCopyDefault());
  NSArray *languages =
      [policy[@"Languages-Evaluate"] componentsSeparatedByString:@","];

  printf(PROJECT " " VERSION ": OS X password generator\n");
  printf("Anders Bergh <anders1@gmail.com>\n");

  printf("usage: %s [options]\n\n", argv0);
  printf("Available options are:\n");
  printf("  -a, --algorithm    Available algorithms: memorable, random, "
         "letters, alphanumeric, numbers.\n");
  printf("                     The default is `memorable'.\n");
  printf("  -c, --count        The number of passwords to generate "
         "(default: %d).\n",
         PASS_DEFAULT_COUNT);
  printf("  -l, --length       Desired length of the generated passwords "
         "(default: %d).\n",
         PASS_DEFAULT_LENGTH);
  printf("  -L, --language     Generate passwords in a specified language.\n");
  printf("                     Languages: %s.\n",
         [[languages componentsJoinedByString:@", "] UTF8String]);
  printf("                     Note that this feature is broken and will "
         "produce garbage, bug: rdar://14889281\n");
  printf("  -v, --version      Print the version number and exit.\n");
  printf("  -h, --help         Print this message.\n");
}

int main(int argc, char *argv[]) {
  // Default options
  int count = PASS_DEFAULT_COUNT;
  int length = PASS_DEFAULT_LENGTH;
  SFPWAAlgorithm algorithm = kSFPWAAlgorithmMemorable;
  NSString *language = @"en";

  const struct option longopts[] = {
    { "algorithm", optional_argument, NULL, 'a' },
    { "count", required_argument, NULL, 'c' },
    { "length", required_argument, NULL, 'l' },
    { "language", required_argument, NULL, 'L' },
    { "version", no_argument, NULL, 'v' },
    { "help", no_argument, NULL, 'h' },
    { NULL, 0, NULL, 0 }
  };

  char ch;
  while ((ch = getopt_long(argc, argv, "c:a:l:L:vh", longopts, NULL)) != -1) {
    switch (ch) {
      case 'v':
        printf(PROJECT " " VERSION "\n");
        exit(EXIT_SUCCESS);
        break;

      case 'a':
        if (strcmp(optarg, "memorable") == 0)
          algorithm = kSFPWAAlgorithmMemorable;

        else if (strcmp(optarg, "random") == 0)
          algorithm = kSFPWAAlgorithmRandom;

        else if (strcmp(optarg, "letters") == 0)
          algorithm = kSFPWAAlgorithmLetters;

        else if (strcmp(optarg, "alphanumeric") == 0)
          algorithm = kSFPWAAlgorithmAlphanumeric;

        else if (strcmp(optarg, "numbers") == 0)
          algorithm = kSFPWAAlgorithmNumbers;

        else {
          fprintf(stderr, "error: unknown algorithm.\n");
          usage(argv[0]);
          return EXIT_FAILURE;
        }
        break;

      case 'c':
        count = atoi(optarg);
        break;

      case 'l':
        length = atoi(optarg);
        break;

      case 'L':
        language = [NSString stringWithUTF8String:optarg];
        break;

      default:
        usage(argv[0]);
        return EXIT_FAILURE;
    }
  }

  if (count < 1)
    count = 1;

  if (length < PASS_MIN_LENGTH)
    length = PASS_MIN_LENGTH;

  else if (length > PASS_MAX_LENGTH)
    length = PASS_MAX_LENGTH;

  NSDictionary *policy =
      (NSDictionary *)CFBridgingRelease(SFPWAPolicyCopyDefault());
  assert(policy != NULL);

  SFPWAContextRef ctx = SFPWAContextCreateWithDefaults();
  assert(ctx != NULL);

  if (language) {
    NSArray *languages =
        [policy[@"Languages-Evaluate"] componentsSeparatedByString:@","];
    if ([languages containsObject:language]) {
      SFPWAContextLoadDictionaries(ctx, (__bridge CFArrayRef) @[ language ], 1);
    } else {
      fprintf(stderr,
              "warning: requested language `%s' unavailable, try one of: %s.\n",
              [language UTF8String],
              [[languages componentsJoinedByString:@", "] UTF8String]);
    }
  }

  NSMutableArray *suggestions = (__bridge NSMutableArray *)SFPWAPasswordSuggest(
      ctx, (__bridge CFDictionaryRef)policy, length, 0, count, algorithm);
  assert(suggestions != NULL);

  for (NSString *s in suggestions)
    printf("%s\n", [s UTF8String]);

  SFPWAContextRelease(ctx);

  return EXIT_SUCCESS;
}
