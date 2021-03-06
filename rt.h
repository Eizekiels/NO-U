/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:04:26 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/28 18:32:19 by mguyout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define WIN_LEN 640
# define WIN_HEIGHT 480
# define PLN_DST 100
# define EPS 0.0001
# define ANTIALIA 30
# define MAX 9999
# define AMB 0.2

# define SPH 1
# define PLN 2
# define CON 3
# define CYL 4
# define CUB 5
# define ELL 6

# include "libft/includes/libft.h"
# include "SDL2.framework/Headers/SDL.h"
# include <math.h>

typedef	struct			s_material
{
	double				r;
	double				g;
	double				b;
}						t_material;

typedef	struct			s_coo
{
	double				x;
	double				y;
	double				z;
}						t_coo;

typedef	struct			s_data
{
	unsigned int		*image_int;
	unsigned int		*image_base;
	SDL_Window			*sdl_window;
	SDL_Renderer		*sdl_renderer;
	SDL_Texture			*sdl_texture;
}						t_data;

typedef	struct			s_plane
{
	t_material			*color;
	t_coo				norm;
	t_coo				o;
	double				supp;
	double				reflex;
	int					id;
	int					cut;
	struct s_plane		*next;
}						t_plane;

typedef struct			s_cylinder
{
	t_coo				o;
	t_coo				rot;
	t_coo				dir;
	t_plane				*pln;
	double				radius;
	double				reflex;
	double				shine;
	t_material			*color;
	int					id;
	struct s_cylinder	*next;
}						t_cylinder;

typedef	struct			s_cone
{
	t_coo				o;
	t_coo				dir;
	t_coo				rot;
	t_plane				*pln;
	double				angle;
	double				reflex;
	double				shine;
	int					id;
	t_material			*color;
	struct s_cone		*next;
}						t_cone;

typedef	struct			s_sphere
{
	t_coo				o;
	t_coo				dir;
	t_coo				rot;
	double				radius;
	double				reflex;
	t_material			*color;
	t_plane				*pln;
	double				shine;
	int					id;
	struct s_sphere		*next;
}						t_sphere;

typedef	struct			s_ellipse
{
	t_coo				o;
	t_coo				dir;
	t_coo				rot;
	t_coo				rad1;
	t_coo				rad2;
	t_coo				rad3;
	t_material			*color;
	t_plane				*pln;
	double				shine;
	double				reflex;
	int					id;
	struct s_ellipse	*next;
}						t_ellipse;

typedef	struct			s_cube
{
	t_material			*color;
	double				radius;
	t_coo				dir;
	t_coo				o;
	t_coo				a;
	t_coo				u;
	t_coo				v;
	double				shine;
	double				reflex;
	t_coo				rot;
	int					id;
	struct s_cube		*next;
}						t_cube;

typedef struct			s_light
{
	t_coo				o;
	t_material			*color;
	double				power;
	double				shine;
	double				amb;
	int					id;
	struct s_light		*next;
}						t_light;

typedef	struct			s_ray
{
	t_coo				o;
	t_coo				dir;
	t_coo				obj;
}						t_ray;

typedef	struct			s_cam
{
	t_coo				pos;
	t_coo				forw;
	t_coo				up;
	t_coo				right;
	t_coo				rot;
}						t_cam;

typedef	struct			s_view
{
	double				screen_ratio;
	double				height;
	double				length;
	t_coo				up_left;
}						t_view;

typedef	struct			s_inter
{
	double				dst;
	t_material			*mat;
	t_material			*col;
	t_material			*kdif;
	t_material			*kspe;
	t_ray				*angle;
	t_coo				point;
	int					obj;
	int					num;
	double				reflex;
}						t_inter;

typedef	struct			s_start
{
	t_sphere			*sph;
	t_plane				*pln;
	t_cone				*con;
	t_cylinder			*cyl;
	t_cube				*cub;
	t_ellipse			*ell;
	t_light				*lgh;
}						t_start;

typedef	struct			s_options
{
	int					sepia;
	int					blwh;
	int					maintain;
	int					aa;
	int					obj;
	int					id;
	int					cam_move;
}						t_options;

typedef	struct			s_rt
{
	t_data				*data;
	t_ray				*ray;
	t_cam				*cam;
	t_light				*light;
	t_sphere			*sphere;
	t_plane				*plane;
	t_cone				*cone;
	t_cylinder			*cylinder;
	t_cube				*cube;
	t_ellipse			*ellipse;
	t_view				*view;
	t_ray				*light_ray;
	t_inter				*inter;
	t_start				*start;
	t_options			*op;
	int					depth;
	t_coo				tmp;
}						t_rt;

void					ft_malloc_error(void);
void					ft_bad_arg(int i);
void					ft_exit(void);

void					ft_ini(t_rt *rt);
void					ft_create(t_rt *rt);
void					parser(t_rt *rt, char *file);
int						ft_check_obj(char *str, int fd, t_rt *rt);
void					check_forms(t_rt *rt, int type);
void					ft_reset(t_rt *rt);
t_coo					get_coo(char **str, int err);
t_material				*get_color(char **str);
double					get_radius(char **str);

int						my_key_press(t_rt *rt, SDL_Keysym key);
int						ft_exit_cross(t_rt *rt);
void					put_pxl(t_data *data, int x, int y, t_material *color);
void					put_pxl_base(t_data *data, int x, int y,
						t_material *color);

void					ft_raytracing(t_rt *rt);
void					ft_check_object(t_rt *rt);

t_coo					ft_new_vect(float x, float y, float z);
t_coo					ft_add_vect(t_coo vect1, t_coo vect2);
t_coo					ft_div_vect(double i, t_coo vect);
t_coo					ft_mult_vect(double i, t_coo vect);
t_coo					ft_sub_vect(t_coo vect1, t_coo vect2);

double					scal(t_coo vect1, t_coo vect2);
double					ft_dst(t_coo point1, t_coo point2);
double					ft_norme(t_coo vect);
t_coo					ft_normalize(t_coo vect);
double					disc_eq(double t1, double t2);

double					ft_check_sphere(t_sphere *sphere, t_ray *ray);
void					check_sphere_inter(t_rt *rt, int type);
void					ft_ini_sphere(t_rt *rt);
int						ft_add_sphere(int fd, t_rt *rt, int id);

void					check_plane_inter(t_rt *rt, int type);
double					ft_check_plane(t_plane *plane, t_ray *ray);
void					ft_ini_plane(t_rt *rt);
int						ft_add_plane(int fd, t_rt *rt, int id);

void					check_cone_inter(t_rt *rt, int type);
double					ft_check_cone(t_cone *cone, t_ray *ray);
int						ft_add_cone(int fd, t_rt *rt, int id);

int						ft_add_cylinder(int fd, t_rt *rt, int id);
void					check_cylinder_inter(t_rt *rt, int type);

int						ft_add_light(int fd, t_rt *rt, int id);

int						ft_add_cam(int fd, t_rt *rt);

void					ft_get_point(t_rt *rt);

t_coo					ft_rotation(t_coo vect, t_coo rot);
void					make_rot(t_rt *rt);

t_coo					ft_det_vect(t_coo vect1, t_coo vect2);
void					check_cube_inter(t_rt *rt, int type);
int						ft_add_cube(int fd, t_rt *rt, int id);

void					aliasing(t_rt *rt);
void					ft_ray(t_rt *rt, int x, int y, int type);
void					ft_ini_ray(t_rt *rt, double x, double y);

double					ft_inter_plane_ini(t_ray *ray, t_plane *pln, double t1, double t2);
//double					ft_inter_plane_obj(t_plane *pln, double dc, double t,
//						double t1, double t2);

void					check_ellipse_inter(t_rt *rt, int type);
int						ft_add_ellipse(int fd, t_rt *rt, int id);

t_material				hex_rgb(int col);
unsigned int			col_hexa(int r, int g, int b);
void					ft_check_expose(t_material *mat, double max);

void					sepia(t_rt *rt);
void					bl_wh(t_rt *rt);
void					cpy_image(unsigned int *tab1, unsigned int *tab2);

void					move_object(t_rt *rt, SDL_Event ev);
void					get_obj(t_rt *rt, int x, int y);
void					move_camera(t_rt *rt, SDL_Event ev);
t_coo					ft_inv_rot(t_coo vect, t_coo rot);
void					move_color(t_material *c, double r, double g, double b);
t_coo					ft_reflexion(t_rt *rt);
void					ft_reflexion_ray(t_rt *rt);
void					ft_get_light(t_rt *rt);
void					reflexion_depth(t_rt *rt);
#endif
