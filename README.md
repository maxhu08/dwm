# dwm

this is my fork of dwm

also see my config for `dwmblocks`: https://github.com/maxhu08/dwmblocks

## patches

patches included so far:

- `stacker` https://dwm.suckless.org/patches/stacker
  - makes it so that MOD+J & MOD+K moves windows up & down the stack
- `vanitygaps` https://dwm.suckless.org/patches/vanitygaps
  - provides adjustable gaps with keybinds and more layouts
- `setborderpx` https://dwm.suckless.org/patches/setborderpx
  - provides adjustable borderpx with keybinds
- `tiledmove` https://dwm.suckless.org/patches/tiledmove
  - makes it so MOD+lmb allows windows to stay tiled while moving them
- `resizehere` https://dwm.suckless.org/patches/resizehere
  - prevents mouse from warping to bottom right corner when resizing window

patches i might add later:

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

![1](./screenshots/1.png)

![2](./screenshots/2.png)

![3](./screenshots/3.png)

![4](./screenshots/4.png)

![5](./screenshots/5.png)

![6](./screenshots/6.png)
