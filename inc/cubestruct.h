#ifndef CUBESTRUCT_H
# define CUBESTRUCT_H

/************************************** */

typedef struct s_img_data
{
	void	*img; //puntatore generico per l'immagine.
	char	*addr; //puntatore ai dati dell'immagine restituite da mlx_get_data_addr
	int		bpp; //bit per pixel.
	int		line_length; //dimensione di una linea dell'immagine in byte.
	int		endian; //ordine dei byte (endianess).
}	t_img_data;

typedef struct	s_minimap 
{
	
	t_img_data	img_bg;
	int		minimap_width;
	int		minimap_height;
	//float	offset_x;
	//float	offset_y;

	int		view_size;
	float		cell_width;
	float		cell_height;

}				t_minimap;
/************************************** */




typedef struct s_asset
{
	char	dir;	// N, S, E, W
	float	x;
	float	y;
	float	rad_x;
	float   rad_y;
	float		speed;
	int		movement; //
}	t_asset;


typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct	s_wal_text
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	t_rgb	c_rgb;
	t_rgb	f_rgb;
}	t_wal_text;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

typedef struct	s_map
{
	char		*map_path;
	char		**map_mat;
	int			map_x;
	int			map_y;
	t_wal_text	wall_text;


}	t_map;

/*typedef struct s_key
{
	int w;
	int s;
	int d;
	int a;
} t_key;*/

typedef struct s_game
{
	t_map	map;
	t_mlx	mlx;
	t_asset player;

	/********************* */
	t_minimap minimap;
	//t_key	key;



}	t_game;


#endif