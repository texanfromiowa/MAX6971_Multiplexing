/**************************************************************
  Name      MAX6971_nleds_1_0_0_14segment_multiplex                                
  Author    Bob Powell 
            texanfromiowa@gmail.com
            Copyright (C) 2012-2013, Parallelus Automation, Inc.
          
  Date      June 20, 2013    
  Modified  July 22, 2013                                
  Version   1.0.0      
  Arduino   1.0.5
  
  Notes     
            
            
Legal Stuff:
============

            This program is free software: you can redistribute it and/or modify
            it under the terms of the GNU General Public License as published by
            the Free Software Foundation, either version 3 of the License, or
            at your option, any later version.
	 
            This program is distributed in the hope that it will be useful,
            but WITHOUT ANY WARRANTY; without even the implied warranty of
            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
            GNU General Public License for more details.
	 
            You should have received a copy of the GNU General Public License
            along with this program.  If not, see <http://www.gnu.org/licenses/>.
          
   
   
     
Personal note:
==============

            If you do something interesting with this code, expand it, or just
            have a question, please email me at the address above.  

            I hope you find this example helpful.  Enjoy.

            Bob

****************************************************************/
// Switched to the Shifter library.  This allows for "n" number 
// shift registers to be used without significant changes to the 
// code.  For help in adding libraries to the Arduino IDE, go here:
// http://www.arduino.cc/en/Hacking/Libraries
// This library was obtained from: http://bildr.org/2011/08/74hc595-breakout-arduino/
// 
// The short version of installing a library it to, first, download the library
// (link above).  They usually download as a zip file, so unzip the file which 
// will usually create a directory of the libraries contents.  Third, put this 
// directory into the "libraries" directory of your Arduino IDE (Integrated
// Design Enviroment) software.  In a typical Windows installation, the Arduino
// IDE executable file is located at: c:\Program Files\Arduino\Arduino.exe
// There is a directory called:  c:\Program Files\Arduino\libraries
// The Shifter\ directory will go into this libraries directory.
// For a Mac, this directory is typically located at:
//   /Applications/Arduino.app/Contents/Resources/Java/libraries
// If you have trouble, see the link above for complete instruction from Arduino
// You will need to restart the Arduino IDE for it to realize that this 
// library is present.  Once you have installed the library and restarted the
// IDE, this line tells the compilier to include it:
#include <Shifter.h>
#include <TimerOne.h>

// THESE VARIABLES CHANGE.
// Set the number of leds your using and the number of shift registers used.
// The Shifter library assumes one register = 8 bits.  With this in mind,  
// NUM_LED can never be greater that NUM_REG x 8 bits.
const int NUM_LED = 15;      // number of leds
const int NUM_REG = 2;       // number of shift registers
const int NUM_DIGIT = 4;     // number of digits


// Set variables - Global variables, except for the Arduino
// pins, are CAPITALIZED.  This makes identification of local and 
// global variables easy to understand.  The compilier is case sensitive
// so it understands capitalized and lower case letters.

// These variables are too make things a little easier for humans to read.
// The "const" sets the variable so it cannot be changed
// later in the program (ie. make them constants).  The standard
// constants "true" and "false" function just as well as these.
const bool OFF = 0;
const bool ON = 1;



                                
const int latchPin = 13;
const int clockPin = 11;
const int dataPin = 12;
const int pwmPin = 10;

const int npn4 = 5;
const int npn3 = 4;
const int npn2 = 3;
const int npn1 = 2;
int DIR = MSBFIRST;
int DIGITS = OFF;
int TIMER, MSDELAY;





// Set up the shifter object used to send data to the registers.
Shifter shifter(dataPin, latchPin, clockPin, NUM_REG); 


// Set up the array of leds that is used throughout the program
bool LED[NUM_LED];    
const int NUM_DIGITS = 4;
bool DIGIT[NUM_DIGITS][NUM_LED];
int DIGIT_TRANSISTOR[] = {npn1, npn2, npn3, npn4};
//int DIGIT_TRANSISTOR[] = {npn4, npn3, npn2, npn1};



/*  Added constants for a 14 segment, common cathode single digit
    alphanumeric display.  In this example, a PDC54-11GWA was used.
    The datasheet can be found at: http://www.mouser.com/ds/2/216/PDC54-11GWA-57682.pdf
    
    The 2 shift register is connected as:
    
    Qa = Anode A
    Qb = Anode B
    Qc = Anode C
    Qd = Anode D
    Qe = Anode E
    Qf = Anode F
    Qg = Anode G
    Qh = Anode D.P. (decimal point)

    This quick example is for a single LED display with a single 74HC595.
    The same basic idea applies for multiple LED's and displays.

*/

  const int SEGA = 1;
  const int SEGB = 2;
  const int SEGC = 4;
  const int SEGD = 8;
  const int SEGE = 16;
  const int SEGF = 32;
  const int SEGG = 64;
  const int SEGH = 128;
  // no I
  const int SEGJ = 256;
  const int SEGK = 512;
  const int SEGL = 1024;
  const int SEGM = 2048;
  const int SEGN = 4096;
  // no O
  const int SEGP = 8192;
  const int SEGDP = 16384;
  
  const int NUM0 = SEGA + SEGB + SEGC + SEGD + SEGE + SEGF + SEGJ + SEGN;
  const int NUM1 = SEGB + SEGC;
  const int NUM2 = SEGA + SEGB +  + SEGD + SEGE + SEGK + SEGP;
  const int NUM3 = SEGA + SEGB + SEGC + SEGD + SEGK + SEGP;
  const int NUM4 = SEGB + SEGC + SEGF + SEGK + SEGP;
  const int NUM5 = SEGA + SEGC + SEGD + SEGF + SEGK + SEGP;
  const int NUM6 = SEGA + SEGC + SEGD + SEGE + SEGF + SEGK + SEGP;
  const int NUM7 = SEGA + SEGB + SEGC;
  const int NUM8 = SEGA + SEGB + SEGC + SEGD + SEGE + SEGF + SEGK + SEGP;
  const int NUM9 = SEGA + SEGB + SEGC + SEGD + SEGF + SEGK + SEGP;

  //const int LETA = SEGA + SEGB + SEGC + SEGD + SEGE + SEGF + SEGG + SEGH + SEGJ + SEGK + SEGL + SEGM + SEGN + SEGP;
  const int LETA = SEGA + SEGB + SEGC + SEGE + SEGF + SEGK + SEGP;
  const int LETB = SEGA + SEGB + SEGC + SEGD + SEGE + SEGF + SEGK;
  const int LETC = SEGA + SEGD + SEGE + SEGF;
  const int LETD = SEGA + SEGB + SEGC + SEGD + SEGH + SEGM;
  const int LETE = SEGA + SEGD + SEGE + SEGF + SEGP;
  const int LETF = SEGA + SEGE + SEGF + SEGP;
  const int LETG = SEGA + SEGC + SEGD + SEGE + SEGF + SEGK;
  const int LETH = SEGB + SEGC + SEGE + SEGF + SEGK + SEGP;
  const int LETI = SEGA + SEGD + SEGH + SEGM;
  const int LETJ = SEGB + SEGC + SEGD + SEGE;
  const int LETK = SEGE + SEGF + SEGJ + SEGL;
  const int LETL = SEGD + SEGE + SEGF ;
  const int LETM = SEGB + SEGC + SEGE + SEGF + SEGG + SEGJ ;
  const int LETN = SEGB + SEGC + SEGE + SEGF + SEGG + SEGL;
  const int LETO = SEGA + SEGB + SEGC + SEGD + SEGE + SEGF;
  const int LETP = SEGA + SEGB + SEGE + SEGF + SEGK + SEGP;
  const int LETQ = SEGA + SEGB + SEGC + SEGD + SEGE + SEGF + SEGL;
  const int LETR = SEGA + SEGB + SEGE + SEGF + SEGK + SEGL + SEGP;
  const int LETS = SEGA + SEGD + SEGG + SEGL;
  const int LETT = SEGA + SEGH + SEGM;
  const int LETU = SEGB + SEGC + SEGD + SEGE + SEGF;
  const int LETV = SEGE + SEGF + SEGJ + SEGN;
  const int LETW = SEGB + SEGC + SEGE + SEGF + SEGH + SEGL + SEGN;
  const int LETX = SEGG + SEGJ + SEGL + SEGN;
  const int LETY = SEGG + SEGJ + SEGM;
  const int LETZ = SEGA + SEGD + SEGJ + SEGN;
  const int SPACE = 0;
  const int APOS = SEGJ;
  const int COMMA = SEGN;
  const int PERIOD = SEGDP;
  
  int SEGMENTS[] = {SEGA, SEGB, SEGC, SEGD, SEGE, SEGF, SEGG, SEGH, SEGJ, SEGK, SEGL, SEGM, SEGN, SEGDP}; 
  int NUMBERS[] = {NUM0, NUM1, NUM2, NUM3, NUM4 , NUM5, NUM6, NUM7, NUM8, NUM9};
  int LETTERS[] = {LETA, LETB , LETC, LETD, LETE, LETF, LETG, LETH, LETI, LETJ, LETK, LETL, LETM, LETN, LETO, LETP, LETQ, LETR, LETS, LETT, LETU, LETV, LETW, LETX, LETY, LETZ, SPACE};
  
/**************************************************************
Function: setup
Purpose:  set up Arduino
Args:     none
Returns:  nothing
Notes:    This function is required by the Arduino
***************************************************************/
void setup() {

  // Set timer delay, in microseconds
  //  .1 sec or 100000 = 10Hz = 1/.1
  //  .01 sec or 10000 = 100Hz = 1/.01
  //  .004 sec or 4000 = 250Hz = 1/.004  
  //  .002 sec or 2000 = 500Hz = 1/.002
  //  Running the Timer1 faster that 250Hz is not recommended and could result in 
  //  code that does not function.
  TIMER = 4000;
  MSDELAY = 150;
  Timer1.initialize(TIMER); 
  Timer1.attachInterrupt( outBytes );
  
  //Serial.begin(115200);
  //Serial.println("Started");
  
  // Set up the output pins.  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT); 
  pinMode(npn1, OUTPUT); 
  pinMode(npn2, OUTPUT); 
  pinMode(npn3, OUTPUT); 
  pinMode(npn4, OUTPUT); 
  pinMode(pwmPin, OUTPUT);
  analogWrite(pwmPin, 0);
  
  digitalWrite(npn1, LOW);
  digitalWrite(npn2, LOW);
  digitalWrite(npn3, LOW);
  digitalWrite(npn4, LOW);
  
  // Set up the shifter output
  shifter.clear();
  shifter.write();
  
  // turn off all the LEDS, just in case
  allOff();
  writeBytes();

}  // End of Arduino Setup 



/**************************************************************
Function: loop
Purpose:  loop funtion for Arduino
Args:     none
Returns:  nothing
Notes:    This function is required by the Arduino, and the 
          Arduino will loop through this function indefinately.
***************************************************************/
void loop() {
  
/*****  See detailed descriptions for each funcion below  *****/
//  
//  Most of these functions follow the same basic principle.
//  A duration is selected for how long each led should be on,
//  a repeat count is selected, and how many leds are to be on
//  at once is selected.  

//  For example, flashAll(500, 3) tells the function to turn on
//  all leds for 1/2 a second, then off 1/2 a second.  The do this
//  3 times.
//  
//  Again:
/*****  See detailed descriptions for each funcion below  *****/
  
  // Set a standard delay between each effect
  int loopDelay = 2000;  
  
  // Flash all leds, to let us know its on
  flashAll(250, 3);
  delay(loopDelay);


//  multipexExamples();
//  allOff();
//  writeDigitBytes();
//  delay(2000);

  
 
  // 14 segment display tests
  fourteenSegmentTests();
  delay(loopDelay);



}  // End of Arduino Loop

void multipexExamples(){
  
  int demoTimes[] = {1,2,3,5,10,20,25,30,50,100};
  int demotimescount = 10;
  int cyclecount, loopdelay;
  int totalDelay = 2000;
  //char buf[256];
  
  for(int i = 0; i < demotimescount; i++){
      
    cyclecount = (demoTimes[i] * (totalDelay/1000));
    loopdelay = 333/demoTimes[i];
        
    for(int j = 0; j < cyclecount; j++){
           
      setDigitArray(0, NUMBERS[demoTimes[i]%10]);
      writeDigitBytes();
      sdelay(loopdelay);
      setDigitArray(0, SPACE);

      setDigitArray(1, NUMBERS[(demoTimes[i]/10)%10]);
      writeDigitBytes();
      sdelay(loopdelay);
      setDigitArray(1, SPACE);

      setDigitArray(2, NUMBERS[(demoTimes[i]/100)%10]);
      writeDigitBytes();
      sdelay(loopdelay);
      setDigitArray(2, SPACE);

    }     
  } 
}



void fourteenSegmentTests()
{
  int loopDelay = 2000;  
  int j = 0;

  allOff();

  //setDigitString(250, "Bob was here.");
  //sdelay(loopDelay);

  int segsequence[] = {SEGA, SEGB, SEGC, SEGD, SEGE, SEGF, SEGG, SEGH, SEGJ, SEGK, SEGL, SEGM, SEGN, SEGP, SEGDP};
  for(int i = 0; i <15;i++ ){
    setArray(segsequence[i]);
    writeBytes();
    sdelay(150);  
  }

 
  allOff();
  writeBytes();
  sdelay(loopDelay);
  
//==========================================================
   
  setDigitString(100, "As seen on Lets Make It -- www.letsmakeit.tv");
  sdelay(loopDelay);

  setDigitString(75, "abcdefghijklmnopqrstuvwxyz 1234567890 . -"); 
  sdelay(loopDelay);
  
    
//==========================================================

  int clockSequence[] = {SEGH, SEGJ, SEGK, SEGL, SEGM, SEGN, SEGP, SEGG};
     
  //  Digits are 3-2-1-0   
  // Cycle through loop once   
  for(int m = 0; m < 1; m++){
    // digit 3 - Commented out for this demo
    for(int l = 0; l < 8; l++){
      setDigitArray(3, clockSequence[l]);
  
      // Digit 2
      for(int k = 0; k < 8; k++){   

        setDigitArray(2, clockSequence[k]);

        // Digit 1
        for(int i = 0; i < 8; i++){
  
          setDigitArray(1, clockSequence[i]);
    
            // Digit 0
            for(int j = 0; j < 8; j++){
              setDigitArray(0, clockSequence[j]);
              writeDigitBytes();
              sdelay(2);
            }      
  
        } 
      }
    }
    // Set the end back to initial position
    setDigitArray(0, clockSequence[0]);
    setDigitArray(1, clockSequence[0]);
    setDigitArray(2, clockSequence[0]);
    setDigitArray(3, clockSequence[0]);
    writeDigitBytes();
  }

  sdelay(loopDelay/4);
  allOff(); 
  writeBytes();
  
  sdelay(loopDelay);

 
  


//==========================================================
// count up then down

  for(int i = 0; i <= 2000; i++){
    setNumber(i);
    sdelay(2);   
  }
  delay(loopDelay/2);
  
  allOff();
  writeBytes();
  //delay(loopDelay/2);
  for(int i = 99; i >= 0; i--){
    setNumber(i);
    sdelay(50);    
  }
  sdelay(500);
  allOff();
  writeBytes();
  sdelay(loopDelay);
  
}



/**************************************************************
Function: setNumber
Purpose:  Set a number into the display
Args:     int num - number to display 
Returns:  nothing
Notes:    Sets a number on the display.  THis is hard coded 
          for 4 digits and should be controlled by the
          NUM_DIGITS variable.
***************************************************************/
void setNumber(int num){
  
  allOff();
  setDigitArray(0, NUMBERS[num%10]);
  if(num >= 10)
     setDigitArray(1, NUMBERS[(num/10)%10]);
  if(num >= 100)
     setDigitArray(2, NUMBERS[(num/100)%10]);
  if(num >= 1000)
     setDigitArray(3, NUMBERS[(num/1000)%10]);
  writeDigitBytes();

}


/**************************************************************
Function: setDigitString
Purpose:  Send a string to the display
Args:     int duration - how long an led is on 
          char* buffer - string to display
Returns:  nothing
Notes:    I had to write this fast and hard coded it for
          4 digits.  This should be in a loop that is 
          controlled by NUM_DIGITS variable.  Sorry.
***************************************************************/
void setDigitString(int delayTime, char* buffer){
 
  int bufferLength = strlen(buffer);
  int i;
  
  for(i = 0; i < bufferLength; i++){
      
    setDigitArray(0, getLetterInt(buffer[i]));
    
    if(i == 0){
      setDigitArray(1, SPACE);
      setDigitArray(2, SPACE);
      setDigitArray(3, SPACE);
    }else if(i == 1){
      setDigitArray(1, getLetterInt(buffer[i-1]));
      setDigitArray(2, SPACE);
      setDigitArray(3, SPACE);
    } else if(i == 2){
      setDigitArray(1, getLetterInt(buffer[i-1]));
      setDigitArray(2, getLetterInt(buffer[i-2]));
      setDigitArray(3, SPACE);
    }  else {
      setDigitArray(1, getLetterInt(buffer[i-1]));
      setDigitArray(2, getLetterInt(buffer[i-2]));
      setDigitArray(3, getLetterInt(buffer[i-3]));
    } 
    writeDigitBytes();
    sdelay(delayTime);  
  }
 
    setDigitArray(0, SPACE);
    setDigitArray(1, getLetterInt(buffer[i-1]));
    setDigitArray(2, getLetterInt(buffer[i-2]));
    setDigitArray(3, getLetterInt(buffer[i-3]));
    writeDigitBytes();
    sdelay(delayTime);
    
    setDigitArray(0, SPACE);
    setDigitArray(1, SPACE);
    setDigitArray(2, getLetterInt(buffer[i-1]));
    setDigitArray(3, getLetterInt(buffer[i-2]));
    writeDigitBytes();
    sdelay(delayTime);
  
    setDigitArray(0, SPACE);
    setDigitArray(1, SPACE);
    setDigitArray(2, SPACE);
    setDigitArray(3, getLetterInt(buffer[i-1]));
    writeDigitBytes();
    sdelay(delayTime);
   
  allOff();
  writeBytes();
  sdelay(delayTime);

} 


/**************************************************************
Function: getLetterInt
Purpose:  Converts an alphanumeric string to a number code
Args:     int letter - letter to return 
Returns:  int of the characters value
Notes:    Not all alphanumeric characters are supported
***************************************************************/
int getLetterInt(int letter){
 
  switch (letter) {
    
    case '0':
      return NUM0;
    case '1':
      return NUM1;
    case '2':
      return NUM2;
    case '3':
      return NUM3;
    case '4':
      return NUM4;
    case '5':
      return NUM5;
    case '6':
      return NUM6;
    case '7':
      return NUM7;
    case '8':
      return NUM8;
    case '9':
      return NUM9;
    case 'A':
    case 'a':
      return LETA;
    case 'B':
    case 'b':
      return LETB;
    case 'C':
    case 'c':
      return LETC;
    case 'D':
    case 'd':
      return LETD;
    case 'E':
    case 'e':
      return LETE;
    case 'F':
    case 'f':
      return LETF;
    case 'G':
    case 'g':
      return LETG;
    case 'H':
    case 'h':
      return LETH;
    case 'I':
    case 'i':
      return LETI;
    case 'J':
    case 'j':
      return LETJ;
    case 'K':
    case 'k':
      return LETK;
    case 'L':
    case 'l':
      return LETL;
    case 'M':
    case 'm':
      return LETM;
    case 'N':
    case 'n':
      return LETN;
    case 'O':
    case 'o':
      return LETO;
    case 'P':
    case 'p':
      return LETP;
    case 'Q':
    case 'q':
      return LETQ;
    case 'R':
    case 'r':
      return LETR;
    case 'S':
    case 's':
      return LETS;
    case 'T':
    case 't':
      return LETT;
    case 'U':
    case 'u':
      return LETU;
    case 'V':
    case 'v':
      return LETV;
    case 'W':
    case 'w':
      return LETW;
    case 'X':
    case 'x':
      return LETX;
    case 'Y':
    case 'y':
      return LETY;
    case 'Z':
    case 'z':
      return LETZ;
    case '.':
      return SEGDP;
    case '-':
      return SEGK + SEGP;
    
    default:
      return SPACE;
   
  }
     
}


/**************************************************************
Function: flashAll
Purpose:  Flashes all leds
Args:     int duration - how long an led is on 
          int count - how many times to flash
Returns:  nothing
Notes:    
***************************************************************/
void flashAll(int duration, int count)
{
  for(int i = 0; i < count; i++){
    allOn();  
    writeBytes();  
    delay(duration);
    allOff();
    writeBytes();  
    delay(duration);
  }  
 
}  



/**************************************************************
Function: countUp
Purpose:  Count up, in binary, from one number to another
Args:     int duration - how long an led is on 
          int startNum - starting number
          int endNum - ending number
          bool reverse - true or false - a value of true
                       - reverses the normal direction
Returns:  nothing
Notes:    
**************************************************************/
void countUp(int startNum, int endNum, int duration, bool reverse)
{
 // Clear the array and turns off any leds still on 
 allOff(); 
 
 if((endNum <= startNum) || (endNum < 0))
    return;

  for (int numberToDisplay = startNum; numberToDisplay <= endNum; numberToDisplay++) {
  
    setArray(numberToDisplay);
    if(reverse == true){
      writeBytesRev();
    }
    else{
      writeBytes();
    }
    delay(duration);
  }
  
  allOff(); 
  writeBytes();

} 

/**************************************************************
Function: countDown
Purpose:  Count down, in binary, from one number to another
Args:     int duration - how long an led is on 
          int startNum - starting number
          int endNum - ending number
          bool reverse - true or false - a value of true
                       - reverses the normal direction
Returns:  nothing
Notes:    
**************************************************************/
void countDown(int startNum, int endNum, int duration, bool reverse)
{
 // Clear the array and turns off any leds still on 
 allOff(); 

 if(endNum >= startNum)
    return;
    
  for (int numberToDisplay = startNum; numberToDisplay > endNum; numberToDisplay--) {
    setArray(numberToDisplay);

    if(reverse == true)
      writeBytesRev();
    else
      writeBytes();
    
    delay(duration);
  }
  
  // turn off the last led
  allOff(); 
  writeBytes();
}  
 
 
 
/**************************************************************
Function: sumArray
Purpose:  Take a binary representation of the array of ON and OFF
          positions, and generates an integer.
Args:     int array[]
Returns:  integer of the total
Notes:    See comments on bit shifting at the beginning
          of this file.
**************************************************************/  
int sumArray(bool array[])
{
   int total = 0;
   
   for (int i = 0; i < NUM_LED; i++){
     if (array[i] == ON)
	 total = total + (1<<i);
   }
   
   return(total);
}

/**************************************************************
Function: setArray
Purpose:  Sets the primary array to the binary of the number
          given.
Args:     int num - number to put into array
Returns:  nothing
Notes:    See comments on bit shifting at the beginning
          of this file.  Since this is an integer, it must be
          between -32,768 and 32,767, HOWEVER, it should 
          always be a positive number (0 to 32,767).
**************************************************************/  
void setArray(int num)
{
  // Clear the array
  allOff();
  int i = -1;
  bool value;
  
  while (num > 0){
     value = num & 1;
     if(value == true)
       LED[i] = ON;
     else
       LED[i] = OFF;
       
     num >>= 1;
     i++;
   }  
}


void setDigitArray(int digit, int num)
{

  bool value;
   
   for(int i = 0; i < NUM_LED; i++){
    DIGIT[digit][i] = ON;
     value = num & 1;
     if(value == 1)
       DIGIT[digit][i] = ON;
     else
       DIGIT[digit][i] = OFF;
    num >>= 1;
  }  
}



/**************************************************************
Function: allOn
Purpose:  Turns ON all leds
Args:     none
Returns:  none
Notes:    
**************************************************************/  
void allOn()
{
   for (int i = 0; i < NUM_LED; i++)
   {
     LED[i] = ON;
   }
}

/**************************************************************
Function: allOff
Purpose:  Turns OFF all leds
Args:     none
Returns:  none
Notes:    
**************************************************************/  
void allOff()
{
   for (int i = 0; i < NUM_LED; i++)
   {
     LED[i] = OFF;
   }
   
   for(int i = 0; i < NUM_DIGITS; i++)
     for(int k = 0; k < NUM_LED; k++)
       DIGIT[i][k] = OFF; 
}

/**************************************************************
Function: sdelay
Purpose:  delay function that accounts for timer interupts
Args:     int msec - number of milliseconds of delay
Returns:  none
Notes:    This function was created because while testing,
          timer interupts were effecting the delays.
**************************************************************/
void sdelay(int msec)
{
  if(msec > 15){
    long time = millis();
    long delaytime = time + msec;
    long timenow = millis();

    while(timenow <= delaytime)
      timenow = millis();
  }
  else{
    msec = msec * 1000;  
    
    long time = micros();
    long delaytime = time + msec;
    long timenow = micros();

    while(timenow <= delaytime)
      timenow = micros();
  }
} 

/**************************************************************
Function: writeBits
Purpose:  Write the array with Most Significant Bit first (MSFBFIRST)
Args:     none
Returns:  nothing
Notes:    This function is a wrapper function for outBytes()
***************************************************************/
void writeBytes()
{
  DIR = MSBFIRST;
  DIGITS = OFF;
}
void writeBytesRev()
{
  DIR = MSBFIRST;
  DIGITS = OFF;
}
/**************************************************************
Function: writeDigitBytes
Purpose:  Write the array with Least Significant Bit first (MSFBFIRST)
Args:     none
Returns:  nothing
Notes:    This function is a wrapper function for outBytes()
***************************************************************/
void writeDigitBytes()
{
  DIR = MSBFIRST;
  DIGITS = ON;
}
void writeDigitBytesRev()
{
  DIR = MSBFIRST;
  DIGITS = ON;
}



/**************************************************************
Function: outBytes
Purpose:  Send array data to shift register
Args:     none
Returns:  nothing
Notes:    This is where data is actually sent out, but is not 
          intended to be used directly, but by the interupt. 
***************************************************************/
void outBytes()
{
   int dir = DIR;

  //  Set each digit one by one 
  if(DIGITS == ON){   
    
    for(int i = 0; i < NUM_DIGITS; i++){
      
      digitalWrite(latchPin, LOW);
      
      //digitalWrite(DIGIT_TRANSISTOR[i], HIGH);
    
      // most significant bit first
      if(dir == MSBFIRST){       
        for(int j = 0; j < NUM_LED;j++){
          if(DIGIT[i][j] == ON)
            shifter.setPin(j, HIGH);
          else
            shifter.setPin(j, LOW);
        } 
     }
      // least significant bit first - reverses what is in LED[]
      else if(dir == LSBFIRST){
        int k = 0;
        for(int j = NUM_LED - 1; j > -1;j--){
       
          if(DIGIT[i][j] == ON){
            shifter.setPin(k, HIGH);
          }  
          else{
            shifter.setPin(k, LOW);
          }        
          k++;  
        } 
     }   
   
     // Write the data to the registers
     shifter.write();
     // set the latch high to turn on the output
     digitalWrite(latchPin, HIGH);
     
     
     digitalWrite(DIGIT_TRANSISTOR[i], HIGH);
     delayMicroseconds(MSDELAY);
     digitalWrite(DIGIT_TRANSISTOR[i], LOW);
     }
   }  // end DIGIT == ON 

   //  All digits show the same data 
   else{  // DIGIT = OFF
     
      
     // most significant bit first
     if(dir == MSBFIRST){
       
       for(int i = 0; i < sizeof(LED);i++){
        if(LED[i] == ON)
          shifter.setPin(i, HIGH);
        else
          shifter.setPin(i, LOW);
       } 
     }
      // least significant bit first - reverses what is in LED[]
     else if(dir == LSBFIRST){
       int j = 0;
       for(int i = sizeof(LED) - 1; i > -1;i--){
         if(LED[i] == ON){
           shifter.setPin(j, HIGH);
         }  
         else{
           shifter.setPin(j, LOW);
         }        
         j++;  
       } 
     }   
   
     // Write the data to the registers
     shifter.write();
     // set the latch high to turn on the output
     digitalWrite(latchPin, HIGH);
   

     for(int i = 0; i < NUM_DIGITS; i++){
       digitalWrite(DIGIT_TRANSISTOR[i], HIGH);
       delayMicroseconds(MSDELAY);
       digitalWrite(DIGIT_TRANSISTOR[i], LOW);
     }  
 
     
   }
 
   
}

//  End of program
