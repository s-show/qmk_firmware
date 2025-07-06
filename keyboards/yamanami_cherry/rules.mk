# Build Options
#   change yes to no to disable
#
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output

# QMK Features
OLED_ENABLE = yes           # Enable OLED display
OLED_DRIVER = ssd1306       # OLED driver
OLED_TRANSPORT = i2c
KEY_OVERRIDE_ENABLE = yes   # Enable key overrides
COMBO_ENABLE = yes          # Enable key combos
TAP_DANCE_ENABLE = yes      # Enable tap dance

# Source files
SRC += features/combos.c
SRC += features/overrides.c
SRC += features/tap_dance.c
SRC += features/alt_tab.c
SRC += features/dip_switch.c
SRC += display/oled.c

