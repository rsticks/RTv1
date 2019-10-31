/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <daron@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:55:27 by daron             #+#    #+#             */
/*   Updated: 2019/10/31 14:21:01 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static char		*ft_getbuf(char *scene_name, int *line_count)
{
	int		fd;
	char	*buf;
	char	*line;

	buf = ft_strnew(1);
	if ((fd = open(scene_name, O_RDONLY)) == -1)
		kill_all("Can't open file <ft_getbuf>");
	while (get_next_line(fd, &line) > 0 && (*line_count)++ > -1)
		buf = ft_strjoin_del(buf, ft_strjoin_del(line, "\n", 'L'), 'B');
	if (close(fd) == -1)
		kill_all("Can't close file <ft_getbuf>");
	return (buf);
}

static char		**ft_getscene(char *buf, int line_count, int j)
{
	int		ind;
	int		k;
	char	**scene;

	k = 0;
	if (!buf)
		return (NULL);
	if (!(scene = (char **)malloc(sizeof(char *) * (line_count + 1))))
		kill_all("Can't create scene mass <ft_getscene>");
	while (buf[k] != '\0' && j < line_count)
	{
		ind = 0;
		if (!(scene[j] = (char *)malloc(sizeof(char) * ft_linelen(buf, k))))
			kill_all("Can't malloc memory for scene <ft_getscene>");
		while (buf[k] != '\n' && buf[k] != '\0')
			scene[j][ind++] = buf[k++];
		scene[j][ind] = '\0';
		k++;
		j++;
	}
	free(buf);
	return (scene);
}

void scene_parser(t_sdl *sdl, char *scene_name)
{
	char *buf;

	sdl->line_count = 0;

	buf = ft_getbuf(scene_name, &(sdl->line_count));
	//printf("%s", buf);

	sdl->scene = ft_getscene(buf, sdl->line_count, 0);
	/*int ind;

	ind = 0;
	while (ind < sdl->line_count)
	{
		printf("%s\n", sdl->scene[ind]);
		ind++;
	}
	*/

	sdl->obj_num = 0;
	sdl->obj_counter = 0;
	sdl->light_num = 0;
	sdl->light_counter = 0;

	sdl->obj = NULL;
	sdl->light = NULL;

	sdl->ambient = 0;

	string_parser(sdl);

}