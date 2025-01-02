# hive-core-so-long
The So Long project is a small 2D game that uses the MLX42 graphical library.

### Project plan

<details>
<summary>Active tasks</summary>    

- [ ] Check how to add sounds whit mlx42. 
- [ ] Testing
- [ ] Finalize documentation.

</details>

<details>
<summary>Done</summary>  

- [x] Program input validation:    
    * Takes exactly 2 parameters: `<program> <path>`.   
    * Map file has a `.ber` extension.    
    * Path to the file is valid. 
- [x] Map reading and general validation:  
	* Map is rectangular.
	* There is exactly one start position and one exit position.  
	* There is at least one collectible item.  
	* Map is surrounded by walls. 
	* Map fits the monitor size.
- [x] Check if the map is playable:  
	* There's a valid path between the start and exit.  
	* All collectibles are reachable. 
- [x] Display the game background in the window.  
	* Load sprites for walls, obstacles and empty spaces.  
- [x] Handle user input:
	* Implement movement in 4 directions: up, down, left, and right.  
	* Handle closing the window with ESC.
- [x] Handle player interaction with collectibles and counter:  
	* Detect the collectables and unset it on the map.  
	* Decrease amount of collectables to handle the exit from the game later.  
	* Print number of movements to stdout.
- [x] Implement sprite animation for collectibles. 
	* Load frames and set values to the structure.  
	* Updates the coin animation based on the elapsed time and FPS.  
- [x] Mid-project refactoring and cleaning:
	* Review and clean up header file.  
	* Restructure game object hierarchy, content and review macros.  
	* Optimize functions to reduce complexity, improve performance, and increase abstraction.   
	* Improve error handling.   
- [x] Display the movement count on-screen. 
- [x] Implement game states:  
	* Create layout for win and lose states.  
	* Add main menu.  
	* Allow player to choose a character at the start of the game.   
- [x] Implement enemies:  
	* Add enemies with movement patterns and interactions with the player.  
	* Add animation for enemy.
	* Detect collision with player.  
- [x] Implement a final game loop that handles rendering and events. 

</details>


______________
Made by **Julia Persidskaia**.  
[LinkedIn](https://www.linkedin.com/in/iuliia-persidskaia/)