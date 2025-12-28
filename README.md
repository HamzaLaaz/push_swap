# push_swap
This project is one of the most important algorithmic challenges in the 42 curriculum. It teaches you complexity, sorting, and strict memory management.

Here is a step-by-step strategy to get 100/100 (plus bonuses) on **Push_swap**.

---

### Phase 1: The Foundation (Parsing & Structures)
Don't rush into sorting. If your program crashes on bad input, you fail immediately.

1.  **Data Structure:**
    *   Use a **Doubly Linked List**.
    *   Why? You need access to the `next` (top) and `prev` (bottom) nodes instantly for operations like `rra` (Reverse Rotate).
    *   Struct suggestion:
        ```c
        typedef struct s_stack
        {
            int             value;
            int             index;          // useful for algorithm
            int             cost;           // useful for algorithm
            struct s_stack  *target_node;   // useful for algorithm
            struct s_stack  *next;
            struct s_stack  *prev;
        } t_stack;
        ```

2.  **Parsing Arguments:**
    *   Handle both cases: `./push_swap 1 2 3` AND `./push_swap "1 2 3"`.
    *   **Split:** Use a split function to separate strings by spaces.
    *   **Validation:** Check for non-digits, `INT_MAX`, `INT_MIN` limits, and **duplicates**.
    *   *Tip:* Write your own `atol` (long) to check for integer overflows easily.

---

### Phase 2: The Operations
Implement the 11 operations exactly as described.
*   `sa`, `sb`, `ss`
*   `pa`, `pb`
*   `ra`, `rb`, `rr`
*   `rra`, `rrb`, `rrr`

**Crucial:** Create a separate function for each, and have them print the instruction (e.g., `write(1, "sa\n", 3)`).
**Test:** Create a tiny `main` to manually run `sa`, `pb`, etc., and print the list to ensure the pointers are moving correctly. If you lose a link here, you get segfaults later.

---

### Phase 3: Tiny Sorts (Hardcoded)
Algorithms are too heavy for small stacks. Hardcode the logic for efficiency.

1.  **Stack Size 2:**
    *   If `a > a->next`, just `sa`.
2.  **Stack Size 3:**
    *   There are only 5 unsorted states. Use `if/else` logic to solve them in 1 or 2 moves.
    *   Example: If the biggest number is at the top, `ra`. Then check again.
3.  **Stack Size 4 & 5:**
    *   Push the smallest number(s) to Stack B (`pb`).
    *   Sort the remaining 3 in Stack A using your "Size 3" logic.
    *   Push the numbers back from B to A (`pa`).

---

### Phase 4: The Big Algorithm (100 & 500 Numbers)
**Do not use Radix Sort** if you want 100/100. Radix is stable but often uses too many moves for the 500-number benchmark (you need < 5500 moves).

**Recommended Algorithm: The "Turk" / "Greedy Cost" Algorithm**
This algorithm calculates the "cost" (number of moves) to put a number in the right place and executes the cheapest move.

**Logic Flow:**
1.  **Push to B:** Push all nodes from A to B until only 3 nodes remain in A. (Optional optimization: Don't push the largest 3 nodes, or keep the Median).
2.  **Sort A:** Sort the 3 nodes remaining in A.
3.  **Calculate Target Positions:** For every node in B, look at A. Where does this node belong in A?
    *   *Logic:* It belongs above the smallest number in A that is *bigger* than itself.
4.  **Calculate Cost:** For every node in B, calculate how many moves (`ra`, `rb`, `rra`, `rrb`) it takes to get that node to the top of B *AND* its target position to the top of A.
5.  **Execute Cheapest:** Find the node in B with the lowest cost. Perform the moves (optimize using `rr` or `rrr` if both need to rotate in the same direction). Push to A (`pa`).
6.  **Repeat:** Do this until B is empty.
7.  **Final Align:** Rotate A until the smallest number is at the top.

**Why this works:** It adapts to the data rather than forcing a bit-wise sort. It consistently hits ~600 moves for 100 numbers and ~4800 for 500 numbers.

---

### Phase 5: The Bonus (Checker)
This is easy if you did Phase 1 & 2 cleanly.
1.  Copy your parsing and operations files.
2.  Use `get_next_line` (or similar) to read from Standard Input.
3.  For every line read (e.g., "sa\n"), call the corresponding function (suppress the output writing for the checker).
4.  At the end, check:
    *   Is Stack B empty?
    *   Is Stack A sorted?
    *   Print "OK" or "KO".

---

### Phase 6: Validation & Debugging
1.  **Visualizer:** You **must** use a visualizer. It helps you see *why* your sort is failing. Search GitHub for "push_swap_visualizer" (there are many made by 42 students).
2.  **Benchmarks:**
    *   Generate 100 random numbers: `ARG=$(ruby -e "puts (1..100).to_a.shuffle.join(' ')"); ./push_swap $ARG | wc -l`
    *   Ensure no leaks: `valgrind ./push_swap ...`

### Summary Checklist for Success:
*   [ ] Handle "string" arguments vs "list" arguments.
*   [ ] Handle Integer Overflows (MAX/MIN).
*   [ ] Double Linked List implementation.
*   [ ] Operations (`sa`, `rra`, etc.) strictly tested.
*   [ ] Hardcoded logic for size 3, 4, 5.
*   [ ] Cost calculation algorithm for 100/500.
*   [ ] **Norminette** compliant.
*   [ ] **Makefile** does not relink.
