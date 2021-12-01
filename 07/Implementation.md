# Implementation
In this document, I provide more information on my implementation of the VM Translator. As expected, this project only implements the push/pop and the arithmetic and logical commands.

The VM code follows this set of rules:
- Every line contains only one command.
- The command falls into one of these categories:
- Push/pop commands.
- Arithmetic-logical commands.

### Push/Pop Commands
| Command              | Notes                                                                                                  |
| :------------------- | :----------------------------------------------------------------------------------------------------- |
| `push segment index` | `segment` is one of the options below. An `index` is a nonnegative number.                             |
| `pop segment index`  | `segment` is one of the options below (**except for `constant`**). An `index` is a nonnegative number. |

Valid segments:
- `argument`
- `local`
- `static`
- `constant` (**invalid for `pop`**)
- `this`
- `that`
- `pointer`
- `index`

### Arithmetic-Logical Commands
- Arithmetic: `add`, `sub`, `neg`.
- Comparison: `eq`, `gt`, `lt`.
- Logical: `and`, `or`, `not`.

## The VM Translator
The main program that drives the translation follows this algorithm:
- Check the arguments passed through the terminal. A helper function will implement this. The helper function will validate and return an object with the input and output filenames (and their paths).
- Create the Parser and CodeWriter objects.
- It enters a loop that continues as long as `find_next_command` routine returns true.
    - Call the parser to get the current command type.
    - Enter a switch scenario.
        - If it is an arithmetic command, translate.
        - If it is a push or pop command, translate.
        - Default to print the current line along with an error message. Break the loop.
- On termination, and if no errors have occurred, print a successful translation message.

## The Parser
[This article](https://tomassetti.me/guide-parsing-algorithms-terminology/) gives a practical approach to the implementation of parsers. I use it as a starting point for my solution.

On another note, I will follow the recommended API except for one routine on the parser. As I've done in project 6, I will combine the `hasMoreLines` and the `advance` functions into one. You can find more information about this issue on the [source code for the parser of project six](<../06/Hack Assembler/Hack Assembler/Parser.cpp>) and in [this thread](http://nand2tetris-questions-and-answers-forum.52.s1.nabble.com/hasMoreLines-and-advance-Methods-How-to-properly-implement-them-td4036441.html).

