#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <locale.h>

int main()
{

    int network_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if (connection_status == -1)
    {
        printf("Echec de connexion \n\n");
    }

    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);
    printf("le serveur a envoyer : %s \n", server_response);

    char user[100];
    char mdp[30];
    int n = 0;
    int result = 0;

    printf("\n\n************************************* BIENVENUE ******************************************\n\n");
    printf("RQ : vous avez le droit d'enter comme -Admin ou -Invite seulement \n");
    printf("S'il vous plait entrer votre login:\n ");
    scanf("%s", user);

    send(network_socket, user, strlen(user), 0);

    do
    {
        printf("s'il vous plait entrer votre password (vouz avez %d essai!) : ", 3 - n);
        scanf("%s", mdp);

        send(network_socket, mdp, strlen(mdp), 0);
        recv(network_socket, &result, sizeof(result), 0);

        n++;
    } while (result == 0 && n < 3);
    
    
    
    if (result == 1)
    {
        printf("-----------------Vous etes administrateur -----------------\n\n");      
    }

    else if (result == 2)
    {
        printf("--------------VOUS ETES UTULISATEUR ----------------------\n");
    }
    else
    {
        printf(" mode non specifie \n ");
        exit(1);
    }
    close(network_socket);
    return 0;
}
