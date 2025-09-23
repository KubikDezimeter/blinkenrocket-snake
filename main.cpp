#include "PongGame.h"
#include "TerminalDisplay.h"
#include <ctime>
#include <threads.h>

int main() {
    PongGame game {};
    TerminalDisplay display {};

    struct timespec sleeptime {.tv_nsec = 500 * 1000000};

    do {
        display.show(game.render());
        thrd_sleep(&sleeptime, NULL);
    } while (!game.step());

    return 0;
}
