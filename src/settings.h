#pragma once

/// server address
#define ADDRESS "0.0.0.0"
/// server port
#define PORT 8989
///
#define BUFFSIZE 1024
/// last application version
#define APPVERSION 0

/// encryption number
#define ENCNUM 4793968276703868376938

#define CHARSIZE 256

// client sided variables
#ifdef APPCLIENT
#endif //APPCLIENT


// server sided variables
#ifdef APPSERVER
    #define CLIENTSLIMIT 16
#endif //APPSERVER