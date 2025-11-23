#include QMK_KEYBOARD_H

#include "bangedorrunt.c"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[MAC_BASE] = LAYOUT_ansi_84(
     CW_TOGG,  KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  KC_SNAP,  KC_DEL,   RGB_MOD,
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,
     KC_TAB,   KC_Q,     NAV_W,    KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,
     HYPR_ESC, HRM_A,    HRM_S,    HRM_D,    HRM_F,    KC_G,     KC_H,     HRM_J,    HRM_K,    HRM_L,    HRM_SCLN, KC_QUOT,              KC_ENT,             KC_HOME,
     KC_LSFT,  KC_Z,     KC_X,     KC_C,     NUM_V,    KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,    KC_END,
     KC_LCTL,  KC_LOPTN, KC_LCMD,                                KC_SPC,                                 KC_RCMD,  MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[MAC_FN] = LAYOUT_ansi_84(
     QK_BOOT,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,  KC_TRNS,  RGB_TOG,
     KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[WIN_BASE] = LAYOUT_ansi_84(
     KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_DEL,   RGB_MOD,
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
     KC_TAB,   KC_Q,     NAV_W,    KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
     HYPR_ESC, HRM_A,    HRM_S,    HRM_D,    HRM_F,    KC_G,     KC_H,     HRM_J,    HRM_K,    HRM_L,    HRM_SCLN, KC_QUOT,            KC_ENT,             KC_HOME,
     KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,            KC_UP,    KC_END,
     KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(WIN_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[WIN_FN] = LAYOUT_ansi_84(
     QK_BOOT,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,  KC_TRNS,  RGB_TOG,
     KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[SYM] = LAYOUT_ansi_84(
     KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_SNAP,  KC_DEL,   RGB_MOD,
     KC_TRNS,  C(KC_Z),  C(KC_V),  C(KC_A),  C(KC_C),  C(KC_X),C(KC_PGUP), KC_PGDN,  KC_PGUP,C(KC_PGDN), KC_TRNS,  KC_MINS,  KC_EQL,   KC_BSPC,            KC_NO,
     KC_TRNS,  KC_TRNS,  KC_LABK,  KC_RABK,  KC_BSLS,  KC_PIPE,  KC_LBRC,  KC_RBRC,  KC_LCBR,  KC_RCBR,  KC_PERC,  KC_TRNS,  KC_NO,    KC_NO,              KC_NO,
     HYPR_ESC, KC_EXLM,  KC_MINS,  KC_PLUS,  KC_EQL ,  KC_AMPR,  KC_HASH,  KC_EQL,   KC_LPRN,  KC_RPRN,  KC_GRV,   KC_TRNS,            KC_ENT,             KC_HOME,
     KC_LSFT,            KC_TRNS,  KC_SLSH,  KC_ASTR,  KC_CIRC,  USRNAME,  KC_CIRC,  KC_DLR ,  KC_LABK,  KC_RABK,  KC_TILD,            KC_RSFT,  KC_UP,    KC_END,
     KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD, KC_TRNS,  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[NUM] = LAYOUT_ansi_84(
     KC_NO,    KC_NO,     KC_NO,   KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,      KC_NO,      KC_NO,    KC_NO,   KC_NO,
     KC_NO,    KC_NO,     KC_NO,   KC_NO,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,    KC_NO,      KC_NO,      KC_NO,             KC_NO,
     KC_NO,    KC_NO,     KC_NO,   KC_NO,     KC_NO,    KC_NO,    KC_TAB,   KC_7,     KC_8,   KC_9,     KC_PLUS,  KC_SLSH,    KC_NO,      KC_NO,             KC_NO,
     HYPR_ESC, KC_NO,     KC_LALT, KC_LSFT,   KC_LCTL,  KC_NO,    KC_0,     KC_4,     KC_5,   KC_6,     KC_MINS,  KC_ASTR,                KC_ENT,            KC_HOME,
     KC_LSFT,             KC_NO,   KC_LCTL,   KC_NO,    KC_NO,    KC_PIPE,  KC_1,     KC_2,   KC_3,     KC_DOT ,  KC_TRNS,                KC_RSFT,  KC_UP,   KC_END,
     KC_LCTL,  KC_LOPTN,  TO(MAC_BASE),                          KC_SPC,                     KC_RCMMD, LLOCK,                KC_RCTL,    KC_LEFT,  KC_DOWN, KC_RGHT),

};
