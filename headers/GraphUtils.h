class APPGraphUtils {
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
public:
	std::thread graph;
	
	void graphRender();
	void graphSetColor(int r, int g, int b);
	void graphCls();
	void graphDrawPlot(int x, int y);
	void graphDrawLine(int x1, int y1, int x2, int y2);
	void graphStop();
	void SDLpollEvents();
	void SDLsandbox();
};
