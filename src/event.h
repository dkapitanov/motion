/*   This file is part of Motion.
 *
 *   Motion is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   Motion is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Motion.  If not, see <https://www.gnu.org/licenses/>.
 */

/*
 *    event.h
 *
 *    Include file for event.c
 *
 *    Copyright Jeroen Vreeken, 2002
 *
 */
#ifndef _INCLUDE_EVENT_H_
#define _INCLUDE_EVENT_H_

#include "event_shared.h"

typedef void(* event_handler)(struct context *cnt, motion_event type, struct image_data *img_data,
           char *filename, void *eventdata, struct timeval *tv1);

void event(struct context *cnt, motion_event type, struct image_data *img_data,
           char *filename, void *eventdata, struct timeval *tv1);

const char *imageext(struct context *cnt);

#endif /* _INCLUDE_EVENT_H_ */
