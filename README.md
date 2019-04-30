# fl_readline
Like readline - but with blood sweat and tears!

This repository will house the code for my first personal project, fl_readline. At 42 We are allowed no standard library
functions, except for very low level calls such as write and etc. fl_readline will be my implementation of the GNU
readline library with my own tweaks and modifications, using the (very old) GNU termcap library. In addition, the entire
codebase will be Norme'd, AKA it will be in compliance with my school's (42 Silicon Valley) coding standard.

# Why?
Why not just use something like `ncurses`? Or, you know, `readline`?
Well, because 42 said so. If you didn't already know, I attend a free coding school in Silicon Valley called 42. At 42, we 
are disallowed the use of library functions. One of the first projects at 42 is libft, in which the student recreates
several standard library functions such as atoi, putchar, memmove, etc. Throughout the student's time at 42, they are
encouraged to add more and more functions. In addition we are also required to conform our code to `The Norme`, which
includes several restrictions such as limiting functions to 25 lines per function, 5 functions per file, no `for` loops,
and among other things as well.

# Features

* Full line edition support using `termcap` library
* History support using `t_h_list` struct
* Basic copy/cut/paste features


# Controls
* `LEFT` and `RIGHT` - Moves cursor
* `UP` and `DOWN` - Navigate through history
* `CTRL + LEFT` and `CTRL + RIGHT` - Move to previous/next word
* `HOME` and `END` - Move to beginning/end of line
* `CTRL + c` and `CTRL + SHIFT + x` - Cut line starting before/after cursor
* `CTRL + c` and `CTRL + SHIFT + c` - Copy line starting before/after cursor
* `CTRL + v` and `CTRL + SHIFT + v` - Paste clipboard starting before/after cursor


# How to use
Below is a sample main on how one can use the library (when it is, of course, compiled with your own libft)

```c
#include "libft.h"
#include "fl_readline.h"

int		main(void)
{
	t_h_list	history;
	char		*command;

	if (!fl_term_check())
		return (1);
	fl_init_history(&history);
	while (1)
	{
		command = fl_readline(&history, C_BLUE"$> "C_WHITE);
		if (ft_strequ(command, "exit"))
			break ;
		ft_putchar('\n');
		free(command);
	}
	fl_free_history(&history);
	free(command);
	return (0);
}
```

# Additional details
Overall, the code for this project is easy to follow. It all revolves around the `t_line` struct, which stores things such
as cursor position, window dimensions, the actual line, etc. Another very important part of the code is the
`fl_update_cursor(t_line *line)` function, which allows us to control where the cursor is based on a single integer offset.
More documentation will be provided in the future. Most likely.
