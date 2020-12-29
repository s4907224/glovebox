#include "handlers/sdl_handler.h"
#include "helpers/sdl_utils.h"

int gbox::SDLHandler::m_instance_counter = 0;

gbox::SDLHandler::SDLHandler()
{
  m_ID = m_instance_counter++;

  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for SDLHandler with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif

  init_window();
}

gbox::SDLHandler::~SDLHandler()
{
  #ifdef DEBUG_PRINTS
  std::cout<<"Dtor called for SDLHandler with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif

  // delete m_window;
}

gbox::SDLHandler::SDLHandler(const SDLHandler& _SDLgbox_other)
{
  m_ID = m_instance_counter++;
  m_window = _SDLgbox_other.m_window;
  m_context = _SDLgbox_other.m_context;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy ctor called for SDLHandler with ID "<<m_ID<<" and SDLHandler with ID "<<_SDLgbox_other.m_ID<<std::dec<<'\n';
  #endif
}

gbox::SDLHandler& gbox::SDLHandler::operator=(const SDLHandler& _SDLgbox_other)
{
  m_ID = _SDLgbox_other.m_ID;
  m_window = _SDLgbox_other.m_window;
  m_context = _SDLgbox_other.m_context;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy assignment called for SDLHandler with ID "<<m_ID<<" and SDLHandler with ID "<<_SDLgbox_other.m_ID<<std::dec<<'\n';
  #endif

  return *this;
}

gbox::SDLHandler::SDLHandler(SDLHandler&& _SDLgbox_other)
{
  m_ID = _SDLgbox_other.m_ID;
  m_window = _SDLgbox_other.m_window;
  m_context = _SDLgbox_other.m_context;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move ctor called for SDLHandler with ID "<<m_ID<<" and SDLHandler with ID "<<_SDLgbox_other.m_ID<<std::dec<<'\n';
  #endif

  _SDLgbox_other.m_ID = -1;
}

gbox::SDLHandler& gbox::SDLHandler::operator=(SDLHandler&& _SDLgbox_other)
{
  m_ID = _SDLgbox_other.m_ID;
  m_window = _SDLgbox_other.m_window;
  m_context = _SDLgbox_other.m_context;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move assignment called for SDLHandler with ID "<<m_ID<<" and SDLHandler with ID "<<_SDLgbox_other.m_ID<<std::dec<<'\n';
  #endif

  _SDLgbox_other.m_ID = -1;
  return *this;
}

bool gbox::SDLHandler::init_window()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0 || SDL_Init(SDL_INIT_AUDIO) < 0)
  {
    return false;
  }

  Mix_OpenAudio(
      44100,
      MIX_DEFAULT_FORMAT,
      2,
      4096
    );

  //SDL_AudioInit("dsound");

  SDL_Rect rect;
  SDL_GetDisplayBounds(0,&rect);

  m_display_resolution = {rect.w, rect.h};
  m_resolution = {int(rect.w/1.2f), int(rect.h/1.2f)};
  m_alt_resolution = m_resolution;

  m_window = SDL_CreateWindow(
      "glovebox",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      width(),
      height(),
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

  if (!m_window)
  {
    return false;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  m_context = SDL_GL_CreateContext(m_window);
  if(!m_context)
  {
    return false;
  }

  return true;

  SDL_GL_SetSwapInterval(1);

  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(m_window);
  SDL_GL_MakeCurrent(m_window, m_context);
  SDL_GL_SetSwapInterval(1);
}

void gbox::SDLHandler::update()
{
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  m_key_handler->update();
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT :
      {
        m_quit = true; break;
      }

      case SDL_WINDOWEVENT :
      {
        switch (event.window.event)
        {
          case SDL_WINDOWEVENT_SIZE_CHANGED :
          {
            SDL_GetWindowSize(m_window,&m_resolution[0], &m_resolution[1]);
            handle_resize();
            break;
          }
          case SDL_WINDOWEVENT_MOVED :
          {
            if (not m_is_fullscreen)
            {
              m_windowed_position = {event.window.data1, event.window.data2};
            }
            break;
          }
        }
        break;
      }

      case SDL_KEYDOWN :
      {
        m_key_handler->press_key(gbox::sdl_scancode_to_gbox(event.key.keysym.scancode));
        break;
      } // end of keydown

      case SDL_KEYUP :
      {
        m_key_handler->release_key(gbox::sdl_scancode_to_gbox(event.key.keysym.scancode));
        break;
      }
      default : break;
    } // end of event switch
  } // end of poll events
  SDL_GL_SwapWindow(m_window);
}

bool gbox::SDLHandler::toggle_fullscreen()
{
  if(m_is_fullscreen)
  {
    exit_fullscreen();
    return false;
  }
  enter_fullscreen();
  return true;
}

void gbox::SDLHandler::enter_fullscreen()
{
  m_is_fullscreen = true;

  m_alt_resolution = m_resolution;

  m_resolution = m_display_resolution;

  SDL_SetWindowSize(m_window, width(), height());

  if(m_borderless)
  {
    SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  }
  else
  {
    SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
  }
  
}

void gbox::SDLHandler::exit_fullscreen()
{
  m_is_fullscreen = false;

  m_resolution = m_alt_resolution;
  SDL_SetWindowFullscreen(m_window, 0);
  SDL_SetWindowSize(m_window, width(), height());
  SDL_SetWindowPosition(m_window, m_windowed_position[0], m_windowed_position[1]);
}

void gbox::SDLHandler::handle_resize()
{
  resize_gl();
}