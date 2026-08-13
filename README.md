# 🐚 minishell - 42 School

> *As beautiful as a shell. A deep dive into creating a functional UNIX command interpreter from scratch, exploring parsing, multi-processing, and system interactions.*

## 💡 About The Project

**minishell** is a milestone project in the 42 School curriculum where you must recreate a mini version of `bash`. It reads user input, parses it, and executes commands just like a real UNIX shell. 

This project is a massive leap forward, combining the multi-processing concepts learned in `pipex` with extremely rigorous string manipulation and memory management. It requires building a custom Lexer and Parser to understand complex command lines involving pipes (`|`), redirections (`<`, `>`, `<<`, `>>`), quotes (`'` and `"`), and environment variables (`$`).

![minishell](/assets/mini_0.jpg)

---

## 🧠 Deep Dive: Core Concepts Explored

### 1. Lexing & Parsing (The Front-End)
Before a command can be executed, the raw string typed by the user must be understood by the program:
*   **Tokenization (Lexer):** The raw string is broken down into meaningful chunks called tokens (e.g., commands, flags, strings, operators). 
*   **Quote Handling:** The shell must differentiate between single quotes `'` (where everything is literal) and double quotes `"` (where environment variables like `$USER` must be expanded into their actual values).
*   **Syntax Analysis (Parser):** The tokens are organized into a logical structure (often a linked list of commands or an Abstract Syntax Tree) that dictates how data will flow between pipes and files.

### 2. Execution & Process Management (The Back-End)
Once the input is parsed, the shell must act as an orchestrator for the operating system:
*   **Pipes & Redirections:** Expanding on `pipex`, minishell must dynamically create `pipe()` channels and use `dup2()` to route standard input and output through an arbitrary number of commands and file redirections (including `<<` heredocs).
*   **Forking:** For every external command (like `ls` or `grep`), the shell uses `fork()` to create a child process. The parent waits (`waitpid`) and retrieves the exit status code (which is then stored in the special variable `$?`).

### 3. Built-in Commands & Environment
Not all commands are external binaries; some must be executed directly by the shell itself to modify its own internal state:
*   **Built-ins:** You must implement exact replicas of `cd`, `echo` (with `-n`), `pwd`, `export`, `unset`, `env`, and `exit`.
*   **Dynamic Environment:** The shell inherits an array of environment variables upon startup. This array must be converted into a dynamic data structure (like a linked list) so variables can be added, modified, or removed on the fly via `export` and `unset`.

### 4. Signal Handling
A robust shell must not crash or exit when the user spams keyboard shortcuts:
*   **`sigaction`:** The shell must intercept and handle POSIX signals. For example, pressing `Ctrl+C` (`SIGINT`) should display a new prompt on a new line instead of killing the shell, and `Ctrl+\` (`SIGQUIT`) must be ignored in the main prompt but handled correctly if a child process is running.

---

## 🛠️ Architecture Overview

### The Read-Eval-Print Loop (REPL)
*   **Read:** Uses the `readline` library to prompt the user and capture input while maintaining a command history.
*   **Evaluate:** Passes the input through the Lexer (to create tokens), the Expander (to resolve `$VARS`), and the Parser (to build the command table).
*   **Print (Execute):** The Executor iterates through the command table, sets up pipes/redirections, and either executes built-ins directly or forks for `execve`.

### Error Handling & Edge Cases
*   Memory leaks must be strictly avoided, especially when a command fails or a signal interrupts execution.
*   File descriptors must be meticulously closed to prevent the system from running out of available open files (FD leaks).

![some funny commands](/assets/mini_1.jpg) 

---

## 🚀 Compilation & Usage

### Instructions
1. Clone the repository containing the project files.
2. Ensure the `readline` library is installed on your system.
3. Compile the project using the provided `Makefile`.

### Compilation
```bash
make
```

### Usage
Execute the program to launch your interactive shell:

```bash
./minishell
```

Once inside, you can run standard UNIX commands, chain them with pipes, and redirect outputs:
```bash
minishell$ echo "Hello 42" | grep 42 > output.txt
minishell$ cat output.txt
Hello 42
minishell$ exit
```