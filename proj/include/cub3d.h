#ifndef CUB3D_H
# define CUB3D_H

# include <../minilibx-linux/mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define TEX_SIZE 64
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

# define EVT_PRESS 2
# define EVT_RELEASE 3
# define EVT_DESTROY 17

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}	t_keys;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		hex;
}	t_color;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;

typedef struct s_draw
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
}	t_draw;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		frame;
	t_player	player;
	t_keys		keys;
	t_map		map;
	t_color		floor;
	t_color		ceiling;
}	t_game;

int		init_game(t_game *game);
void	init_player(t_game *game, char dir, double x, double y);
void	init_player_dir(t_player *p, char dir);
void	init_keys(t_game *game);

void	render_frame(t_game *game);
void	put_pixel(t_img *img, int x, int y, int color);

void	raycast(t_game *game);
void	init_ray(t_game *game, t_ray *ray, int x);
void	calc_step_dist(t_game *game, t_ray *ray);
void	perform_dda(t_game *game, t_ray *ray);
void	calc_wall_dist(t_game *game, t_ray *ray);

void	draw_column(t_game *game, t_ray *ray, int x);
void	calc_draw_params(t_ray *ray, t_draw *draw);
int		get_wall_color(t_ray *ray);
void	draw_ver_line(t_game *game, int x, t_draw *draw);

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		close_window(t_game *game);
int		game_loop(t_game *game);
void	process_movement(t_game *game);

void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	strafe_left(t_game *game);
void	strafe_right(t_game *game);

void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
void	rotate_player(t_player *p, double angle);

int		can_move(t_game *game, double x, double y);
void	free_game(t_game *game);
void	free_map(t_game *game);
int		ft_strlen_safe(char *str);

int		init_hardcoded_map(t_game *game);
int		find_player(t_game *game);
int		copy_map_lines(t_game *game, char **lines);
void	init_colors(t_game *game);

#endif