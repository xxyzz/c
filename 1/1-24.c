#include <stdio.h>
// https://en.wikipedia.org/wiki/Bracket

int main() {
  int c, previous = '\0', pre_previous = '\0', parentheses = 0, brackets = 0,
         braces = 0, single_quotes = 0, double_quotes = 0, single_comments = 0,
         multi_comments = 0, possible_comment = 0, after_quote = 0;

  while ((c = getchar()) != EOF) {
    if (possible_comment) {
      if (c == '/')
        ++single_comments;
      else if (c == '*')
        ++multi_comments;
      --possible_comment;
    } else if (single_comments) {
      if (c == '\n')
        --single_comments;
    } else if (multi_comments) {
      if (previous == '*' && c == '/')
        --multi_comments;
    } else if (single_quotes) { // 'x', '\t', '\\', '\''
      ++after_quote;
      if (c == '\'' && previous != '\\' && after_quote == 2) {
        --single_quotes;
        after_quote = 0;
      } else if (c == '\'' && pre_previous == '\\' && after_quote == 3) {
        --single_quotes;
        after_quote = 0;
      }
    } else if (double_quotes) {
      if (previous != '\\' && c == '"')
        --double_quotes;
    } else {
      if (c == '(')
        ++parentheses;
      else if (c == ')')
        --parentheses;
      else if (c == '[')
        ++brackets;
      else if (c == ']')
        --brackets;
      else if (c == '{')
        ++braces;
      else if (c == '}')
        --braces;
      else if (c == '"')
        ++double_quotes;
      else if (c == '\'')
        ++single_quotes;
      else if (c == '/')
        ++possible_comment;
    }
    pre_previous = previous;
    previous = c;
  }

  if (parentheses)
    printf("unbalanced parentheses: %d\n", parentheses);
  if (brackets)
    printf("unbalanced brackets: %d\n", brackets);
  if (braces)
    printf("unbalanced braces: %d\n", braces);
  if (single_quotes)
    printf("unbalanced single quotes: %d\n", single_quotes);
  if (double_quotes)
    printf("unbalanced double quotes: %d\n", double_quotes);
  if (single_comments)
    printf("unbalanced single line comments: %d\n", single_comments);
  if (multi_comments)
    printf("unbalanced multi-line comments: %d\n", multi_comments);

  return 0;
}
