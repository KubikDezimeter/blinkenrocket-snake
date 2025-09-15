#include "Game.h"
#include "TerminalDisplay.h"

int main() {
    Game game {};
    TerminalDisplay display {};
    display.show(game.render());

    return 0;
}
