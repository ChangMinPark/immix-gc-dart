# ImmixInDart
This repository contains all the files to be replaced to implement Immix GC in Dart. 
Follow the steps below to apply these files in Dart VM. 



Step 1: Cloning an Offical Dart SDK Repository
---
- Clone [Official Dart SDK](https://github.com/dart-lang/sdk).
- Follow the building steps [here](https://github.com/dart-lang/sdk/wiki/Building). 



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



