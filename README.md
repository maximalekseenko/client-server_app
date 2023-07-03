Simple program for tracking user activity.



# Compiling
This code is compiled via [Cmake](https://cmake.org).

After compiling, [./build](./build/) directory will appear, containing two files: [server](./build/server) and [client](./build/client);

## Settings
Before compiling edit [settings.h](./src/settings.h), setting server ip address.

## Running
Example usage:
* run [server](./build/server) on first device;
* add new users by pressing `n` while in global menu:
    * type password and username;
    * switch between password and username by arrow keys;
    * confirm new user by pressing `enter` key;
    * cancel new user creation by double-pressing `escape` key;
* switch between users in global menu by arrow keys;
* delete extra users by pressing `n` while in global menu;
* run [client](./build/client) on second device;
* if runned first time: enter username and password;
* update [server](./build/server) by pressing any button;

## Requirements
C++20
sqlite3
ncurses.h

# Running

Running client with no server avaliable

## Controls
Server Application includes some user interface for interacting with database.

Common actions are:
* Double-tap `Esc` - Exit or cancel;
* `Enter` - Select;
* `Arrow` keys - Move cursor.



# Structure


## Client

> ### connection
> This module contains functions for connecting and talking to server.
>

> ### login
> This module contains functions for woking with config file, password and username.
>
> Also contains functions for password encoding.

## Server

> ### connection
> This module contains functions for connecting to clients.
>

> ### data
> This module contains functions for editing and accessing database.
>

> ### threading
> This module contains functions for handling client requests.
>

> ### window
> This module contains logic for user interface.
>
