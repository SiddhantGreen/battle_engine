# Community Hack

## Building

Requirements (Windows):
- DevkitARM (4.3, 4.5, or 4.7 https://devkitpro.org/wiki/Getting_Started/devkitARM windows installer here)
- Python (Atleast 3.4 https://www.python.org/downloads/)
- Armips(Latest: https://buildbot.orphis.net/armips/)
- Visual C++ runtime DLL https://www.microsoft.com/en-ca/download/details.aspx?id=48145

Make sure you have an *environment variable* for `DEVKITARM`, `python` and `armips`. If not, create them.

Extract the `deps.zip` file. I've taken the liberty of building a few dependancies to save some work.

Next, create a directory called `roms` and place a clean FireRed US version 1.0 ROM inside called `BPRE0.gba`.


Now we can build the project by running `make`.

If the last line is `Done.` then everything succeeded.

Credits:
- https://github.com/Touched project structure
- https://github.com/pret string related tools being used
- https://github.com/Zarel showdown assets such as descriptions and table data
- All contributors!
