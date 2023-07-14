# Rockbox, customized by meyertime

For Rockbox generally, see the official website: https://www.rockbox.org/

Original README: [docs/README](docs/README)

This is a fork of Rockbox that implements some customizations specifically for the Sansa Fuze.  They are released as 3 variations:

- `sedimentary` - [Custom keymap](#custom-keymap) and some [other improvements](#other-improvements)
- `igneous` - [Custom FM regions](#custom-fm-regions), some [additional radio refinements](#additional-radio-refinements), and some [other improvements](#other-improvements)
- `metamorphic` - Combination of `sedimentary` and `igneous`

These customizations are based on the latest stable version of Rockbox.  Releases are published here: https://github.com/meyertime/rockbox/releases

Currently, I am only testing for the Sansa Fuze.  If there is interest in `igneous` for the Clip+, please open an issue, and I will provide the build.

## Breaking changes

Please take special note of the following breaking changes when compared to the official Rockbox:

- These builds are designed to be booted from the microSD card and will most likely not work when booted from internal flash memory.  See [boot from microSD card](#boot-from-microsd-card) for more information.
- The [custom FM regions](#custom-fm-regions) will not work unless the device has the RDA5802 FM chip; therefore, do not install `igneous` or `metamorphic` builds on devices that do not have this FM chip.
- The [custom FM region](#custom-fm-regions) names are hard-coded rather than having translations depending on the configured language.  These may or may not make sense in languages other than English.

## Custom keymap

This section applies to `sedimentary` and `metamorphic` builds.

The scroll wheel on the Sansa Fuze eventually wears out and becomes hard to turn.  It's also a bit gimmicky in my opinion.  I much preferred the interface of the Clip+.  The custom keymap tries to avoid using the scroll wheel as much as is practical.  It is still used to control the volume in some cases.  Instead, the four direction buttons tend to move things in their respective directions, much like the Clip+.

## Custom FM regions

This section applies to `igneous` and `metamorphic` builds.

This customization changes the "Other" FM region to be 65-76 MHz and take advantage of the RDA5802's support for it.  It also adds 3 more regions in order to make available every combination of step (.05 or .1 MHz) and emphasis (50 or 75 μS) supported by this chip for this band.  However, if you attempt to use any of these regions with other FM chips, the stated frequency will not match the actual tuning frequency, if you don't run into errors first.

I had a need to receive FM frequencies in the 72-76 MHz range.  This is an unusual band that is not in common use anywhere in the world anymore.  Of all the FM chips supported by Rockbox, only the RDA5802 supports FM frequencies below 76 MHz.  It has a 65-76 MHz band.  However, the official version of Rockbox does not make use of this band, most likely because not all FM chips support it, and it is rarely used anyway.

If you've made it this far, then you might be wondering which devices have the RDA5802 chip.  It appears that only _some_ Sansa Fuze v2 units and _some_ Sansa Clip+ units have this chip.  I have only gotten my hands on Sansa Fuze v2 units with this chip.  You can check which FM chip it has in Rockbox's menu: System -> Debug (Keep Out!) -> FM Radio.

There appears to be a correlation between the FM chip and the batch code printed on the back of the Fuze.  (This is not a true serial number, as multiple units have the same code printed on the back, and it's not exactly a model number, because part of the code seems to indicate the year and month of manufacture, so I call it a batch code.)  Here's what I know about the batch code.  The four-digit numeric portion (characters 3 through 6) seem to be a date code in YYMM format, ranging from 2008 to 2011.  The last 3 characters indicate the size of the internal flash memory.  Other than that, I have not been able to decipher the meaning of the rest, but devices with the same batch code seem to have the same FM chip.  Here are the batch codes I have seen and their hardware differences:

Batch code     | Version | FM chip
-------------- | ------- | -------
BH0910BMWK-4GB | v2      | Si4702
BH1002CABK-4GB | v2      | Si4702
BH1006CBAK-4GB | v2      | RDA5802
BH1006CBNK-4GB | v2      | RDA5802

### Additional radio refinements

This section applies to `igneous` and `metamorphic` builds.

- FM radio no longer prompts to auto-scan when there are no presets.  Auto-scan is still available in the FM radio menu.
- FM radio now defaults to "Scan" mode at all times.  Previously, FM radio defaulted to "Preset" mode when there are presets and the current frequency corresponds to one of the presets.
- You will now be prompted to save presets after clearing or deleting the last preset.  Previously, there was no way to clear FM presets permanently without editing the preset file by hand.  You still cannot save a new preset file when there are no presets to save.

## Other improvements

This section applies to all builds.

- Fixed `grep: warning: stray \ before #` warnings during build process.
- Added meyertime to the credits.
- Avoid using internal flash memory entirely; see the following section for details.

### Boot from microSD card

Rockbox has the ability to boot from firmware located on the microSD card rather than internal flash memory.  As long as you have the latest v3.15 bootloader installed on the device, it will look for a special file on the microSD card to indicate where to look for firmware.  For example, Rockbox is normally loaded from a directory called `.rockbox` in internal flash memory; however, on a Fuze v2 device, if a file called `rockbox_main.fuze2` is found on the microSD card root, and its contents are empty or `/`, it will load Rockbox firmware from `/<microSD1>/.rockbox`.  If the contents indicate some other directory, such as `/example`, it will load from `/<microSD1>/example/.rockbox`.  For a Fuze v1 device, it will look for `rockbox_main.fuze`.  For a Clip+ device, it will look for `rockbox_main.clip+`.

The reason for this is because all flash memory wears out as it is written to.  In other words, it has a limited number of writes that can be done before the memory can no longer be written to.  If that happens to the device's internal flash memory, then best case scenario, the device will still function, but anything written to the internal memory will not have any effect.  Worst case scenario, the internal memory is left in an invalid state, and the device will no longer function at all.  That's why it is best to avoid using the internal memory and use only a microSD card inserted into the device.  These cards are cheap and easy to replace, unlike the internal flash memory chip.

However, at least with the latest stable version of Rockbox, v3.15, it still looks to the internal flash memory and saves to it for many things, including configuration, theme files, plugins, etc.  I have made changes in this fork to make it look to `/<microSD1>/.rockbox` for everything.  This is a bit of a hacky workaround, because it means you must use that exact location for your Rockbox installation.  Other directories specified by the `rockbox_main.*` file are not supported; it must be empty or `/`.  It was done this way because most directories are hard-coded using preprocessor directives at build time in the current stable version of the code, so it would require an overhaul of the code to allow these directories to change dynamically at run time.

Here is basically how to perform the installation:

- If Rockbox stable v3.15 or newer is not already installed on the internal flash memory, install it.
    - With no microSD card inserted, connect the device over USB (and mount the internal storage, if using Linux).
    - Use Rockbox Utility to install Rockbox stable v3.15 as you normally would.
    - Safely remove USB and disconnect the device.  Turn it off and on again.
- Insert the microSD card into the device.
- Connect the device over USB (and mount if necessary).  It should show two drives: one for internal and one for the microSD card.
- Copy the `.rockbox` directory from the internal storage to the microSD card.  There should be a directory called `.rockbox` in the microSD card when you are done.
- Create an empty file called `rockbox_main.fuze`, `rockbox_main.fuze2`, or `rockbox_main.clip+` into the microSD card root directory, depending on your model of device.
- Unzip the contents of one of these builds (`sedimentary`, `igneous`, or `metamorphic`) into the microSD card.  Have it write into any matching directories and overwrite any matching files.
- Safely remove both USB drives and disconnect the device.  Turn it off and on again.
- If successful, the Rockbox screen should indicate the meyertime build variant (`sedimentary`, `igneous`, or `metamorphic`) as part of the version number while booting.
    - If you install your own build from this fork, the version will indicate the build date instead.

Then, to use the device going forward:

- Do not use the device without the microSD card inserted.  That microSD card is now just for that device.
- In Rockbox, you can set Settings -> General Settings -> System -> USB Hide Internal Drive to "Yes" if desired.  Then, when connecting the device to your computer, you will only see the microSD card and avoid accidentally using the internal flash memory.
- When you need to copy files to or from the microSD card, simply connect the device over USB to access the microSD card.
- If the microSD card wears out (because all flash memory eventually does), you can simply repeat the installation process for a new microSD card.

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