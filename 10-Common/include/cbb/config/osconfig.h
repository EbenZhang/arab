#ifndef _OS_CONFIG_H_
#define _OS_CONFIG_H_

#ifdef WIN32
#include <winsock2.h>
#include <stdlib.h>
#include <io.h>
#include <time.h>
#else

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h> 
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <net/if.h>

#endif



#ifdef __MACH__
typedef int socklen_t;
#endif

#include <errno.h>

#ifdef WIN32

#include <winsock2.h>
#include <io.h>

typedef int socklen_t;
typedef SOCKET Socket;

#ifndef EWOULDBLOCK            
#define EWOULDBLOCK             WSAEWOULDBLOCK
#endif
#ifndef EINPROGRESS            
#define EINPROGRESS             WSAEINPROGRESS
#endif
#ifndef EALREADY               
#define EALREADY                WSAEALREADY
#endif
#ifndef ENOTSOCK               
#define ENOTSOCK                WSAENOTSOCK
#endif
#ifndef EDESTADDRREQ           
#define EDESTADDRREQ            WSAEDESTADDRREQ
#endif
#ifndef EMSGSIZE               
#define EMSGSIZE                WSAEMSGSIZE
#endif
#ifndef EPROTOTYPE             
#define EPROTOTYPE              WSAEPROTOTYPE
#endif
#ifndef ENOPROTOOPT            
#define ENOPROTOOPT             WSAENOPROTOOPT
#endif
#ifndef EPROTONOSUPPORT        
#define EPROTONOSUPPORT         WSAEPROTONOSUPPORT
#endif
#ifndef ESOCKTNOSUPPORT        
#define ESOCKTNOSUPPORT         WSAESOCKTNOSUPPORT
#endif
#ifndef EOPNOTSUPP             
#define EOPNOTSUPP              WSAEOPNOTSUPP
#endif
#ifndef EPFNOSUPPORT           
#define EPFNOSUPPORT            WSAEPFNOSUPPORT
#endif
#ifndef EAFNOSUPPORT           
#define EAFNOSUPPORT            WSAEAFNOSUPPORT
#endif
#ifndef EADDRINUSE             
#define EADDRINUSE              WSAEADDRINUSE
#endif
#ifndef EADDRNOTAVAIL          
#define EADDRNOTAVAIL           WSAEADDRNOTAVAIL
#endif
#ifndef ENETDOWN               
#define ENETDOWN                WSAENETDOWN
#endif
#ifndef ENETUNREACH            
#define ENETUNREACH             WSAENETUNREACH
#endif
#ifndef ENETRESET              
#define ENETRESET               WSAENETRESET
#endif
#ifndef ECONNABORTED           
#define ECONNABORTED            WSAECONNABORTED
#endif
#ifndef ECONNRESET             
#define ECONNRESET              WSAECONNRESET
#endif
#ifndef ENOBUFS                
#define ENOBUFS                 WSAENOBUFS
#endif
#ifndef EISCONN                
#define EISCONN                 WSAEISCONN
#endif
#ifndef ENOTCONN               
#define ENOTCONN                WSAENOTCONN
#endif
#ifndef ESHUTDOWN              
#define ESHUTDOWN               WSAESHUTDOWN
#endif
#ifndef ETOOMANYREFS           
#define ETOOMANYREFS            WSAETOOMANYREFS
#endif
#ifndef ETIMEDOUT              
#define ETIMEDOUT               WSAETIMEDOUT
#endif
#ifndef ECONNREFUSED           
#define ECONNREFUSED            WSAECONNREFUSED
#endif
#ifndef ELOOP                  
#define ELOOP                   WSAELOOP
#endif
#ifndef EHOSTDOWN              
#define EHOSTDOWN               WSAEHOSTDOWN
#endif
#ifndef EHOSTUNREACH           
#define EHOSTUNREACH            WSAEHOSTUNREACH
#endif
#ifndef EPROCLIM               
#define EPROCLIM                WSAEPROCLIM
#endif
#ifndef EUSERS                 
#define EUSERS                  WSAEUSERS
#endif
#ifndef EDQUOT                 
#define EDQUOT                  WSAEDQUOT
#endif
#ifndef ESTALE                 
#define ESTALE                  WSAESTALE
#endif
#ifndef EREMOTE                
#define EREMOTE                 WSAEREMOTE
#endif

typedef LONGLONG Int64; 
inline int getErrno() { return WSAGetLastError(); }

typedef char BufType;

#else
typedef int Socket;
static const Socket INVALID_SOCKET = -1;
static const int SOCKET_ERROR = -1;

inline int closesocket( Socket fd ) { return close(fd); };

inline int getErrno() { return errno; }

typedef unsigned char BufType;

#ifndef WSANOTINITIALISED 
#define WSANOTINITIALISED  EPROTONOSUPPORT
#endif

#endif



#ifdef _WIN32
/*
 * Structure defined by POSIX.1b to be like a timeval.
 */
struct timespec {
	time_t	tv_sec;		/* seconds */
	long	tv_nsec;	/* and nanoseconds */
};

#define snprintf _snprintf
#endif


#endif

//end of file


