// Copyright 2021-2024 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @mainpage Pascal Getreuer's QMK keymap
 *
 * This is my Quantum Mechanical Keyboard (QMK) keymap for the Dactyl Ergodox.
 * Who knew a keyboard could do so much?
 *
 * Feature libraries
 * -----------------
 *  * features/achordion.h: customize the tap-hold decision
 *  * features/autocorrection.h: run rudimentary autocorrection on your keyboard
 *  * features/caps_word.h: modern alternative to Caps Lock
 *  * features/custom_shift_keys.h: they're surprisingly tricky to get right;
 *                                  here is my approach
 *  * features/layer_lock.h: macro to stay in the current layer
 *  * features/mouse_turbo_click.h: macro that clicks the mouse rapidly
 *  * features/orbital_mouse.h: a polar approach to mouse key control
 *  * features/repeat_key.h: a "repeat last key" implementation
 *  * features/sentence_case.h: capitalize first letter of sentences
 *  * features/select_word.h: macro for convenient word or line selection
 *  * features/socd_cleaner.h: enhance WASD for fast inputs for gaming
 *
 * License
 * -------
 * This repo uses the Apache License 2.0 except where otherwise indicated. See
 * LICENSE.txt for details.
 *
 * For further documentation of this keymap's features, see
 * <https://getreuer.info/posts/keyboards>
 */

#ifdef ACHORDION_ENABLE
#include "features/achordion.h"
#endif  // ACHORDION_ENABLE
#ifdef LAYER_LOCK_ENABLE
#include "features/layer_lock.h"
#endif  // LAYER_LOCK_ENABLE

enum layers {
  MAC_BASE,
  ENGRAMMER,
  WIN_BASE,
  WIN_FN,
  SYM,
  NUM,
  WIN,
  FUN,
};

enum custom_keycodes {
  LLOCK = SAFE_RANGE,
  UPDIR,
  USRNAME,
};

// Short aliases for home row mods and other tap-hold keys.
#define HYPR_ESC MT(MOD_HYPR, KC_ESC)

#define QWTY_A LT(SYM, KC_A)
#define QWTY_S LALT_T(KC_S)
#define QWTY_D LSFT_T(KC_D)
#define QWTY_F LCTL_T(KC_F)
#define QWTY_J RCTL_T(KC_J)
#define QWTY_K RSFT_T(KC_K)
#define QWTY_L RALT_T(KC_L)
#define QWTY_SCLN LT(SYM, KC_SCLN)

#define HOME_C LT(SYM, KC_C)
#define HOME_I LALT_T(KC_I)
#define HOME_E LSFT_T(KC_E)
#define HOME_A LCTL_T(KC_A)
#define HOME_T RCTL_T(KC_T)
#define HOME_S RSFT_T(KC_S)
#define HOME_N RALT_T(KC_N)
#define HOME_Q LT(SYM, KC_Q)

#define NUM_V LT(NUM, KC_V)
#define WIN_W LT(WIN, KC_W)

#define NUM_K LT(NUM, KC_K)
#define WIN_Y LT(WIN, KC_Y)

/**
 * Combos (https://docs.qmk.fm/features/combo)
 **/
const uint16_t caps_combo[] PROGMEM = {KC_J, KC_M, COMBO_END};
const uint16_t j_k_combo[] PROGMEM = {KC_J, NUM_K, COMBO_END};
// clang-format off
combo_t key_combos[] = {
    COMBO(caps_combo, CW_TOGG),          // J and M => activate Caps Word.
    COMBO(j_k_combo, OSL(NUM)),          // J and K => one-shot NUM layer
};
// clang-format on

/**
 * Tap-hold configuration (https://docs.qmk.fm/tap_hold)
 **/
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case HOME_I:
    case HOME_N:
    case QWTY_S:
    case QWTY_L:
      return TAPPING_TERM + 15;
    default:
      return TAPPING_TERM;
  }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
  // If you quickly hold a tap-hold key after tapping it, the tap action is
  // repeated. Key repeating is useful e.g. for Vim navigation keys, but can
  // lead to missed triggers in fast typing. Here, returning 0 means we
  // instead want to "force hold" and disable key repeating.
  switch (keycode) {
    case HOME_T:
    case HOME_A:
    // Repeating is useful for Vim navigation keys.
    case QWTY_J:
    case QWTY_K:
    case NUM_K:
      return QUICK_TAP_TERM;  // Enable key repeating.
    default:
      return 0;  // Otherwise, force hold and disable key repeating.
  }
}

/**
 * Achordion (https://getreuer.info/posts/keyboards/achordion)
 **/
#ifdef ACHORDION_ENABLE
bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record,
                     uint16_t other_keycode, keyrecord_t* other_record) {
  // Also allow same-hand holds when the other key is in the rows outside the
  // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboards are split.
  uint8_t row = other_record->event.key.row;
  if (!(1 <= row && row <= 3)) {
    return true;
  }

  switch (tap_hold_keycode) {
    // Exceptionally allow symbol layer LTs + row 0 in same-hand chords.
    case HOME_C:
    case HOME_Q:
    case QWTY_A:
    case QWTY_SCLN:
      if (row == 0) {
        return true;
      }
      break;
    // Exceptionally allow NUM layer combo C + V and J + K as a same-hand chord
    case NUM_V:
      if (other_keycode == KC_C) {
        return true;
      }

    case NUM_K:
      if (other_keycode == KC_J) {
        return true;
      }
      break;
  }

  return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
  switch (tap_hold_keycode) {
    default:
      return 250;  // Use a timeout of 800 ms.
  }
}

uint16_t achordion_streak_chord_timeout(uint16_t tap_hold_keycode,
                                        uint16_t next_keycode) {
  // Disable streak detection on LT keys.
  if (IS_QK_LAYER_TAP(tap_hold_keycode)) {
    return 0;
  }
  // Exceptions so that certain hotkeys don't get blocked as streaks.
  switch (tap_hold_keycode) {
    case HOME_T:
    case QWTY_K:
      if (next_keycode == KC_C || next_keycode == KC_V) {
        return 0;
      }
      break;
    case QWTY_J:
      if (next_keycode == QWTY_K) {
        return 0;
      }
      break;
  }
  // Otherwise, tap_hold_keycode is a mod-tap key.
  const uint8_t mod = mod_config(QK_MOD_TAP_GET_MODS(tap_hold_keycode));
  if ((mod & MOD_LSFT) != 0) {
    return 100;  // A short streak timeout for Shift mod-tap keys.
  } else {
    return 220;  // A longer timeout otherwise.
  }
}
#endif  // ACHORDION_ENABLE

///////////////////////////////////////////////////////////////////////////////
// Status LEDs
///////////////////////////////////////////////////////////////////////////////
#ifdef STATUS_LED_1
// LED 1 indicates when any layer above the SYM layer is active.
layer_state_t layer_state_set_user(layer_state_t state) {
  STATUS_LED_1(get_highest_layer(layer_state) > SYM);
  return state;
}
#endif  // STATUS_LED_1

#ifdef STATUS_LED_2
// LED 2 indicates when Sentence case is in primed to capitalize the next key.
void sentence_case_primed(bool primed) { STATUS_LED_2(primed); }
#endif  // STATUS_LED_2

#ifdef STATUS_LED_3
// LED 3 indicates when Caps word is active.
void caps_word_set_user(bool active) { STATUS_LED_3(active); }
#endif  // STATUS_LED_3

/**
 * User macro callbacks (https://docs.qmk.fm/feature_macros)
 **/

void keyboard_post_init_user(void) {}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
#ifdef ACHORDION_ENABLE
  if (!process_achordion(keycode, record)) {
    return false;
  }
#endif  // ACHORDION_ENABLE
#ifdef LAYER_LOCK_ENABLE
  if (!process_layer_lock(keycode, record, LLOCK)) {
    return false;
  }
#endif  // LAYER_LOCK_ENABLE

  if (record->event.pressed) {
    switch (keycode) {
      case UPDIR:
        SEND_STRING_DELAY("../", TAP_CODE_DELAY);
        return false;
      case USRNAME:
        SEND_STRING_DELAY("bangedorrunt", TAP_CODE_DELAY);
        return false;
    }
  }
  return true;
}

void matrix_scan_user(void) {
#ifdef ACHORDION_ENABLE
  achordion_task();
#endif  // ACHORDION_ENABLE
#ifdef LAYER_LOCK_ENABLE
  layer_lock_task();
#endif  // LAYER_LOCK_ENABLE
}
