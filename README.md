# SOMA Patcher

This patcher fixes game-breaking bugs which severely limit map complexity in HPL3. 

Without the patch, the game will crash shortly after loading saves on larger maps. This is due to an error in the texture streaming/allocation system, in which the engine overflows a 2048-slot ring buffer and returns a null/garbage ptr. 

The solution is to add a simple ring guard at a few callsites within the application. To do this, the patcher splices in a small amount of machine code at these sites, permanently modifying the executable until the game is reinstalled. 

This also resolves a throttling/streaming bug, which causes many textures to load in at low resolution (or sometimes not at all).

## Usage Instructions

Run `SomaPatcher.exe` in the root directory of your SOMA install. Make sure `Soma.exe` and `Soma_NoSteam.exe` are present.

Currently only supports Steam installs. Theoretically will work with the GOG version, but this is untested.

## Build

### Windows

Requires `Visual Studio 2017` or later.
  
- After cloning or downloading the repo, open the folder in Visual Studio.
  
- Run the build the usual VS way (`Ctrl + B`), or navigate to the `CMakeLists.txt` file within Visual Studio and save it.

### Linux

Requires `Ninja` (https://github.com/ninja-build/ninja) and `Python 3.9` or later.

- Run `build.py` from the console.
