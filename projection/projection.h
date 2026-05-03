/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:01:47 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/03 16:29:35 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTION_H
#define PROJECTION_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../dda/dda.h"
#include "../minilibx-linux/mlx.h"
#include "../types.h"

extern const unsigned char tmp_map[7][6];
int init(t_test* data_ptr);
void draw_rectangle(t_test* data, int x, int y, int color);
void draw(t_test* data);
int close_window(t_test* data);
int key_handler(int key, t_test* params);

#endif
