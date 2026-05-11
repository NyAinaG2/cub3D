/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:01:47 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/11 19:27:23 by mrakotos         ###   ########.fr       */
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
#include "../types.h"

extern const unsigned char tmp_map[7][6];
int init(t_test* data_ptr);
void draw_rectangle(t_test* data, int x, int y, int color);
void draw(t_test* data);
int close_window(t_test* data);
int key_handler(int key, t_test* params);
double clamp_time(double time, double tmax);
double get_current_time();
double get_delta_time(t_test* data);
int is_move_valid(t_test* data, float px, float py);
int move(t_test* data);
void move_forward(t_test* data);
void move_backward(t_test* data);
void move_left(t_test* data);
void move_right(t_test* data);
int key_press(int key, t_test* data);
int key_release(int key, t_test* data);

#endif
