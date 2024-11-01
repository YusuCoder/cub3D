# 42Cursus Cub3D developed by [ryusupov](https://github.com/YusuCoder) and [tkubanyc](https://github.com/Tilek12)

<p align="center">
  <img src="textures/record.gif" alt="cub3d demo" width="600" height="auto">
</p>


### Project overview for Cub3D
![GitHub last commit](https://img.shields.io/github/last-commit/YusuCoder/cub3D)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/YusuCoder/cub3D)
![GitHub repo size](https://img.shields.io/github/repo-size/YusuCoder/minishell)
![GitHub language count](https://img.shields.io/github/languages/count/YusuCoder/cub3D)
![GitHub contributors](https://img.shields.io/github/contributors/YusuCoder/cub3D)
![GitHub top language](https://img.shields.io/github/languages/top/YusuCoder/cub3D)

# :speaking_head: About
> Welcome to cub3d, a journey into the world of raycasting, where 3D visuals come to life through fundamental computer graphics techniques. This project, created during my time at the prestigious 1337 School, dives deep into the intricacies of raycasting, enabling immersive environments with elegant simplicity. In cub3d, we explore the mechanics behind raycasting—a technique that projects rays from a virtual eye to map a 3D perspective onto a 2D screen.
  It’s the engine behind many early 3D games and remains relevant for understanding the basics of 3D rendering. This project builds a functional raycasting engine, transforming 2D map data into 3D spaces with walls, textures, and lighting effects, creating a compelling visual experience.

## Steps to implement

According to the constraints imposed by the subject, the parsing was carried out in the following way :

### 1. Parsing
   - Texture path
     - Extract path to textures
     - Check if the path is valid or not
     - Check if the paths are named with ```NO```, ```SO```, ```EA```, ```WE```
   - RGB color codes
     - Extract the color codes
     - Check if the floor if ```F``` and Ceiling is ```C```
     - Check if there are three color codes
     - Check if the codes are not more then ```255``` and not less than ```0```
   - Maap
     - Extract the map
     - Remove all the unnecessaary newlines
     - Check if the map is covered with walls from each side
     - Check if the map has only ```0```, ```1``` and ```(N, E, S, W)```
     - Check if the empty spaces inside the map (space or tabs) are closed with walls and they're not reachable

## Example of the valid map:

![Horizontal line check](https://github.com/YusuCoder/cub3D/blob/parse/textures/Horizontal%20line%20check.png?raw=true)


### 2. Graphical rendering:
  - Ray casting
    - Raycasting is a rendering technique used to create a 3D perspective of the game world. In this part, raycasting is implemented to calculate the angles of rays emanating from the player’s viewpoint. These rays are then cast onto the walls of the map, allowing the determination of the distance from the player to each wall. Based on these calculations, the engine determines the color of each wall to be rendered on the         screen. Raycasting creates the illusion of depth and adds a sense of realism to the game environment.
  - Rendering the walls:
    - In this part of the project deals with rendering the game world, including walls, floors, and ceilings, onto the screen. By utilizing the map layout, the player’s position and direction, and the raycasting results, the engine determines the appropriate colors for each pixel on the screen. This information is then used to render the walls, creating a 3D perspective. Additionally, floors and ceilings are rendered to         enhance the immersive experience. The rendering part gives life and visual representation to the game world.
  - Player Movement:
    - This part focuses on handling player movement and rotation within the game world. Keyboard input is used to control the player, allowing them to move forward, backward, and sideways. Additionally, the player can rotate left or right. The code monitors keyboard events and updates the player’s position and direction accordingly. This part enables the player to navigate and explore the game world.

![Horizontal line check](https://github.com/YusuCoder/cub3D/blob/parse/textures/renderuing.png?raw=true)

## Installation

1. Clone the repository
```
  git clone https://github.com/YusuCoder/cub3D.git
```

2. Open the repository and run this command:
```
  make
```

### OR
```
  make bonus
```

## Controls:

```1```, ```2```, ```3``` for changing the weapons<br>
```M``` to hide or show the minimap<br>
```W,A,S,D``` to move the player<br>
```T``` to set the timer<br>


## Useful links:

- https://lodev.org/cgtutor/raycasting.html
- https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)
- https://guy-grave.developpez.com/tutoriels/jeux/doom-wolfenstein-raycasting/
- https://github.com/vinibiavatti1/RayCastingTutorial/wiki
- https://github.com/qst0/ft_libgfx
