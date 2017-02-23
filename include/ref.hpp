#ifndef DA_REF_HPP
#define DA_REF_HPP

#error //please use std::ref

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/detail/workaround.hpp>

/**
 @file
*/

/**
 Boost namespace.
*/
namespace boost
{

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, == 1600 )

struct ref_workaround_tag {};

#endif

// reference_wrapper

/**
 @brief Contains a reference to an object of type `T`.

 `reference_wrapper` is primarily used to "feed" references to
 function templates (algorithms) that take their parameter by
 value. It provides an implicit conversion to `T&`, which
 usually allows the function templates to work on references
 unmodified.
*/
template<class T> class reference_wrapper
{
public:
	/**
	 Type `T`.
	*/
	typedef T type;

	/**
	 Constructs a `reference_wrapper` object that stores a
	 reference to `t`.

	 @remark Does not throw.
	*/
	BOOST_FORCEINLINE explicit reference_wrapper(T &t): t_(boost::addressof(t)) {}

	#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, == 1600 )

	BOOST_FORCEINLINE explicit reference_wrapper(T &t,
	        ref_workaround_tag): t_(boost::addressof(t)) {}

	#endif

	#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
	/**
	 @remark Construction from a temporary object is disabled.
	*/
	BOOST_DELETED_FUNCTION(reference_wrapper(T &&t))
public:
	#endif

	/**
	 @return The stored reference.
	 @remark Does not throw.
	*/
	BOOST_FORCEINLINE operator T &() const
	{
		return *t_;
	}

	/**
	 @return The stored reference.
	 @remark Does not throw.
	*/
	BOOST_FORCEINLINE T &get() const
	{
		return *t_;
	}

	/**
	 @return A pointer to the object referenced by the stored
	   reference.
	 @remark Does not throw.
	*/
	BOOST_FORCEINLINE T *get_pointer() const
	{
		return t_;
	}

	/**
	 @return operator()'s return
	 @remark Does not throw.
	*/
	typename result_of<T()>::type operator()() const
	{
		return (*t_)();
	}
	template <typename T0>
	typename result_of<T(T0)>::type operator()(T0 t0) const
	{
		return (*t_)(t0);
	}
	template <typename T0, typename T1>
	typename result_of<T(T0, T1)>::type operator()(T0 t0, T1 t1) const
	{
		return (*t_)(t0, t1);
	}
	template <typename T0, typename T1, typename T2>
	typename result_of<T(T0, T1, T2)>::type operator()(T0 t0, T1 t1, T2 t2) const
	{
		return (*t_)(t0, t1, t2);
	}
	template <typename T0, typename T1, typename T2, typename T3>
	typename result_of<T(T0, T1, T2, T3)>::type operator()(T0 t0, T1 t1, T2 t2,
	        T3 t3) const
	{
		return (*t_)(t0, t1, t2, t3);
	}
	template <typename T0, typename T1, typename T2, typename T3, typename T4>
	typename result_of<T(T0, T1, T2, T3, T4)>::type operator()(T0 t0, T1 t1, T2 t2,
	        T3 t3, T4 t4) const
	{
		return (*t_)(t0, t1, t2, t3, t4);
	}
	template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
	typename result_of<T(T0, T1, T2, T3, T4, T5)>::type operator()(T0 t0, T1 t1,
	        T2 t2, T3 t3, T4 t4, T5 t5) const
	{
		return (*t_)(t0, t1, t2, t3, t4, t5);
	}
	template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	typename result_of<T(T0, T1, T2, T3, T4, T5, T6)>::type operator()(T0 t0, T1 t1,
	        T2 t2, T3 t3, T4 t4, T5 t5, T6 t6) const
	{
		return (*t_)(t0, t1, t2, t3, t4, t5, t6);
	}
	template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	typename result_of<T(T0, T1, T2, T3, T4, T5, T6, T7)>::type operator()(T0 t0,
	        T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7) const
	{
		return (*t_)(t0, t1, t2, t3, t4, t5, t6, t7);
	}
	template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	typename result_of<T(T0, T1, T2, T3, T4, T5, T6, T7, T8)>::type operator()(
	    T0 t0, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8) const
	{
		return (*t_)(t0, t1, t2, t3, t4, t5, t6, t7, t8);
	}
	template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
	typename result_of<T(T0, T1, T2, T3, T4, T5, T6, T7, T8, T9)>::type operator()(
	    T0 t0, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9) const
	{
		return (*t_)(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
	}

private:

	T *t_;
};

// ref

/**
 @cond
*/
#if defined( __BORLANDC__ ) && BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT(0x581) )
#  define BOOST_REF_CONST
#else
#  define BOOST_REF_CONST const
#endif
/**
 @endcond
*/

/**
 @return `reference_wrapper<T>(t)`
 @remark Does not throw.
*/
template<class T> BOOST_FORCEINLINE reference_wrapper<T> BOOST_REF_CONST ref(
    T  &t)
{
	#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, == 1600 )
	return reference_wrapper<T>(t, ref_workaround_tag());
	#else
	return reference_wrapper<T>(t);
	#endif
}

// cref

/**
 @return `reference_wrapper<T const>(t)`
 @remark Does not throw.
*/
template<class T> BOOST_FORCEINLINE reference_wrapper<T const> BOOST_REF_CONST
cref(T const &t)
{
	return reference_wrapper<T const>(t);
}

#undef BOOST_REF_CONST

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

/**
 @cond
*/
#if defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
#  define BOOST_REF_DELETE
#else
#  define BOOST_REF_DELETE = delete
#endif
/**
 @endcond
*/

/**
 @remark Construction from a temporary object is disabled.
*/
template<class T> void ref(T const &&) BOOST_REF_DELETE;

/**
 @remark Construction from a temporary object is disabled.
*/
template<class T> void cref(T const &&) BOOST_REF_DELETE;

#undef BOOST_REF_DELETE

#endif

// is_reference_wrapper

/**
 @brief Determine if a type `T` is an instantiation of
 `reference_wrapper`.

 The value static constant will be true if the type `T` is a
 specialization of `reference_wrapper`.
*/
template<typename T> struct is_reference_wrapper
{
	BOOST_STATIC_CONSTANT(bool, value = false);
};

/**
 @cond
*/
template<typename T> struct is_reference_wrapper< reference_wrapper<T> >
{
	BOOST_STATIC_CONSTANT(bool, value = true);
};

#if !defined(BOOST_NO_CV_SPECIALIZATIONS)

template<typename T> struct is_reference_wrapper< reference_wrapper<T> const >
{
	BOOST_STATIC_CONSTANT(bool, value = true);
};

template<typename T> struct
	is_reference_wrapper< reference_wrapper<T> volatile >
{
	BOOST_STATIC_CONSTANT(bool, value = true);
};

template<typename T> struct
	is_reference_wrapper< reference_wrapper<T> const volatile >
{
	BOOST_STATIC_CONSTANT(bool, value = true);
};

#endif // !defined(BOOST_NO_CV_SPECIALIZATIONS)

/**
 @endcond
*/


// unwrap_reference

/**
 @brief Find the type in a `reference_wrapper`.

 The `typedef` type is `T::type` if `T` is a
 `reference_wrapper`, `T` otherwise.
*/
template<typename T> struct unwrap_reference
{
	typedef T type;
};

/**
 @cond
*/
template<typename T> struct unwrap_reference< reference_wrapper<T> >
{
	typedef T type;
};

#if !defined(BOOST_NO_CV_SPECIALIZATIONS)

template<typename T> struct unwrap_reference< reference_wrapper<T> const >
{
	typedef T type;
};

template<typename T> struct unwrap_reference< reference_wrapper<T> volatile >
{
	typedef T type;
};

template<typename T> struct
	unwrap_reference< reference_wrapper<T> const volatile >
{
	typedef T type;
};

#endif // !defined(BOOST_NO_CV_SPECIALIZATIONS)

/**
 @endcond
*/

// unwrap_ref

/**
 @return `unwrap_reference<T>::type&(t)`
 @remark Does not throw.
*/
template<class T> BOOST_FORCEINLINE typename unwrap_reference<T>::type
&unwrap_ref(T &t)
{
	return t;
}

// get_pointer

/**
 @cond
*/
template<class T> BOOST_FORCEINLINE T *get_pointer(reference_wrapper<T> const
        &r)
{
	return r.get_pointer();
}
/**
 @endcond
*/

} // namespace boost

#endif // #ifndef BOOST_CORE_REF_HPP
