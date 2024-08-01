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

// Funzione per invertire una stringa
static void reverse_str(char *str) 
{
    int start;
    int end;

	start = 0;
	end = 0;
    while (str[end] != '\0')
	{
		end++;
	} 
    end--;

    char temp;
    while (start < end) 
	{
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Funzione per convertire un intero in una stringa
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

// Funzione per costruire il testo del contatore FPS
static void build_fps_text(int fps, char *fps_text) 
{
    char fps_str[64];
    int_to_str(fps, fps_str);

    // Costruisci la stringa completa del contatore FPS
    int i = 0;
    fps_text[i++] = 'F';
    fps_text[i++] = 'P';
    fps_text[i++] = 'S';
    fps_text[i++] = ':';
    fps_text[i++] = ' ';
    
    int j = 0;
    while (fps_str[j] != '\0') 
	{
        fps_text[i++] = fps_str[j++];
    }
    fps_text[i] = '\0'; // Terminatore null
}



// Funzione per disegnare il contatore FPS
void draw_fps_counter(t_game *g) 
{
    char fps_text[64];
    
    // Ottieni FPS e costruisci la stringa
    int fps;
	fps = (int)(1 / g->frametime_sec);
    build_fps_text(fps, fps_text);
    
    // Disegna il testo del contatore FPS sull'immagine
    mlx_string_put(g->mlx.mlx_ptr, g->mlx.win_ptr, 10, 10, 0xFFFFFF, fps_text); // 0xFFFFFF è il colore bianco
}