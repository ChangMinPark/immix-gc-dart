# ImmixInDart
This repository contains all the files to be replaced to implement Immix GC in Dart. 
Follow the steps below to apply these files in Dart VM. 


Step 1: Cloning Dart VM Repository
---
- Clone this [DartVM repository](https://github.com/dart-lang/sdk).
- Follow the building steps [here](https://github.com/dart-lang/sdk/wiki/Building). 


Step 2: Cloning our ImmixInDart 
---
- Go to runtime directory
```sh
$ (...)/sdk/runtime
```

- Clone our repository
```sh
$ git clone https://github.com/ChangMinPark/ImmixInDart.git
```

- Add our directory to PATH (Optional). You can add this line to shell config file. It will make your life easier to run **_buildDart.sh_** script anywhere.  
```sh
$ export PATH="$PATH:$PWD"
```

Usage
---
- Please work on files under Immix. 
- After modification, use build script. (Mode: default or immix)
```sh
$ buildDart.sh [Mode]
```



