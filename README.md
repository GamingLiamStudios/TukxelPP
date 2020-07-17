# TukxelPP

## Summary
Tukxel++ is a port of Tukxel, a Voxel-Like Game Engine, to C++. Tukxel++ uses [Glitter](http://polytonic.github.io/Glitter/), a dead-simple boilerplate for OpenGL intended to make the development of OpenGL applications much easier.

Tukxel uses modules, coded in TBD, to add extra functionality.

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

If you compile and run, you should now be able to use Tukxel++
