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
  - Rendering
