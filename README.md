# Cub3d

This will be the last project developed in C. For that reason, the project will consist of a series of rigorous tests. A plan will also be created and all the code will be commented, in order to develop organizational and personal planning skills.

The project is to create a “realistic” 3D graphical representation of the inside of a maze from a first-person perspective using ray-cast principles.

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

The RayCast code:

    The code initializes various variables and loads necessary game sprites using the MLX library. It also sets up various hooks for keyboard and mouse input, and for updating the game state. Overall, it seems to be initializing the game engine and setting it up to be run.

Loop:

    Handling key and mouse events, and rendering the game using the mlx library. The update function is called by the game loop and updates the game time, checks for certain events, and renders the game. The keytest and keytestout functions handle key events and update variables based on the key pressed or released. The mouse function handles mouse events and updates the camera position based on mouse movement. The button_press function handles mouse button events and updates variables related to shooting.
