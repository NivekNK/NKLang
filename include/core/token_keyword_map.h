/* C++ code produced by gperf version 3.1 */
/* Command-line: 'C:\\ProgramData\\chocolatey\\lib\\gperf\\tools\\gperf.exe' -CGD -N is_valid_keyword -Z TokenKeywordMap -K keyword -L C++ -t token_keyword_map.gperf  */
/* Computed positions: -k'1-2' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif

#line 1 "token_keyword_map.gperf"

#include "core/token.h"
#line 4 "token_keyword_map.gperf"
struct TokenKeyword {
    const char* keyword;
    nk::Token::TokenType token;
};

#define TOTAL_KEYWORDS 13
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 6
#define MIN_HASH_VALUE 3
#define MAX_HASH_VALUE 24
/* maximum key range = 22, duplicates = 0 */

class TokenKeywordMap
{
private:
  static inline unsigned int hash (const char *str, size_t len);
public:
  static const struct TokenKeyword *is_valid_keyword (const char *str, size_t len);
};

inline unsigned int
TokenKeywordMap::hash (const char *str, size_t len)
{
  static const unsigned char asso_values[] =
    {
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25,  5, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25,  0, 25, 25,
      25,  5,  5, 25, 25,  0, 25, 25, 15, 10,
      25, 10, 25, 25,  0,  0,  0, 10, 25, 25,
      25, 10, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
      25, 25, 25, 25, 25, 25
    };
  return len + asso_values[static_cast<unsigned char>(str[1])] + asso_values[static_cast<unsigned char>(str[0])];
}

static const struct TokenKeyword wordlist[] =
  {
#line 21 "token_keyword_map.gperf"
    {"str", nk::Token::String},
#line 12 "token_keyword_map.gperf"
    {"true", nk::Token::True},
#line 10 "token_keyword_map.gperf"
    {"if", nk::Token::If},
#line 20 "token_keyword_map.gperf"
    {"i32", nk::Token::Int32},
#line 17 "token_keyword_map.gperf"
    {"self", nk::Token::Self},
#line 13 "token_keyword_map.gperf"
    {"false", nk::Token::False},
#line 16 "token_keyword_map.gperf"
    {"return", nk::Token::Return},
#line 19 "token_keyword_map.gperf"
    {"f32", nk::Token::Float32},
#line 9 "token_keyword_map.gperf"
    {"type", nk::Token::Type},
#line 15 "token_keyword_map.gperf"
    {"for", nk::Token::For},
#line 14 "token_keyword_map.gperf"
    {"func", nk::Token::Func},
#line 18 "token_keyword_map.gperf"
    {"mut", nk::Token::Mut},
#line 11 "token_keyword_map.gperf"
    {"else", nk::Token::Else}
  };

static const signed char lookup[] =
  {
    -1, -1, -1,  0,  1, -1, -1,  2,  3,  4,  5,  6, -1,  7,
     8, -1, -1, -1,  9, 10, -1, -1, -1, 11, 12
  };

const struct TokenKeyword *
TokenKeywordMap::is_valid_keyword (const char *str, size_t len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          int index = lookup[key];

          if (index >= 0)
            {
              const char *s = wordlist[index].keyword;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &wordlist[index];
            }
        }
    }
  return 0;
}
