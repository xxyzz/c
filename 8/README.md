# CHAPTER 8: The UNIX System Interface

## 8.1 File Descriptors

## 8.2 Low Level I/O—Read and Write

## 8.3 Open, Creat, Close, Unlink

#### Exercise 8-1

Rewrite the program `cat` from Chapter 7 using `read`, `write`, `open` and `close` instead of their standard library equivalents. Perform experiments to determine the relative speeds of the two versions.

## 8.4 Random Access—Lseek

## 8.5 Example—An Implementation of Fopen and Getc

#### Exercise 8-2

Rewrite `fopen` and `_fillbuf` with fields instead of explicit bit operations. Compare code size and execution speed.
