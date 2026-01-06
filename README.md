# Push_Swap

*This project has been created as part of the 42 curriculum by hlaaz.*

## Description

**Push_swap** is a highly structured algorithmic challenge that requires sorting a set of unique integer values using two stacks and a limited set of instructions. The goal is to write a C program that calculates and displays the shortest sequence of actions to sort the data. This project focuses on understanding complexity, rigor in C programming, and the implementation of efficient sorting algorithms.

## Instructions

### Compilation

The project is compiled using a `Makefile` with the flags `-Wall`, `-Wextra`, and `-Werror`.

* To compile the mandatory **push_swap** program:


```bash
make

```


* To compile the bonus **checker** program:


```bash
make bonus

```



### Execution

The programs take a list of integers as arguments. The first argument is placed at the top of the stack.

**Push_swap example:**

```bash
./push_swap 2 1 3 6 5 8

```

**Checker example:**

```bash
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG

```

### Available Operations

The following instructions are used to manipulate the stacks:

*
  **sa / sb / ss**: Swap the first two elements at the top of stack a, b, or both.


*
  **pa / pb**: Push the top element from one stack to the top of the other.


*
  **ra / rb / rr**: Shift all elements up by one (first becomes last).


*
  **rra / rrb / rrr**: Shift all elements down by one (last becomes first).



## Resources

*
  **Sorting Algorithms**: Research into various algorithms to meet the benchmarks (e.g., sorting 500 numbers in under 5500 operations).


*
  **Complexity**: Understanding  vs  to optimize the instruction count.


*
  **AI Usage**: AI was used to assist in designing the `get_next_line` logic for the bonus checker and for brainstorming the stack parsing structure. All AI-generated code was thoroughly reviewed and tested to ensure it complies with the Norm and is fully understood by the author.
