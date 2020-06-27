/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 18:20:40 by wquinoa           #+#    #+#             */
/*   Updated: 2020/06/14 21:45:37 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MAP_H
# define T_MAP_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "../minilibx_o/mlx.h"
# include "../minilibx_o/get_next_line.h"
# define HEIGHT 64
# define FISH 8
# define ROTATION 0.08
# define SQ(x) (x * x)

typedef unsigned short		t_uint16;
typedef unsigned long long	t_uint64;
typedef long long			t_int64;
typedef unsigned char		t_uint8;

enum					e_key
{
	esc = 53,
	w_key = 13,
	a_key = 0,
	s_key = 1,
	d_key = 2,
	c_key = 8,
	h_key = 4,
	m_key = 46,
	t_key = 17,
	r_key = 15,
	pl_key = 24,
	mi_key = 27,
	up = 126,
	dn = 125,
	lf = 123,
	rt = 124,
	alp = (255 << 24),
	red = (255 << 16),
	grn = (255 << 8),
	blu = 255,
	crt_f = 1,
	hal_f = 2,
	map_f = 4,
	tex_f = 8,
	ref_f = 16,
};

typedef struct 			s_player
{
	float				x;
	float				y;
	float				dir;
	float				fov;
	float				fov_2;
	float				deltaray;
	uint8_t				speed;
}						t_player;

typedef struct			s_texture
{
	char				*no;
	char				*so;
	char				*ea;
	char				*we;
	char				*sp;
	int					flr;
	int					ceil;
}						t_texture;

typedef struct			s_frame
{
	void				*img;
	char				*addr;
	int					bpp;
	int					line_l;
	int					en;
	uint8_t				scale;
	int					width;
	int					height;
}						t_frame;

typedef struct			s_window
{
	void				*mlx;
	void				*win;
	uint16_t			width;
	uint16_t			height;
	struct s_player		*player;
}						t_window;

typedef struct			s_trig
{
	float				cos_v;
	float				sin_v;
	float				cos_v_pi_2;
	float				sin_v_pi_2;
}						t_trig;

typedef struct			s_opt
{
	int					flag;
}						t_options;

typedef struct			s_game
{
	char				**map;
	struct s_frame		*frm;
	struct s_player		*plr;
	struct s_window		*wnd;
	struct s_texture	*txr;
	struct s_opt		*opt;
	uint16_t			x0;
	uint16_t			y0;
	uint16_t			ray;
	uint32_t			flags;
	t_frame				*tex;
	t_frame				*no;
	t_frame				*so;
	t_frame				*ea;
	t_frame				*we;
}						t_game;

char					**ft_read_map(uint16_t rows, uint16_t longest, t_game *g, char *av);
void					ft_minimap(t_game *g, t_frame *f);
void					ft_init_player(char dir, int x_pos, int y_pos, t_game *g);
void					ft_paint(t_frame *f, int x, int y, int color);
void					ft_mix(t_frame *f, int x, int y, int color);

#endif