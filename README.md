# pacman-like

This is a QtCreator based 2D game, inspired by pacman-killer. Made as a part of my graphics course at college.

PS - I haven't played the original pacman. Gameplay may differ!

## GAMEPLAY

Initial background has a pond, and a trampoline.

Balls continuously fly over the ground, with/without slopes.

Player can jump once from the ground, and move sideways, either by increasing velocity in a direction or displacement.

Obstacles in form of porcupines and magnets appear timely in different directions.

All walls are reflective, with greater coefficient of restitution in vertical walls (left/right).

Air resistance and gravity are everpresent.

Player wobbles while in water with greater friciton without bouncing.

Player experiences boost at a ball, and 30% greater at trampoline.

Magnets cause constant acceleration in left/right direction.

Player loses health points on colliding with walls, or porcupines, based on speed or momentum of porcupine(s).

Player gains health on jumping over balls from up, based on their radii and rotation angles if any.

Game ends when health reaches 0.00.

Health bar is displayed in green/red color underground. Score and health are shown in title bar.

Thus, aim of the game is to maximize the score as much as possible in as much time as possible.

## CONTROLS

Game is grame controlled, with events happening at regular intervals.

A : Add displacement in left direction

W : Add displacement in right direction

SPACE : Jump

LEFT : Add velocity in left direction

RIGHT : Add velocity in right direction

DOWN : Stop velocity in horiontal (left/right) direction

ESC : Exit
