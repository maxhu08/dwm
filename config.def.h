// clang-format off

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 0;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 0;       /* vert inner gap between windows */
static const unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Jetbrains Mono NerdFont:size=12", "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_gray1[]       = "#171717";
static const char col_gray2[]       = "#404040";
static const char col_gray3[]       = "#a1a1aa";
static const char col_gray4[]       = "#171717";
static const char col_accent[]      = "#14b8a6";
static const char *colors[][3]      = {
	/*               fg         bg           border     */
	[SchemeNorm] = { col_gray3, col_gray1 ,  col_gray2   },
	[SchemeSel]  = { col_gray4, col_accent,  col_accent  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_accent, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
  /* modifier                     key        function        argument */

	// open app launcher MOD+r
  { MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },

	// spawn terminal MOD+return
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },

  // screenshot MOD+S (requires script in ~/Dev/scripts/screenshot.sh)
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("exec ~/Dev/scripts/screenshot.sh") },

  // open file manager (nemo) MOD+e
	{ MODKEY,                       XK_e,      spawn,          SHCMD("exec nemo") },

	// show hide bar MOD+b
	{ MODKEY,                       XK_b,      togglebar,      {0} },

	// move focus across windows MOD+j Mod+k
	STACKKEYS(MODKEY,                          focus)

	// move windows MOD+J Mod+K
	STACKKEYS(MODKEY|ShiftMask,                push)

	// incrase or decrease windows in master stack MOD+i Mod+d
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

	// adjust mfact MOD+h Mod+l
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	// adjust cfact MOD+H Mod+L Mod+O
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },

	{ MODKEY,                       XK_Return, zoom,           {0} },

	// adjust gaps MOD+ALT+u MOD+ALT+U
	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +10 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -10 } },

	// adjust inside gaps MOD+ALT+i MOD+ALT+i
	// { MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	// { MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },

	//  adjust outside gaps MOD+ALT+o MOD+ALT+o
	// { MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	// { MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },

	// { MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	// { MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	// { MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	// { MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	// { MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	// { MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	// { MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	// { MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	// { MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	// { MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },

	// tab tag
	{ MODKEY,                       XK_Tab,    view,           {0} },

	// close window
	{ MODKEY,                       XK_c,      killclient,     {0} },

	// change layouts MOD+(T|F|M)
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	// { MODKEY,                       XK_space,  setlayout,      {0} },
	// { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	// view all windows MOD+0
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },

	// make window on all tags MOD+SHIFT+0
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	// move window to monitor
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

  // setborderpx MOD+[+-]
  { MODKEY|ShiftMask,             XK_minus, 		  setborderpx,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_plus, 		    setborderpx,    {.i = +1 } },
	// { MODKEY|ShiftMask,             XK_numbersign, 	setborderpx,    {.i = 0 } },

	// change tag MOD+[1-9]
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	// quit dwm MOD+SHIFT+backspace
	{ MODKEY|ShiftMask,             XK_BackSpace, quit,        {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

