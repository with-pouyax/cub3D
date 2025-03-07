# Norminette Rules for C Files

These rules apply exclusively to C files to ensure compliance with Norminette standards:

## File Formatting
- **End with a newline**: Every file must end with a newline character.
- **Line length**: Lines must not exceed 80 characters.
- **Indentation**: Use tabs for indentation, not spaces.

## Naming Conventions
- **Variables and Functions**: Use snake_case for naming.
- **Macros and Constants**: Use uppercase letters.
- **Typedefs**: Must end with `_t`.

## Functions
- **Length**: Functions must not exceed 25 lines.
- **Responsibility**: Each function should have a single responsibility.
- **Parameters**: Limit functions to a maximum of 4 parameters.

## Control Structures
- **Braces**: Use braces `{}` even for single-line statements.
- **Spacing**: Ensure a space between control keywords (e.g., `if`, `while`) and the opening parenthesis.

## Spacing
- **Operators**: Surround operators with spaces.
- **Commas**: Follow commas with a space.
- **Trailing Spaces**: Avoid trailing spaces at the end of lines.

## Comments
- **Language**: Write comments in English.
- **Relevance**: Ensure comments are relevant and concise.
- **Avoidance**: Avoid unnecessary or redundant comments.

## Header Files
- **Include Guards**: Use include guards in header files.
- **Content**: Only include declarations, macros, and typedefs.

## Includes
- **Order**: Sort includes alphabetically.
- **System vs Local**: System includes (`<stdio.h>`) must precede local includes (`"myheader.h"`).

## Declarations
- **One per Line**: Declare one variable per line.
- **Placement**: Declare variables at the beginning of a block.

## Forbidden Practices
- **Global Variables**: Do not use global variables.
- **Goto Statement**: Avoid using `goto`.
- **Debugging**: Do not use `printf` for debugging; use proper debugging tools instead. 