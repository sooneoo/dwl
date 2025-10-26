/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }

#define BGIMG "/home/petr/.config/dwl/wallpaper.png"


/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 1;  /* border pixel of windows */
static const unsigned int systrayspacing   = 2; /* systray spacing */
static const int showsystray               = 1; /* 0 means no systray */
static const float rootcolor[]             = COLOR(0x222222ff);
static const float bordercolor[]           = COLOR(0x444444ff);
static const float focuscolor[]            = COLOR(0x005577ff);
static const float urgentcolor[]           = COLOR(0xff0000ff);

static const char *fonts[]                 = {"monospace:size=10"};

enum { SchemeNorm, SchemeSel, SchemeUrg }; /* color schemes */

static uint32_t colors[][3]                = {
	/*               fg          bg          border    */
                                 
	[SchemeNorm] = { 0xbbbbbbff, 0x222222FF, 0x3A3833FF },
	[SchemeSel]  = { 0xeeeeeeFF, 0xCC7700FF, 0x3A3833FF },
	[SchemeUrg]  = { 0,          0,          0x770000ff },
};


/* This conforms to the xdg-protocol. Set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[] = {0.1f, 0.1f, 0.1f, 1.0f}; /* You can also use glsl colors */

static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8" };


static const char *const autostart[] = {
    "swayidle", "-w",
    //"timeout", "300", "swaylock -f -c 000000",
    //"timeout", "600", "swaymsg 'output * dpms off'",
    //"resume", "swaymsg 'output * dpms on'",
    "before-sleep", "swaylock -f -i"BGIMG, NULL

    ,"swaybg", "-i", BGIMG, "-m", "fill", NULL
    , NULL /* terminate */
};


/* logging */
static int log_level = WLR_ERROR;

/* NOTE: ALWAYS keep a rule declared even if you don't use rules (e.g leave at least one example) */
static const Rule rules[] = {0
	/* app_id             title       tags mask     isfloating   monitor */
	/* examples: */
//	{ "Gimp_EXAMPLE",     NULL,       0,            1,           -1 }, /* Start on currently visible tags floating, not tiled */
//	{ "firefox_EXAMPLE",  NULL,       1 << 8,       0,           -1 }, /* Start on ONLY tag "9" */
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * WARNING: negative values other than (-1, -1) cause problems with Xwayland clients
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899
*/
/* NOTE: ALWAYS add a fallback rule, even if you are completely sure it won't be used */
static const MonitorRule monrules[] = {
	/* name       mfact  nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	*/
	/* defaults */
	//{ NULL,       0.55f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	{ "eDP-1",    0.5f,  1,      1,    layouts, WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	{ "HDMI-1",    0.5f,  1,      1.5,    layouts, WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/

    .layout = "cz",
    .variant = "",
    .options = "grp:alt_shift_toggle"
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;

/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO
/*
#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }
*/

#define TAGKEYS(KEY, SKEY, TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,            tag,             {.ui = 1 << TAG} } \
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char * termcmd[] = { "alacritty", NULL };
static const char * menucmd[] = { "bemenu-run", NULL };

static const char * volumeup[] = {"pamixer", "--increase", "5", NULL };
static const char * volumedown[] = {"pamixer", "--decrease", "5", NULL };
static const char * volumemute[] = {"pamixer", "--toggle-mute", NULL};
static const char * screenshot[] = {"slurp", "|", "grim", NULL};
static const char * brightnessup[] = {"brightnessctl", "set", "+10%", NULL};
static const char * brightnessdown[] = {"brightnessctl", "set", "10%-", NULL};
static const char * screenlock[] = {"swaylock", "-f", "-i", BGIMG, NULL};

/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
 * do not remove them.
 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	{ MODKEY,                    XKB_KEY_p,                        spawn,          {.v = menucmd} },
	{ MODKEY,                    XKB_KEY_Return,                   spawn,          {.v = termcmd} },
    { 0,                         XKB_KEY_XF86AudioRaiseVolume,     spawn,          {.v = volumeup } },
    { 0,                         XKB_KEY_XF86AudioLowerVolume,     spawn,          {.v = volumedown } },
    { 0,                         XKB_KEY_XF86AudioMute,            spawn,          {.v = volumemute } },	
    { 0,                         XKB_KEY_XF86MonBrightnessUp,      spawn,          {.v = brightnessup } },
    { 0,                         XKB_KEY_XF86MonBrightnessDown,    spawn,          {.v = brightnessdown } },
    { MODKEY|WLR_MODIFIER_ALT,   XKB_KEY_s,                        spawn,          {.v = screenshot} },
    { MODKEY,                    XKB_KEY_l,                        spawn,          {.v = screenlock} },

    { MODKEY,                    XKB_KEY_Tab,                      focusstack,     {.i = +1} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_ISO_Left_Tab,             focusstack,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_b,                        togglebar,      {0} },
	{ MODKEY,                    XKB_KEY_i,                        incnmaster,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_d,                        incnmaster,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,                        setmfact,       {.f = -0.05f} },
	{ MODKEY,                    XKB_KEY_l,                        setmfact,       {.f = +0.05f} },
	{ MODKEY,                    XKB_KEY_j,                        zoom,           {0} },
	{ MODKEY,                    XKB_KEY_k,                        view,           {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Q,                        killclient,     {0} },
	{ MODKEY,                    XKB_KEY_t,                        setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_f,                        setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    XKB_KEY_w,                        setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                    XKB_KEY_space,                    setlayout,      {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,                    togglefloating, {0} },
	{ MODKEY,                    XKB_KEY_e,                        togglefullscreen, {0} },
	{ MODKEY,                    XKB_KEY_0,                        view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright,               tag,            {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_comma,                    focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,                   focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,                     tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,                  tagmon,         {.i = WLR_DIRECTION_RIGHT} },
    TAGKEYS(XKB_KEY_plus, XKB_KEY_1, 0),
    TAGKEYS(XKB_KEY_ecaron, XKB_KEY_2, 1),
    TAGKEYS(XKB_KEY_scaron, XKB_KEY_3, 2),
    TAGKEYS(XKB_KEY_ccaron, XKB_KEY_4, 3),
    TAGKEYS(XKB_KEY_rcaron, XKB_KEY_5, 4),
    TAGKEYS(XKB_KEY_zcaron, XKB_KEY_6, 5),
    TAGKEYS(XKB_KEY_yacute, XKB_KEY_7, 6),
    TAGKEYS(XKB_KEY_aacute, XKB_KEY_8, 7),

	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_E,          quit,           {0} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ ClkLtSymbol, 0,      BTN_LEFT,   setlayout,      {.v = &layouts[0]} },
	{ ClkLtSymbol, 0,      BTN_RIGHT,  setlayout,      {.v = &layouts[2]} },
	{ ClkTitle,    0,      BTN_MIDDLE, zoom,           {0} },
	{ ClkStatus,   0,      BTN_MIDDLE, spawn,          {.v = termcmd} },
	{ ClkClient,   MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ ClkClient,   MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ ClkClient,   MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ ClkTagBar,   0,      BTN_LEFT,   view,           {0} },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,     {0} },
	{ ClkTagBar,   MODKEY, BTN_LEFT,   tag,            {0} },
	{ ClkTagBar,   MODKEY, BTN_RIGHT,  toggletag,      {0} },
	{ ClkTray,     0,      BTN_LEFT,   trayactivate,   {0} },
	{ ClkTray,     0,      BTN_RIGHT,  traymenu,       {0} },
};




