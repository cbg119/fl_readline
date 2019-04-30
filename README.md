# fl_readline
Like readline - but with blood sweat and tears!

This repository will house the code for my first personal project, fl_readline. At 42 We are allowed no standard library
functions, except for very low level calls such as write and etc. fl_readline will be my implementation of the GNU
readline library with my own tweaks and modifications, using the (very old) GNU termcap library. In addition, the entire
codebase will be Norme'd, AKA it will be in compliance with my school's (42 Silicon Valley) coding standard.


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
