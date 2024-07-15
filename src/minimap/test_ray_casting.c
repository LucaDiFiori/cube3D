#include "../../inc/cube3d.h"

/*************************************MAPPA ZOOMATA*************************** */




// Funzione per riempire la schermata di un dato colore
/*

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





/******************************************************************************* */






/*void init_minimap(t_game *g)
{
    g->minimap.img_bg.img = mlx_new_image(g->mlx.mlx_ptr, g->minimap.minimap_width, g->minimap.minimap_height);
    g->minimap.img_bg.addr = mlx_get_data_addr(g->minimap.img_bg.img, &g->minimap.img_bg.bpp, &g->minimap.img_bg.line_length, &g->minimap.img_bg.endian);
    g->minimap.cell_height = (float) g->minimap.minimap_height / 9; // 9 è il doppio di view_size (4) + 1 per il centro
    g->minimap.cell_width = (float) g->minimap.minimap_width / 9;
    fill_background(g, &g->minimap.img_bg, g->minimap.minimap_width, g->minimap.minimap_height, 0x404040);
    draw_map(g);
    draw_player(g);
    mlx_put_image_to_window(g->mlx.mlx_ptr, g->mlx.win_ptr, g->minimap.img_bg.img, RES_X - g->minimap.minimap_width, 0);
}

void draw_map(t_game *g) 
{
    int view_size = 4; // Dimensione dell'area visibile intorno al personaggio
    int start_x = max(0, g->player.x - view_size);
    int end_x = min(g->map.map_x - 1, g->player.x + view_size);
    int start_y = max(0, g->player.y - view_size);
    int end_y = min(g->map.map_y - 1, g->player.y + view_size);

    float cell_width_with_margin = g->minimap.cell_width * 0.9;
    float cell_height_with_margin = g->minimap.cell_height * 0.9;

    for (int y = start_y; y <= end_y; y++) {
        for (int x = start_x; x <= end_x; x++) {
            float map_x = (x - (g->player.x - view_size)) * g->minimap.cell_width + (g->minimap.cell_width - cell_width_with_margin) / 2;
            float map_y = (y - (g->player.y - view_size)) * g->minimap.cell_height + (g->minimap.cell_height - cell_height_with_margin) / 2;

            if (g->map.map_mat[y][x] == '1') {
                draw_square(g, map_x, map_y, cell_width_with_margin, cell_height_with_margin);
            }
        }
    }
}

void draw_player(t_game *g) 
{
    // Calcola la posizione del giocatore sulla minimappa in base alla sua posizione nel mondo di gioco
    float player_x = (g->player.x - (g->player.x - 4)) * g->minimap.cell_width + (g->minimap.cell_width / 2);
    float player_y = (g->player.y - (g->player.y - 4)) * g->minimap.cell_height + (g->minimap.cell_height / 2);

    // Riduci il raggio del giocatore per creare un buffer visivo tra il giocatore e i muri
    float radius = (g->minimap.cell_width / 4) * 0.75; // Riduci il raggio del 25%

    draw_circle(g, &g->minimap.img_bg, player_x, player_y, radius, 0x00FF00);
}

void minimap_test(t_game *g) {
    fill_background(g, &g->minimap.img_bg, g->minimap.minimap_width, g->minimap.minimap_height, 0x404040);    
    draw_map(g);
    draw_player(g);
    mlx_put_image_to_window(g->mlx.mlx_ptr, g->mlx.win_ptr, g->minimap.img_bg.img, RES_X - g->minimap.minimap_width, 0);
}*/












































// ***************************MAPPA INTERA************************************ 
//questa per farla disegnare con mappe irregolari
void draw_map(t_game *g) 
{

    // Itera su tutta la mappa
    for (int y = 0; y < g->map.map_y; y++) {
        for (int x = 0; x < g->map.map_x; x++) {
            float map_x = x * g->minimap.cell_width;
            float map_y = y * g->minimap.cell_height;

            if (g->map.map_mat[y][x] == '1') {
                draw_square(g, map_x, map_y, g->minimap.cell_width, g->minimap.cell_height);
            }
        }
    }
}

/*__________________________________________________________________________________________________*/
/*void draw_line(t_game *g, t_img_data *img, float x0, float y0, float x1, float y1, int color)
{
    int xi0 = (int)x0;
    int yi0 = (int)y0;
    int xi1 = (int)x1;
    int yi1 = (int)y1;

    int dx = abs(xi1 - xi0);
    int dy = abs(yi1 - yi0);
    int sx = xi0 < xi1 ? 1 : -1;
    int sy = yi0 < yi1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

   while (1) {
        if (xi0 >= 0 && xi0 < g->minimap.minimap_width && yi0 >= 0 && yi0 < g->minimap.minimap_height) { // Controllo dei limiti
            int pixel_index = (yi0 * img->line_length) + (xi0 * (img->bpp / 8));
            *(unsigned int *)(img->addr + pixel_index) = color;
        }

        //if (xi0 == xi1 && yi0 == yi1) break;

        e2 = err;
        if (e2 > -dx) { err -= dy; xi0 += sx; }
        if (e2 <  dy) { err += dx; yi0 += sy; }
    }
}

void draw_map(t_game *g)
{
    // Itera su tutta la mappa
    for (int y = 0; y < g->map.map_y; y++) {
        for (int x = 0; x < g->map.map_x; x++) {
            float map_x = x * g->minimap.cell_width;
            float map_y = y * g->minimap.cell_height;

            if (g->map.map_mat[y][x] == '1') {
                draw_square(g, map_x, map_y, g->minimap.cell_width, g->minimap.cell_height);
            } else if (g->map.map_mat[y][x] == '0') {
                // Calcola il vettore di direzione normalizzato
                float dir_x = g->player.dir_vec[0];
                float dir_y = g->player.dir_vec[1];
                float length = sqrt(dir_x * dir_x + dir_y * dir_y);
                dir_x /= length;
                dir_y /= length;

                // Inizia dal centro del giocatore
                float ray_x = g->player.x;
                float ray_y = g->player.y;

                // Continua fino a che non si colpisce un muro
                while (ray_x >= 0 && ray_x < g->map.map_x && ray_y >= 0 && ray_y < g->map.map_y) {
                    // Controlla se la cella è un muro
                    int cell_x = (int)ray_x;
                    int cell_y = (int)ray_y;
                    if (g->map.map_mat[cell_y][cell_x] == '1') {
                        // Disegna il raggio fino al punto di impatto con il muro
                        draw_line(g, &g->minimap.img_bg, g->player.x * g->minimap.cell_width, g->player.y * g->minimap.cell_height, ray_x * g->minimap.cell_width, ray_y * g->minimap.cell_height, 0xFF0000);
                        break;
                    }

                    // Avanza il raggio nella direzione del vettore di direzione
                    ray_x += dir_x;
                    ray_y += dir_y;
                }
            }
        }
    }
}*/
/*__________________________________________________________________________________________________*/

void init_minimap(t_game *g)
{
    g->minimap.img_bg.img = mlx_new_image(g->mlx.mlx_ptr, g->minimap.minimap_width, g->minimap.minimap_height);
    g->minimap.img_bg.addr = mlx_get_data_addr(g->minimap.img_bg.img, &g->minimap.img_bg.bpp, &g->minimap.img_bg.line_length, &g->minimap.img_bg.endian);
    g->minimap.cell_height = (float) g->minimap.minimap_height / g->map.map_y;
    g->minimap.cell_width = (float) g->minimap.minimap_width / g->map.map_x;
    fill_background(g, &g->minimap.img_bg, g->minimap.minimap_width, g->minimap.minimap_height, 0x404040);
    draw_map(g);
    mlx_put_image_to_window(g->mlx.mlx_ptr, g->mlx.win_ptr, g->minimap.img_bg.img, RES_X - g->minimap.minimap_width, 0);
}

void draw_player(t_game *g, float x, float y) 
{

    // Calcola la posizione del giocatore nel minimappa
    float player_x = x * g->minimap.cell_width;
    float player_y = y * g->minimap.cell_height;

    float radius = g->minimap.cell_width / 3; // Dimensione del cerchio che rappresenta il giocatore

    draw_circle(g, &g->minimap.img_bg, player_x, player_y, radius, 0x00FF00);
}



void minimap_test(t_game *g) {
    fill_background(g, &g->minimap.img_bg, g->minimap.minimap_width, g->minimap.minimap_height, 0x404040);    
    draw_map(g);
    draw_player(g, g->player.x, g->player.y);
    mlx_put_image_to_window(g->mlx.mlx_ptr, g->mlx.win_ptr, g->minimap.img_bg.img, RES_X - g->minimap.minimap_width, 0);
}