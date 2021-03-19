/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: presentcity <presentcity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:46:19 by pdrake            #+#    #+#             */
/*   Updated: 2020/12/27 13:18:47 by presentcity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

void	*ft_memset (void *dest, int c, size_t len);
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(int symbol);
char	*ft_toupper(char *bt);
int		ft_tolower(int bt);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_itoa(int n);
int		ft_strcmp(char *s1, char *s2);

#endif
