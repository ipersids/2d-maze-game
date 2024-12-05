# hive-core-so-long
The So Long project is a small 2D game that uses the MLX42 graphical library.

### Project plan

<details>
<summary>Active tasks</summary>  

- [ ] Map reading and general validation:  
	* Map is rectangular.
	* There is exactly one start position and one exit position.  
	* There is at least one one collectible item.
	* Map is surrounded by walls.   
- [ ] Check if the map is playable:  
	* There's a valid path between the start and exit.  
	* All collectibles are reachable.

</details>

<details>
<summary>Backlog</summary>   

- [ ] Implement a basic game loop that handles rendering and events.  
- [ ] Load sprite images (player, walls, exit, collectibles).   
- [ ] Display game objects on the window.  
- [ ] Implement sprite animation.  
- [ ] Improve movement controls: collision detection.   
- [ ] Handle player interaction with collectibles and counter.  
- [ ] Implement the game conditions: win, lose, chose a character...   
- [ ] Implement enemies that move and interact with the player.  
- [ ] Display the movement count directly on screen.  

</details>

<details>
<summary>Done</summary>  

- [x] Program input validation:    
    * Takes exactly 2 parameters: `<program> <path>`.   
    * Map file has a `.ber` extension.    
    * Path to the file is valid.  
- [x] Handle user input:
	* Implement movement in 4 directions: up, down, left, and right.  
	* Handle closing the window with ESC.

</details>


______________
Made by **Julia Persidskaia**.  
[LinkedIn](https://www.linkedin.com/in/iuliia-persidskaia/)