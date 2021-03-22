#include <motion/config.h>
#include <motion/plugin.h>
#include <motion/event_shared.h>

#include <stdio.h>

int process_event(void* arg, ...);

struct plugin_info *plugin_entry(void) __attribute__((used));
struct plugin_info *plugin_entry(void) {
    static struct extension_point event_extension_point = {EVENT_EXTENSION, process_event};
    static struct extension_point *extensions[] = {&event_extension_point, 0};
    static struct plugin_info plugin = {"Event Plugin", &extensions[0]};
    return &plugin;
}

static int process_camera_found (struct plugin_event_data* event_data) {
    printf("Plugin process camera found event\n");
    /* Do something ...  */
    return 0;
}

static int process_stream (struct plugin_event_data* event_data) {
    printf("Plugin process stream event\n");
    /* Do something ...  */
    return 0;
}

static int process_default (struct plugin_event_data* event_data) {
    printf("Plugin process default event\n"); 
    /* Do something ...  */
    return 0;
} 

int process_event(void* arg, ...) {
    struct plugin_event_data* event_data = (struct plugin_event_data*)arg;
    switch (event_data->eventtype) {
        case EVENT_CAMERA_FOUND:
            return process_camera_found(event_data);
        case EVENT_STREAM:
            return process_stream(event_data);
        default:
            return process_default(event_data);
    }
    return 1;
}