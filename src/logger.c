#include "logger.h"

// Niveau actuel (variable statique privée)
static LogLevel_e current_level = APP_LOG_INFO;

// Codes couleurs ANSI
#define RESET   "\x1b[0m"
#define GREY    "\x1b[90m"
#define CYAN    "\x1b[36m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define RED     "\x1b[31m"
#define FATAL   "\x1b[37;41m" // Blanc sur fond rouge

static const char* level_strings[] = {
    "TRACE", "DEBUG", "INFO ", "WARN ", "ERROR", "FATAL"
};

static const char* level_colors[] = {
    GREY, CYAN, GREEN, YELLOW, RED, FATAL
};

void logger_set_level(LogLevel_e level) {
    current_level = level;
}

void logger_log(LogLevel_e level, const char *file, int line, const char *fmt, ...) {
    // Filtrage par niveau
    if (level < current_level) return;

    // 1. Récupération de l'heure
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char time_buf[20];
    strftime(time_buf, 20, "%H:%M:%S", tm_info);

    // 2. Affichage du préfixe : [HEURE] [NIVEAU] fichier:ligne
    // On utilise stderr pour les logs (bonnes pratiques), stdout pour le programme
    fprintf(stderr, "%s %s[%s]%s \x1b[90m%s:%d:\x1b[0m ", 
            time_buf, 
            level_colors[level], 
            level_strings[level], 
            RESET,
            file, 
            line);

    // 3. Affichage du message utilisateur (va_list)
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    // 4. Retour à la ligne et reset couleur
    fprintf(stderr, RESET "\n");
}