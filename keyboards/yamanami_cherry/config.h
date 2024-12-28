/*
Copyright 2021 s-show

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* display setting */
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7
#define OLED_TIMEOUT 0
// #define OLED_FONT_H "keyboards/yamanami_cherry/glcdfont.c"

/* split keyboard setting */
// シリアル通信のピンは `keyboard.json` で設定
#define SERIAL_USART_HALF_DUPLEX
#define SPLIT_OLED_ENABLE

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* combo setting */
// #define COMBO_ONLY_FROM_LAYER 0
#define EXTRA_SHORT_COMBOS  // 同時押しするキー数を6つまでに制限
