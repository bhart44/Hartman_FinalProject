# One-Note MIDI Chords

## Basic Information:

Written by Ben Hartman
12-14-2019

## Purpose

This program was written to allow a user to retreieve a single note input from a MIDI device and turn that note into a chord. The program includes every triad and seventh note chord quality possible, and allows the user to choose the quality of the chord using the command line interface. Once the user selects the desired type of chord, the program adds the corresponding intervals to the note played by the user on their MIDI device. The program then outputs the MIDI notes through the output device where they can then be recording using a digital audio workstation. 

This allows the user to produce chords of any quality in any key, which is especially useful for musicians who don't have piano playing skills, but would like to produce chord progressions in different keys.

## Algorithm

The program runs on a loop of 60 seconds which first searches for MIDI input and retrieves any input data if any. Once input data exists, the program stores the value of the MIDI note being played (0-127) as a variable. The program then asks for and stores user input for which type of chord to produce. Then the user's selection is run through a switch statement until the correct chord is reached. The output of the switch statement is the MIDI Note-on and Note-off messages that produce the notes, other than the root, of the selected chord. Once the chord has been produced, the switch statement exits and counts the number of times the switch statement has been run. Once the switch statement is run, it will not run again, assuring that MIDI messages don't keep outputing as an infinite loop. 

## How to Compile and Run

You must install PortMIDI from PortMedia in order to run this program 

Paste this Text in your command line to install PortMIDI:

**brew install portmidi**

To compile use:

**gcc MIDI.c -o MIDI -lportmidi**

To run use:

**./MIDI.c**

