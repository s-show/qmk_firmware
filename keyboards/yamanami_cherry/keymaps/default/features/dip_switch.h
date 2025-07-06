// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H
#include <stdbool.h>
#include <stdint.h>

bool dip_switch_update_mask_user(uint32_t state);
