# SO_LONG

My 6th project at 42 Network's Hive Helsinki 🐝

A 2D game using a minimal windowing/graphics library (MLX42)

> [!TIP]
> If you're at a 42 school and doing this project: It's genuinely so much better to ask fellow students instead of reading online solutions ✨

---

## Description

This project's about using the school's basic [MLX42](https://github.com/codam-coding-college/MLX42) windowing/graphics library to make a two-dimentional game where the player needs to pick up all the collectibles and reach the exit.

Mandatory parts include:
- Map validation
	- Map must be rectangular and surrounded by walls
	- There is only one player, only one exit, and at least one collectible
	- The player must be able to reach all collectibles and the exit
	- Handling maps of any size
- Write the current move count to the terminal
- Movement in 4 direction

Bonus parts include:
- Make the player lose when they touch an enemy
- Add some sprite animation
- Display the movement counter on screen

Extra features I added:
- Optional and skippable step-by-step visualization of the map validation in terminal
- Optional game-state history in terminal
- Enemies spawn after collectible pickups - enemies chase the player
- Gain attacks by picking up collectibles, and use those to defeat enemies (with on-screen attacks count)
- Homemade pixel art - it's not great, but it's mine ^^'

---

## Usage

> [!NOTE]
> Code was written and tested for Linux (using Hive's Ubuntu iMacs)

- Optionally, adjust settings at `include/settings.h`
- Compile by running `make` (or `make visualize` for visualized map validation and game-state history)
- Run `./so_long` with a map (e.g. the ones in the `maps` directory)

---

## Credits

- [Eve Keinan](https://github.com/EvAvKein)
