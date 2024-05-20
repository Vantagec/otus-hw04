#include <sstream>
#include <list>
#include <gtest/gtest.h>
#include <print_ip.h>
#include <string>
#include <string_view>

template <typename T>
void check(T &&value, std::string &&expected)
{
    std::stringstream sStream;
    print_ip(std::forward<T>(value), sStream);
    EXPECT_EQ(sStream.str(), expected);
};

TEST(PrintIpTest, IntegralValues)
{
    check(int8_t{-1}, "255");
    check(int16_t{0}, "0.0");
    check(int32_t{2130706433}, "127.0.0.1");
    check(int64_t{8875824491850138409}, "123.45.67.89.101.112.131.41");
}

TEST(PrintIpTest, StringValue)
{
    check(std::string{""}, "");
    check(std::string{"Hello, World!"}, "Hello, World!");
}

TEST(PrintIpTest, VectorValue)
{
    check(std::vector<short>{}, "");
    check(std::vector<int>{100, 200, 300, 400}, "100.200.300.400");
}

TEST(PrintIpTest, ListValue)
{
    check(std::list<int>{}, "");
    check(std::list<short>{400, 300, 200, 100}, "400.300.200.100");
}

TEST(PrintIpTest, TupleValue)
{
    check(std::make_tuple(), "");
    check(std::make_tuple(123, 456, 789, 0), "123.456.789.0");

    
}

