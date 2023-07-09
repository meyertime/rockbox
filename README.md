@@ -0,0 +1,49 @@ 
# Rockbox, customized by meyertime

For Rockbox generally, see the official website: https://www.rockbox.org/

Original README: [docs/README](docs/README)

This is a fork of Rockbox that implements some customizations specifically for the Sansa Fuze.  They are released as 3 variations:

- `sedimentary` - [Custom keymap](#custom-keymap)
- `igneous` - [Custom FM region](#custom-fm-region)
- `metamorphic` - Combination of `sedimentary` and `igneous`

I plan to publish releases here: https://github.com/meyertime/rockbox/releases

Currently, I am only testing for the Sansa Fuze v2.  If there is interest in `sedimentary` for the Sansa Fuze v1 or `igneous` for the Clip+, please open an issue, and I will provide those builds.

## Custom keymap

The scroll wheel on the Sansa Fuze eventually wears out and becomes hard to turn.  It's also a bit gimmicky in my opinion.  I much preferred the interface of the Clip+.  The custom keymap tries to avoid using the scroll wheel as much as is practical.  It is still used to control the volume in some cases.  Instead, the four direction buttons tend to move things in their respective directions, much like the Clip+.

## Custom FM region

I had a need to receive FM frequencies in the 72-76 MHz range.  This is an unusual band that is not in common use anywhere in the world anymore.  Of all the FM chips supported by Rockbox, only the RDA5802 supports FM frequencies below 76 MHz.  It has a 65-76 MHz band.  However, the official version of Rockbox does not make use of this band, most likely because not all FM chips support it, and it is rarely used anyway.  This customization changes the "Other" FM region to be 65-76 MHz and take advantage of the RDA5802's support for it.  However, if you attempt to use this region with other FM chips, the stated frequency will not match the actual tuning frequency, if you don't run into errors first.

If you've made it this far, then you might be wondering which devices have the RDA5802 chip.  It appears that only _some_ Sansa Fuze v2 units and _some_ Sansa Clip+ units have this chip.  I have only gotten my hands on Sansa Fuze v2 units with this chip.  You can check which FM chip it has in Rockbox's menu: System -> Debug (Keep Out!) -> FM Radio.

There appears to be a correlation between the FM chip and the batch code printed on the back of the Fuze.  (This is not a true serial number, as multiple units have the same code printed on the back, and it's not exactly a model number, because part of the code seems to indicate the year and month of manufacture, so I call it a batch code.)  Here's what I know about the batch code.  The four-digit numeric portion (characters 3 through 6) seem to be a date code in YYMM format, ranging from 2008 to 2011.  The last 3 characters indicate the size of the internal flash memory.  Other than that, I have not been able to decipher the meaning of the rest, but devices with the same batch code seem to have the same FM chip.  Here are the batch codes I have seen and their hardware differences:

Batch code     | Version | FM chip
-------------- | ------- | -------
BH0910BMWK-4GB | v2      | Si4702
BH1002CABK-4GB | v2      | Si4702
BH1006CBAK-4GB | v2      | RDA5802
BH1006CBNK-4GB | v2      | RDA5802

## Development

To build it yourself, first build the platform build tools:

- Clone this repo.
- Create a build directory inside the repo root (e.g. `build`) and change to it.
- Switch to the `master` branch.
- `../tools/rockboxdev.sh --prefix=/some/writable/path`
    - I like to use `tools/build` inside this repo for the prefix.
    - If you run into trouble, clean all build directories, including the ones it makes under `/tmp`.
- Go grab a snack or play a video game.  Building the build tools will take a while...
- The good news is, you only have to do these steps once, as long as you keep the built files around.

Then, build Rockbox:

- Switch to the `stable` branch.
- Change to the build directory you created inside the repo root.
- Add the built build tools to the `PATH`.  For example, if your prefix was `/some/writable/path`, then `export PATH=/some/writable/path/bin:$PATH`.
- `../tools/configure`
    - You will be prompted for the device target, etc.
    - You will also be prompted which meyertime variant to use (`sedimentary`, `igneous`, or `metamorphic`).
    - This step is only needed once per build directory.  You can have multiple build directories configured for different devices.
- `make -j`
    - The `-j` flag enables multi-threading for a faster build on modern machines.
- The output you need is in your build directory; for example, `rockbox.sansa`.
- Optionally, `make zip` will package everything in a zip.