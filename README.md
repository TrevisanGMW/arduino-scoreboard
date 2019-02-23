# arduino-scoreboard
A simple Arduino Scoreboard

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

This will make the number way take the same space as other numbers, keeping it always in the same place.
