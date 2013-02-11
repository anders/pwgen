Reverse-engineered header for Apple's password suggestion API.

To use it, simply include `SecurityFoundation/SFPasswordAssistant.h` in your
project and and link with `SecurityFoundation.framework`. There is an example
application called `pwgen` which can be used to generate passwords in a
terminal.

    usage: ./pwgen [options]

    Option:            Meaning:
      -c, --count        The number of passwords to generate.
      -a, --algorithm    One of {memorable, random, letters, alphanumeric, numbers}.
                         The default algorithm is `memorable'.
      -l, --length       The desired length of the generated passwords.
      -h, --help         Prints this message.

Everything in this repository is released into the public domain.
