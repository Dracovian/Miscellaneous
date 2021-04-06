# Simple Password Generator

This is a very simple password generator written in C that might have several
problems.

# Usage

```
    --charset <GROUP>
    --length <NUMBER>

Groups:
    U - Uppercase English Alphabet
    L - Lowercase English Alphabet
    N - Numbers 0 to 9
    S - Special English Characters

Example:
    --charset ULNS --length 30
    --charset LN --length 12
    --charset LUN --length 16
```

At the moment there's no mixing-and-matching arguments, maybe that'll be
something I'll implement in the future.

# You're relying on someone else's source code

That is true, this isn't the first repository I wrote that makes use of someone
else's code. My Base32 extension for PHP uses code from Matthew Garrett as you
can see here: https://github.com/Dracovian/php-base32/issues/1

Of course I'm not licensing this software nor will I be expecting to make money
off of this code. So I feel that there's really no issue with me using code from
someone else; especially if I've made heavy modifications to said code like in
the circumstance of my PCG code.

I do plan on making a better system of crediting authors of the code I re-use as
well as I plan on improving my knowledge of the C and C++ languages. It is all a
matter of time in the end.