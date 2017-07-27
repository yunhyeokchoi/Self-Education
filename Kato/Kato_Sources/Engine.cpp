//Engine.h has <list>, <SDL.h> included.
#include "Engine.h"
//It includes <SDL.h>.
#include "Timer.h"
//#include "Macro.h"
#include "DebugTools.h"

#include <fstream> //file stream; open file
#include <sstream> //string stream; file -> string

namespace KatoEngine
{
  Engine::Engine
  (const char* title, unsigned int scrwidth, unsigned int scrheight, std::string strexepath)
    : pm_scrwidth(scrwidth), pm_scrheight(scrheight), pm_title(title),
      pm_psdlwin(0), pm_psurf(0), pm_isquit(false), pm_ptimer(new Timer()),
      pm_strexepath(strexepath)
  {
    Initialize();
  }

  Engine::~Engine()
  {
    if (pm_ptimer)
      delete pm_ptimer;

    SDL_GL_DeleteContext(pm_hglContext);

    glBindVertexArray(0);
    glDeleteProgram(pm_hprogram);
  }

  void Engine::Update()
  {
    //an event handler
    SDL_Event eventhnd; 

    //unsigned int countedFrames = 0;

    //start_tick & end_tick
    Uint32 stat = 0, endt;
    float dt;

    pm_ptimer->Start();

    while (!pm_isquit)
    {
      //Average FPS = number_of_frames / (time_passed / 1000.f)
      //float avgfps = countedFrames / (pm_timer.Show() / 1000.f);

      //printf("AVERAGE FPS = %f\n", avgfps);
      //printf("TIME / 1000.f = %f\n", (pm_timer.Show() / 1000.f));

      if (PollWindowEvent(eventhnd))
        break;


      /*
        while(1)
        {
          end = SDL_GetTicks();
          dt = end - start;
          start = end;
          Function(dt);
        }
      */

      for (int i = 0; i < 100000000; ++i)
      {
        long int x = i * i * i;
        x = x  * x;
      }

      //What if timer's Uint32 value gets overflowed?
      endt = pm_ptimer->Show();
      //printf("endt - stat = %i\n", endt - stat);

      dt = (endt - stat) / 1000.f;
      stat = endt;

      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(pm_hprogram);

      glBindVertexArray(pm_primitive);
      glDrawArrays(GL_TRIANGLES, 1, 3);

      glUseProgram(0);
      glBindVertexArray(0);

      SDL_GL_SwapWindow(pm_psdlwin);
      //KATO_DEBUG_TEST(ENGINE_TEST, printf("dt = %f", dt));

      //printf("%i\n", pm_ptimer->Show());

      //Pretty much this is where the Render & PhysicsUpdate will be called.
      //++countedFrames;

      //PhysicsUpdate(1.f);
    }

    this->Quit();
  }

  bool Engine::PollWindowEvent(SDL_Event& currEvent)
  {
    //Till the event gets emptied out.
    while (SDL_PollEvent(&currEvent))
    {
      PollKeyboardEvent(currEvent);

      /*
        https://wiki.libsdl.org/SDL_EventType#Remarks
        #1 An SDL_QUIT event is generated when the user clicks
        on the close button of the last existing window.
      */
      if (currEvent.type == SDL_QUIT)
      {
        pm_isquit = true;
        return true;
        //Stop assessing for the leftover msgs, and just break.
        //break;
      }
    }

    return false;
  }

  void Engine::PollKeyboardEvent(SDL_Event& currEvent)
  {
    switch (currEvent.type)
    {
      case SDL_KEYDOWN :
      {
        printf("KEYDOWN\n");
        //SetKeyPressed();
        break;
      }
      case SDL_KEYUP :
      {
        printf("KEYUP\n");
        //SetKeyPressed();
        break;
      }
    }
  }

  void Engine::Initialize()
  {
    if (SDL_Init(//SDL's video subsystem
        SDL_INIT_VIDEO) < 0)
        printf("Failed to initialize SDL; %s\n", SDL_GetError());
    else
    {
      pm_psdlwin = SDL_CreateWindow(pm_title,
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    pm_scrwidth,
                                    pm_scrheight,
                                    SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
      if (!pm_psdlwin)
        printf("Failed to create Window; %s\n", SDL_GetError());
      else
      {
        int att;

        //Enable double buffer.
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        //Chose not to use deprecated functions.
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        pm_hglContext = SDL_GL_CreateContext(pm_psdlwin);
        DEBUG_ASSERT(pm_hglContext != 0, "Failed to create context!");

        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &att);
        printf("SDL_GL_CONTEXT_MAJOR_VERSION : %i\n", att);
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &att);
        printf("SDL_GL_CONTEXT_MINOR_VERSION : %i\n", att);

        glewInit();

        glClearColor(0.1f, 0.2f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(pm_psdlwin);

        //Creating shader program
        pm_hprogram = glCreateProgram();
        printf("%s\n", glewGetErrorString(glGetError()));

        //Creating vertex shader
        GLuint vertexshader = ReadShaderSource(GL_VERTEX_SHADER, "C:\\Users\\Student\\Desktop\\Repos\\Kato\\Kato_Sources\\vertexshader.vs");
        GLuint fragmentshader = ReadShaderSource(GL_FRAGMENT_SHADER, "C:\\Users\\Student\\Desktop\\Repos\\Kato\\Kato_Sources\\fragmentshader.fs");
        glAttachShader(pm_hprogram, vertexshader);
        glAttachShader(pm_hprogram, fragmentshader);
        glLinkProgram(pm_hprogram);

        glDetachShader(pm_hprogram, vertexshader);
        glDetachShader(pm_hprogram, fragmentshader);

        glDeleteShader(vertexshader);
        glDeleteShader(fragmentshader);

        GLint iv;
        //int loglen;
        glGetProgramiv(pm_hprogram, GL_LINK_STATUS, &iv);
        //glGetProgramiv(pm_hprogram, GL_INFO_LOG_LENGTH, &loglen);
        if (iv != GL_TRUE)
        {
          DEBUG_ASSERT(iv == GL_TRUE, "Failed to link program.\n");
        }

        glGenVertexArrays(1, &pm_primitive);
        glBindVertexArray(pm_primitive);

        GLuint buffer;
        //Vertices have to be written in clockwise direction.
        GLfloat bufferData[] = { 0.0f, 0.0f, 0.0f,
                                 0.0f, 0.5f, 0.0f,
                                 0.5f, 0.0f, 0.0f,
                                 0.0f, -0.5f, 0.0f,

                                 1.f, 0.f, 0.f, 1.f,
                                 0.f, 1.f, 0.f, 1.f, 
                                 0.f, 0.f, 1.f, 1.f, 
                                 1.f, 0.f, 0.f, 1.f };

        //Create OpenGL buffer object.
        glGenBuffers(1, &buffer);
        //Bind the buffer object we generated to the GL_ARRAY_BUFFER target!
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        //Allocate memory for buffer data in GPU.
        glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), &bufferData, 
                     //GL_STATIC_DRAW let GPU know that bufferData we passed won't change.
                     GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, /*x, y, z*/ 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, /*r, g, b, a*/ 4, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(float[12]));

        glBindVertexArray(0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //Get HDC for the window(?)
        pm_psurf = SDL_GetWindowSurface(pm_psdlwin);
        //perhaps format in the SDL_Surface struct has something to do with
        //pixelformatdescriptor(?)
        SDL_FillRect(pm_psurf, 0, SDL_MapRGB(pm_psurf->format, 0xFF, 0xFF, 0xFF));
        //SwapBuffer(?)
        SDL_UpdateWindowSurface(pm_psdlwin);
        //SDL_Delay(5000);
      }
    }
  }

  void Engine::Quit()
  {
    SDL_DestroyWindow(pm_psdlwin);
    SDL_Quit();
  }

  GLuint Engine::ReadShaderSource(GLenum shadertype, const char* filename)
  {
    std::fstream file;
    //file open
    file.open(filename);
    DEBUG_ASSERT(file.is_open(), "Opening shader failed: %s\n"/*, filename*/);

    std::stringstream sstream;
    //Insert file stream buffer into string stream.
    sstream << file.rdbuf();

    std::string source = sstream.str();
    const char* sourcegl = source.c_str();
    GLuint shader = glCreateShader(shadertype);
    glShaderSource(shader, 1, &sourcegl, 0);

    //Compiling shader.
    glCompileShader(shader);

    GLint iv;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &iv);

    if (iv != GL_TRUE)
      DEBUG_ASSERT(iv == GL_TRUE, "Failed to compile shader source. %s\n"/*, filename*/);

    file.close();
  
    return shader;
  }
}