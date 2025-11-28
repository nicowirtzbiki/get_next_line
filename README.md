# get_next_line

A minimal, robust implementation of line-by-line file reading in C.

## Overview

`get_next_line` returns the next line available from a given **file descriptor** (file, STDIN, pipe, socket, …). 
Each call reads as much data as needed from the FD, stores incomplete data between calls, and returns exactly **one line**, **including the trailing `\n**` when present.
If the end of file is reached without a final newline `\n`, get_next_line returns the last line without a `\n`.

> This behavior follows the official requirements of the 42 project get_next_line, including the use of static storage to maintain state across calls.

### Function Contract

- **Input**: A valid file descriptor`fd` opened for reading.
- **Output**: A pointer to a newly allocated C-string containing the next line from `fd`:
  - If the line ends with `\n`, the returned _string_ **includes** that `\n`.
  - If the file ends without a trailing newline `\n`, the returned _string_ does **not** include `\n`.

- **Internal Persistence**: get_next_line uses a **static stash** to hold leftover data between function calls. This allows reconstruction of lines that span multiple read() operations.

### Error Handling and Return

- `get_next_line` returns **`NULL`** if:

  - `fd` is invalid;
  - A `read()` error occurs;
  - End of file is reached (EOF) **and** no buffer data remains.

- If successful, it returns an allocated _string_ (then the user must call `free()`).

### Multi-FD Support (Bonus)

On get_next_line_bonus.c, a static stash is maintained per FD, via an array indexed by file descriptor.