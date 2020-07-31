#include <stdio.h>

void escape(char s[], char t[]);
void real_escape(char s[], char t[]);

int main() {
  char s[100];
  char t1[] = "They killed\n Kenny!";
  char t2[] = "You\\n bastards!";
  escape(s, t1);
  printf("escape(s, t1): %s\n", s);
  real_escape(s, t2);
  printf("real_escape(s, t2): %s\n", s);
  return 0;
}

// convert \t, \n to "\t", "\n"
void escape(char s[], char t[]) {
  int j = 0;
  for (int i = 0; t[i] != '\0'; i++) {
    switch (t[i]) {
    case '\t':
      s[j++] = '\\';
      s[j++] = 't';
      break;
    case '\n':
      s[j++] = '\\';
      s[j++] = 'n';
      break;
    default:
      s[j++] = t[i];
      break;
    }
  }
  s[j] = '\0';
}

void real_escape(char s[], char t[]) {
  int j = 0;
  for (int i = 0; t[i] != '\0'; i++) {
    if (t[i] == '\\') {
      switch (t[++i]) {
      case 't':
        s[j++] = '\t';
        break;
      case 'n':
        s[j++] = '\n';
        break;
      default:
        s[j++] = '\\';
        s[j++] = t[i];
        break;
      }
    } else
      s[j++] = t[i];
  }
  s[j] = '\0';
}
