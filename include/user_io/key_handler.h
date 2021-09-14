#ifndef GBOX_KEYHANDLER_H
#define GBOX_KEYHANDLER_H

#define DEBUG_PRINTS

#include <iostream>
#include <memory>
#include <array>
#include <set>
#include <vector>

#include "user_io/key_state.h"
#include "user_io/key_binds.h"

namespace gbox
{
  enum scancodes{
    GBSC_unknown=0,
    GBSC_A=1,
    GBSC_B,
    GBSC_C,
    GBSC_D,
    GBSC_E,
    GBSC_F,
    GBSC_G,
    GBSC_H,
    GBSC_I,
    GBSC_J,
    GBSC_K,
    GBSC_L,
    GBSC_M,
    GBSC_N,
    GBSC_O,
    GBSC_P,
    GBSC_Q,
    GBSC_R,
    GBSC_S,
    GBSC_T,
    GBSC_U,
    GBSC_V,
    GBSC_W,
    GBSC_X,
    GBSC_Y,
    GBSC_Z,
    GBSC_1,
    GBSC_2,
    GBSC_3,
    GBSC_4,
    GBSC_5,
    GBSC_6,
    GBSC_7,
    GBSC_8,
    GBSC_9,
    GBSC_0,
    GBSC_return,
    GBSC_escape,
    GBSC_backspace,
    GBSC_tab,
    GBSC_space,
    GBSC_minus,
    GBSC_equals,
    GBSC_left_bracket,
    GBSC_right_bracket,
    GBSC_backslash,
    GBSC_non_us_hash,
    GBSC_semicolon,
    GBSC_apostrophe,
    GBSC_backtick,
    GBSC_comma,
    GBSC_period,
    GBSC_forward_slash,
    GBSC_caps_lock,
    GBSC_F1,
    GBSC_F2,
    GBSC_F3,
    GBSC_F4,
    GBSC_F5,
    GBSC_F6,
    GBSC_F7,
    GBSC_F8,
    GBSC_F9,
    GBSC_F10,
    GBSC_F11,
    GBSC_F12,
    GBSC_print_screen,
    GBSC_scroll_lock,
    GBSC_pause,
    GBSC_insert,
    GBSC_home,
    GBSC_page_up,
    GBSC_delete,
    GBSC_end,
    GBSC_page_down,
    GBSC_right,
    GBSC_left,
    GBSC_down,
    GBSC_up,
    GBSC_num_lock,
    GBSC_np_divide,
    GBSC_np_multiply,
    GBSC_np_minus,
    GBSC_np_plus,
    GBSC_np_enter,
    GBSC_np_1,
    GBSC_np_2,
    GBSC_np_3,
    GBSC_np_4,
    GBSC_np_5,
    GBSC_np_6,
    GBSC_np_7,
    GBSC_np_8,
    GBSC_np_9,
    GBSC_np_0,
    GBSC_np_period,
    GBSC_non_us_backslash,
    GBSC_application,
    GBSC_power,
    GBSC_np_equals,
    GBSC_F13,
    GBSC_F14,
    GBSC_F15,
    GBSC_F16,
    GBSC_F17,
    GBSC_F18,
    GBSC_F19,
    GBSC_F20,
    GBSC_F21,
    GBSC_F22,
    GBSC_F23,
    GBSC_F24,
    GBSC_execute,
    GBSC_help,
    GBSC_menu,
    GBSC_select,
    GBSC_stop,
    GBSC_again,
    GBSC_undo,
    GBSC_cut,
    GBSC_copy,
    GBSC_paste,
    GBSC_find,
    GBSC_mute,
    GBSC_volumeup,
    GBSC_volumedown,
    GBSC_np_comma,
    GBSC_np_equals_as4,
    GBSC_international1,
    GBSC_international2,
    GBSC_international3,
    GBSC_international4,
    GBSC_international5,
    GBSC_international6,
    GBSC_international7,
    GBSC_international8,
    GBSC_international9,
    GBSC_lang1,
    GBSC_lang2,
    GBSC_lang3,
    GBSC_lang4,
    GBSC_lang5,
    GBSC_lang6,
    GBSC_lang7,
    GBSC_lang8,
    GBSC_lang9,
    GBSC_alt_erase,
    GBSC_sys_req,
    GBSC_cancel,
    GBSC_clear,
    GBSC_prior,
    GBSC_return2,
    GBSC_separator,
    GBSC_out,
    GBSC_oper,
    GBSC_clear_again,
    GBSC_crsel,
    GBSC_exsel,
    GBSC_np_00,
    GBSC_np_000,
    GBSC_thousands_separator,
    GBSC_decimal_separator,
    GBSC_currency_unit,
    GBSC_currency_sub_unit,
    GBSC_np_left_parentheses,
    GBSC_np_right_parentheses,
    GBSC_np_left_brace,
    GBSC_np_right_brace,
    GBSC_np_tab,
    GBSC_np_backspace,
    GBSC_np_A,
    GBSC_np_B,
    GBSC_np_C,
    GBSC_np_D,
    GBSC_np_E,
    GBSC_np_F,
    GBSC_np_xor,
    GBSC_np_power,
    GBSC_np_percent,
    GBSC_np_less,
    GBSC_np_greater,
    GBSC_np_ampersand,
    GBSC_np_double_ampersand,
    GBSC_np_pipe,
    GBSC_np_double_pipe,
    GBSC_np_colon,
    GBSC_np_hash,
    GBSC_np_space,
    GBSC_np_at,
    GBSC_np_exclaim,
    GBSC_np_memstore,
    GBSC_np_memrecall,
    GBSC_np_memclear,
    GBSC_np_memadd,
    GBSC_np_memsubtract,
    GBSC_np_memmultiply,
    GBSC_np_memdivide,
    GBSC_np_plusminus,
    GBSC_np_clear,
    GBSC_np_clear_entry,
    GBSC_np_binary,
    GBSC_np_octal,
    GBSC_np_decimal,
    GBSC_np_hexadecimal,
    GBSC_left_control,
    GBSC_left_shift,
    GBSC_left_alt,
    GBSC_left_gui,
    GBSC_right_control,
    GBSC_right_shift,
    GBSC_right_alt,
    GBSC_right_gui,
    GBSC_mode,
    GBSC_audio_next,
    GBSC_audio_prev,
    GBSC_audio_stop,
    GBSC_audio_play,
    GBSC_audio_mute,
    GBSC_media_select,
    GBSC_browser,
    GBSC_mail,
    GBSC_calculator,
    GBSC_computer,
    GBSC_ac_search,
    GBSC_ac_home,
    GBSC_ac_back,
    GBSC_ac_forward,
    GBSC_ac_stop,
    GBSC_ac_refresh,
    GBSC_ac_bookmarks,
    GBSC_brightness_down,
    GBSC_brightness_up,
    GBSC_display_switch,
    GBSC_keyboard_illum_toggle,
    GBSC_keyboard_illum_down,
    GBSC_keyboard_illum_up,
    GBSC_eject,
    GBSC_sleep,
    GBSC_app1,
    GBSC_app2
  };

  #define GBSCANCODE_MAX_VAL GBSC_app2

  class KeyHandler
  {
    public:
      // dtor
      ~KeyHandler();
      // ctor
      KeyHandler();
      // copy ctor
      KeyHandler(const KeyHandler& _keyhandler_other);
      // copy assignment operator
      KeyHandler& operator=(const KeyHandler& _keyhandler_other);
      // move ctor
      KeyHandler(KeyHandler&& _keyhandler_other);
      // move assignment operator
      KeyHandler& operator=(KeyHandler&& _keyhandler_other);
      // property for ID
      const int& ID() {return m_ID;}

      void flush_keystates();

      void press_key(int _scancode);
      void release_key(int _scancode);

      void update();

      std::vector<std::shared_ptr<gbox::KeyState>> get_active_keys() const;

      void register_keybind(int _scancode, int _keybind);

      std::set<int> get_keybinds(int _scancode) const;

    private:
      static int m_instance_counter;
      int m_ID;

      std::array<std::shared_ptr<gbox::KeyState>, GBSCANCODE_MAX_VAL + 1> m_keystates;
      std::set<int> m_active_keys;

      std::array<std::set<int>, GBSCANCODE_MAX_VAL + 1> m_keybinds;
  };// class KeyHandler
}// namespace gbox

#endif // GBOXKEYHANDLERH