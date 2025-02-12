/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:58:29 by sanhwang          #+#    #+#             */
/*   Updated: 2025/02/11 14:56:16 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

t_map_info	*init_map_info(void)
{
	t_map_info	*map_info;

	map_info = malloc(sizeof(t_map_info));
	if (!map_info)
		return (NULL);
	map_info->config_count = 0;
	map_info->map_started = 0;
	map_info->last_valid_line_found = 0;
	map_info->map_ended = 0;
	return (map_info);
}

char	**parse_map(char *map)
{
	char	*all_lines;
	char	**split_lines;

	all_lines = parse_map_read(map);
	if (!all_lines)
		return (NULL);
	split_lines = ft_split(all_lines, '\n');
	free(all_lines);
	return (split_lines);
}

void	clean_and_close(int fd)
{
	cleanup_gnl(fd);
	close(fd);
}

char	*parse_map_read(char *map)
{
	int		fd;
	char	*all_lines;

	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		get_next_line(-1);
		exit_error("Error: cannot open file");
	}
	all_lines = handle_file_open(map, fd);
	if (!all_lines)
	{
		get_next_line(-1);
		clean_and_close(fd);
		return (NULL);
	}
	all_lines = read_map_lines(fd, all_lines);
	clean_and_close(fd);
	if (!all_lines)
	{
		get_next_line(-1);
		return (NULL);
	}
	return (all_lines);
}
