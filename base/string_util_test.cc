#include "base/string_util.h"
#include "gtest/gtest.h"

#define EXPECT_COPY_STREQ(str1, str2) do { \
    char *_str2 = str2; \
    EXPECT_STREQ(str1, _str2); \
    free(_str2); \
  } while (false);

TEST(StringUtilTest, ToLower) {
  EXPECT_EQ('a', to_lower_ascii('a'));
  EXPECT_EQ('a', to_lower_ascii('A'));
  EXPECT_NE('a', to_lower_ascii('b'));
  EXPECT_NE('a', to_lower_ascii('B'));
  EXPECT_EQ('1', to_lower_ascii('1'));
}

TEST(StringUtilTest, CopyToLower) {
  EXPECT_COPY_STREQ("", string_copy_to_lower_ascii(""));
  EXPECT_COPY_STREQ("abcdef123xyz", string_copy_to_lower_ascii("aBcDeF123xYz"));
}

TEST(StringUtilTest, ToUpper) {
  EXPECT_EQ('A', to_upper_ascii('A'));
  EXPECT_EQ('A', to_upper_ascii('a'));
  EXPECT_NE('A', to_upper_ascii('B'));
  EXPECT_NE('A', to_upper_ascii('b'));
  EXPECT_EQ('1', to_upper_ascii('1'));
}

TEST(StringUtilTest, CopyToUpper) {
  EXPECT_COPY_STREQ("", string_copy_to_upper_ascii(""));
  EXPECT_COPY_STREQ("ABCDEF123XYZ", string_copy_to_upper_ascii("aBcDeF123xYz"));
}

TEST(StringUtilTest, StringCompareCaseInsensitive) {
  EXPECT_EQ(0, string_compare_case_insensitive("", ""));
  EXPECT_EQ(0, string_compare_case_insensitive("a", "A"));
  EXPECT_EQ(0, string_compare_case_insensitive("abc123", "ABC123"));
}

TEST(StringUtilTest, StringEq) {
  EXPECT_TRUE(string_eq("", ""));
  EXPECT_FALSE(string_eq("", "a"));
  EXPECT_TRUE(string_eq("a", "a"));
  EXPECT_FALSE(string_eq("a", "aa"));

  EXPECT_TRUE(string_eq_case_insensitive("", ""));
  EXPECT_FALSE(string_eq_case_insensitive("", "a"));
  EXPECT_TRUE(string_eq_case_insensitive("a", "a"));
  EXPECT_FALSE(string_eq_case_insensitive("a", "aa"));

  EXPECT_TRUE(string_eq_case_insensitive("aAbB", "aabb"));
  EXPECT_FALSE(string_eq_case_insensitive("aBa", ""));
}

TEST(StringUtilTest, FormatBytes) {
  EXPECT_COPY_STREQ("0 B", format_bytes(0));
  EXPECT_COPY_STREQ("256 B", format_bytes(256));
  EXPECT_COPY_STREQ("1023 B", format_bytes(1023));
  EXPECT_COPY_STREQ("1.0 kB", format_bytes(1024));
  EXPECT_COPY_STREQ("2.0 kB", format_bytes(1997));
  EXPECT_COPY_STREQ("2.0 kB", format_bytes(2047));
  EXPECT_COPY_STREQ("1.0 TB", format_bytes(1024 * 1024 * 1024 * 1024LL));
}
