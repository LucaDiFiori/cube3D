#ifndef CUBESTRUCT_H
# define CUBESTRUCT_H

#include "cubemacro.h"

/************************************** */

enum e_wall_side
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3,
	DOOR = 4,
	DOOROPEN = 5
};

typedef struct s_img
{
	void	*img; //puntatore generico per l'immagine.
	int		*addr; //puntatore ai dati dell'immagine restituite da mlx_get_data_addr
	int		bpp; //bit per pixel.
	int		line_length; //dimensione di una linea dell'immagine in byte.
	int		endian; //ordine dei byte (endianess).
	int		width;
	int		height;
}	t_img;

typedef struct	s_minimap 
{
	t_img	img_bg;
	int		minimap_width;
	int		minimap_height;
	double	cell_width;
	double 	cell_height;
}				t_minimap;
/************************************** */


typedef struct s_mov
{
	bool up;
	bool down;
	bool left;
	bool right;
} t_mov;

typedef struct s_asset
{
	/*direzione iniziale personaggio*/
	char	start_dir;	// N, S, E, W
	
	/*posizioni personaggio */
	double	x;
	double	y;

	/*vettore direzione personaggio*/
	double	dir_vec[2];

	/*tasto premuto per il movimento*/
	int keys[256];
	int toggle_door_debounce;

	//velocità di movimento e rotazione calcolate in base al frametime
	double move_speed;
	double rot_speed;

	// piano del campo visivo
	double plane_x;
	double plane_y;

}	t_asset;


typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct	s_wal_text
{
	/*percorsi delle texture dei vari muri*/
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	/*colori muro e soffitto*/
	t_rgb	c_rgb;
	t_rgb	f_rgb;
	
	/*indice della direzione del muro per disegnare la texture corrispondente*/
	int		wall_side;
	
	/*matrice/hashmap che conterrà i valori interi dei singoli pixel per ogni texture dei muri
	  [5] = numero delle texture dei muri + 1
	  [1] = un puntatore ad un array di pixel 64*64*/
	int		**wall_pixels;

	/* indica quale colonna di pixel della texture deve essere campionata per essere 
	   disegnata nella colonna corrente dell'immagine di gioco.*/
	int column_x;

	/*variabile che indicherà il pixel nella colonna (tex_colum) della texture 
	Funzione: column_y rappresenta la coordinata della riga nella texture a cui 
	          si sta accedendo in un formato intero.
    Utilizzo: Questa variabile è calcolata a partire da current_tex_y e usata 
	          per accedere ai dati di colore dalla texture. È il valore intero 
			  ottenuto dalla parte frazionaria di current_tex_y, usando 
			  un'operazione di mascheramento (& (tex->size - 1)) per assicurarsi 
			  che sia compreso nei limiti della texture.*/
	int column_y;

	/*
	 rappresenta la quantità di incremento verticale nella texture per ogni 
	 incremento di un pixel nella colonna della schermata durante il rendering 
	 della colonna stessa. 
	 In altre parole, è la frazione di altezza della texture che corrisponde 
	 a un singolo pixel sullo schermo.
	Rappresenta una sorta di proporzione o rapporto tra 
	l'altezza della texture e l'altezza della colonna della parete sullo schermo. 
	Questo rapporto assicura che la texture venga correttamente scalata e mappata 
	sui pixel della colonna della parete in modo proporzionale.*/
	double vertical_step;

	/*posizione corrente all'interno della texture, lungo l'asse verticale, da cui leggere il prossimo pixel
	  Funzione: current_tex_y rappresenta la posizione corrente nella texture lungo 
	            l'asse Y, ma non è un valore intero; è una variabile a virgola 
				mobile (float o double).
      Utilizzo: Questa variabile viene usata per calcolare in modo continuo la 
	            riga di texel della texture da campionare mentre il rendering procede. 
				È incrementata in base a tex->vertical_step per scorrere attraverso le 
				righe della texture. */
	double current_tex_y;
}	t_wal_text;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

typedef struct	s_map
{
	t_wal_text	text;
	char		*map_path;
	char		**map_mat;
	int			map_x;
	int			map_y;
	int			exit_x;
	int			exit_y;

	//colori del soffitto e del muro in formato intero
	int			c_color;
	int			f_color;


}	t_map;


typedef struct ray
{
	//camera plane
	double  camera_x;
	//direction of the ray
	double	dir_x; 
	double	dir_y;

	//which box of the map we're in
	int current_x; //mapX
	int current_y; //mapY

	//length of ray from current position to next x or y-side
	double side_dist_x;
	double side_dist_y;

	//length of ray from one x or y-side to next x or y-side
	// (distance that the ray has to travel to go from 1 x-side to the next x-side, 
	//  or from 1 y-side to the next y-side)
	double delta_dist_x;
    double delta_dist_y;
 
	//distance projected on camera direction
	double wall_distance; //distanza perpendicolare dal muro al piano della telecamera

	//posizione esatta del punto di intersezione tra il raggio e il muro colpito.
	//the exact value where the wall was hit (decimal value)
	// Note that even if it's called wallX, it's actually an y-coordinate of the wall if side==1
	double	wall_x;

	//what direction to step in x or y-direction (either +1 or -1)
	int step_x;
    int step_y; 

	//was a NS or a EW wall hit?
	int side; 
    
	//height of line to draw on screen
	int		line_height; 
	//lowest and highest pixel to fill in current stripe
	int		draw_start; 
	int		draw_end; 

	int hit_type; // 1 = muro, 2 = porta 3 = porta aperta


}	t_ray;




typedef struct s_game
{
	t_map	map;
	t_mlx	mlx;
	t_asset player;
	t_minimap minimap;
	//t_key	key;
	double time; //time of current frame
	double old_time; //time of previous frame
	//valore utilizzato per il calcolo del tempo di un frame (lo userò per il framerate)
	//e aggiornare la velocità di movimento  
	double frametime_sec;

	//struct info raycasting
	t_ray	ray;

	//matrice che rappresenta i pixel della finestra
	int **screen_pixels; //  la sua TEXTURE_PIXELS

	/*struct contenente il puntatore e le info del frame*/
	t_img	frame;

	t_img   fps;/**************************** */

}	t_game;


#endif