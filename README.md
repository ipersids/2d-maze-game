# hive-core-so-long
<div align="center">
	<picture>
		<img src="https://github.com/ayogun/42-project-badges/blob/main/badges/so_longm.png" alt="42 The 'So Long' school project with a bonus badge.">
	</picture>  

<p><a href="https://www.hive.fi/en/curriculum">Hive (42 School Network)</a></p>  

<h1> So Long</h1> 

<picture>
		<img src="textures/readme-gif/preview-game-win.gif" alt="Game demonstration (win screen)">
</picture>  

</div>

#### Introduction
So Long is a fun little 2D maze game where player need to collect all the coins and find the way out to win. No need to worry about creating a map with enemies; the game will automatically add them if there’s enough space, and it’ll still be totally playable. 

### Features  
1) **Main menu:** Player can choose your character (colored: green, red, or yellow):  
	* Use the arrow keys `←` | `→` or `A` | `D` to pick a color.  
	* Press `Enter` to start the game.  
2) **Win and lose screens.**  
3) **Enemies generated automatically:** The game adds enemies based on the map with this logic:  
	* 5% of the free spaces on the map can have enemies (this is for an "easy" difficulty level).  
	* The game will still make sure it's playable, so if it’s not, no enemies will be placed.  
	* Enemies are placed randomly on free cells using a pseudo-random number generator (`ft_rand()` from `libf`).   
	* Enemies won’t start moving until the player makes their first move, giving you some time to figure things out.  
4) **Animation support:** Enemies and collectibles have smooth animations, and everything runs at the same speed (FPS is based on speed and the number of frames in the animation).  
5) **Custom map support:**  
	* Map needs to be rectangular, surrounded by walls (`1`), and include exactly one player (`P`) and one exit (`E`), with at least one collectible (`C`).  
	* The rest of the map can have `0` as free spaces.  
	* The map file needs to have a `.ber` extension.  
	* The game will check the map and automatically generate the visuals if it’s valid.   
6) **Error handling:** If something goes wrong, a clear error message will be shown in `stdout`. There are a few types of errors:  
	* Custom errors if there’s something wrong with the map.  
	* Errors from the `MLX42` library if there's a problem on that side.  
	* System errors, like if there’s an issue with memory or reading the file.  

### Controls
| Key         | Action                      |
|-------------|-----------------------------|
| `W` or `↑`  | Move Up                     |
| `A` or `←`  | Move Left                   |
| `S` or `↓`  | Move Down                   |
| `D` or `→`  | Move Right                  |
| `ESC`       | Exit the Game               |
| `Enter`     | Start the game (main menu)  |

### Setup  
**1. Clone the Repository**  
To clone the repository along with its submodules `MLX42` and `libft`, run:
```bash
git clone --recurse-submodules https://github.com/ipersids/hive-core-so-long.git so-long
cd so-long
```
**2. Build the project:**  
```bash
make
```

Other commands:  
	* `make clean` will remove all .o' files from the directory.  
	* `make fclean` will remove all .o' and executable files.  
	* `make re` will trigger the fclean command and rebuild the program.   

**3. Run the game:**
To run the game with a map, use:
```bash
./so_long maps/map.ber
```
**4. Enjoy 😎**

______________
Made by **Julia Persidskaia**.  
[LinkedIn](https://www.linkedin.com/in/iuliia-persidskaia/)

<div align="center">... and Thanks for All the Fish. 🐟 

<picture>
		<img src="textures/readme-gif/preview-game-over.gif" alt="Game demonstration (win screen)">
</picture>  

</div>