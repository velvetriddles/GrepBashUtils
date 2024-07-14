# Unix Utilities Project

This project contains implementations of two essential Unix utilities: `cat` and `grep`. These implementations are written in C and aim to replicate the core functionality of their Unix counterparts.

## Table of Contents

1. [Overview](#overview)
2. [Cat Utility](#cat-utility)
3. [Grep Utility](#grep-utility)
4. [Building the Project](#building-the-project)
5. [Running Tests](#running-tests)
6. [Project Goals and Learning Outcomes](#project-goals-and-learning-outcomes)
7. [Implementation Details](#implementation-details)
8. [Challenges and Solutions](#challenges-and-solutions)

## Overview

This project is an educational exercise to understand the inner workings of common Unix utilities. The implementations strive to match the behavior of the standard Unix tools while providing a clear, readable codebase for learning purposes. By recreating these fundamental tools, we gain insights into systems programming, file I/O operations, and text processing in C.

## Cat Utility

The `cat` utility reads files sequentially, writing them to standard output. It's a fundamental Unix tool used for displaying file contents, concatenating files, and creating new files.

### Supported Flags

- `-b` (--number-nonblank): Number non-empty output lines
- `-e`: Display non-printing characters (see `-v`), and display $ at end of each line
- `-n` (--number): Number all output lines
- `-s` (--squeeze-blank): Squeeze multiple adjacent blank lines
- `-t`: Display non-printing characters (see `-v`), and display TAB characters as ^I
- `-v` (--show-nonprinting): Display non-printing characters using ^ and M- notation, except for LFD and TAB

## Grep Utility

The `grep` utility searches any given input files for lines containing a match to a specified pattern. It's an essential tool for text searching and manipulation in Unix-like operating systems.

### Supported Flags

- `-e` pattern: Use pattern as the pattern; useful to protect patterns beginning with -
- `-i`: Ignore case distinctions
- `-v`: Invert the sense of matching, to select non-matching lines
- `-c`: Output count of matching lines only
- `-l`: Output matching files only
- `-n`: Prefix each line of output with its line number
- `-h`: Output matching lines without preceding them by file names
- `-s`: Suppress error messages about nonexistent or unreadable files
- `-f` file: Obtain patterns from file, one per line
- `-o`: Output the matched parts of a matching line

## Building the Project

To build both utilities, use the provided Makefile:

```
make
```

This will compile both `s21_cat` and `s21_grep` executables.

To build individual utilities:

```
make s21_cat
make s21_grep
```

## Running Tests

Each utility comes with its own test script. To run the tests:

```
make test
```

This will execute both test scripts and display the results.

## Project Goals and Learning Outcomes

1. **Systems Programming**: Gain hands-on experience with low-level file operations, process management, and system calls in C.
2. **Text Processing**: Develop skills in manipulating and analyzing text data efficiently.
3. **Command-Line Argument Parsing**: Learn to parse and handle various command-line options and arguments.
4. **Error Handling**: Implement robust error checking and reporting mechanisms.
5. **Performance Optimization**: Optimize code for efficient processing of large files and complex patterns.
6. **Code Organization**: Practice structuring a C project with multiple source files and headers.
7. **Testing and Debugging**: Develop comprehensive test suites and debug complex C programs.

## Implementation Details

- **Memory Management**: Careful consideration has been given to memory allocation and deallocation to prevent leaks.
- **Buffer Handling**: Efficient buffer management for reading files and processing text.
- **Regular Expressions**: For `grep`, a custom regex engine has been implemented to handle pattern matching.
- **File I/O**: Both utilities demonstrate different approaches to file input/output operations.
- **Modular Design**: The code is organized into logical modules for better maintainability and readability.

## Challenges and Solutions

1. **Efficient Pattern Matching**: Implementing an efficient algorithm for pattern matching in `grep` was challenging. We used a simplified version of the Boyer-Moore algorithm to optimize search operations.

2. **Handling Large Files**: To efficiently process large files, we implemented buffered I/O operations and ensured that memory usage remains constant regardless of file size.

3. **Cross-Platform Compatibility**: While focusing on Unix-like systems, we've taken steps to ensure the code is as portable as possible, avoiding platform-specific functions where feasible.

4. **Performance vs. Readability**: Balancing code performance with readability was a constant consideration. We've added comments and chosen clear variable names to maintain readability without significantly compromising performance.

5. **Edge Cases**: Handling various edge cases, especially in file processing and pattern matching, required careful testing and refinement of our implementations.

## Contributing

This project is primarily for educational purposes. However, if you find any bugs or have suggestions for improvements, please feel free to open an issue or submit a pull request.