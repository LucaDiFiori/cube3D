#include "../../inc/cube3d.h"


/*void my_pixel_put(t_game *g, t_img *data, int x, int y, int color)
{
    char *dst;

    // Verifica che le coordinate siano all'interno dei limiti dell'immagine
    if (x >= 0 && x < g->minimap.minimap_width && y >= 0 && y < g->minimap.minimap_height)
    {
        dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
        *(unsigned int*)dst = color;
    }
*/
void my_pixel_put(t_game *g, t_img *data, int x, int y, int color)
{
    int *dst;

    // Verifica che le coordinate siano all'interno dei limiti dell'immagine
    if (x >= 0 && x < g->minimap.minimap_width && y >= 0 && y < g->minimap.minimap_height)
    {
        // Calcola l'indice del pixel nell'array di int
        dst = data->addr + (y * (data->line_length / sizeof(int))) + x;
        
        // Imposta il colore del pixel
        *dst = color;
    }
}

// Funzione per riempire la schermata di un dato colore
void fill_background(t_game *g, t_img *data, int width, int height, int background_color)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            my_pixel_put(g, data, x, y, background_color);
        }
    }
}

/*    questa funzione disegna un quadrato della dimensione, colore e posizione indicati*/
void draw_square(t_game *g, double start_x, double start_y,
    double size_x, double size_y) 
{
    int x = (int)start_x;
    int y;

    while (x < start_x + size_x) {
        y = (int)start_y;
        while (y < start_y + size_y) {
            my_pixel_put(g, &g->minimap.img_bg, x, y, 0xFFFFFF);
            y++;
        }
        x++;
    }
}

void draw_door(t_game *g, double start_x, double start_y,
    double size_x, double size_y) 
{
    int x = (int)start_x;
    int y;

    while (x < start_x + size_x) {
        y = (int)start_y;
        while (y < start_y + size_y) {
            my_pixel_put(g, &g->minimap.img_bg, x, y, 0x00FFFF);
            y++;
        }
        x++;
    }
}

void draw_circle(t_game *g, t_img *img_data, double center_x, double center_y,
    double radius, int color) 
{
    double x = center_x - radius;
    double y;

    while (x <= center_x + radius) {
        y = center_y - radius;
        while (y <= center_y + radius) {
            if ((x - center_x) * (x - center_x) + (y - center_y)* (y - center_y)
                <= radius * radius) 
            {
                my_pixel_put(g, img_data, (int)x, (int)y, color);
            }
            y++;
        }
        x++;
    }
}
