# Design Documentation

Before I describe how my code works, I need to state that a lot of the ideas and actual code that I used to build this program are based on examples from Akito van Troyer and out of "The Audio Programming Book" by Richard Lazzarini and Richard Boulanger. The program is just for me to understand PortMIDI better. 

I decided to design my program around taking realtime MIDI input and turning sing notes into chords instead of offline chord calculations using user root note input because of my limited ability to create a GUI. Playing notes on the piano and getting chords is a lot more fun than typing in the details of a chord and getting the result. That being said here is how my program works:

## Pre-Processors

The program requires the libraries stdio.h, stdbool.h, portmidi.h, porttime.h, math.h, and time.h to run, so those are all listed as #include at the top of the program. Then I defined a few macros at the top of the code to be used throughout the code. kMIDIInputDeviceID and kMIDIOutputDeviceID are just names for the MIDI device inputs and outputs and do not change throughout the code. Then kMaxMIDIEvents is set to 32 so that there are never more than 32 MIDI events happening at the same time. MD_NOTEON and MD_NOTEOFF are both set to the note-on and note-off messages according to the MIDI specifications. Then I used the definition of a Status Byte from "The Audio Programming Book" as SBYTE that includes the message and which channel it is on. 

## Functions

I only used one function outside of the main function in this program, although in hindsight I would have used more. This function is the delay function and is only used in between note-on and note-off messages in order to sustain the MIDI notes that are output as a result of the chord calculations.

## Main Function

The main function starts off by me declaring and/or defining all of the variables and pointers that I use throughout the code. 
I have 3 variables to store PortMIDI errors, number of current MIDI devices, current MIDI device number, MIDI device info, number of MIDI events, and MIDI events themselves a the top. Then there are two pointers that are for the MIDI input and output streams, which are very important. I then declare PortTime errors as a variable as well as a bunch of number-holding variables of different forms for the PortTime timer, MIDI channel, MIDI note number, delay function timer, and user input chord. 

### User Input Chord Quality

Next, I used an enumeration to number a list of chords given their names. Then I used typedef to name that struct "quality."
This made it easier for me to keep track of which chords were being used in the switch statement holding chord data below. then I have a printf statement that lists the chord types and asks for the user to define which type of chord they would like to play 1-9. This is followed by a switch statement that records the number chosen and assigns it to the variable "inputhchord." Later on in the function, "inputchord" is recalled in a switch statement to calculate the correct MIDI output. 

### Opening PortTime and PortMIDI

Next there are a few clusters of code that begin the PortMedia Libraries which I used Akito's code for. prError is set to the Pt_Time function Pt_Start with some numbers inside it. This means that the timer has started. The next line says that if the previous line did not return ptNoError (which is a double negative) then to print out the specific error code according to PortTime and return 1. The same exact form is used to open PortMIDI input and output below, but Pm_OpenOutput and Pm_OpenInput must include their corresponding input and output stream pointers defined above, and the correct input and output devices must be used, which were defined already. 

### Streaming Loop

The next step in the code is a "while" loop that starts the Pt_Time timer at 0 and runs until it hits 60 seconds. Nested inside that loop is the PortMIDI function Pm_Poll in an "if" loop. If there is any MIDI input stream at all, the code will continue from here. Then the actual MIDI data is captured from the MIDI device and each message is stored in the PortMIDI defined variable PmEvent defined at the top as midiEvents. Just below that, for every MIDI event that is recorded, the status and two data bytes are printed out from the midiEvents struct followed by the timestamp that they were receieved. This step just lets the user know that the MIDI notes are being recorded by the program by printing out the MIDI data. Next, my very original code kicks into swing. I stored the MIDI note value (data byte 1 in a note-on message) of the current note as integer "b." Integer b comes in handy in the switch statement that comes next. 

