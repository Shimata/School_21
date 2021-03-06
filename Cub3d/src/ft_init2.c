/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquinoa <wquinoa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 13:35:08 by wquinoa           #+#    #+#             */
/*   Updated: 2020/07/03 17:45:28 by wquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		ft_draw_scene(t_game *g, t_frame *f, t_window *w)
{
	f->img = mlx_new_image(w->mlx, w->width, w->height);
	f->addr = mlx_get_data_addr(f->img, &f->bpp, &f->line_l, &f->en);
	ft_cast_ray(g, g->plr);
	if (g->sprites)
	{
		g->items = 0;
		ft_add_sprite(g->sprites, g);
	}
	(g->flags & sav_f) ? ft_bmp(g, f) : 0;
	mlx_put_image_to_window(w->mlx, w->win, f->img, 0, 0);
	mlx_destroy_image(w->mlx, f->img);
}

static void	ft_fill_tab(t_game *g, t_frame ****tap, char ***lnk)
{
	t_frame	***tab;
	char	**link;

	tab = *tap;
	link = *lnk;
	tab[0] = &g->no;
	tab[1] = &g->so;
	tab[2] = &g->ea;
	tab[3] = &g->we;
	tab[4] = &g->sp;
	link[0] = g->txr->no;
	link[1] = g->txr->so;
	link[2] = g->txr->ea;
	link[3] = g->txr->we;
	link[4] = g->txr->sp;
}

static void	ft_load_textures(t_game *g)
{
	t_frame	*tex;
	t_frame	***tab;
	char	**ln;
	int8_t	i;

	i = 0;
	if (!(tab = (t_frame***)malloc(sizeof(t_frame**) * 5)))
		ft_errors(bad_malloc);
	!(ln = (char**)malloc(sizeof(char*) * 5)) ? ft_errors(bad_malloc) : 0;
	ft_fill_tab(g, &tab, &ln);
	while (i < 5)
	{
		if (!(tex = (t_frame *)malloc(sizeof(t_frame))))
			ft_errors(bad_malloc);
		if (!(tex->img = mlx_xpm_file_to_image(g->wnd->mlx, ln[i], &tex->width,
		&tex->height)))
			ft_errors(bad_tex);
		free(ln[i]);
		tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_l,
		&tex->en);
		*tab[i] = tex;
		i++;
	}
	free(ln);
	free(tab);
}

static void	ft_init2(char *av, int save)
{
	t_game				scene;
	static t_window		win;
	static t_texture	texture;
	static t_player		player;
	static t_frame		f;

	ft_bzero(&scene, sizeof(scene));
	scene.wnd = &win;
	scene.txr = &texture;
	scene.plr = &player;
	scene.frm = &f;
	scene.map = ft_read_map(0, 0, &scene, av);
	win.height <= 0 ? ft_errors(bad_res) : 0;
	scene.flags = (save == 3) ? 32 : 0;
	scene.sprites = ft_init_sprites(scene.map);
	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, win.width, win.height, av);
	ft_minimap(&scene);
	ft_load_textures(&scene);
	ft_draw_scene(&scene, &f, &win);
	mlx_hook(win.win, 17, (1L << 5), &ft_exit, NULL);
	mlx_hook(win.win, 2, (1L << 0), &key_press, &scene);
	mlx_mouse_show();
	mlx_loop(win.mlx);
}

void		ft_init(char **av, int ac)
{
	int i;

	i = 0;
	if (ac >= 2)
	{
		while (av[1][i])
			i++;
		if (ft_strncmp(&av[1][i - 4], ".cub", 4))
			ft_errors(bad_map);
	}
	if (ac == 3)
	{
		while (ft_isspace(*av[2]))
			av[2]++;
		if (ft_strncmp(av[2], "--save", 6))
			ft_errors(bad_args);
	}
	if (ac > 3)
		ft_errors(bad_args);
	ft_init2(av[1], ac);
}
