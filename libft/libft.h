/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:25:27 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/03/23 02:42:01 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

/*
**	libc functions
*/

void		*ft_memset(void *b, int c, size_t n);

void		ft_bzero(void *b, size_t n);

void		*ft_memcpy(void *s1, const void *s2, size_t n);

void		*ft_memccpy(void *s1, const void *s2, int c, size_t n);

void		*ft_memmove(void *s1, const void *s2, size_t n);

void		*ft_memchr(const void *s1, int c, size_t n);

int			ft_memcmp(const void *s1, const void *s2, size_t n);

size_t		ft_strlen(const char *s);

int			ft_isalpha(int c);

int			ft_isdigit(int c);

int			ft_isalnum(int c);

int			ft_isascii(int c);

int			ft_isprint(int c);

int			ft_toupper(int c);

int			ft_tolower(int c);

char		*ft_strchr(const char *s, int c);

char		*ft_strrchr(const char *s, int c);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

size_t		ft_strlcpy(char *dst, const char *src, size_t size);

size_t		ft_strlcat(char *dst, const char *src, size_t size);

char		*ft_strnstr(const char *s1, const char *s2, size_t n);

int			ft_atoi(const char *str);

void		*ft_calloc(size_t count, size_t size);

char		*ft_strdup(const char *s1);

/*
**	Additional functions
*/

char		*ft_substr(char const *s, unsigned int start, size_t len);

char		*ft_strjoin(char const *s1, char const *s2);

char		*ft_strtrim(char const *s1, char const *set);

char		**ft_split(char const *s, char c);

char		*ft_itoa(int n);

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void		ft_putchar_fd(char c, int fd);

void		ft_putstr_fd(char *s, int fd);

void		ft_putendl_fd(char *s, int fd);

void		ft_putnbr_fd(int n, int fd);

/*
**	Bonus functions
*/

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

t_list		*ft_lstnew(void *data);

void		*ft_lstadd_front(t_list **aslt, t_list *new);

int			ft_lstsize(t_list *lst);

t_list		*ft_lstlast(t_list *lst);

t_list		*ft_lstadd_back(t_list **alst, t_list *new);

void		*ft_lstdelone(t_list *lst, void (*del)(void *));

void		*ft_lstclear(t_list **lst, void (*del)(void *));

void		*ft_lstiter(t_list *lst, void (*f)(void *));

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
