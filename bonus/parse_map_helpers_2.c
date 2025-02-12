/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_helpers_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:31:39 by dantoine          #+#    #+#             */
/*   Updated: 2025/02/11 22:50:14 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d_bonus.h"

char	*error_extra_lines(char *cur_line, char *all_lines)
{
	free(cur_line);
	free(all_lines);
	get_next_line(-1);
	printf("Error: Extra lines found after the map.\n");
	return (NULL);
}

char	*handle_map_line(char *cur_line, char *all_lines, t_map_info *map_info)
{
	if (map_info->map_ended)
	{
		printf("Error: Extra lines found after the map.\n");
		return (NULL);
	}
	if (!map_info->map_started)
		map_info->map_started = 1;
	if (is_valid_map_line(cur_line))
	{
		map_info->last_valid_line_found = 1;
		return (process_map_lines(cur_line, all_lines));
	}
	else if (map_info->last_valid_line_found)
	{
		printf("Error: Invalid line after map content.\n");
		return (NULL);
	}
	return (NULL);
}

char	*handle_file_open(char *map, int fd)
{
	char	*result;

	if (fd < 0)
		return (NULL);
	result = parse_map_read_prep(map);
	if (!result)
	{
		cleanup_gnl(fd);
		close(fd);
	}
	return (result);
}
