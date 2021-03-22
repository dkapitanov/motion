/*
    plugin.c

    Main extation point for motion

    Copyright Dmitriy Kapitanov, 2021
*/

#include "motion.h"
#include "plugin.h"
#include "logger.h"
#include <stdbool.h>
#include <dlfcn.h>

#if defined HAVE_PLUGINS

static struct plugin_registry* get_event_registry() {
    static struct plugin_registry event_registry = {.plugin_handlers={0},.size=0};
    return &event_registry;
}

struct plugin_registry* get_registry(extension_type type) {
    
    switch (type)
    {
    case EVENT_EXTENSION:
        return get_event_registry();
    default:
         MOTION_LOG(ERR, TYPE_ALL, NO_ERRNO
                ,"Unsupported extension type %d", type);
        return NULL;
    }
}

static void add_extension (struct plugin_registry* registry, struct extension_point* point) {
    
    if (!registry) {
        MOTION_LOG(ERR, TYPE_ALL, NO_ERRNO
                ,"Plugin registry is NULL");
        return;
    }
    registry->plugin_handlers[registry->size++] = point->handler;
}

void load_plugin(const char* plugin_file)
{
    MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                    ,"Loading plugin file %s", plugin_file );

    struct plugin_info* (*entry_function)(void);

    const char    *errmsg;
    void          *handle; 

    if (!plugin_file || !*plugin_file) {
        return;
    }
    dlerror();
    handle = dlopen(plugin_file, RTLD_NOW | RTLD_LOCAL);
    errmsg = dlerror();
    if (errmsg) {
        MOTION_LOG(ERR, TYPE_ALL, NO_ERRNO
                ,"dlopen error [%s]", errmsg);
        return;
    }

    entry_function = dlsym(handle, PLUGIN_ENTRY_FUNCTION);
    errmsg = dlerror();
    if (errmsg) {
        MOTION_LOG(ERR, TYPE_ALL, NO_ERRNO
                ,"dlsym error [%s]", errmsg);
        return;
    }

    struct plugin_info * info = entry_function();
    if (info) {
        for (struct extension_point ** extension = info->extension_point_lst; 
                *extension;  ++extension) { 
                    add_extension(get_registry((*extension)->type), *extension);
        }
    }
}

/*void plugin_process_event(struct context *cnt, motion_event type, struct image_data *img_data,
           char *filename, void *eventdata, struct timeval *tv1)
{
    MOTION_LOG(NTC, TYPE_ALL, NO_ERRNO
                        ,"Plugin process event with type %d", type );
    struct plugin_registry *registry = get_registry(EVENT_EXTENSION);
    if (!registry) {
        MOTION_LOG(ERR, TYPE_ALL, NO_ERRNO
                ,"Unknown registry for the type %d", EVENT_EXTENSION);
        return;
    }
    struct plugin_event my_event = {cnt, type, img_data, filename, eventdata, tv1};
    for (int i = 0; i < registry->size; ++i) {
        if (registry->event_plugin_handlers[i](&my_event))
            break;
    }
}*/

#endif