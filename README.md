# SecurityFoundation
Reverse-engineered header for Apple's password assistant API.

Simply include `SecurityFoundation/SFPasswordAssistant.h` in your
project and link to `SecurityFoundation.framework`.

`pwgen` is an example CLI application which generates passwords:

    usage: ./pwgen [options]

    Option:            Meaning:
      -c, --count        The number of passwords to generate.
      -a, --algorithm    One of {memorable, random, letters, alphanumeric, numbers}.
                         The default algorithm is `memorable'.
      -l, --length       The desired length of the generated passwords.
      -h, --help         Prints this message.
