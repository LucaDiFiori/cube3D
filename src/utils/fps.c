/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-30 11:19:16 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-07-30 11:19:16 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

unsigned long get_time_in_milliseconds()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

/**
 * Function: reverse_str
 * ----------------------
 * Reverses a given string in place. This function modifies the original 
 * string by swapping characters from the beginning and end, moving towards 
 * the center until the entire string is reversed.
 */
static void reverse_str(char *str) 
{
    int start;
    int end;
    char temp;

	start = 0;
	end = 0;
    while (str[end] != '\0')
	{
		end++;
	} 
    end--;
    while (start < end) 
	{
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

/**
 * Function: int_to_str
 * ---------------------
 * Converts an integer to its string representation. This function populates 
 * the provided character array with the string equivalent of the integer.
 */
static void int_to_str(int num, char *str) 
{
    int i;

	i = 0;
    if (num == 0) 
	{
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    while (num > 0) 
	{
        str[i++] = (num % 10) + '0';
        num /= 10;
    }
    str[i] = '\0';
    reverse_str(str);
}

/**
 * Function: build_fps_text
 * -------------------------
 * Constructs a string representing the FPS (frames per second) counter, formatted 
 * as "FPS: <fps>". This function converts the integer FPS value to a string and 
 * concatenates it with the "FPS: " prefix.
 */
static void build_fps_text(int fps, char *fps_text) 
{
    char	fps_str[64];
    int		j;
	int		i;
    
	int_to_str(fps, fps_str);
    i = 0;
    fps_text[i++] = 'F';
    fps_text[i++] = 'P';
    fps_text[i++] = 'S';
    fps_text[i++] = ':';
    fps_text[i++] = ' ';
	j = 0;
    while (fps_str[j] != '\0') 
	{
        fps_text[i++] = fps_str[j++];
    }
    fps_text[i] = '\0';
}

/**
 * Function: draw_fps_counter
 * ----------------------------
 * Draws the FPS (frames per second) counter on the game window. This function 
 * calculates the current FPS based on the frame time, constructs the corresponding 
 * text string, and renders it onto the game window.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the game state and rendering data.
 *
 * Process:
 *  - Calculates the FPS by taking the reciprocal of `g->frametime_sec`, which represents 
 *    the time taken to render one frame. This gives the number of frames per second.
 *  - Constructs the FPS text string using `build_fps_text`, storing the result in `fps_text`.
 *  - Uses `mlx_string_put` to draw the FPS text string onto the game window at position (10, 10) 
 *    with a white color (0xFFFFFF).
 */
void draw_fps_counter(t_game *g) 
{
    char	fps_text[64];
    int		fps;

	fps = (int)(1 / g->frametime_sec);
    build_fps_text(fps, fps_text);
    mlx_string_put(g->mlx.mlx_ptr, g->mlx.win_ptr, 10, 10, 0xFFFFFF, fps_text);
}