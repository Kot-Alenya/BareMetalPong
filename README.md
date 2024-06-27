## Introduction
This is an experimental project aimed at diving into the world of low-level programming by creating a small game for "bare metal".<br>
The project is divided into two main parts: Modules and Game (they even have different coding styles).<br> 
The first part handles the hardware interaction, while the second part uses the first as a foundation for the game.<br>
If you decide to write something for bare metal, this project might be useful as it already contains many ready-made solutions, please check out the Modules part.<br>
I must warn you that the code is not documented, although I tried to write it clearly, I hope it won't cause you major problems!<br>
If you're interested in what the final result looks like, download download the release boot image from [here](https://github.com/potokaalex/BareMetalPong/releases), create a bootable USB drive, or use a virtual machine to boot it up.<br>
Upon startup, you will be greeted by an unfriendly black screen. Type the command help/? to get a list of available features.<br>
If you use my project for your own purposes, please include the license file somewhere.<br>

## Requirements
- Gnu make.
- Binutils x86.
- Gcc x86.
- Grub x86.
 
All of them are available [here](https://github.com/potokaalex/Binutils-Gcc-Grub-i386).
