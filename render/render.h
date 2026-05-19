/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:01:47 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/19 10:34:16 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTION_H
#define PROJECTION_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../dda/dda.h"
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include "../parse/parse.h"
#include "../types.h"

int close_window(t_test* data);
void put_pixel_to_img(t_test* data, int x, int y, int color);
int is_move_valid(t_test* data, float px, float py);
void normalize_direction(t_test* data);
int move(t_test* data);
int key_press(int key, t_test* data);
int key_release(int key, t_test* data);
void draw_column(int len, int x, t_test* data, t_params* params);
void init_textures(t_data* parse, t_test* data);
t_texture* get_texture(t_params* params, t_test* data);
float set_player_direction(char direction);
void render(t_test* data);
int init_render(t_test* data, t_data* parse);

#endif
