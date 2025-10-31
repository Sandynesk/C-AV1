#include "utils.h"
#include <string.h> // Para fgets e strcspn

/**
 * @brief Implementação (placeholder) da leitura segura.
 * Vamos usar isso mais tarde para o modo interativo.
 */
int read_safe_string(char *buffer, int size) {
    
    if (fgets(buffer, size, stdin) != NULL) {
        // Remove o '\n' (quebra de linha) do final, se fgets o capturou
        buffer[strcspn(buffer, "\n")] = '\0';
        return 0; // Sucesso
    }
    return -1; // Erro ou EOF
}