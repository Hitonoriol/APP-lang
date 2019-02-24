class APPGraphUtils {
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
public:
	int x,y,xx,yy;
	std::string action;
	
	std::thread graph;
	
	void graphRender();
	void graphSetColor(int r, int g, int b);
	void graphCls();
	void graphDrawPlot(int x, int y);
	void graphPreDrawPlot(int x, int y);
	void SDLTasks();
	void graphDrawLine(int x1, int y1, int x2, int y2);
	void graphStop();
	void SDLpollEvents();
	void SDLsandbox();
};
