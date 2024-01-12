#include "server.h"

int callback_increment(const struct _u_request *request, struct _u_response *response, void *user_data)
{
    UNUSED(user_data);

    const char *host = u_map_get(request->map_header, "Host");

    if (host != NULL) 
    {
        strncpy(server_data.last_increment_by, host, sizeof(server_data.last_increment_by) - 1);
        server_data.last_increment_by[sizeof(server_data.last_increment_by) - 1] = '\0';

        time(&server_data.last_increment_timestamp);
    }

    server_data.counter++;
    
    printf(KCYN"Increment COUNTER:\n"KDEF);
    printf(KCYN"    Counter value: %d\n"KDEF, server_data.counter);
    printf(KCYN"    Incremented by: %s\n"KDEF, server_data.last_increment_by);
    printf(KCYN"    Timestamp: %s\n"KDEF, ctime(&server_data.last_increment_timestamp));

    ulfius_set_string_body_response(response, 200, "Increment success!");

    return U_CALLBACK_CONTINUE;
}

int callback_print(const struct _u_request *request, struct _u_response *response, void *user_data) 
{
    UNUSED(request);
    UNUSED(user_data);

    json_t *root = json_object();

    struct tm *local_time = localtime(&server_data.last_increment_timestamp);

    char timestamp[100];
    
    strftime(timestamp, sizeof(timestamp), "%a %b %d %H:%M:%S %Y", local_time);

    json_object_set_new(root, "counter", json_integer(server_data.counter));
    json_object_set_new(root, "last_incremented_by", json_string(server_data.last_increment_by));
    json_object_set_new(root, "last_incremented_timestamp", json_string(timestamp));

    char *json_response = json_dumps(root, JSON_INDENT(2));

    ulfius_set_string_body_response(response, 200, json_response);

    free(json_response);
    json_decref(root);

    return U_CALLBACK_CONTINUE;
}

int main(void) 
{
    struct _u_instance instance;

    if (ulfius_init_instance(&instance, SERVER_PORT, NULL, NULL) != U_OK) 
    {
        fprintf(stderr, KRED"Error initializing Ulfius instance\n"KDEF);
        return EXIT_FAILURE;
    }

    ulfius_add_endpoint_by_val(&instance, "POST", "/increment", NULL, 0, &callback_increment, NULL);
    ulfius_add_endpoint_by_val(&instance, "GET", "/print", NULL, 0, &callback_print, NULL);

    server_data.counter = 0;
    strcpy(server_data.last_increment_by, "None");
    time(&server_data.last_increment_timestamp);

    if (ulfius_start_framework(&instance) == U_OK) 
    {
        printf(KBLU"Ulfius server started on port %d\n\n"KDEF, instance.port);
        getchar();
    }
    else
        fprintf(stderr, KRED"Error starting Ulfius framework\n"KDEF);

    ulfius_stop_framework(&instance);
    ulfius_clean_instance(&instance);

    return 0;
}