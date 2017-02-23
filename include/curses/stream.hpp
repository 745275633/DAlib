#ifndef DA_CURSES_STREAM_HPP
#define DA_CURSES_STREAM_HPP

#include <iostream>
#include <streambuf>

#include <DA/curses/window.hpp>

namespace DA
{
namespace curses
{
class ostreambuf : public ::std::streambuf
{
private:
	window win_;
public:
	ostreambuf(window &win): win_(win) {}
	~ostreambuf()
	{
		sync();
	}
protected:
	virtual int_type overflow(int_type c)
	{
		if (c != EOF)
		{
			if (!win_.put(c))
				return EOF;
		}

		return c;
	}

	int sync()

	try
	{
		win_.refresh();
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}; //class ostreambuf
/*
class ostream : public std::ostream
{
protected:
	ostreambuf buf;
public:
	ostream(window &win): ::std::ostream(0), buf(win)
	{
		rdbuf(&buf);
	}
}; //class ostream
*/

class istreambuf : public ::std::streambuf
{
private:
	window win_;
public:
	istreambuf(window &win): win_(win) {};
	virtual int_type underflow()
	{
		int_type c;

		if ((c = win_.get(true)) != -1)
			return c;
		else
			return EOF;
	}
	virtual int_type uflow()
	{
		int_type c;

		if ((c = win_.get()) != -1)
			return c;
		else
			return EOF;
	}
}; //class istreambuf
/*
class istream : public std::istream
{
protected:
	istreambuf buf;
public:
	istream(window &win): ::std::istream(0), buf(win)
	{
		rdbuf(&buf);
	}
}; //class ostream
*/
class streambuf : public ::std::streambuf
{
private:
	window win_;
protected:
	virtual int_type overflow(int_type c)
	{
		if (c != EOF)
		{
			if (!win_.put(c))
				return EOF;
		}

		return c;
	}

	int sync()

	try
	{
		win_.refresh();
		return 0;
	}
	catch (...)
	{
		return -1;
	}
public:
	streambuf(window &win): win_(win) {}
	~streambuf()
	{
		sync();
	}
	virtual int_type underflow()
	{
		int_type c;

		if ((c = win_.get(true)) != -1)
			return c;
		else
			return EOF;
	}
	virtual int_type uflow()
	{
		int_type c;

		if ((c = win_.get()) != -1)
			return c;
		else
			return EOF;
	}
}; //class streambuf

static ::std::ostream &winout()
{
	static ostreambuf buf_{ostreambuf{stdwin()}};
	static ::std::ostream cwinout_(&buf_);
	return cwinout_;
}
static ::std::istream &winin()
{
	static istreambuf buf_{istreambuf{stdwin()}};
	static ::std::istream cwinin_(&buf_);
	return cwinin_;
}

inline ::std::iostream &window::operator()()
{
	if (sm)
		return *sm;
	else
		return *(sm = ps(new ::std::iostream(new streambuf(*this))));
}
} //namespace curses
} //namespace DA
#endif
