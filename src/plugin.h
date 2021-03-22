
/*
 *    plugin.h
 *
 *      Copyright 2021 by Dmitriy Kapitanov (dkapitanov84@gmail.com)
 *
 */

#ifndef _INCLUDE_PLUGIN_H
#define _INCLUDE_PLUGIN_H
#if defined HAVE_PLUGINS

#include "config.h"

#ifdef __APPLE__
    #define PLUGIN_EXTENSION ".dylib"
#else
    #define PLUGIN_EXTENSION ".so"
#endif

#define MAX_EXTENSIONS_COUNT 512
#define PLUGIN_ENTRY_FUNCTION "plugin_entry"

typedef enum {
    EVENT_EXTENSION = 1,
    /* Other extensions here... */
} extension_type;

struct extension_point {
    extension_type type;
    int (*handler)(void*, ...);
};

struct plugin_info {
    const char* plugin_name;
    struct extension_point **extension_point_lst;
};

typedef int (*plugin_handler_type)(void*, ...);
struct plugin_registry{
    plugin_handler_type plugin_handlers [MAX_EXTENSIONS_COUNT];
    int size;
};

struct plugin_registry* get_registry(extension_type type);
void load_plugin(const char* plugn_file);

#endif /* HAVE_PLUGINS */
#endif /* _INCLUDE_PLUGIN_H */