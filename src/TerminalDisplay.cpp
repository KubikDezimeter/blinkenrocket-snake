#include "TerminalDisplay.h"

void TerminalDisplay::show(Frame frame) const {
    std::cout << '\n';
    std::cout << "╔════════╗\n";
    for (auto& row : frame) {
        std::cout << "║";
        for (auto& pixel : row) {
            std::cout << (pixel ? "O" : " ");
        }
        std::cout << "║\n";
    }
    std::cout << "╚════════╝\n";
}
