#include <iostream>
#include <vector>
#include <random>
#include <ranges>
#include <algorithm>
#include "SDL3/SDL.h"
#include <string>

void draw(const std::vector<int>& vec,
    SDL_Renderer* renderer,
    int current,     
    int foundIndex)   
{
    for (int i = 0; i < (int)vec.size(); ++i) {
        if      (i == current)      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else if (i == foundIndex)   SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        else                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderLine(renderer, i, 99, i, vec[i]);
        //SDL_RenderPoint(renderer, i, vec[i]);
        
    }
}

void check_events(bool& running, SDL_Event& e) {
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_EVENT_QUIT:
            running = false;
            break;
        case SDL_EVENT_KEY_DOWN:
            if (e.key.key == SDLK_ESCAPE)
                running = false;
            break;
        default:
            break;
        }
    }
}

void linear_search(std::vector<int>& vec,
    int key,
    SDL_Renderer* renderer,
    SDL_Window* window,
    bool& running,
    SDL_Event& e)
{
    int foundIndex = -1;

    for (int i = 0; i < (int)vec.size() && running; ++i) {
        check_events(running, e);
        if (!running) break;

        if (vec[i] == key) {
            foundIndex = i;

            std::string msg = "Value " + std::to_string(key)
                + " found at index " + std::to_string(i);
            SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_INFORMATION,
                "Linear Search Result",
                msg.c_str(),
                window
            );

            running = false;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw(vec, renderer, i, foundIndex);
            SDL_RenderPresent(renderer);

            break;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw(vec, renderer, i,  -1);
        SDL_RenderPresent(renderer);
        SDL_Delay(30);
    }

    if (running && foundIndex < 0) {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_WARNING,
            "Linear Search Result",
            ("Value " + std::to_string(key) + " not found").c_str(),
            window
        );
    }
}

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(
        "Searching Visualizer",
        800, 600, 0,
        &window,
        &renderer
    );

    if (!SDL_SetRenderLogicalPresentation(renderer,
        /*w=*/100, /*h=*/100,
        SDL_LOGICAL_PRESENTATION_STRETCH))
    {
        std::cerr << "SDL_SetRenderLogicalPresentation failed: "
            << SDL_GetError() << "\n";
        return 1;
    }

    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 99);
    std::vector<int> vec(100);
    for (auto& x : vec) x = dist(rd);

    bool running = true;
    SDL_Event e;

    linear_search(vec, 99, renderer, window, running, e);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
