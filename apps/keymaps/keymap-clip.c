/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright © Rafaël Carré 2008
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/
/* Button Code Definitions for Sansa Clip target */

#include "config.h"
#include "action.h"
#include "button.h"
#include "settings.h"

#ifndef MEYERTIME_KEYMAP

/* {Action Code,    Button code,    Prereq button code } */

/*
 * The format of the list is as follows
 * { Action Code,   Button code,    Prereq button code }
 * if there's no need to check the previous button's value, use BUTTON_NONE
 * Insert LAST_ITEM_IN_LIST at the end of each mapping
 */
static const struct button_mapping button_context_standard[]  = {
    { ACTION_STD_PREV,        BUTTON_UP,                        BUTTON_NONE },
    { ACTION_STD_PREVREPEAT,  BUTTON_UP|BUTTON_REPEAT,          BUTTON_NONE },
    { ACTION_STD_NEXT,        BUTTON_DOWN,                      BUTTON_NONE },
    { ACTION_STD_NEXTREPEAT,  BUTTON_DOWN|BUTTON_REPEAT,        BUTTON_NONE },

    { ACTION_STD_MENU,        BUTTON_HOME|BUTTON_REL,           BUTTON_HOME },
    { ACTION_STD_QUICKSCREEN, BUTTON_HOME|BUTTON_REPEAT,        BUTTON_HOME },

    { ACTION_STD_OK,          BUTTON_SELECT|BUTTON_REL,         BUTTON_SELECT },
    { ACTION_STD_OK,          BUTTON_RIGHT,                     BUTTON_NONE },
    { ACTION_STD_CANCEL,      BUTTON_LEFT,                      BUTTON_NONE },
    { ACTION_STD_CANCEL,      BUTTON_POWER,                     BUTTON_NONE },

    { ACTION_STD_CONTEXT,     BUTTON_SELECT|BUTTON_REPEAT,      BUTTON_SELECT },

    LAST_ITEM_IN_LIST
}; /* button_context_standard */


static const struct button_mapping button_context_wps[]  = {
    { ACTION_WPS_PLAY,     BUTTON_UP|BUTTON_REL,        BUTTON_UP },
    { ACTION_WPS_STOP,     BUTTON_POWER|BUTTON_REL,     BUTTON_POWER },

    { ACTION_WPS_SKIPPREV, BUTTON_LEFT|BUTTON_REL,    BUTTON_LEFT },
    { ACTION_WPS_SEEKBACK, BUTTON_LEFT|BUTTON_REPEAT, BUTTON_NONE },
    { ACTION_WPS_STOPSEEK, BUTTON_LEFT|BUTTON_REL,    BUTTON_LEFT|BUTTON_REPEAT },

    { ACTION_WPS_SKIPNEXT, BUTTON_RIGHT|BUTTON_REL,    BUTTON_RIGHT },
    { ACTION_WPS_SEEKFWD,  BUTTON_RIGHT|BUTTON_REPEAT, BUTTON_NONE },
    { ACTION_WPS_STOPSEEK, BUTTON_RIGHT|BUTTON_REL,    BUTTON_RIGHT|BUTTON_REPEAT },

    { ACTION_WPS_ABSETB_NEXTDIR,    BUTTON_POWER|BUTTON_RIGHT,   BUTTON_POWER },
    { ACTION_WPS_ABSETA_PREVDIR,    BUTTON_POWER|BUTTON_LEFT,    BUTTON_POWER },
    { ACTION_WPS_ABRESET,           BUTTON_POWER|BUTTON_UP,      BUTTON_POWER },

    { ACTION_WPS_VOLUP,     BUTTON_VOL_UP,                   BUTTON_NONE },
    { ACTION_WPS_VOLUP,     BUTTON_VOL_UP|BUTTON_REPEAT,     BUTTON_NONE },
    { ACTION_WPS_VOLDOWN,   BUTTON_VOL_DOWN,                  BUTTON_NONE },
    { ACTION_WPS_VOLDOWN,   BUTTON_VOL_DOWN|BUTTON_REPEAT,    BUTTON_NONE },

    { ACTION_WPS_BROWSE,        BUTTON_SELECT|BUTTON_REL,     BUTTON_SELECT },
    { ACTION_WPS_CONTEXT,       BUTTON_SELECT|BUTTON_REPEAT,  BUTTON_SELECT },

    { ACTION_WPS_QUICKSCREEN,   BUTTON_HOME|BUTTON_REPEAT,    BUTTON_HOME },
    { ACTION_WPS_MENU,          BUTTON_HOME|BUTTON_REL,      BUTTON_HOME },

    { ACTION_WPS_PITCHSCREEN,   BUTTON_UP|BUTTON_REPEAT,        BUTTON_NONE },
    { ACTION_WPS_ID3SCREEN,     BUTTON_SELECT|BUTTON_DOWN,      BUTTON_SELECT },

#ifdef HAVE_HOTKEY /* down|repeat doesn't work in the file browser */
    { ACTION_WPS_HOTKEY,        BUTTON_DOWN|BUTTON_REPEAT,      BUTTON_NONE }, 
#else
    { ACTION_WPS_VIEW_PLAYLIST, BUTTON_DOWN|BUTTON_REPEAT,      BUTTON_NONE }, 
#endif

#ifndef HAS_BUTTON_HOLD /* Clip+ */
    { ACTION_STD_KEYLOCK,       BUTTON_HOME|BUTTON_SELECT,      BUTTON_NONE },
#endif /* HAS_BUTTON_HOLD */

    LAST_ITEM_IN_LIST
}; /* button_context_wps */

static const struct button_mapping button_context_settings[] = {
    { ACTION_STD_OK,            BUTTON_HOME|BUTTON_REL,     BUTTON_HOME },
    { ACTION_STD_CANCEL,        BUTTON_POWER,               BUTTON_NONE },
    { ACTION_SETTINGS_RESET,    BUTTON_SELECT,              BUTTON_NONE },
    
    { ACTION_SETTINGS_INC,      BUTTON_UP,                  BUTTON_NONE },
    { ACTION_SETTINGS_INCREPEAT,BUTTON_UP|BUTTON_REPEAT,    BUTTON_NONE },
    { ACTION_SETTINGS_DEC,      BUTTON_DOWN,                BUTTON_NONE },
    { ACTION_SETTINGS_DECREPEAT,BUTTON_DOWN|BUTTON_REPEAT,  BUTTON_NONE },

    { ACTION_STD_PREV,          BUTTON_LEFT,                BUTTON_NONE },
    { ACTION_STD_PREVREPEAT,    BUTTON_LEFT|BUTTON_REPEAT,  BUTTON_NONE },
    { ACTION_STD_NEXT,          BUTTON_RIGHT,               BUTTON_NONE },
    { ACTION_STD_NEXTREPEAT,    BUTTON_RIGHT|BUTTON_REPEAT, BUTTON_NONE },

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_STD),
}; /* button_context_settings */

static const struct button_mapping button_context_list[]  = {
    { ACTION_LISTTREE_PGUP,   BUTTON_SELECT|BUTTON_UP,    BUTTON_SELECT },
    { ACTION_LISTTREE_PGDOWN, BUTTON_SELECT|BUTTON_DOWN,  BUTTON_SELECT },

#ifdef HAVE_VOLUME_IN_LIST
    { ACTION_LIST_VOLUP,        BUTTON_VOL_UP|BUTTON_REPEAT,    BUTTON_NONE },
    { ACTION_LIST_VOLUP,        BUTTON_VOL_UP,                  BUTTON_NONE },

    { ACTION_LIST_VOLDOWN,      BUTTON_VOL_DOWN,                BUTTON_NONE },
    { ACTION_LIST_VOLDOWN,      BUTTON_VOL_DOWN|BUTTON_REPEAT,  BUTTON_NONE },
#else
    { ACTION_LISTTREE_PGUP,     BUTTON_VOL_UP,                  BUTTON_NONE },
    { ACTION_LISTTREE_PGUP,     BUTTON_VOL_UP|BUTTON_REPEAT,    BUTTON_NONE },
    { ACTION_LISTTREE_PGDOWN,   BUTTON_VOL_DOWN,                BUTTON_NONE },
    { ACTION_LISTTREE_PGDOWN,   BUTTON_VOL_DOWN|BUTTON_REPEAT,  BUTTON_NONE },
#endif
    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_STD)
}; /* button_context_list */

static const struct button_mapping button_context_tree[]  = {
    { ACTION_TREE_WPS,    BUTTON_HOME|BUTTON_SELECT,    BUTTON_HOME },
    { ACTION_TREE_STOP,   BUTTON_POWER|BUTTON_REL,      BUTTON_POWER },
#ifdef HAVE_HOTKEY
//    { ACTION_TREE_HOTKEY, BUTTON_NONE,                  BUTTON_NONE },
#endif

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_LIST),
}; /* button_context_tree */

static const struct button_mapping button_context_listtree_scroll_without_combo[]  = {
    { ACTION_NONE,              BUTTON_LEFT,                BUTTON_NONE },
    { ACTION_STD_CANCEL,        BUTTON_LEFT|BUTTON_REL,     BUTTON_LEFT },
    { ACTION_TREE_ROOT_INIT,    BUTTON_LEFT|BUTTON_REPEAT,  BUTTON_LEFT },
    { ACTION_TREE_PGLEFT,       BUTTON_LEFT|BUTTON_REPEAT,  BUTTON_NONE },
    { ACTION_NONE,              BUTTON_RIGHT,               BUTTON_NONE },
    { ACTION_STD_OK,            BUTTON_RIGHT|BUTTON_REL,    BUTTON_RIGHT },
    { ACTION_TREE_PGRIGHT,      BUTTON_RIGHT|BUTTON_REPEAT, BUTTON_NONE },

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_CUSTOM|CONTEXT_TREE),
}; /* button_context_listtree_scroll_without_combo */

static const struct button_mapping button_context_listtree_scroll_with_combo[]  = {
    { ACTION_TREE_PGLEFT,   BUTTON_HOME|BUTTON_LEFT,               BUTTON_NONE },
    { ACTION_TREE_ROOT_INIT,BUTTON_HOME|BUTTON_LEFT|BUTTON_REPEAT, BUTTON_HOME|BUTTON_LEFT },
    { ACTION_TREE_PGLEFT,   BUTTON_HOME|BUTTON_LEFT|BUTTON_REPEAT, BUTTON_NONE },
    { ACTION_TREE_PGRIGHT,  BUTTON_HOME|BUTTON_RIGHT,              BUTTON_NONE },
    { ACTION_TREE_PGRIGHT,  BUTTON_HOME|BUTTON_RIGHT|BUTTON_REPEAT,BUTTON_NONE },

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_CUSTOM|CONTEXT_TREE),
}; /* button_context_listtree_scroll_with_combo */

static const struct button_mapping button_context_mainmenu[]  = {
    { ACTION_TREE_WPS, BUTTON_HOME|BUTTON_REL, BUTTON_HOME },

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_TREE),
}; /* button_context_mainmenu */

static const struct button_mapping button_context_yesno[]  = {
    { ACTION_YESNO_ACCEPT,          BUTTON_SELECT,              BUTTON_NONE },

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_STD),
}; /* button_context_settings_yesno */

static const struct button_mapping button_context_quickscreen[]  = {
    { ACTION_NONE,       BUTTON_LEFT,                   BUTTON_NONE },
    { ACTION_STD_CANCEL, BUTTON_POWER|BUTTON_REL,       BUTTON_NONE },
    { ACTION_STD_CANCEL, BUTTON_HOME,                   BUTTON_NONE },
    { ACTION_STD_CANCEL, BUTTON_SELECT,                 BUTTON_NONE },
    { ACTION_QS_TOP,     BUTTON_UP|BUTTON_REL,          BUTTON_NONE },
    { ACTION_QS_TOP,     BUTTON_UP|BUTTON_REPEAT,       BUTTON_NONE },
    { ACTION_QS_DOWN,    BUTTON_DOWN|BUTTON_REL,        BUTTON_NONE },
    { ACTION_QS_DOWN,    BUTTON_DOWN|BUTTON_REPEAT,     BUTTON_NONE },
    { ACTION_QS_LEFT,    BUTTON_LEFT|BUTTON_REL,        BUTTON_NONE },
    { ACTION_QS_LEFT,    BUTTON_LEFT|BUTTON_REPEAT,     BUTTON_NONE },
    { ACTION_QS_RIGHT,   BUTTON_RIGHT|BUTTON_REL,       BUTTON_NONE },
    { ACTION_QS_RIGHT,   BUTTON_RIGHT|BUTTON_REPEAT,    BUTTON_NONE },

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_STD),
}; /* button_context_quickscreen */

static const struct button_mapping button_context_settings_right_is_inc[]  = {
    { ACTION_SETTINGS_INC,      BUTTON_RIGHT,               BUTTON_NONE },
    { ACTION_SETTINGS_INCREPEAT,BUTTON_RIGHT|BUTTON_REPEAT, BUTTON_NONE },
    { ACTION_SETTINGS_DEC,      BUTTON_LEFT,                BUTTON_NONE },
    { ACTION_SETTINGS_DECREPEAT,BUTTON_LEFT|BUTTON_REPEAT,  BUTTON_NONE },

    { ACTION_STD_CANCEL,        BUTTON_POWER,               BUTTON_NONE },

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_STD),
}; /* button_context_settings_right_is_inc */

static const struct button_mapping button_context_pitchscreen[]  = {
    { ACTION_PS_INC_SMALL,      BUTTON_UP,                      BUTTON_NONE },
    { ACTION_PS_INC_BIG,        BUTTON_UP|BUTTON_REPEAT,        BUTTON_NONE },
    { ACTION_PS_DEC_SMALL,      BUTTON_DOWN,                    BUTTON_NONE },
    { ACTION_PS_DEC_BIG,        BUTTON_DOWN|BUTTON_REPEAT,      BUTTON_NONE },   
    { ACTION_PS_NUDGE_LEFT,     BUTTON_LEFT,                    BUTTON_NONE },
    { ACTION_PS_NUDGE_LEFTOFF,  BUTTON_LEFT|BUTTON_REL,         BUTTON_NONE },
    { ACTION_PS_NUDGE_RIGHT,    BUTTON_RIGHT,                   BUTTON_NONE },
    { ACTION_PS_NUDGE_RIGHTOFF, BUTTON_RIGHT|BUTTON_REL,        BUTTON_NONE },
    { ACTION_PS_TOGGLE_MODE,    BUTTON_HOME|BUTTON_REL,         BUTTON_HOME },
    { ACTION_PS_RESET,          BUTTON_SELECT,                  BUTTON_NONE },
    { ACTION_PS_EXIT,           BUTTON_POWER,                   BUTTON_NONE },
    { ACTION_PS_SLOWER,         BUTTON_LEFT|BUTTON_REPEAT,      BUTTON_NONE },
    { ACTION_PS_FASTER,         BUTTON_RIGHT|BUTTON_REPEAT,     BUTTON_NONE },
    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_STD),
}; /* button_context_pitchscreen */

#ifdef HAVE_RECORDING
/** Recording Screen **/
static const struct button_mapping button_context_recscreen[]  = {
    { ACTION_REC_PAUSE,          BUTTON_SELECT,                 BUTTON_NONE },
    { ACTION_REC_NEWFILE,        BUTTON_HOME|BUTTON_REL,        BUTTON_HOME },
    { ACTION_STD_MENU,           BUTTON_DOWN|BUTTON_REPEAT,     BUTTON_NONE },
    { ACTION_SETTINGS_INC,       BUTTON_RIGHT,                  BUTTON_NONE },
    { ACTION_SETTINGS_INCREPEAT, BUTTON_RIGHT|BUTTON_REPEAT,    BUTTON_NONE },
    { ACTION_SETTINGS_DEC,       BUTTON_LEFT,                   BUTTON_NONE },
    { ACTION_SETTINGS_DECREPEAT, BUTTON_LEFT|BUTTON_REPEAT,     BUTTON_NONE },
    { ACTION_SETTINGS_INC,       BUTTON_VOL_UP,                 BUTTON_NONE },
    { ACTION_SETTINGS_INCREPEAT, BUTTON_VOL_UP|BUTTON_REPEAT,   BUTTON_NONE },
    { ACTION_SETTINGS_DEC,       BUTTON_VOL_DOWN,               BUTTON_NONE },
    { ACTION_SETTINGS_DECREPEAT, BUTTON_VOL_DOWN|BUTTON_REPEAT, BUTTON_NONE },
    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_STD)
}; /* button_context_recscreen */
#endif

/** FM Radio Screen **/
static const struct button_mapping button_context_radio[]  = {
    { ACTION_NONE,              BUTTON_SELECT,                  BUTTON_NONE },
    { ACTION_NONE,              BUTTON_UP|BUTTON_REPEAT,        BUTTON_NONE },
    { ACTION_NONE,              BUTTON_DOWN|BUTTON_REPEAT,      BUTTON_NONE },
    { ACTION_FM_MODE,           BUTTON_DOWN,                    BUTTON_NONE },
    { ACTION_FM_PRESET,         BUTTON_SELECT|BUTTON_REL,       BUTTON_SELECT },
    { ACTION_FM_STOP,           BUTTON_POWER|BUTTON_REL,        BUTTON_POWER },
    { ACTION_FM_MENU,           BUTTON_SELECT|BUTTON_REPEAT,    BUTTON_SELECT},
    { ACTION_FM_EXIT,           BUTTON_HOME|BUTTON_REL,         BUTTON_HOME },
    { ACTION_FM_PLAY,           BUTTON_UP,                      BUTTON_NONE },
    { ACTION_SETTINGS_INC,      BUTTON_VOL_UP,                  BUTTON_NONE },
    { ACTION_SETTINGS_INCREPEAT,BUTTON_VOL_UP|BUTTON_REPEAT,    BUTTON_NONE },
    { ACTION_SETTINGS_DEC,      BUTTON_VOL_DOWN,                BUTTON_NONE },
    { ACTION_SETTINGS_DECREPEAT,BUTTON_VOL_DOWN|BUTTON_REPEAT,  BUTTON_NONE },

#ifndef HAS_BUTTON_HOLD /* Clip+ */
    { ACTION_STD_KEYLOCK,       BUTTON_HOME|BUTTON_SELECT,      BUTTON_NONE },
#endif /* HAS_BUTTON_HOLD */

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_SETTINGS)
}; /* button_context_radio */

static const struct button_mapping button_context_keyboard[]  = {
    { ACTION_KBD_LEFT,         BUTTON_LEFT,                     BUTTON_NONE },
    { ACTION_KBD_LEFT,         BUTTON_LEFT|BUTTON_REPEAT,       BUTTON_NONE },
    { ACTION_KBD_RIGHT,        BUTTON_RIGHT,                    BUTTON_NONE },
    { ACTION_KBD_RIGHT,        BUTTON_RIGHT|BUTTON_REPEAT,      BUTTON_NONE },
    { ACTION_KBD_UP,           BUTTON_UP,                       BUTTON_NONE },
    { ACTION_KBD_UP,           BUTTON_UP|BUTTON_REPEAT,         BUTTON_NONE },
    { ACTION_KBD_DOWN,         BUTTON_DOWN,                     BUTTON_NONE },
    { ACTION_KBD_DOWN,         BUTTON_DOWN|BUTTON_REPEAT,       BUTTON_NONE },

    { ACTION_KBD_CURSOR_LEFT,  BUTTON_VOL_UP,                   BUTTON_NONE },
    { ACTION_KBD_CURSOR_LEFT,  BUTTON_VOL_UP|BUTTON_REPEAT,     BUTTON_NONE },
    { ACTION_KBD_CURSOR_RIGHT, BUTTON_VOL_DOWN,                 BUTTON_NONE },
    { ACTION_KBD_CURSOR_RIGHT, BUTTON_VOL_DOWN|BUTTON_REPEAT,   BUTTON_NONE },

    /*{ ACTION_KBD_PAGE_FLIP,    ,       BUTTON_NONE },*/
    { ACTION_KBD_BACKSPACE,    BUTTON_HOME,                     BUTTON_NONE },
    { ACTION_KBD_BACKSPACE,    BUTTON_HOME|BUTTON_REPEAT,       BUTTON_NONE },
    { ACTION_KBD_SELECT,       BUTTON_SELECT|BUTTON_REL,        BUTTON_NONE },
    { ACTION_KBD_DONE,         BUTTON_SELECT|BUTTON_REPEAT,     BUTTON_NONE },
    { ACTION_KBD_ABORT,        BUTTON_POWER,                    BUTTON_NONE },

    LAST_ITEM_IN_LIST
}; /* button_context_keyboard */

static const struct button_mapping button_context_bmark[]  = {
    { ACTION_BMS_DELETE,       BUTTON_HOME,        BUTTON_NONE },

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_LIST),
}; /* button_context_bmark */

#ifdef USB_ENABLE_HID
static const struct button_mapping button_context_usb_hid[] = {
    { ACTION_USB_HID_MODE_SWITCH_NEXT, BUTTON_POWER|BUTTON_REL,    BUTTON_POWER },
    { ACTION_USB_HID_MODE_SWITCH_PREV, BUTTON_POWER|BUTTON_REPEAT, BUTTON_POWER },

    LAST_ITEM_IN_LIST
}; /* button_context_usb_hid */

static const struct button_mapping button_context_usb_hid_mode_multimedia[] = {
    { ACTION_USB_HID_MULTIMEDIA_VOLUME_DOWN,         BUTTON_VOL_DOWN,               BUTTON_NONE },
    { ACTION_USB_HID_MULTIMEDIA_VOLUME_DOWN,         BUTTON_VOL_DOWN|BUTTON_REPEAT, BUTTON_NONE },
    { ACTION_USB_HID_MULTIMEDIA_VOLUME_UP,           BUTTON_VOL_UP,                 BUTTON_NONE },
    { ACTION_USB_HID_MULTIMEDIA_VOLUME_UP,           BUTTON_VOL_UP|BUTTON_REPEAT,   BUTTON_NONE },
    { ACTION_USB_HID_MULTIMEDIA_VOLUME_MUTE,         BUTTON_SELECT|BUTTON_REL,      BUTTON_SELECT },
    { ACTION_USB_HID_MULTIMEDIA_PLAYBACK_PLAY_PAUSE, BUTTON_UP|BUTTON_REL,          BUTTON_UP },
    { ACTION_USB_HID_MULTIMEDIA_PLAYBACK_STOP,       BUTTON_HOME|BUTTON_REL,        BUTTON_HOME },
    { ACTION_USB_HID_MULTIMEDIA_PLAYBACK_TRACK_PREV, BUTTON_LEFT|BUTTON_REL,        BUTTON_LEFT },
    { ACTION_USB_HID_MULTIMEDIA_PLAYBACK_TRACK_NEXT, BUTTON_RIGHT|BUTTON_REL,       BUTTON_RIGHT },

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_USB_HID)
}; /* button_context_usb_hid_mode_multimedia */

static const struct button_mapping button_context_usb_hid_mode_presentation[] = {
    { ACTION_USB_HID_PRESENTATION_SLIDESHOW_START, BUTTON_UP|BUTTON_REL,          BUTTON_UP },
    { ACTION_USB_HID_PRESENTATION_SLIDESHOW_LEAVE, BUTTON_HOME|BUTTON_REL,        BUTTON_HOME },
    { ACTION_USB_HID_PRESENTATION_SLIDE_PREV,      BUTTON_LEFT|BUTTON_REL,        BUTTON_LEFT },
    { ACTION_USB_HID_PRESENTATION_SLIDE_NEXT,      BUTTON_RIGHT|BUTTON_REL,       BUTTON_RIGHT },
    { ACTION_USB_HID_PRESENTATION_SLIDE_FIRST,     BUTTON_LEFT|BUTTON_REPEAT,     BUTTON_LEFT },
    { ACTION_USB_HID_PRESENTATION_SLIDE_LAST,      BUTTON_RIGHT|BUTTON_REPEAT,    BUTTON_RIGHT },
    { ACTION_USB_HID_PRESENTATION_SCREEN_BLACK,    BUTTON_DOWN|BUTTON_REL,        BUTTON_DOWN },
    { ACTION_USB_HID_PRESENTATION_SCREEN_WHITE,    BUTTON_DOWN|BUTTON_REPEAT,     BUTTON_DOWN },
    { ACTION_USB_HID_PRESENTATION_LINK_PREV,       BUTTON_VOL_UP,                 BUTTON_NONE },
    { ACTION_USB_HID_PRESENTATION_LINK_PREV,       BUTTON_VOL_UP|BUTTON_REPEAT,   BUTTON_NONE },
    { ACTION_USB_HID_PRESENTATION_LINK_NEXT,       BUTTON_VOL_DOWN,               BUTTON_NONE },
    { ACTION_USB_HID_PRESENTATION_LINK_NEXT,       BUTTON_VOL_DOWN|BUTTON_REPEAT, BUTTON_NONE },
    { ACTION_USB_HID_PRESENTATION_MOUSE_CLICK,     BUTTON_SELECT|BUTTON_REL,      BUTTON_SELECT },
    { ACTION_USB_HID_PRESENTATION_MOUSE_OVER,      BUTTON_SELECT|BUTTON_REPEAT,   BUTTON_SELECT },

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_USB_HID)
}; /* button_context_usb_hid_mode_presentation */

static const struct button_mapping button_context_usb_hid_mode_browser[] = {
    { ACTION_USB_HID_BROWSER_SCROLL_UP,        BUTTON_VOL_UP,                       BUTTON_NONE },
    { ACTION_USB_HID_BROWSER_SCROLL_UP,        BUTTON_VOL_UP|BUTTON_REPEAT,         BUTTON_NONE },
    { ACTION_USB_HID_BROWSER_SCROLL_DOWN,      BUTTON_VOL_DOWN,                     BUTTON_NONE },
    { ACTION_USB_HID_BROWSER_SCROLL_DOWN,      BUTTON_VOL_DOWN|BUTTON_REPEAT,       BUTTON_NONE },
    { ACTION_USB_HID_BROWSER_SCROLL_PAGE_UP,   BUTTON_UP|BUTTON_REL,                BUTTON_UP },
    { ACTION_USB_HID_BROWSER_SCROLL_PAGE_DOWN, BUTTON_DOWN|BUTTON_REL,              BUTTON_DOWN },
    { ACTION_USB_HID_BROWSER_ZOOM_IN,          BUTTON_UP|BUTTON_REPEAT,             BUTTON_UP },
    { ACTION_USB_HID_BROWSER_ZOOM_OUT,         BUTTON_DOWN|BUTTON_REPEAT,           BUTTON_DOWN },
    { ACTION_USB_HID_BROWSER_ZOOM_RESET,       BUTTON_SELECT|BUTTON_REPEAT,         BUTTON_SELECT },
    { ACTION_USB_HID_BROWSER_ZOOM_RESET,       BUTTON_UP|BUTTON_DOWN|BUTTON_REPEAT, BUTTON_UP|BUTTON_DOWN },
    { ACTION_USB_HID_BROWSER_TAB_PREV,         BUTTON_LEFT|BUTTON_REL,              BUTTON_LEFT },
    { ACTION_USB_HID_BROWSER_TAB_NEXT,         BUTTON_RIGHT|BUTTON_REL,             BUTTON_RIGHT },
    { ACTION_USB_HID_BROWSER_TAB_CLOSE,        BUTTON_HOME|BUTTON_REPEAT,           BUTTON_HOME },
    { ACTION_USB_HID_BROWSER_HISTORY_BACK,     BUTTON_LEFT|BUTTON_REPEAT,           BUTTON_LEFT },
    { ACTION_USB_HID_BROWSER_HISTORY_FORWARD,  BUTTON_RIGHT|BUTTON_REPEAT,          BUTTON_RIGHT },
    { ACTION_USB_HID_BROWSER_VIEW_FULL_SCREEN, BUTTON_SELECT|BUTTON_REL,            BUTTON_SELECT },

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_USB_HID)
}; /* button_context_usb_hid_mode_browser */

#ifdef HAVE_USB_HID_MOUSE
static const struct button_mapping button_context_usb_hid_mode_mouse[] = {
    { ACTION_USB_HID_MOUSE_UP,                BUTTON_UP,                                BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_UP_REP,            BUTTON_UP|BUTTON_REPEAT,                  BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_DOWN,              BUTTON_DOWN,                              BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_DOWN_REP,          BUTTON_DOWN|BUTTON_REPEAT,                BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_LEFT,              BUTTON_LEFT,                              BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_LEFT_REP,          BUTTON_LEFT|BUTTON_REPEAT,                BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_RIGHT,             BUTTON_RIGHT,                             BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_RIGHT_REP,         BUTTON_RIGHT|BUTTON_REPEAT,               BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_BUTTON_LEFT,       BUTTON_SELECT,                            BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_BUTTON_LEFT_REL,   BUTTON_SELECT|BUTTON_REL,                 BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_LDRAG_UP,          BUTTON_SELECT|BUTTON_UP,                  BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_LDRAG_UP_REP,      BUTTON_SELECT|BUTTON_UP|BUTTON_REPEAT,    BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_LDRAG_DOWN,        BUTTON_SELECT|BUTTON_DOWN,                BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_LDRAG_DOWN_REP,    BUTTON_SELECT|BUTTON_DOWN|BUTTON_REPEAT,  BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_LDRAG_LEFT,        BUTTON_SELECT|BUTTON_LEFT,                BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_LDRAG_LEFT_REP,    BUTTON_SELECT|BUTTON_LEFT|BUTTON_REPEAT,  BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_LDRAG_RIGHT,       BUTTON_SELECT|BUTTON_RIGHT,               BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_LDRAG_RIGHT_REP,   BUTTON_SELECT|BUTTON_RIGHT|BUTTON_REPEAT, BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_BUTTON_RIGHT,      BUTTON_HOME,                              BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_BUTTON_RIGHT_REL,  BUTTON_HOME|BUTTON_REL,                   BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_RDRAG_UP,          BUTTON_HOME|BUTTON_UP,                    BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_RDRAG_UP_REP,      BUTTON_HOME|BUTTON_UP|BUTTON_REPEAT,      BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_RDRAG_DOWN,        BUTTON_HOME|BUTTON_DOWN,                  BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_RDRAG_DOWN_REP,    BUTTON_HOME|BUTTON_DOWN|BUTTON_REPEAT,    BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_RDRAG_LEFT,        BUTTON_HOME|BUTTON_LEFT,                  BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_RDRAG_LEFT_REP,    BUTTON_HOME|BUTTON_LEFT|BUTTON_REPEAT,    BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_RDRAG_RIGHT,       BUTTON_HOME|BUTTON_RIGHT,                 BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_RDRAG_RIGHT_REP,   BUTTON_HOME|BUTTON_RIGHT|BUTTON_REPEAT,   BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_WHEEL_SCROLL_UP,   BUTTON_VOL_UP,                            BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_WHEEL_SCROLL_UP,   BUTTON_VOL_UP|BUTTON_REPEAT,              BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_WHEEL_SCROLL_DOWN, BUTTON_VOL_DOWN,                          BUTTON_NONE },
    { ACTION_USB_HID_MOUSE_WHEEL_SCROLL_DOWN, BUTTON_VOL_DOWN|BUTTON_REPEAT,            BUTTON_NONE },

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_USB_HID)
}; /* button_context_usb_hid_mode_mouse */
#endif
#endif

/* get_context_mapping returns a pointer to one of the above defined arrays depending on the context */
const struct button_mapping* get_context_mapping(int context)
{
    switch (context)
    {
        case CONTEXT_STD:
            return button_context_standard;

        case CONTEXT_WPS:
            return button_context_wps;

        case CONTEXT_LIST:
            return button_context_list;
        case CONTEXT_TREE:
            if (global_settings.hold_lr_for_scroll_in_list)
                return button_context_listtree_scroll_without_combo;
            else
                return button_context_listtree_scroll_with_combo;
        case CONTEXT_MAINMENU:
            return button_context_mainmenu;
        case CONTEXT_CUSTOM|CONTEXT_TREE:
            return button_context_tree;

        case CONTEXT_SETTINGS:
        case CONTEXT_SETTINGS_TIME:
            return button_context_settings;
        case CONTEXT_CUSTOM|CONTEXT_SETTINGS:
        case CONTEXT_SETTINGS_COLOURCHOOSER:
        case CONTEXT_SETTINGS_EQ:
        case CONTEXT_SETTINGS_RECTRIGGER:
            return button_context_settings_right_is_inc;

        case CONTEXT_YESNOSCREEN:
            return button_context_yesno;
        case CONTEXT_FM:
            return button_context_radio;
        case CONTEXT_BOOKMARKSCREEN:
            return button_context_bmark;
        case CONTEXT_QUICKSCREEN:
            return button_context_quickscreen;
        case CONTEXT_PITCHSCREEN:
            return button_context_pitchscreen;
#ifdef HAVE_RECORDING
        case CONTEXT_RECSCREEN:
            return button_context_recscreen;
#endif
        case CONTEXT_KEYBOARD:
            return button_context_keyboard;
#ifdef USB_ENABLE_HID
        case CONTEXT_USB_HID:
            return button_context_usb_hid;
        case CONTEXT_USB_HID_MODE_MULTIMEDIA:
            return button_context_usb_hid_mode_multimedia;
        case CONTEXT_USB_HID_MODE_PRESENTATION:
            return button_context_usb_hid_mode_presentation;
        case CONTEXT_USB_HID_MODE_BROWSER:
            return button_context_usb_hid_mode_browser;
#ifdef HAVE_USB_HID_MOUSE
        case CONTEXT_USB_HID_MODE_MOUSE:
            return button_context_usb_hid_mode_mouse;
#endif
#endif
        default:
            return button_context_standard;
    }
    return button_context_standard;
}



#else /* MEYERTIME_KEYMAP */

// The following code has not been tested on a Clip, and it is not intended to
// be used, as the Clip has no scroll wheel, so it does not need a custom
// keymap.  Rather, it is the same keymap as above, except refactored to use
// the more readable macros like the custom Fuze keymap.  It is intended to be
// used for comparison to the Fuze keymap.

#define DOWN(b, a) { a, b, BUTTON_NONE }
#define REPEAT(b, a) { a, b|BUTTON_REPEAT, BUTTON_NONE }
#define UP(b, a) { a, b|BUTTON_REL, BUTTON_NONE }
#define SHORT(b, a) { a, b|BUTTON_REL, b }
#define LONG(b, a) { a, b|BUTTON_REPEAT, b }
#define END(b, a) { a, b|BUTTON_REL, b|BUTTON_REPEAT }
#define COMBO(b1, b2, a) { a, b1|b2, b1 }

static const struct button_mapping button_context_standard[]  = {
    DOWN  (BUTTON_UP,     ACTION_STD_PREV),
    REPEAT(BUTTON_UP,     ACTION_STD_PREVREPEAT),
    DOWN  (BUTTON_DOWN,   ACTION_STD_NEXT),
    REPEAT(BUTTON_DOWN,   ACTION_STD_NEXTREPEAT),
    DOWN  (BUTTON_LEFT,   ACTION_STD_CANCEL),
    DOWN  (BUTTON_RIGHT,  ACTION_STD_OK),
    SHORT (BUTTON_SELECT, ACTION_STD_OK),
    LONG  (BUTTON_SELECT, ACTION_STD_CONTEXT),
    SHORT (BUTTON_HOME,   ACTION_STD_MENU),
    LONG  (BUTTON_HOME,   ACTION_STD_QUICKSCREEN),
    DOWN  (BUTTON_POWER,  ACTION_STD_CANCEL),

    LAST_ITEM_IN_LIST
}; /* button_context_standard */

static const struct button_mapping button_context_wps[]  = {
    SHORT (BUTTON_UP,                  ACTION_WPS_PLAY),
    REPEAT(BUTTON_UP,                  ACTION_WPS_PITCHSCREEN),
    SHORT (BUTTON_LEFT,                ACTION_WPS_SKIPPREV),
    REPEAT(BUTTON_LEFT,                ACTION_WPS_SEEKBACK),
    END   (BUTTON_LEFT,                ACTION_WPS_STOPSEEK),
    SHORT (BUTTON_RIGHT,               ACTION_WPS_SKIPNEXT),
    REPEAT(BUTTON_RIGHT,               ACTION_WPS_SEEKFWD),
    END   (BUTTON_RIGHT,               ACTION_WPS_STOPSEEK),
    SHORT (BUTTON_SELECT,              ACTION_WPS_BROWSE),
    LONG  (BUTTON_SELECT,              ACTION_WPS_CONTEXT),
    COMBO (BUTTON_SELECT, BUTTON_DOWN, ACTION_WPS_ID3SCREEN),
    LONG  (BUTTON_HOME,                ACTION_WPS_QUICKSCREEN),
    SHORT (BUTTON_HOME,                ACTION_WPS_MENU),
    SHORT (BUTTON_POWER,               ACTION_WPS_STOP),
    COMBO (BUTTON_POWER, BUTTON_RIGHT, ACTION_WPS_ABSETB_NEXTDIR),
    COMBO (BUTTON_POWER, BUTTON_LEFT,  ACTION_WPS_ABSETA_PREVDIR),
    COMBO (BUTTON_POWER, BUTTON_UP,    ACTION_WPS_ABRESET),
    DOWN  (BUTTON_VOL_UP,              ACTION_WPS_VOLUP),
    REPEAT(BUTTON_VOL_UP,              ACTION_WPS_VOLUP),
    DOWN  (BUTTON_VOL_DOWN,            ACTION_WPS_VOLDOWN),
    REPEAT(BUTTON_VOL_DOWN,            ACTION_WPS_VOLDOWN),

#ifdef HAVE_HOTKEY /* down|repeat doesn't work in the file browser */
    REPEAT(BUTTON_DOWN, ACTION_WPS_HOTKEY), 
#else
    REPEAT(BUTTON_DOWN, ACTION_WPS_VIEW_PLAYLIST), 
#endif

#ifndef HAS_BUTTON_HOLD /* Clip+ */
    DOWN  (BUTTON_HOME|BUTTON_SELECT, ACTION_STD_KEYLOCK),
#endif /* HAS_BUTTON_HOLD */

    LAST_ITEM_IN_LIST
}; /* button_context_wps */

static const struct button_mapping button_context_settings[] = {
    // Also applies to time settings
    DOWN  (BUTTON_UP,     ACTION_SETTINGS_INC),
    REPEAT(BUTTON_UP,     ACTION_SETTINGS_INCREPEAT),
    DOWN  (BUTTON_DOWN,   ACTION_SETTINGS_DEC),
    REPEAT(BUTTON_DOWN,   ACTION_SETTINGS_DECREPEAT),
    DOWN  (BUTTON_LEFT,   ACTION_STD_PREV),
    REPEAT(BUTTON_LEFT,   ACTION_STD_PREVREPEAT),
    DOWN  (BUTTON_RIGHT,  ACTION_STD_NEXT),
    REPEAT(BUTTON_RIGHT,  ACTION_STD_NEXTREPEAT),
    DOWN  (BUTTON_SELECT, ACTION_SETTINGS_RESET),
    SHORT (BUTTON_HOME,   ACTION_STD_OK),
    DOWN  (BUTTON_POWER,  ACTION_STD_CANCEL),

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_STD),
}; /* button_context_settings */

static const struct button_mapping button_context_list[]  = {
    COMBO (BUTTON_SELECT, BUTTON_UP,   ACTION_LISTTREE_PGUP),
    COMBO (BUTTON_SELECT, BUTTON_DOWN, ACTION_LISTTREE_PGDOWN),

#ifdef HAVE_VOLUME_IN_LIST
    DOWN  (BUTTON_VOL_UP,   ACTION_LIST_VOLUP),
    REPEAT(BUTTON_VOL_UP,   ACTION_LIST_VOLUP),
    DOWN  (BUTTON_VOL_DOWN, ACTION_LIST_VOLDOWN),
    REPEAT(BUTTON_VOL_DOWN, ACTION_LIST_VOLDOWN),
#else
    DOWN  (BUTTON_VOL_UP,   ACTION_LISTTREE_PGUP),
    REPEAT(BUTTON_VOL_UP,   ACTION_LISTTREE_PGUP),
    DOWN  (BUTTON_VOL_DOWN, ACTION_LISTTREE_PGDOWN),
    REPEAT(BUTTON_VOL_DOWN, ACTION_LISTTREE_PGDOWN),
#endif
    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_STD)
}; /* button_context_list */

static const struct button_mapping button_context_tree[]  = {
    COMBO (BUTTON_HOME, BUTTON_SELECT, ACTION_TREE_WPS),
    SHORT (BUTTON_POWER,               ACTION_TREE_STOP),
#ifdef HAVE_HOTKEY
//  DOWN  (BUTTON_NONE, ACTION_TREE_HOTKEY),
#endif

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_LIST),
}; /* button_context_tree */

static const struct button_mapping button_context_listtree_scroll_without_combo[]  = {
    DOWN  (BUTTON_LEFT,  ACTION_NONE),
    SHORT (BUTTON_LEFT,  ACTION_STD_CANCEL),
    LONG  (BUTTON_LEFT,  ACTION_TREE_ROOT_INIT),
    REPEAT(BUTTON_LEFT,  ACTION_TREE_PGLEFT),
    DOWN  (BUTTON_RIGHT, ACTION_NONE),
    SHORT (BUTTON_RIGHT, ACTION_STD_OK),
    REPEAT(BUTTON_RIGHT, ACTION_TREE_PGRIGHT),

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_CUSTOM|CONTEXT_TREE),
}; /* button_context_listtree_scroll_without_combo */

static const struct button_mapping button_context_listtree_scroll_with_combo[]  = {
    DOWN  (BUTTON_HOME|BUTTON_LEFT,  ACTION_TREE_PGLEFT),
    LONG  (BUTTON_HOME|BUTTON_LEFT,  ACTION_TREE_ROOT_INIT),
    REPEAT(BUTTON_HOME|BUTTON_LEFT,  ACTION_TREE_PGLEFT),
    DOWN  (BUTTON_HOME|BUTTON_RIGHT, ACTION_TREE_PGRIGHT),
    REPEAT(BUTTON_HOME|BUTTON_RIGHT, ACTION_TREE_PGRIGHT),

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_CUSTOM|CONTEXT_TREE),
}; /* button_context_listtree_scroll_with_combo */

static const struct button_mapping button_context_mainmenu[]  = {
    SHORT (BUTTON_HOME, ACTION_TREE_WPS),

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_TREE),
}; /* button_context_mainmenu */

static const struct button_mapping button_context_yesno[]  = {
    DOWN  (BUTTON_SELECT, ACTION_YESNO_ACCEPT),

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_STD),
}; /* button_context_settings_yesno */

static const struct button_mapping button_context_quickscreen[]  = {
    UP    (BUTTON_UP,     ACTION_QS_TOP),
    REPEAT(BUTTON_UP,     ACTION_QS_TOP),
    UP    (BUTTON_DOWN,   ACTION_QS_DOWN),
    REPEAT(BUTTON_DOWN,   ACTION_QS_DOWN),
    DOWN  (BUTTON_LEFT,   ACTION_NONE),
    UP    (BUTTON_LEFT,   ACTION_QS_LEFT),
    REPEAT(BUTTON_LEFT,   ACTION_QS_LEFT),
    UP    (BUTTON_RIGHT,  ACTION_QS_RIGHT),
    REPEAT(BUTTON_RIGHT,  ACTION_QS_RIGHT),
    DOWN  (BUTTON_SELECT, ACTION_STD_CANCEL),
    DOWN  (BUTTON_HOME,   ACTION_STD_CANCEL),
    UP    (BUTTON_POWER,  ACTION_STD_CANCEL),

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_STD),
}; /* button_context_quickscreen */

static const struct button_mapping button_context_settings_right_is_inc[]  = {
    DOWN  (BUTTON_LEFT,  ACTION_SETTINGS_DEC),
    REPEAT(BUTTON_LEFT,  ACTION_SETTINGS_DECREPEAT),
    DOWN  (BUTTON_RIGHT, ACTION_SETTINGS_INC),
    REPEAT(BUTTON_RIGHT, ACTION_SETTINGS_INCREPEAT),
    DOWN  (BUTTON_POWER, ACTION_STD_CANCEL),

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_STD),
}; /* button_context_settings_right_is_inc */

static const struct button_mapping button_context_pitchscreen[]  = {
    DOWN  (BUTTON_UP,     ACTION_PS_INC_SMALL),
    REPEAT(BUTTON_UP,     ACTION_PS_INC_BIG),
    DOWN  (BUTTON_DOWN,   ACTION_PS_DEC_SMALL),
    REPEAT(BUTTON_DOWN,   ACTION_PS_DEC_BIG),   
    DOWN  (BUTTON_LEFT,   ACTION_PS_NUDGE_LEFT),
    UP    (BUTTON_LEFT,   ACTION_PS_NUDGE_LEFTOFF),
    REPEAT(BUTTON_LEFT,   ACTION_PS_SLOWER),
    DOWN  (BUTTON_RIGHT,  ACTION_PS_NUDGE_RIGHT),
    UP    (BUTTON_RIGHT,  ACTION_PS_NUDGE_RIGHTOFF),
    REPEAT(BUTTON_RIGHT,  ACTION_PS_FASTER),
    DOWN  (BUTTON_SELECT, ACTION_PS_RESET),
    SHORT (BUTTON_HOME,   ACTION_PS_TOGGLE_MODE),
    DOWN  (BUTTON_POWER,  ACTION_PS_EXIT),

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_STD),
}; /* button_context_pitchscreen */

#ifdef HAVE_RECORDING
/** Recording Screen **/
static const struct button_mapping button_context_recscreen[]  = {
    REPEAT(BUTTON_DOWN,     ACTION_STD_MENU),
    DOWN  (BUTTON_LEFT,     ACTION_SETTINGS_DEC),
    REPEAT(BUTTON_LEFT,     ACTION_SETTINGS_DECREPEAT),
    DOWN  (BUTTON_RIGHT,    ACTION_SETTINGS_INC),
    REPEAT(BUTTON_RIGHT,    ACTION_SETTINGS_INCREPEAT),
    DOWN  (BUTTON_SELECT,   ACTION_REC_PAUSE),
    SHORT (BUTTON_HOME,     ACTION_REC_NEWFILE),
    DOWN  (BUTTON_VOL_UP,   ACTION_SETTINGS_INC),
    REPEAT(BUTTON_VOL_UP,   ACTION_SETTINGS_INCREPEAT),
    DOWN  (BUTTON_VOL_DOWN, ACTION_SETTINGS_DEC),
    REPEAT(BUTTON_VOL_DOWN, ACTION_SETTINGS_DECREPEAT),

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_STD)
}; /* button_context_recscreen */
#endif

/** FM Radio Screen **/
static const struct button_mapping button_context_radio[]  = {
    DOWN  (BUTTON_UP,       ACTION_FM_PLAY),
    REPEAT(BUTTON_UP,       ACTION_NONE),
    DOWN  (BUTTON_DOWN,     ACTION_FM_MODE),
    REPEAT(BUTTON_DOWN,     ACTION_NONE),
    DOWN  (BUTTON_SELECT,   ACTION_NONE),
    SHORT (BUTTON_SELECT,   ACTION_FM_PRESET),
    LONG  (BUTTON_SELECT,   ACTION_FM_MENU),
    SHORT (BUTTON_HOME,     ACTION_FM_EXIT),
    SHORT (BUTTON_POWER,    ACTION_FM_STOP),
    DOWN  (BUTTON_VOL_UP,   ACTION_SETTINGS_INC),
    REPEAT(BUTTON_VOL_UP,   ACTION_SETTINGS_INCREPEAT),
    DOWN  (BUTTON_VOL_DOWN, ACTION_SETTINGS_DEC),
    REPEAT(BUTTON_VOL_DOWN, ACTION_SETTINGS_DECREPEAT),

#ifndef HAS_BUTTON_HOLD /* Clip+ */
    DOWN  (BUTTON_HOME|BUTTON_SELECT, ACTION_STD_KEYLOCK),
#endif /* HAS_BUTTON_HOLD */

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_SETTINGS)
}; /* button_context_radio */

static const struct button_mapping button_context_keyboard[]  = {
    DOWN  (BUTTON_UP,       ACTION_KBD_UP),
    REPEAT(BUTTON_UP,       ACTION_KBD_UP),
    DOWN  (BUTTON_DOWN,     ACTION_KBD_DOWN),
    REPEAT(BUTTON_DOWN,     ACTION_KBD_DOWN),
    DOWN  (BUTTON_LEFT,     ACTION_KBD_LEFT),
    REPEAT(BUTTON_LEFT,     ACTION_KBD_LEFT),
    DOWN  (BUTTON_RIGHT,    ACTION_KBD_RIGHT),
    REPEAT(BUTTON_RIGHT,    ACTION_KBD_RIGHT),
    UP    (BUTTON_SELECT,   ACTION_KBD_SELECT),
    REPEAT(BUTTON_SELECT,   ACTION_KBD_DONE),
    DOWN  (BUTTON_HOME,     ACTION_KBD_BACKSPACE),
    REPEAT(BUTTON_HOME,     ACTION_KBD_BACKSPACE),
    DOWN  (BUTTON_POWER,    ACTION_KBD_ABORT),
    DOWN  (BUTTON_VOL_UP,   ACTION_KBD_CURSOR_LEFT),
    REPEAT(BUTTON_VOL_UP,   ACTION_KBD_CURSOR_LEFT),
    DOWN  (BUTTON_VOL_DOWN, ACTION_KBD_CURSOR_RIGHT),
    REPEAT(BUTTON_VOL_DOWN, ACTION_KBD_CURSOR_RIGHT),

    /*{ ACTION_KBD_PAGE_FLIP,    ,       BUTTON_NONE },*/

    LAST_ITEM_IN_LIST
}; /* button_context_keyboard */

static const struct button_mapping button_context_bmark[]  = {
    DOWN  (BUTTON_HOME, ACTION_BMS_DELETE),

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_LIST),
}; /* button_context_bmark */

#ifdef USB_ENABLE_HID
static const struct button_mapping button_context_usb_hid[] = {
    SHORT (BUTTON_POWER, ACTION_USB_HID_MODE_SWITCH_NEXT),
    LONG  (BUTTON_POWER, ACTION_USB_HID_MODE_SWITCH_PREV),

    LAST_ITEM_IN_LIST
}; /* button_context_usb_hid */

static const struct button_mapping button_context_usb_hid_mode_multimedia[] = {
    SHORT (BUTTON_UP,       ACTION_USB_HID_MULTIMEDIA_PLAYBACK_PLAY_PAUSE),
    SHORT (BUTTON_LEFT,     ACTION_USB_HID_MULTIMEDIA_PLAYBACK_TRACK_PREV),
    SHORT (BUTTON_RIGHT,    ACTION_USB_HID_MULTIMEDIA_PLAYBACK_TRACK_NEXT),
    SHORT (BUTTON_SELECT,   ACTION_USB_HID_MULTIMEDIA_VOLUME_MUTE),
    SHORT (BUTTON_HOME,     ACTION_USB_HID_MULTIMEDIA_PLAYBACK_STOP),
    DOWN  (BUTTON_VOL_UP,   ACTION_USB_HID_MULTIMEDIA_VOLUME_UP),
    REPEAT(BUTTON_VOL_UP,   ACTION_USB_HID_MULTIMEDIA_VOLUME_UP),
    DOWN  (BUTTON_VOL_DOWN, ACTION_USB_HID_MULTIMEDIA_VOLUME_DOWN),
    REPEAT(BUTTON_VOL_DOWN, ACTION_USB_HID_MULTIMEDIA_VOLUME_DOWN),

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_USB_HID)
}; /* button_context_usb_hid_mode_multimedia */

static const struct button_mapping button_context_usb_hid_mode_presentation[] = {
    SHORT (BUTTON_UP,       ACTION_USB_HID_PRESENTATION_SLIDESHOW_START),
    SHORT (BUTTON_DOWN,     ACTION_USB_HID_PRESENTATION_SCREEN_BLACK),
    LONG  (BUTTON_DOWN,     ACTION_USB_HID_PRESENTATION_SCREEN_WHITE),
    SHORT (BUTTON_LEFT,     ACTION_USB_HID_PRESENTATION_SLIDE_PREV),
    LONG  (BUTTON_LEFT,     ACTION_USB_HID_PRESENTATION_SLIDE_FIRST),
    SHORT (BUTTON_RIGHT,    ACTION_USB_HID_PRESENTATION_SLIDE_NEXT),
    LONG  (BUTTON_RIGHT,    ACTION_USB_HID_PRESENTATION_SLIDE_LAST),
    SHORT (BUTTON_SELECT,   ACTION_USB_HID_PRESENTATION_MOUSE_CLICK),
    LONG  (BUTTON_SELECT,   ACTION_USB_HID_PRESENTATION_MOUSE_OVER),
    SHORT (BUTTON_HOME,     ACTION_USB_HID_PRESENTATION_SLIDESHOW_LEAVE),
    DOWN  (BUTTON_VOL_UP,   ACTION_USB_HID_PRESENTATION_LINK_PREV),
    REPEAT(BUTTON_VOL_UP,   ACTION_USB_HID_PRESENTATION_LINK_PREV),
    DOWN  (BUTTON_VOL_DOWN, ACTION_USB_HID_PRESENTATION_LINK_NEXT),
    REPEAT(BUTTON_VOL_DOWN, ACTION_USB_HID_PRESENTATION_LINK_NEXT),

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_USB_HID)
}; /* button_context_usb_hid_mode_presentation */

static const struct button_mapping button_context_usb_hid_mode_browser[] = {
    SHORT (BUTTON_UP,             ACTION_USB_HID_BROWSER_SCROLL_PAGE_UP),
    LONG  (BUTTON_UP,             ACTION_USB_HID_BROWSER_ZOOM_IN),
    LONG  (BUTTON_UP|BUTTON_DOWN, ACTION_USB_HID_BROWSER_ZOOM_RESET),
    SHORT (BUTTON_DOWN,           ACTION_USB_HID_BROWSER_SCROLL_PAGE_DOWN),
    LONG  (BUTTON_DOWN,           ACTION_USB_HID_BROWSER_ZOOM_OUT),
    SHORT (BUTTON_LEFT,           ACTION_USB_HID_BROWSER_TAB_PREV),
    LONG  (BUTTON_LEFT,           ACTION_USB_HID_BROWSER_HISTORY_BACK),
    SHORT (BUTTON_RIGHT,          ACTION_USB_HID_BROWSER_TAB_NEXT),
    LONG  (BUTTON_RIGHT,          ACTION_USB_HID_BROWSER_HISTORY_FORWARD),
    SHORT (BUTTON_SELECT,         ACTION_USB_HID_BROWSER_VIEW_FULL_SCREEN),
    LONG  (BUTTON_SELECT,         ACTION_USB_HID_BROWSER_ZOOM_RESET),
    LONG  (BUTTON_HOME,           ACTION_USB_HID_BROWSER_TAB_CLOSE),
    DOWN  (BUTTON_VOL_UP,         ACTION_USB_HID_BROWSER_SCROLL_UP),
    REPEAT(BUTTON_VOL_UP,         ACTION_USB_HID_BROWSER_SCROLL_UP),
    DOWN  (BUTTON_VOL_DOWN,       ACTION_USB_HID_BROWSER_SCROLL_DOWN),
    REPEAT(BUTTON_VOL_DOWN,       ACTION_USB_HID_BROWSER_SCROLL_DOWN),

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_USB_HID)
}; /* button_context_usb_hid_mode_browser */

#ifdef HAVE_USB_HID_MOUSE
static const struct button_mapping button_context_usb_hid_mode_mouse[] = {
    DOWN  (BUTTON_UP,                  ACTION_USB_HID_MOUSE_UP),
    REPEAT(BUTTON_UP,                  ACTION_USB_HID_MOUSE_UP_REP),
    DOWN  (BUTTON_DOWN,                ACTION_USB_HID_MOUSE_DOWN),
    REPEAT(BUTTON_DOWN,                ACTION_USB_HID_MOUSE_DOWN_REP),
    DOWN  (BUTTON_LEFT,                ACTION_USB_HID_MOUSE_LEFT),
    REPEAT(BUTTON_LEFT,                ACTION_USB_HID_MOUSE_LEFT_REP),
    DOWN  (BUTTON_RIGHT,               ACTION_USB_HID_MOUSE_RIGHT),
    REPEAT(BUTTON_RIGHT,               ACTION_USB_HID_MOUSE_RIGHT_REP),
    DOWN  (BUTTON_SELECT,              ACTION_USB_HID_MOUSE_BUTTON_LEFT),
    UP    (BUTTON_SELECT,              ACTION_USB_HID_MOUSE_BUTTON_LEFT_REL),
    DOWN  (BUTTON_SELECT|BUTTON_UP,    ACTION_USB_HID_MOUSE_LDRAG_UP),
    REPEAT(BUTTON_SELECT|BUTTON_UP,    ACTION_USB_HID_MOUSE_LDRAG_UP_REP),
    DOWN  (BUTTON_SELECT|BUTTON_DOWN,  ACTION_USB_HID_MOUSE_LDRAG_DOWN),
    REPEAT(BUTTON_SELECT|BUTTON_DOWN,  ACTION_USB_HID_MOUSE_LDRAG_DOWN_REP),
    DOWN  (BUTTON_SELECT|BUTTON_LEFT,  ACTION_USB_HID_MOUSE_LDRAG_LEFT),
    REPEAT(BUTTON_SELECT|BUTTON_LEFT,  ACTION_USB_HID_MOUSE_LDRAG_LEFT_REP),
    DOWN  (BUTTON_SELECT|BUTTON_RIGHT, ACTION_USB_HID_MOUSE_LDRAG_RIGHT),
    REPEAT(BUTTON_SELECT|BUTTON_RIGHT, ACTION_USB_HID_MOUSE_LDRAG_RIGHT_REP),
    DOWN  (BUTTON_HOME,                ACTION_USB_HID_MOUSE_BUTTON_RIGHT),
    UP    (BUTTON_HOME,                ACTION_USB_HID_MOUSE_BUTTON_RIGHT_REL),
    DOWN  (BUTTON_HOME|BUTTON_UP,      ACTION_USB_HID_MOUSE_RDRAG_UP),
    REPEAT(BUTTON_HOME|BUTTON_UP,      ACTION_USB_HID_MOUSE_RDRAG_UP_REP),
    DOWN  (BUTTON_HOME|BUTTON_DOWN,    ACTION_USB_HID_MOUSE_RDRAG_DOWN),
    REPEAT(BUTTON_HOME|BUTTON_DOWN,    ACTION_USB_HID_MOUSE_RDRAG_DOWN_REP),
    DOWN  (BUTTON_HOME|BUTTON_LEFT,    ACTION_USB_HID_MOUSE_RDRAG_LEFT),
    REPEAT(BUTTON_HOME|BUTTON_LEFT,    ACTION_USB_HID_MOUSE_RDRAG_LEFT_REP),
    DOWN  (BUTTON_HOME|BUTTON_RIGHT,   ACTION_USB_HID_MOUSE_RDRAG_RIGHT),
    REPEAT(BUTTON_HOME|BUTTON_RIGHT,   ACTION_USB_HID_MOUSE_RDRAG_RIGHT_REP),
    DOWN  (BUTTON_VOL_UP,              ACTION_USB_HID_MOUSE_WHEEL_SCROLL_UP),
    REPEAT(BUTTON_VOL_UP,              ACTION_USB_HID_MOUSE_WHEEL_SCROLL_UP),
    DOWN  (BUTTON_VOL_DOWN,            ACTION_USB_HID_MOUSE_WHEEL_SCROLL_DOWN),
    REPEAT(BUTTON_VOL_DOWN,            ACTION_USB_HID_MOUSE_WHEEL_SCROLL_DOWN),

    LAST_ITEM_IN_LIST__NEXTLIST(CONTEXT_USB_HID)
}; /* button_context_usb_hid_mode_mouse */
#endif
#endif

/* get_context_mapping returns a pointer to one of the above defined arrays depending on the context */
const struct button_mapping* get_context_mapping(int context)
{
    switch (context)
    {
        case CONTEXT_STD:
            return button_context_standard;

        case CONTEXT_WPS:
            return button_context_wps;

        case CONTEXT_LIST:
            return button_context_list;
        case CONTEXT_TREE:
            if (global_settings.hold_lr_for_scroll_in_list)
                return button_context_listtree_scroll_without_combo;
            else
                return button_context_listtree_scroll_with_combo;
        case CONTEXT_MAINMENU:
            return button_context_mainmenu;
        case CONTEXT_CUSTOM|CONTEXT_TREE:
            return button_context_tree;

        case CONTEXT_SETTINGS:
        case CONTEXT_SETTINGS_TIME:
            return button_context_settings;
        case CONTEXT_CUSTOM|CONTEXT_SETTINGS:
        case CONTEXT_SETTINGS_COLOURCHOOSER:
        case CONTEXT_SETTINGS_EQ:
        case CONTEXT_SETTINGS_RECTRIGGER:
            return button_context_settings_right_is_inc;

        case CONTEXT_YESNOSCREEN:
            return button_context_yesno;
        case CONTEXT_FM:
            return button_context_radio;
        case CONTEXT_BOOKMARKSCREEN:
            return button_context_bmark;
        case CONTEXT_QUICKSCREEN:
            return button_context_quickscreen;
        case CONTEXT_PITCHSCREEN:
            return button_context_pitchscreen;
#ifdef HAVE_RECORDING
        case CONTEXT_RECSCREEN:
            return button_context_recscreen;
#endif
        case CONTEXT_KEYBOARD:
            return button_context_keyboard;
#ifdef USB_ENABLE_HID
        case CONTEXT_USB_HID:
            return button_context_usb_hid;
        case CONTEXT_USB_HID_MODE_MULTIMEDIA:
            return button_context_usb_hid_mode_multimedia;
        case CONTEXT_USB_HID_MODE_PRESENTATION:
            return button_context_usb_hid_mode_presentation;
        case CONTEXT_USB_HID_MODE_BROWSER:
            return button_context_usb_hid_mode_browser;
#ifdef HAVE_USB_HID_MOUSE
        case CONTEXT_USB_HID_MODE_MOUSE:
            return button_context_usb_hid_mode_mouse;
#endif
#endif
        default:
            return button_context_standard;
    }
    return button_context_standard;
}

#endif /* MEYERTIME_KEYMAP */
