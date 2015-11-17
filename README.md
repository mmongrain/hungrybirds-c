# hungrybirds-c
An adversarial game for two in C.

## Dependencies & Compilation
hungrybirds-c requires GLib 2.0 (https://developer.gnome.org/glib/), which it uses for portable data structure implementations and memory management. It is available through all major Linux package repositories as `libglib2.0-dev`.

A simple Makefile (for use with GNU make) is included for convenience. `make` will compile the executable into a.o, which can then be run with `./a.o`.

## Command line options
option     | description
---------- | -----------
-b         | Starts a single-player game as Birds. Mutually exclusive with -l.
-l         | Starts a single-player game as Larva. Mutually exclusive with -b.
-d [depth] | Sets a depth (>= 1) for the minimax AI search. Default 3. Higher takes more time, yields better AI decisions. Requires -b or -l.
-v         | Verbose mode. Prints lots of stuff including AI decision tree.

If no command-line options are specified, the game defaults to non-verbose two-player game.

### Example syntax
If compiled with the default Makefile, the command `./a.o -d 3 -b -v` would start a single-player game as the birds with AI depth of 3 and verbose printing to the terminal.
