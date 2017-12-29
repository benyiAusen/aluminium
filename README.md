# aluminium: Introduction

Internal SNES title string changer for Super Mario World ROMs

This little tool can change the default "SUPER MARIOWORLD" ROM string for a custom one. Ideal for finished hacks!
I wrote this little thing in C to see how could I use file manipulation in tools to change bytes in machine code for a platform such as a console, and because I was bored and had nothing to do. This repo includes a 64-bit Windows binary and the source code.

# aluminium: Usage

aluminium has two modes of operation. Via arguments and direct execution.

VIA ARGUMENTS:
aluminium rom.sfc -<option>
  -t <TITLE>: This option writes a custom 20-character title into the target ROM. Any characters after the 20th are ignored, and this is by design.
  -d: Displays part of the target ROM's information
  -r: Restores the target ROM's original game string. The original string is "SUPER MARIOWORLD\20h\20h\20h\20h\20h".
  
DIRECT EXECUTION:
1. Open up aluminium.
2. Input ROM filename.
3. Type the new title, or type a special command into the prompt.

"restore": Restores the target ROM's original game string. The original string is "SUPER MARIOWORLD\20h\20h\20h\20h\20h".
"exit": Quits without doing anything.


# aluminium: Build from Source
For Windows, MinGW64 is needed to use GNU make and GCC natively. For Linux, the base-devel package is required.
To build, just type "make" in a terminal.
