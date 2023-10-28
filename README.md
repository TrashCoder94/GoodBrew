# GoodBrew

[![Build](https://github.com/TrashCoder94/GoodBrew/actions/workflows/build.yml/badge.svg)](https://github.com/TrashCoder94/GoodBrew/actions/workflows/build.yml)
[![Test](https://github.com/TrashCoder94/GoodBrew/actions/workflows/test.yml/badge.svg)](https://github.com/TrashCoder94/GoodBrew/actions/workflows/test.yml)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/1640b63da8a1499a8ab98a72cb31c560)](https://www.codacy.com/gh/TrashCoder94/GoodBrew/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=TrashCoder94/GoodBrew&amp;utm_campaign=Badge_Grade)

## Prerequisites

### Windows
This is for the CommitChecker, on Windows, this uses the WSL to compile local changes in a Linux environment.
1. Download the Windows Subsystem for Linux from the Microsoft Store: https://www.microsoft.com/store/productid/9P9TQF7MRM4R?ocid=pdpshare
2. Follow the instructions here to install the system and a distribution: https://learn.microsoft.com/en-us/windows/wsl/installs

### Linux
```
sudo apt-get update && sudo apt-get install xorg-dev libxrandr-dev libxcursor-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libdrm-dev libgbm-dev xvfb fluxbox
sudo apt-get install libsfml-dev
```

## How To Setup

1.	Clone using your source control provider (I use GitHub Desktop for example :octocat:).
2.	Go to `/GoodBrew/Scripts/` and run the `GenerateProjectFiles` script for your os.
3.	Premake should have generated `GB.sln` (or platform equivalent) in your root folder. You should have code access now!
