# SecurityFoundation
Reverse-engineered header for Apple's password assistant API.

Simply include `SecurityFoundation/SFPasswordAssistant.h` in your
project and link to `SecurityFoundation.framework`.

`pwgen` is an example CLI application which generates passwords:

    usage: ./pwgen [options]
    
    Option:          Meaning:
      -c, --count      The number of passwords to generate.
      -a, --algorithm  Available algorithms: memorable, random
                       letters, alphanumeric, numbers.
                       The default is `memorable'.
      -l, --length     Desired length of the generated passwords.
      -h, --help       Prints this message.
