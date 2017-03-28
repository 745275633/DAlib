#ifndef DA_CURSES_WINDOWS
#define DA_CURSES_WINDOWS

#include <curses.h>
#include <DA/exception.hpp>
#include <memory>

namespace DA
{
namespace curses
{
class window
{
protected:
	typedef WINDOW win_st;
	typedef ::std::shared_ptr<win_st> pw;
	pw win_;
private:
	int last_char = 0;
	typedef ::std::shared_ptr<::std::iostream> ps;
	ps sm;
public:
	static void delete_win(WINDOW *win)
	{
		if (win == ::stdscr)
		{
			endwin();
			return;
		}

		wclear(win);
		delwin(win);
	}
	window(int lines, int cols, int begy = 0, int begx = 0)
		: win_(pw(::newwin(lines, cols, begy, begx), delete_win))
	{}
	window(win_st *win, int lines, int cols, int begy = 0, int begx = 0)
		: win_(pw(::derwin(win, lines, cols, begy, begx), delete_win))
	{}
	window(const window &win, int lines, int cols, int begy = 0, int begx = 0)
		: win_(pw(::derwin(win.win_.get(), lines, cols, begy, begx), delete_win))
	{}
	window(pw win): win_(win) {}
	window(::std::auto_ptr<win_st> win): win_(pw(win.release())) {}
	window(::std::unique_ptr<win_st> &&win): win_(pw(win.release())) {}
	/*window(win_st *win): win_(pw(win))
	{
		win = std::null_ptr;
	}*/
	~window() = default;
	pw raw()
	{
		retuen win_;
	}
	bool put(char c)
	{
		return !::waddch(win_.get(), c);
	}
	int get(bool peek = false)
	{
		if (peek)
			return last_char;
		else
			return last_char =  ::wgetch(win_.get());
	}
	void keypad(bool on)
	{
		if (::keypad(win_.get(), on))
			DA_THROW_EXCEPTION_0();
	}
	void refresh()
	{
		if (::wrefresh(win_.get()))
			DA_THROW_EXCEPTION_0();
	}
	void clear()
	{
		if (::wclear(win_.get()))
			DA_THROW_EXCEPTION_0();
	}
	void move(int y, int x)
	{
		if (::wmove(win_.get(), y, x))
			DA_THROW_EXCEPTION_0();
	}
	::std::iostream &operator()();
	window &operator()(int y, int x)
	{
		move(y, x);
		return *this;
	}
}; //class window
static window &stdwin()
{
	static window win(::std::shared_ptr<WINDOW>(::stdscr));
	return win;
}
static window make_window(WINDOW *win)
{
	if (win == ::stdscr)
		return stdwin();

	WINDOW *tmp = win;
	win = 0;
	return window(::std::shared_ptr<WINDOW>(win));
}
} //namespace curses
} //namespace DA
#endif
