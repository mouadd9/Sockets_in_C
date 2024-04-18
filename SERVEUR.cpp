#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <string.h>
#include <locale.h>

//---------------------------------------------------------- les structures utilisee ---------------------------------------------------------------------------------

typedef struct
{
    char login[50];
    char Mot_de_passe[50];
    char type[50];
} compte;

int main()
{
    setlocale(LC_ALL, "fr_FR.UTF-8");

    char server_message[256] = "vous avez  ete  connecte  au serveur avec succes";
    // cr ation du server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    // definir une adresse pour socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind socket to our specified IP address
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    listen(server_socket, 6); // 6 combien des sockets seront connect s a celui l

    int client_socket = accept(server_socket, NULL, NULL);

    // envoi des donnes
    send(client_socket, server_message, sizeof(server_message), 0);

    int test = 0, result = 0;
    char mdp[30];
    char nom[50];

    FILE *f = fopen("comptes.txt", "r");
    if (f == NULL)
    {
        printf("erreur lors de l,ouverture de  fichier comptes.txt \n");
        exit(1);
    }
    else
    {
        printf("verification d'identite : \n ");
       
        recv(client_socket, nom, sizeof(nom), 0);
        printf("%s \n ", nom);
        while (!feof(f))
        {
            fscanf(f, "%s%s%s", C.login, C.Mot_de_passe, C.type);
            if (strcmp(nom, C.login) == 0)
            {
                while (test <= 3)
                {
                    
                    recv(client_socket, mdp, sizeof(mdp), 0);
                    printf("%s \n ", mdp);
                    if (strcmp(mdp, C.Mot_de_passe) == 0)
                    {
                        if (strcmp(C.type, "admin") == 0)
                        {
                            result = 1;
                            send(client_socket, &result, sizeof(result), 0);
                            break;
                        }
                        else if (strcmp(C.type, "invite") == 0)
                        {
                            result = 2;
                            send(client_socket, &result, sizeof(result), 0);
                            break;
                        }
                    }
                    result = 0;
                    send(client_socket, &result, sizeof(result), 0);
                    test++;
                }
            }
            else
            {
                result = -1;
            }
        }
        send(client_socket, &result, sizeof(result), 0);
    }

    close(server_socket);
    return 0;
}
