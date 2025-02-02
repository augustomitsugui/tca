#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// data
typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

// hora
typedef struct
{
    int hora;
    int minuto;
} Hora;

// endereço
typedef struct
{
    char *logradouro;
    int numero;
    char *bairro;
    char *cidade;
    char *estado;
} Endereco;

// local de encontro
typedef struct
{
    char *nomelocal;
    Endereco endereco;
} Local;

// categoria de encontro

typedef struct
{
    char *nome;
} Categoria;

// amigo
typedef struct
{
    char *nome;
    Data nascimento;
    char *apelido;
    char *email;
    char *telefone;
} Amigo;

//  encontro
typedef struct
{
    Data data;
    Hora hora;
    char **amigosencontro;
    char *categoriaencontro;
    char *localencontro;
    char *descricao;
    char *nomeencontro;
    int numamigosencontro;

} Encontro;

// variaveisL globais

Local *locais;
int numlocais = 0;

Categoria *categorias;
int numcategorias = 0;

Encontro *encontros;
int numencontros = 0;

Amigo *amigos;
int numamigos = 0;

// funcoes encontro
void recuperaencontros();
void limpaencontros();
void salvaencontros();
int excluirencontro();
int alterarencontro();
void relatorioporcat();
void listarencontro();
void listartodosencontros();
void imprimeencontro();
void escolherencontroesp();
void listaNomeAmigos();
void listaNomeLocal();
int cadastrarencontro();
// funções categoria

int excluircategoria();
int alterarcategoria();
int cadastrarcategoria();
void recuperacategoria();
void limpacategoria();
void salvacategoria();
void listarcategoria();

void imprimecategoria();
void escolhercategoriaesp();

// funcoes local
int alterarlocal();
int cadastrarlocal();
int excluirlocal();
void recuperalocal();
void limpalocal();
void salvalocal();
void listarlocal();
void listatodoslocais();
void imprimelocal();
void escolherlocalesp();

// funcoes amigo
void listaramigo();
int cadastraramigo();
int excluiramigo();
int alteraramigo();
void recuperaamigo();
void limpaamigo();
void salvaamigo();
void listatodosamigos();
void imprimeAmigo(int amigo);
void escolherAmigoEsp();

// funcoes aux
int validarhora();
void flushs();
void limpaTela();
int validardatanas();
void recuperadado();
void limpadado();
void salvadado();
int validardataenc();

// funcoes menu
void menu_relatorio();
void menu_encontro();
void menu_amigo();
void menu_local();
void menu_categoria();
int menuprincipal();

int menuprincipal()
{

    int opcao = 0;

    while (opcao <= 0 || opcao > 6)
    {
        limpaTela();
        printf("1 - manter amigo\n");
        printf("2 - manter local \n");
        printf("3 - manter categoria\n");
        printf("4 - manter encontro\n");
        printf("5 - relatórios\n");
        printf("6 - sair\n");
        printf("escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            menu_amigo();
            break;

        case 2:
            menu_local();
            break;
        case 3:
            menu_categoria();
            break;
        case 4:
            menu_encontro();
            break;

        case 5:
            menu_relatorio();
            break;
        case 6:
            return -1;
        default:

            printf("opção inválida! tente novamente\n\n");
            system("pause");
            limpaTela();
            break;
        }
    }
    return 0;
}
void menu_local()
{
    int opcao = 0;
    // bota um while também igual vc fez com o menu_amigo
    limpaTela();
    printf("1 - cadastrar local\n");
    printf("2 - alterar local\n");
    printf("3 - excluir local\n");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        cadastrarlocal();
        break;
    case 2:
        alterarlocal();
        break;
    case 3:
        excluirlocal();
        break;
    default:
    {
        printf("opção inválida! tente novamente");
        system("pause");
        limpaTela();
        menu_local();
    }
    }
}
void menu_categoria()
{
    int opcao = 0;
    // bota while igual em menu_amigo

    limpaTela();
    printf("1 - cadastrar categoria\n");
    printf("2 - alterar categoria\n");
    printf("3 - excluir categoria\n");
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        cadastrarcategoria();
        break;
    case 2:
        alterarcategoria();
        break;
    case 3:
        excluircategoria();
        break;
    default:
    {
        printf("opção inválida! tente novamente");
        system("pause");
        limpaTela();
        menu_local();
    }
    }
}
void menu_amigo()
{
    int opcao = 0;
    while (opcao < 1 || opcao > 3)
    {
        limpaTela();
        printf("1 - cadastrar amigo\n");
        printf("2 - alterar amigo\n");
        printf("3 - excluir amigo\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            cadastraramigo();
            break;
        case 2:
            alteraramigo();
            break;
        case 3:
            excluiramigo();
            break;
        default:
        {
            printf("opção inválida! tente novamente");
            system("pause");
            limpaTela();
            menu_amigo();
        }
        }
    }
}
void menu_encontro()
{
    int opcao = 0;

    // faz um while igual vc fez na dos amigos :) - dica do augusto, 06/12/24

    while (opcao < 1 || opcao > 3)
    {
        limpaTela();
        printf("1 - cadastrar encontro\n");
        printf("2 - alterar encontro\n");
        printf("3 - excluir encontro\n");
        scanf("%d", &opcao);
        switch (opcao)
        {

        case 1:
            cadastrarencontro();
            break;
        case 2:
            alterarencontro();
            break;
        case 3:
            excluirencontro();
            break;
        default:
        {
            printf("opção inválida! tente novamente");
            system("pause");
            limpaTela();
            menu_encontro();
        }
        }
    }
}
void menu_relatorio()
{

    int opcao = 0;
    while (opcao < 1 || opcao > 6)
    {
        limpaTela();
        printf("1 - listar amigos\n");
        printf("2 - listar locais\n");
        printf("3 - listar categorias\n");
        printf("4 - listar encontros\n");
        printf("5 - relatório por categoria\n");
        printf("6 - voltar\n");

        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            listaramigo();
            break;
        case 2:
            listarlocal();
            break;
        case 3:
            listarcategoria();
            break;
        case 4:
            listarencontro();
            break;
        case 5:
            relatorioporcat();
            break;
        case 6:
            break;
        default:
        {
            printf("opção inválida! tente novamente");
            system("pause");
            limpaTela();
            menu_relatorio();
        }
        }
    }
}

void flushs()
{
#ifdef _WIN32
    fflush(stdin);
#else
    __fpurge(stdin);
#endif
}

void limpaTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// main
int main()
{
    int a = 0;
    recuperadado();

    while (a != -1)
    {
        a = menuprincipal();
    }

    salvadado();
    limpadado();
}

// funções fazendo suas funções
void recuperadado()
{
    recuperaencontros();
    recuperaamigo();
    recuperalocal();
    recuperacategoria();
}
void salvadado()
{
    salvaencontros();
    salvaamigo();
    salvalocal();
    salvacategoria();
}
void limpadado()
{
    limpaencontros();
    limpaamigo();
    limpalocal();
    limpacategoria();
}
int validardatanas(Data d)
{

    if (d.mes < 1 || d.mes > 12)
        return 0; // Mês inválido

    if (d.dia < 1)
        return 0; // Dia inválido

    int ano_atual = 2025; // Substitua este valor pelo ano atual caso precise

    if (d.ano < 0 || d.ano > ano_atual)
    {
        return 0; // Ano inválido
    }

    // Verificar se o dia é válido para o mês
    if (d.mes == 2)
    {
        // Verificar fevereiro (ano bissexto)
        if ((d.ano % 4 == 0 && d.dia > 29) || (d.ano % 4 != 0 && d.dia > 28))
            return 0; // Dia inválido em fevereiro
    }
    else if (d.mes == 4 || d.mes == 6 || d.mes == 9 || d.mes == 11)
    {
        // Meses com 30 dias
        if (d.dia > 30)
            return 0; // Dia inválido para o mês
    }
    else
    {
        // Meses com 31 dias
        if (d.dia > 31)
            return 0; // Dia inválido para o mês
    }

    return 1; // Data válida
}
int validardataenc(Data d)
{

    if (d.mes < 1 || d.mes > 12)
        return 0; // Mês inválido

    if (d.dia < 1)
        return 0; // Dia inválido

    int ano_atual = 2025; // Substitua este valor pelo ano atual caso precise

    if (d.ano < 0 || d.ano < ano_atual)
    {
        return 0; // Ano inválido
    }

    // Verificar se o dia é válido para o mês
    if (d.mes == 2)
    {
        // Verificar fevereiro (ano bissexto)
        if ((d.ano % 4 == 0 && d.dia > 29) || (d.ano % 4 != 0 && d.dia > 28))
            return 0; // Dia inválido em fevereiro
    }
    else if (d.mes == 4 || d.mes == 6 || d.mes == 9 || d.mes == 11)
    {
        // Meses com 30 dias
        if (d.dia > 30)
            return 0; // Dia inválido para o mês
    }
    else
    {
        // Meses com 31 dias
        if (d.dia > 31)
            return 0; // Dia inválido para o mês
    }

    return 1; // Data válida
}

// Função para validar a hora
int validarhora(Hora hora)
{
    if (hora.hora < 0 || hora.hora > 23)
    {
        return 0;
    }

    if (hora.minuto < 0 || hora.minuto > 59)
    {
        return 0;
    }
    return 1; // Hora e minuto válidos
}

int cadastrarcategoria()
{

    char aux[100];
    int categoria_existente = 0;

    // Verificar se o amigo já está cadastrado (pelo nome ou email)
    for (int i = 0; i < numcategorias; i++)
    {
        if (strcmp(categorias[i].nome, aux) == 0)
        {
            categoria_existente = 1;
            break;
        }
    }

    if (categoria_existente)
    {
        printf("Amigo já cadastrado com esse nome ou email.\n");
        return -1; // Retorna -1 para indicar que o cadastro falhou
    }

    printf("você escolheu adicionar categoria\n (Após adicionar a categoria, voltará pro menu automaticamente.)");
    if (numcategorias == 0)
    {
        categorias = (Categoria *)malloc(1 * sizeof(Categoria));
    }
    else
    {
        categorias = (Categoria *)realloc(categorias, (numcategorias + 1) * sizeof(Categoria));
    }
    printf("Qual o nome da categoria?\n");
    flushs();
    gets(aux);
    flushs();
    categorias[numcategorias].nome = (char *)malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(categorias[numcategorias].nome, aux);
    printf("%s\n", categorias[numcategorias].nome);
    numcategorias++;
    limpaTela();

    return 0;
}

int alterarcategoria()
{
    if (numcategorias == 0)
    {
        printf("Voce ainda nao tem categorias! adicione uma primeiro\n\n");
        system("pause");
        limpaTela();
        return 0;
    }

    char categoria[100];

    int encontrado = 0, i, aux;
    printf("digite o nome da categoria que você quer editar\n (Após alterar a categoria voltará pro menu automaticamente\n");
    flushs();
    gets(categoria);
    flushs();

    for (i = 0; i < numcategorias; i++)
    {

        aux = strcmp(categorias[i].nome, categoria);

        if (aux == 0)
        {
            encontrado = 1;

            printf("digite a nova categoria:\n");
            flushs();
            gets(categoria);
            flushs();
            categorias[i].nome = (char *)malloc((strlen(categoria) + 1) * sizeof(char));
            strcpy(categorias[i].nome, categoria);

            printf("%s\n", categorias[i].nome);
            limpaTela();
            return 0;
        }
    }

    if (!encontrado)
    {
        printf("categoria não encontrada!\n");
        system("pause");
        limpaTela();
    }

    return 0;
}

int excluircategoria()
{
    if (numcategorias == 0)
    {
        printf("Voce ainda nao tem categorias! adicione uma primeiro\n");
        system("pause");
        limpaTela();
        return 0;
    }
    char nome[100];
    int i, j;
    int encontrado = 0;

    printf("Qual o nome da categoria que você quer excluir?(Ao excluir a categoria, voltará pro menu automaticamente\n");
    flushs();
    gets(nome);
    for (i = 0; i <= numcategorias; i++)
    {
        int aux = strcmp(categorias[i].nome, nome);
        if (aux == 0)
        {
            encontrado = 1;
            printf("categoria  %s encontrado, excluindo\n", categorias[i].nome);

            free(categorias[i].nome);
            for (j = i; j < numcategorias - 1; j++)
            {
                categorias[j] = categorias[j + 1];
            }
            categorias = (Categoria *)realloc(categorias, (numcategorias - 1) * sizeof(Categoria));
            numcategorias--;
        }
    }

    if (!encontrado)
    {
        printf("categoria não encontrada!\n");
        system("pause");
        limpaTela();
        return 0;
    }

    return 0;
}

int cadastrarlocal()
{

    char aux[100];
    printf("você escolheu adicionar local\n (Após adicionar o local voltará pro menu automaticamente)");
    if (numlocais == 0)
    {
        locais = (Local *)malloc(1 * sizeof(Local));
    }
    else
    {
        locais = (Local *)realloc(locais, (numlocais + 1) * sizeof(Local));
    }
    printf("Qual o nome do local\n");
    flushs();
    gets(aux);
    flushs();
    locais[numlocais].nomelocal = (char *)malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(locais[numlocais].nomelocal, aux);
    printf("%s\n", locais[numlocais].nomelocal);
    limpaTela();
    printf("qual o logradouro(nome da rua)?\n");
    flushs();
    gets(aux);
    flushs();
    locais[numlocais].endereco.logradouro = (char *)malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(locais[numlocais].endereco.logradouro, aux);
    printf("%s\n", locais[numlocais].endereco.logradouro);
    limpaTela();
    printf("digite o número do local\n");
    scanf("%d", &locais[numlocais].endereco.numero);
    limpaTela();
    printf("qual o bairro?\n");
    flushs();
    gets(aux);
    flushs();
    locais[numlocais].endereco.bairro = (char *)malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(locais[numlocais].endereco.bairro, aux);
    printf("%s\n", locais[numlocais].endereco.bairro);
    limpaTela();
    printf("qual a cidade?\n");
    flushs();
    gets(aux);
    flushs();
    locais[numlocais].endereco.cidade = (char *)malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(locais[numlocais].endereco.cidade, aux);
    printf("%s\n", locais[numlocais].endereco.cidade);
    limpaTela();
    printf("qual o estado?\n");
    flushs();
    gets(aux);
    flushs();
    locais[numlocais].endereco.estado = (char *)malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(locais[numlocais].endereco.estado, aux);
    printf("%s\n", locais[numlocais].endereco.estado);
    numlocais++;
    limpaTela();

    return 0;
}

int alterarlocal()
{
    if (numlocais == 0)
    {
        printf("Voce ainda nao tem locais! adicione um primeiro\n\n");
        system("pause");
        limpaTela();
        return 0;
    }

    char aux[100];
    int dado, encontrado = 0, h;
    printf("Qual o nome do local que você quer editar?(Após editar o local, voltará pro menu automaticamente)");
    flushs();
    gets(aux);
    flushs();

    for (int i = 0; i < numlocais; i++)
    {
        int aux1 = strcmp(locais[i].nomelocal, aux);
        if (aux1 == 0)
        {
            encontrado = 1;
            printf("local %s encontrado\n", locais[i].nomelocal);
            printf("dados do local:\n nome(1):%s\n logradouro(2):%s\n numero(3):%i\n bairro(4):%s\n cidade(5):%s\n estado(6):%s\n", locais[i].nomelocal, locais[i].endereco.logradouro, locais[i].endereco.numero, locais[i].endereco.bairro, locais[i].endereco.cidade, locais[i].endereco.estado);
            printf("qual dado você quer editar?\n");
            scanf("%d", &dado);
            limpaTela();
            switch (dado)
            {
            case 1:
                printf("digite o novo nome do local:\n");
                flushs();
                gets(aux);
                flushs();
                locais[i].nomelocal = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                strcpy(locais[i].nomelocal, aux);
                printf("%s\n", locais[i].nomelocal);
                limpaTela();
                break;

            case 2:
                printf("digite o novo logradouro:\n");
                flushs();
                gets(aux);
                flushs();
                locais[i].endereco.logradouro = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                strcpy(locais[i].endereco.logradouro, aux);
                printf("%s\n", locais[i].endereco.logradouro);
                limpaTela();

                break;

            case 3:
                printf("digite o novo numero:\n");
                scanf("%d", &locais[i].endereco.numero);
                limpaTela();
                printf("digite 1 para voltar pro  menu principal ou 0 para finalizar");
                scanf("%d", &h);
                limpaTela();

                break;

            case 4:
                printf("digite o novo bairro:\n");
                flushs();
                gets(aux);
                flushs();
                locais[i].endereco.bairro = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                strcpy(locais[i].endereco.bairro, aux);
                printf("%s\n", locais[i].endereco.bairro);
                limpaTela();
                break;

            case 5:
                printf("digite a nova cidade:\n");
                flushs();
                gets(aux);
                flushs();
                locais[i].endereco.cidade = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                strcpy(locais[i].endereco.cidade, aux);
                printf("%s\n", locais[i].endereco.cidade);
                limpaTela();
                break;

            case 6:
                printf("digite o novo estado:\n");
                flushs();
                gets(aux);
                flushs();
                locais[i].endereco.estado = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                strcpy(locais[i].endereco.estado, aux);
                printf("%s\n", locais[i].endereco.estado);
                limpaTela();

                break;
            }
        }
    }
    if (!encontrado)
    {
        printf("local não encontrado!\n");
        system("pause");
        limpaTela();
    }

    return 0;
}

int excluirlocal()
{

    if (numlocais == 0)
    {
        printf("Voce ainda nao tem locais! adicione um primeiro\n\n");
        system("pause");
        limpaTela();
        return 0;
    }

    char nome[100];
    int i, j;
    int encontrado = 0;

    printf("Qual o nome do local que você quer excluir?\n (Após excluir o local, voltará pro menu automaticamente)");
    flushs();
    gets(nome);
    for (i = 0; i < numlocais; i++)
    {
        int aux = strcmp(locais[i].nomelocal, nome);
        if (aux == 0)
        {
            encontrado = 1;
            printf("local %s encontrado, excluindo\n", locais[i].nomelocal);

            free(locais[i].nomelocal);
            free(locais[i].endereco.logradouro);
            free(locais[i].endereco.bairro);
            free(locais[i].endereco.cidade);
            free(locais[i].endereco.estado);
            // Deslocar os elementos à esquerda para "remover" o amigo
            for (j = i; j < numlocais - 1; j++)
            {
                locais[j] = locais[j + 1];
            }
            locais = (Local *)realloc(locais, (numlocais - 1) * sizeof(Local));
            numlocais--;
            printf("local excluido!\n");

            return 0;

            break;
        }

        if (!encontrado)
        {
            printf("local não encontrado!\n");
            system("pause");
            limpaTela();

            return 0;
        }
    }
    return 0;
}

int excluiramigo()
{
    if (numamigos == 0)
    {
        printf("Voce ainda nao tem amigos adicionados! adicione um primeiro\n\n");
        system("pause");
        limpaTela();
        return 0;
    }

    char nome[100];
    int i, j, encontrado = 0;

    printf("Digite o nome do amigo que deseja excluir: (Após excluir o amigo, voltará pro menu automaticamente)");

    flushs();

    gets(nome);
    flushs();

    for (i = 0; i <= numamigos; i++)
    {

        int aux = strcmp(amigos[i].nome, nome); // Compara o nome do amigo da lista com o nome que o usuário inseriu
        if (aux == 0)
        { // Se a comparação retornar 0, significa que os nomes são iguais (encontrou o amigo)
            encontrado = 1;
            printf("Amigo %s encontrado, excluindo\n", amigos[i].nome);

            // Liberar a memória alocada para o amigo
            free(amigos[i].nome);
            free(amigos[i].apelido);
            free(amigos[i].email);
            free(amigos[i].telefone);

            // Deslocar os elementos à esquerda para "remover" o amigo da lista
            for (j = i; j < numamigos - 1; j++)
            {
                amigos[j] = amigos[j + 1]; // Move o próximo amigo para a posição atual, efetivamente "apagando" o amigo que foi excluído
            }

            // Redimensiona o array para remover o espaço extra
            amigos = (Amigo *)realloc(amigos, (numamigos - 1) * sizeof(Amigo)); // Redefine o tamanho do array para um a menos, removendo o amigo da memória
            numamigos--;                                                        // Decrementa a quantidade de amigos, já que um foi excluído
            printf("Amigo excluido!\n");
            break;
        }
    }

    if (!encontrado)
    {
        printf("Amigo não encontrado!\n");
        system("pause");
        limpaTela();
    }

    return 0;
}

int alteraramigo()
{
    if (numamigos == 0)
    {
        printf("Voce ainda nao tem amigos adicionados! adicione um primeiro\n\n");
        system("pause");
        limpaTela();
        return 0;
    }

    char aux[100];
    int dado, encontrado = 0;

    printf("Qual o nome do amigo que você quer alterar? (Após alterar o amigo, voltará pro menu automaticamente)");
    flushs();
    gets(aux);

    flushs();

    for (int i = 0; i < numamigos; i++)
    {
        int aux2 = strcmp(amigos[i].nome, aux); // Comparar o nome do amigo
        if (aux2 == 0)
        {
            encontrado = 1;
            printf("Amigo %s encontrado!\n", amigos[i].nome);
            printf("Dados do amigo:\n");
            printf("1. Nome: %s\n", amigos[i].nome);
            printf("2. Apelido: %s\n", amigos[i].apelido);
            printf("3. Email: %s\n", amigos[i].email);
            printf("4. Data de Nascimento: %02d/%02d/%d\n", amigos[i].nascimento.dia,
                   amigos[i].nascimento.mes, amigos[i].nascimento.ano);
            printf("5. Telefone: %s\n", amigos[i].telefone); // Exibir o telefone

            printf("Qual dado você quer editar? (1 - Nome, 2 - Apelido, 3 - Email, 4 - Data de Nascimento, 5 - Telefone): ");
            scanf("%d", &dado);
            flushs(); // Limpar o buffer após scanf

            switch (dado)
            {
            case 1:
                printf("Digite o novo nome:\n");
                flushs();
                gets(aux);
                // Liberar memória antiga e alocar nova para o nome
                free(amigos[i].nome);
                amigos[i].nome = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                strcpy(amigos[i].nome, aux);
                printf("Novo nome: %s\n", amigos[i].nome);
                break;

            case 2:
                printf("Digite o novo apelido:\n");
                flushs();
                gets(aux);

                // Liberar memória antiga e alocar nova para o apelido
                free(amigos[i].apelido);
                amigos[i].apelido = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                strcpy(amigos[i].apelido, aux);
                printf("Novo apelido: %s\n", amigos[i].apelido);
                break;

            case 3:
                printf("Digite o novo email:\n");
                flushs();
                gets(aux);

                // Liberar memória antiga e alocar nova para o email
                free(amigos[i].email);
                amigos[i].email = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                strcpy(amigos[i].email, aux);
                printf("Novo email: %s\n", amigos[i].email);
                break;

            case 4:
                printf("Digite a nova data de nascimento (dia mês ano): ");
                scanf("%d %d %d", &amigos[i].nascimento.dia, &amigos[i].nascimento.mes, &amigos[i].nascimento.ano);

                if (!validardatanas(amigos[i].nascimento))
                {
                    printf("Data inválida! A data não foi alterada.\n");
                }
                else
                {
                    printf("Nova data de nascimento: %02d/%02d/%d\n",
                           amigos[i].nascimento.dia, amigos[i].nascimento.mes, amigos[i].nascimento.ano);
                }
                break;

            case 5:
                printf("Digite o novo telefone (DD XXXX XXXX):\n");
                flushs();
                gets(aux);

                // Liberar memória antiga e alocar nova para o telefone
                free(amigos[i].telefone);
                amigos[i].telefone = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                strcpy(amigos[i].telefone, aux);
                printf("Novo telefone: %s\n", amigos[i].telefone);
                break;

            default:
                printf("Opção inválida!\n");
                break;
            }
            break; // Sai do loop após encontrar o amigo
        }
    }

    if (!encontrado)
    {
        printf("Amigo não encontrado!\n");
        system("pause");
        limpaTela();
    }

    return 0;
}

int cadastraramigo()
{
    char aux[100];

    int amigo_existente = 0;

    if (numamigos == 0)
    {
        amigos = (Amigo *)malloc(sizeof(Amigo));
    }
    else
    {
        amigos = (Amigo *)realloc(amigos, (numamigos + 1) * sizeof(Amigo));
    }

    // pegar nome
    limpaTela();
    printf("nome: ");
    flushs();
    gets(aux);
    for (int i = 0; i < numamigos; i++)
    {
        if (strcmp(amigos[i].nome, aux) == 0 || strcmp(amigos[i].email, aux) == 0)
        {
            amigo_existente = 1;
            break;
        }
    }

    if (amigo_existente)
    {
        printf("Amigo já cadastrado com esse nome ou email.\n");
        system("pause");
        return -1; // Retorna -1 para indicar que o cadastro falhou
    }
    else
    {
        flushs();
        amigos[numamigos].nome = (char *)malloc((strlen(aux) + 1) * sizeof(char));
        strcpy(amigos[numamigos].nome, aux);
    }
    // pegar apelido
    limpaTela();
    printf("apelido do amigo:\n ");
    flushs();
    gets(aux);
    flushs();
    amigos[numamigos].apelido = (char *)malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(amigos[numamigos].apelido, aux);

    // pegar email
    limpaTela();
    printf("Qual o email do seu amigo\n");
    flushs();
    gets(aux);
    flushs();
    amigos[numamigos].email = (char *)malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(amigos[numamigos].email, aux);

    // pegar telefone
    limpaTela();
    printf("Qual o telefone do amigo: DD XXXX XXXX\n");
    flushs();
    gets(aux);
    flushs();
    amigos[numamigos].telefone = (char *)malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(amigos[numamigos].telefone, aux);

    // pegar data de nascimento

    limpaTela();
    int data_valida = 0;
    while (!data_valida)
    {

        printf("Digite a data de nascimento do seu amigo (dia mês ano): ");
        scanf("%d %d %d", &amigos[numamigos].nascimento.dia,
              &amigos[numamigos].nascimento.mes, &amigos[numamigos].nascimento.ano);

        // Validar a data
        data_valida = validardatanas(amigos[numamigos].nascimento);
        if (!data_valida)
        {
            printf("Data inválida. Tente novamente.\n");
        }
    }

    numamigos++;

    return 0;
}

void recuperaamigo()
{

    int sep = 0, i;
    char c, aux[200];

    FILE *pArq;
    pArq = fopen("amigos.txt", "r");
    if (pArq)
    {
        i = 0;
        while ((c = fgetc(pArq)) != EOF)
        {
            if ((c != '\n') && (c != '$'))
            {
                aux[i] = c;
                i++;
            }
            else if ((c == '\n') || (c == '$'))
            {
                aux[i] = '\0';
                i = 0;

                if (sep == 0)
                {
                    if (numamigos == 0)
                    {
                        amigos = (Amigo *)malloc(1 * sizeof(Amigo));
                    }
                    else
                    {
                        amigos = (Amigo *)realloc(amigos, (numamigos + 1) * sizeof(Amigo));
                    }
                    amigos[numamigos].nome = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                    strcpy(amigos[numamigos].nome, aux);
                }
                else if (sep == 1)
                {
                    amigos[numamigos].apelido = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                    strcpy(amigos[numamigos].apelido, aux);
                }
                else if (sep == 2)
                {
                    amigos[numamigos].email = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                    strcpy(amigos[numamigos].email, aux);
                }
                else if (sep == 3)
                {
                    amigos[numamigos].telefone = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                    strcpy(amigos[numamigos].telefone, aux);
                }
                else if (sep == 4)
                {
                    amigos[numamigos].nascimento.dia = atoi(aux);
                }
                else if (sep == 5)
                {
                    amigos[numamigos].nascimento.mes = atoi(aux);
                }
                else if (sep == 6)
                {
                    amigos[numamigos].nascimento.ano = atoi(aux);
                }
                sep++;
                if (c == '\n')
                {
                    numamigos++;
                    sep = 0;
                }
            }
        }
    }
    fclose(pArq);
}

void salvaamigo()
{
    FILE *pArq;
    pArq = fopen("amigos.txt", "w");
    if (pArq == NULL)
    {
        printf("ERRO! não foi possível salvar as informações");
        exit(0);
    }

    for (int i = 0; i < numamigos; i++)
    {
        fprintf(pArq, "%s$", amigos[i].nome);
        fprintf(pArq, "%s$", amigos[i].apelido);
        fprintf(pArq, "%s$", amigos[i].email);
        fprintf(pArq, "%s$", amigos[i].telefone);
        fprintf(pArq, "%i$", amigos[i].nascimento.dia);
        fprintf(pArq, "%i$", amigos[i].nascimento.mes);
        fprintf(pArq, "%i$", amigos[i].nascimento.ano);
        fprintf(pArq, "%c", '\n');
    }
    fclose(pArq);
}

void limpaamigo()
{
    if (numamigos == 0)
    {
        return;
    }
    else
    {
        for (int i = 0; i < numamigos; i++)
        {
            free(amigos[i].nome);
            free(amigos[i].apelido);
            free(amigos[i].email);
            free(amigos[i].telefone);
        }
        free(amigos);
    }
}

void recuperalocal()
{

    int sep = 0, i;
    char c, aux[200];

    FILE *pArq;
    pArq = fopen("locais.txt", "r");
    if (pArq)
    {
        i = 0;
        while ((c = fgetc(pArq)) != EOF)
        {
            if ((c != '\n') && (c != '$'))
            {
                aux[i] = c;
                i++;
            }
            else if ((c == '\n') || (c == '$'))
            {
                aux[i] = '\0';
                i = 0;

                if (sep == 0)
                {
                    if (numlocais == 0)
                    {
                        locais = (Local *)malloc(1 * sizeof(Local));
                    }
                    else
                    {
                        locais = (Local *)realloc(locais, (numlocais + 1) * sizeof(Local));
                    }
                    locais[numlocais].nomelocal = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                    strcpy(locais[numlocais].nomelocal, aux);
                }
                else if (sep == 1)
                {
                    locais[numlocais].endereco.logradouro = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                    strcpy(locais[numlocais].endereco.logradouro, aux);
                }
                else if (sep == 2)
                {
                    locais[numlocais].endereco.numero = atoi(aux);
                }
                else if (sep == 4)
                {
                    locais[numlocais].endereco.bairro = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                    strcpy(locais[numlocais].endereco.bairro, aux);
                }
                else if (sep == 5)
                {
                    locais[numlocais].endereco.cidade = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                    strcpy(locais[numlocais].endereco.cidade, aux);
                }
                else if (sep == 6)
                {
                    locais[numlocais].endereco.estado = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                    strcpy(locais[numlocais].endereco.estado, aux);
                }

                sep++;
                if (c == '\n')
                {
                    numlocais++;
                    sep = 0;
                }
            }
        }
    }
    fclose(pArq);
}
void salvalocal()
{
    FILE *pArq;
    pArq = fopen("locais.txt", "w");
    if (pArq == NULL)
    {
        printf("ERRO! não foi possível salvar as informações");
        exit(0);
    }

    for (int i = 0; i < numlocais; i++)
    {
        fprintf(pArq, "%s$", locais[i].nomelocal);
        fprintf(pArq, "%s$", locais[i].endereco.logradouro);
        fprintf(pArq, "%i$", locais[i].endereco.numero);
        fprintf(pArq, "%s$", locais[i].endereco.bairro);
        fprintf(pArq, "%s$", locais[i].endereco.cidade);
        fprintf(pArq, "%s$", locais[i].endereco.estado);

        fprintf(pArq, "%c", '\n');
    }
    fclose(pArq);
}

void limpalocal()
{
    if (numlocais == 0)
    {
        return;
    }
    else
    {
        for (int i = 0; i < numlocais; i++)
        {
            free(locais[i].nomelocal);
            free(locais[i].endereco.logradouro);
            free(locais[i].endereco.bairro);
            free(locais[i].endereco.cidade);
            free(locais[i].endereco.estado);
        }
        free(locais);
    }
}

void recuperacategoria()
{

    int i;
    char c = 0, aux[200];

    FILE *pArq;
    pArq = fopen("categorias.txt", "r");
    if (pArq)
    {
        i = 0;
        while ((c = fgetc(pArq)) != EOF)
        {
            if ((c != '\n') && (c != '$'))
            {
                aux[i] = c;
                i++;
            }
            else if ((c == '\n') || (c == '$'))
            {
                aux[i] = '\0';
                i = 0;

                if (c == '$')
                {
                    if (numcategorias == 0)
                    {
                        categorias = (Categoria *)malloc(1 * sizeof(Categoria));
                    }
                    else
                    {
                        categorias = (Categoria *)realloc(categorias, (numcategorias + 1) * sizeof(Categoria));
                    }
                    categorias[numcategorias].nome = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                    strcpy(categorias[numcategorias].nome, aux);
                }

                if (c == '\n')
                {
                    numcategorias++;
                }
            }
        }
    }
    fclose(pArq);
}

void salvacategoria()
{

    FILE *pArq;
    pArq = fopen("categorias.txt", "w");
    if (pArq == NULL)
    {
        printf("ERRO! não foi possível salvar as informações");
        exit(0);
    }

    for (int i = 0; i < numcategorias; i++)
    {
        fprintf(pArq, "%s$", categorias[i].nome);

        fprintf(pArq, "%c", '\n');
    }
    fclose(pArq);
}

void limpacategoria()
{

    if (numcategorias == 0)
    {
        return;
    }
    else
    {
        for (int i = 0; i < numcategorias; i++)
        {
            free(categorias[i].nome);
        }
        free(categorias);
    }
}

void listaramigo()
{
    int op = 0;
    if (numamigos < 1)
    {
        printf("nenhum amigo adicionado!\n");
        system("pause");
        limpaTela();
        return;
    }
    else
    {

        limpaTela();
        printf("1 - listar amigo específico\n");
        printf("2 - listar todos os amigos \n");

        scanf("%d", &op);

        switch (op)
        {
        case 1:
            escolherAmigoEsp();
            break;

        case 2:
            listatodosamigos();
            break;
        default:
        {

            printf("opção inválida! tente novamente");
            system("pause");
            limpaTela();
            listaramigo();
        }
        }
    }
}

void escolherAmigoEsp()
{
    int amigue;
    printf("escolha um amigo para listar as informações\n\n");

    for (int i = 0; i < numamigos; i++)
    {
        printf("%d [ %s ] \n", i + 1, amigos[i].nome);
    }
    scanf("%d", &amigue);

    imprimeAmigo(amigue - 1);
    flushs();
    system("pause");
}

void imprimeAmigo(int amigo)
{
    printf("Amigo [%d]\n", amigo + 1);
    printf("Nome: [%s]\n", amigos[amigo].nome);
    printf("Apelido: [%s]\n", amigos[amigo].apelido);
    printf("Email: [%s]\n", amigos[amigo].email);
    printf("Telefone:[%s]\n", amigos[amigo].telefone);
    printf("Data de nascimento: %d/%d/%d\n", amigos[amigo].nascimento.dia, amigos[amigo].nascimento.mes, amigos[amigo].nascimento.ano);
}

void listatodosamigos()
{

    for (int i = 0; i < numamigos; i++)
    {
        imprimeAmigo(i);
        printf("\n");
    }
    flushs();
    system("pause");
}

void listarlocal()
{

    int op = 0;
    if (numlocais < 1)
    {
        printf("nenhum local adicionado!\n");
        system("pause");
        limpaTela();
        return;
    }
    else
    {

        limpaTela();
        printf("1 - listar local específico\n");
        printf("2 - listar todos os locais \n");

        scanf("%d", &op);

        switch (op)
        {
        case 1:
            escolherlocalesp();
            break;

        case 2:
            listatodoslocais();
            break;
        default:
        {

            printf("opção inválida! tente novamente");
            system("pause");
            limpaTela();
            listarlocal();
        }
        }
    }
}

void escolherlocalesp()
{
    int localesc;
    printf("escolha um local para listar as informações\n\n");

    for (int i = 0; i < numlocais; i++)
    {
        printf("%d [ %s ] \n", i + 1, locais[i].nomelocal);
    }
    scanf("%d", &localesc);

    imprimelocal(localesc - 1);
    flushs();
    system("pause");
}

void imprimelocal(int local)
{
    printf("Local [%d]\n", local + 1);
    printf("Nome: [%s]\n", locais[local].nomelocal);
    printf("Logradouro: [%s]\n", locais[local].endereco.logradouro);
    printf("Número: [%d]\n", locais[local].endereco.numero);
    printf("Bairro:[%s]\n", locais[local].endereco.bairro);
    printf("Cidade:[%s]\n", locais[local].endereco.cidade);
    printf("Estado:[%s]\n", locais[local].endereco.estado);
}

void listatodoslocais()
{

    for (int i = 0; i < numlocais; i++)
    {
        imprimelocal(i);
        printf("\n");
    }
    flushs();
    system("pause");
}

void listarcategoria()
{

    if (numcategorias == 0)
    {
        printf("nenhuma categoria adicionado!\n");
        system("pause");
        limpaTela();
        return;
    }
    else
    {
        printf("Categorias:\n");
        for (int i = 0; i < numcategorias; i++)
        {

            printf("%02d. - %s\n", i + 1, categorias[i].nome);
        }
        system("pause");
    }
}
int cadastrarencontro()
{
    int erro = 0, op = 0;
    char aux[100];

    if (numamigos == 0 || numlocais == 0 || numcategorias == 0)
    {
        printf("Você ainda não possui ");

        if (numamigos == 0 && numlocais == 0 && numcategorias == 0)
        {
            printf("nenhum amigo, nenhum local e nenhuma categoria adicionados.\n");
        }
        else
        {
            if (numamigos == 0)
            {
                printf("nenhum amigo adicionado");
            }

            if (numlocais == 0)
            {
                if (numamigos == 0)
                {
                    printf(", ");
                }
                printf("nenhum local adicionado");
            }

            if (numcategorias == 0)
            {
                if (numamigos == 0 || numlocais == 0)
                {
                    printf(" e ");
                }
                printf("nenhuma categoria adicionada");
            }

            printf(".\n");
        }

        printf("\nVolte para o menu e crie as opções necessárias!\n");
        system("pause");
        return -1;
    }

    printf("Você escolheu adicionar um encontro\n (Após adicionar o encontro, voltará para o menu automaticamente)\n");

    if (numencontros == 0)
    {
        encontros = (Encontro *)malloc(sizeof(Encontro));
    }
    else
    {
        encontros = (Encontro *)realloc(encontros, (numencontros + 1) * sizeof(Encontro));
    }

    if (encontros == NULL)
    {
        printf("Erro de alocação de memória para encontros!\n");
        return -1;
    }

    limpaTela();
    printf("Qual o nome do encontro?\n");
    flushs();
    gets(aux); // Usando gets, conforme solicitado
    flushs();

    encontros[numencontros].nomeencontro = (char *)malloc((strlen(aux) + 1) * sizeof(char));
    if (encontros[numencontros].nomeencontro == NULL)
    {
        printf("Erro de alocação de memória para nome do encontro!\n");
        system("pause");
        return -1;
    }
    strcpy(encontros[numencontros].nomeencontro, aux);
    printf("%s\n", encontros[numencontros].nomeencontro);
    limpaTela();

    encontros[numencontros].amigosencontro = NULL;
    encontros[numencontros].numamigosencontro = 0;

    while (erro != 1)
    {
        if (numamigos == 0)
        {
            printf("Nenhum amigo cadastrado ainda. Deseja cadastrar um amigo? (1 - Sim / 2 - Não): ");
            scanf("%d", &op);
            if (op == 1)
            {
                cadastraramigo();
                salvaamigo();
            }
            else
            {
                printf("Você não pode adicionar um amigo ao encontro sem cadastrá-lo.\n");
                erro = 1;
                system("pause");
                return 0;
            }
        }

        printf("Qual amigo você deseja adicionar ao encontro?\n");
        listaNomeAmigos();

        printf("Digite o número do amigo: ");
        scanf("%d", &op);

        if (op <= 0 || op > numamigos)
        {
            printf("Opção inválida!!\n");
            system("pause");
        }
        else
        {
            int amigoIgual = 0;
            for (int i = 0; i < encontros[numencontros].numamigosencontro; i++)
            {
                if (strcmp(encontros[numencontros].amigosencontro[i], amigos[op - 1].nome) == 0)
                {
                    amigoIgual = 1;
                    break;
                }
            }

            if (amigoIgual)
            {
                printf("Esse amigo já foi adicionado ao encontro.\n\n");
                printf("Selecione outro amigo.\n\n");
                system("pause");
            }
            else
            {
                // Aloca espaço para o nome do amigo
                if (encontros[numencontros].numamigosencontro == 0)
                {
                    encontros[numencontros].amigosencontro = (char **)malloc(sizeof(char *));
                }
                else
                {
                    encontros[numencontros].amigosencontro = (char **)realloc(encontros[numencontros].amigosencontro, (encontros[numencontros].numamigosencontro + 1) * sizeof(char *));
                }

                if (encontros[numencontros].amigosencontro == NULL)
                {
                    printf("Erro de alocação de memória para amigos no encontro!\n");
                    system("pause");
                    return -1;
                }

                // Aloca espaço para o nome do amigo
                encontros[numencontros].amigosencontro[encontros[numencontros].numamigosencontro] = (char *)malloc((strlen(amigos[op - 1].nome) + 1) * sizeof(char));

                // Copia o nome do amigo para o encontro
                strcpy(encontros[numencontros].amigosencontro[encontros[numencontros].numamigosencontro], amigos[op - 1].nome);

                encontros[numencontros].numamigosencontro++;

                printf("Amigo Adicionado!\n");
                system("pause");

                if (encontros[numencontros].numamigosencontro == numamigos)
                {
                    printf("Todos os amigos já foram adicionados ao encontro!\n");
                    system("pause");
                    erro = 1; // Define erro = 1 para parar o loop
                }
                else if (numamigos > 1 && encontros[numencontros].numamigosencontro != numamigos)
                {
                    limpaTela();
                    printf("\tDeseja adicionar mais um amigo? \t");
                    printf("\t\t\n 1 - Sim");
                    printf("\t\t\n 2 - Não \n");

                    scanf("%d", &op);

                    if (op == 1)
                    {
                        erro = 0; // Mantém erro = 0 para continuar o loop
                    }
                    else if (op == 2)
                    {
                        erro = 1; // Define erro = 1 para parar o loop
                    }
                    else
                    {
                        printf("Erro: Opção inválida!\n");
                        system("pause");
                    }
                }
            }
        }
    }

    limpaTela();
    int data_valida = 0;
    while (!data_valida)
    {
        printf("Digite a data do encontro (dd mm aaaa): ");
        scanf("%d %d %d", &encontros[numencontros].data.dia, &encontros[numencontros].data.mes, &encontros[numencontros].data.ano);

        // Validar a data
        data_valida = validardataenc(encontros[numencontros].data);

        if (!data_valida)
        {
            printf("Data inválida. Tente novamente.\n");
            system("pause");
            limpaTela();
        }
    }
    printf("Data marcada!");
    system("pause");
    limpaTela();

    int hora_valida = 0;
    while (!hora_valida)
    {
        printf("Digite a hora do encontro (hora minuto): ");
        scanf("%d %d", &encontros[numencontros].hora.hora, &encontros[numencontros].hora.minuto);

        // Valida a hora
        hora_valida = validarhora(encontros[numencontros].hora);
        if (!hora_valida)
        {
            printf("Hora inválida. Tente novamente.\n");
            system("pause");
            limpaTela();
        }
    }
    printf("Hora marcada!");
    system("pause");

    int categoria_valida = 0;
    while (!categoria_valida)
    {
        limpaTela();
        printf("Escolha a categoria do encontro\n");
        listarcategoria();
        printf("Digite o número da categoria: ");
        scanf("%d", &op);

        if (op <= 0 || op > numcategorias)
        {
            printf("Opção inválida. Tente novamente.\n");
        }
        else
        {
            encontros[numencontros].categoriaencontro = (char *)malloc(strlen(categorias[op - 1].nome) + 1);
            strcpy(encontros[numencontros].categoriaencontro, categorias[op - 1].nome);
            categoria_valida = 1;
        }
    }

    printf("Categoria adicionada!!");
    system("pause");
    limpaTela();

    int local_valido = 0;
    while (!local_valido)
    {
        if (numlocais == 0)
        {
            printf("Nenhum local cadastrado ainda. Deseja cadastrar um local? (1 - Sim / 2 - Não): ");
            scanf("%d", &op);
            if (op == 1)
            {
                cadastrarlocal(); // Função para cadastrar um novo local
                salvalocal();     // Função para salvar os locais
            }
            else
            {
                printf("Você não pode adicionar um local ao encontro sem cadastrá-lo.\n");
                erro = 1;
            }
        }
        else
        {
            printf("Escolha um local para o encontro:\n");
            listaNomeLocal();
            printf("Digite o número do local desejado: ");
            scanf("%d", &op);

            if (op <= 0 || op > numlocais)
            {
                printf("Opção inválida!!\n");
            }
            else
            {
                // Atribuir local ao encontro
                encontros[numencontros].localencontro = (char *)malloc((strlen(locais[op - 1].nomelocal) + 1) * sizeof(char));
                strcpy(encontros[numencontros].localencontro, locais[op - 1].nomelocal);
                local_valido = 1;
            }
        }

        printf("Local adicionado!!");
        system("pause");
        limpaTela();

        printf("Adicione uma descrição ao encontro\n ");
        int desc_valida = 0;

        while (!desc_valida)
        {
            flushs();
            char descricao[500];
            printf("\nDigite a descrição do encontro: ");
            gets(descricao); // Usando gets, conforme solicitado

            encontros[numencontros].descricao = (char *)malloc((strlen(descricao) + 1) * sizeof(char));

            if (encontros[numencontros].descricao == NULL)
            {
                printf("Erro de alocação de memória para a descrição!\n");
                return -1;
            }

            strcpy(encontros[numencontros].descricao, descricao);
            printf("Descrição adicionada com sucesso!\n");
            desc_valida = 1;

            printf("Encontro Adicionado!!");
            system("pause");
            limpaTela();
        }
    }

    numencontros++;
    return 0;
}

void listaNomeAmigos()
{
    printf("Amigos:\n");
    for (int i = 0; i < numamigos; i++)
    {
        printf("%d - [%s]\n", i + 1, amigos[i].nome);
    }
}
void listaNomeLocal()

{
    printf("Locais:\n");
    for (int i = 0; i < numlocais; i++)
    {
        printf("%d - [%s]\n", i + 1, locais[i].nomelocal);
    }
}
void listarencontro()
{
    int op = 0;
    if (numencontros < 1)
    {
        printf("Nenhum encontro cadastrado!\n");
        system("pause");
        limpaTela();
        return;
    }
    else
    {
        limpaTela();
        printf("1 - Listar encontro específico\n");
        printf("2 - Listar todos os encontros\n");

        scanf("%d", &op);

        switch (op)
        {
        case 1:
            escolherencontroesp();
            break;

        case 2:
            listartodosencontros();
            break;
        default:
        {
            printf("Opção inválida! Tente novamente.\n");
            system("pause");
            limpaTela();
            listarencontro();
        }
        }
    }
}

void listartodosencontros()
{
    for (int i = 0; i < numencontros; i++)
    {
        imprimeencontro(i);
        printf("\n");
    }
    flushs();
    system("pause");
}

void imprimeencontro(int encontro)
{
    printf("Encontro [%d]\n", encontro + 1);
    printf("Nome: [%s]\n", encontros[encontro].nomeencontro);
    printf("Data: %d/%d/%d\n", encontros[encontro].data.dia, encontros[encontro].data.mes, encontros[encontro].data.ano);
    printf("Hora: %d:%d\n", encontros[encontro].hora.hora, encontros[encontro].hora.minuto);
    printf("Categoria: [%s]\n", encontros[encontro].categoriaencontro);
    printf("Local: [%s]\n", encontros[encontro].localencontro);

    printf("Amigos no encontro:\n");
    for (int i = 0; i < encontros[encontro].numamigosencontro; i++)
    {
        printf("- %s\n", encontros[encontro].amigosencontro[i]);
    }

    if (encontros[encontro].descricao != NULL)
    {
        printf("Descrição: [%s]\n", encontros[encontro].descricao);
    }

    else
    {
        printf("Nenhuma descrição foi adicionada ao encontro.\n");
    }
}
void escolherencontroesp()
{
    int encontro;
    printf("Escolha um encontro para listar as informações\n\n");

    for (int i = 0; i < numencontros; i++)
    {
        printf("%d - [ %s ] \n", i + 1, encontros[i].nomeencontro);
    }
    scanf("%d", &encontro);

    imprimeencontro(encontro - 1);
    flushs();
    system("pause");
}
void relatorioporcat()
{

    int categoriaEscolhida;
    if (numencontros == 0)
    {
        printf("Nenhum encontro registrado até o momento.\n");
        system("pause");
        return;
    }

    printf("Categorias disponíveis:\n");
    listarcategoria();

    printf("\nEscolha a categoria para ver os encontros: ");
    scanf("%d", &categoriaEscolhida);

    if (categoriaEscolhida <= 0 || categoriaEscolhida > numcategorias)
    {
        printf("Categoria inválida!\n");
        return;
    }

    int encontrou = 0;
    for (int i = 0; i < numencontros; i++)
    {
        if (strcmp(encontros[i].categoriaencontro, categorias[categoriaEscolhida - 1].nome) == 0)
        {
            printf("\nEncontro: %s\n", encontros[i].nomeencontro);
            printf("Data: %d/%d/%d\n", encontros[i].data.dia, encontros[i].data.mes, encontros[i].data.ano);
            printf("Hora: %02d:%02d\n", encontros[i].hora.hora, encontros[i].hora.minuto);
            printf("Local: %s\n", encontros[i].localencontro);
            printf("Descrição: %s\n", encontros[i].descricao);
            printf("\n========================\n");
            encontrou = 1;
        }
    }

    if (!encontrou)
    {
        printf("Não há encontros para essa categoria.\n");
    }
    system("pause");
}
int alterarencontro()
{
    if (numencontros == 0)
    {
        printf("Você ainda não tem encontros registrados! Adicione um primeiro.\n\n");
        system("pause");
        limpaTela();
        return 0;
    }

    char nomeEncontro[100];
    int dado, encontrado = 0;

    printf("Qual o nome do encontro que você deseja alterar? (Após alterar, voltará pro menu automaticamente)\n");
    flushs();
    gets(nomeEncontro);

    for (int i = 0; i < numencontros; i++)
    {
        int cmp = strcmp(encontros[i].nomeencontro, nomeEncontro);
        if (cmp == 0)
        {
            encontrado = 1;
            printf("Encontro %s encontrado!\n", encontros[i].nomeencontro);
            printf("Dados do encontro:\n");
            printf("1. Nome: %s\n", encontros[i].nomeencontro);
            printf("2. Data: %02d/%02d/%d\n", encontros[i].data.dia, encontros[i].data.mes, encontros[i].data.ano);
            printf("3. Hora: %02d:%02d\n", encontros[i].hora.hora, encontros[i].hora.minuto);
            printf("4. Local: %s\n", encontros[i].localencontro);
            printf("Encontro %s encontrado!\n", encontros[i].nomeencontro);
            printf("5. Amigos:\n");
            for (int j = 0; j < encontros[i].numamigosencontro; j++)
            {
                printf("   %d. %s\n", j + 1, encontros[i].amigosencontro[j]);
            }

            printf("Qual dado você quer editar? (1 - Nome, 2 - Data, 3 - Hora, 4 - Local, 5 - Descrição 6 - Amigos): ");

            scanf("%d", &dado);

            // Adicionando uma mensagem de depuração aqui
            printf("Você escolheu a opção: %d\n", dado); // Verifica se a opção está sendo lida corretamente

            switch (dado)
            {
            case 1:
                printf("Digite o novo nome do encontro:\n");
                flushs();           // Mantido flushs()
                gets(nomeEncontro); // Mantido o uso de gets()

                free(encontros[i].nomeencontro);
                encontros[i].nomeencontro = (char *)malloc((strlen(nomeEncontro) + 1) * sizeof(char));
                strcpy(encontros[i].nomeencontro, nomeEncontro);
                printf("Novo nome: %s\n", encontros[i].nomeencontro);
                break;

            case 2:
                printf("Digite a nova data do encontro (dia mês ano): ");
                if (scanf("%d %d %d", &encontros[i].data.dia, &encontros[i].data.mes, &encontros[i].data.ano) != 3)
                {
                    printf("Entrada inválida para a data!\n");
                    flushs();
                    return 0;
                }
                if (!validardataenc(encontros[i].data))
                { // Valida a data
                    printf("Data inválida! A data não foi alterada.\n");
                }
                else
                {
                    printf("Nova data: %02d/%02d/%d\n", encontros[i].data.dia, encontros[i].data.mes, encontros[i].data.ano);
                }
                break;

            case 3:
                printf("Digite a nova hora do encontro (hora minuto): ");
                if (scanf("%d %d", &encontros[i].hora.hora, &encontros[i].hora.minuto) != 2)
                {
                    printf("Entrada inválida para a hora!\n");
                    flushs();
                    return 0;
                }
                if (!validarhora(encontros[i].hora))
                { // Valida a hora
                    printf("Hora inválida! A hora não foi alterada.\n");
                }
                else
                {
                    printf("Nova hora: %02d:%02d\n", encontros[i].hora.hora, encontros[i].hora.minuto);
                }
                break;

            case 4:
                printf("Escolha um novo local para o encontro:\n");
                listaNomeLocal(); // Função que lista os locais disponíveis
                int op;
                if (scanf("%d", &op) != 1 || op <= 0 || op > numlocais)
                {
                    printf("Opção inválida!\n");
                    flushs();
                    return 0;
                }
                free(encontros[i].localencontro);
                encontros[i].localencontro = (char *)malloc((strlen(locais[op - 1].nomelocal) + 1) * sizeof(char));
                strcpy(encontros[i].localencontro, locais[op - 1].nomelocal);
                printf("Novo local: %s\n", encontros[i].localencontro);
                break;

            case 5:
                printf("Digite a nova descrição do encontro:\n");
                flushs();                                      // Mantido flushs()
                gets(nomeEncontro);                            // Mantido o uso de gets()
                nomeEncontro[strcspn(nomeEncontro, "\n")] = 0; // Remover o '\n'

                free(encontros[i].descricao);
                encontros[i].descricao = (char *)malloc((strlen(nomeEncontro) + 1) * sizeof(char));
                strcpy(encontros[i].descricao, nomeEncontro);
                printf("Nova descrição: %s\n", encontros[i].descricao);
                break;
            case 6: // Vamos adicionar uma nova opção para editar os amigos do encontro
                printf("Amigos atuais do encontro '%s':\n", encontros[i].nomeencontro);
                if (encontros[i].numamigosencontro == 0)
                {
                    printf("Nenhum amigo registrado neste encontro.\n");
                }
                else
                {
                    // Exibe os amigos associados ao encontro
                    for (int j = 0; j < encontros[i].numamigosencontro; j++)
                    {
                        printf("%d. %s\n", j + 1, encontros[i].amigosencontro[j]);
                    }
                }

                printf("\nEscolha uma opção:\n");
                printf("1. Adicionar um amigo\n");
                printf("2. Remover um amigo\n");
                printf("0. Voltar\n");

                int opAmigo;
                scanf("%d", &opAmigo);

                if (opAmigo == 1)
                {
                    // Adicionar amigo
                    listaNomeAmigos(); // Função que lista os amigos disponíveis
                    int opAmigoAdicionar;
                    printf("Escolha o amigo que você deseja adicionar ao encontro: ");
                    scanf("%d", &opAmigoAdicionar);

                    if (opAmigoAdicionar <= 0 || opAmigoAdicionar > numamigos)
                    {
                        printf("Opção inválida!\n");
                    }
                    else
                    {
                        // Verifica se o amigo já está no encontro
                        int amigoExistente = 0;
                        for (int k = 0; k < encontros[i].numamigosencontro; k++)
                        {
                            if (strcmp(encontros[i].amigosencontro[k], amigos[opAmigoAdicionar - 1].nome) == 0)
                            {
                                amigoExistente = 1;
                                break;
                            }
                        }

                        if (amigoExistente)
                        {
                            printf("Este amigo já está no encontro.\n");
                        }
                        else
                        {
                            encontros[i].amigosencontro = (char **)realloc(encontros[i].amigosencontro, (encontros[i].numamigosencontro + 1) * sizeof(char *));
                            if (encontros[i].amigosencontro == NULL)
                            {
                                printf("Erro de alocação de memória!\n");
                                return 0;
                            }

                            encontros[i].amigosencontro[encontros[i].numamigosencontro] = (char *)malloc((strlen(amigos[opAmigoAdicionar - 1].nome) + 1) * sizeof(char));
                            strcpy(encontros[i].amigosencontro[encontros[i].numamigosencontro], amigos[opAmigoAdicionar - 1].nome);
                            encontros[i].numamigosencontro++;
                            printf("Amigo '%s' adicionado com sucesso!\n", amigos[opAmigoAdicionar - 1].nome);
                        }
                    }
                }
                else if (opAmigo == 2)
                {
                    if (encontros[i].numamigosencontro == 0)
                    {
                        printf("Não há amigos para remover.\n");
                    }
                    else
                    {
                        printf("Escolha o amigo a ser removido:\n");
                        for (int j = 0; j < encontros[i].numamigosencontro; j++)
                        {
                            printf("%d. %s\n", j + 1, encontros[i].amigosencontro[j]);
                        }
                        int opAmigoRemover;
                        printf("Escolha o número do amigo a ser removido: ");
                        scanf("%d", &opAmigoRemover);

                        if (opAmigoRemover <= 0 || opAmigoRemover > encontros[i].numamigosencontro)
                        {
                            printf("Opção inválida!\n");
                        }
                        else
                        {
                            free(encontros[i].amigosencontro[opAmigoRemover - 1]);

                            for (int j = opAmigoRemover - 1; j < encontros[i].numamigosencontro - 1; j++)
                            {
                                encontros[i].amigosencontro[j] = encontros[i].amigosencontro[j + 1];
                            }

                            encontros[i].amigosencontro = (char **)realloc(encontros[i].amigosencontro, (encontros[i].numamigosencontro - 1) * sizeof(char *));
                            encontros[i].numamigosencontro--;

                            printf("Amigo removido com sucesso!\n");
                        }
                    }
                }
                else if (opAmigo == 0)
                {
                    printf("Voltando...\n");
                    return 0;
                }
                else
                {
                    printf("Opção inválida!\n");
                }
                break;

            default:
                printf("Opção inválida!\n");
                break;
            }
            break;
        }
    }

    if (!encontrado)
    {
        printf("Encontro não encontrado!\n");
        system("pause");
        limpaTela();
    }
    return 0;
}

int excluirencontro()
{

    if (numencontros == 0)
    {
        printf("Você ainda não tem encontros adicionados! Adicione um primeiro.\n\n");
        system("pause");
        limpaTela();
        return 0;
    }

    char nome[100];
    int i, j, encontrado = 0;

    printf("Digite o nome do encontro que deseja excluir: (Após excluir o encontro, voltará pro menu automaticamente)\n");

    flushs();

    gets(nome);
    flushs();

    for (i = 0; i < numencontros; i++)
    {
        int aux = strcmp(encontros[i].nomeencontro, nome);
        if (aux == 0)
        {
            encontrado = 1;
            printf("Encontro '%s' encontrado, excluindo...\n", encontros[i].nomeencontro);

            free(encontros[i].nomeencontro);
            free(encontros[i].descricao);
            free(encontros[i].localencontro);

            for (int k = 0; k < encontros[i].numamigosencontro; k++)
            {
                free(encontros[i].amigosencontro[k]);
            }
            free(encontros[i].amigosencontro);

            for (j = i; j < numencontros - 1; j++)
            {
                encontros[j] = encontros[j + 1];
            }

            encontros = (Encontro *)realloc(encontros, (numencontros - 1) * sizeof(Encontro));
            numencontros--;
            printf("Encontro excluído!\n");
            break;
        }
    }

    if (!encontrado)
    {
        printf("Encontro não encontrado!\n");
        system("pause");
        limpaTela();
    }

    return 0;
}
void recuperaencontros()
{
    int sep = 0, i;
    char c, aux[200];

    FILE *pArq;
    pArq = fopen("encontros.txt", "r");
    if (pArq)
    {
        i = 0;
        while ((c = fgetc(pArq)) != EOF)
        {

            if ((c != '\n') && (c != '$') && (c != '@'))
            {
                aux[i] = c;
                i++;
            }
            else if ((c == '\n') || (c == '$') || (c == '@'))
            {
                aux[i] = '\0';
                i = 0;

                if (sep == 0)
                {
                    if (numencontros == 0)
                    {
                        encontros = (Encontro *)malloc(sizeof(Encontro));
                    }
                    else
                    {
                        encontros = (Encontro *)realloc(encontros, (numencontros + 1) * sizeof(Encontro));
                    }
                    encontros[numencontros].nomeencontro = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                    strcpy(encontros[numencontros].nomeencontro, aux);
                    encontros[numamigos].numamigosencontro = 0;
                }
                if (sep == 1 && c != '@')
                {
                    sep = 2;
                }
                if (sep == 1 && c == '@')
                {

                    if (encontros[numencontros].numamigosencontro == 0)
                    {
                        encontros[numencontros].amigosencontro = (char **)malloc(sizeof(char *));
                    }
                    else
                    {
                        encontros[numencontros].amigosencontro = (char **)realloc(encontros[numencontros].amigosencontro, (encontros[numencontros].numamigosencontro + 1) * sizeof(char *));
                    }

                    encontros[numencontros].amigosencontro[encontros[numencontros].numamigosencontro] = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                    strcpy(encontros[numencontros].amigosencontro[encontros[numencontros].numamigosencontro], aux);
                    encontros[numencontros].numamigosencontro++;

                    sep = 0;
                }
                else if (sep == 2)
                {
                    encontros[numencontros].data.dia = atoi(aux);
                }
                else if (sep == 3)
                {
                    encontros[numencontros].data.mes = atoi(aux);
                }
                else if (sep == 4)
                {
                    encontros[numencontros].data.ano = atoi(aux);
                }
                else if (sep == 5)
                {
                    encontros[numencontros].hora.hora = atoi(aux);
                }
                else if (sep == 6)
                {
                    encontros[numencontros].hora.minuto = atoi(aux);
                }
                else if (sep == 7)
                {
                    encontros[numencontros].categoriaencontro = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                    strcpy(encontros[numencontros].categoriaencontro, aux);
                }
                else if (sep == 8)
                {
                    encontros[numencontros].localencontro = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                    strcpy(encontros[numencontros].localencontro, aux);
                }
                else if (sep == 9)
                {
                    encontros[numencontros].descricao = (char *)malloc((strlen(aux) + 1) * sizeof(char));
                    strcpy(encontros[numencontros].descricao, aux);
                }
                sep++;

                if (c == '\n')
                {
                    numencontros++;
                    sep = 0;
                }
            }
        }
    }

    fclose(pArq);
}

void salvaencontros()
{
    FILE *pArq;
    pArq = fopen("encontros.txt", "w");
    if (pArq == NULL)
    {
        printf("ERRO! não foi possível salvar os encontros.\n");
        exit(0);
    }

    for (int i = 0; i < numencontros; i++)
    {

        fprintf(pArq, "%s$", encontros[i].nomeencontro);

        for (int j = 0; j < encontros[i].numamigosencontro; j++)
        {
            fprintf(pArq, "%s@", encontros[i].amigosencontro[j]);
        }

        fprintf(pArq, "%d$%d$%d$", encontros[i].data.dia, encontros[i].data.mes, encontros[i].data.ano);

        fprintf(pArq, "%d$%d$", encontros[i].hora.hora, encontros[i].hora.minuto);

        fprintf(pArq, "%s$", encontros[i].categoriaencontro);

        fprintf(pArq, "%s$", encontros[i].localencontro);

        fprintf(pArq, "%s$", encontros[i].descricao);

        fprintf(pArq, "%c", '\n');
    }

    fclose(pArq);
}
void limpaencontros()
{
    if (numencontros == 0)
    {
        return;
    }
    else
    {
        for (int i = 0; i < numencontros; i++)
        {
            free(encontros[i].nomeencontro);
            for (int j = 0; j < encontros[i].numamigosencontro; j++)
            {
                free(encontros[i].amigosencontro[j]);
            }
            free(encontros[i].amigosencontro);
            free(encontros[i].categoriaencontro);
            free(encontros[i].localencontro);
            free(encontros[i].descricao);
        }
        free(encontros);
    }
}
