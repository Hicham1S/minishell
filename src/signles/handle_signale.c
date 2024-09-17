#include "../tokenization/tokens.h"

// Handle SIGINT (Ctrl+C)
void sigint_handler(int signum)
{
    (void)signum;  // Suppress unused parameter warning
    g_signal_flag = 1;  // Set signal flag to indicate SIGINT was received
    write(STDOUT_FILENO, "\n", 1);  // Move to a new line
    rl_on_new_line();  // Reset readline
    rl_replace_line("", 0);  // Clear the current input line
    rl_redisplay();  // Redisplay the prompt
}

// Handle EOF (Ctrl+D)
void handle_eof(void)
{
    write(STDOUT_FILENO, "exit\n", 5);
    exit(EXIT_SUCCESS);  // Exit the shell
}
