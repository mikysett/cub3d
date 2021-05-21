# Cub3D - 42Lisbon

To clone with submodules: `git clone --recursive <project url>`

Use `make` or `make bonus` for the improved version.

* `m`: toggle minimap
* `f`: toggle fps count
* `Esc`: quit the game

* Render distance related shadows
* Skybox feature
* Delta time used to normalize mouvement speed (with `make bonus` rule)
* Lifebar with healing/damaging items and traps
* Map extras = `3`: Healing object, `4`: Trap

## To compile on linux/mac
* You should install first `MinilibX` on your machine
* In ft_constants.h toggle IS_OS_MAC accordingly
* In Makefile take the LIBS definition accordingly

### Linux Notes
* On linux alpha-byte for pixels doesn't seems to work
In order to have a proper render on linux you should write every layer on the scene layer and sacrifice the shadow effect.
Otherwise background will be black because of obj layer, which is used for sprites.
Normally is transparent everywhere exept on opaque sprites segments.

### Resources
Special thanks to @dda-silv. You can find his repo with useful resources here:
[dda-silv cub3D repo](https://github.com/DimitriDaSilva/42_cub3d)
