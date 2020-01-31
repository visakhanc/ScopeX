
#include "scope.h"
#include "capture.h"
#include "menu.h"
#include "settings.h"

void Do_ScopeMenu(void);
void Do_ScopeCh1(void);
void Do_ScopeCh2(void);
void Do_ScopeBothCh(void);
void Do_CaptureMenu(void);
void Do_CaptureLowEdge(void);
void Do_CaptureHighEdge(void);
void Do_SettingsMenu(void);
void Do_BacklightMenu(void);


/* Main Menu definition */
MenuItem MainMenuItems[] = {
	
	{ "Scope", Do_ScopeMenu },
	{ "Measure", LA_Measure },
	{ "Capture", Do_CaptureMenu },
	{ "Settings", Do_SettingsMenu }
	
};

Menu MainMenu = {
	
	"MAIN MENU",
	MainMenuItems,
	4	// Oscilloscope, Capture, Measure
};


/* Scope submenu definitions */
MenuItem ScopeMenuItems[] = {

	{ "Channel 1", Do_ScopeCh1 },
	{ "Channel 2", Do_ScopeCh2 },
	{ "Both CH", Do_ScopeBothCh }

};

Menu ScopeMenu = {
	
	"SCOPE",
	ScopeMenuItems,
	3
};


/* Capture submenu definition */
MenuItem CaptureMenuItems[] =  {

	{ "Low Edge", Do_CaptureLowEdge },
	{ "High Edge", Do_CaptureHighEdge }
	
};

Menu CaptureMenu = {
	
	"CAPTURE",
	CaptureMenuItems,
	2
};


/* Settings submenu definition */
MenuItem SettingsMenuItems[] =  {

	{ "Backlight", Do_BacklightMenu }

};

Menu SettingsMenu = {
	
	"SETTINGS",
	SettingsMenuItems,
	1
};

MenuItem BacklightMenuItems[] = {
	
	{ "ON", Backlight_On },
	{ "OFF", Backlight_Off }
};

Menu BacklightMenu = {

	"BACKLIGHT",
	BacklightMenuItems,
	2
};
	



// Call back functions

void Do_ScopeMenu(void)
{
	Do_Menu(&ScopeMenu);
}

void Do_ScopeCh1(void)
{
	Begin_Scope(CH1);
}

void Do_ScopeCh2(void)
{
	Begin_Scope(CH2);
}

void Do_ScopeBothCh(void)
{
	Begin_Scope(BOTH_CH);
}

void Do_CaptureMenu(void)
{
	Do_Menu(&CaptureMenu);
}

void Do_CaptureLowEdge(void)
{
	LA_Capture(LOW_EDGE);
}

void Do_CaptureHighEdge(void)
{
	LA_Capture(HIGH_EDGE);
}


void Do_SettingsMenu(void)
{
	Do_Menu(&SettingsMenu);
	
}

void Do_BacklightMenu(void)
{
	Do_Menu(&BacklightMenu);
}