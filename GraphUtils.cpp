#include "headers/APP.h"

void APPGraphUtils::graphRender(){
	SDL_RenderPresent(renderer);
}

void APPGraphUtils::graphSetColor(int r, int g, int b){
	SDL_SetRenderDrawColor(renderer, r, g, b, 0);
}

void APPGraphUtils::graphCls(){
	SDL_RenderClear(renderer);
	graphRender();
}

void APPGraphUtils::graphDrawPlot(int x, int y){	//:[$0=50][$1=50],
	graphSetColor(255,255,255);
	cout<<"Est probitie"<<endl;
	SDL_RenderDrawPoint(renderer, x, y);
	graphRender();
}

void APPGraphUtils::graphPreDrawPlot(int ax, int ay){
	this->x = ax;
	this->y = ay;
	action = "plot";
	cout<<x<<" "<<y<<" "<<action<<endl;
	SDLTasks();
}

void APPGraphUtils::graphDrawLine(int x1, int y1, int x2, int y2){
	SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
	graphRender();
}

void APPGraphUtils::graphStop(){
		SDL_DestroyWindow(window);
    	SDL_Quit();
	    graph.detach();
		return;
}

void APPGraphUtils::SDLTasks(){
	if (action != "none"){
    	graphDrawPlot(x, y);
    	action = "none";
	}
}

void APPGraphUtils::SDLpollEvents() {
	while (1) {
		SDLTasks();
		SDL_Event event;
    	while (SDL_PollEvent(&event)) {
        	if (event.type == SDL_QUIT) {
				graphStop();
				return;
			}
    	}
	}
}

void APPGraphUtils::SDLsandbox(){
	action = "none";
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
    graphSetColor(0,0,0);
    graphCls();
    graphSetColor(255,255,255);
    if (window == NULL) {
        return;
    }
	SDLpollEvents();
}
