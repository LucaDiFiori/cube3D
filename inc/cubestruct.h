#ifndef CUBESTRUCT_H
# define CUBESTRUCT_H

#include "cubemacro.h"

enum e_wall_side
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3,
	DOOR = 4,
	DOOROPEN = 5
};

/**
 * Struct: s_img
 * --------------
 * Represents an image within the graphical engine. This structure holds 
 * information about the image data and its properties, used for rendering 
 * graphics in the game.
 * 
 * Members:
 *  - img: A generic pointer to the image object. This is used by the MLX library 
 *    to reference the image created or manipulated.
 *  - addr: A pointer to the image data array returned by `mlx_get_data_addr`. 
 *    This allows direct access to the pixel data of the image for manipulation.
 *  - bpp: The number of bits per pixel for the image. This defines the color depth 
 *    and is used to interpret the pixel data correctly.
 *  - line_length: The number of bytes in a single line of the image. This helps 
 *    in navigating through rows of pixel data when reading or writing to the image.
 *  - endian: Indicates the byte order (endianness) used in the image data. This 
 *    is important for correctly interpreting the pixel color values.
 *  - width: The width of the image in pixels.
 *  - height: The height of the image in pixels.
 */
typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

/**
 * Struct: s_minimap
 * ------------------
 * Represents the minimap in the game, including its background image and dimensions, 
 * as well as the size of cells and player indicator on the minimap.
 * 
 * Members:
 *  - img_bg: An instance of `t_img` representing the background image of the minimap. 
 *    It holds the image data and properties needed to render the minimap background.
 *  - minimap_width: The width of the minimap in pixels. This defines the overall size 
 *    of the minimap on the screen.
 *  - minimap_height: The height of the minimap in pixels. This defines the overall size 
 *    of the minimap on the screen.
 *  - cell_width: The width of each cell in the minimap grid, in pixels. This determines 
 *    the size of each grid cell representing a part of the game map.
 *  - cell_height: The height of each cell in the minimap grid, in pixels. This determines 
 *    the size of each grid cell representing a part of the game map.
 *  - player_radius: The radius of the player indicator on the minimap, in pixels. This 
 *    is used to visually represent the player's position and size on the minimap.
 */
typedef struct	s_minimap 
{
	t_img	img_bg;
	int		minimap_width;
	int		minimap_height;
	double	cell_width;
	double 	cell_height;
	double  player_radius;
}				t_minimap;

/**
 * Struct: s_asset
 * ---------------
 * Represents the player's assets and state in the game. This includes the player's
 * initial direction, position, movement vectors, input states, and movement parameters.
 * 
 * Members:
 *  - start_dir: The initial direction of the player character. This is represented 
 *    by a single character where:
 *    - 'N' stands for North
 *    - 'S' stands for South
 *    - 'E' stands for East
 *    - 'W' stands for West
 *  - x: The x-coordinate of the player's position in the game world.
 *  - y: The y-coordinate of the player's position in the game world.
 *  - dir_vec: A 2D array representing the direction vector of the player. The first 
 *    element (`dir_vec[0]`) represents the x-component, and the second element 
 *    (`dir_vec[1]`) represents the y-component of the direction.
 *  - keys: An array of integers used to track the state of keyboard keys. Each index 
 *    corresponds to a specific key, where the value indicates whether the key is pressed 
 *    (typically 1 for pressed and 0 for not pressed).
 *  - toggle_door_debounce: An integer used to debounce the door toggle action, preventing 
 *    multiple toggles from being registered in quick succession.
 *  - move_speed: The movement speed of the player character, calculated based on the 
 *    frame time. This determines how fast the player can move through the game world.
 *  - rot_speed: The rotation speed of the player character, calculated based on the 
 *    frame time. This controls how quickly the player can rotate or change direction.
 *  - plane_x: The x-component of the player's view plane. This helps define the field of 
 *    view and influences the direction in which the player can look.
 *  - plane_y: The y-component of the player's view plane. This complements `plane_x` 
 *    and helps define the 2D orientation of the player's view.
 */
typedef struct s_asset
{
	char	start_dir;
	double	x;
	double	y;
	double	dir_vec[2];
	int		keys[256];
	int		toggle_door_debounce;
	double	move_speed;
	double	rot_speed;
	double	plane_x;
	double	plane_y;
}	t_asset;

/**
 * Struct: s_rgb
 * -------------
 * Represents a color in the RGB color model. This struct is used to define colors 
 * by specifying the intensity of red, green, and blue components.
 * 
 * Members:
 *  - r: The red component of the color. An integer value typically in the range of 0 to 255.
 *  - g: The green component of the color. An integer value typically in the range of 0 to 255.
 *  - b: The blue component of the color. An integer value typically in the range of 0 to 255.
 */
typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

/**
 * Struct: s_wal_text
 * -------------------
 * Handles wall texture data and color settings for rendering.
 * This struct stores paths to texture files for different wall directions, ceiling and floor colors,
 * and variables required to map textures onto walls accurately.
 * 
 * Members:
 *  - north: File path to the texture for the north wall.
 *  - south: File path to the texture for the south wall.
 *  - east: File path to the texture for the east wall.
 *  - west: File path to the texture for the west wall.
 *  - c_rgb: RGB values for the ceiling color, represented by a `t_rgb` struct.
 *  - f_rgb: RGB values for the floor color, represented by a `t_rgb` struct.
 *  - wall_side: Index indicating the wall direction to select the appropriate texture.
 *  - wall_pixels: Matrix of pixel values for wall textures. 
 *  - column_x: Column index in the texture to sample for the current column of the game image.
 *  - column_y: Row index in the texture for the current pixel being accessed, derived from `current_tex_y`.
 *    This value is adjusted to fit within the texture boundaries using masking.
 *  - vertical_step: The amount by which the texture's vertical coordinate increases for each pixel 
 *    in the wall column, ensuring correct scaling of the texture to match the wall column height.
 *  - current_tex_y: Current vertical position in the texture from which to read the next pixel. 
 *    This floating-point value is incremented by `vertical_step` as rendering progresses to sample 
 *    the correct row in the texture.
 */
typedef struct	s_wal_text
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	t_rgb	c_rgb;
	t_rgb	f_rgb;
	int		wall_side;
	int		**wall_pixels;
	int		column_x;
	int		column_y;
	double	vertical_step;
	double	current_tex_y;
}	t_wal_text;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

/**
 * Struct: s_map
 * --------------
 * Represents the game map and associated texture and color information.
 * This struct contains data related to the map layout, textures for walls, and colors for ceiling and floor.
 * 
 * Members:
 *  - text: A `t_wal_text` struct containing paths to wall textures, ceiling and floor colors,
 *          and texture sampling data.
 *  - map_path: File path to the map definition.
 *  - map_mat: Matrix of characters representing the map layout, with each character corresponding
 *             to different map features (e.g., walls, doors).
 *  - map_x: Width of the map in terms of the number of columns.
 *  - map_y: Height of the map in terms of the number of rows.
 *  - c_color: Color of the ceiling, stored as an integer.
 *  - f_color: Color of the floor, stored as an integer.
 *  - num_players: Number of players or starting positions defined in the map.
 */
typedef struct	s_map
{
	t_wal_text	text;
	char		*map_path;
	char		**map_mat;
	int			map_x;
	int			map_y;
	int			c_color;
	int			f_color;
	int			num_players;
}	t_map;

/**
 * Struct: ray
 * -----------
 * Represents the data and calculations related to a single ray cast in the 3D rendering system.
 * This struct contains information used for determining how a ray interacts with the map and its elements,
 * including walls and doors.
 * 
 * Members:
 *  - camera_x: The x-coordinate of the ray in camera space, representing the position of the ray in the camera plane.
 *  - dir_x: The x-component of the ray's direction vector.
 *  - dir_y: The y-component of the ray's direction vector.
 * 
 *  - current_x: The current x-coordinate (column) of the map cell the ray is in.
 *  - current_y: The current y-coordinate (row) of the map cell the ray is in.
 * 
 *  - side_dist_x: The distance from the current position to the next vertical (x) grid line.
 *  - side_dist_y: The distance from the current position to the next horizontal (y) grid line.
 * 
 *  - delta_dist_x: The distance the ray travels to move from one vertical (x) grid line to the next.
 *  - delta_dist_y: The distance the ray travels to move from one horizontal (y) grid line to the next.
 * 
 *  - wall_distance: The perpendicular distance from the wall to the camera plane, used to determine the depth of the wall.
 * 
 *  - wall_x: The exact position (in decimal) where the ray intersects the wall. If the ray hits a vertical wall, this value
 *             represents the x-coordinate. If the ray hits a horizontal wall, this is effectively the y-coordinate.
 * 
 *  - step_x: The direction to step in the x-direction for the next grid line (either +1 for stepping right or -1 for left).
 *  - step_y: The direction to step in the y-direction for the next grid line (either +1 for stepping down or -1 for up).
 * 
 *  - side: Indicates which side of the wall was hit. 0 for vertical (NS) walls and 1 for horizontal (EW) walls.
 * 
 *  - line_height: The height of the line to draw on the screen, representing the height of the wall slice in pixels.
 *  - draw_start: The lowest pixel to fill in the current column on the screen.
 *  - draw_end: The highest pixel to fill in the current column on the screen.
 * 
 *  - hit_type: Type of object hit by the ray. 1 for wall, 2 for door, and 3 for an open door.
 */
typedef struct ray
{
	double	camera_x;
	double	dir_x; 
	double	dir_y;
	int		current_x;
	int		current_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
    double	delta_dist_y;
	double	wall_distance;
	double	wall_x;
	int		step_x;
    int		step_y; 
	int		side; 
	int		line_height; 
	int		draw_start; 
	int		draw_end; 
	int		hit_type;
}	t_ray;

/**
 * Struct: s_game
 * --------------
 * Represents the overall state of the game, including game settings, player data, rendering information, and timing.
 * 
 * Members:
 *  - map: Holds the map information, including textures and map layout.
 *    - `t_map` contains data such as the paths to texture files, colors for ceiling and floor, and the map matrix.
 * 
 *  - mlx: Contains the MinilibX library-related data.
 *    - `t_mlx` includes pointers to the MLX instance and the game window.
 * 
 *  - player: Stores information about the player, including position, direction, and movement.
 *    - `t_asset` includes the player's initial position, direction vector, movement speed, and other player-related data.
 * 
 *  - minimap: Holds information about the minimap display.
 *    - `t_minimap` includes the minimap image, dimensions, and player indicator.
 * 
 *  - frametime_sec: The time taken for the last frame to be rendered, measured in seconds.
 * 
 *  - ray: Contains information for raycasting, including ray direction, position, and distance to walls.
 *    - `t_ray` includes data for calculating ray intersections with walls and other objects in the game world.
 * 
 *  - screen_pixels: A 2D array representing the pixels of the game window. It stores the color values of each pixel.
 *    - This array is used to render the game scene and other visual elements.
 * 
 *  - frame: Image data for the current frame being rendered.
 *    - `t_img` includes the image pointer, pixel data, and image properties like width and height.
 * 
 *  - fps: Image data for the FPS counter displayed on the screen.
 *    - `t_img` includes the image pointer, pixel data, and image properties for the FPS counter.
 * 
 *  - mouse_pos: The current position of the mouse within the game window.
 * 
 *  - frame_time_init_flag: Flag to check if frame time initialization has been performed.
 * 
 *  - current_time: The current time in milliseconds, used for calculating frame time.
 * 
 *  - frame_time: The time elapsed since the last frame in milliseconds, used to manage frame rate.
 */
typedef struct s_game
{
	t_map			map;
	t_mlx			mlx;
	t_asset			player;
	t_minimap		minimap;
	double			frametime_sec;
	t_ray			ray;
	int				**screen_pixels;
	t_img			frame;
	t_img			fps;
	int				mouse_pos;
	int				frame_time_init_flag;
	unsigned long	current_time;
	unsigned long	frame_time;
}	t_game;


#endif