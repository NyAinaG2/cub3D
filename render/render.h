/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrrand <andrrand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:01:47 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/20 18:37:57 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../dda/dda.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../parse/parse.h"
# include "../types.h"
# include <math.h>
# include <stdlib.h>
# include <sys/time.h>

int			close_window(t_game *data);
void		put_pixel_to_img(t_game *data, int x, int y, int color);
int			is_move_valid(t_game *data, float px, float py);
void		normalize_direction(t_game *data);
int			move(t_game *data);
int			key_press(int key, t_game *data);
int			key_release(int key, t_game *data);
void		draw_column(int len, int x, t_game *data, t_params *params);
void		init_textures(t_data *parse, t_game *data);
int			sample_texture(t_texture *texture, int x, int y);
int			get_texture_y(t_texture *texture, t_column *column);
int			get_texture_x(t_texture *texture, t_params *params);
t_texture	*get_texture(t_params *params, t_game *data);
float		set_player_direction(char direction);
void		render(t_game *data);
int			init_render(t_game *data, t_data *parse);
double		get_time(void);
void		update_game_time(t_game *data);

#endif
