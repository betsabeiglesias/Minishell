*This project has been created as part of the 42 curriculum by [aolabarr](https://github.com/aolabarr), [beiglesi](https://github.com/betsabeiglesias).*

# Minishell

## Description

Minishell is a simplified recreation of a Unix shell, written in C, that reproduces the core behavior of `bash` for everyday interactive use. It reads a command line, tokenizes it, expands variables, builds a pipeline of commands connected through pipes and redirections, and executes it by forking child processes (or running built-ins directly in the shell process when needed).

The goal of the project is to understand, from the inside, how a shell talks to the operating system: process creation (`fork`, `execve`, `wait`), file descriptor duplication (`dup`, `dup2`, `pipe`), signal handling, and the parsing/expansion logic that turns a raw line of text into something a kernel can run.

The project follows the 42 Norm and is built without using any external shell-parsing library: tokenization, syntax checking, command-list construction and the linked-list/string utilities (`libft` and a custom `liblst`) are all implemented from scratch.

## Features

Minishell implements the mandatory part of the subject:

- **Interactive prompt** (`minishell> `) with a working **history**, powered by the Readline library.
- **Command execution**, locating the binary either through the `PATH` environment variable or via a relative/absolute path.
- **Pipes** (`|`): the output of each command in a pipeline is connected to the input of the next one through a `pipe()`/`dup2()` chain, with one child process per command.
- **Redirections**:
  - `<` redirects standard input from a file.
  - `>` redirects standard output to a file (truncating it).
  - `>>` redirects standard output to a file in append mode.
  - `<<` (heredoc) reads from the current input until a line matching the given delimiter is found, without updating the history.
- **Quoting**:
  - Single quotes (`'`) prevent any interpretation of metacharacters inside them.
  - Double quotes (`"`) prevent interpretation of metacharacters except for `$` (variable expansion still happens inside them).
- **Environment variable expansion** (`$VAR`) and **exit status expansion** (`$?`), expanded to the value/status at the moment the line is parsed.
- **Signal handling**, mirroring bash's interactive behavior:
  - `Ctrl-C` prints a new line and redisplays an empty prompt.
  - `Ctrl-D` on an empty line exits the shell.
  - `Ctrl-\` is ignored in interactive mode (and reported as `Quit` while a foreground command is running, as in bash).
- A single global variable (`g_status`) is used to record the signal received, kept separate from the shell's internal data structures, as required by the subject.
- **Syntax checking** for unclosed quotes and misplaced/consecutive metacharacters (e.g. `|`, `<`, `>` used without a valid command around them).

Built-ins implemented:

| Built-in | Behavior |
|---|---|
| `echo` | Supports the `-n` option (no trailing newline). |
| `cd` | Changes directory using a relative or absolute path, and keeps `OLDPWD`/`PWD` updated. |
| `pwd` | Prints the current working directory (no options). |
| `export` | Without options; sets or updates environment variables. |
| `unset` | Without options; removes an environment variable. |
| `env` | Without options or arguments; prints the current environment. |
| `exit` | Without options; exits the shell with the appropriate status code. |

> The extra part of the subject (`&&` / `||` with parentheses for priority, and `*` wildcards) is **not implemented** in this repository.

## Project structure

```
.
├── Makefile
├── inc/
│   ├── minishell.h                         # Central header, includes everything else
│   ├── functions.h                         # Function prototypes
│   ├── variables.h                         # Structs (t_mini, t_exec, t_varenv, ...) and g_status
│   └── macros.h                            # Error codes/messages and shell constants
├── lib/
│   ├── libft/                              # Custom C standard library replacement
│   └── liblst/                             # Custom linked-list utility library
└── src/
    ├── main.c                              # Entry point, main read-eval loop
    ├── tokenization_*.c                    # Splits the input line into tokens
    ├── check_syntax_*.c, check_utils.c     # Syntax validation
    ├── parse.c, expansion_*.c              # Parsing and $VAR / $? expansion
    ├── command_list_*.c                    # Builds the list of commands to execute
    ├── execution_*.c                       # Forking, piping, redirections, waiting
    ├── builtin_*.c                         # echo, cd, pwd, export, unset, env, exit
    ├── signals_*.c                         # Signal handlers (shell / child / built-in)
    ├── environment.c, init_data.c          # Environment and shell state initialization
    └── free*.c, handle_error.c             # Memory cleanup and error reporting
```

## Instructions

### Requirements

- A Linux/macOS environment with `cc`/`gcc` and `make`.
- The Readline development library (e.g. `sudo apt install libreadline-dev` on Debian/Ubuntu).

### Compilation

```bash
git clone https://github.com/betsabeiglesias/Minishell.git
cd Minishell
make
```

The Makefile first builds `libft` and `liblst` from `lib/`, then compiles and links `minishell` with the flags `-Wall -Wextra -Werror`.

Available rules:

| Rule | Effect |
|---|---|
| `make` / `make all` | Builds the libraries and the `minishell` executable. |
| `make clean` | Removes object files (shell and libraries). |
| `make fclean` | Removes object files and the executable. |
| `make re` | `fclean` followed by `all`. |

### Running

```bash
./minishell
```

This starts the interactive prompt. Some usage examples:

```bash
minishell> echo -n "hello"
minishell> ls -l | grep .c | wc -l
minishell> cat < input.txt > output.txt
minishell> cat << EOF
heredoc line 1
EOF
minishell> echo $HOME $? $USER
minishell> export MY_VAR=42 && echo $MY_VAR   # note: '&&' is not implemented
minishell> exit
```

## Resources

Ineresting references to understand bash:

- [Bash Reference Manual (GNU)](https://www.gnu.org/software/bash/manual/bash.html)
- [Advanced Programming in the UNIX Environment, W. Richard Stevens](https://www.amazon.com/Programming-Environment-Addison-Wesley-Professional-Computing/dp/0321637739)
- [The Linux man-pages project](https://man7.org/linux/man-pages/) (`fork`, `execve`, `pipe`, `dup2`, `signal`, `waitpid`, `readline`)
- [GNU Readline Library documentation](https://tiswww.case.edu/php/chet/readline/readline.html)
