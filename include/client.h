#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "common.h"

/**
 * @brief Client types
 * 
 */
typedef enum
{
    CLIENT_INCREMENTER, // Client incrementer
    CLIENT_PRINTER,     // Client printer
} client_type;


/**
 * @brief Client representation data
 * 
 */
struct 
{
    int socket_fd;      // Socket file descriptor
    client_type type;   // Client type
} client;

// Buffer size for request and response
#define BUFFER_SIZE 512

/**
 * @brief Signal handler
 * 
 * @param sig Signal number
 * @param info Signal info
 * @param context Context
 */
void signal_handler(int sig, siginfo_t *info, void* context);

/**
 * @brief Initialize signal handler
 * 
 */
void signal_handler_init(void);

/**
 * @brief Set request increment to bufferc
 * 
 * @param server_ip Server ip
 * @param buffer Buffer to store request
*/
void set_request_increment(const char* server_ip, char* buffer);

/**
 * @brief Set request print to buffer
 * 
 * @param server_ip Server ip
 * @param buffer Buffer to store request
*/
void set_request_print(const char* server_ip, char* buffer);

/**
 * @brief Do work with server (send request and receive response) while client is not terminated
 * 
 * @param request Request to send
*/
void do_work(const char* request);

/**
 * @brief Connect to IPV4 socket
 * 
 * @param socket_ipv4 Socket ipv4
 * @param socket_port Socket port
 * @return error_code Error code
*/
int connect_ipv4_sockect(const char *socket_ipv4, const uint16_t socket_port);

/**
 * @brief End client
 * 
 */
void end(void);

#endif //__CLIENT_H__