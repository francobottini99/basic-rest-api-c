#include "client.h"

void signal_handler(int sig, siginfo_t *info, void* context)
{
    UNUSED(info);
    UNUSED(context);

    if(sig == SIGTERM || sig == SIGINT || sig == SIGHUP || sig == SIGPIPE)
        end();
}

void signal_handler_init(void)
{
    struct sigaction sa = 
    {
        .sa_sigaction = signal_handler,
        .sa_flags = SA_SIGINFO
    };
    sigemptyset(&sa.sa_mask);
    
	sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGHUP, &sa, NULL);
    sigaction(SIGPIPE, &sa, NULL);
}

void set_request_increment(const char* server_ip, char* buffer)
{
    sprintf(buffer, "POST /increment HTTP/1.1\r\n");
    sprintf(buffer + strlen(buffer), "Host: %s\r\n", server_ip);
    sprintf(buffer + strlen(buffer), "Content-Length: 0\r\n");
    sprintf(buffer + strlen(buffer), "\r\n");
}

void set_request_print(const char* server_ip, char* buffer)
{
    sprintf(buffer, "GET /print HTTP/1.1\r\n");
    sprintf(buffer + strlen(buffer), "Host: %s\r\n", server_ip);
    sprintf(buffer + strlen(buffer), "\r\n");
}

void do_work(const char* request)
{
    char response[BUFFER_SIZE];

    sleep((unsigned int)(rand() % 3));

    while (1)
	{
        if (send(client.socket_fd, request, strlen(request), 0) < 0)
            fprintf(stderr, KRED"\nFail send request to the server\n"KDEF);
        else
        {
            memset(response, 0, BUFFER_SIZE);
            
            if(recv(client.socket_fd, response, BUFFER_SIZE - 1, 0) > 0)
                if(client.type == CLIENT_PRINTER)
                    printf(KGRN"%s"KDEF, strstr(response, "\r\n\r\n"));
        }

		sleep((unsigned int)(rand() % 5 + 1));
	}
}

int connect_ipv4_sockect(const char *socket_ipv4, const uint16_t socket_port)
{
    struct sockaddr_in server_address;

    client.socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (client.socket_fd < 0)
    {
        perror("socket() failed");
        return -1;
    } 

    memset(&server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(socket_port);

    if (inet_pton(AF_INET, socket_ipv4, &server_address.sin_addr) <= 0) 
    {
        perror("socket() failed");
        return -1;
    }

    if (connect(client.socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) 
    {
        perror("connect() failed");
        return -1;
    }

    return 0;
}

void end(void) 
{
    printf(KRED"\n\nClient end !\n"KDEF);

    close(client.socket_fd);

    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, KRED"\nBad number of arguments !\n"KDEF);
        exit(EXIT_FAILURE);
    }

    int cli_type = atoi(argv[1]);

	if((*argv[1] != '0' && cli_type == 0) || cli_type < 0 || cli_type > 1)
	{
		fprintf(stderr, KRED"Bad argument client type!"KDEF);
		exit(EXIT_FAILURE);
	}

    if (connect_ipv4_sockect(argv[2], SERVER_PORT) < 0)
    {
        fprintf(stderr, KRED"\nConnection to server failed\n"KDEF);
        exit(EXIT_FAILURE);
    }
    
    signal_handler_init();

    char request[BUFFER_SIZE];

    switch ((client_type)cli_type)
    {
    case CLIENT_INCREMENTER:
        set_request_increment(argv[2], request);
        break;
    
    case CLIENT_PRINTER:
        set_request_print(argv[2], request);
        break;

    default:
        break;
    }

    client.type = (client_type)cli_type;

    do_work(request);

    end();

    return EXIT_SUCCESS;
}