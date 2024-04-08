/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:46:48 by aogbi             #+#    #+#             */
/*   Updated: 2023/11/21 23:03:57 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *nptr);

void				*ft_bzero(void *ptr, size_t num);

void				*ft_calloc(size_t num_elements, size_t element_size);

int					ft_isalnum(int c);

int					ft_isalpha(int c);

int					ft_isascii(int c);

int					ft_isdigit(int c);

int					ft_isprint(int c);

char				*ft_itoa(int n);

void				*ft_memchr(const void *ptr, int value, size_t num);

int					ft_memcmp(const void *ptr1, const void *ptr2, size_t num);

void				*ft_memcpy(void *dest, const void *src, size_t n);

void				*ft_memmove(void *dest, const void *src, size_t n);

void				*ft_memset(void *ptr, int value, size_t num);

void				ft_putchar_fd(char c, int fd);

void				ft_putstr_fd(char *s, int fd);

char				**ft_split(char const *s, char c);

char				*ft_strchr(const char *str, int character);

char				*ft_strdup(const char *src);

void				ft_striteri(char *s, void (*f)(unsigned int, char *));

char				*ft_strjoin(char const *s1, char const *s2);

size_t				ft_strlcat(char *dest, const char *src, size_t size);

size_t				ft_strlcpy(char *dest, const char *src, size_t size);

size_t				ft_strlen(const char *str);

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int					ft_strncmp(const char *str1, const char *str2, size_t n);

char				*ft_strrchr(const char *str, int character);

char				*ft_strtrim(char const *s1, char const *set);

char				*ft_substr(char const *s, unsigned int start, size_t len);

int					ft_tolower(int c);

int					ft_toupper(int c);

void				ft_putendl_fd(char *s, int fd);

void				ft_putnbr_fd(int n, int fd);

char				*ft_strcpy(char *dst, const char *src);

char				*ft_strnstr(const char *big, const char *little,
						size_t len);

t_list				*ft_lstnew(void *content);

void				ft_lstadd_front(t_list **lst, t_list *new);

int					ft_lstsize(t_list *lst);

t_list				*ft_lstlast(t_list *lst);

void				ft_lstadd_back(t_list **lst, t_list *new);

void				ft_lstdelone(t_list *lst, void (*del)(void *));

void				ft_lstclear(t_list **lst, void (*del)(void *));

void				ft_lstiter(t_list *lst, void (*f)(void *));

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif
