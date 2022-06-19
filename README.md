# Matrix  

Implementation of a proprietary library for processing numerical matrices in the C programming language. Matrices are one of the basic data structures in programming, e.g. they are used to represent table values, for computational tasks and neural networks. As part of the project you will learn more about matrices and solidify knowledge of structured programming.


## Contents  

1. [Information](#information) \
   1.1. [Historical background](#historical-background) \
   1.2. [Matrix basics](#matrix-basics)
2. [Implementation of the matrix.h library functions](#implementation-of-the-matrixh-library-functions)


# Information

## Historical background

The first mentions of matrices (or as they were called then - "magic squares") were found in ancient China. \
They became famous in the middle of the 18th century thanks to the work of the famous mathematician Gabriel Cramer, who published his work "Introduction to the Analysis of Algebraic Curves", which described a fundamentally new algorithm for solving systems of linear equations. \
Soon after, the works of Carl Friedrich Gauss on the "classical" method of solving linear equations, the Cayley-Hamilton theorem, the works of Karl Weierstrass, Georg Frobenius, and other outstanding scientists were published. \
It was not until 1850 that James Joseph Sylvester introduced the term "Matrix" in his work.

## Matrix basics

A matrix is a collection of numbers arranged into a fixed number of rows and columns.

Matrix A is a rectangular table of numbers arranged in m rows and n columns

```
    1 2 3
A = 4 5 6
    7 8 9
```

```
     1  2  3  4
В =  5  6  7  8
     9 10 11 12
```

You can get the desired element with the help of indices, as follows
A[1,1] = 1, where the first index is the row number, the second is the column number.

Matrix A will have elements with the following indices:

```
    (1,1) (1,2) (1,3)
A = (2,1) (2,2) (2,3)
    (3,1) (3,2) (3,3)
```

The order of a matrix is the number of its rows or columns. \
The main diagonal of a square matrix is the diagonal from the upper left to the lower right corner. \
A rectangular matrix (B) is a matrix with the number of rows not equal to the number of columns. \
A square matrix (A) is a matrix with the number of rows equal to the number of columns.

A column matrix is a matrix with only one column:

```
    (1,1)
A = (2,1)
    (n,1)
```

A row matrix is a matrix that has only one row:

```
A = (1,1) (1,2) (1,m)
```

Tip: A column matrix and a row matrix are also often called vectors.

A diagonal matrix is a square matrix in which all elements outside the main diagonal are zero. \
An identity matrix is a diagonal matrix with all diagonal elements equal to one:

```
    1 0 0
A = 0 1 0
    0 0 1
```

A triangular matrix is a square matrix with all elements on one side of the main diagonal equal to zero.

```
    1 2 3
A = 0 4 5
    0 0 6
```

# Implementation of the matrix.h library functions

- The library developed in C language of C11 standard using gcc compiler
- Did not use outdated and legacy language constructions and library functions. Used the POSIX.1-2017 standard.
- It is a static library (with the matrix.h header file)
- Full coverage of library functions code with unit-tests using the Check library
- Unit tests covered at least 80% of each function (checked using gcov)  
- Use a Makefile for building the library and tests (with targets all, clean, test, matrix.a, gcov_report)
- The gcov_report target should generate a gcov report in the form of an html page.
- Verifiable accuracy of the fractional part is up to 6 decimal places

&nbsp;
<div style="text-align:center"> 
<i>created by Egor Oleynik in April 2022</i>
</div>