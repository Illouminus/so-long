/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edouard <edouard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 12:17:55 by edouard           #+#    #+#             */
/*   Updated: 2024/01/21 20:36:25 by edouard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 5
#endif

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *get_next_line(int fd);

char *read_and_store(int fd, char **buffer);

char *extract_line(char **buffer);

void *ft_calloc(size_t nmemb, size_t size);

void ft_bzero(void *s, size_t n);

char *ft_strjoin(char const *s1, char const *s2);

char *ft_strdup(const char *s1);

char *ft_substr(char const *s, unsigned int start, size_t len);

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);

char *ft_strchr(const char *s, int c);

#endif