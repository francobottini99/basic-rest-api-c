#ifndef __SERVER_H__
#define __SERVER_H__

#include <ulfius.h>
#include <jansson.h>

#include "common.h"

// Server data storage structure
struct
{
    unsigned int counter;            // Counter value
    char last_increment_by[100];     // Last increment by host
    time_t last_increment_timestamp; // Last increment timestamp (UTC)
} server_data;

/**
 * @brief End point to incrementing the counter value
 * 
 * @param request HTTP request
 * @param response HTTP response
 * @param user_data User data (unused)
*/
int callback_increment(const struct _u_request *request, struct _u_response *response, void *user_data);

/**
 * @brief End point to print the counter value and last increment information
 * 
 * @param request HTTP request (unused)
 * @param response HTTP response
 * @param user_data User data (unused)
*/
int callback_print(const struct _u_request *request, struct _u_response *response, void *user_data);

#endif // __SERVER_H__