// jumopking.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "common_function.h"
#include "BaseObject.h"
#include "TextObject.h"

TTF_Font* g_font = NULL;

BaseObject g_background;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("game jump king dream", 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SCREEN_WIDTH, 
                                SCREEN_HEIGHT, 
                                SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
    }

    //Init TTF
    if (TTF_Init() < 0)
        return false;
    //size
    g_font = TTF_OpenFont("fonts/EnterCommand.ttf", 100);

    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("img/background.png", g_screen);
    if (ret == false)
        return false;

    return true;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    TTF_CloseFont(g_font);
    
    IMG_Quit();
    IMG_Quit();
}

int selectMenu() {
    bool running = true;

    TextObject text_start_; //TextObject lop doi tuong
    TextObject text_quit_; //TextObject lop doi tuong

    text_start_.SetText("Start!!");
    text_quit_.SetText("Quit!!");
    text_start_.setColor(TextObject::RED_TEXT);
    text_quit_.setColor(TextObject::RED_TEXT);

    while (running) {
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        text_start_.loadFromRenderedText(g_font, g_screen);
        text_start_.RenderText(g_screen, 100, 100);

        text_quit_.loadFromRenderedText(g_font, g_screen);
        text_quit_.RenderText(g_screen, 400, 100);

        while (SDL_PollEvent(&g_event) != 0) {
            switch (g_event.type) {
            case SDL_QUIT:
                return MENU_QUIT;
                break;
            case SDL_MOUSEBUTTONDOWN:
                int mouseX = g_event.button.x;
                int mouseY = g_event.button.y;
                SDL_Point mouse_point = { mouseX, mouseY };
                SDL_Rect pos_text = text_start_.GetRect();
                if (SDL_PointInRect(&mouse_point, &pos_text))
                {
                    text_start_.setColor(TextObject::BLACK_TEXT);

                }
            }
        }
        

        SDL_RenderPresent(g_screen);
    }

}

#undef main
int main(int argc, char* argv[])
{
    // Khởi tạo SDL2 và cửa sổ
    SDL_Init(SDL_INIT_VIDEO);

    if (InitData() == false)
        return -1;

    if (LoadBackground() == false)
        return -1;

    selectMenu();

    bool is_quit = false;
    while (!is_quit)
    {
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        SDL_RenderPresent(g_screen);
    }

    return 0;
}