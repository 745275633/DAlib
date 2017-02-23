/*!
 * \file DA/progress.hpp
 * \author 吞噬黑洞的数据（745275633）
 */
#ifndef DA_PROGRESS_HPP
#define DA_PROGRESS_HPP

#include <boost/noncopyable.hpp>
#include <boost/timer.hpp>
#include <boost/io/ios_state.hpp>
#include <boost/cstdint.hpp>  // for uintmax_t
#include <iostream>
#include <string>

namespace DA
{
//  progress_timer  ----------------------------------------------------------//
template<unsigned int N = 2>
class progress_timer : public boost::timer, private boost::noncopyable
{

public:
	explicit progress_timer(std::ostream &os = std::cout)
	// os is hint; implementation may ignore, particularly in embedded systems
		: boost::timer(), boost::noncopyable(), m_os(os)
	{
		static_assert(N <= 10, "N must <= 0");
	}
	~progress_timer()
	{
		//  A) Throwing an exception from a destructor is a Bad Thing.
		//  B) The progress_timer destructor does output which may throw.
		//  C) A progress_timer is usually not critical to the application.
		//  Therefore, wrap the I/O in a try block, catch and ignore all exceptions.
		try
		{
			// use istream instead of ios_base to workaround GNU problem (Greg Chicares)
			boost::io::ios_all_saver ias(m_os);
			m_os.setf(std::istream::fixed,
			          std::istream::floatfield);
			m_os.precision(N);
			double a = elapsed();
			std::string b;

			if (a > 3600)
			{
				a /= 3600;
				b = " h\n";
			}
			else if (a > 60)
			{
				a /= 60;
				b = " min\n";
			}
			else
				b = " s\n";

			m_os << a << b << std::endl;
		}
		catch (...) {} // eat any exceptions
	} // ~progress_timer

private:
	std::ostream &m_os;
};

//  progress_display  --------------------------------------------------------//
template<typename T = unsigned long, typename U = double>
class progress_display : private boost::noncopyable
{
public:
	explicit progress_display(T expected_count_,
	                          std::ostream &os = std::cout,
	                          const std::string &s1 = "\n",  //leading strings
	                          const std::string &s2 = "",
	                          const std::string &s3 = "")
	// os is hint; implementation may ignore, particularly in embedded systems
		: boost::noncopyable(), m_os(os), m_s1(s1), m_s2(s2), m_s3(s3)
	{
		restart(expected_count_);
	}

	void           restart(T expected_count_)
	//  Effects: display appropriate scale
	//  Postconditions: count()==0, expected_count()==expected_count_
	{
		_count = _next_tic_count = _tic = 0;
		_expected_count = expected_count_;
		m_os << m_s1 << "0%   10   20   30   40   50   60   70   80   90   100%\n"
		     << m_s2 << "|----|----|----|----|----|----|----|----|----|----|"
		     << std::endl  // endl implies flush, which ensures display
		     << m_s3;

		if (!_expected_count) _expected_count = 1;    // prevent divide by zero
	} // restart

	T operator+=(T increment)
	//  Effects: Display appropriate progress tic if needed.
	//  Postconditions: count()== original count() + increment
	//  Returns: count().
	{
		if ((_count += increment) >= _next_tic_count)
		{
			display_tic();
		}

		return _count;
	}

	T operator++()
	{
		return operator+=(1);
	}
	T count() const
	{
		return _count;
	}
	T expected_count() const
	{
		return _expected_count;
	}

private:
	std::ostream      &m_os;  // may not be present in all imps
	const std::string  m_s1;  // string is more general, safer than
	const std::string  m_s2;  //  const char *, and efficiency or size are
	const std::string  m_s3;  //  not issues

	T _count, _expected_count, _next_tic_count;
	unsigned int  _tic;
	void display_tic()
	{
		// use of floating point ensures that both large and small counts
		// work correctly.  static_cast<>() is also used several places
		// to suppress spurious compiler warnings.
		unsigned int tics_needed =
		    static_cast<unsigned int>(
		        (static_cast<U>(_count) / _expected_count) * 50.0);

		do
		{
			m_os << '*' << std::flush;
		}
		while (++_tic < tics_needed);

		_next_tic_count =
		    static_cast<T>((_tic / 50.0) * _expected_count);

		if (_count == _expected_count)
		{
			if (_tic < 51) m_os << '*';

			m_os << std::endl;
		}
	} // display_tic
};

} // namespace DA

#endif  // DA_PROGRESS_HPP
