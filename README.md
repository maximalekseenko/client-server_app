Simple program for 


# Compiling
This code is compiles via Cmake.

After compiling [./build](./build/) directory will appear. 

There will be two files: [server](./build/server) and [client](./build/client);


# Controls
Server Application includes user interface for interacting with database.

Common actions are:
* Double-tap `Esc` - Exit or cancel;
* `Enter` - Select;
* `Arrow` keys - Move cursor.

# Req
C++20
sqlite3
ncurses.h


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
