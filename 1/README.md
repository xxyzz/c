# CHAPTER 1: A Tutorial Introduction

## 1.1 Getting Started

#### Exercise 1-1

Run the “`hello, world`” program on your system. Experiment with leaving out parts of the program, to see what error messages you get.

#### Exercise 1-2

Experiment to find out what happens when `printf`’s argument string contains `\c`, where c is some character not listed above.

## 1.2 Variables and Arithmetic Expressions

#### Exercise 1-3

Modify the temperature conversion program to print a heading above the table.

#### Exercise 1-4

Write a program to print the corresponding Celsius to Fahrenheit table.

## 1.3 The For Statement

#### Exercise 1-5

Modify the temperature conversion program to print the table in reverse order, that is, from 300 degrees to 0.

## 1.4 Symbolic Constants

## 1.5 Character Input and Output

### 1.5.1 File Copying

#### Exercise 1-6

Verify that the expression `getchar() != EOF` is 0 or 1.

#### Exercise 1-7

Write a program to print the value of `EOF`.

### 1.5.2 Character Counting

### 1.5.3 Line Counting

#### Exercise 1-8

Write a program to count blanks, tabs, and newlines.

#### Exercise 1-9

Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank.

#### Exercise 1-10

Write a program to copy its input to its output, replacing each tab by `\t`, each backspace by `\b`, and each backslash by `\\`. This makes tabs and backspaces visible in an unambiguous way.

### 1.5.4 Word Counting

#### Exercise 1-11

How would you test the word count program? What kinds of input are most likely to uncover bugs if there are any?

#### Exercise 1-12

Write a program that prints its input one word per line.

## 1.6 Arrays

#### Exercise 1-13

Write a program to print a histogram of the lengths of words in its input. It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging.

#### Exercise 1-14

Write a program to print a histogram of the frequencies of different characters in its input.

## 1.7 Functions

#### Exercise 1-15

Rewrite the temperature conversion program of Section 1.2 to use a function for conversion.

## 1.8 Arguments—Call by Value

## 1.9 Character Arrays

#### Exercise 1-16

Revise the main routine of the longest-line program so it will correctly print the length of arbitrarily long input lines, and as much as possible of the text.

#### Exercise 1-17

Write a program to print all input lines that are longer than 80 characters.

#### Exercise 1-18

Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines.

#### Exercise 1-19

Write a function `reverse(s)` that reverses the character string `s`. Use it to write a program that reverses its input a line at a time.

## 1.10 External Variables and Scope

#### Exercise 1-20

Write a program `detab` that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every *n* columns. Should *n* be a variable or a symbolic parameter?

#### Exercise 1-21

Write a program `entab` that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for `detab`. When either a tab or a single blank would suffice to reach a tab stop, which should be given preference?

#### Exercise 1-22

Write a program to “fold” long input lines into two or more shorter lines after the last non-blank character that occurs before the n-th column of input. Make sure your program does something intelligent with very long lines, and if there are no blanks or tabs before the specified column.

#### Exercise 1-23

Write a program to remove all comments from a C program. Don’t forget to handle quoted strings and character constants properly. C comments do not nest.
