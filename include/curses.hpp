#ifndef DA_CURSES_HPP
#define DA_CURSES_HPP

#include <curses.h>
#include <unistd.h>

#include <DA/bit.hpp>
#include <DA/exception.hpp>

#include <DA/curses/stream.hpp>

namespace DA
{
namespace curses
{
using ::sleep;
using ::usleep;
using ::echo;
using ::noecho;
using ::cbreak;
using ::nocbreak;
using ::nl;
using ::nonl;
using ::raw;
using ::noraw;
namespace init_mode
{
typedef unsigned long mode_t;
const mode_t echo = 0x1;
const mode_t cbreak = 0x2;
const mode_t newline = 0x4;
const mode_t keypad = 0x8;
const mode_t raw = 0x10;
}
static void init(init_mode::mode_t mode = init_mode::cbreak | init_mode::keypad)

try
{
	using ::DA::bit::look;

	if (!::initscr())
		DA_THROW_EXCEPTION_1("initscr error");

	{
		if (look(mode, init_mode::echo))
		{
			if (echo())
				DA_THROW_EXCEPTION_1("set echo error");
		}
		else
		{
			if (noecho())
				DA_THROW_EXCEPTION_1("set noecho error");
		}

		if (look(mode, init_mode::cbreak))
		{
			if (cbreak())
				DA_THROW_EXCEPTION_1("set cbreak error");
		}
		else
		{
			if (nocbreak())
				DA_THROW_EXCEPTION_1("set nocbreak error");
		}

		if (look(mode, init_mode::newline))
		{
			if (nl())
				DA_THROW_EXCEPTION_1("set newline error");
		}
		else
		{
			if (nonl())
				DA_THROW_EXCEPTION_1("set nonl error");
		}

		stdwin().keypad(look(mode, init_mode::keypad));

		if (look(mode, init_mode::raw))
		{
			if (raw())
				DA_THROW_EXCEPTION_1("set newline error");
		}
		else
		{
			if (noraw())
				DA_THROW_EXCEPTION_1("set nonl error");
		}
	}

	if (::refresh())
		DA_THROW_EXCEPTION_1("refresh error");
}

DA_CATCH_EXCEPTION
} //namespace curses
} //namespace DA

#endif
