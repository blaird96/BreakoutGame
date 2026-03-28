# BreakoutGame
Breakout game in C++ as part of UMGC CMSC 495 Group 3 Capstone project.

## Setting up SFML:

- First, you will have to download both the MinGW compliler and the SFML library at this link: https://www.sfml-dev.org/download/sfml/3.0.2/.
- The one that should be downloaded is the '**32-Bit GCC 14.2.0 MinGW (DW2) (UCRT)**' and the corresponding 32-bit compiler.
- Using 32-bit over 64 because 32 can be used on both 64-bit and 32-but machines, whereas the 64-bit can only be used on 64-bit machines
- After downloading both zip files, extract both the zip file contants and place the root folders, 'mingw32' and 'SFML-3.0.2' into your C: drive.
- After moiving it, you need to add the path of the complier to your environment variables, which can be done following the steps below:
    - Copy the path to the compiler (should be just C:\mingw32)
    - In the in the start menu, look up 'Edit Environment variables for Your Account'
    - Once there, click on the row that corresponds to the 'Path' variable and then the 'Edit...' button
    - One in the subpage, click on the 'New' button and paste/put the root in the text area that shows up in the table.
    - After adding it, click 'OK' then 'OK' again to exit out of all of the windows.
    - To test to make sure it is downloaded, open the command prompt/terminal and type 'g++ --version' and it should show this as part of the message:
        - 'g++.exe (MinGW-W64 i686-ucrt-posix-dwarf, built by Brecht Sanders, r2) 14.2.0'
- This is built with Visual Studio Code as the intened IDE, it will have to be installed if it isn't.  

Here is a video for a basic walkthrough if you would prefer: https://www.youtube.com/watch?v=RHrU3I1EI. 
