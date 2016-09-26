Run Escape: a simple maze game developed in C++ with OpenGL and Open AL
=======================================================================

This project, in C ++ and OpenGL, is a born as a university project: is developed for Multimedial Sistems course of MSc of Computer Science at University of Padova.
It is a game based on a maze, in which the aim is to set off alarms in the maze, within a configurable time limit.

The *map* and the *alarms* are completely configurable by txt file, so you can have a new game each time!!


### Prerequisites

I suppose that you're using a Debian based distros and that you already have a C++ compiler installed. You can also run it on Windows OS.
To compile and run this game you have to install some different packages as:
- freeglut3​
- freeglut3­dev
- libghc­alut­dev ​
- libalut­dev

If you have Ubuntu based system, you can type this command in your console:
```bash
    sudo apt-get install freeglut3​ freeglut3­dev libghc­alut­dev ​libalut­dev
```
 
### How To Compile

To compile the game, enter into the project folder, and from you console type:
```bash
g++ main.cpp -o main.out -lGL -lGLU -lglut -lalut -lopenal

```

### How To Run
To run the game you only type:
```bash
./main.out
```

**If you want have the debug message type:**
```bash
./main.out debug
```

### How to play

To play the game you there are some simple commmand:

+ **W**: Go foward
+ **S**: Go backward
+ **A**: Turn left
+ **D**: Turn right
+ **ESC**: Exit the game
+ **SPACEBAR**: Disable the alarm

