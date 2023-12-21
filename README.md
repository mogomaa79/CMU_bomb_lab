# CMU Bomb Lab Writeup

## Introduction

The CMU Bomb Lab is a reverse engineering challenge where participants must defuse binary "bombs" by understanding and manipulating assembly code. See "https://www.cs.cmu.edu/afs/cs/academic/class/15213-s20/www/recitations/recitation04-bomblab.pdf" for more information and helpful tips. This writeup outlines the process and tools used to successfully navigate the challenges.

## Tools

- **GDB Debugger:** For stepping through code, setting breakpoints, and inspecting registers.
- **Objdump:** Extracts and displays assembly code from binary files.
- **Ada Software (Optional):** Graphical debugger for a user-friendly assembly code representation.
- **Python (Optional):** Useful for scripting tasks or additional analysis.

## Extracting Assembly Code

To begin analysis, use objdump to extract assembly code:

```bash
objdump -d bomb_binary > dump.asm
```

## Phase 1

The assembly code for Phase 1 performs a string comparison using the `strings_not_equal` function. The goal is to input a string that matches a predefined string stored in memory. 
**Using GDB Debugger:**
   - Use GDB to examine the memory at the specified address (`$4203520`).
   - Command: `(gdb) x/s 0x402400`
   - This command displays the string stored at the memory address.
- The correct string for this phase is "Border relations with Canada have never been better."

## Phase 2
The assembly code for Phase 2 begins by taking input using `read_six_numbers` to read exactly six numbers. If this condition is not met, the bomb explodes. The subsequent checks aim to verify a specific pattern within the numbers.

Observing the assembly code with GDB reveals a for loop that checks whether each number is equal to twice the number before it. Additionally, it ensures that the first number is 1. Consequently, the correct sequence of numbers to pass this phase is 1 2 4 8 16 32.

## Phase 3

In Phase 3, the assembly code begins by allocating memory for stack and local variables. It then calls `scanf` to take two integer inputs using the format "%d %d".

1. **Input Verification:**
   - The code checks if the number of successful inputs is greater than 1 (`$1, %eax`).
   - If not, the bomb explodes using the `explode_bomb` function.

2. **Input Range Check:**
   - The first input is compared to ensure it falls within the range 1 <= x <= 7 (`cmpl $7, 8(%rsp)`).
   - If the condition is not met, the bomb explodes.

3. **Switch Statement:**
   - The assembly code utilizes a switch statement based on the value of the first input (`movl $4203983, %esi`).
   - The corresponding case statements redirect to specific code blocks based on the first input.

4. **Correct Input:**
   - To pass this phase, the second input should match the value stored in `%eax` after the switch statement.
   - A valid solution is inputting "2 707," which directs the control flow to the case statement storing 707 in `%eax`.


## Phase 4

The assembly code for Phase 4 comprises two functions: `func4` and `phase_4`. 

### Function `func4`:

The `func4` function performs a binary search operation. It takes three integer parameters (`%edx`, `%esi`, and `%edi`) and returns an integer result in `%eax`.

### Function `phase_4`:

`phase_4` begins by taking two integer inputs using `sscanf` with the format "%d %d". If the number of successful inputs is not equal to 2 or if the second input is greater than 14, the bomb explodes.

The `phase_4` code calls the recursive function `func4`. With parameters `%edx = 14`, `%esi = 0`, and `%edi` taken from the second input, the function performs a binary search operation. The result of this operation is stored in `%eax`. The subsequent comparisons with `%eax` determine whether the bomb should explode or not.

The input pair should correspond to a valid range for this operation. Choosing values such as `7 0` or `3 0` or `0 0` adheres to the binary search logic. By tracing the assembly code with GDB to see register values, I found these values to work.


## Phase 5

1. **String Length Check:**
   - The code calls the `string_length` function to determine the length of the input string. If the length is not 6, the bomb explodes.

2. **Character Transformation Loop:**
   - The function then enters a loop, iterating over each character of the input string.
   - For each character, it performs a bitwise AND operation with 1111 and accesses an array hidden in memory with the resulting index.
   - The obtained values are stored in a new string.

3. **Comparison with "flyers":**
   - After the loop, the new string is compared with the constant string "flyers."
   - If the strings are not equal, the bomb explodes.

4. **Reverse Engineering the Hidden Array:**
   - To successfully defuse Phase 5, we need to reverse-engineer the hidden array's indexes.
   - The correct order of indexes is 3, 14, 13, 4, 5, 6, corresponding to the ASCII values 'ionefj'.

The input string that, when processed through these steps, results in the word "flyers" is "ionefj".


# Solving CMU Bomb Lab - Phase 6

## Initial Analysis

The assembly code for Phase 6 involves several loops and checks, making it a more complex challenge. I first analyzed the initial lines of the assembly code, which called `read_six_numbers` and checked the input for certain conditions using loops. Specifically, it verified that the six numbers were in the range of 0 to 6 (inclusive) and ensured that no number was repeated.

Considering the limited permutations (720 in total), two different approaches were employed to find the correct input.

## Approach 1: Brute-Force with Python
I implemented a Python script 'brute.py' utilizing the `subprocess` and `itertools` libraries to execute the bomb binary with all possible permutations. The script generated a file with initial lines and each permutation, then executed the bomb, checking for the correct answer.

## Approach 2: Reverse-engineering the answer using GDB & Ada
Now we'd go through all the rest of the code. It first enters a loop to calculate 7 - value for all the values. Then another loop shows the values being used to access some nodes in some order. The values in these nodes I found they are Linked List nodes carrying value and next pointer taking a total of 16 bytes after padding. 

The values in these nodes found using GDB Debugger are:
1. 332
2. 168
3. 924
4. 691
5. 477
6. 443

Another loop is then used to check something. The function connects all the linked list nodes by the order of the numbers inputted after the complement by seven. Another function is then used to check that every node values in order is larger than the one after it. So, the order of node values should be:
924, 691, 477, 443, 332, 168. 
Which corresponds to 3 4 5 6 1 2, which can be mapped to a shift after complement by 7:
4 3 2 1 6 5, which is the same answer found after brute-forcing the permutations.
