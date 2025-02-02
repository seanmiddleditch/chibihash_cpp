#include "chibihash/chibihash64.hh"

#include <cassert>

constexpr uint8_t test1[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
constexpr uint64_t hash1 = 0x8F922660063E3E75;
static_assert(chibihash::hash64_data(test1, sizeof(test1)) == hash1, "Test1 failed");

constexpr char test2[] = "abcdefgh";
constexpr uint64_t hash2 = hash1;
static_assert(chibihash::hash64_string(test2) == hash2, "Test2 failed");

constexpr char test3[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Etiam massa libero, varius id orci sed, aliquam.";
constexpr uint64_t hash3 = 0xD03BBFD423290484;
static_assert(chibihash::hash64_string(test3) == 0xD03BBFD423290484, "Test3 failed");

constexpr std::nullptr_t test4 = {};
constexpr uint64_t hash4 = 0x9EA80F3B18E26CFB;
static_assert(chibihash::hash64_data(test4, 0) == hash4, "Test4 failed");

constexpr char test5[] = "qwertyuiopasdfghjklzxcvbnm123456";
constexpr uint64_t hash5 = 0x2EF296DB634F6551;
static_assert(chibihash::hash64_string(test5) == hash5, "Test5 failed");

constexpr uint8_t test6[] =
{
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z',
	'x', 'c', 'v', 'b', 'n', 'm', '1', '2', '3', '4',
	'5', '6', '7', '8', '9'
};
constexpr uint64_t hash6 = 0x0F56CF3735FFA943;
static_assert(chibihash::hash64_data(test6, sizeof(test6)) == hash6, "Test6 failed");

int main()
{
	assert(chibihash::hash64_data(test1, sizeof(test1)) == hash1);
	assert(chibihash::hash64_string(test2) == hash2);
	assert(chibihash::hash64_string(test3) == hash3);
	assert(chibihash::hash64_data(test4, 0) == hash4);
	assert(chibihash::hash64_string(test5) == hash5);
	assert(chibihash::hash64_data(test6, sizeof(test6)) == hash6);
}