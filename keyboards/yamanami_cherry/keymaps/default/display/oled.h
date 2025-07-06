// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation);
bool oled_task_user(void);
#endif
