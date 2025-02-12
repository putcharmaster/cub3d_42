/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:21:17 by sanhwang          #+#    #+#             */
/*   Updated: 2025/02/11 22:51:33 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../includes/GETNEXTLINE/get_next_line.h"
# include "../includes/libft/libft.h"
# include "../mlx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768

/************KEYBINDS***********/
# define ARROW_R 65363
# define ARROW_L 65361
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_Z 122
# define KEY_Q 113
# define KEY_ESC 65307
# define PATH_MAX 200

typedef struct s_map_info
{
	int			config_count;
	int			map_started;
	int			last_valid_line_found;
	int			map_ended;
}				t_map_info;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	char		*path;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_texture;

typedef struct s_wall_data
{
	int			x;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_wall_data;

typedef struct s_wall_calc
{
	t_texture	**texture;
	double		*wall_x;
	double		perp_wall_dist;
}				t_wall_calc;

typedef struct s_img
{
	void		*img;
	void		*addr;
	int			bits_p_pxl;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		pos_x;
	double		pos_y;
	double		move_speed;
	double		rotate_speed;
}				t_ray;

typedef struct s_dda
{
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		ray_dir_x;
	double		ray_dir_y;
}				t_dda;

typedef struct s_tokens
{
	int			no;
	int			so;
	int			ea;
	int			we;
	int			f;
	int			c;
}				t_tokens;

typedef struct s_minimap
{
	int			pos_x;
	int			pos_y;
	int			scale;
	int			border;
	int			show;
	int			width;
	int			height;
	int			color;
	int			plyr_color;
}				t_minimap;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_w;
	int			win_h;
	char		**map;
	int			map_width;
	int			map_height;
	int			floor_color;
	int			ceiling_color;
	int			key_w;
	int			key_s;
	int			key_a;
	int			key_d;
	int			key_left;
	int			key_right;
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
	t_ray		ray;
	t_img		image;
	t_minimap	minimap;
	t_tokens	*tokens;
}				t_data;

typedef struct s_config
{
	t_data		*data;
	char		*line;
	char		**split;
	int			fd;
}				t_config;

// minimap.c
void			init_minimap(t_data *data);
void			draw_minimap(t_data *data);
void			draw_square(t_data *data, int x, int y, int size);

// check_file.c
void			check_file(char *file);

// check_map.c
void			check_map(t_data *data);
int				map_height(char **map);

// config_parser_0.c
void			parse_config(t_data *data, char *file);
void			save_token_status(t_config *config);
void			check_duplicates(t_config *config);

// config_parser_1.c
int				process_config_line(t_config *config);
int				check_config_colors(t_config *config);
int				check_config_walls(t_config *config);
int				check_config_textures(t_config *config);

// config_parser_2.c
int				load_texture(t_data *data, t_texture *texture, char *path);
int				parse_rgb(char *line);
int				validate_rgb_value(char **split, int *rgb, int i);

// config_parser_3.c
void			cleanup_config(t_data *data, char *line, char **split, int fd);

// draw_walls.c
void			draw_wall(t_data *data, t_dda *dda, int x,
					double perp_wall_dist);
// error.c
void			exit_error(char *message);
void			handle_fd_error(t_data *data);

// free_helpers_1.c
void			free_split(char **split);
void			free_textures(t_data *data);
void			cleanup_gnl(int fd);
void			free_and_close(char *line, int fd);
void			free_and_exit(t_data *data, char *msg);

// free_helpers_2.c
void			free_token(t_data *data);

// free.c
void			free_resources(t_data *data);
void			free_img(t_data *data);
void			free_map(t_data *data);
void			free_win(t_data *data);
void			free_mlx(t_data *data);

// main.c
void			init_data(t_data *data);

// map_helpers.c
void			clean_map(t_data ***data);
void			check_surr_walls(t_data **data);

// movements.c
void			mv_fw(t_data *data);
void			mv_bw(t_data *data);
void			strafe_left(t_data *data);
void			strafe_right(t_data *data);

// parse_map_0.c
t_map_info		*init_map_info(void);
char			**parse_map(char *map);
void			clean_and_close(int fd);
char			*parse_map_read(char *map);

// parse_map_1.c
char			*handle_file_open(char *map, int fd);
char			*read_map_lines(int fd, char *all_lines);

// parse_map_2.c
char			*parse_map_read_prep(char *map);
char			*process_map_lines(char *cur_line, char *all_lines);
int				process_map_configs(char *cur_line, int *config_count);

// parse_map_helpers.c
int				is_config_line(const char *line);
int				is_valid_map_line(char *line);
char			*return_error(char *all_lines);
char			*error_invalid_config(char *cur_line, char *all_lines);
char			*error_invalid_map_line(char *cur_line, char *all_lines);

// parse_map_helpers_2.c
char			*error_extra_lines(char *cur_line, char *all_lines);
char			*handle_map_line(char *cur_line, char *all_lines,
					t_map_info *map_info);

// pixel_put.c
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);

// raycast_helpers.c
void			init_dda(double ray_dir_x, double ray_dir_y, t_data *data,
					t_dda *dda);
void			calculate_step(t_dda *dda, double ray_dir_x, double rary_dir_y,
					t_data *data);
void			calculate_ray(t_data *data, int x, double *ray_dir_x,
					double *rary_dir_y);
void			perform_dda(t_data *data, t_dda *dda);

// raycasting.c
void			cast_rays(t_data *data);

// render.c
int				key_press(int key, t_data *data);
int				key_release(int key, t_data *data);
int				close_win(t_data *data);
int				render(t_data *data);

// rotate.c
void			rotate_left(t_data *data);
void			rotate_right(t_data *data);

// texture_mapping.c
void			draw_floor_ceiling(t_data *data);

// valid_map_elem.c
void			validate_map_elements(t_data *data);

// valid_plyr_pos.c
void			validate_player_position(t_data *data);

#endif