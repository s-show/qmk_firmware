// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "overrides.h"
#include "keymap_japanese.h"
#include "layers.h"

// key override setting start
// 全てのレイヤーでキーオーバーライドを有効化
// Ctrl, Win, Altキーを押していたらキーオーバーライドを発動しない
// JP_* を使わなくても実装可能だが、キーマップの読みやすさを優先して使っている。

// Keycap > US && OS -> JIS の設定
const key_override_t JP_GRV_key_override  = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_GRV,  JP_TILD, 1 << _QWERTY_UJ, MOD_MASK_CAG);
const key_override_t KC_SCLN_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_SCLN, KC_QUOT, 1 << _QWERTY_UJ, MOD_MASK_CAG);
const key_override_t JP_QUOT_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_QUOT, JP_DQUO, 1 << _QWERTY_UJ, MOD_MASK_CAG);
const key_override_t JP_BSLS_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_BSLS, JP_PIPE, 1 << _LOWER_UJ, MOD_MASK_CAG);
const key_override_t KC_MINS_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_MINS, JP_UNDS, 1 << _LOWER_UJ, MOD_MASK_CAG);
const key_override_t JP_EQL_key_override  = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_EQL,  JP_PLUS, 1 << _LOWER_UJ,  MOD_MASK_CAG);
const key_override_t JP_LBRC_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_LBRC, JP_LCBR, 1 << _LOWER_UJ,  MOD_MASK_CAG);
const key_override_t JP_RBRC_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_RBRC, JP_RCBR, 1 << _LOWER_UJ,  MOD_MASK_CAG);
const key_override_t KC_2_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_2,    KC_LBRC, 1 << _LOWER_UJ,  MOD_MASK_CAG);
const key_override_t KC_6_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_6,    KC_EQL,  1 << _LOWER_UJ,  MOD_MASK_CAG);
const key_override_t KC_7_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_7,    JP_AMPR, 1 << _LOWER_UJ,  MOD_MASK_CAG);
const key_override_t KC_8_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_8,    JP_ASTR, 1 << _LOWER_UJ,  MOD_MASK_CAG);
const key_override_t KC_9_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_9,    JP_LPRN, 1 << _LOWER_UJ,  MOD_MASK_CAG);
const key_override_t KC_0_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_0,    JP_RPRN, 1 << _LOWER_UJ,  MOD_MASK_CAG);

// Keycap > JIS && OS -> US の設定
const key_override_t JIS_US_KC_SCLN_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_SCLN, KC_PLUS, 1 << _QWERTY_JU, MOD_MASK_CAG);
const key_override_t JIS_US_KC_COLN_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_COLN, KC_ASTR, 1 << _QWERTY_JU, MOD_MASK_CAG);
const key_override_t JIS_US_KC_AT_key_override   = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_AT,   KC_GRV,  1 << _QWERTY_JU, MOD_MASK_CAG);
const key_override_t JIS_US_KC_MINS_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_MINS, KC_EQL,  1 << _LOWER_JU,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_CIRC_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_CIRC, KC_TILD, 1 << _LOWER_JU,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_BSLS_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_BSLS, KC_UNDS, 1 << _LOWER_JU,  MOD_MASK_CAG);
const key_override_t JIS_US_JP_YEN_key_override  = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_YEN,  KC_PIPE, 1 << _LOWER_JU,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_2_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_2,    KC_DQUO, 1 << _LOWER_JU,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_6_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_6,    KC_AMPR, 1 << _LOWER_JU,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_7_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_7,    KC_QUOT, 1 << _LOWER_JU,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_8_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_8,    KC_LPRN, 1 << _LOWER_JU,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_9_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_9,    KC_RPRN, 1 << _LOWER_JU,  MOD_MASK_CAG);
const key_override_t JIS_US_KC_0_key_override    = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_0,    KC_NO,   1 << _LOWER_JU,  MOD_MASK_CAG);

// Keycap > JIS && OS -> JIS の設定
const key_override_t JIS_JIS_JP_SLSH_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, JP_SLSH, JP_PIPE, 1 << _LOWER_JJ, MOD_MASK_CAG);
