# minishell
![C](https://img.shields.io/badge/C-5C6D7E?style=flat-square&logo=c&logoColor=A8B9CC) ![Linux](https://img.shields.io/badge/Linux-2C6BED?style=flat-square&logo=linux&logoColor=white)

![parsing](https://img.shields.io/badge/-parsing-6B6B6B?style=flat-square) ![pipes](https://img.shields.io/badge/-pipes-6B6B6B?style=flat-square) ![fork & execve](https://img.shields.io/badge/-fork%20%26%20execve-6B6B6B?style=flat-square) ![signal handling](https://img.shields.io/badge/-signal%20handling-6B6B6B?style=flat-square) ![variable expansion](https://img.shields.io/badge/-variable%20expansion-6B6B6B?style=flat-square) ![glob matching](https://img.shields.io/badge/-glob%20matching-6B6B6B?style=flat-square)

> **What this is:** A small Unix shell\
> **Context:** A 42 school project\
> **Dev time:** several months\
> **Team size:** 2\
> **Role:** project lead

![screenshot](demo/minishell_demo.png)

## Usage

```bash
make
./minishell
```

## Overview

- ~6,500 lines of C, including our partially-implemented `libc`
- Builtins: `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Pipe chains `a | b | c`
- Redirections with `<`, `>`, `>>` and heredocs
- Expansion of `$VAR` and `$?`, with quote semantics (`'` and `"`)
- Signals handled per context (prompt, heredoc, child process)
- Invalid input is rejected with an error naming the first offending token
- External commands resolved via `PATH` and relative paths
- Integrated readline prompt with history
- Bonus: glob expansion for `*`
- Bonus: `&&` and `||` with bash precedence and `()` for grouping

## Architecture

    input -> scanner -> token validator -> parser -> expander -> executor

## Coding standard

Written to the 42 Norm (no more than 25 lines per function, no more than 80 characters per line).
