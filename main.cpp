
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<vector>
#include<list>
#include<cstdlib>
#include "Sho.h"
#include "EnemigoAzul.h"
#include "EnemigoVerde.h"
#include "EnemigoRojo.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background, *instrucciones;
SDL_Rect rect_background, rect_instrucciones;


void loopJuego()
{

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;


    list<Personaje*> personajes;
    personajes.push_back(new Sho(renderer,&personajes));
    personajes.push_back(new EnemigoVerde(renderer,&personajes));
    personajes.push_back(new EnemigoRojo(renderer,&personajes));

    //Main Loop
    int frame=0;
    int animacion_sho = 0;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                exit(0);
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return;
                }
            }
        }

        if(frame%1000==0)
        {
            personajes.push_back(new EnemigoAzul(renderer,&personajes));
        }

        for(list<Personaje*>::iterator p=personajes.begin();
                p!=personajes.end();
                p++)
            (*p)->act();

        SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);

        // Clear the entire screen to our selected color.
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, background, NULL, &rect_background);

        for(list<Personaje*>::iterator p=personajes.begin();
                p!=personajes.end();
                p++)
            (*p)->draw(renderer);

        for(list<Personaje*>::iterator p=personajes.begin();
                p!=personajes.end();
                p++)
            if((*p)->muerto)
            {
                personajes.erase(p);
                break;
            }

        SDL_RenderPresent(renderer);

        frame++;
    }
}

void instructions(){
    int w=0,h=0;
    instrucciones = IMG_LoadTexture(renderer,"fondo_instrucciones.png");
    SDL_QueryTexture(instrucciones, NULL, NULL, &w, &h);
    rect_instrucciones.x = 0;
    rect_instrucciones.y = 0;
    rect_instrucciones.w = w;
    rect_instrucciones.h = h;

   while(true){
    while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                exit(0);
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return;
                }
            }
        }



    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        // Clear the entire screen to our selected color.
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, instrucciones, NULL, &rect_instrucciones);
    SDL_RenderPresent(renderer);
   }

}

class MenuButton
{
public:
    SDL_Texture *selected;
    SDL_Texture *unselected;
//    SDL_Texture *sho_standing_menu;
//    SDL_Texture *sho_punching_menu;
    SDL_Rect rect,sho_standing_rect,sho_punching_rect;
    bool is_selected;
    MenuButton(string selected, string unselected,/*string shoSelected,string shoUnselected*/ int x, int y)
    {
        this->selected = IMG_LoadTexture(renderer,selected.c_str());
        this->unselected = IMG_LoadTexture(renderer,unselected.c_str());
//        this->sho_standing_menu = IMG_LoadTexture(renderer,shoSelected);
//        this->sho_punching_menu = IMG_LoadTexture(renderer,shoUnselected);

        SDL_QueryTexture(this->selected, NULL, NULL, &rect.w, &rect.h);
        rect.x = x;
        rect.y = y;
        is_selected = false;
    }

    void render()
    {
        if(is_selected)
            SDL_RenderCopy(renderer,selected,NULL,&rect);
        else
            SDL_RenderCopy(renderer,unselected,NULL,&rect);
    }

    void select()
    {
        is_selected = true;
    }

    void unselect()
    {
        is_selected = false;
    }
};

void mainMenu()
{
    int w=0,h=0;
    int opcion = 1;
    SDL_Texture *menu_fondo = IMG_LoadTexture(renderer,"menu_fondo.png");
    SDL_Texture *sho_standing_menu= IMG_LoadTexture(renderer,"standing_left.png");
    SDL_Texture *sho_punching_menu= IMG_LoadTexture(renderer,"punch_left.png");

    SDL_Rect menu_rect,sho_standing_rect,sho_punching_rect;
    vector<MenuButton*>buttons;
    vector<MenuButton*>shos;
    buttons.push_back(new MenuButton("button1_selected.png","button1_unselected.png",300,300));
    buttons.push_back(new MenuButton("button2_selected.png","button2_unselected.png",300,400));
    buttons.push_back(new MenuButton("button3_selected.png","button3_unselected.png",300,500));
    SDL_QueryTexture(menu_fondo, NULL, NULL, &menu_rect.w, &menu_rect.h);
    menu_rect.x = 0;
    menu_rect.y = 0;

    SDL_QueryTexture(sho_standing_menu, NULL, NULL, &w, &h);
    sho_standing_rect.x = 500;
    sho_standing_rect.y = 300;
    sho_standing_rect.w = w;
    sho_standing_rect.h = h;

    SDL_QueryTexture(sho_punching_menu, NULL, NULL, &w, &h);
    sho_punching_rect.x = -10;
    sho_punching_rect.y = 300;
    sho_punching_rect.w = w;
    sho_punching_rect.h = h;


    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return;
            }
            if(Event.type == SDL_KEYDOWN)
            {
//                if(Event.key.keysym.sym == SDLK_2)
//                {
//                    exit(0);
//                }
//                if(Event.key.keysym.sym == SDLK_1)
//                {
//                    loopJuego();
//                }
                if(opcion!=0){
                    SDL_RenderCopy(renderer, sho_standing_menu, NULL, &sho_standing_rect);
                    SDL_RenderPresent(renderer);
                }

                if(Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return;
                }
                if(Event.key.keysym.sym == SDLK_DOWN)
                {
                    opcion++;
                    if(opcion > 3)
                        opcion = 3;
                }
                if(Event.key.keysym.sym == SDLK_UP)
                {
                    opcion--;
                    if(opcion < 1)
                        opcion = 1;
                }
                if(Event.key.keysym.sym == SDLK_RETURN)
                {
                    switch(opcion)
                    {
                        case 1:
                            loopJuego();
                        break;
                        case 2:
                            instructions();
                            cout<<"Entro a la opcion 2"<<endl;
                        break;
                        case 3:
                            exit(0);
                        break;
                    }
                }
            }
        }

        SDL_RenderCopy(renderer,menu_fondo,NULL,&menu_rect);


        for(int i=0;i<buttons.size();i++)
        {
            buttons[i]->unselect();
        }
        buttons[opcion-1]->select();
        for(int i=0;i<buttons.size();i++)
        {
            buttons[i]->render();
        }

       SDL_RenderPresent(renderer);
    }
}

int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1024/*WIDTH*/, 768/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    mainMenu();

	return 0;
}
