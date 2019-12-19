# Design Documentation

Before I describe how my code works, I need to state that a lot of the ideas and actual code that I used to build this program are based on examples from Akito van Troyer and out of "The Audio Programming Book" by Richard Lazzarini and Richard Boulanger. The program is just for me to understand PortMIDI better. 

I decided to design my program around taking realtime MIDI input and turning sing notes into chords instead of offline chord calculations using user root note input because of my limited ability to create a GUI. Playing notes on the piano and getting chords is a lot more fun than typing in the details of a chord and getting the result. That being said here is how my program works:

## Pre-Processors

The program requires the libraries stdio.h, stdbool.h, portmidi.h, porttime.h, math.h, and time.h to run, so those are all listed as #include at the top of the program. Then I defined a few macros at the top of the code to be used throughout the code. kMIDIInputDeviceID and kMIDIOutputDeviceID are just names for the MIDI device inputs and outputs and do not change throughout the code. Then kMaxMIDIEvents is set to 32 so that there are never more than 32 MIDI events happening at the same time. MD_NOTEON and MD_NOTEOFF are both set to the note-on and note-off messages according to the MIDI specifications. Then I used the definition of a Status Byte from "The Audio Programming Book" as SBYTE that includes the message and which channel it is on. 

## Functions

I only used one function outside of the main function in this program, although in hindsight I would have used more. This function is the delay function and is only used in between note-on and note-off messages in order to sustain the MIDI notes that are output as a result of the chord calculations.

## Main Function

The main function starts off by me declaring and/or defining all of the variables and pointers that I use throughout the code. 
