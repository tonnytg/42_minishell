/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:43:27 by antthoma          #+#    #+#             */
/*   Updated: 2023/02/21 00:55:29 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int			ft_printf(const char *s, ...);
int			ft_choice(char c, int length, va_list args);
int			ft_get_char(va_list args);
int			ft_get_str(va_list args);
int			ft_get_int(va_list args);
int			ft_get_pointer(va_list args, char c);
int			ft_get_unsigned_to_ascii(va_list args);
int			ft_get_hex(va_list args, char c);
int			ft_isalpha(int c);
int			ft_isprint(int c);
int			ft_tolower(int c);
int			ft_isdigit(int c);
int			ft_toupper(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
char		*ft_strchr(const char *s, int c);
size_t		ft_strdump(const char *s);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_atoi(const char *nptr);
long int	ft_atol(const char *nptr);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(const char *s, const char *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
int			ft_putstr(char *str);
int			is_negative(int n);
int			ft_len_digits(unsigned int n);
int			ft_putchar_fd(int c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int			ft_pow(int a, int b);
char		*ft_unsigned_to_ascii(unsigned int n);
char		*ft_unsigned_to_hex(unsigned long long n, char flag);
size_t		ft_calc_size_base(unsigned long int n, int base);
int			ft_strisdigit(char *str);
int			max(int arr[], int len);
char		*ft_char_to_bit(int dec);
int			max_arrary(int *arr, int len);

/* Create for Minishell */
char		*ft_strpbrk(const char *str, const char *delim);
char		*ft_strtok(char *str, const char *delim, int tigger);

#endif
