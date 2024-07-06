#include "../../inc/cube3d.h"



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


	//___________________________METTO L'IMMAGINE A SCHERMO_____________________
    // Collega l'immagine alla finestra (metto l'immagine a schermo)
    fill_background(img_data, MINI_RES_X, MINI_RES_Y, background_color);
	//__________________________________________________________________________


	/*DA LIBERARE:
	 image con la funzione mlx_destroy_image: mlx_destroy_image(g_s->mlx.mlx_ptr, image);*/
}






/*funzione per disegnare un quadratino nel punto indicato*/
void draw_player_square(t_img_data *img_data, float player_map_x, float player_map_y, int color) {
    int size = 5; // Dimensione del lato del quadrato, regola questo per cambiare le dimensioni
    int start_x = player_map_x - size / 2;
    int start_y = player_map_y - size / 2;
    int end_x = start_x + size;
    int end_y = start_y + size;

    for (int x = start_x; x < end_x; x++) {
        for (int y = start_y; y < end_y; y++) {
            my_pixel_put(img_data, x, y, color);
        }
    }
}

/*Questa funzione prende la sesso puntatore ad immagine creato in create_background
  e ci disegna il personaggio*/
void drow_player(t_game *g_s, t_img_data *img_data)
{
    int color = 0xFFFFFF; // Colore bianco per il giocatore


    // Calcolo delle coordinate del giocatore sulla minimappa
    float player_map_x = g_s->player.x * RES_X / MINI_RES_X ;    // Scala x sulla mappa  // MINI_RES_X/RES_X chat aveva messo cosi;
    float player_map_y = g_s->player.y * RES_Y / MINI_RES_Y;  // Scala y sulla mappa


	printf("player_map_x: %f\n", player_map_x);
	printf("player_map_y: %f\n", player_map_y);

    // Disegna il giocatore sulla minimappa
    //my_pixel_put(img_data, player_map_x, player_map_y, color);
	draw_player_square(img_data, player_map_x, player_map_y, color);

    // Mostra l'immagine della minimappa sulla finestra principale
    mlx_put_image_to_window(g_s->mlx.mlx_ptr, g_s->mlx.win_ptr, img_data->img, RES_X - MINI_RES_X, 0);
}







/*******SONO ARRIVATO QUI MA DEVO IMPLEMENTARE UNA FUNZIONE CHE CALCOLI LA LUNGHEZZA E L'ALTEZZA DELLA MAPPA 
 * IL PROBLEMA E IN DROW PLAYER SQUARE
 * - drow player square funziona per il personaggio ma forse per la 
 *   mappa dovrei usare mlx_put_image_to_window con dei quadrati binachi di una certa dimensione
*/
void draw_map(t_game *g_s, t_img_data *img_data)
{
    int color = 0xFFFFFF; // Colore bianco per i muri
    int y = 0;

    while (g_s->map.map_mat[y] != NULL) // Itera su ogni linea finché non è NULL
    {
        int x = 0;
        while (g_s->map.map_mat[y][x] != '\0') // Itera su ogni carattere della linea finché non è il terminatore di stringa
        {
            if (g_s->map.map_mat[y][x] == '1') // Se il carattere è '1', disegna un quadrato bianco
            {
                float map_x = x * RES_X / MINI_RES_X;
                float map_y = y * RES_Y / MINI_RES_Y;
                //draw_player_square(img_data, map_x, map_y, color);
                my_pixel_put(img_data, map_x, map_y, color); //una volta riscritta sostituire draw_player_quare
            }
            x++;
        }
        y++;
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
	drow_player(g_s, &img_data);


}