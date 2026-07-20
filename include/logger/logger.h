/**
 * @file logger.h
 * @author Téo Trény
 * @brief Système de logs colorés avec contexte (fichier, ligne et temps)
 * @version 0.1
 * @date 2025-12-08
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

// Niveau de log
typedef enum {
    APP_LOG_TRACE = 0,
    APP_LOG_DEBUG,
    APP_LOG_INFO,
    APP_LOG_WARN,
    APP_LOG_ERROR,
    APP_LOG_FATAL,
    APP_LOG_NONE
} LogLevel_e;

/**
 * @brief Configure le niveau de log affiché
 * Par défaut : LOG_INFO
 * 
 * @param level LogLevel_e level
 */
void logger_set_level(LogLevel_e level);

/**
 * @brief Fonction internet (ne pas appeler directement)
 * 
 */
void logger_log(LogLevel_e level, const char *file, int line, const char *fmt, ...);

// MACROS UTILISATEUR

// Affiche tout, très verbeux (Gris)
#define LOG_TRACE(...) logger_log(APP_LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)

// Pour le débogage (Cyan)
#define LOG_DEBUG(...) logger_log(APP_LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)

// Informations générales (Vert)
#define LOG_INFO(...)  logger_log(APP_LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)

// Avertissements (Jaune)
#define LOG_WARN(...)  logger_log(APP_LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)

// Erreurs (Rouge)
#define LOG_ERROR(...) logger_log(APP_LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)

// Erreurs critiques (Rouge fond clignotant ou gras)
#define LOG_FATAL(...) logger_log(APP_LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

#endif