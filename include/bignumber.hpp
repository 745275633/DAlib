#ifndef DA_BIGNUMBER_HPP
#define DA_BIGNUMBER_HPP
#include <boost/operators.hpp>
#include <boost/swap.hpp>
#include <boost/algorithm/string.hpp> //for to_upper_copy
#include <DA/exception.hpp>
//#include <DA/functional.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <functional>
#include <algorithm> //for max

namespace DA
{
template<bool use_HEX = true, typename Container = std::vector<int>>
class bignumber :
	boost::totally_ordered1<bignumber<use_HEX, Container>,
	boost::totally_ordered2<bignumber<use_HEX, Container>, std::string,
	boost::integer_arithmetic1<bignumber<use_HEX, Container>,
	boost::unit_steppable<bignumber<use_HEX, Container>>>>>
{
private:
	typedef Container vi;
	typedef ::std::shared_ptr<vi> pvi;
	pvi value;
	bool positive_;
private:
	void clear_zero()
	{
		if (value->empty())
		{
			value->push_back(0);
			positive_ = true;
			return;
		}

		auto it = end(*value);
		--it;

		while (*it == 0)
		{
			if (it == begin(*value))
			{
				break;
			}

			value->erase(it);
			--it;
		}
	}
public:
	bignumber(long n = 0): positive_(n < 0 ? false : true)
	{
		value = ::std::make_shared<vi>();

		if (n)
		{
			n = n < 0 ? -n : n;

			while (n > 0)
			{
				value->push_back(n % (use_HEX ? 16 : 10));
				n /= use_HEX ? 16 : 10;
			}
		}
		else
		{
			value->push_back(0);
		}
	}
	bignumber(const std::string &rhs): positive_(rhs[0] == '-' ? false : true)
	{
		value = ::std::make_shared<vi>();
		//value->resize(rhs.size());
		auto it = rhs.crend();

		if (!positive())
			--it;

		std::transform(rhs.crbegin(), it,
		               back_inserter(*value),
		               [](decltype(*it) x) -> typename vi::value_type
		{
			if (x >= 'a' && x <= 'z')
				return x - 'a' + 10;
			else if (x >= 'A' && x <= 'Z')
				return x - 'A' + 10;
			else
				return x - '0';
		}
		              );
		auto newend = std::remove_if(begin(*value), end(*value),
		                            [](typename vi::value_type x) -> bool
		{
			if (x < 0 || x >= (use_HEX ? 16 : 10))
				return true;

			return false;
		}
		                           );
		value->erase(newend);
		clear_zero();
	}
	bignumber(const bignumber &rhs, bool inverse = false):
		positive_(inverse ? !rhs.positive() : rhs.positive())
	{
		value = ::std::make_shared<vi>(begin(*rhs.value), end(*rhs.value));
	}
	bignumber(bignumber &&rhs, bool inverse = false):
		positive_(inverse ? !rhs.positive() : rhs.positive())
	{
		value = ::std::move(rhs.value);
		rhs.value = nullptr;
	}
	bignumber &operator=(const bignumber &rhs)
	{
		value->assign(begin(*rhs.value), end(*rhs.value));
		positive_ = rhs.positive();
		return *this;
	}
	bignumber &operator=(bignumber &&rhs)
	{
		value = ::std::move(rhs.value);
		rhs.value = nullptr;
		positive_ = rhs.positive();
		return *this;
	}
	void swap(bignumber &rhs)
	{
		::boost::swap(value, rhs.value);
		::boost::swap(positive_, rhs.positive_);
	}
	bool positive() const
	{
		return positive_;
	}
	void inverse()
	{
		positive_ = !positive_;
	}
public:
	friend bool abslt(const bignumber &lhs, const bignumber &rhs)
	{
		if (lhs.value->size() < rhs.value->size())
			return true;
		else if (rhs.value->size() < lhs.value->size())
			return false;
		else
			for (auto lit = begin(*lhs.value) , rit = begin(*rhs.value);
			        lit != end(*lhs.value) ; ++lit, ++rit)
				if (*lit < *rit)
					return true;
				else if (*rit < *lit)
					return false;

		return false;
	}
	friend bool operator<(const bignumber &lhs, const bignumber &rhs)
	{
		if (lhs.positive() != rhs.positive())
			return rhs.positive();
		else if (lhs.positive())
			return abslt(lhs, rhs);
		else
			return !abslt(lhs, rhs);
	}
	friend bool operator==(const bignumber &lhs, const bignumber &rhs)
	{
		if (lhs.value->size() != rhs.value->size()
		        || lhs.positive() != rhs.positive())
			return false;
		else
			for (auto lit = begin(*lhs.value), rit = begin(*rhs.value);
			        lit != end(*lhs.value); ++lit, ++rit)
				if (*lit != *rit)
					return false;

		return true;
	}
	//bignumber and string
	friend bool operator==(const bignumber &lhs, const std::string &rhs)
	{
		return lhs.str() == rhs;
	}
	friend bool operator<(const bignumber &lhs, const std::string &rhs)
	{
		return lhs < bignumber(rhs);
	}
	friend bool operator>(const bignumber &lhs, const std::string &rhs)
	{
		return lhs > bignumber(rhs);
	}
	//math
	friend bignumber operator-(const bignumber &rhs)
	{
		return bignumber<use_HEX, Container> (rhs, true);
	}
	friend bignumber &operator+=(bignumber &lhs, const bignumber &rhs)
	{
		if (lhs.positive() == rhs.positive())
		{
			bignumber<use_HEX, Container> tmp(lhs);
			tmp.value->reserve(std::max(tmp.value->size(), rhs.value->size())
			                   + 2);

			for (auto lit = begin(*tmp.value), rit = begin(*rhs.value);
			        rit != end(*rhs.value); ++lit, ++rit)
			{
				if (lit == end(*tmp.value))
					tmp.value->push_back(*rit);
				else
				{
					*lit += *rit;
					auto it = lit;

					while (*it >= (use_HEX ? 16 : 10))
					{
						*it -= use_HEX ? 16 : 10;
						++it;

						if (it == end(*tmp.value))
						{
							tmp.value->push_back(1);
						}
						else
							++(*it);
					}
				}
			}

			lhs = ::std::move(tmp);
		}
		else
		{
			if (lhs == -rhs)
			{
				lhs.value->clear();
				lhs.value->push_back(0);
			}
			else if (lhs.positive())
				lhs -= -rhs;
			else
				lhs = rhs - -lhs;
		}

		return lhs;
	}
	friend bignumber &operator-=(bignumber &lhs, const bignumber &rhs)
	{
		if (lhs.positive() == rhs.positive())
		{
			if (lhs == rhs)
			{
				lhs.value->clear();
				lhs.value->push_back(0);
			}
			else if (lhs < rhs)
				lhs = -(rhs - lhs);
			else
			{
				bignumber<use_HEX, Container> tmp(lhs);

				for (auto lit = begin(*tmp.value), rit = begin(*rhs.value);
				        rit != end(*rhs.value); ++lit, ++rit)
				{
					*lit -= *rit;
					auto it = lit;

					while (*it < 0)
					{
						*it += use_HEX ? 16 : 10;
						++it;
						--(*it);
					}
				}

				tmp.clear_zero();
				lhs = ::std::move(tmp);
			}
		}
		else
		{
			if (lhs.positive())
				lhs += -rhs;
			else
				lhs = lhs + -rhs;
		}

		return lhs;
	}
	friend bignumber operator*=(bignumber &lhs, const bignumber &rhs)
	{
		if (rhs == "4")
			return (lhs += lhs += lhs);

		if (rhs == "8")
			return (lhs += lhs += lhs += lhs);

		bignumber n(lhs);

		for (bignumber i(1); i < rhs; ++i)
			lhs += n;

		return lhs;
	}
	std::string str() const
	{
		std::stringstream ss;

		if (!positive())
			ss << "-";

		if (use_HEX)
			ss << std::hex;

		std::copy(value->crbegin(), value->crend(),
		          std::ostream_iterator<int>(ss, ""));
		return boost::to_upper_copy(ss.str());
	}
}; // class bignumber

template<bool use_HEX, typename Container>
bignumber<use_HEX, Container> &operator++(bignumber<use_HEX, Container> &rhs)
{
	rhs += 1;
	return rhs;
}
template<bool use_HEX, typename Container>
bignumber<use_HEX, Container> &operator--(bignumber<use_HEX, Container> &rhs)
{
	rhs -= 1;
	return rhs;
}
template<bool use_HEX, typename Container>
std::ostream &operator<<(std::ostream &lhs,
                         const bignumber<use_HEX, Container> &rhs)
{
	lhs << rhs.str();
	return lhs;
}
template<bool use_HEX, typename Container>
void swap(bignumber<use_HEX, Container> &a, bignumber<use_HEX, Container> &b)
{
	a.swap(b);
}
} // namespace DA
#endif
