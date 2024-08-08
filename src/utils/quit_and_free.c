/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:11:16 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/06/24 11:15:59 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	print_error(char *error)
{
	ft_printf("Error: %s\n", error);
}

int free_matrix(void **ptr_matric)
{
    int i;

    i = 0;
    while (ptr_matric[i] != NULL)
    {
        free(ptr_matric[i]);
        i++;
    }
    free(ptr_matric);
    return (0);
}

static void ft_destroy_engine(t_game *g)
{
	if (g->mlx.mlx_ptr && g->mlx.win_ptr)
		mlx_destroy_window(g->mlx.mlx_ptr, g->mlx.win_ptr);
	if (g->mlx.mlx_ptr)
	{
		mlx_destroy_display(g->mlx.mlx_ptr);
		mlx_loop_end(g->mlx.mlx_ptr);
		free(g->mlx.mlx_ptr);
	}
}


//void ft_destroy(t_game *g)

static void destroy_struct(t_game *g)
{		
	if (g->map.text.north)
		free(g->map.text.north);
	if (g->map.text.south)
		free(g->map.text.south);
	if (g->map.text.east)
		free(g->map.text.east);
	if (g->map.text.west)
		free(g->map.text.west);
	if (g->map.map_mat != NULL)
		free_matrix((void **)g->map.map_mat);
	if (g->screen_pixels != NULL)
		free_matrix((void **)g->screen_pixels);
	if (g->map.text.wall_pixels)
		free_matrix((void **)g->map.text.wall_pixels);
}

static void destroy_img(t_game *g)
{
	if (g->frame.img)
		mlx_destroy_image(g->mlx.mlx_ptr, g->frame.img);
	if (g->minimap.img_bg.img)
		mlx_destroy_image(g->mlx.mlx_ptr, g->minimap.img_bg.img);
	if (g->fps.img)
		mlx_destroy_image(g->mlx.mlx_ptr, g->fps.img);
}

int	ft_close_x(t_game *ptr_game)
{
	quit_and_free("See U <3", 0, ptr_game);
	return (0);
}

void clear_matrix(int **matrix)
{
    int i, j;

    i = 0;
    while (i < RES_Y)
    {
        j = 0;
        while (j < RES_X)
        {
            matrix[i][j] = 0;
            j++;
        }
        i++;
    }
}




/*POI FARE UN ENUM PER IL TIèPE_ERR E RIORDINARE*/
int quit_and_free(char *error, int err_type, t_game *g)
{
	if (err_type == 0)
	{
		ft_printf("%s\n", error);
		destroy_struct(g);
		destroy_img(g);
		ft_destroy_engine(g);
	}
	else if (err_type == 1) 
		print_error(error);
	else if (err_type == 2)
	{
		print_error(error);
		destroy_struct(g);
		destroy_img(g);
		ft_destroy_engine(g);
	}
	exit (0);
}
