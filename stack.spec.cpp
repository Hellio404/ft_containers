#include "tests.hpp"
#include "ft_stack.hpp"
#ifndef NTEST
#define NTEST 1000
#endif

namespace nstest_stack
{
	template <typename T>
	T get_value()
	{
		return (T());
	}

	template <>
	std::string get_value<std::string>()
	{
		std::string default_val[] = {"", "random string to test", "another random string to test",
									 "yet another random string to test", "last random string to test",
									 "random string to test", "another random string to test",
									 "yet another random string to test", "last random string to test"};
		if (!(std::rand() % 4))
			return (std::string(default_val[std::rand() % 8]));
		std::string ret = "";
		for (int i = 0; i < 5; ++i)
			ret += (std::rand() % 26) + 'a';
		return (ret);
	}

	template <class C>
	void print_full_stack(const C &s)
	{
		std::cout << "empty: " << s.empty() << std::endl;
		std::cout << "size: " << s.size() << std::endl;
		if (!s.empty())
			std::cout << "top: " << s.top() << std::endl;
	}

	template <class C>
	void test_copy_construct_equal(C &s1, C &s2)
	{
		std::cout << "test_copy_construct_equal:" << std::endl;

		C v3(s1);
		print_full_stack<C>(s1);
		print_full_stack<C>(s2);
		print_full_stack<C>(v3);
		v3 = s1;
		print_full_stack<C>(s1);
		print_full_stack<C>(s2);
		print_full_stack<C>(v3);
		s1 = v3;
		s1 = s2;
		s2 = v3;
		v3 = C(v3);
		print_full_stack<C>(s1);
		print_full_stack<C>(s2);
		print_full_stack<C>(v3);
		v3 = C(s1);
	}

	template <class C>
	void test_construct(C &s1, C &)
	{
		switch (std::rand() % 5)
		{
		case 0:
			std::cout << "test_construct:" << std::endl;
			const typename C::container_type v(std::rand() % 20, get_value<typename C::value_type>());
			s1 = C(v);
			print_full_stack<C>(s1);
			break;
		}
	}
	template <class C>
	void test_push(C &s1, C &)
	{
		std::cout << "test_push:" << std::endl;

		s1.push(get_value<typename C::value_type>());
	}

	template <class C>
	void test_pop(C &s1, C &)
	{
		std::cout << "test_pop:" << std::endl;

		if (!s1.empty())
			s1.pop();
	}

	template <class C>
	void test_comparison(C &s1, C &s2)
	{
		std::cout << "test_comparison:" << std::endl;

		std::cout << "s1 < s2: " << (s1 < s2) << std::endl;
		std::cout << "s1 > s2: " << (s1 > s2) << std::endl;
		std::cout << "s1 <= s2: " << (s1 <= s2) << std::endl;
		std::cout << "s1 >= s2: " << (s1 >= s2) << std::endl;
		std::cout << "s1 == s2: " << (s1 == s2) << std::endl;
		std::cout << "s1 != s2: " << (s1 != s2) << std::endl;
	}
}
template <class C>
void test_stack(int seed)
{
	std::srand(seed);
	void (*array[])(C &, C &) = {
		&nstest_stack::test_construct<C>,
		&nstest_stack::test_copy_construct_equal<C>,
		&nstest_stack::test_push<C>,
		&nstest_stack::test_pop<C>,
		&nstest_stack::test_comparison<C>};
	C s1;
	C s2;
	for (int i = 0; NTEST == -1 || i < NTEST; i++)
	{
		int rand = std::rand() % sizeof(array) / sizeof(void (*)(C &, C &));
		if (std::rand() % 2)
			array[rand](s1, s2);
		else
			array[rand](s2, s1);
		nstest_stack::print_full_stack<C>(s1);
		nstest_stack::print_full_stack<C>(s2);
		std::cout << "========================================" << std::endl;
	}
}

int main(int argc, char **argv)
{
	int seed = 42;
	int ret = 0;

	if (argc == 2)
		seed = atoi(argv[1]);

	test_stack<NAMESPACE::stack<std::string> >(seed);

	if (!isatty(1))
		std::cout << (char)'\3' << std::endl;
	return ret;
}
