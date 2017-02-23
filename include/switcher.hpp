namespace DA
{
template <typename T>
class switcher
{
private:
	typedef ::std::function<void()> func_type;
	typedef ::std::unordered_map<T, func_type> case_type;
	case_type func_list_;
	func_type default_;
public:
	switcher() = default;
	switcher(case_type func_list) : func_list_(func_list){};
	switcher(case_type func_list, func_type defa) : func_list_(func_list), default_(defa){};
	switcher(func_type defa) : default_(defa){};
	void addcase(case_type case_)
	{
		func_list_.insert(case_);
	}
	void addcase(case_type::value_type case_)
	{
		func_list_.insert(case_);
	}
	void operator()(case_type::key_type key)
	{
		try
		{
			auto &fun = func_list_.at(key);
			fun();
		}
		catch(::std::out_of_range &)
		{
			default_();
		}
		catch(...)
		{
			throw;
		}
	}
};
}
