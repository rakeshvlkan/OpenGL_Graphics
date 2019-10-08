#ifndef CALLBACKS_H
#define CALLBACKS_H
class ICallbacks
{

public:
	virtual void framebuffer_size_callback(int width, int height) {};
	virtual void mouse_callback(double xpos, double ypos) {};
	virtual void scroll_callback(double xoffset, double yoffset) {};
	virtual void RenderScene() {};
	virtual void KeyboardCB(int key, bool IsPressed) {};
};



#endif
