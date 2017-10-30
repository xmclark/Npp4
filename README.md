# Npp4

A Perforce plugin for Notepad++.

## Installation

Currently, the only method for installation is by building from source. The plugin will be added to the notepad++ plugin manager when it is prime time.

### Install From Source

Building requires [cmake][] and [Microsoft Visual Studio][].

1. Open `cmake-gui` and select the Npp4 source directory. create a new directory `/build` adjacent to `/src` and set this as the build directoy. Click configure button and then click generate button. Select the Visual Studio 2015 generator or a later one. 

2. Click the Open Project button. Build the solution.

3. If the build succeeds, then the look in the `build\bin` directory for the dll. Copy this to a debugging notepad++ plugins directory or your installed notepad++ plugins directory. 

## Bugs and Feature Requests

Feel free to use the github tracker. Pull requests are welcome.