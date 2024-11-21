#ifndef SUGESTION_H
#define SUGESTION_H

#include <vector>
#include <string>
#include <termios.h>
#include <unistd.h>

// Função para exibir as sugestões no terminal
void printSuggestions(const std::vector<std::string>& suggestions, const std::string& prefix);

// Função para configurar o terminal em modo de leitura de caracteres (sem esperar Enter)
void setTerminalMode(bool enable);

#endif // SUGESTION_H
