#ifndef DA_BIT_HPP
#define DA_BIT_HPP
namespace DA
{
namespace bit
{
template <typename T>
bool look(T flags, T mask)
{
	return ((flags & mask) == mask);
}
template <typename T>
void open(T flags, T mask)
{
	flags |= mask;
}
template <typename T>
void close(T flags, T mask)
{
	flags &= ~mask;
}
template <typename T>
void toggling(T flags, T mask)
{
	flags ^= mask;
}
template <typename T>
void mask(T flags, T mask)
{
	flags &= mask;
}
} //namespace bit
} //namespace DA
#endif
