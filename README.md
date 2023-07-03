Simple program for tracking user activity.



# Compiling
This code is compiled via [Cmake](https://cmake.org).

## Settings
Before compiling edit [settings.h](./src/settings.h), setting server ip address.

## Results
After compiling, [./build](./build/) directory will appear, containing two files: [server](./build/server) and [client](./build/client);

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
