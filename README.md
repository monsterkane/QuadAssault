![Imgur](http://i.imgur.com/vDTZ6FK.png)
### Translation status: 17% completed (33/193) - [help](https://github.com/monsterkane/QuadAssault/blob/master/TODO)###

### About ###
A 2D C++ OpenGL game featuring normal mapping, deferred rendering and lots of lights. 

The game was developed by Marko Stanik as his [graduation project](http://staniks.blogspot.com/2012/06/releasing-graduation-project-source.html).

Aim of this project is to refactor and improve the original game.

### Dependencies ###
* [SFML 2.1](http://sfml-dev.org/download/sfml/2.1/)
* [GLEW](http://glew.sourceforge.net/)

### What has been done so far ###
* SFML 2.0-aplha dependency replaced by SFML 2.1 stable
* Added Linux support and cmake build system
* Translated source file names to English
* Improved source tree

### What's being worked on now ###
* Translating the source code and data files from Croatian to English
* Cleaning up the source code

### What will be worked on in the future ###
* Design a decent singleplayer campaign
* Multiplayer
* AI

### Compiling on Linux ###
#### Prerequisities ####
Create **lib/** folder and copy in **.so** files that come with **SFML/lib**
#### Building ####

```Bash
mkdir build && cd build
cmake ..
make
```

### Compiling on Windows (Visual Studio) ###
#### Prerequisities ####
* Create **bin/** folder and copy in **.dll** files that come with **SFML/bin** including **openal32.dll** and **libsndfile-1.dll**
* Copy **glew32.dll** to the **bin/** folder
* Create **lib/** folder and copy in **.lib** files that come with **SFML/lib**
* Copy **glew32.lib** to the **lib/** folder

#### Building ####
* Use **cmake-gui** to generate a Visual Studio Solution
* Set project's working directory in Visual Studio to **bin/**
* If you wish to compile in **debug** mode, make sure to link against **-d** version of SFML libraries

### Contribution ###
Contributing is much appreciated!

Simply fork the repository, commit changes and fire off a pull request.

### License ###
 GNU General Public License v3
