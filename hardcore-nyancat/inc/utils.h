/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyancat         <inyancat@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created  2016/11/11 16:22:51 by inyancat          #+#    #+#             */
/*   Updated  2016/11/12 20:18:11 by inyancat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wchar.h>
#include <stdbool.h>
#include "ascii.h"

#pragma clang diagnostic ignored "-Wlanguage-extension-token"

//////////////////////////////////STRING TESTS//////////////////////////////////

//no bench
# define HP_TIMING_AVAIL 0
# define ITERATIONS 100000

# define CHAR char
# define UCHAR unsigned char

# define SMALL_CHAR 127
# define sfmt "s"
# define BIG_CHAR CHAR_MAX
# define STRCMP strcmp
# define MEMCMP memcmp
# define MEMSET memset
# define STRCPY strcpy
# define STRCMP strcmp
# define STRLEN strlen
# define MEMCPY memcpy
# define STREQ(a, b)	(strcmp((a), (b)) == 0)
# define CHARBYTES 1
# define CHARBYTESLOG 0
# define CHARALIGN 1
# define MIDCHAR 0x7f
# define LARGECHAR 0xfe
# define CHAR__MAX CHAR_MAX
# define CHAR__MIN CHAR_MIN

# define BUF1PAGES 1

#define IMPL(name, test) \
	impl_t tst_ ## name	= { __STRING (name), (void (*) (void))name, test }; \
	__start_impls[__i++] = tst_ ## name;

#define CALL(impl, ...)	\
	  (* (proto_t) (impl)->fn) (__VA_ARGS__)

#define INIT() __start_impls = malloc(sizeof(impl_t) * 10);

typedef struct
{
	const char *name;
	void (*fn) (void);
	long test;
} impl_t;

static impl_t			*__start_impls;
static int				__i;

extern unsigned char	*buf1, *buf2;
extern int				ret, do_srandom;
extern unsigned int		seed;
extern size_t			page_size;
extern char				*it;
extern int				errors;

# define OPT_ITERATIONS 10000
# define OPT_RANDOM 10001
# define OPT_SEED 10002
# define TEST_FUNCTION test_main()

#define FOR_EACH_IMPL(impl, notall) \
	for (impl_t *impl = __start_impls; impl < __start_impls + __i; ++impl)	\
    	if (!notall || impl->test)

void	test_init();
void	error(int code, int a, const char *pattern, ...);

int		test_main_strcmp(void *fun);
int		test_main_strcpy(void *fun);

void	check (int thing, int number);
void	equal (const char *a, const char *b, int number);

void	ncurses_init();
void	ncurses_deinit();
void	write_result(char *fun_name, bool succeed);
void	ncurses_loop(void);
