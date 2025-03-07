# libft - Custom C Standard Library Implementation

![Libft](https://user-images.githubusercontent.com/58959408/150704272-0d7b454d-2872-4695-aade-e5bc9c3b79aa.jpg)


Welcome to my **libft** repository! 🚀  
This project is my implementation of a subset of the **C Standard Library functions**, written in **C**, as part of the **42 School curriculum**.  
The library provides essential **memory management, string manipulation, character checking, and file descriptor operations**.

---

## 📌 Functions List & Detailed Descriptions

### 1️⃣ Memory Functions

1. **`ft_memset(void *s, int c, size_t n)`**  
   Fills `n` bytes of the memory block pointed to by `s` with the byte `c`.  
   Equivalent to `memset()` in `<string.h>`.  
   Useful for initializing memory to a specific value.

2. **`ft_bzero(void *s, size_t n)`**  
   Writes `n` bytes of zero (`\0`) to the memory block pointed to by `s`.  
   Equivalent to `bzero()`, though in modern C, `memset(s, 0, n)` is preferred.  
   Used to safely initialize memory.

3. **`ft_memcpy(void *dest, const void *src, size_t n)`**  
   Copies `n` bytes from `src` to `dest`.  
   Does **not** handle overlapping memory regions.  
   If overlapping is a concern, use `ft_memmove()`.

4. **`ft_memmove(void *dest, const void *src, size_t n)`**  
   Similar to `ft_memcpy()`, but **handles overlapping memory regions**.  
   Copies bytes in a way that prevents data corruption.

5. **`ft_memchr(const void *s, int c, size_t n)`**  
   Scans the first `n` bytes of `s` to find the first occurrence of `c`.  
   Returns a pointer to the matching byte if found, or `NULL` otherwise.

6. **`ft_memcmp(const void *s1, const void *s2, size_t n)`**  
   Compares two memory blocks byte by byte for `n` bytes.  
   Returns `0` if they are identical; otherwise, returns a positive or negative value.

7. **`ft_calloc(size_t count, size_t size)`**  
   Allocates memory for `count` elements of `size` bytes each and initializes all bytes to zero.  
   Unlike `malloc()`, this ensures safe allocation by setting the memory to `0`.

---

### 2️⃣ String Functions

8. **`ft_strlen(const char *s)`**  
   Returns the length of a null-terminated string, **excluding** the null terminator.

9. **`ft_strlcpy(char *dst, const char *src, size_t dstsize)`**  
   Copies up to `dstsize - 1` characters from `src` to `dst`, ensuring null-termination.  
   Returns the length of `src`.

10. **`ft_strlcat(char *dst, const char *src, size_t dstsize)`**  
    Concatenates `src` to `dst` without exceeding `dstsize`.  
    Ensures null-termination and returns the total length the string would have been.

11. **`ft_strchr(const char *s, int c)`**  
    Returns a pointer to the **first occurrence** of `c` in `s`.  
    Returns `NULL` if `c` is not found.

12. **`ft_strrchr(const char *s, int c)`**  
    Returns a pointer to the **last occurrence** of `c` in `s`.

13. **`ft_strnstr(const char *haystack, const char *needle, size_t len)`**  
    Searches for the first occurrence of `needle` in `haystack`, looking at most `len` characters.  
    Returns `NULL` if `needle` is not found.

14. **`ft_strncmp(const char *s1, const char *s2, size_t n)`**  
    Compares two strings up to `n` characters.  
    Returns `0` if they are equal; otherwise, returns a positive or negative value.

15. **`ft_atoi(const char *str)`**  
    Converts a string to an integer.  
    Handles leading whitespace, optional `+` or `-` signs, and stops at the first non-digit character.

---

### 3️⃣ Character Checking and Conversion

16. **`ft_isalpha(int c)`**  
    Checks if `c` is an **alphabetic** character (`a-z` or `A-Z`).

17. **`ft_isdigit(int c)`**  
    Checks if `c` is a **digit** (`0-9`).

18. **`ft_isalnum(int c)`**  
    Checks if `c` is **alphanumeric** (either a letter or a digit).

19. **`ft_isascii(int c)`**  
    Checks if `c` is within the **ASCII range** (0 to 127).

20. **`ft_isprint(int c)`**  
    Checks if `c` is a **printable** character.

21. **`ft_toupper(int c)`**  
    Converts a lowercase letter to uppercase.

22. **`ft_tolower(int c)`**  
    Converts an uppercase letter to lowercase.

---

### 4️⃣ File Descriptor Functions

31. **`ft_putchar_fd(char c, int fd)`**  
    Writes a single character `c` to the file descriptor `fd`.

32. **`ft_putstr_fd(char *s, int fd)`**  
    Writes the string `s` to the file descriptor `fd`.

33. **`ft_putendl_fd(char *s, int fd)`**  
    Writes the string `s` followed by a newline (`\n`) to `fd`.

34. **`ft_putnbr_fd(int n, int fd)`**  
    Writes the integer `n` to the file descriptor `fd`.

---

## 🛠 Building the Library

- Run `make` to compile the **libft** static library (`libft.a`).
- Run `make clean` to remove object files.
- Run `make fclean` to remove object files and the compiled library.
- Run `make re` to clean and rebuild everything.

---

## 🤝 Contributing

Feel free to **fork the repository** and use it in your projects! 🚀

---

## 📜 License

This project is licensed under the **MIT License**.

---

If you find this repository helpful, consider giving it a ⭐ on GitHub!  
Happy coding! 😊🚀
