#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////
  //Initialization flag
  bool success_1 = true;
  SDL_Window* gWindow = nullptr;
  SDL_Surface* gScreenSurface = nullptr;

  // //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
      std::cout<<"SDL could not initialize! SDL_Error: "<< SDL_GetError() <<std::endl;
      success_1 = false;
  }
  else
  {
      //Create window
      gWindow = SDL_CreateWindow( "Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN );
      if( gWindow == NULL )
      {
          std::cout<<"Window could not be created! SDL_Error:"<<SDL_GetError()<<std::endl;
          success_1 = false;
      }
      else
      {
          //Get window surface
          gScreenSurface = SDL_GetWindowSurface( gWindow );
      }
  }

  //Loading success flag
  bool success_2 = true;
  SDL_Surface* gHelloWorld = nullptr;
  //Load splash image
  gHelloWorld = SDL_LoadBMP("assets/mamba.bmp");
  if( gHelloWorld == NULL )
  {
      std::cout<<"Unable to load image"<<SDL_GetError()<<std::endl;
      success_2 = false;
  }

  if(!success_1)
  {
      std::cout<<"Failed to initialize!\n";
  }
  else
  {
      //Load media
      if(!success_2)
      {
          std::cout<<"Failed to load media!\n";
      }
      else
      {
          //Apply the image
          SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
          //Update the surface
          SDL_UpdateWindowSurface( gWindow );
          //Wait two seconds
          //SDL_Delay( 2000 );
      }
  }
    SDL_Delay( 4000 );
    // Deallocate surface
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
//////////////////////////////////////////////////////////////////////////////////////////////////
  // // Create Window
  // sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
  //                               SDL_WINDOWPOS_CENTERED, screen_width,
  //                               screen_height, SDL_WINDOW_SHOWN);

  // if (nullptr == sdl_window) {
  //   std::cerr << "Window could not be created.\n";
  //   std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  // }

  // // Create renderer
  // sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  // if (nullptr == sdl_renderer) {
  //   std::cerr << "Renderer could not be created.\n";
  //   std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  // }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
