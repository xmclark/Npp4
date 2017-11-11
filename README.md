# Npp4

A Perforce plugin for Notepad++.

## Current Features:

1. Load/Save Perforce connection configuration.
2. Add opened file to default changelist.
3. Revert opened file.
4. Checkout opened file in default changelist.

## Installation

Currently, the only method for installation is by building from source. The plugin will be added to the notepad++ plugin manager when it is prime time.

The project is only built in the Unicode configuration.

### Dependencies

Current dependencies are:

1. [nlohmann/json][]
2. [P4API][]

No work is required as all headers and binaries are currently checked into git. In the future, these dependencies should be collected by CMake (if anybody knows how to do this, please tell me). 

The P4API is on version 2016.2. It would be on a later version, but the Perforce people have a bug in their build system for the API causing certain stub libraries to not be copied to the output. 

### Install From Source

Building requires [cmake][] and [Microsoft Visual Studio][].

1. Open `cmake-gui` and select the Npp4 source directory. create a new directory `/build` adjacent to `/src` and set this as the build directoy. Click configure button and then click generate button. Select the Visual Studio 2015 generator or a later one. 

2. Click the Open Project button. Build the solution.

3. If the build succeeds, then the look in the `build\bin` directory for the dll. Copy this to a debugging notepad++ plugins directory or your installed notepad++ plugins directory. 

## Bugs and Feature Requests

Feel free to use the github tracker. Pull requests are welcome.

[nlohmann/json]: https://github.com/nlohmann/json
[P4API]: https://www.perforce.com/downloads/helix-core-c/c-api
[cmake]: https://www.cmake.org
[Microsoft Visual Studio]: https://www.visualstudio.com
