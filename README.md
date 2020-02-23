# One-Note MIDI Chords

## Basic Information:

Written by Ben Hartman

12-14-2019

## Purpose

This program was written to allow a user to retrieve a single note input from a MIDI device and turn that note into a chord. The program includes every triad and seventh note chord quality possible, and allows the user to choose the quality of the chord using the command line interface. Once the user selects the desired type of chord, the program adds the corresponding intervals to the note played by the user on their MIDI device. The program then outputs the MIDI notes through the output device where they can then be recording using a digital audio workstation. 

This allows the user to produce chords of any quality in any key, which is especially useful for musicians who don't have piano playing skills, but would like to produce chord progressions in different keys.

## Algorithm

The program runs on a loop of 60 seconds which first searches for MIDI input and retrieves any input data if any. Once input data exists, the program stores the value of the MIDI note being played (0-127) as a variable. The program then asks for and stores user input for which type of chord to produce. Then the user's selection is run through a switch statement until the correct chord is reached. The output of the switch statement is the MIDI Note-on and Note-off messages that produce the notes, other than the root, of the selected chord. Once the chord has been produced, the switch statement exits and counts the number of times the switch statement has been run. Once the switch statement is run, it will not run again, assuring that MIDI messages don't keep outputing as an infinite loop. 

## How to Compile and Run

### First Steps
You must download the PortMIDI C library from PortMedia, unless already downloaded in order to run this program. Here are the steps to do so:

If you haven't already, visit the website ***https://brew.sh*** and install Homebrew for your computer. Homebrew will allow you to download and place the PortMIDI library on your computer and use it to run this MIDI program.

Once Homebrew has been successfully installed, Paste this Text in your command line to install PortMIDI:

**brew install portmidi**

Homebrew will now take a few minutes to download the PortMIDI library and will let you know when it has finished. Once PortMIDI has been successfully installed, you will be able to continue with the following steps.

### Compile and Run 

1. Open up your IDE of choice and open the file midichords.c where you have downloaded it. You should keep the code for this program open for the next few steps.

2. You need to connect a MIDI device (MIDI keyboard controller) to your computer and make sure it appears in the "AudioMIDI Setup" application before midichords.c will properly function.

3. Next open your terminal and navigate to the folder containing midichords.c 

4. Compile the program by typing in to your command line interface:

*gcc midichords.c -o midichords -lportmidi*

You now have an executable file called "midichords" in the same folder as "midichords.c" and are able to run the program.

  5. To run the program, type in:

*./midichords.c*

### Syncing the MIDI Device and the Program

Look at the output from the program. Each printed device has a number 1-n on the left side. Determine which MIDI device you would like to use from the list printed out. Make note of the input and output of the device you would like to use because they are listed seperately. Go back to the program and change the number of kMIDIInputDevice and kMIDIOutputDevice at the top of the mdidichords.c file to match the two numbers of the devices on the list. Now go back and run step number 4 above one more time.

Now your MIDI device and midichords.c are in sync and using the same MIDI device. 

### Implement the Program

1. Run the code using step 5 above.

2. Select the type of chord you would like to play on your device.

3. Play one note 

4. Return to the command line interface and type in "^C" to end the program.
