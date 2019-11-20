# Hartman Final Project
1. What will (likely) be the title of your project?

...Basic Wavetable Synthesizer

***

2. In just a sentence or two, summarize your project. (E.g., "A website that lets you buy and sell stocks.")

...I will incorperate PortAudio and PortMIDI to create a working wavetable synthesizer.

***

3. In a paragraph or more, detail your project. What will your software do? What features will it have? How will it be executed?

...My software will receive MIDI data from an input source and create notes based on three wavetables to output. The software will have three fixed wavetables to choose from upon loading the program; a sine wave, sawtooth wave, and square wave. Once the user chooses the waveform for the program, it will be set for the remainder of the program running. These waveforms will be stored as typedefs in a struct in the code. In real time, the program will receive MIDI input data from one MIDI channel. Of that one channel, the program will extract only the MIDI pitch from the incoming notes. The program will then use a function to determine the proper frequency for the input MIDI note and multiply the waveform by that frequency. The program will then use PortAudio to produce the sound and output it through the selected device.
  
 ***

4. In the world of software, most everything takes longer to implement than you expect. And so it's not uncommon to accomplish less in a fixed amount of time than you hope.
In a sentence (or list of features), define a GOOD outcome for your final project. I.e., what WILL you accomplish no matter what?

 A good outcome of the project would be a program that recieves MIDI input data and registers notes in real time. 

***

5. In a sentence (or list of features), define a BETTER outcome for your final project. I.e., what do you THINK you can accomplish before the final project's deadline?

A better outcome would be to end up with a project that recieves MIDI input data and registers notes in real time, as well as assigns the proper frequencies to each MIDI pitch.

***

6. In a sentence (or list of features), define a BEST outcome for your final project. I.e., what do you HOPE to accomplish before the final project's deadline?

The Best outcome of my final project would be a program that recieves MIDI input from a MIDI controller, and from start to finish assigns that MIDI note to a frequency and wavetable to produce notes on a keyboard in real time. 

***

7. In a paragraph or more, outline your next steps. What new skills will you need to acquire? What topics will you need to research?

I will need to spend a lot of time learning more about PortAudio and PortMIDI because I have limited experience with PortAudio and no experience at all with PortMIDI. I feel like with the knowledge I have about MIDI from EP-321, I will be able to implement the MIDI aspect of the project with some studying. I'm a little worried about using PortAudio so much for the project because I still don't understand as much as I would like to about the way digital audio functions. I will need to practice writing a program that processes data continuously in real time before I begin the final piece of code for the project because I know that's still a new process for me.
