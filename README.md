# arduino-scoreboard
A simple Arduino Scoreboard


![Image of finished scoreboard](https://cdn.thingiverse.com/assets/79/06/77/86/94/20190216_191034.mp4_snapshot_00.25_%5B2019.02.23_12.01.08.png)


Single press : Adds a point
Long press: Resets it to zero


The printable 3d case for it:
https://www.thingiverse.com/thing:3448349

You'll need this library to make it work:
https://github.com/MajicDesigns/MD_MAX72XX

One other thing you have to do for this code to work is to change one line in 
"\Users\<UserName>\Documents\Arduino\libraries\MD_MAX72XX\src\MD_MAX72xx_font.cpp"


Replace this 
"3, 0x42, 0x7f, 0x40,  // 49 - '1'"

with

"5, 0x00, 0x42, 0x7f, 0x40, 0x00,	// 49 - '1'"

(No quotation marks)

This will make the number one take the same space as other numbers, keeping it always in the same place.

Want to make the same scoreboard?

What you will need:

-x1 Arduino Uno
-x1 MAX7219 Dot Matrix Module 4-in-1 Display For Arduino
-x1 Momentary SPST NO Red Round Cap Push Button Switch AC
and Resistors, wires, soldering iron, and a way to power up your arduino

![Image showing how to plug wires](https://cdn.thingiverse.com/assets/b0/35/76/8a/8d/HowTo.png)

