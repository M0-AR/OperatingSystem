# Operating Systems Projects

This repository contains a collection of projects and code examples related to operating systems concepts. The projects cover topics such as creating a simple shell, memory management, and thread synchronization in both C and Java.

## Table of Contents

- [Project 1: MyShell](#project-1-myshell)
- [Project 2: Memory Management](#project-2-memory-management)
- [Java Thread Examples](#java-thread-examples)
- [C Thread Examples](#c-thread-examples)
- [Technologies Used](#technologies-used)
- [License](#license)

## Project 1: MyShell

This project is a simple shell implementation in C that can execute commands with arguments, handle I/O redirection, and run processes in the background.

### How to Run

1.  Navigate to the `OpLap1` directory:
    ```bash
    cd OpLap1
    ```
2.  Compile the source code:
    ```bash
    gcc -o myshell myshell.c
    ```
3.  Run the shell:
    ```bash
    ./myshell
    ```

## Project 2: Memory Management

This project implements a memory manager in C. It provides functionalities similar to `malloc()` and `free()` and supports four different memory allocation strategies:

*   **First-fit:** Select the first suitable block.
*   **Best-fit:** Select the smallest suitable block.
*   **Worst-fit:** Select the largest suitable block.
*   **Next-fit:** Select the first suitable block after the last allocation.

### Key Functions

-   `initmem()`: Initializes memory structures.
-   `mymalloc()`: Allocates a new block of memory.
-   `myfree()`: Deallocates a block of memory.
-   `mem_holes()`: Returns the number of free blocks.
-   `mem_allocated()`: Returns the total allocated memory.
-   `mem_free()`: Returns the total free memory.

### How to Run

1.  Navigate to the project directory:
    ```bash
    cd OpLap2/"Mandatory Assignment 2"
    ```
2.  Compile the project using make:
    ```bash
    make
    ```
3.  Run the tests:
    ```bash
    ./mem -test <test_name> <strategy>
    ```
    For example, to run all tests with the first-fit strategy:
    ```bash
    ./mem -test all first
    ```

## Java Thread Examples

The `thread_project` directory contains Java examples that demonstrate common concurrency issues and solutions:

-   `Deadlock.java`: Shows how to prevent deadlocks by ordering locks.
-   `RaceCondition.java`: Illustrates a race condition when multiple threads access shared data.
-   `Starvation.java`: Demonstrates a scenario where a thread is perpetually denied necessary resources.
-   `Account.java` and `BalanceMonitor.java`: Helper classes for the examples.

## C Thread Examples

The `thread_examples` directory contains simple C programs to illustrate basic thread operations, such as creating and executing threads in a specific order.

## Technologies Used

-   C
-   Java

## License

This project is unlicensed. You are free to use, modify, and distribute the code. It is recommended to add a license file if you plan to share this repository publicly. The [MIT License](https://opensource.org/licenses/MIT) is a good and simple choice.
