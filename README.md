# Tukxel++

Tukxel++ is a port of Tukxel, A Voxel-like Game Engine that focuses on customizability & speed, to C++.

We also have a [Discord Server](https://discord.gg/vAcbPDD).

## Planned Features(as of 8th of August 2020)

### Voxel

This engine works with voxels, which are mainly cubes, but can be replaced with external models.

### Module API

This is the main feature of Tukxel, They can be coded in C#(using [DllExport](github.com/3F/DllExport)) or C++ & are very feature-rich.
The some of the capabilities of Modules are:

* The ability to add custom/replace existing Blocks & Entities
* Use custom Models and Textures
* Listen for & Execute at 'Game Events'
* Communicate with other Modules
* Specify additional Protocols for inter-client communication
* Module Packs

### Smaller Features

* Virtual Surround & Multi Speaker Configurations support
* Small & Easy to Share World Files
* Multiplayer
* Customizable Shaders

## Getting Started

Tukxel++ has a single dependency: [cmake](http://www.cmake.org/download/), which is used to generate platform-specific makefiles or project files. Start by cloning this repository,

```bash
git clone https://github.com/DEV0002/TukxelPP
cd TukxelPP
cd build
```

Then generate a project file or makefile for your platform. If you want to use a particular IDE, make sure it is installed; don't forget to set the Start-Up Project in Visual Studio or the Target in Xcode.

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

If you compile and run, you should now have a upto date copy of Tukxel.  
Disclaimer: First compile will take a longer than subsequent compiles.
