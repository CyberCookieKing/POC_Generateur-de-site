/******************************************************************************/
/*                                                                            */
/*                       Générateur de site web en C                          */
/*                         Auteur: CyberCookieKing                            */
/*                                                                            */
/* But :                                                                      */
/*   Crée un générateur de site web simple en utilisant la bibliothèque       */
/*   libmicrohttpd. Le site généré affiche "Hello @name!!" où @name est       */
/*   substituté par une autre variable.                                       */
/*                                                                            */
/* Installation :                                                             */
/*   apt install libmicrohttpd-dev                                            */
/*                                                                            */
/* Compilation :                                                              */
/*   gcc -o webGenerator webGenerator.c -lmicrohttpd                          */
/*                                                                            */
/* Utilisation :                                                              */
/*   - Lancer l'exécutable 'webGenerator'                                     */
/*   - Le site sera disponible sur le port 8080                               */
/*   - Ouvrez un navigateur et accédez à l'URL http://localhost:8080/         */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

int request_handler(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method, const char *version,
                    const char *upload_data, size_t *upload_data_size, void **con_cls)
{
    const char *name = "World";  // Variable contenant le nom à substituer
    const char *response_template = "<html><body><h1>Hello @name!!</h1></body></html>";
    char *response;
    struct MHD_Response *http_response;
    int ret;

    size_t response_size = strlen(response_template) + strlen(name) - strlen("@name") + 1;
    response = malloc(response_size);
    if (response == NULL) {
        return MHD_NO;
    }

    const char *placeholder = "@name";
    const char *placeholder_position = strstr(response_template, placeholder);
    if (placeholder_position != NULL) {
        size_t placeholder_length = strlen(placeholder);
        size_t prefix_length = placeholder_position - response_template;
        size_t suffix_length = strlen(placeholder_position + placeholder_length);

        strncpy(response, response_template, prefix_length);
        response[prefix_length] = '\0';
        strcat(response, name);
        strcat(response, response_template + prefix_length + placeholder_length);
    } else {
        strcpy(response, response_template);
    }

    http_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, http_response);
    MHD_destroy_response(http_response);

    return ret;
}

int main()
{
    struct MHD_Daemon *daemon;

    MHD_AccessHandlerCallback request_callback = (MHD_AccessHandlerCallback)&request_handler;
    daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, 8080, NULL, NULL, request_callback, NULL, MHD_OPTION_END);
    if (daemon == NULL)
    {
        printf("Erreur lors du démarrage du serveur.\n");
        return 1;
    }
    printf("Serveur en cours d'exécution sur le port 8080...\n");

    getchar();  // Attendre une entrée de l'utilisateur pour arrêter le serveur

    MHD_stop_daemon(daemon);

    return 0;
}
