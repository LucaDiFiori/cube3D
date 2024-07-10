#include "../../inc/cube3d.h"



//funzione per riempire la schermata di un dato colore
static void fill_background(t_minimap *data, int width, int height, int background_color)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            my_pixel_put(data, x, y, background_color);
        }
    }
}

void create_background(t_game *g_s) {
	int background_color = 0x404040; // Colore di sfondo (verde)
	//t_minimap *img_data = &(g_s->minimap);

	// Alloco memoria per una nuova immagine attraverso mlx_new_image
	g_s->minimap.img = mlx_new_image(g_s->mlx.mlx_ptr, g_s->minimap.minimap_width, g_s->minimap.minimap_height);

	// Estraggo i dati dell'immagine 
	g_s->minimap.addr = mlx_get_data_addr(g_s->minimap.img, &g_s->minimap.bpp, &g_s->minimap.line_length, &g_s->minimap.endian);

	// Riempie lo sfondo dell'immagine con il colore di sfondo 
	fill_background(&g_s->minimap, g_s->minimap.minimap_width, g_s->minimap.minimap_height, background_color);

	// Mostra l'immagine della minimappa sulla finestra principale
	mlx_put_image_to_window(g_s->mlx.mlx_ptr, g_s->mlx.win_ptr, g_s->minimap.img, RES_X - g_s->minimap.minimap_width, 0);
}





void draw_map(t_game *g_s) {
	int view_size = 4; // Dimensione dell'area visibile intorno al personaggio
	int start_x = max(0, g_s->player.x - view_size);
	int end_x = min(g_s->map.map_x - 1, g_s->player.x + view_size);
	int start_y = max(0, g_s->player.y - view_size);
	int end_y = min(g_s->map.map_y - 1, g_s->player.y + view_size);

	float cell_width = g_s->minimap.minimap_width / (2.0 * view_size + 1);
	float cell_height = g_s->minimap.minimap_height / (2.0 * view_size + 1);

	// Calcola gli offset per centrare la minimappa
	float offset_x = (g_s->minimap.minimap_width - ((end_x - start_x + 1) * cell_width)) / 6;
	float offset_y = (g_s->minimap.minimap_height - ((end_y - start_y + 1) * cell_height)) / 6;

	t_minimap *img_data = &(g_s->minimap);
	int y = start_y;
	while (y <= end_y) {
		int x = start_x;
		while (x <= end_x) {
			float map_x = (x - start_x) * cell_width;
			float map_y = (y - start_y) * cell_height;

			if (g_s->map.map_mat[y][x] == '1') {
				draw_square(img_data, map_x, map_y, cell_width, cell_height); // Disegna un quadrato proporzionato alla cella
			} else if (x == g_s->player.x && y == g_s->player.y) {
				draw_circle(img_data, map_x + offset_x, map_y + offset_y, cell_width / 12, 0x00FF00);
			}
			x++;
		}
		y++;
	}
}


/*void create_background(t_game *g_s) 
{
    if (access("../textures/Coin.xpm", F_OK) == -1) {
        perror("Errore nell'apertura del file bg_minimap.xpm");  //CAPIRE PERCHE NON LO APRE
        return; // Uscire dalla funzione se il file non può essere aperto
    } else {
        g_s->minimap.img_mmp_bg = mlx_xpm_file_to_image(g_s->mlx.mlx_ptr, 
            "../textures/Coin.xpm", &g_s->minimap.cell_width, &g_s->minimap.cell_height);
        if (!g_s->minimap.img_mmp_bg) {
            printf("Errore nel caricamento dell'immagine\n");
           return;
        }
    }

    for (int y = 0; y < g_s->minimap.minimap_height; y++) {
        for (int x = 0; x < g_s->minimap.minimap_width; x++) {
            mlx_put_image_to_window(g_s->mlx.mlx_ptr, g_s->mlx.win_ptr, g_s->minimap.img_mmp_bg, x * g_s->minimap.cell_width, y * g_s->minimap.cell_height);
        }
    }    
}*/






void minimap_test(t_game *g_s) {
	create_background(g_s);
	draw_map(g_s);



}