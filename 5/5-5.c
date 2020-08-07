#include <stdio.h>
#include <string.h>

char *my_strncpy(char *dest, const char *src, size_t n);
char *my_strncat(char *dest, const char *src, size_t n);
int my_strncmp(const char *s1, const char *s2, size_t n);

int main() {
  char s1[1000] = "I'm an agent of chaos.";
  char *s2 = "Why so serious?";
  char *s3 = "Let's put a smile on that face!";

  printf("copy part: %s\n", my_strncpy(s1, s2, 6));
  printf("copy all: %s\n", my_strncpy(s1, s2, strlen(s2) + 10));

  printf("append all: %s\n", my_strncat(s1, s3, strlen(s3) + 10));
  printf("append part: %s\n", my_strncat(s1, s3, 5));

  printf("compare same: %d\n", my_strncmp(s2, s2, strlen(s2) + 10));
  printf("compare same: %d\n", my_strncmp(s1, s2, 6));
  printf("compare diff: %d\n", my_strncmp(s2, s3, strlen(s3)));
  printf("compare diff: %d\n", my_strncmp(s3, s2, 2));

  return 0;
}

char *my_strncpy(char *dest, const char *src, size_t n) {
  char *cp = dest;
  for (size_t i = 0; i < n && (*dest++ = *src++); i++)
    ;
  *dest = '\0';
  return cp;
}

char *my_strncat(char *dest, const char *src, size_t n) {
  char *cp = dest;
  while (*dest)
    dest++;
  my_strncpy(dest, src, n);
  return cp;
}

int my_strncmp(const char *s1, const char *s2, size_t n) {
  for (size_t i = 0; i < n && *s1 == *s2; s1++, s2++, i++)
    if (*s1 == '\0')
      return 0;
  return *s1 - *s2;
}
