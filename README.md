# RESTFUL API in C

Basic web server that allows incrementing a counter and viewing its status through two endpoints. Additionally, a client application is implemented to consume these endpoints.

### Authors:
- **Bottini, Franco Nicolas**

### How to compile?

To compile the project, once the repository is cloned, simply create the *Makefile* using the *CMake* script and run it:

```bash
$ git clone https://github.com/francobottini99/APIRESTC-2023.git
$ cd APIRESTC-2023
$ cmake .
$ make
```

The output will be two executables located in the `/bin` folder: `client` and `server`.

> [!NOTE]
> To compile the project, it is necessary to have the `Ulfius` framework installed on the system.

### Client

The `client` binary generates processes that consume the server's endpoints. There are two client options (depending on which endpoint you want to consume), which are:

- *CLIENT_INCREMENTER* (0)
- *CLIENT_PRINTER* (1)

Once a client is created, it sends its first request to the server within a pseudo-random delay of 0 to 3 seconds. After that, the requests are sent at pseudo-random intervals between 1 and 5 seconds. The client continues running indefinitely until the user terminates it or until the server process ends.

To create a client, the server must be running on the system, and the type of client and the server's IP address should be passed as input arguments to the binary:

```bash
$ ./bin/client 0 127.0.0.1 # Run an INCREMENTER client connecting to a server on localhost.
$ ./bin/client 1 127.0.0.1 # Run a PRINTER client connecting to a server on localhost.
```

As many client processes as needed can be executed.

`N` client processes of type *INCREMENTER* can be generated in the background using the script `create_incrementers.bash` located in the `/tests` directory. It takes the number of clients to create and the server's IP as input:

```bash
$ ./test/create_incrementers.sh 100 127.0.0.1 # Run 100 INCREMENTER clients in the background, connecting to a server on localhost.
```

To check the number of active clients (counting both *INCREMENTER* and *PRINTER* types) running on the system (in the foreground and background), the `active.bash` script can be used:

```bash
$ ./test/active.bash # Prints the number of active clients in the console
```

Additionally, to terminate all active clients (*INCREMENTER* and *PRINTER*) running in the foreground and background, the `clear.bash` script can be used:

```bash
$ ./test/clear.bash # Terminates all active client processes
```

These two scripts can also be found in the `/tests` directory.

### Server

The `server` binary runs the server process and creates the endpoints that will be consumed by the clients in the system.

To run the server, simply execute the binary:
```bash
$ ./bin/server # Launches the Server process
```
The process does not allow multiple executions, meaning there can only be one server running on the system at a time.

While the server is running, every time an *INCREMENTER* client sends a request to the server, it prints the current state of the counter, a timestamp, and the IP address of the client that sent the request.

### How it works

The server runs on port 8537 and creates a counter along with two endpoints that allow incrementing the counter and viewing its state, including the date and time of the last increment and the IP address of the client that performed it. The endpoints are: `/increment` and `/print`. The first one increments the counter by 1, and the second returns the current counter status along with information about its last increment.

Clients connect to the server through an *IPV4* socket and send *GET* and *POST* requests (as appropriate) to the server’s endpoints in an infinite loop until they are terminated.
