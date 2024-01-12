# API RESTFUL en C

Servidor web básico que permite incrementar un contador y ver su estado a través de dos *end points*. Ademas, se implementa una aplicación cliente consume dichos *end points*.

### Autores:
- **Bottini, Franco Nicolas**

### ¿ Como compilar ?

Para compilar el proyecto, una vez clonado el repositorio, basta con crear el *Makefile* utilizando el script *CMake* y ejecutarlo:

```bash
$ git clone https://github.com/francobottini99/APIRESTC-2023.git
$ cd APIRESTC-2023
$ cmake .
$ make
```

Como salida obtendremos dos ejecutables ubicados en la carpeta `/bin`: `client` y `server`.

> [!NOTE]
> Para compilar el proyecto es necesario tener instalado el *framework* `Ulfius` en el equipo.

### Cliente

Con el binario `client` se generan los procesos que consumen los *end points* del servidor, existen dos opciones de clientes (según que *end point* se desee consumir), estos son:

- *CLIENT_INCREMENTER* (0)
- *CLIENT_PRINTER* (1)

Una vez creado un cliente, este enviara la primera solicitud al servidor en un plazo pseudoaleatorio de 0 a 3 segundos, luego de esto, el envió de solicitudes se repite en intervalos pseudoaleatorios de entre 1 y 5 segundos. El cliente continua su ejecución indefinidamente hasta que es finalizado por el usuario, o en su defecto, hasta que finaliza la ejecución del servidor.

Para crear un cliente es necesario que el servidor este en ejecución en el equipo y se debe dar como argumento de entrada al binario el tipo de cliente a creer y la ip del servidor al cual se va a conectar el nuevo cliente:

```bash
$ ./bin/client 0 127.0.0.1 # Ejecuta un cliente INCREMENTER que se conecta a un servidor en el localhost.
$ ./bin/client 1 127.0.0.1 # Ejecuta un cliente PRINTER que se conecta a un servidor en el localhost.
```

Se pueden ejecutar tantos procesos cliente como se desee.

Se pueden generar `N` procesos clientes del tipo *INCREMENTER* en segundo plano utilizando el script `create_incrementers.bash` ubicado en el directorio `/tests`. Este recibe como argumento de entrada el numero de clientes a crear y la ip del servidor al cual se conectan:

```bash
$ ./test/create_incrementers.sh 100 127.0.0.1 # Ejecuta 100 clientes INCREMENTER en segundo plano que se conectan a un servidor en el localhost.
```

Para conocer el numero de clientes activos (cuenta tanto los de tipo *INCREMENTER* como los de tipo *PRINTER*) corriendo en el sistema (en primer y segundo plano), se puede utilizar el script `active.bash`:

```bash
$ ./test/active.bash # Imprime en consola el numero de clientes activos
```

Por otra parte, para finalizar la ejecución de todos los clientes activos (*INCREMENTER* y *PRINTER*) en primer y segundo plano, se puede utilizar el script `clear.bash`:

```bash
$ ./test/clear.bash # Finaliza la ejecucion de todos los clientes activos
```

Estos dos scripts tambien se encuentran el directorio `/tests`.

### Servidor

El binario `Server` ejecuta el proceso servidor y crea los *end points* que van a consumir los clientes del sistema.

Para ejecutar el servidor basta con ejecutar el binario: 
```bash
$ ./bin/server # Lanza el proceso Servidor
```
El proceso no admite múltiples ejecuciones, es decir, no puede haber mas de un servidor corriendo en el equipo al mismo tiempo.

Mientras el servidor esta en ejecución, cada vez que un cliente *INCREMENTER* envía una solicitud al servidor, imprime por consola el estado actual del contador, un *timestamp* y la *IP* del cliente que envió la solicitud.

### Lógica de Funcionamiento

El servidor se ejecuta sobre el puerto 8537 y se encarga de crear un contador y dos *end points* que permiten incrementar el contador y ver su estado junto con la fecha y hora del ultimo incremento y la *IP* del cliente que lo realizo. Los *end points* son: `/increment` y `/print`. El primero incrementa el contador en 1 y el segundo retorna el estado actual del contador junto con la información de su ultimo incremento. 

Los clientes se conectan a este a través de un sockect *IPV4* y envían solicitudes *GET* y *POST* (según corresponda) a los *end points* del servidor en un bucle infinito hasta su finalización. 