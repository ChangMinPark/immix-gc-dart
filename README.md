# Immix Garbage Collection in Dart
This repository contains all the files to be replaced to implement Immix GC in Dart. 
Follow the steps below to apply these files in Dart VM. 



Step 1: Cloning an Offical Dart SDK Repository
---
- Follow the building steps [here](https://github.com/dart-lang/sdk/wiki/Building). 
  - Possible errors
    - **_Ninja Error: loading 'build.ninja': No such file or directory_** -
    Before running **_./tools/build.py_**, run this
    ```sh
    $ gclient sync
    ```


Step 2: Cloning our ImmixInDart Repo 
---
- Go to runtime directory
```sh
$ cd (...)/sdk/runtime
```

- Clone and move to our repository
```sh
$ git clone https://github.com/ChangMinPark/ImmixInDart.git
$ cd ImmixInDart
```

- Add our directory to PATH (Optional). You can add this line to shell config file. It will make your life easier to run **_buildDart.sh_** script anywhere.  
```sh
$ export PATH="$PATH:$PWD"
```



Usage
---
- Please work on files under **_immix_** directory. Files under **_default_** directory are for reverting to default. 
- After modification, use build script. (Mode: default or immix)
```sh
$ buildDart.sh [Mode]
```



Extra
---
- [Observatory](https://dart-lang.github.io/observatory/)
  - Enable
    ```sh
    $ dart --enable-vm-service:8181/127.0.0.1 --observe --pause-isolates-on-start <dart script>.dart
    ```
  - Dart Observatory does not work on filefox. (I used **_Chromium_**)
    ```sh
    $ apt-get install chromium-browser
    ```
  - Open up Chromium, and go to **_https://127.0.0.1:8181_**
  - Enable an access to host's LocalHost (Link current client's LocalHost to host's LocalHost). Run this on client side.
    ```sh
    $ ssh -L 8181:127.0.0.1:8181 <server>
    ```
