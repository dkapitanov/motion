/*    event_shared.h
 *
 *      Copyright 2021 by Dmitriy Kapitanov (dkapitanov84@gmail.com)
 *
 */

#ifndef _INCLUDE_EVENT_SHARED_H
#define _INCLUDE_EVENT_SHARED_H

typedef enum {
    EVENT_FILECREATE = 1,
    EVENT_MOTION,
    EVENT_FIRSTMOTION,
    EVENT_ENDMOTION,
    EVENT_TIMELAPSE,
    EVENT_TIMELAPSEEND,
    EVENT_STREAM,
    EVENT_IMAGE_DETECTED,
    EVENT_IMAGEM_DETECTED,
    EVENT_IMAGE_SNAPSHOT,
    EVENT_IMAGE,
    EVENT_IMAGEM,
    EVENT_IMAGE_PREVIEW,
    EVENT_FILECLOSE,
    EVENT_DEBUG,
    EVENT_CRITICAL,
    EVENT_AREA_DETECTED,
    EVENT_CAMERA_LOST,
    EVENT_CAMERA_FOUND,
    EVENT_FFMPEG_PUT,
    EVENT_LAST,
} motion_event;

#if defined HAVE_PLUGINS

struct plugin_event_data {
    struct context *cnt; 
    motion_event eventtype; 
    struct image_data *img_data;
    char *filename; 
    void *eventdata; 
    struct timeval *tv1;
};

#endif /* HAVE_PLUGINS */

#endif /* _INCLUDE_EVENT_SHARED_H */