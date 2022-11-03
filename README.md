# Cub3d

This will be the last project developed in C. For that reason, the project will consist of a series of rigorous tests. A plan will also be created and all the code will be commented, in order to develop organizational and personal planning skills.

The project is to create a “realistic” 3D graphical representation of the inside of a maze from a first-person perspective using ray-cast principles.

Example:

![Screenshot_2021-11-15-20-29-19-5](https://user-images.githubusercontent.com/60687885/199837502-e3f44670-a6b7-4471-bb87-541c326136ba.png)


My Goals

    Rigor, use of C, use of basic algorithms, information research, windows, colors, events, fill shapes, etc.

The first step:

Parsing:

The game will be loaded based on a file (.cub) where all the game information will be stored, such as the map, sprites (.xpm), ceilling and floor colors.

As expected, any unrecognized file type will be thrown an error, and the program should close automatically!
A function was developed for this, it will try to recognize the expected file type and if it was possible to open it.
Function: ft_file_check(path, ext.)


How my check map works:
There is a example how my check map works:

![check_map](https://user-images.githubusercontent.com/60687885/199610878-7ff79209-b54e-4617-99b2-9bc14d2142c6.gif)
