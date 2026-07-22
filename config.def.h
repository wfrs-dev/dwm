/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "IosevkaTermSlab NFP:size=10" };
static const char dmenufont[]       = "IosevkaTermSlab NFP:size=10";
/* Esquema de Colores Fedora */
static const char col_bg_norm[]     = "#1c252c"; /* Fondo inactivo (Dark Navy) */
static const char col_border_norm[] = "#3e4b59"; /* Borde inactivo (Slate Gray) */
static const char col_fg_norm[]     = "#a4b0be"; /* Texto inactivo (Light Gray) */

static const char col_bg_sel[]      = "#3c6eb4"; /* Fondo enfocado (Fedora Blue) */
static const char col_border_sel[]  = "#518be8"; /* Borde enfocado (Bright Fedora Blue) */
static const char col_fg_sel[]      = "#ffffff"; /* Texto enfocado (Blanco) */

static const char *colors[][3]      = {
	/*               fg           bg           border   */
	[SchemeNorm] = { col_fg_norm, col_bg_norm, col_border_norm },
	[SchemeSel]  = { col_fg_sel,  col_bg_sel,  col_border_sel  },
};

static const char *const autostart[] = {
    "udiskie", NULL,
    "sh", "~/.config/wscripts/x/screen.sh", NULL,
    "feh", "--bg-fill", "~/.config/wallpaper.jpg", NULL,
    "nm-applet", NULL,
    "sh", "-c", "conky -c ~/.config/conky/conky.lua 2>/dev/null | dwm-setstatus", NULL,
	"alacritty", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "󰎥 ", "󰎨 ", "󰎫 ", "󰎲 ", "󰎯 ", "󰎴 ", "󰎷 ", "󰎺 ", "󰎽 " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "",     NULL,       NULL,       0,            1,           -1 },
	// { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " ",      tile },    /* first entry is default */
	{ " ",      NULL },    /* no layout function means floating behavior */
	{ " ",      monocle },
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-p", "  " "-fn", dmenufont, "-nb", col_bg_norm, "-nf", col_fg_norm, "-sb", col_bg_sel, "-sf", col_fg_sel, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */

    /* 1. GESTIÓN DE VENTANAS Y ENFOQUE */
    // Promueve la ventana enfocada al área principal (Master), o la intercambia con la actual si ya estás en ella.
	{ MODKEY,                       XK_Return, zoom,           {0} },
    // Cambia el foco de la pantalla a la siguiente ventana en la pila.
	{ MODKEY,                       XK_Tab,    focusstack,     {.i = +1 } },
    // Cambia el foco de la pantalla a la ventana anterior en la pila.
	{ MODKEY|ShiftMask,             XK_Tab,    focusstack,     {.i = -1 } },
    // Cierra de forma limpia la ventana que tiene el foco actual.
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    // Lanza la terminal predeterminada
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    // Muestra/oculta la barra de estado
	{ MODKEY,                       XK_b,      togglebar,      {0} },

    /* 2. CONTROL DE DISPOSICIÓN Y LAYOUTS */
    // Activa la disposición dividida estándar (Master a la izquierda, Stack a la derecha).
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    // Cambia al modo flotante, permitiendo mover ventanas libremente sobre la pantalla.
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    // Maximiza la ventana enfocada ocupando toda la pantalla (como vimos antes).
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    // Alterna de forma rápida entre el último layout usado y el actual.
	{ MODKEY,                       XK_space,  setlayout,      {0} },
    // Reduce horizontalmente el tamaño del área principal (Master).
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    // Incrementa horizontalmente el tamaño del área principal (Master).
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    // Incrementa la cantidad de ventanas que pueden estar juntas en el área principal.
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    // Reduce la cantidad de ventanas permitidas en el área principal (mínimo 1).
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

    /* 3. VENTANAS FLOTANTES */
    // Convierte la ventana enfocada a modo flotante (o la regresa al tiling).
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

    /* 4. LANZADOR Y SALIDA */
    // Ejecuta dmenu en la parte superior para buscar y abrir cualquier aplicación.
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    // Cierra el proceso de dwm (esto finaliza la sesión gráfica y te regresa al login).
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

    /* 5. GESTIÓN DE WORKSPACES (TAGS) Y MONITORES */
    // Alterna entr el ultimo tag usado y el actual.
	{ MODKEY|ControlMask,           XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    // Mueve el foco al monitor izquierdo (en configuraciones multipantalla).
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    // Mueve el foco al monitor derecho.
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    // Envía la ventana enfocada al monitor de la izquierda.
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    // Envía la ventana enfocada al monitor de la derecha.
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    // define TAGKEYS(KEY,TAG):
    //     MODKEY + KEY => cambia la vista al TAG seleccionado
    //     MODKEY + Shift + KEY => Mueve la ventana enfocada al TAG seleccionado
    //     MODKEY + Control + KEY => Muestra en pantalla las ventanas de múltiples tags a la vez.
    //     MODKEY + Control + Shift + KEY => Asigna la ventana enfocada a múltiples tags simultáneamente.
	TAGKEYS(XK_ampersand,    0)
	TAGKEYS(XK_bracketleft,  1)
	TAGKEYS(XK_braceleft,    2)
	TAGKEYS(XK_parenleft,    3)
	TAGKEYS(XK_less,         4)
	TAGKEYS(XK_greater,      5)
	TAGKEYS(XK_parenright,   6)
	TAGKEYS(XK_braceright,   7)
	TAGKEYS(XK_bracketright, 8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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
