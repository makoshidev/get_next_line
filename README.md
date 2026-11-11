*This project has been created as part of the 42 curriculum by mshikhov.*

## Description
`get_next_line` is a function written in C that reads and returns one line at a time from a file descriptor (`fd`), ending with a newline character `\n` if present, until the end of the file is reached. The main goal of the project is to master file I/O operations, static variable management, and heap memory allocation without causing leaks.

## Instructions

### Compilation
The project is compiled along with source code or a main test file using `cc` with the `-D BUFFER_SIZE=n` flag:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
```

If `BUFFER_SIZE` is not specified during compilation, the default value defined in `get_next_line.h` (`42`) is used.

### Usage Example
```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Algorithm & Technical Choices
The implementation relies on a single static string pointer (`remainder`) to retain unread data between function calls:
1. **Buffer Read Loop (`read_file`)**: The function checks if a newline is already present in `remainder`. If not, it reads from the file descriptor in chunks of size `BUFFER_SIZE` and appends each chunk using `update_remainder`. Reading stops immediately once a `\n` is encountered or when EOF (`bytes_read == 0`) is hit.
2. **Line Extraction (`get_return`)**: Once a complete line or EOF is reached, the line to return (up to and including `\n`) is extracted via `ft_substr`. The extracted part is severed from `remainder`, leaving only the subsequent data for future calls.
3. **Memory Cleanup**: If EOF is reached and the remaining buffer is empty, or if an error occurs, the static buffer is freed and reset to `NULL` to prevent memory leaks.

## Resources
- [Linux man pages: `read(2)`, `malloc(3)`, `free(3)`](https://man7.org/linux/man-pages/)
- GNU C Library documentation on static variables and file descriptors.

### AI Usage
AI was used during the refactoring and debugging phase:
- Code review to detect subtle edge-case memory leaks and buffer boundaries in `get_return`.
- Structuring this documentation in compliance with the 42 subject requirements.