
enum layers {
  MAC_BASE,
  MAC_FN,
  WIN_BASE,
  WIN_FN,
  SYM,
  NUM,
};

enum { TD_RSFT_LANG };
enum custom_keycodes { LLOCK = SAFE_RANGE, USRNAME };
// Short aliases for home row mods and other tap-hold keys.
#define HYPR_ESC MT(MOD_HYPR, KC_ESC)

#define NAV_W MT(MOD_MEH, KC_W)
#define TD_RSFT TD(TD_RSFT_LANG)

#define HRM_A LT(SYM, KC_A)
#define HRM_S LALT_T(KC_S)
#define HRM_D LCMD_T(KC_D)
#define HRM_F LCTL_T(KC_F)
#define HRM_J RCTL_T(KC_J)
#define HRM_K RCMD_T(KC_K)
#define HRM_L RALT_T(KC_L)
#define HRM_SCLN LT(SYM, KC_SCLN)

#define NUM_V LT(NUM, KC_V)

///////////////////////////////////////////////////////////////////////////////
// Tap-hold configuration (https://docs.qmk.fm/tap_hold)
///////////////////////////////////////////////////////////////////////////////
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case TD_RSFT:
      return TAPPING_TERM - 35;  // Snappier hold for right Shift
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
    // Repeating is useful for Vim navigation keys.
    case HRM_J:
    case HRM_K:
    case KC_H:
    case HRM_L:
      return QUICK_TAP_TERM;  // Enable key repeating.
    default:
      return 0;  // Otherwise, force hold and disable key repeating.
  }
}

#ifdef FLOW_TAP_TERM
bool is_flow_tap_key(uint16_t keycode) {
  if ((get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) != 0) {
    return false;  // Disable Flow Tap on hotkeys.
  }
  // Extract the tap keycode from tap-hold keys
  uint16_t tap_keycode = keycode;
  if (IS_QK_MOD_TAP(keycode)) {
    tap_keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
  } else if (IS_QK_LAYER_TAP(keycode)) {
    tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
  }

  switch (tap_keycode) {
    case KC_SPC:
    case KC_A ... KC_Z:
    case KC_DOT:
    case KC_COMM:
    case KC_SCLN:
    case KC_SLSH:
      return true;
  }
  return false;
}

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t* record,
                           uint16_t prev_keycode) {
  // Only apply Flow Tap when following a letter key, and not hotkeys.
  if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
    switch (keycode) {
      case HRM_F:
      case HRM_J:
      case NAV_W:
      case NUM_V:
        return FLOW_TAP_TERM - 35;  // Shorter timeout otherwise
      case HRM_A:
      case HRM_S:
      case HRM_D:
      case HRM_K:
      case HRM_L:
      case HRM_SCLN:
        return FLOW_TAP_TERM;  // Longer timeout otherwise.
    }
  }

  return 0;  // Disable Flow Tap otherwise.
}
#endif  // FLOW_TAP_TERM

// Track the previous keycode to make contextual decisions for speculative hold
static uint16_t prev_keycode = 0;

bool get_speculative_hold(uint16_t keycode, keyrecord_t* record) {
  // Define keys that should have contextual speculative hold behavior
  bool is_contextual_key = (keycode == HRM_F || keycode == HRM_J);
  bool prev_was_space = prev_keycode == KC_SPC;

  // Disable speculative hold for certain keys when they follow space
  // to prevent issues with chorded sequences in editors and other applications
  if (is_contextual_key && prev_was_space) {
    return false;
  }

  switch (keycode) {  // Enable speculative holding for these keys.
    case HRM_A:
    case HRM_S:
    case HRM_D:
    case HRM_F:
    case HRM_J:
    case HRM_K:
    case HRM_L:
    case HRM_SCLN:
    case NUM_V:
    case NAV_W:
      return true;
  }
  return false;  // Disable otherwise.
}

#ifdef COMBO_ENABLE
const uint16_t combo_dummy[] PROGMEM = {COMBO_END};
combo_t key_combos[] = {
    // Map dummy combo to KC_NO so it does nothing
    COMBO(combo_dummy, KC_NO),
};
#endif

///////////////////////////////////////////////////////////////////////////////
// User macro callbacks (https://docs.qmk.fm/feature_macros)
///////////////////////////////////////////////////////////////////////////////
void keyboard_post_init_user(void) {}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (record->event.pressed) {
    // Update the previous keycode when a key is pressed
    prev_keycode = keycode;

    switch (keycode) {
      case USRNAME:
        SEND_STRING_DELAY("bangedorrunt", TAP_CODE_DELAY);
        return false;
    }
  }

  return true;
}
#ifdef KEY_OVERRIDE_ENABLE
// Hyper + J/K/L/H -> Down/Up/Right/Left
const key_override_t hypr_j_override =
    ko_make_basic(MOD_MASK_CSAG, HRM_J, KC_DOWN);
const key_override_t hypr_k_override =
    ko_make_basic(MOD_MASK_CSAG, HRM_K, KC_UP);
const key_override_t hypr_l_override =
    ko_make_basic(MOD_MASK_CSAG, HRM_L, KC_RIGHT);
const key_override_t hypr_h_override =
    ko_make_basic(MOD_MASK_CSAG, KC_H, KC_LEFT);

const key_override_t* key_overrides[] = {&hypr_j_override, &hypr_k_override,
                                         &hypr_l_override, &hypr_h_override};
#endif

#ifdef TAP_DANCE_ENABLE
// Double tap Shift to macOS input source switch (Ctrl+Space)
tap_dance_action_t tap_dance_actions[] = {
    [TD_RSFT_LANG] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, LCTL(KC_SPC))};
#endif
