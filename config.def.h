/* See LICENSE file for copyright and license details. */

#include "push.c"

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMonoNL-Medium:size=12", "fontawesome:size=9" };
static const char col_gray1[]       = "#240041";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#c79bff";
static const char col_gray4[]       = "#00ffb7";
static const char col_cyan[]        = "#900048";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      							instance    title       tags mask     isfloating   monitor */
	{ "Gimp"								,  NULL,       NULL,       0,            1,           -1 },
	{ "vscodium"							,  NULL,       NULL,       1 << 0,       0,           -1 },
	{ "quterowser"							,  NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Brave-browser"						,  NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Firefox-esr"							,  NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Zathura"								,  NULL,       NULL,       1 << 2,       0,           -1 },
	{ "discord"								,  NULL,       NULL,       1 << 3,       0,           -1 },
	{ "telegram-desktop"					,  NULL,       NULL,       1 << 3,       0,           -1 },

};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;   /* number of clients in master area */
static const int resizehints = 1;   /* 1 means respect size hints in tiled resizals */

/* mouse scroll resize */
static const int scrollsensetivity = 30; /* 1 means resize window by 1 pixel for each scroll event */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  		= {"xfce4-terminal", NULL };
static const char *lockcmd[] 		= {"xscreensaver-command", "-lock", NULL };
static const char *scrotcmd[] 		= {"scrot", "/home/gabo/Pictures/screenshots/%Y-%m-%d-%H_%M_%S.jpg", NULL };
static const char scratchpadname[] 	= "scratchpad";
static const char *scratchpadcmd[] 	= { "st", "-t", scratchpadname, "-g", "120x34", NULL };

/* menus */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] 		= {"j4-dmenu-desktop", "--dmenu", "dmenu -i", NULL };
static const char *tsearchmenu[] 	= {"dmenu_tsearch", NULL };
static const char *dialmenu[] 		= {"tmenu", "/home/gabo/tmenus/dial.yaml", NULL };
static const char *focusmenu[] 		= {"tmenu", "/home/gabo/tmenus/focus.yaml", NULL };
static const char *windowmenu[] 	= {"dmenu_twindow", NULL };
static const char *passmenu[] 		= {"passmenu", NULL };

/* brightness + volume control */
static const char *brightnessup[] 	= {"bctrl", "5+", NULL };
static const char *brightnessdown[] = {"bctrl", "5-", NULL };
static const char *volumeup[] 		= {"vctrl", "5+", NULL };
static const char *volumedown[] 	= {"vctrl", "5-", NULL };
static const char *volumezero[] 	= {"vctrl ", "0%", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	// menus
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_d, 	   spawn,          {.v = tsearchmenu } },
	{ MODKEY,						XK_9, 	   spawn,          {.v = dialmenu } },
	{ MODKEY,                       XK_e,  	   spawn,          {.v = focusmenu } },
	{ MODKEY,			            XK_Tab,    spawn,		   {.v = windowmenu } },
	{ MODKEY|ShiftMask,             XK_p,  	   spawn,          {.v = passmenu } },
	// brightness control
	{ MODKEY|ControlMask,			XK_Right,  spawn,          {.v = brightnessup } },
	{ MODKEY|ControlMask,			XK_Left,   spawn,          {.v = brightnessdown } },
	// volume control
	{ MODKEY|ControlMask,			XK_Up, 	   spawn,          {.v = volumeup } },
	{ MODKEY|ControlMask,			XK_Down,   spawn,          {.v = volumedown } },
	// terminal
	{ MODKEY|ShiftMask,           	XK_w,	   spawn,          {.v = termcmd } },
	{ MODKEY,           			XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                 		XK_w,  	   togglescratch,  {.v = scratchpadcmd } },
	// toggle status bar
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	// lock
	{ MODKEY,            			XK_l,      spawn,		   {.v = lockcmd } },
	// screenshot
	{ MODKEY,			            XK_Print,  spawn,		   {.v = scrotcmd } },
	// Change vertical split position
	{ MODKEY|ControlMask,           XK_z,      setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_x,      setmfact,       {.f = +0.05} },
	// toggle gaps
	{ MODKEY,						XK_g,      togglegaps,     {0} },
	// set default gaps
	{ MODKEY|Mod1Mask,				XK_g,      defaultgaps,    {0} },
	// increase/decrease general gaps
// { MODKEY|Mod1Mask,             	XK_z,      incrgaps,       {.i = +1 } },
// { MODKEY|Mod1Mask,             	XK_x,  	   incrgaps,       {.i = -1 } },
	// increase/decrease general outer gaps
	{ MODKEY|Mod1Mask,				XK_z,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask,    			XK_x,      incrogaps,      {.i = -1 } },
	// increase/decrease general inner gaps
	{ MODKEY|Mod1Mask|ControlMask,	XK_z,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ControlMask,	XK_x,  	   incrigaps,      {.i = -1 } },
	// increase/decrease horizontal outer gaps
	{ MODKEY|Mod1Mask,              XK_Up,     incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_Down,   incrohgaps,     {.i = -1 } },
	// increase/decrease horizontal inner gap
	{ MODKEY|Mod1Mask|ControlMask,	XK_Up,     incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ControlMask,	XK_Down,   incrihgaps,     {.i = -1 } },
	// increase/decrease vertical outer gap
	{ MODKEY|Mod1Mask,             	XK_Left,   incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask,             	XK_Right,  incrovgaps,     {.i = -1 } },
	// increase/decrease vertical inner gap
	{ MODKEY|Mod1Mask|ControlMask, 	XK_Left,   incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ControlMask, 	XK_Right,  incrivgaps,     {.i = -1 } },
//  { MODKEY,                       XK_Return, zoom,           {0} },
//  { MODKEY,                       XK_Tab,    view,           {0} },
	// move position of window stack
	{ MODKEY|ShiftMask,             XK_x,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_z,      pushup,         {0} },
	// move focus of window stack
	{ MODKEY,                       XK_x,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_z,      focusstack,     {.i = -1 } },
	// close window
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	// set layouts - tile, floating, monocle
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },

	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	// view all tags
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	// make windoow sticky
	{ MODKEY,             			XK_s,      tag,            {.ui = ~0 } },
	// ????
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 1  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, //Quits dwm (so it restarts by restartsig patch)
};

/* resizemousescroll direction argument list */
static const int scrollargs[][2] = {
	/* width change         height change */
	{ +scrollsensetivity,	0 },
	{ -scrollsensetivity,	0 },
	{ 0, 				  	+scrollsensetivity },
	{ 0, 					-scrollsensetivity },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      	{0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      	{.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           	{0} },
	{ ClkStatusText,        0,              Button2,        spawn,          	{.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      	{0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, 	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    	{0} },
	// Vertical Scroll
	{ ClkClientWin,         MODKEY,         Button4,        resizemousescroll, 	{.v = &scrollargs[1]} },
	{ ClkClientWin,         MODKEY,         Button5,        resizemousescroll, 	{.v = &scrollargs[0]} },
	// Horizontal Scroll
	{ ClkClientWin,         MODKEY,         Button6,        resizemousescroll, 	{.v = &scrollargs[3]} },
	{ ClkClientWin,         MODKEY,         Button7,        resizemousescroll, 	{.v = &scrollargs[2]} },
	{ ClkTagBar,            0,              Button1,        view,           	{0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     	{0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            	{0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      	{0} },
};


