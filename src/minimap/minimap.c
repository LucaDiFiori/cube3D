#include "../../inc/cube3d.h"











































// ***************************MAPPA INTERA************************************ 
//questa per farla disegnare con mappe irregolari
void draw_map(t_game *g) 
{
    // Itera su tutta la mappa
    for (int y = 0; y < g->map.map_y; y++) {
        // Calcola la lunghezza della riga corrente
        int row_length = ft_strlen(g->map.map_mat[y]);
        for (int x = 0; x < row_length; x++) {
            double map_x = x * g->minimap.cell_width;
            double map_y = y * g->minimap.cell_height;

            if (g->map.map_mat[y][x] == '1') {
                draw_square(g, map_x, map_y, g->minimap.cell_width - 1, g->minimap.cell_height - 1); //questi -1 danno l effetto griglia sulla mappa
            }
        }
    }
}



void init_minimap(t_game *g)
{
    init_img_data(g, &g->minimap.img_bg, g->minimap.minimap_width, g->minimap.minimap_height);
    /*g->minimap.img_bg.img = mlx_new_image(g->mlx.mlx_ptr, g->minimap.minimap_width, g->minimap.minimap_height);
    g->minimap.img_bg.addr = mlx_get_data_addr(g->minimap.img_bg.img,
        &g->minimap.img_bg.bpp, &g->minimap.img_bg.line_length,
        &g->minimap.img_bg.endian);*/
    g->minimap.cell_height = (double) g->minimap.minimap_height / g->map.map_y;
    g->minimap.cell_width = (double) g->minimap.minimap_width / g->map.map_x;

    
    
    //fill_background(g, &g->minimap.img_bg, g->minimap.minimap_width, g->minimap.minimap_height, 0x404040);
    //draw_map(g);
    //mlx_put_image_to_window(g->mlx.mlx_ptr, g->mlx.win_ptr, g->minimap.img_bg.img, RES_X - g->minimap.minimap_width, 0);
}

void draw_player(t_game *g, double x, double y) 
{

    // Calcola la posizione del giocatore nel minimappa
    double player_x = x * g->minimap.cell_width;
    double player_y = y * g->minimap.cell_height;

    double radius = g->minimap.cell_width / 3; // Dimensione del cerchio che rappresenta il giocatore

    draw_circle(g, &g->minimap.img_bg, player_x, player_y, radius, 0x00FF00);
}



void draw_minimap(t_game *g) {
    fill_background(g, &g->minimap.img_bg, g->minimap.minimap_width, g->minimap.minimap_height, 0x404040);    
    draw_map(g);
    draw_player(g, g->player.x, g->player.y);
    mlx_put_image_to_window(g->mlx.mlx_ptr, g->mlx.win_ptr, g->minimap.img_bg.img, RES_X - g->minimap.minimap_width, 0);

}

