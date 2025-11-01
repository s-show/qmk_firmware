// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H
/*
 * カスタムキーコードの定義
 * 
 * なぜ SAFE_RANGE を使った enum ではなく、明示的な値を持つ #define を使用しているか：
 * 
 * 1. 元々の問題：
 *    最初は以下のように定義していました：
 *      enum custom_keycodes { QWERTY = 0, ALT_TAB, WIN_TAB, ... };
 *    この場合、RAISE_UU に 7 が割り当てられ、標準キーコード KC_D (0x07) と
 *    衝突してしまい、KC_D を押すと RAISE レイヤーキーとして誤認識される問題が
 *    発生していました。
 * 
 * 2. enum と SAFE_RANGE を使わない理由：
 *    `enum custom_keycodes { QWERTY = SAFE_RANGE, ... }` が QMK の標準的な
 *    アプローチですが、ヘッダーファイルでこれを使用するとインクルード順序の
 *    依存関係によりコンパイルエラーが発生します。SAFE_RANGE は
 *    quantum_keycodes.h で定義されており、keycodes.h がインクルードされる
 *    時点では利用できない場合があります。
 * 
 * 3. 採用した解決策：
 *    0x7E40 (QK_USER) から始まる明示的な値を持つ #define を使用。
 *    これは QMK のユーザーキーコード範囲で、標準キーコード (0x00-0x7E3F は
 *    QMK システムキーコードとして予約済み) と衝突しません。
 * 
 * 補足: 0x7E40 は QMK ファームウェアにおける QK_USER/SAFE_RANGE の実際の値です。
 */
#define QWERTY  0x7E40
#define ALT_TAB 0x7E41
#define WIN_TAB 0x7E42
#define LOWER_UU 0x7E43
#define LOWER_UJ 0x7E44
#define LOWER_JU 0x7E45
#define LOWER_JJ 0x7E46
#define RAISE_UU 0x7E47
#define RAISE_UJ 0x7E48
#define RAISE_JU 0x7E49
#define RAISE_JJ 0x7E4A
