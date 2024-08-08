/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:51:18 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/07/07 14:43:50 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cube3d.h"

/**
 * Function: init_game
 * --------------------
 * Initializes various components of the game and sets up the game environment.
 * This function is responsible for preparing the game engine, loading textures, 
 * initializing player settings, setting up the FPS counter, initializing the minimap, 
 * and preparing the frame image.
 *
 * Parameters:
 *  - g: A pointer to the game structure that holds all game-related data.
 *
 * Process:
 *  - Initializes the graphics engine and creates the game window.
 *    - Calls `init_engine(g)` to set up the graphics library (e.g., MiniLibX) 
 *      and create a window. If initialization fails, it invokes `quit_and_free` 
 *      to handle errors and clean up resources.
 *  - Initializes the texture matrix for wall textures.
 *    - Calls `init_textures_mat(g)` to set up the matrix that holds pixel data 
 *      for the various wall textures used in the game.
 *  - Initializes player direction.
 *    - Calls `init_player_dir(g)` to configure the initial direction and orientation 
 *      of the player based on the starting direction (N, W, S, E) read from the map.
 *  - Initializes the FPS counter image.
 *    - Calls `init_fps_counter(g)` to set up the image used to display the frames 
 *      per second (FPS) counter on the screen.
 *  - Initializes the minimap.
 *    - Calls `init_minimap(g)` to set up the minimap display, including its size, 
 *      cell dimensions, and other relevant parameters.
 *  - Initializes the frame image pointer.
 *    - Calls `init_img_data(g, &g->frame, RES_X, RES_Y)` to allocate and initialize 
 *      the image data for the frame buffer with specified width (`RES_X`) and height (`RES_Y`).
 */
static void init_game(t_game *g)
{
	if (!init_engine(g))
		quit_and_free(MLX_ERR, 2, g);
	init_textures_mat(g);
	init_player_dir(g);
	init_fps_counter(g); 
	init_minimap(g);
	init_img_data(g, &g->frame, RES_X, RES_Y);
}

/**
 * Function: validator
 * --------------------
 * Validates the provided map file for the game by checking its extension, 
 * opening the file, extracting necessary information, and verifying the map's 
 * correctness. This function ensures that the map file is properly formatted 
 * and ready for use in the game.
 *
 * Parameters:
 *  - game_struct: A pointer to the game structure that holds all game-related data.
 *  - argv: An array of command-line arguments, where `argv[1]` is expected 
 *          to be the path to the map file.
 *
 * Process:
 *  - Checks the file extension of the map file to ensure it has the correct `.cub` 
 *    extension.
 *    - Calls `check_extension(argv[1], game_struct)` to validate the file extension.
 *      If the extension is incorrect, the function exits with an error.
 *  - Opens the map file for reading.
 *    - Uses `open(argv[1], O_RDONLY)` to get a file descriptor for the map file. 
 *      If the file cannot be opened, it closes the file descriptor (if it was opened) 
 *      and exits with an error.
 *  - Extracts and verifies the map data from the file.
 *    - Calls `extract_info(game_struct, map_fd)` to parse and extract necessary 
 *      information from the map file. If this fails, it exits with an error.
 *    - Calls `extract_map(game_struct, map_fd)` to read the actual map data. 
 *      If this fails, it exits with an error.
 *    - Calls `check_map(game_struct)` to validate the extracted map data for correctness. 
 *      If the map data is invalid, it exits with an error.
 *  - Closes the file descriptor after all operations are complete.
 */
static void	validator(t_game *game_struct, char **argv)
{
	int	map_fd;

	check_extension(argv[1], game_struct);
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
	{
		close(map_fd);
		quit_and_free(OPEN_ERR, 1, game_struct);
	}
	if (!extract_info(game_struct, map_fd))
		quit_and_free(DATA_ERR, 2, game_struct);
	if (!extract_map(game_struct, map_fd))
		quit_and_free(MAP_ERR, 2, game_struct);	
	if (!check_map(game_struct))
	{
		quit_and_free(MAP_ERR, 2, game_struct);
	}
	close(map_fd);
}

/**
 * Function: ft_cube
 * ------------------
 * This function is called repeatedly during the game loop to manage frame rendering, 
 * handle game logic, and update the frame rate display. It calculates the time 
 * elapsed since the last frame, updates movement and rendering parameters, 
 * and processes the rendering of each frame.
 *
 * Parameters:
 *  - g: A pointer to the game structure containing all necessary game data.
 *
 * Process:
 *  - Initializes the time tracking for frame rate if it's the first call.
 *    - If `frame_time_init_flag` is `0`, sets `last_frame_time` to `0` and updates 
 *      `frame_time_init_flag` to `1`.
 *  - Retrieves the current time in milliseconds.
 *    - Calls `get_time_in_milliseconds()` to get the current time.
 *    - Calculates the time difference (`frame_time`) since the last frame.
 *  - Checks if it is time to render a new frame based on the frame time.
 *    - Compares `frame_time` to `FPS_LIMIT` to determine if enough time has passed 
 *      for a new frame to be rendered.
 *  - If it is time to render:
 *    - Converts `frame_time` from milliseconds to seconds and updates `frametime_sec`.
 *    - Updates player movement speed and rotation speed based on the frame time and 
 *      predefined constants `MOVESPEED` and `ROTSPEED`.
 *    - Calls `handle_movement(g)` to process player input and update movement.
 *    - Calls `render(g)` to draw the current frame to the screen.
 *    - Calls `draw_fps_counter(g)` to display the current frame rate on the screen.
 *    - Updates `last_frame_time` to the current time for the next frame calculation.
 *
 * Return:
 *  - Returns `0` to indicate that the function has completed successfully.
 */
static int ft_cube (t_game *g)
{
	static unsigned long	last_frame_time;

	if (g->frame_time_init_flag == 0)
	{
		last_frame_time = 0;
		g->frame_time_init_flag = 1;
	}
	g->current_time = get_time_in_milliseconds();
	g->frame_time = g->current_time - last_frame_time;
	if (g->frame_time >= FPS_LIMIT)
	{
		g->frametime_sec = g->frame_time / 1000.0;
		g->player.move_speed = g->frametime_sec * MOVESPEED;
		g->player.rot_speed = g->frametime_sec * ROTSPEED;
		handle_movement(g);
		render(g);
		draw_fps_counter(g);
		last_frame_time = g->current_time;
	}
	return (0);
}

/**
 * Function: main
 * --------------
 * The entry point of the program. This function initializes the game structure, 
 * validates the map file, sets up the game environment, and starts the game loop.
 *
 * Parameters:
 *  - argc: The number of command-line arguments passed to the program.
 *  - argv: An array of strings representing the command-line arguments.
 *
 * Process:
 *  - Checks if exactly one command-line argument (the map file) is provided.
 *    - If not, calls `quit_and_free` with an error code `ARG_ERR` and exits.
 *  - Initializes the game structure using `init_game_struct()`.
 *    - This sets up the necessary data and configuration for the game.
 *  - Validates the map file using `validator()`:
 *    - Checks the file extension and contents to ensure it's a valid map file.
 *    - Passes the file descriptor to functions that extract information and map data.
 *  - Initializes the game environment using `init_game()`:
 *    - Sets up the graphical engine, textures, player data, minimap, and frame image.
 *  - Sets up input handling using `handle_input()`:
 *    - Prepares for processing user input to control the game.
 *  - Starts the game loop:
 *    - Uses `mlx_loop_hook()` to periodically call the `ft_cube` function to handle
 *      frame rendering and game logic.
 *  - Enters the main loop with `mlx_loop()`, which keeps the window open and 
 *    processes events until the window is closed.
 *
 * Return:
 *  - Returns `0` to indicate successful execution of the program.
 */
int	main(int argc, char **argv)
{
	t_game	game_struct;

	if (argc != 2)
		quit_and_free(ARG_ERR, 1, &game_struct);
	init_game_struct(&game_struct);
	validator(&game_struct, argv);
	init_game(&game_struct);
	handle_input(&game_struct);
	mlx_loop_hook(game_struct.mlx.mlx_ptr, ft_cube, &game_struct); 
    mlx_loop(game_struct.mlx.mlx_ptr);
}