# Tribute
[This is where you can find what this repo is tributing](https://github.com/tsoding/nothing)

## Changes

* Made cross-compiling easier by using CMake *(debatable)*.
* Still adhering to the GNUC header definitions.
    * Yet breaking tradition with the variable and function naming.

## Planned Features

* **Make my own code look like actual C code by making things consistent**
* Improve upon the comments in the code *(right now they're either vague or verbose)*
* Use GLU for the graphics
* Use OpenAL for the audio
* Use ZLib compression for game data *(graphics, audio, network packets)*
* Implement threaded optimizations *(good luck)*
* Implement rudimentary netcode *(again, good luck)*
* Add in-game MIDI audio editor
* Add in-game menu editor
* Add in-game sprite editor

## Implemented Features

* [PCG-64 Pseudorandom Number Generator](http://www.pcg-random.org/)
* HSLA and RGBA color functions.
* Linked SDL2 using CMake.

## Bug Submissions

I'll be adhering to the existing standard that [Tsoding](https://github.com/tsoding) uses for [Nothing](https://github.com/tsoding/nothing) with some minor alerations:
```
/* [Issue #123]: Title of issue.
** Simple explanation of said issue.
**  And indenting any lines that exceeds 80 columns (for those still using 80 column displays).
**  But only indenting once instead of nesting infinite indented lines.
*/
```

And for simple TODO's:
```
/* [TODO #123]: Title of TODO.
** Simple explanation of said TODO.
**  Ditto with the indenting that was previously explained.
*/
```