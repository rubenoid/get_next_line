# get_next_line
Write a function which returns a line read from a file descriptor, without the newline.

## Function name
get_next_line

## Prototype
int get_next_line(int fd, char **line);

## Parameters
1. file descriptor for reading
2. The value of what has been read

## Return value
- 1: A line has been read
- 0: EOF has been reached
- -1: An error happened

## External functions
read, malloc, free

## Bonus
- Use one single static variable.
- To be able to manage multiple file descriptor with your get_next_line. For example, if the file descriptors 3, 4 and 5 are accessible for reading, then you can call get_next_line once on 3, once on 4, once again on 3 then once on 5 etc. without
losing the reading thread on each of the descriptors.

## Compile
compile with the flag -D BUFFER_SIZE=xx
