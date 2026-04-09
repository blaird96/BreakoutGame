# List of Possible Future Implementations 

---

This document is just a list of possible further additions to this project. Anyone can feel free to add anything that they would like to add in the future, or put it in the Discord and I'll put it in ASAP. Also if interested in implementing a certain feature, put your name in the respective **Who is interested in Implementing?** section, or put it in the Discord. 

---

## 01 - Audio and Music (SFX):

### Summary:
This involves adding both background music and different sound effects when certain events happen, including but not limited to:
- Music:
    - Could do different for menu(s) and during gameplay, or do same.
- Audio:
    - Ball colides with wall.
    - Ball colides with paddle.
    - Ball colides with brick.
        - Maybe different SFX for different bricks (**Feature 03**). 
    - Ball goes out-of-bounds (loss of life)
    - Winning the level/game.
    - Losing the level/game.
    - Clicking Buttons in the menu(s)

### References:
Official SFML tutorial for Audio and Music: **https://www.sfml-dev.org/tutorials/3.0/audio/sounds/**

### Who is interested in Implementing?

---

## 02 - Additional Levels:

### Summary:
Creating additional levels for more vareity in the game and more difficulty (assuming) as levels go on. Would likely involve reworking the brick spawning mechanisms.  

### Who is interested in Implementing?

### 02-1 - Level Select Menu:

#### Summary:
Will need an additional menu between what is the start menu now and the play screen for the player to select the level. Only needed if doing additional levels, but 100% needed if we do.   

#### Who is interested in Implementing?

---

## 03 - Additional Brick Types:

### Summary:
Creating different blocks that might do different things in the game area, such as exploding, indestrcutable etc. May spice the game up a little bit more. 

### Who is interested in Implementing?

---

## 04 - Storing high scores in Database to be Displayed:

### Summary:
Have a SQL Database that stores the high score of the user for each level thay have completed to be displayed in the level select menu/home page. Likley use a SQLite c++ implementation. 

### Who is interested in Implementing?
- Ethan 
