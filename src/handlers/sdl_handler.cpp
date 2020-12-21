#include "handlers/sdl_handler.h"

int gbox::SDLHandler::m_instance_counter = 0;

gbox::SDLHandler::SDLHandler()
{
  m_ID = m_instance_counter++;
  std::cout<<"Ctor called for SDLHandler with ID "<<m_ID<<" @"<<std::hex<<this<<'\n';
  init_window();
}

gbox::SDLHandler::~SDLHandler()
{
  std::cout<<"Dtor called for SDLHandler with ID "<<m_ID<<" @"<<std::hex<<this<<'\n';
  delete m_window;
}

gbox::SDLHandler::SDLHandler(const SDLHandler& _SDLgbox_other)
{
  m_ID = m_instance_counter++;
  std::cout<<"Copy ctor called for SDLHandler with ID "<<m_ID<<" and SDLHandler with ID "<<_SDLgbox_other.m_ID<<'\n';
}

gbox::SDLHandler& gbox::SDLHandler::operator=(const SDLHandler& _SDLgbox_other)
{
  m_ID = _SDLgbox_other.m_ID;
  std::cout<<"Copy assignment called for SDLHandler with ID "<<m_ID<<" and SDLHandler with ID "<<_SDLgbox_other.m_ID<<'\n';
  return *this;
}

gbox::SDLHandler::SDLHandler(SDLHandler&& _SDLgbox_other)
{
  m_ID = _SDLgbox_other.m_ID;
  std::cout<<"Move ctor called for SDLHandler with ID "<<m_ID<<" and SDLHandler with ID "<<_SDLgbox_other.m_ID<<'\n';
  _SDLgbox_other.m_ID = -1;
}

gbox::SDLHandler& gbox::SDLHandler::operator=(SDLHandler&& _SDLgbox_other)
{
  m_ID = _SDLgbox_other.m_ID;
  std::cout<<"Move assignment called for SDLHandler with ID "<<m_ID<<" and SDLHandler with ID "<<_SDLgbox_other.m_ID<<'\n';
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

  m_window = SDL_CreateWindow(
      "glovebox",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      rect.w/1.2f,
      rect.h/1.2f,
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

  if (!m_window)
  {
    return false;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
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

void gbox::SDLHandler::draw()
{
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
        int w,h;
        SDL_GetWindowSize(m_window,&w,&h);
        break;
      }

      case SDL_KEYDOWN :
      {
        break;
      } // end of keydown

      case SDL_KEYUP :
      {
        break;
      }
      default : break;
    } // end of event switch
  } // end of poll events
  SDL_GL_SwapWindow(m_window);
}