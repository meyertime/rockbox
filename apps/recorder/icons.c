/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2002 Robert E. Hak
 *
 * All files in this archive are subject to the GNU General Public License.
 * See the file COPYING in the source tree root for full license agreement.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/
#include <string.h>
#include "lcd.h"
#include "font.h"
#include "kernel.h"
#include "sprintf.h"
#include "rtc.h"
#include "powermgmt.h"

#include "settings.h"

#include "icons.h"

const unsigned char bitmap_icons_5x8[][5] =
{
    [Icon_Lock_Main]  ={0x78,0x7f,0x49,0x7f,0x78}, /* Lock Main */
    [Icon_Lock_Remote]={0x78,0x7f,0x49,0x7f,0x78}  /* Lock Remote */
};

const unsigned char bitmap_icons_6x8[][6] =
{
    { 0x60, 0x7f, 0x03, 0x33, 0x3f, 0x00 }, /* Musical note */
    { 0x7e, 0x41, 0x41, 0x42, 0x7e, 0x00 }, /* Folder */
    { 0x55, 0x00, 0x55, 0x55, 0x55, 0x55 }, /* Playlist */
    { 0x3e, 0x1c, 0x08, 0x00, 0x00, 0x00 }, /* Cursor / Marker */
    { 0x58, 0x5f, 0x42, 0x50, 0x55, 0x55 }, /* WPS file */
    { 0x63, 0x7f, 0x3a, 0x7f, 0x63, 0x00 }, /* Mod or ajz file */
    { 0x60, 0x70, 0x38, 0x2c, 0x7e, 0x7e }, /* Font file */
    { 0x3e, 0x2a, 0x3e, 0x2a, 0x2a, 0x3e }, /* Language file */
    { 0x4e, 0x51, 0x51, 0x40, 0x55, 0x55 }, /* Config file */
    { 0x0a, 0x0a, 0x5f, 0x4e, 0x24, 0x18 }, /* Plugin file */
    { 0xff, 0x81, 0xaf, 0xaa, 0x8c, 0xf8 }, /* Bookmark file */
    { 0x77, 0x55, 0x55, 0x55, 0x55, 0x77 }, /* Queued Item */
    { 0x3e, 0x41, 0x3e, 0x1c, 0x1c, 0x08 }, /* Moving Item */
};

const unsigned char bitmap_icons_7x8[][7] =
{
    {0x08,0x1c,0x3e,0x3e,0x3e,0x14,0x14}, /* Power plug */
    {0x1c,0x14,0x3e,0x2a,0x22,0x1c,0x08}, /* USB plug */
    {0x01,0x1e,0x1c,0x3e,0x7f,0x20,0x40}, /* Speaker mute */
    {0x00,0x7f,0x7f,0x3e,0x1c,0x08,0x00}, /* Play */
    {0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f}, /* Stop */
    {0x00,0x7f,0x7f,0x00,0x7f,0x7f,0x00}, /* Pause */
    {0x7f,0x3e,0x1c,0x7f,0x3e,0x1c,0x08}, /* Fast forward */
    {0x08,0x1c,0x3e,0x7f,0x1c,0x3e,0x7f}, /* Fast backward */
    {0x1c,0x3e,0x7f,0x7f,0x7f,0x3e,0x1c}, /* Record */
    {0x1c,0x3e,0x7f,0x00,0x7f,0x3e,0x1c}, /* Record pause */
    {0x40,0xa0,0xa0,0xa0,0x7f,0x02,0x02}, /* Radio on */
    {0x42,0xa4,0xa8,0xb0,0x7f,0x22,0x42}, /* Radio mute */
    {0x44,0x4e,0x5f,0x44,0x44,0x44,0x38}, /* Repeat playmode */
    {0x44,0x4e,0x5f,0x44,0x38,0x02,0x7f}, /* Repeat-one playmode */
    {0x3e,0x41,0x51,0x41,0x45,0x41,0x3e}, /* Shuffle playmode (dice) */
    {0x04,0x0c,0x1c,0x3c,0x1c,0x0c,0x04}, /* Down-arrow */
    {0x20,0x30,0x38,0x3c,0x38,0x30,0x20}, /* Up-arrow */
    {0x7f,0x04,0x4e,0x5f,0x44,0x38,0x7f}  /* Repeat-AB playmode */
};

/* Disk/MMC activity */
const unsigned char bitmap_icon_disk[12] =
#ifdef HAVE_MMC
    {0x15,0x3f,0x7d,0x7B,0x77,0x67,0x79,0x7b,0x57,0x4f,0x47,0x7f};
#else
    {0x00,0x00,0x00,0x1c,0x22,0x41,0x49,0x41,0x22,0x1c,0x00,0x00};
#endif

/*
 * Print play mode to status bar
 */
void statusbar_icon_play_mode(int mode)
{
    lcd_mono_bitmap(bitmap_icons_7x8[mode], ICON_PLAY_MODE_X_POS,
                    STATUSBAR_Y_POS, ICON_PLAY_MODE_WIDTH, STATUSBAR_HEIGHT);
}

/*
 * Print shuffle mode to status bar
 */
void statusbar_icon_shuffle(void)
{
    lcd_mono_bitmap(bitmap_icons_7x8[Icon_Shuffle], ICON_SHUFFLE_X_POS,
                    STATUSBAR_Y_POS, ICON_SHUFFLE_WIDTH, STATUSBAR_HEIGHT);
}
