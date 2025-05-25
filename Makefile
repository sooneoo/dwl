SRC=src/include

FIND=find
CC=gcc
PKG_CONFIG=pkg-config


XWAYLAND =
XLIBS =
# Uncomment to build XWayland support
XWAYLAND = -DXWAYLAND
XLIBS = xcb xcb-icccm

PKGS = wlroots-0.19 wayland-server xkbcommon libinput pixman-1 fcft $(XLIBS) dbus-1

CFLAGS += -Wall 
CFLAGS += -O3
CFLAGS += -I$(SRC) -I$(SRC)/protocols/
CFLAGS += -DWLR_USE_UNSTABLE
CFLAGS +=-DVERSION=\"1.0\"
CFLAGS += $(XWAYLAND)
CFLAGS += $$(pkg-config --cflags $(PKGS))
CFLAGS += -lm

LIBS += $$(pkg-config --libs $(PKGS))

TARGET=dwl
CACHE=.cache
OUTPUT=$(CACHE)/release
PREFIX = /usr/local
MANDIR = $(PREFIX)/share/man
DATADIR = $(PREFIX)/share


MODULE += main.o
MODULE += util.o
MODULE += dbus.o
MODULE += helpers.o
MODULE += icon.o
MODULE += item.o
MODULE += menu.o
MODULE += tray.o
MODULE += watcher.o


OBJ=$(addprefix $(CACHE)/,$(MODULE))


$(CACHE)/%.o:
	$(CC) $(CFLAGS) -c $< -o $@


all: env $(SRC)/protocols/cursor-shape-v1-protocol.h \
	$(SRC)/protocols/pointer-constraints-unstable-v1-protocol.h \
	$(SRC)/protocols/wlr-layer-shell-unstable-v1-protocol.h \
	$(SRC)/protocols/wlr-output-power-management-unstable-v1-protocol.h \
	$(SRC)/protocols/xdg-shell-protocol.h \
	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(OUTPUT)/$(TARGET) 


-include dep.list


.PHONY: env dep clean install


WAYLAND_SCANNER   = `$(PKG_CONFIG) --variable=wayland_scanner wayland-scanner`
WAYLAND_PROTOCOLS = `$(PKG_CONFIG) --variable=pkgdatadir wayland-protocols`

$(SRC)/protocols/cursor-shape-v1-protocol.h:
	$(WAYLAND_SCANNER) enum-header \
		$(WAYLAND_PROTOCOLS)/staging/cursor-shape/cursor-shape-v1.xml $@
$(SRC)/protocols/pointer-constraints-unstable-v1-protocol.h:
	$(WAYLAND_SCANNER) enum-header \
		$(WAYLAND_PROTOCOLS)/unstable/pointer-constraints/pointer-constraints-unstable-v1.xml $@
$(SRC)/protocols/wlr-layer-shell-unstable-v1-protocol.h:
	$(WAYLAND_SCANNER) enum-header \
		protocols/wlr-layer-shell-unstable-v1.xml $@
$(SRC)/protocols/wlr-output-power-management-unstable-v1-protocol.h:
	$(WAYLAND_SCANNER) server-header \
		protocols/wlr-output-power-management-unstable-v1.xml $@
$(SRC)/protocols/xdg-shell-protocol.h:
	$(WAYLAND_SCANNER) server-header \
		$(WAYLAND_PROTOCOLS)/stable/xdg-shell/xdg-shell.xml $@

dep:
	$(FIND) src -name "*.c" | xargs $(CC) -I$(SRC) -MM | sed 's|[a-zA-Z0-9_-]*\.o|$(CACHE)/&|' > dep.list


exec: all 
	$(OUTPUT)/$(TARGET)


install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	rm -f $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	cp -f $(OUTPUT)/$(TARGET) $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	mkdir -p $(DESTDIR)$(MANDIR)/man1
	cp -f dwl.1 $(DESTDIR)$(MANDIR)/man1
	chmod 644 $(DESTDIR)$(MANDIR)/man1/dwl.1
	mkdir -p $(DESTDIR)$(DATADIR)/wayland-sessions
	cp -f dwl.desktop $(DESTDIR)$(DATADIR)/wayland-sessions/dwl.desktop
	chmod 644 $(DESTDIR)$(DATADIR)/wayland-sessions/dwl.desktop

env:
	mkdir -pv $(CACHE)
	mkdir -pv $(OUTPUT)


clean: 
	rm -rvf $(CACHE)



