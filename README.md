# SecurityFoundation
Reverse-engineered header for Apple's password assistant API.

Simply include `SecurityFoundation/SFPasswordAssistant.h` in your
project and link to `SecurityFoundation.framework`.

`pwgen` is an example CLI application which generates passwords:

    usage: ./pwgen [options]

    Option:          Meaning:
      -a, --algorithm  Available algorithms: memorable, random
                       letters, alphanumeric, numbers.
      -c, --count      The number of passwords to generate.
                       The default is `memorable'.
      -l, --length     Desired length of the generated passwords.
      -L, --language   Generate passwords in a specified language (BUGGY).
                       Languages: en, de, es, fr, it, nl, pt, jp.
                       The default setting is English.
      -h, --help       Prints this message.
