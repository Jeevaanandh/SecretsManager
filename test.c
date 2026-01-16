#include <stdio.h>
#include <termios.h>
#include <unistd.h>

void disable_echo() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void enable_echo() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int main() {
    char password[50];

    printf("Enter password: ");
    disable_echo();
    fgets(password, sizeof(password), stdin);
    enable_echo();

    printf("\nPassword entered: %s", password);
    return 0;
}
