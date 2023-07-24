#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char* my_getline() {
    static char buffer[BUFFER_SIZE];
    static int buffer_index = 0;
    static int buffer_size = 0;

    char* line = NULL;
    int line_index = 0;
    char c;

    while (1) {
        if (buffer_index >= buffer_size) {
            buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            if (buffer_size <= 0) {
                if (line_index > 0) {
                    // If we've read some characters before encountering EOF or error,
                    // allocate memory for the line and return it.
                    line = (char*)malloc(line_index + 1);
                    if (line) {
                        for (int i = 0; i < line_index; i++) {
                            line[i] = buffer[i];
                        }
                        line[line_index] = '\0';
                    }
                }
                return line; // Return NULL at EOF or error
            }
            buffer_index = 0;
        }

        c = buffer[buffer_index++];
        if (c == '\n') {
            line = (char*)malloc(line_index + 1);
            if (line) {
                for (int i = 0; i < line_index; i++) {
                    line[i] = buffer[i];
                }
                line[line_index] = '\0';
            }
            return line;
        } else {
            // Expand the line buffer and store the character
            if (line_index % BUFFER_SIZE == 0) {
                line = (char*)realloc(line, line_index + BUFFER_SIZE + 1);
                if (!line) {
                    perror("Memory allocation error");
                    exit(EXIT_FAILURE);
                }
            }
            line[line_index++] = c;
        }
    }
}

int main() {
    char* line;
    
    while (1) {
        printf("Enter a line (or press Ctrl+D to exit): ");
        line = my_getline();
        if (!line) {
            // NULL returned by my_getline indicates EOF or error
            break;
        }
        printf("You entered: %s\n", line);
        free(line); // Remember to free the allocated memory
    }

    return 0;
}

