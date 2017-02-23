#include <cstdlib>
#undef NULL
#define NULL nullptr
namespace DA
{
template <typename T>
T get_NULL()
{
	return static_cast<T>(0);
}
class empty_class {};
class null_class;
}
