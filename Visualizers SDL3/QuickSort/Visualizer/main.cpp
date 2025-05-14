#include <iostream>
#include <vector>
#include <random>
#include <ranges>
#include <algorithm>
#include "SDL3/SDL.h"

void draw_state(const std::vector<int>& v, SDL_Renderer* renderer, int red, int blue) {
    for (int i = 0; i < (int)v.size(); ++i) {
        if (i == red)  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else if (i == blue) SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        else                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderLine(renderer, i, 99, i, v[i]);
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

void QS(std::vector<int>& arr, int start, int end, SDL_Renderer* renderer, bool& running, SDL_Event& e)
{
    if (!running || start >= end) return;

    int i = start;
    int j = end;
    int pivot = arr[(start + end) / 2];

    while (i <= j && running) {
        while (i <= end && arr[i] < pivot) ++i;
        while (j >= start && arr[j] > pivot) --j;
        if (i <= j) {
            std::swap(arr[i], arr[j]);

            // immediate visual update
            check_events(running, e);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            draw_state(arr, renderer, i, j);
            SDL_RenderPresent(renderer);
            SDL_Delay(13);

            ++i; --j;
        }
    }

    if (start < j) QS(arr, start, j, renderer, running, e);
    if (i < end)   QS(arr, i, end, renderer, running, e);
}

int main() {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 99);
    std::vector<int> vec(100);
    for (auto& x : vec) x = dist(rd);

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer("Quicksort Visualizer", 800, 600, 0, &window, &renderer);

    if (!SDL_SetRenderLogicalPresentation(renderer,
        /*w=*/100, /*h=*/100,
        SDL_LOGICAL_PRESENTATION_STRETCH))
    {
        std::cerr << "SDL_SetRenderLogicalPresentation failed: "
            << SDL_GetError() << "\n";
        return 1;
    }

    bool running = true;
    SDL_Event e;

    // run the sort+visualizer
    QS(vec, 0, int(vec.size()) - 1, renderer, running, e);

    if (std::ranges::is_sorted(vec))
        std::cout << "its sorted!\n";

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
