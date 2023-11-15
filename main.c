#include "shell.h"

int main(int argc, char **argv) {
    info_t info[] = { INFO_INIT };
    int file_descriptor = 2;

    // Using inline assembly to manipulate the file descriptor
    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (file_descriptor)
        : "r" (file_descriptor));

    // Check if there is exactly one command-line argument
    if (argc == 2) {
        // Try to open the specified file for reading
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            // Handle file opening errors
            if (errno == EACCES) {
                exit(126);
            } else if (errno == ENOENT) {
                _eputs(argv[0]);
                _eputs(": 0: Can't open ");
                _eputs(argv[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            } else {
                return EXIT_FAILURE;
            }
        }
        info->readfd = fd; // Assign the file descriptor
    }

    // Initialize the environment list and read command history
    populate_env_list(info);
    read_history(info);

    // Execute the shell program
    hsh(info, argv);

    return EXIT_SUCCESS;
}
