![dwm](./dwm.png)

# dwm - dynamic window manager

Fork personalizado de **dwm 6.8**, el gestor de ventanas dinámico, extremadamente
rápido, pequeño y ligero para X. Incluye parches, herramientas propias y una
configuración adaptada a un entorno con estética Arch Linux, fuente Nerd Font y
scripts de arranque.

## Características

- **Base:** dwm 6.8 (rama `master`).
- **Bandeja del sistema (systray)** — parche `dwm-systray-6.7`.
- **Autostart** — parche `dwm-cool_autostart-6.5` (ver `autostart[]` en `config.def.h`).
- **Estado en todos los monitores** — parche `dwm-statusallmons-6.5`.
- **`dwm-setstatus`** — programa propio equivalente a `xsetroot`: lee líneas de
  `stdin` y actualiza el nombre de la ventana raíz (texto de la barra).
- **dmenu** incluido en `dmenu/`, con un `dmenu_run` optimizado (escaneo directo
  de `$PATH`).
- **Tema Arch Linux:** colores azul/gris definidos en `config.def.h`.
- **Fuente:** `IosevkaTermSlab NFP:size=10`.
- **9 tags** representados con iconos Nerd Font.
- **Atajos personalizados** (ver sección *Atajos*).

## Requisitos

Para compilar dwm se necesitan las cabeceras de Xlib, así como Xinerama,
fontconfig y Xft (freetype):

- `libX11-devel`
- `libXinerama-devel`
- `libXft-devel`
- `fontconfig-devel`

Para compilar `dmenu` se requieren `libX11-devel`, `libXft-devel` y `fontconfig-devel`.

## Compilación e instalación

Ajusta `config.mk` según tu sistema (por defecto se instala en `/usr/local`).
Después:

```sh
make clean install
```

Esto compila e instala `dwm` y `dwm-setstatus` (este último se construye en la
misma regla `dwm` del `Makefile`). Si es necesario, ejecuta con privilegios de
root.

Para el menú de aplicaciones:

```sh
cd dmenu
make clean install
```

## Ejecución

Añade la siguiente línea a tu `.xinitrc` para iniciar dwm con `startx`:

```sh
exec dwm
```

Para conectar dwm a una pantalla concreta, asegúrate de que `DISPLAY` esté
definido correctamente:

```sh
DISPLAY=foo.bar:1 exec dwm
```

### Arranque automático

dwm lanza automáticamente los programas definidos en `autostart[]`
(`config.def.h`): `udiskie`, `dunst`, `nm-applet`, `picom`, `setxkbmap`,
`numlockx`, `alacritty`, `clipcatd`, `feh` (fondo de pantalla), un script de
pantalla y `conky` cuyo flujo se canaliza a `dwm-setstatus`.

### Barra de estado

`dwm-setstatus` permite enviar el estado a la barra sin depender de `xsetroot`:

```sh
conky -c /home/walter/.config/conky/conky.lua | dwm-setstatus
```

## Atajos principales

`MODKEY` es la tecla **Super** (`Mod4Mask`).

| Atajo | Acción |
| --- | --- |
| `MOD + Enter` | Promover ventana enfocada a master (`zoom`) |
| `MOD + Shift + Enter` | Abrir terminal (`alacritty`) |
| `MOD + Tab` / `MOD + Shift + Tab` | Siguiente / anterior ventana |
| `MOD + Shift + c` | Cerrar ventana enfocada |
| `MOD + b` | Mostrar/ocultar barra |
| `MOD + t` / `MOD + f` / `MOD + m` | Layout tile / floating / monocle |
| `MOD + Space` | Alternar layout anterior |
| `MOD + h` / `MOD + l` | Reducir / aumentar área master (`mfact`) |
| `MOD + i` / `MOD + d` | Aumentar / reducir clientes en master |
| `MOD + Shift + Space` | Alternar flotante |
| `MOD + r` | Lanzar `dmenu_run` |
| `MOD + v` | Menú del portapapeles (`clipcat-menu`) |
| `MOD + Shift + q` | Salir de dwm |
| `MOD + 0` | Ver todos los tags |
| `MOD + Shift + 0` | Mover ventana a todos los tags |
| `MOD + ,` / `MOD + .` | Enfocar monitor izquierdo / derecho |
| `MOD + Shift + ,` / `MOD + Shift + .` | Enviar ventana a monitor izquierdo / derecho |

Los tags se manejan con `TAGKEYS(KEY, TAG)`:

- `MOD + tecla` → ver el tag
- `MOD + Shift + tecla` → mover ventana al tag
- `MOD + Ctrl + tecla` → ver varios tags a la vez
- `MOD + Ctrl + Shift + tecla` → asignar ventana a varios tags

## Configuración

La configuración se realiza editando `config.def.h` y recompilando. En la primera
compilación, `config.h` se genera copiando `config.def.h`; para conservar tus
cambios, edita `config.h` (o vuelve a copiar desde `config.def.h`).

## Estructura del proyecto

```
.
├── config.def.h        # Configuración por defecto (colores, tags, atajos, autostart)
├── config.mk           # Versión, rutas, flags y librerías
├── Makefile            # Reglas de compilación/instalación de dwm y dwm-setstatus
├── dwm.c               # Código fuente principal de dwm
├── dwm-setstatus.c     # Actualiza el nombre de la ventana raíz (estado de la barra)
├── drw.c / drw.h       # Utilidades de dibujo (fuentes, colores)
├── util.c / util.h     # Utilidades varias
├── dwm.1               # Página de manual
├── dmenu/              # Menú dinámico incluido (con dmenu_run optimizado)
└── patches/            # Parches aplicados (systray, autostart, statusallmons)
```

## Parches aplicados

| Parche | Descripción |
| --- | --- |
| `dwm-systray-6.7.diff` | Bandeja del sistema en la barra |
| `dwm-cool_autostart-6.5.diff` | Arranque automático de programas |
| `dwm-statusallmons-6.5.diff` | Estado compartido entre monitores |

## Licencia

Consulta el archivo [LICENSE](LICENSE) para detalles sobre derechos y licencia
(MIT/X11).
