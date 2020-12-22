#ifndef GBOX_KEYHANDLER_H
#define GBOX_KEYHANDLER_H

#include <iostream>
#include <memory>
#include <array>
#include <set>
#include <vector>

#include "user_io/key_state.h"

namespace gbox
{
  enum keycodes{
    GBKC_unknown=0,
    GBKC_backspace,
    GBKC_tab,
    GBKC_return,
    GBKC_escape,
    GBKC_space,
    GBKC_exclaimation,
    GBKC_double_quote,
    GBKC_hash,
    GBKC_dollar,
    GBKC_percent,
    GBKC_ampersand,
    GBKC_quote,
    GBKC_left_parentheses,
    GBKC_right_parentheses,
    GBKC_asterisk,
    GBKC_plus,
    GBKC_comma,
    GBKC_minus,
    GBKC_period,
    GBKC_forward_slash,
    GBKC_0,
    GBKC_1,
    GBKC_2,
    GBKC_3,
    GBKC_4,
    GBKC_5,
    GBKC_6,
    GBKC_7,
    GBKC_8,
    GBKC_9,
    GBKC_colon,
    GBKC_semicolon,
    GBKC_less_than,
    GBKC_equals,
    GBKC_greater_than,
    GBKC_question,
    qk_at,
    GBKC_left_square,
    GBKC_back_slash,
    GBKC_right_square,
    GBKC_caret,
    GBKC_underscore,
    GBKC_back_quote,
    GBKC_a,
    GBKC_b,
    GBKC_c,
    GBKC_d,
    GBKC_e,
    GBKC_f,
    GBKC_g,
    GBKC_h,
    GBKC_i,
    GBKC_j,
    GBKC_k,
    GBKC_l,
    GBKC_m,
    GBKC_n,
    GBKC_o,
    GBKC_p,
    GBKC_q,
    GBKC_r,
    GBKC_s,
    GBKC_t,
    GBKC_u,
    GBKC_v,
    GBKC_w,
    GBKC_x,
    GBKC_y,
    GBKC_z,
    GBKC_delete,
    GBKC_caps_lock,
    GBKC_F1,
    GBKC_F2,
    GBKC_F3,
    GBKC_F4,
    GBKC_F5,
    GBKC_F6,
    GBKC_F7,
    GBKC_F8,
    GBKC_F9,
    GBKC_F10,
    GBKC_F11,
    GBKC_F12,
    GBKC_print_screen,
    GBKC_scroll_lock,
    GBKC_pause,
    GBKC_insert,
    GBKC_home,
    GBKC_page_up,
    GBKC_end,
    GBKC_page_down,
    GBKC_right,
    GBKC_left,
    GBKC_down,
    GBKC_up,
    GBKC_numlock,
    GBKC_np_divide,
    GBKC_np_multiply,
    GBKC_np_minus,
    GBKC_np_plus,
    GBKC_np_enter,
    GBKC_np_1,
    GBKC_np_2,
    GBKC_np_3,
    GBKC_np_4,
    GBKC_np_5,
    GBKC_np_6,
    GBKC_np_7,
    GBKC_np_8,
    GBKC_np_9,
    GBKC_np_0,
    GBKC_np_period,
    GBKC_application,
    GBKC_power,
    GBKC_np_equals,
    GBKC_np_comma,
    GBKC_left_control,
    GBKC_left_shift,
    GBKC_left_alt,
    GBKC_left_gui,
    GBKC_right_control,
    GBKC_right_shift,
    GBKC_right_alt,
    GBKC_right_gui
  };

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

      void press_key(int _keycode);
      void release_key(int _keycode);

      void update();

      std::vector<std::shared_ptr<gbox::KeyState>> get_active_keys() const;

    private:
      static int m_instance_counter;
      int m_ID;

      std::array<std::shared_ptr<gbox::KeyState>, GBKC_right_gui + 1> m_keystates;
      std::set<int> m_active_keys;

  };// class KeyHandler
}// namespace gbox

#endif // GBOXKEYHANDLERH