/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:56:45 by anorjen           #+#    #+#             */
/*   Updated: 2020/07/14 20:22:37 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

#define L_ENDIAN 0
#define B_ENDIAN 1

int		endian()
{
	uint32_t	i = 1;
	uint8_t	*p = (uint8_t*)(&i);

	if (*p == 1)
		return L_ENDIAN;
	else
		return B_ENDIAN;
}

void*		input;
uint64_t	saved_length;
uint8_t*	end;

uint32_t	a;
uint32_t	b;
uint32_t	c;
uint32_t	d;
uint32_t	block[16];

const uint32_t	t[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

const uint32_t	s[64] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

void		append_padding_bits() {
    end = (uint8_t*)(input) + saved_length;
    *end = 0x80;
    ++end;

    while ((end - (uint8_t*)(input)) % 64 != 56)
        *end = 0x00, ++end;
}

void		ft_swap(uint8_t *one, uint8_t *two)
{
	uint8_t	buf;

	buf = *one;
	*one = *two;
	*two = buf;
}

void		append_length() {
    uint64_t length = saved_length * 8;
    memcpy((void*)(end), &length, 8);

    if (endian() == B_ENDIAN) {
        ft_swap(end, end + 7);
        ft_swap(end + 1, end + 6);
        ft_swap(end + 2, end + 5);
        ft_swap(end + 3, end + 4);
    }

    end += 8;
}

void		init_buffer() {
    uint8_t _a[4] = { 0x01, 0x23, 0x45, 0x67 };
    uint8_t _b[4] = { 0x89, 0xab, 0xcd, 0xef };
    uint8_t _c[4] = { 0xfe, 0xdc, 0xba, 0x98 };
    uint8_t _d[4] = { 0x76, 0x54, 0x32, 0x10 };

    a = *(uint32_t*)(&_a);
    b = *(uint32_t*)(&_b);
    c = *(uint32_t*)(&_c);
    d = *(uint32_t*)(&_d);
}

uint32_t	rotate_left(uint32_t x, uint32_t s)
{
	return (x << s) | (x >> (32 - s));
}

uint32_t	F(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) | (~x & z);
}

uint32_t	G(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & z) | (~z & y);
}

uint32_t	H(uint32_t x, uint32_t y, uint32_t z)
{
	return x ^ y ^ z;
}

uint32_t	I(uint32_t x, uint32_t y, uint32_t z)
{
	return y ^ (~z | x);
}

void		ft_round(uint32_t *a, uint32_t b, uint32_t c, uint32_t d, uint32_t k, uint32_t s, uint32_t i, uint32_t(*function)(uint32_t, uint32_t, uint32_t)) {
    *a += function(b, c, d) + block[k] + t[i];
    *a = rotate_left(*a, s);
    *a += b;
}

void		process_block(uint8_t* adress) {
    uint32_t	aa;
	uint32_t	bb;
	uint32_t	cc;
	uint32_t	dd;

	memcpy(&block, (void*)(adress), 64);
	aa = a;
	bb = b;
	cc = c;
	dd = d;
    // ft_round(&a, b, c, d, 0, 7, 1, F);
    // ft_round(&d, a, b, c, 1, 12, 2, F);
    // ft_round(&c, d, a, b, 2, 17, 3, F);
    // ft_round(&b, c, d, a, 3, 22, 4, F);

    // ft_round(&a, b, c, d, 4, 7, 5, F);
    // ft_round(&d, a, b, c, 5, 12, 6, F);
    // ft_round(&c, d, a, b, 6, 17, 7, F);
    // ft_round(&b, c, d, a, 7, 22, 8, F);

    // ft_round(&a, b, c, d, 8, 7, 9, F);
    // ft_round(&d, a, b, c, 9, 12, 10, F);
    // ft_round(&c, d, a, b, 10, 17, 11, F);
    // ft_round(&b, c, d, a, 11, 22, 12, F);

    // ft_round(&a, b, c, d, 12, 7, 13, F);
    // ft_round(&d, a, b, c, 13, 12, 14, F);
    // ft_round(&c, d, a, b, 14, 17, 15, F);
    // ft_round(&b, c, d, a, 15, 22, 16, F);

    // ft_round(&a, b, c, d, 1, 5, 17, G);
    // ft_round(&d, a, b, c, 6, 9, 18, G);
    // ft_round(&c, d, a, b, 11, 14, 19, G);
    // ft_round(&b, c, d, a, 0, 20, 20, G);

    // ft_round(&a, b, c, d, 5, 5, 21, G);
    // ft_round(&d, a, b, c, 10, 9, 22, G);
    // ft_round(&c, d, a, b, 15, 14, 23, G);
    // ft_round(&b, c, d, a, 4, 20, 24, G);

    // ft_round(&a, b, c, d, 9, 5, 25, G);
    // ft_round(&d, a, b, c, 14, 9, 26, G);
    // ft_round(&c, d, a, b, 3, 14, 27, G);
    // ft_round(&b, c, d, a, 8, 20, 28, G);

    // ft_round(&a, b, c, d, 13, 5, 29, G);
    // ft_round(&d, a, b, c, 2, 9, 30, G);
    // ft_round(&c, d, a, b, 7, 14, 31, G);
    // ft_round(&b, c, d, a, 12, 20, 32, G);

    // ft_round(&a, b, c, d, 5, 4, 33, H);
    // ft_round(&d, a, b, c, 8, 11, 34, H);
    // ft_round(&c, d, a, b, 11, 16, 35, H);
    // ft_round(&b, c, d, a, 14, 23, 36, H);

    // ft_round(&a, b, c, d, 1, 4, 37, H);
    // ft_round(&d, a, b, c, 4, 11, 38, H);
    // ft_round(&c, d, a, b, 7, 16, 39, H);
    // ft_round(&b, c, d, a, 10, 23, 40, H);

    // ft_round(&a, b, c, d, 13, 4, 41, H);
    // ft_round(&d, a, b, c, 0, 11, 42, H);
    // ft_round(&c, d, a, b, 3, 16, 43, H);
    // ft_round(&b, c, d, a, 6, 23, 44, H);

    // ft_round(&a, b, c, d, 9, 4, 45, H);
    // ft_round(&d, a, b, c, 12, 11, 46, H);
    // ft_round(&c, d, a, b, 15, 16, 47, H);
    // ft_round(&b, c, d, a, 2, 23, 48, H);

    // ft_round(&a, b, c, d, 0, 6, 49, I);
    // ft_round(&d, a, b, c, 7, 10, 50, I);
    // ft_round(&c, d, a, b, 14, 15, 51, I);
    // ft_round(&b, c, d, a, 5, 21, 52, I);

    // ft_round(&a, b, c, d, 12, 6, 53, I);
    // ft_round(&d, a, b, c, 3, 10, 54, I);
    // ft_round(&c, d, a, b, 10, 15, 55, I);
    // ft_round(&b, c, d, a, 1, 21, 56, I);

    // ft_round(&a, b, c, d, 8, 6, 57, I);
    // ft_round(&d, a, b, c, 15, 10, 58, I);
    // ft_round(&c, d, a, b, 6, 15, 59, I);
    // ft_round(&b, c, d, a, 13, 21, 60, I);

    // ft_round(&a, b, c, d, 4, 6, 61, I);
    // ft_round(&d, a, b, c, 11, 10, 62, I);
    // ft_round(&c, d, a, b, 2, 15, 63, I);
    // ft_round(&b, c, d, a, 9, 21, 64, I);

	ssize_t	i;

	i = 0;
	while (i < 64)
	{
		uint32_t	F;
		uint8_t		g;

		F = 0;
		g = 0;
		if (i >= 0 && i < 16)
		{
			F = (bb & cc) | (~bb & dd);
			g = i;
		}
		else if (i >= 16 && i < 32)
		{
			F = (dd & bb) | (~dd & cc);
			g = (5 * i + 1) % 16;
		}
		else if (i >= 32 && i < 48)
		{
			F = bb ^ cc ^ dd;
			g = (3 * i + 5) % 16;
		}
		else if (i >= 48 && i < 64)
		{
			F = cc ^ (bb | ~dd);
			g = (7 * i) % 16;
		}
		F = F + aa + t[i] + block[g];
		aa = dd;
		dd = cc;
		cc = bb;
		bb = bb + rotate_left(F, s[i]);
		++i;
	}

	// for i from 0 to 63
    //     var int F, g
    //     if 0 ≤ i ≤ 15 then
    //         F := (B and C) or ((not B) and D)
    //         g := i
    //     else if 16 ≤ i ≤ 31 then
    //         F := (D and B) or ((not D) and C)
    //         g := (5×i + 1) mod 16
    //     else if 32 ≤ i ≤ 47 then
    //         F := B xor C xor D
    //         g := (3×i + 5) mod 16
    //     else if 48 ≤ i ≤ 63 then
    //         F := C xor (B or (not D))
    //         g := (7×i) mod 16
    //     //Be wary of the below definitions of a,b,c,d
    //     F := F + A + K[i] + M[g]
    //     A := D
    //     D := C
    //     C := B
    //     B := B + leftrotate(F, s[i])
    // end for

    a += aa;
	b += bb;
	c += cc;
	d += dd;
}

void		process()
{
	uint8_t*	temp;

	temp = (uint8_t*)(input);
	while (temp != end)
	{
		process_block(temp);
		temp += 64;
	}
}

uint8_t		*finish()
{
    uint8_t	*hash;

	hash = (uint8_t*)malloc(16);
    memcpy(&hash[0], &a, 4);
    memcpy(&hash[4], &b, 4);
    memcpy(&hash[8], &c, 4);
    memcpy(&hash[12], &d, 4);
    return hash;
}

uint8_t		*MD5(void* original_input, uint64_t size)
{
    uint8_t	*place;

	place = (uint8_t*)malloc(size + 100);
    memcpy((void*)(place), original_input, size);
    input = (void*)(place);
    saved_length = size;
    append_padding_bits();
    append_length();
    init_buffer();
    process();
    free(place);
    return finish();
}

char		*md5hash_to_string(uint8_t *hash) {
    char	*hex_char = "0123456789abcdef";
    char	*ret;
	size_t	j;

	j = 0;
	ret = (char *)malloc(sizeof(char) * 32);
    for (int i = 0; i < 16; ++i) {
        ret[j++] = hex_char[hash[i] >> 4];
        ret[j++] = hex_char[hash[i] & 0x0F];
    }
	ret[j] = '\0';
    return ret;
}

int			main() {
	//#define test_speed

	#ifndef test_speed
		char	*s;
		char	*hash;

		while (1)
		{
			write(1, "Input: ", 7);
			get_next_line(0, &s);
			write(1, "Hash: ", 7);
			hash = md5hash_to_string(MD5(&s[0], ft_strlen(s)));
			write(1, hash, ft_strlen(hash));
			write(1, "\n", 1);
		}
	#else
		int arr[500];
		int counter = 0;
		int start = clock();
		while(clock() - start < 1000)
			MD5(&arr[counter%500], 7), counter++;
		std::cout << counter;
	#endif

	return 0;
}



// int	main(int ac, char **av)
// {
// 	char	*hash;

// 	if (ac == 2)
// 	{
// 		hash = main_loop(av[1]);
// 	}
// 	print_hash(hash);
// 	return (0);
// }
