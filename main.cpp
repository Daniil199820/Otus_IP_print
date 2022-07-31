#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <type_traits>
#include <tuple>
#include <list>




template <typename T, typename ...Ts>
using areSame_t = std::conjunction<std::is_same<T, Ts>...>;


template<std::size_t I = 0, typename... Tp>
typename std::enable_if<I == sizeof...(Tp) , void>::type
print_ip(std::tuple<Tp...> tup)
{
	std::cout << "\n";
}




template <size_t I = 0, typename... Ts>
typename std::enable_if<(I < sizeof...(Ts)),
	void>::type
	print_ip(std::tuple<Ts...> tup)
{

	static_assert(areSame_t<Ts...>::value,"Are different types of tuple");

	// Print element of tuple
	
	if(I==0)
		std::cout << std::get<I>(tup);
	else
		std::cout << "." << std::get<I>(tup);
	
	// Go to next element
	print_ip<I + 1>(tup);
	
}

template <typename T>
typename std::enable_if<std::is_same<T,std::string>::value, void>::type
print_ip(T str)
{
	std::cout << str<<'\n';
}

template <typename T>
typename std::enable_if<!std::is_same<T, std::string>::value && std::is_arithmetic<T>::value, void>::type
print_ip(T number)
{
	int size = sizeof(T)-1;
	for (int i = size; i >=0; --i)
	{
		uint8_t u_number = (number >> 8 * i) & 0xff;
		if(i==size)
			std::cout << unsigned(u_number);
		else
			std::cout << "." <<unsigned(u_number);
	}
	
	std::cout << "\n";
}

template <typename T>
typename std::enable_if<!std::is_same<T, std::string>::value && std::is_same<decltype(begin(std::declval<T>()),end(std::declval<T>()), void()), void>::value, void>::type
print_ip(T container)
{
	for (auto it = container.begin(); it != container.end(); ++it)
	{
		if (it == container.begin())
			std::cout << *it;
		else
			std::cout << "." << *it;
	}
	std::cout << "\n";
}

int main()
{
	print_ip(int8_t{ -1 }); // 255
	print_ip(int16_t{ 0 }); // 0.0
	print_ip(int32_t{ 2130706433 }); // 127.0.0.1
	print_ip(int64_t{ 8875824491850138409 });// 123.45.67.89.101.112.131.41
	print_ip(std::string{ "Hello, World!" }); // Hello, World!
	print_ip(std::vector<int>{100, 200, 300, 400}); // 100.200.300.400
	print_ip(std::list<short>{400, 300, 200, 100}); // 400.300.200.100
	print_ip(std::make_tuple(123,456, 789, 0)); // 123.456.789.0

	return 0;
}