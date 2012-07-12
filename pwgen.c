/*
 * pwgen.c -- Generates passwords using Apple's private API
 * Written by Anders Bergh <anders1@gmail.com> in 2012
 *
 * Public Domain
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#import <assert.h>

#include <CoreFoundation/CoreFoundation.h>

#include "SecurityFoundation/SFPWA.h"

static void usage(const char *argv0) {
	printf("Usage: %s OPTIONS...\n\n", argv0);
	printf("Option  Long option  Meaning\n");
	printf("-c      --count      The number of passwords to generate.\n");
	printf("-a      --algorithm  One of {memorable, random, letters, alphanumeric, numbers}.\n");
	printf("                     The default algorithm is `memorable'.\n");
	printf("-l      --length     The length of the generated passwords.\n");
	printf("-h      --help       Prints this message.\n");
	exit(1);
}

int main (int argc, char *argv[]) {
	void *buf = NULL;
	int ch, i, n;
	int count = -1, length = -1;
	int count_set = 0, length_set = 0;
	SFPWAAlgorithm algorithm = SFPWAAlgorithmMemorable;

	const struct option longopts[] = {
		{ "algorithm", optional_argument, NULL, 'a' },
		{ "count",     required_argument, NULL, 'c' },
		{ "length",    required_argument, NULL, 'l' },
		{ "help",      no_argument,       NULL, 'h' },
		{ NULL,        0,                 NULL, 0   }
	};

	while ((ch = getopt_long(argc, argv, "c:a:l:h", longopts, NULL)) != -1) {
		switch (ch) {
			case 'a':
				if (strcmp(optarg, "memorable") == 0)
					algorithm = SFPWAAlgorithmMemorable;
				else if (strcmp(optarg, "random") == 0)
					algorithm = SFPWAAlgorithmRandom;
				else if (strcmp(optarg, "letters") == 0)
					algorithm = SFPWAAlgorithmLetters;
				else if (strcmp(optarg, "alphanumeric") == 0)
					algorithm = SFPWAAlgorithmAlphanumeric;
				else if (strcmp(optarg, "numbers") == 0)
					algorithm = SFPWAAlgorithmNumbers;
				else {
					fprintf(stderr, "Error: unknown algorithm `%s'.\n\n", optarg);
					usage(argv[0]);
				}
				break;
			case 'c':
				count_set = 1;
				count = atoi(optarg);
				break;
			case 'l':
				length_set = 1;
				length = atoi(optarg);
				break;
			default:
				usage(argv[0]);
				return 1;
		}
	}

	if (!count_set || !length_set) {
		fprintf(stderr, "Error: count or length not specified.\n\n");
		usage(argv[0]);
		return 1;
	}

	if (count < 1) {
		fprintf(stderr, "Error: invalid count `%d' (should be at least 1).\n\n", count);
		usage(argv[0]);
		return 1;
	}
	
	if (length < 5) {
		fprintf(stderr, "Error: invalid length `%d' (should be at least 5).\n\n", length);
		usage(argv[0]);
		return 1;
	}

	SFPWAContext *ctx = SFPWAContextCreateWithDefaults();
	assert(ctx != NULL);
	
	CFDictionaryRef policy = SFPWAPolicyCopyDefault();
	assert(policy != NULL);
	
	CFMutableArrayRef suggestions = SFPWAPasswordSuggest(ctx, policy, length, 0, count, algorithm);
	assert(suggestions != NULL);
	
	for (i = 0; i < CFArrayGetCount(suggestions); i++) {
		CFStringRef s = CFArrayGetValueAtIndex(suggestions, i);
		assert(s != NULL);
		
		n = CFStringGetMaximumSizeForEncoding(CFStringGetLength(s), CFStringGetSystemEncoding()) + 1;
		buf = malloc(n);
		assert(buf != NULL);
		
		if (CFStringGetCString(s, buf, n, CFStringGetSystemEncoding()))
			printf("%s\n", buf);

		free(buf);
	}

	CFRelease(policy);
	CFRelease(suggestions);
	
	SFPWAContextRelease(ctx);
	
	return 0;
}