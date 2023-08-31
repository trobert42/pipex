/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:10:53 by cdine             #+#    #+#             */
/*   Updated: 2022/04/19 14:35:17 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		ft_strlen(const char *s);
char	*ft_cattoline(char *buff, char *line);
char	*ft_strdup(char *s, int src_len);
int		ft_isline(char *str);
void	ft_trim(char *buff, int ret, int fd);

#endif
