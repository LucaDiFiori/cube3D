#include "../../inc/cube3d.h"

/*************************************MAPPA ZOOMATA*************************** */




// Funzione per riempire la schermata di un dato colore
/*static void fill_background(t_game *g, t_img_data *data, int width, int height, int background_color)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            my_pixel_put(g, data, x, y, background_color);
        }
    }
}

void create_background(t_game *g) 
{
    int background_color = 0x404040; // Colore di sfondo (verde)

    // Alloco memoria per una nuova immagine attraverso mlx_new_image
    g->minimap.img_bg.img = mlx_new_image(g->mlx.mlx_ptr, g->minimap.minimap_width, g->minimap.minimap_height);

    // Estraggo i dati dell'immagine 
    g->minimap.img_bg.addr = mlx_get_data_addr(g->minimap.img_bg.img, &g->minimap.img_bg.bpp, &g->minimap.img_bg.line_length, &g->minimap.img_bg.endian);

    // Riempie lo sfondo dell'immagine con il colore di sfondo 
    fill_background(g, &g->minimap.img_bg, g->minimap.minimap_width, g->minimap.minimap_height, background_color);

    // Mostra l'immagine della minimappa sulla finestra principale
    mlx_put_image_to_window(g->mlx.mlx_ptr, g->mlx.win_ptr, g->minimap.img_bg.img, RES_X - g->minimap.minimap_width, 0);
}


//SAREBBE BELLO SE ZUMMASSE SENZA CANCELLARE LA MAPPA DOPO 4 QUADRATI
void draw_map(t_game *g) 
{
    int view_size = 4; // Dimensione dell'area visibile intorno al personaggio
    int start_x = max(0, g->player.x - view_size);
    int end_x = min(g->map.map_x - 1, g->player.x + view_size);
    int start_y = max(0, g->player.y - view_size);
    int end_y = min(g->map.map_y - 1, g->player.y + view_size);

    int y = start_y;
    while (y <= end_y) {
        int x = start_x;
        while (x <= end_x) {
            float map_x = (x - start_x) * g->minimap.cell_width;
            float map_y = (y - start_y) * g->minimap.cell_height;

            if (g->map.map_mat[y][x] == '1') {
                draw_square(g, &g->minimap.img_bg, map_x, map_y, g->minimap.cell_width, g->minimap.cell_height); // Disegna un quadrato proporzionato alla cella
            }
            x++;
        }
        y++;
    }
}


void draw_player(t_game *g, float x, float y) 
{
    float player_x = (x - max(0, g->player.x - 4)) * g->minimap.cell_width + g->minimap.cell_width / 2;
    float player_y = (y - max(0, g->player.y - 4)) * g->minimap.cell_height + g->minimap.cell_height / 2;
    float radius = g->minimap.cell_width / 4; // Dimensione del cerchio che rappresenta il giocatore

    draw_circle(g, &g->minimap.img_bg, player_x, player_y, radius, 0x00FF00);
}

void minimap_test(t_game *g) {
    create_background(g);
    draw_map(g);
    draw_player(g, g->player.x, g->player.y);
}*/




































// ***************************MAPPA INTERA************************************ 

void draw_map(t_game *g) 
{
    // Calcola la dimensione delle celle nel minimappa
    float cell_width = (float) g->minimap.minimap_width / g->map.map_x;
    float cell_height = (float) g->minimap.minimap_height / g->map.map_y;

    // Itera su tutta la mappa
    for (int y = 0; y < g->map.map_y; y++) {
        for (int x = 0; x < g->map.map_x; x++) {
            float map_x = x * cell_width;
            float map_y = y * cell_height;

            if (g->map.map_mat[y][x] == '1') {
                draw_square(g, &g->minimap.img_bg, map_x, map_y, cell_width, cell_height);
            }
        }
    }
}

void init_minimap(t_game *g)
{
    g->minimap.img_bg.img = mlx_new_image(g->mlx.mlx_ptr, g->minimap.minimap_width, g->minimap.minimap_height);
    g->minimap.img_bg.addr = mlx_get_data_addr(g->minimap.img_bg.img, &g->minimap.img_bg.bpp, &g->minimap.img_bg.line_length, &g->minimap.img_bg.endian);
    fill_background(g, &g->minimap.img_bg, g->minimap.minimap_width, g->minimap.minimap_height, 0x404040);
    draw_map(g);
    mlx_put_image_to_window(g->mlx.mlx_ptr, g->mlx.win_ptr, g->minimap.img_bg.img, RES_X - g->minimap.minimap_width, 0);
}

void draw_player(t_game *g, float x, float y) 
{
    // Calcola la dimensione delle celle nel minimappa
    float cell_width = (float) g->minimap.minimap_width / g->map.map_x;
    float cell_height = (float) g->minimap.minimap_height / g->map.map_y;

    // Calcola la posizione del giocatore nel minimappa
    float player_x = x * cell_width;
    float player_y = y * cell_height;

    float radius = cell_width / 5; // Dimensione del cerchio che rappresenta il giocatore

    draw_circle(g, &g->minimap.img_bg, player_x, player_y, radius, 0x00FF00);
}



/*CAPIRE PERCHE NON STAMPA TUTTA LA MAPPA*/
void minimap_test(t_game *g) {
    fill_background(g, &g->minimap.img_bg, g->minimap.minimap_width, g->minimap.minimap_height, 0x404040);    
    draw_map(g);
    draw_player(g, g->player.x, g->player.y);
    mlx_put_image_to_window(g->mlx.mlx_ptr, g->mlx.win_ptr, g->minimap.img_bg.img, RES_X - g->minimap.minimap_width, 0);
}