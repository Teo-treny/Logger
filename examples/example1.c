#include <logger/logger.h>
#include <stdio.h>

int main(void) {

    // Log classique
    LOG_TRACE("Voici un log de trace");
    LOG_DEBUG("Voici un log de debug");
    LOG_INFO("Voici un log d'info");
    LOG_WARN("Voici un log d'avertissement");
    LOG_ERROR("Voici un log d'erreur");
    LOG_FATAL("Voici un log d'erreur critique");

    return 0;
}