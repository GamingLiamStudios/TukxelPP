# Tukxel++
Tukxel++ is a port of Tukxel, A Voxel-like Game Engine that focuses on customizability & speed, to C++. Tukxel++ uses a Stripped down version of [Glitter](http://polytonic.github.io/Glitter/), a dead-simple boilerplate for OpenGL intended to make the development of OpenGL applications much easier.

We also have a [Discord Server](https://discord.gg/vAcbPDD).

## Planned Features(as of 8th of August 2020):
### Cube
The engine primarily works with cubes but supports external models.
### Module API
This is the main feature of Tukxel, Modules. They can be coded in C#(using [DllExport](github.com/3F/DllExport)) or C++ & are very feature-rich.
They will be able to:
* Add and Replace Blocks & Entities
* Use custom Models and Textures
* Listen for & Execute at 'Game Events'
* Communicate with other Modules
* Specify other Server Protocols
* Developers Developers Developers
### Smaller Features
* Virtual Surround & Multi Speaker Configurations support
* Small & Easy to Share World Files
* Multiplayer
* Customizable Shaders

## Getting Started
Tukxel++ has a single dependency: [cmake](http://www.cmake.org/download/), which is used to generate platform-specific makefiles or project files. Start by cloning this repository, making sure to pass the `--recursive` flag to grab all the dependencies. If you forgot, then you can `git submodule update --init` instead.

```bash
git clone --recursive https://github.com/DEV0002/TukxelPP
cd TukxelPP
cd Build
```

Now generate a project file or makefile for your platform. If you want to use a particular IDE, make sure it is installed; don't forget to set the Start-Up Project in Visual Studio or the Target in Xcode.

```bash
# UNIX Makefile
cmake ..

# Mac OSX
cmake -G "Xcode" ..

# Microsoft Windows
cmake -G "Visual Studio 16" ..
cmake -G "Visual Studio 16 Win64" ..
...
```

First compile will take a longer than subsequent compiles.


