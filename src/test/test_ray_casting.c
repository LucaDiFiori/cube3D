#include "../../inc/cube3d.h"

int calculate_map_width(char **map_mat) {
    int width = 0;
    while (map_mat[0][width] != '\0') {
        width++;
    }
    return width;
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
void draw_square(t_img_data *img_data, int start_x, int start_y, int size, int color)
{
    int end_x = start_x + size;
    int end_y = start_y + size;

    for (int x = start_x; x < end_x; x++)
    {
        for (int y = start_y; y < end_y; y++)
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

    int cell_width = MINI_RES_X / MAP_WIDTH; // Calcola la larghezza di ogni cella sulla minimappa
    int cell_height = MINI_RES_Y / MAP_HEIGHT; // Calcola l'altezza di ogni cella sulla minimappa

    for (int y = 0; y < MAP_HEIGHT; y++) // Itera su ogni riga della mappa
    {
        for (int x = 0; x < MAP_WIDTH; x++) // Itera su ogni colonna della mappa
        {
            if (g_s->map.map_mat[y][x] == '1') // Se il carattere è '1', disegna un quadrato bianco
            {
                int map_x = x * cell_width;
                int map_y = y * cell_height;
                draw_square(img_data, map_x, map_y, cell_width, color); // Disegna un quadrato proporzionato alla cella
            }
            else if (g_s->map.map_mat[y][x] == 'N' || g_s->map.map_mat[y][x] == 'W' //disegno il personaggio
                ||g_s->map.map_mat[y][x] == 'W' || g_s->map.map_mat[y][x] == 'O')
            {
                int map_x = x * cell_width;
                int map_y = y * cell_height;
                 draw_square(img_data, map_x, map_y, cell_width, player_color);
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