#pragma once

#include <stdint.h>
#include <types.h>

static inline uint8 inportb(uint16 port)
{
	uint8 value;
	__asm__ __volatile__("inb %1, %0" : "=a"(value) : "dN"(port));
	return value;
}

static inline void outportb(uint16 port, uint8 data)
{
	__asm__ __volatile__("outb %1, %0" : : "dN"(port), "a"(data));
}