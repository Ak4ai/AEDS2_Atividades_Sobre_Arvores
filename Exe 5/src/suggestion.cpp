#include "suggestion.h"
#include <iostream>

void printSuggestions(const std::vector<std::string>& suggestions, const std::string& prefix) {
    // Limpa o console (funciona para a maioria dos terminais)
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Digite as primeiras letras da palavra para sugestões (aperte 'ESC' para sair):" << std::endl;
    std::cout << "Prefixo atual: " << prefix << std::endl;
    std::cout << "Sugestões:" << std::endl;

    // Exibe as sugestões
    for (const std::string& suggestion : suggestions) {
        std::cout << suggestion << std::endl;
    }
}

void setTerminalMode(bool enable) {
    static struct termios oldt, newt;
    if (enable) {
        // Configura o terminal para não esperar por Enter
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        // Restaura o modo padrão do terminal
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}
