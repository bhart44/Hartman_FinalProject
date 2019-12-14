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

//struct for chords
typedef struct Notes {
	int third;
	int fifth;
	int seventh;
}Notes;

//create struct for different chord qualities
typedef struct Chord {
    Notes notes[3];
}Chord; //Semi-colon at the end

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
  int chord; //chord quality
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

      }
          // if(count < 1){
            //Major triad on
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 4), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEON, chan), (b + 7), 0x78)); 
            //hold out notes
            delay(1000);
            //Major triad off
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 4), 0x78));
            Pm_WriteShort(outputStream, 0, Pm_Message(SBYTE(MD_NOTEOFF, chan), (b + 7), 0x78));
            //count number of times through loop
            // count++;
            // }ç
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
