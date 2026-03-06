// Copyright 2024 Alex Baldwin
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Thumb cluster keys
#define NUM_TAB LT(LAYER_NUMPAD, KC_TAB)
#define LW_BSPC LT(LAYER_LOWER, KC_BSPC)
#define RAI_DEL LT(LAYER_RAISE, KC_DEL)
#define NUM_ESC LT(LAYER_NUMPAD, KC_ESC)
#define RAI_ENT LT(LAYER_RAISE, KC_ENT)
#define LW_SPC  LT(LAYER_LOWER, KC_SPC)

// Adjust layer tap keys
#define ADJ_KCQ  LT(LAYER_ADJUST, KC_Q)
#define ADJ_SLSH LT(LAYER_ADJUST, KC_SLSH)

// Lower layer mod-taps
#define ALT_F2  MT(MOD_LALT, KC_F2)
#define CTL_F1  MT(MOD_LCTL, KC_F1)
#define CTL_F10 MT(MOD_LCTL, KC_F10)
#define ALT_F9  MT(MOD_LALT, KC_F9)

// Raise layer mod-taps
#define CTL_EQL RCTL_T(KC_EQL)

// Misc
#define ALT_DOT MT(MOD_LALT, KC_DOT)

// ─── Home row mod macros ───────────────────────────────────────────

// Full GACS home row mods (both hands)
#define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                 \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                 \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                 \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LGUI_T(L10), LALT_T(L11), LSFT_T(L12), LCTL_T(L13),        L14,\
            R15,  RCTL_T(R16), RSFT_T(R17), LALT_T(R18), RGUI_T(R19),\
     LCTL_T(L20),         L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,         R29,  \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

// Left-only GACS home row mods (right hand unmodified)
#define _HOME_ROW_MOD_LEFT_GACS(                                       \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                 \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                 \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                 \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
     LGUI_T(L10), LALT_T(L11), LSFT_T(L12), LCTL_T(L13),         L14,\
             R15,         R16,         R17,         R18,         R19,  \
     LCTL_T(L20),         L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,         R29,  \
      __VA_ARGS__
#define HOME_ROW_MOD_LEFT_GACS(...) _HOME_ROW_MOD_LEFT_GACS(__VA_ARGS__)

// ─── Layer row macros (36-key core) ────────────────────────────────

#define _BASE_L1 ADJ_KCQ,    KC_W,     KC_E,   KC_R,    KC_T
#define _BASE_R1                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _BASE_L2    KC_A,    KC_S,     KC_D,   KC_F,    KC_G
#define _BASE_R2                KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN
#define _BASE_L3    KC_Z,    KC_X,     KC_C,   KC_V,    KC_B
#define _BASE_R3                KC_N,    KC_M, KC_COMM,  KC_DOT,ADJ_SLSH
#define _BASE_TL             NUM_TAB,LW_BSPC, RAI_DEL
#define _BASE_TR             RAI_ENT,  LW_SPC, NUM_ESC

#define LAYOUT_LAYER_BASE \
    _BASE_L1, _BASE_R1, \
    _BASE_L2, _BASE_R2, \
    _BASE_L3, _BASE_R3, \
    _BASE_TL, _BASE_TR

#define LAYOUT_LAYER_POINTER \
    _______, _______, _______, _______, _______,    MS_BTN1, DRGSCRL, _______, _______, _______, \
    _______, _______, _______, _______, _______,    MS_BTN2, SNIPING_MODE, _______, _______, _______, \
    _______, _______, _______, _______, _______,    _______, SNIPING_TOGGLE, _______, _______, _______, \
                      _______, MS_BTN1, MS_BTN2,    _______, _______, _______

#define LAYOUT_LAYER_LOWER \
    G(KC_1), G(KC_2), G(KC_3),  G(KC_4),G(KC_5),    G(KC_6),  G(KC_7),G(KC_8),  G(KC_9),G(KC_0), \
    KC_WBAK, KC_WFWD, KC_HOME,   KC_END, KC_APP,    KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,  KC_F6, \
    CTL_F1,ALT_F2,C(G(KC_LEFT)),C(G(KC_RIGHT)),  KC_F5,    KC_F5,   KC_F7,    KC_F8,  ALT_F9, CTL_F10, \
                      _______, _______, _______,    _______, _______, _______

#define LAYOUT_LAYER_RAISE \
    KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_QUOT, KC_GRV, \
    KC_QUOT,KC_DQT,   KC_LPRN, KC_RPRN, KC_PGUP,    KC_MINS, CTL_EQL, KC_LCBR, KC_RCBR,KC_BSLS, \
    KC_ESC,_______,KC_ESC,KC_ENT, KC_PGDN,           KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_PIPE, \
                      _______, _______, _______,    _______, _______, _______

#define LAYOUT_LAYER_ADJUST \
    XXXXXXX,TG(LAYER_NUMPAD), KC_CAPS, XXXXXXX, XXXXXXX,    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, RM_TOGG, \
    RM_TOGG, RM_NEXT, RM_VALU, RM_VALD, XXXXXXX,            XXXXXXX, KC_WBAK, KC_WFWD,  KC_APP, DRG_TOG, \
    RM_NEXT,RM_PREV, RM_HUEU, RM_HUED, QK_BOOT,             XXXXXXX, XXXXXXX, DPI_DOWN, DPI_UP, DPI_CYCLE, \
                      _______, _______, _______,    KC_VOLD, KC_VOLU, KC_MPLY

#define LAYOUT_LAYER_NUMPAD \
    TG(LAYER_NUMPAD), KC_F9,   KC_F8,  KC_F7,  KC_F12,    KC_CIRC,   KC_7,   KC_8,   KC_9, KC_ASTR, \
    KC_NO,  KC_F6,   KC_F5,  KC_F4,  KC_F11,              KC_MINS,   KC_4,   KC_5,   KC_6,  KC_EQL, \
    KC_LSFT,  KC_F3,   KC_F2,  KC_F1,  KC_F10,            KC_PLUS,   KC_1,   KC_2,   KC_3, KC_SLSH, \
                      _______, _______, _______,    KC_ENT,    KC_0, KC_DOT

// ─── Wrapper macros for different keyboard layouts ─────────────────

// Simityl / Skeletyl: 3x5 + 3 thumb keys per side
#define LAYOUT_split_3x5_3_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

// Corne (crkbd): 3x6 + 3 thumb keys per side — adds outer column
#define _CORNE_WRAP6(                                                  \
    OL1, L01, L02, L03, L04, L05, R06, R07, R08, R09, R10, OR1,       \
    OL2, L11, L12, L13, L14, L15, R16, R17, R18, R19, R20, OR2,       \
    OL3, L21, L22, L23, L24, L25, R26, R27, R28, R29, R30, OR3,       \
              LT1, LT2, LT3,                   RT1, RT2, RT3)         \
    OL1, L01, L02, L03, L04, L05, R06, R07, R08, R09, R10, OR1,       \
    OL2, L11, L12, L13, L14, L15, R16, R17, R18, R19, R20, OR2,       \
    OL3, L21, L22, L23, L24, L25, R26, R27, R28, R29, R30, OR3,       \
              LT1, LT2, LT3,                   RT1, RT2, RT3

#define LAYOUT_split_3x6_3_wrapper(...) LAYOUT_split_3x6_3(_CORNE_WRAP6(__VA_ARGS__))

// Helper: wrap a 36-key layer into 42 keys for corne by adding outer columns
#define CORNE_OUTER(OL1, OL2, OL3, OR1, OR2, OR3, ...) \
    _CORNE_ADD_OUTER(OL1, OL2, OL3, OR1, OR2, OR3, __VA_ARGS__)

#define _CORNE_ADD_OUTER(                                              \
    OL1, OL2, OL3, OR1, OR2, OR3,                                     \
    L01, L02, L03, L04, L05, R06, R07, R08, R09, R10,                 \
    L11, L12, L13, L14, L15, R16, R17, R18, R19, R20,                 \
    L21, L22, L23, L24, L25, R26, R27, R28, R29, R30,                 \
              LT1, LT2, LT3,           RT1, RT2, RT3)                 \
    OL1, L01, L02, L03, L04, L05, R06, R07, R08, R09, R10, OR1,       \
    OL2, L11, L12, L13, L14, L15, R16, R17, R18, R19, R20, OR2,       \
    OL3, L21, L22, L23, L24, L25, R26, R27, R28, R29, R30, OR3,       \
              LT1, LT2, LT3,           RT1, RT2, RT3
