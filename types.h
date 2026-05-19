/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 09:01:01 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/19 09:47:16 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
#define TYPES_H

#define WIN_W 980
#define WIN_H 720
#define WIN_TITLE "cub3D"
#define ROTATION_SPEED 0.001
#define MOVE_SPEED 0.001
#define ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_D 100
#define KEY_S 115
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

typedef struct s_move
{
	int rotate_left;
	int rotate_right;
	int forward;
	int backward;
	int left;
	int right;
} t_move;

typedef struct s_texture
{
	int size_x;
	int size_y;
	int line_length;
	int bpp;
	int endian;
	char* addr;
	void* img;
} t_texture;

typedef struct test_s
{
	t_move move;
	void* mlx_ptr;
	void* windows_ptr;
	char** map;
	t_texture north;
	t_texture east;
	t_texture south;
	t_texture west;
	float px;
	float py;
	float player_box;
	float direction;
	float fov_max;
	float fov_min;
	float fov;
	float step;
	double game_time;
	int wall_color;
	int ceil_color;
	int floor_color;
	int map_size_x;
	int map_size_y;
	void* img;
	char* addr;
	int bpp;
	int line_length;
	int endian;
} t_test;

typedef struct s_point
{
	float x;
	float y;
} t_point;

typedef struct s_column
{
	float step;
	int start;
	int current;
	int len;
} t_column;

typedef struct s_vec
{
	t_point delta;
	t_point side;
	t_point angle;
	t_point step;
	t_point res;
	float t;
	int map_x;
	int map_y;
	int hit;
	char first_hit;
} t_vec;

typedef struct s_params
{
	char side;
	char direction;
	float scale;
	float d;
} t_params;

typedef struct s_dda
{
	t_point hit_p;
	t_point side_d;
	float distance;
	int side;
} t_dda;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

#endif
