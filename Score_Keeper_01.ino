// Use the MD_MAX72XX library to Print some text on the display
//
// Demonstrates the use of the library to print text.
//
// User can enter text on the serial monitor and this will display as a
// message on the display.

#include <MD_MAX72xx.h>
//#include <SPI.h>

//#define  PRINT(s, v) { Serial.print(F(s)); Serial.print(v); }

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define MAX_DEVICES 4

#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS
#define BUTTON_LEFT_PIN    4 // Data Pin for Left Button
#define BUTTON_RIGHT_PIN    2 // Data Pin for Right Button
long buttonTimerR = 0;
long longPressTimeR = 500;
boolean buttonActiveR = false;
boolean longPressActiveR = false;

long buttonTimerL = 0;
long longPressTimeL = 500;
boolean buttonActiveL = false;
boolean longPressActiveL = false;

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(CS_PIN, MAX_DEVICES);
// Arbitrary pins
//MD_MAX72XX mx = MD_MAX72XX(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Text parameters
#define CHAR_SPACING  1 // pixels between characters

// Global message buffers shared by Serial and Scrolling functions
#define BUF_SIZE  75
char message[BUF_SIZE] = {"   000"};
bool newMessageAvailable = true;
int currentScoreLeft = 0,
    currentScoreRight = 0;
int lastNumberPushup = 0;
bool resetBeforeFirstUse = true;
bool hasLeftDownState = true;
String howMuchSpace;

void printText(uint8_t modStart, uint8_t modEnd, char *pMsg) // *************** LED MATRIX PRINT FUNCTION ***************
// Print the text string to the LED matrix modules specified.
// Message area is padded with blank columns after printing.
{
  uint8_t   state = 0;
  uint8_t   curLen;
  uint16_t  showLen;
  uint8_t   cBuf[8];
  int16_t   col = ((modEnd + 1) * COL_SIZE) - 1;

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  do     // finite state machine to print the characters in the space available
  {
    switch(state)
    {
      case 0: // Load the next character from the font table
        // if we reached end of message, reset the message pointer
        if (*pMsg == '\0')
        {
          showLen = col - (modEnd * COL_SIZE);  // padding characters
          state = 2;
          break;
        }

        // retrieve the next character form the font file
        showLen = mx.getChar(*pMsg++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
        curLen = 0;
        state++;
        // !! deliberately fall through to next state to start displaying

      case 1: // display the next part of the character
        mx.setColumn(col--, cBuf[curLen++]);

        // done with font character, now display the space between chars
        if (curLen == showLen)
        {
          showLen = CHAR_SPACING;
          state = 2;
        }
        break;

      case 2: // initialize state for displaying empty columns
        curLen = 0;
        state++;
        // fall through

      case 3: // display inter-character spacing or end of message padding (blank columns)
        mx.setColumn(col--, 0);
        curLen++;
        if (curLen == showLen)
          state = 0;
        break;

      default:
        col = -1;   // this definitely ends the do loop
    }
  } while (col >= (modStart * COL_SIZE));

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void setup() // ********************* SETUP ********************
{
  mx.begin();
  // Code written for IR 06H, EN not used, so jumper should be plugged.
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_LEFT_PIN, INPUT);
  pinMode(BUTTON_RIGHT_PIN, INPUT);
  //Serial.begin(9600);  // Serial for debuggin, should be off on final to avoid delays
  Serial.begin(9600);
}



void loop() // ********************* LOOP ********************
{
  int buttonStateLeft = digitalRead(BUTTON_LEFT_PIN);
  int buttonStateRight = digitalRead(BUTTON_RIGHT_PIN);
  Serial.println(buttonStateRight);
  
  if (true == true) // LED Matrix Updater
  {
    String messageUpdater;


    // Space Manager
    if (currentScoreLeft <= 9 && currentScoreRight <= 9){
      howMuchSpace =  "       ";
    } else if (currentScoreLeft >= 10 && currentScoreRight <= 9){
      howMuchSpace =  "     ";
    } else if (currentScoreLeft <= 9 && currentScoreRight >= 10){
      howMuchSpace =  "     ";
    } else if (currentScoreLeft >= 10 && currentScoreRight >= 10){
      howMuchSpace =  "   ";
    } else {
      howMuchSpace =  "   ";
    }
    
    messageUpdater = String(currentScoreLeft) + howMuchSpace + String(currentScoreRight); // Creates space between numbers
    messageUpdater.toCharArray(message,10); // how many numbers to load
    printText(0, MAX_DEVICES-1, message); // update message using LED Matrix Function
    newMessageAvailable = false;
  }



  // RIGHT BUTTON CODE ******************************************************************
   if (buttonStateRight == HIGH) {
    if (buttonActiveR == false) {
      buttonActiveR = true;
      buttonTimerR = millis();
    }
    if ((millis() - buttonTimerR > longPressTimeR) && (longPressActiveR == false)) {
      longPressActiveR = true;
      currentScoreRight = 0;
      delay(300);
    }
  } else {
    if (buttonActiveR == true) {
      if (longPressActiveR == true) {
        longPressActiveR = false;
      } else {
        currentScoreRight = currentScoreRight + 1;
        delay(300);
      }
      buttonActiveR = false;
    }
  }


  // LEFT BUTTON CODE ******************************************************************
   if (buttonStateLeft == HIGH) {
    if (buttonActiveL == false) {
      buttonActiveL = true;
      buttonTimerL = millis();
    }
    if ((millis() - buttonTimerL > longPressTimeL) && (longPressActiveL == false)) {
      longPressActiveL = true;
      currentScoreLeft = 0;
      delay(300);
    }
  } else {
    if (buttonActiveL == true) {
      if (longPressActiveL == true) {
        longPressActiveL = false;
      } else {
        currentScoreLeft = currentScoreLeft + 1;
        delay(300);
      }
      buttonActiveL = false;
    }
  }
}
