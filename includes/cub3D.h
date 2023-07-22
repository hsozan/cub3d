/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stunca <stunca@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 08:43:26 by sreinhol          #+#    #+#             */
/*   Updated: 2023/07/22 17:30:22 by stunca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define FAILED -1
# define SUCCESS 0
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_A 0
# define KEY_D 2
# define KEY_W 13
# define KEY_S 1
# define KEY_ESC 53
# define KEY_SPACE 49
# define KEY_LSHIFT 258
# define KEY_RSHIFT 257
# define S_WIDTH 1280
# define S_HEIGHT 960
# define TEX_WIDTH 256
# define TEX_HEIGHT 256
# define X_KEY_PRESS 2

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*ceiling_color;
	char	*floor_color;
	int		width;
	int		height;
	int		map_row;
	char	**map_array;
	int		*len;
	int		line_length;
	char	player;
	int 	player_x;
	int 	player_y;
	char	player_dir;
}			t_map;

typedef struct s_check
{
	int		fd;
	char	*str;
	int		control;
	int		identifiers;
	int		player;
	int		max_i;
	int		max_j;
	bool	map_started;
}			t_check;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		sl;		// ???
	int		bpp;	// ??? bir çok problemin temsili ???
	int		endian; // adres bildisini bit olrak saklar
	int		width;
	int		height;
}			t_img;

typedef struct s_ray
{
	double	camerax;
	double	raydirx; // ışın mesafesi-yönü
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty; // kenarın mesafesi
	double	deltadistx; 
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		texnum;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		texx;
}			t_ray;

typedef struct s_mini
{
	int	white;
	int	red;
	int	midh;
	int	midw;
	int	k;
	int	l;
	int	x;
	int	y;
	int	i;
	int	j;
}			t_mini;

typedef struct s_data
{
	void				*mlx_ptr; // görüntü tütar
	void				*win_ptr;
	void				*mlx_img;
	int					*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					img_width;
	int					img_height;
	int					**texture;
	int					buffer[S_HEIGHT][S_WIDTH];
	unsigned long		floor_color;
	unsigned long		ceiling_color;
	double				posx;
	double				posy;
	double				dirx;
	double				diry;
	int					mouse_x;
	int					mouse_y;
	double				planex;
	double				planey;
	double				move_speed;
	double				rot_speed;
	double				time;
	double				old_time;
	t_map				map;
	t_img				img[5];
	bool				tflag;
	bool				up;
	bool				down;
	bool				sleft;
	bool				sright;
	bool				rleft;
	bool				rright;
	//pthread_t			t;
}			t_data;
// mlx_ptr: MiniLibX kütüphanesine ait bir işaretçi, grafik penceresiyle etkileşim sağlamak için kullanılır.
// win_ptr: Grafik penceresine ait bir işaretçi, çizimlerin yapılacağı pencereyi temsil eder.
// mlx_img: Grafik penceresindeki görüntü için bir işaretçi.
// addr: Görüntünün bellekteki adresini tutan bir işaretçi.
// bits_per_pixel: Her pikselin kaç bit ile temsil edildiğini belirten bir tamsayı.
// line_length: Görüntüdeki her satırın bellekte kaç bayt tuttuğunu belirten bir tamsayı.
// endian: Bellekteki baytların hangi sırada olduğunu belirten bir tamsayı.
// img_width: Görüntünün genişliğini temsil eden bir tamsayı.
// img_height: Görüntünün yüksekliğini temsil eden bir tamsayı.
// texture: Bir dizi diziye (2D dizisi) işaret eden bir işaretçi. Texture'lar için kullanılır.
// buffer: Oyunun görüntü tamponunu tutan 2D tam sayı dizisi.
// floor_color: Zemin rengini temsil eden bir unsigned long türü.
// ceiling_color: Tavan rengini temsil eden bir unsigned long türü.
// posx, posy: Oyuncunun konumunu temsil eden ondalık sayılar (double).
// dirx, diry: Oyuncunun bakış yönünü temsil eden ondalık sayılar (double).
// mouse_x, mouse_y: Fare konumunu temsil eden tamsayılar.
// planex, planey: Oyuncunun kamera düzleminin yönlendirilmesini temsil eden ondalık sayılar (double).
// move_speed: Oyuncunun hareket hızını temsil eden ondalık sayı (double).
// rot_speed: Oyuncunun dönüş hızını temsil eden ondalık sayı (double).
// time: Oyun süresini temsil eden ondalık sayı (double).
// old_time: Önceki oyun süresini temsil eden ondalık sayı (double).
// map: Oyun haritasını temsil eden t_map türünde bir yapı.
// img: Oyun için kullanılan görüntülerin (t_img) bir dizisi.
// tflag: Bir bayrak (flag) değeri, belirli bir durumu temsil eder.
// up, down, sleft, sright, rleft, rright: Yön ve hareket tuşlarının durumunu temsil eden bayraklar (bool).

# define BUFFER_SIZE 42

int		check_input(int argc, char **argv);
void	init_map_and_check(t_data *data, t_check *check, char *input);
int		init_data(t_data *data);
void	get_identifiers(t_data *data, t_check *check);
void	save_map_info(t_data *data, t_check *check);
void	check_map(t_data *data, t_check *check);
void	fill_map(t_data *data, char *input, t_check *check);
void	check_borders(t_data *data, t_check *check);
void	save_colors(t_data *data, t_check *check, char *str, char c);
int		check_color(t_data *data, char **rgb, char c);
void	init_player_map(t_data *data);

char	*get_next_line(int fd);
void	gnl(char **str, int in, bool map, t_check *check);

void	error(char *msg);
void	error_free(char *msg, char *str);
void	error_free2(char *msg, char **str);
void	error_free3(char *msg, t_data *data);
void	error_free4(char *msg, t_data *data);
void	error_free5(char *msg, t_data *data);
int		ft_exit(t_data *data);

int		main_loop(t_data *info);
void	ceiling_floor_color(t_data *data);
void	calculate_step(t_data *data, t_ray *ray);
void	calculate_scene(t_data *data, t_ray *ray, int x);
void	draw_scene(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		key_press(t_data *info);
int		key_dir_on(int key, t_data *data);
int		key_dir_off(int key, t_data *data);
void	mouse_move(t_data *data);
void	mini_map(t_data *data);

void    *check_sound(void *d);

#endif