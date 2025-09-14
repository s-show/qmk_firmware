// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H

// combo setting start
enum combo_events {
    SDF_ALT_SPACE,
    // JK_IME_ON,
    // DF_IME_OFF,
    DOTSLSH_ALT,
    ZX_ALT,
    MCOMM_WIN,
    CV_WIN,
    SD_CTRL,
    KL_CTRL,
    XC_SALT,
    COMMDOT_SALT,
};

// Combo definitions
extern const uint16_t PROGMEM sdf_combo[];
// extern const uint16_t PROGMEM jk_combo[];
// extern const uint16_t PROGMEM df_combo[];
extern const uint16_t PROGMEM dotslsh_combo[];
extern const uint16_t PROGMEM zx_combo[];
extern const uint16_t PROGMEM mcomm_combo[];
extern const uint16_t PROGMEM cv_combo[];
extern const uint16_t PROGMEM sd_combo[];
extern const uint16_t PROGMEM kl_combo[];
extern const uint16_t PROGMEM xc_combo[];
extern const uint16_t PROGMEM commdot_combo[];

// Function declarations
void process_combo_event(uint16_t combo_index, bool pressed);
