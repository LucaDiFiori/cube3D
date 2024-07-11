#include "../../inc/cube3d.h"

/*************************************MAPPA ZOOMATA*************************** */




// Funzione per riempire la schermata di un dato colore
static void fill_background(t_game *g, t_img_data *data, int width, int height, int background_color)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            my_pixel_put(g, data, x, y, background_color);
        }
    }
}

void create_background(t_game *g_s) 
{
    int background_color = 0x404040; // Colore di sfondo (verde)

    // Alloco memoria per una nuova immagine attraverso mlx_new_image
    g_s->minimap.img_bg.img = mlx_new_image(g_s->mlx.mlx_ptr, g_s->minimap.minimap_width, g_s->minimap.minimap_height);

    // Estraggo i dati dell'immagine 
    g_s->minimap.img_bg.addr = mlx_get_data_addr(g_s->minimap.img_bg.img, &g_s->minimap.img_bg.bpp, &g_s->minimap.img_bg.line_length, &g_s->minimap.img_bg.endian);

    // Riempie lo sfondo dell'immagine con il colore di sfondo 
    fill_background(g_s, &g_s->minimap.img_bg, g_s->minimap.minimap_width, g_s->minimap.minimap_height, background_color);

    // Mostra l'immagine della minimappa sulla finestra principale
    mlx_put_image_to_window(g_s->mlx.mlx_ptr, g_s->mlx.win_ptr, g_s->minimap.img_bg.img, RES_X - g_s->minimap.minimap_width, 0);
}

void draw_map(t_game *g_s) 
{
    int view_size = 4; // Dimensione dell'area visibile intorno al personaggio
    int start_x = max(0, g_s->player.x - view_size);
    int end_x = min(g_s->map.map_x - 1, g_s->player.x + view_size);
    int start_y = max(0, g_s->player.y - view_size);
    int end_y = min(g_s->map.map_y - 1, g_s->player.y + view_size);

    int y = start_y;
    while (y <= end_y) {
        int x = start_x;
        while (x <= end_x) {
            float map_x = (x - start_x) * g_s->minimap.cell_width;
            float map_y = (y - start_y) * g_s->minimap.cell_height;

            if (g_s->map.map_mat[y][x] == '1') {
                draw_square(g_s, &g_s->minimap.img_bg, map_x, map_y, g_s->minimap.cell_width, g_s->minimap.cell_height); // Disegna un quadrato proporzionato alla cella
            }
            x++;
        }
        y++;
    }
}



void draw_player(t_game *g_s, float x, float y) 
{
    float player_x = (x - max(0, g_s->player.x - 4)) * g_s->minimap.cell_width + g_s->minimap.cell_width / 2;
    float player_y = (y - max(0, g_s->player.y - 4)) * g_s->minimap.cell_height + g_s->minimap.cell_height / 2;
    float radius = g_s->minimap.cell_width / 4; // Dimensione del cerchio che rappresenta il giocatore

    draw_circle(g_s, &g_s->minimap.img_bg, player_x, player_y, radius, 0x00FF00);
}

void minimap_test(t_game *g_s) {
    create_background(g_s);
    draw_map(g_s);
    draw_player(g_s, g_s->player.x, g_s->player.y);
}








/******************************MAPPA INTERA************************************ 
// Funzione per riempire la schermata di un dato colore
static void fill_background(t_game *g, t_img_data *data, int width, int height, int background_color)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            my_pixel_put(g, data, x, y, background_color);
        }
    }
}

void create_background(t_game *g_s) 
{
    int background_color = 0x404040; // Colore di sfondo (verde)

    // Alloco memoria per una nuova immagine attraverso mlx_new_image
    g_s->minimap.img_bg.img = mlx_new_image(g_s->mlx.mlx_ptr, g_s->minimap.minimap_width, g_s->minimap.minimap_height);

    // Estraggo i dati dell'immagine 
    g_s->minimap.img_bg.addr = mlx_get_data_addr(g_s->minimap.img_bg.img, &g_s->minimap.img_bg.bpp, &g_s->minimap.img_bg.line_length, &g_s->minimap.img_bg.endian);

    // Riempie lo sfondo dell'immagine con il colore di sfondo 
    fill_background(g_s, &g_s->minimap.img_bg, g_s->minimap.minimap_width, g_s->minimap.minimap_height, background_color);

    // Mostra l'immagine della minimappa sulla finestra principale
    mlx_put_image_to_window(g_s->mlx.mlx_ptr, g_s->mlx.win_ptr, g_s->minimap.img_bg.img, RES_X - g_s->minimap.minimap_width, 0);
}

void draw_map(t_game *g_s) 
{
    // Calcola la dimensione delle celle nel minimappa
    float cell_width = (float) g_s->minimap.minimap_width / g_s->map.map_x;
    float cell_height = (float) g_s->minimap.minimap_height / g_s->map.map_y;

    // Itera su tutta la mappa
    for (int y = 0; y < g_s->map.map_y; y++) {
        for (int x = 0; x < g_s->map.map_x; x++) {
            float map_x = x * cell_width;
            float map_y = y * cell_height;

            if (g_s->map.map_mat[y][x] == '1') {
                draw_square(g_s, &g_s->minimap.img_bg, map_x, map_y, cell_width, cell_height);
            }
        }
    }
}

void draw_player(t_game *g_s, float x, float y) 
{
    // Calcola la dimensione delle celle nel minimappa
    float cell_width = (float) g_s->minimap.minimap_width / g_s->map.map_x;
    float cell_height = (float) g_s->minimap.minimap_height / g_s->map.map_y;

    // Calcola la posizione del giocatore nel minimappa
    float player_x = x * cell_width;
    float player_y = y * cell_height;

    float radius = cell_width / 4; // Dimensione del cerchio che rappresenta il giocatore

    draw_circle(g_s, &g_s->minimap.img_bg, player_x, player_y, radius, 0x00FF00);
}

void minimap_test(t_game *g_s) {
    create_background(g_s);
    draw_map(g_s);
    draw_player(g_s, g_s->player.x, g_s->player.y);
}*/