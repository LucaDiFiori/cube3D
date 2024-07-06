#include "../../inc/cube3d.h"

/*calcola la lunghezza piu lunga fra tutte le*/
int calculate_map_width(char **map_mat) {
    int max_width = 0;
    int y = 0;

    while (map_mat[y] != NULL) {
        int current_width = ft_strlen(map_mat[y]);
        if (current_width > max_width) {
            max_width = current_width;
        }
        y++;
    }

    return max_width;
}

// Funzione per calcolare dinamicamente l'altezza della mappa
int calculate_map_height(char **map_mat) {
    int height = 0;
    while (map_mat[height] != NULL) {
        height++;
    }
    return height;
}






/*funzione per riempire la schermata di un dato colore*/
void fill_background(t_img_data *data, int width, int height, int background_color)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            my_pixel_put(data, x, y, background_color);
        }
    }
}

void create_backgound(t_game *g_s, t_img_data *img_data)
{
    int background_color = 0x404040; // Colore di sfondo (verde)

    //___________________________CREO L'IMMAGINE______________________________
    // alloco memoria per una nuova immagine attraverso mlx_new_image
    img_data->img = mlx_new_image(g_s->mlx.mlx_ptr, MINI_RES_X, MINI_RES_Y);
	//estraggo i dati dell'immagine 
    img_data->addr = mlx_get_data_addr(img_data->img, &img_data->bpp, &img_data->line_length, &img_data->endian);

    // Riempie lo sfondo dell'immagine con il colore di sfondo 
    fill_background(img_data, MINI_RES_X, MINI_RES_Y, background_color);
	//__________________________________________________________________________

    // Mostra l'immagine della minimappa sulla finestra principale
    mlx_put_image_to_window(g_s->mlx.mlx_ptr, g_s->mlx.win_ptr, img_data->img, RES_X - MINI_RES_X, 0);


	/*DA LIBERARE:
	 image con la funzione mlx_destroy_image: mlx_destroy_image(g_s->mlx.mlx_ptr, image);*/
}









/*    questa funzione disegna un quadrato della dimensione, colore e posizione indicati*/
void draw_square(t_img_data *img_data, float start_x, float start_y, float size_x, float size_y, int color)
{
    float end_x = start_x + size_x;
    float end_y = start_y + size_y;

    for (float x = start_x; x < end_x; x++)
    {
        for (float y = start_y; y < end_y; y++)
        {
            my_pixel_put(img_data, x, y, color);
        }
    }
}





/*******SONO ARRIVATO QUI MA DEVO IMPLEMENTARE UNA FUNZIONE CHE CALCOLI LA LUNGHEZZA E L'ALTEZZA DELLA MAPPA 
 * IL PROBLEMA E IN DROW PLAYER SQUARE
 * - drow player square funziona per il personaggio ma forse per la 
 *   mappa dovrei usare mlx_put_image_to_window con dei quadrati binachi di una certa dimensione
*/
void draw_map(t_game *g_s, t_img_data *img_data)
{
    int color = 0xFFFFFF; // Colore bianco per i muri
    int player_color = 0x00FF00;

    int MAP_WIDTH = calculate_map_width(g_s->map.map_mat);
    int MAP_HEIGHT = calculate_map_height(g_s->map.map_mat);

    float cell_width = MINI_RES_X / MAP_WIDTH; // Calcola la larghezza di ogni cella sulla minimappa
    float cell_height = MINI_RES_Y / MAP_HEIGHT; // Calcola l'altezza di ogni cella sulla minimappa

    float offset_x = (MINI_RES_X - (MAP_WIDTH * cell_width)) / 2; // Calcola l'offset orizzontale per centrare la mappa
    float offset_y = (MINI_RES_Y - (MAP_HEIGHT * cell_height)) / 2; // Calcola l'offset verticale per centrare la mappa

    for (int y = 0; y < MAP_HEIGHT; y++) // Itera su ogni riga della mappa
    {
        for (int x = 0; x < MAP_WIDTH; x++) // Itera su ogni colonna della mappa
        {
            if (g_s->map.map_mat[y][x] == '1') // Se il carattere è '1', disegna un quadrato bianco
            {
                float map_x = x * cell_width + offset_x;
                float map_y = y * cell_height + offset_y;
                draw_square(img_data, map_x, map_y, cell_width, cell_height, color); // Disegna un quadrato proporzionato alla cella
            }
            else if (g_s->map.map_mat[y][x] == 'N' || g_s->map.map_mat[y][x] == 'W' //disegno il personaggio
                ||g_s->map.map_mat[y][x] == 'W' || g_s->map.map_mat[y][x] == 'O')
            {
                float map_x = x * cell_width + offset_x;
                float map_y = y * cell_height + offset_y;
                draw_square(img_data, map_x, map_y, cell_width, cell_height, player_color);
            }
        }
    }
}






void minimap_test(t_game *g_s)
{
	/*la variabile img_data (contenente il puntatore all'immagine) mi serve
	  qui perchè io ogni volta andrò a modificare la stessa immagine della minimappa
	  prima riempendola di grigio, poi disegnando il personaggio etc*/
	t_img_data img_data;

	
	create_backgound(g_s, &img_data);

	draw_map(g_s, &img_data);



}