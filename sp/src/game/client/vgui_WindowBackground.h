#include <vgui/IVGui.h>
#include <vgui_controls/Frame.h>

class IWindowBackground
{
public:
	virtual void		Create(vgui::VPANEL parent) = 0;
	virtual void		Destroy(void) = 0;
};

extern IWindowBackground* backgroundwindow;

class WindowBackground : public vgui::Frame
{
	DECLARE_CLASS_SIMPLE(WindowBackground, vgui::Frame);

	WindowBackground(vgui::VPANEL parent);
	~WindowBackground() {};

protected:
	virtual void OnCommand(const char* pcCommand);
	virtual void PaintBackground();

private:

};