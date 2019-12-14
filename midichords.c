#include <stdio.h>
#include <stdbool.h>
#include <portmidi.h>
#include <porttime.h>
#include <math.h>
#include <time.h>

#define kMIDIInputDeviceID 0
#define kMIDIOutputDeviceID 3
#define kMaxMIDIEvents 32
#define MD_NOTEON 0x90
#define MD_NOTEOFF 0x80
#define SBYTE(mess,chan) mess | chan

void delay(int number_of_seconds);

//delay function
void delay(int number_of_seconds){
  int milli_seconds = 1000 * number_of_seconds;   //convert time into milliseconds
  clock_t start_time = clock(); //start time
  while(clock() < start_time + milli_seconds);//looping til require time is not met
}

//-----------------------------MAIN FUNCTION HERE--------------------------------//
int main(){
  PmError error; //Store error codes returned by PortMIDI functions
  int numDevices; //Store the number of MIDI device available
  PmDeviceID curDeviceID; //current device ID

  const PmDeviceInfo *pDeviceInfo; //Provides information and capabilities of PortMIDI devices
  int numMIDIEvents = 0; //Store a count for all incoming MIDI events
  PmEvent midiEvents[kMaxMIDIEvents]; //Hold individual MIDI events
  PortMidiStream *inputStream; //a descriptor for an open MIDI input device
  PortMidiStream *outputStream; //a descriptor for an open MIDI output device
  
  PtError ptError; //Store error codes returned by PortTime
  long msg, time; //Hold individual messages and store time
  char chan = 1; //which MIDI channel we are using 
  int b;//Integer to hold MIDI note value
  int count = 0; //int for timer
  int inputchord; //chord quality

  //list of chords 
  typedef enum quality {
    major = 1, minor, dim, aug, maj7, min7, dominant, halfdim7, dim7
  }quality;

  printf("Specify the type of chord (1-8) you would like to play:  \n");
  printf("1 = Major Triad\n2 = Minor Triad\n3 = Diminished Triad\n4 = Augmented Triad\n5 = Major Seventh\n6 = Minor Seventh\n7 = Dominant Chord\n8 = Half Diminished Seventh\n9 = Diminished Seventh\n");
  scanf("%d", &inputchord);

//-------------------------------------Initialize and Process Everything-------------------------//
  //Initialize Port MIDI
  error = Pm_Initialize();
  if(error != pmNoError){
    printf("Error: Pm_Initialize() failed with %s\n", Pm_GetErrorText(error));
    return 1;
  }

  //Get the number of port MIDI devices available
  numDevices = Pm_CountDevices();

  //Iterate over each device and print out information about them
  for(curDeviceID = 0; curDeviceID < numDevices; curDeviceID++){
    pDeviceInfo = Pm_GetDeviceInfo(curDeviceID);
    printf("--------------------------------------------\n");
    printf("ID: %d, Name: %s, ",curDeviceID,pDeviceInfo->name);
    printf("MIDI API: %s\n",pDeviceInfo->interf);
    printf("Max MIDI outputs: %d\t",pDeviceInfo->output);
    printf("Max MIDI inputs: %d\n\n",pDeviceInfo->input);
  }

  //start a timer
  ptError = Pt_Start(1, NULL, NULL);//yup
  if(ptError != ptNoError){
    printf("Error Code %d", ptError);
    return 1;
  }

  //open a MIDI input
  error = Pm_OpenInput(&inputStream, kMIDIInputDeviceID, NULL, 512L, NULL, NULL);
  if(ptError != ptNoError){
    printf("Error: Pt_Start Failed with error code %d\n", ptError);
    return 1; 
  }

  //open a MIDI output
  error = Pm_OpenOutput(&outputStream, kMIDIOutputDeviceID, NULL, 512L, NULL, NULL, 0);
  if(ptError != ptNoError){
    printf("Error: Pt_Start Failed with error code %d\n", ptError);
    return 1;
  }

  //run streamfor 10 Seconds
  while(Pt_Time(NULL)< 60000){
    //if there is any MIDI input stream
    if(Pm_Poll(inputStream)){
      //count the number of MIDI events into the variable numMIDIEvents
      numMIDIEvents = Pm_Read(inputStream, midiEvents, kMaxMIDIEvents);
      //until the max number of midi events is reached (32)
      for(int i=0; i < numMIDIEvents; i++){
        //print every MIDI event
        printf("status: 0x%.2x, byte1: %d, byte2: %d, time: %.3f\n",
        Pm_MessageStatus(midiEvents[i].message),//MIDI status
            Pm_MessageData1(midiEvents[i].message),//Note Number
            Pm_MessageData2(midiEvents[i].message),//Velocity
            (double) midiEvents[i].timestamp/1000.);
        
            //store MIDI note as variable b
            b = Pm_MessageData1(midiEvents[i].message);

            //if the chord has
            if(count < 1){
            switch(inputchord){

//----------------------------------------------triads-------------------------------------
           
            //major triad chord
            case major:
            //send note on messages to the third and fifth of the chord
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 4), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 7), 0x78)); 
            //hold out notes for one second
            delay(1000);
            //send note off messages to the same notes
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 4), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 7), 0x78));
            break;

            //minor triad chord
            case minor:
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 3), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 7), 0x78)); 
            delay(1000);
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 3), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 7), 0x78));
            break;

            //diminished triad chord
            case dim:
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 3), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 6), 0x78)); 
            delay(1000);
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 3), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 6), 0x78));
            break;

            //augmented triad chord
            case aug:
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 4), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 8), 0x78)); 
            delay(1000);
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 4), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 8), 0x78));
            break;

//---------------------------------------seventh chords----------------------------------------

            //major seventh chord
            case maj7:
            //send note on messages for the third, fifth, and seventh of the chord
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 4), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 7), 0x78)); 
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 11), 0x78)); 
            //hold out notes one second
            delay(1000);
            //send note off messages to the same notes
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 4), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 7), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 11), 0x78));
            break;

            //minor seventh chord
            case min7:
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 3), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 7), 0x78)); 
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 10), 0x78)); 
            delay(1000);
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 3), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 7), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 10), 0x78));
            break;
            
            //half diminished seventh chord
            case halfdim7:
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 3), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 6), 0x78)); 
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 10), 0x78)); 
            delay(1000);
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 3), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 6), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 10), 0x78));
            break;
            
            //dominant seventh chord
            case dominant:
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 4), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 7), 0x78)); 
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 10), 0x78)); 
            delay(1000);
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 4), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 7), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 10), 0x78));
            break;
            
            //diminished seventh chord
            case dim7:
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 4), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 7), 0x78)); 
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 10), 0x78)); 
            delay(1000);
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 4), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 7), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 10), 0x78));
            break;
            
            //if number is out of range
              default:
            printf("input does not exist\n");
            
          return 0;
            }

            count++;
          }
        }
    }
}

  //close MIDI input stream
  error = Pm_Close(inputStream);
  if(error != pmNoError){
    printf("Error: %s", Pm_GetErrorText(error));
    return 1; 
  }

  //close MIDI output stream
  error = Pm_Close(outputStream);
  if(error != pmNoError){
    printf("Error: %s", Pm_GetErrorText(error));
    return 1; 
  }

  //Terminate Port MIDI
  error = Pm_Terminate();
  if(error != pmNoError){
    printf("Error: Pm_Terminate() failed with %s\n",Pm_GetErrorText(error));
    return 1;
  }

  //Stop the timer
  ptError = Pt_Stop();//arguments are Resolution, callback function, and user data
  if(ptError != ptNoError){
    printf("Error: Pt_Stop() failed with error code %d\n",ptError);
    return 1;
  }
}
