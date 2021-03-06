# FollowThroughWebDevelopmentWithReasonML
Just preserving code written while following through WebDevelopmentWithReasonML by J. David Eisenberg

Obs: by the time I started to read this book, ReasonML and BuckleScript were already rebranded as ReScript.
So, there we some differences in the tools, dependencies and code.

## Preparation

```
takeshi:FollowThroughWebDevelopmentWithReasonML$ node -v
v12.19.0

takeshi:FollowThroughWebDevelopmentWithReasonML$ npm install -g bs-platform

changed 1 package, and audited 2 packages in 2s

found 0 vulnerabilities
```

## Creating a project from the book

```
takeshi:FollowThroughWebDevelopmentWithReasonML$ bsb -init shirts -theme basic-reason
Making directory shirts

takeshi:FollowThroughWebDevelopmentWithReasonML$ tree -a shirts/ 
shirts/
├── bsconfig.json
├── .gitignore
├── package.json
├── README.md
└── src
    └── Demo.re

1 directory, 5 files
```
## Building a project
```
takeshi:FollowThroughWebDevelopmentWithReasonML$ cd shirts/

takeshi:shirts$ cat src/Demo.re 
Js.log("Hello, ReScript!");

takeshi:shirts$ npm run build

> shirts@0.1.0 build
> bsb -make-world

Dependency Finished
bsb: [4/4] src/Demo-Shirts.cmj
takeshi:shirts$ 

```

The above created src/Demo.bs.js that can be execute by node:
```

takeshi:shirts$ cat src/Demo.bs.js 
// Generated by ReScript, PLEASE EDIT WITH CARE
'use strict';


console.log("Hello, ReScript!");

/*  Not a pure module */

takeshi:shirts$ node src/Demo.bs.js 
Hello, ReScript!
```

## Adding bundler (parcel) to generate javascript bundle and provide HMR (Hot Module Reload) for a web app project
```
takeshi:shirts$ npm install --save-dev parcel
```

## Preparing a web app 
```
takeshi:shirts$ rm src/Deme.re # removed demo file

takeshi:shirts$ npm install --save rescript-webapi # added rescript-webapi

takeshi:shirts$ vim bsconfig.json # added rescript-webapi to bs-dependencies

takeshi:shirts$ vim src/index.html # copied from the book

takeshi:shirts$ vim src/WebShirts.re # written following the book

```
## Building the web app

First we build (transpile *.re scripts to *.bs.js scripts)
```
takeshi:shirts$ npm run build

> shirts@0.1.0 build
> bsb -make-world

Dependency on rescript-webapi
bsb: [352/352] src/Webapi.cmj
bsb: [467/467] install.stamp
Dependency Finished
bsb: [1/1] src/WebShirts-Shirts.cmj

  Warning number 52
  /mnt/ssd/work/src/git/MayamaTakeshi/FollowThroughWebDevelopmentWithReasonML/shirts/src/WebShirts.re:55:25-39
  
  53 │   switch (int_of_string(s)) {
  54 │     | result => Some(result)
  55 │     | exception(Failure("int_of_string")) => None
  56 │   }
  57 │ };
  
  Code should not depend on the actual values of
this constructor's arguments. They are only for information
and may change in future versions. (See manual section 8.5)

```
Obs: ignore the above Warning for now.

We can automatically rebuild files by running bsb in watch mode:
```
takeshi:shirts$ npm run start

> shirts@0.1.0 start
> bsb -make-world -w

Dependency on rescript-webapi
Dependency Finished
>>>> Start compiling 
bsb: [1/1] src/WebShirts-Shirts.cmj

  Warning number 52
  /mnt/ssd/work/src/git/MayamaTakeshi/FollowThroughWebDevelopmentWithReasonML/shirts/src/WebShirts.re:55:25-39
  
  53 │   switch (int_of_string(s)) {
  54 │     | result => Some(result)
  55 │     | exception(Failure("int_of_string")) => None
  56 │   }
  57 │ };
  
  Code should not depend on the actual values of
this constructor's arguments. They are only for information
and may change in future versions. (See manual section 8.5)
  
>>>> Finish compiling 46 mseconds

```

Then generate the javascript bundle:
``` 
takeshi:shirts$ npx parcel build src/index.html --public-url ./
✨ Built in 1.68s

dist/index.html              677 B    300ms
dist/index.7bf4b1eb.js    18.47 KB    959ms
takeshi:shirts$ 
```
## Run parcel to serve the app and monitor for changes in files
```
takeshi:shirts$ npx parcel src/index.html
Server running at http://localhost:1234
✨ Built in 539ms
```
## Test the app

Open http://localhost:1234 in the browser and confirm HMR is working by doing some changes in src/WebShirts.re

The changes will be detected by 'bsb -make-world -w' that will generate src/WebShirts.bs.js. 

Then since this file is referenced by index.html which is watched by parcel, it will cause parcel to rebundle the artifacts and send to the client code in the browser via WebSocket.

So up to this point we learned how to write web apps with ReScript. 

However, rescript-webapi is very low level and instead we should use RescriptReact.

## Generating module interface file

Chapter 7 teaches to do this using this example:
```
bsc -bs-re-out lib/bs/src/Shirts-ModShirts.cmi > src/Shirts.rei
```

