<div align="center">

```
gabo's fork of
      ██╗               `
      ██║               `
████████║ ██╗ ██████████╗
██╔═══██║ ██║ ██╔═██╔═██║
████████████████║ ██║ ██║
╚═══════════════╝ ╚═╝ ╚═╝
dynamic window manager
```

dwm is an extremely fast, small, and dynamic window manager for X.

</div>

![](screenshot.jpg)

## Requirements

In order to build dwm you need the `Xlib` header files.

## ⚙️ Installation

Edit `config.mk` to match your local setup (dwm is installed into
the `/usr/local` namespace by default).
`
Afterwards enter the following command to build and install dwm (if
necessary as root):

```sh
make clean install
```

## 🔄 Running dwm

Add the following line to your .xinitrc to start dwm using startx:

```sh
exec dwm
```

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

```sh
DISPLAY=foo.bar:1 exec dwm   # This will start dwm on display :1 of the host foo.bar.
```

In order to display status info in the bar, you can do something
like this in your .xinitrc:

```sh
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
    sleep 1
done &
exec dwm
```

## 🔧 Customizing dwm

The customization/configuration of dwm is done by creating a custom `config.h`
and (re)compiling the source code.

<a name="keybinds"></a>

## ⌨️ Current Keybinds

**Keyboard**

## `navigation`

|          Bind           |            Command            |
| :---------------------: | :---------------------------: |
|      `mod + [1-9]`      |      Switch to tag [1-9]      |
|        `mod + 0`        |         View all tags         |
|  `mod + shift + [1-9]`  |   Move client to tag [1-9]    |
|     `mod + [z / x]`     |  Move focus of window stack   |
| `mod + shift + [z / x]` | Move position of window stack |
|    `mod + shift + q`    |          Kill client          |

<!-- - `mod + [1-9]`: Switch to tag [1-9]
- `mod + 0`: View all tags
- `mod + shift + [1-9]`: Move client to tag [1-9]
- `mod + [z / x]`: Move focus of window stack
- `mod + shift + [z / x]`: Move position of window stack
- `mod + shift + q`: kill client -->

## `layouts`

|         Bind          |              Command              |
| :-------------------: | :-------------------------------: |
|       `mod + t`       |        Set layout to tile         |
|       `mod + f`       |      Set layout to floating       |
|       `mod + m`       |       Set layout to monocle       |
|     `mod + space`     | Alternate two latest used layouts |
| `mod + shift + space` |     Toggle floating on client     |
|       `mod + s`       |        Make window sticky         |

<!-- - `mod + t`: set layout to tile
- `mod + f`: set layout to floating
- `mod + m`: set layout to monocle

- `mod + space`: alternate two latest used layouts
- `mod + shift + space`: toggle floating on client
- `mod + s`: make window sticky -->

## `commands`

|     Bind      |      Command      |
| :-----------: | :---------------: |
|   `mod + w`   |  Spawn terminal   |
|   `mod + b`   | Toggle status bar |
| `mod + print` |    Screenshot     |
|   `mod + r`   |    Restart dwm    |

<!-- - `mod + ctrl + [left / right]`: brightness control using [personal script](https://github.com/gbgabo/scripts)
- `mod + ctrl + [up / down]`: volume control using [personal script](https://github.com/gbgabo/scripts)
- `mod + w`: Spawn terminal
- `mod + b`: Toggle status bar
- `mod + l`: lock screen
- `mod + print`: screenshot
- `mod + r`: restart dwm -->

## `menus`

|        Bind         |                     Menu                     |
| :-----------------: | :------------------------------------------: |
|      `mod + d`      | Spawn application laucher (j4-dmenu-desktop) |
|  `mod + shift + d`  |       Spawn web search (dmenu_tsearch)       |
|  `mod + shift + 9`  |        Spawn dial menu (custom tmenu)        |
|  `mod + shift + e`  |       Spawn focus menu (custom tmenu)        |
| `mod + shift + tab` |  Spawn opened windows menu (dmenu_twindow)   |
|  `mod + shift + p`  |        Spawn password menu (passmenu)        |

<!-- - `mod + d`: Spawn application laucher (j4-dmenu-desktop)
- `mod + shift + d`: Spawn web search (dmenu_tsearch)
- `mod + shift + 9`: Spawn dial menu (custom tmenu)
- `mod + shift + e`: Spawn focus menu (custom tmenu)
- `mod + shift + tab`: Spawn opened windows menu (dmenu_twindow)
- `mod + shift + p`: Spawn pass menu () -->

## `media controls`

|             Bind              |                                    Command                                    |
| :---------------------------: | :---------------------------------------------------------------------------: |
| `mod + ctrl + [left / right]` | Brightness control using [personal script](https://github.com/gbgabo/scripts) |
|  `mod + ctrl + [up / down]`   |   Volume control using [personal script](https://github.com/gbgabo/scripts)   |
|          `mod + ???`          |                                  Mute volume                                  |
|          `mod + ???`          |                               Play/pause media                                |

<!-- - `mod + ctrl + [left / right]`: Brigthness control
- `mod + ctrl + [up / down]`: Volume control
- `mod + ???`: Mute volume -->

## `gaps control`

|                Bind                 |                 Command                 |
| :---------------------------------: | :-------------------------------------: |
|              `mod + g`              |               toggle gaps               |
|           `mod + alt + g`           |            set default gaps             |
|        `mod + alt + [z / x]`        |  increase/decrease general outer gaps   |
|    `mod + alt + ctrl + [z / x]`     |  increase/decrease general inner gaps   |
|      `mod + alt + [up / down]`      | increase/decrease horizontal outer gaps |
|  `mod + alt + ctrl + [up / down]`   | increase/decrease horizontal inner gaps |
|    `mod + alt + [left / right]`     |  increase/decrease vertical outer gaps  |
| `mod + alt + ctrl + [left / right]` |  increase/decrease vertical inner gap   |

<!-- - `mod + g`: toggle gaps
- `mod + alt + g`: set default gaps

- `mod + alt + [z / x]`: increase/decrease general outer gaps
- `mod + alt + ctrl + [z / x]`: increase/decrease general inner gaps

- `mod + alt + [up / down]`: increase/decrease horizontal outer gaps
- `mod + alt + ctrl + [up / down]`: increase/decrease horizontal inner gap

- `mod + alt + [left / right]`: increase/decrease vertical outer gaps
- `mod + alt + ctrl + [left / right]`: increase/decrease vertical inner gap -->

<!-- - **Mouse**

- `mod + drag with left click`: Move client
- `mod + drag with right click`: Resize client -->

## ➕ Current Patches

**Essential stuff**

`restartsig`

- allow dwm to self restart, without the need of leaving Xorg and calling dwm again;
- https://dwm.suckless.org/patches/restartsig/

`alwayscenter`

- makes any new floating window spawn in center of the screen;
- https://dwm.suckless.org/patches/alwayscenter/

**Visual**

`centretitle`

- status bar displays window title at its center;
- https://dwm.suckless.org/patches/centretitle/

`vanitygaps`

- adds gaps for tiling layout;
- there isn't gaps for monocle layout, but the community [finds a way](https://gist.github.com/gbgabo/ef588d7ea043ad5fb60d8369250842b7);
- https://dwm.suckless.org/patches/vanitygaps/

**Utilities**

`focusonnetactive`

- allows dwm to work with `wmctrl -a`, necessary for twindow;
- https://dwm.suckless.org/patches/focusonnetactive/

`push`

- `pushup` and `pushdown` provide a way to move clients inside the clients list;
- https://dwm.suckless.org/patches/push/

`tapresize`

- Allows to resize windows with touchpad;
- https://dwm.suckless.org/patches/tapresize/

`scratchpad`

- Allows to spawn or restore a floating terminal window;
- https://dwm.suckless.org/patches/scratchpad/

## ↗️ Other repositories to check

- [gbgabo/dotfiles](https://github.com/gbgabo/dotfiles): current dotfiles used in my system;
- [gbgabo/dmenu](https://github.com/gbgabo/dmenu): dmenu fork with center patch and own color theme;
- [gbgabo/scripts](https://github.com/gbgabo/scripts): personal scripts for volume control, brightness;
- [TinyTools](https://github.com/TinyToolSH): mainly [tmenu](https://github.com/TinyToolSH/tmenu) and [tsearch](https://github.com/TinyToolSH/tsearch), both used as dmenu wrappers for custom menus and search;
- [gbgabo/wallpapers](https://github.com/gbgabo/wallpapers): dedicated repository for all my wallpapers;
