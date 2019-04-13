# sf-pwgen
[![Build Status](https://travis-ci.org/anders/pwgen.svg?branch=master)](https://travis-ci.org/anders/pwgen)

`sf-pwgen` is a command line tool which generates passwords using the
SecurityFoundation framework in macOS. It runs on Mountain Lion and later.

    sf-pwgen 1.5: macOS password generator
    Anders Bergh <anders1@gmail.com>

    usage: ./sf-pwgen [options]

    Available options are:
      -a, --algorithm    Available algorithms: memorable, random, letters, alphanumeric, numbers.
                         The default is `memorable'.
      -c, --count        The number of passwords to generate (default: 5).
      -l, --length       Desired length of the generated passwords (default: 12).
      -L, --language     Generate passwords in a specified language.
                         Languages: en, de, es, fr, it, nl, pt, jp.
                         Note that this feature is broken and will produce garbage, bug: rdar://14889281
      -v, --version      Print the version number and exit.
      -h, --help         Print this message.


## SFPasswordAssistant.h
This project also includes SFPasswordAssistant.h, which is a
reverse-engineered header for Apple's password assistant API
(used in Keychain Access.app, etc). It should work on Snow Leopard
and above.

To use it simply include `SFPasswordAssistant.h` in your project
and link to `SecurityFoundation.framework`.
