SRC += simian.c

ifeq ($(strip $(POINTING_DEVICE_ENABLE)), yes)
    SRC += simian_pointing.c
endif

ifeq ($(strip $(ENCODER_ENABLE)), yes)
    SRC += simian_encoder.c
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    SRC += simian_rgb.c
endif

CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes
MOUSEKEY_ENABLE = yes
