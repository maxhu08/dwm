# dwm

this is my fork of dwm

also see my config for `dwmblocks`: https://github.com/maxhu08/dwmblocks

## patches

patches included so far:

- `stacker` https://dwm.suckless.org/patches/stacker
  - makes it so that MOD+J & MOD+K moves windows up & down the stack
- `vanitygaps` https://dwm.suckless.org/patches/vanitygaps
  - provides adjustable gaps and more layouts
- `tiledmove` https://dwm.suckless.org/patches/tiledmove
  - makes it so MOD+lmb allows windows to stay tiled while moving them
- `resizehere` https://dwm.suckless.org/patches/resizehere
  - prevents mouse from warping to bottom right corner when resizing window

planning to add:

- https://dwm.suckless.org/patches/removeborder

## quick-start

to get started run these commands:

```
git clone https://github.com/maxhu08/dwm
cd dwm
sudo make clean install
```

then add this to your `~/.xinitrc`

```
exec dwm
```

## showcase

![2](./screenshots/2.png)

![1](./screenshots/1.png)
