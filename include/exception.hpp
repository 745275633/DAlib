#ifndef DA_EXCEPTION_HPP
#define DA_EXCEPTION_HPP

#include <boost/throw_exception.hpp>
#include <boost/exception/all.hpp>
#include <boost/current_function.hpp>
#include <exception>
#include <iostream>

#define DA_THROW_EXCEPTION_0() \
	throw ::DA::exception() \
	        << ::boost::throw_function(BOOST_CURRENT_FUNCTION) \
	        << ::boost::throw_file(__FILE__) \
	        << ::boost::throw_line(__LINE__)

#define DA_THROW_EXCEPTION_1(x) \
	throw ::DA::exception() \
	        << ::DA::exception_tag::throw_msg(x) \
	        << ::boost::throw_function(BOOST_CURRENT_FUNCTION) \
	        << ::boost::throw_file(__FILE__) \
	        << ::boost::throw_line(__LINE__)

#define DA_THROW_EXCEPTION_3(name, type, x) \
	namespace DA\
	{\
	namespace exception_tag \
	{\
	struct name;\
	}\
	}\
	throw ::DA::exception() \
	        << ::boost::error_info<DA::exception_tag::##name, type>(x) \
	        << ::boost::throw_function(BOOST_CURRENT_FUNCTION) \
	        << ::boost::throw_file(__FILE__) \
	        << ::boost::throw_line(__LINE__)

#define DA_CATCH_EXCEPTION \
	catch(::DA::exception &e)\
	{\
		::std::cerr << *::boost::get_error_info< ::boost::throw_file>(e) \
		            << "(" << *::boost::get_error_info< ::boost::throw_line>(e) \
		            << "):" \
		            << *::boost::get_error_info< ::boost::throw_function>(e)\
		            << ::std::endl;\
		e << ::boost::throw_function(BOOST_CURRENT_FUNCTION) \
		  << ::boost::throw_file(__FILE__) \
		  << ::boost::throw_line(__LINE__);\
		throw;\
	}\
	catch(::std::exception &e)\
	{\
		BOOST_THROW_EXCEPTION(e);\
	}\
	catch(...)\
	{\
		DA_THROW_EXCEPTION_0();\
	}

#define DA_MAIN_CATCH_EXCEPTION \
	catch(::DA::exception &e)\
	{\
		::std::cerr << ::boost::diagnostic_information(e) << ::std::endl;\
	}\
	catch(::std::exception &e)\
	{\
		::std::cerr << e.what() << ::std::endl;\
	}\
	catch(...)\
	{\
		::std::cerr << "error" << ::std::endl;\
	}
#define DA_MAIN_CATCH_EXCEPTION_ENDFUN(endfun) \
	catch(::DA::exception &e)\
	{\
		::std::cerr << ::boost::diagnostic_information(e) << ::std::endl;\
		endfun;\
	}\
	catch(::std::exception &e)\
	{\
		::std::cerr << e.what() << ::std::endl;\
		endfun;\
	}\
	catch(...)\
	{\
		::std::cerr << "error" << ::std::endl;\
		endfun;\
	}

namespace DA
{
struct exception :
	virtual std::exception,
	virtual boost::exception
{};

namespace exception_tag
{
struct msg;
typedef ::boost::error_info< ::DA::exception_tag::msg, std::string> throw_msg;
}
}

#endif //DA_EXCEPTION_HPP
