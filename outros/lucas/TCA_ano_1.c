
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  ---STRUCTS---

// --/AUXILIARES\--

typedef struct
{
    int dia;
    int mes;
    int ano;
} Tdata;

typedef struct
{
    int hora;
    int min;
} Thora;

typedef struct
{
    char *logradouro;
    int numero;
    char *bairro;
    char *cidade;
    char *estado;

} Tendereco;

// ------------

typedef struct
{
    char *nome;
    Tdata dataNasc;
    char *apelido;
    char *email;
    char *telefone;

} Tamigo;

typedef struct
{
    char *nomeLocal;
    Tendereco endereco;

} Tlocal;

typedef struct
{
    char *nomeCategoria;
} Tcategoria;

typedef struct
{
    Tdata dataEncontro;
    Thora horarioEncontro;
    char **amigoEncontro;
    int numAmigoEncontro;
    Tcategoria categoriaEncontro;
    Tlocal localEncontro;
    char *descricao;

} Tencontro;

//  ---FUNCOES---

//  ----/MENU\---
void MenuPrincipal();
void ProcessarOpc(int opcmenu);

//  ---VALIDACOES---
int ValidaData(int dia, int mes, int ano);
int ValidaHora(int hora, int minuto);

//  ---/AMIGO\---
int MenuAmigo();
void OpcaoAmigo(int opcaux);
Tamigo CadastrarAmigo();
void AlterarAmigo();
void ListarAmigo();
void RemoverAmigo();
void SalvarAmigo();
void RecuperarAmigo();

//  ---/LOCAL\---
int MenuLocal();
void OpcaoLocal(int opcaux);
Tlocal CadastrarLocal();
void AlterarLocal();
void ListarLocal();
void RemoverLocal();
void SalvarLocal();
void RecuperarLocal();

//  -/CATEGORIA\-
int MenuCategoria();
void OpcaoCategoria(int opcaux);
Tcategoria CadastrarCategoria();
void AlterarCategoria();
void ListarCategoria();
void RemoverCategoria();
void SalvarCategoria();
void RecuperarCategoria();

//  --/ENCONTRO\--
int MenuEncontro();
void OpcaoEncontro(int opcaux);
void CadastrarEncontro();
void AlterarEncontro();
void ListarEncontro();
void RemoverEncontro();
void SalvarEncontro();
void RecuperarEncontro();

//  ---/RELATORIO\---
void MenuRelatorio();
void OpcaoRelatorio(int opcaux);
void RelatorioPorCategoria();

//  ---/ARQUIVO\---
void SalvarArquivo();
void RecuperarArquivo();

//  ---/GLOBAIS\---

Tamigo *Gamigo;
int Namigo = 0;

Tlocal *Glocal;
int Nlocal = 0;

Tcategoria *Gcategoria;
int Ncategoria = 0;

Tencontro *Gencontro;
int Nencontro = 0;

int main()
{
    RecuperarArquivo();
    MenuPrincipal();
    return 0;
}

void MenuPrincipal()
{
    int opcmenu = 0;
    system("cls");
    printf(" ______________________\n");
    printf("|----------------------|\n");
    printf("|---------MENU---------|\n");
    printf("|                      |\n");
    printf("| [1] Manter amigo     |\n");
    printf("| [2] Manter local     |\n");
    printf("| [3] Manter categoria |\n");
    printf("| [4] Manter encontro  |\n");
    printf("| [5] Relatorio        |\n");
    printf("| [6] Sair             |\n");
    printf("|______________________|\n\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcmenu);

    if (opcmenu < 1 || opcmenu > 6)
    {
        printf("Opcao invalida!\n");
        system("pause");
        return MenuPrincipal();
    }
    ProcessarOpc(opcmenu);
}

void ProcessarOpc(int opcmenu)
{
    int opcaux = 0;
    switch (opcmenu)
    {
    case 1:
        opcaux = MenuAmigo();
        OpcaoAmigo(opcaux);
        break;
    case 2:
        opcaux = MenuLocal();
        OpcaoLocal(opcaux);
        break;
    case 3:
        opcaux = MenuCategoria();
        OpcaoCategoria(opcaux);
        break;
    case 4:
        opcaux = MenuEncontro();
        OpcaoEncontro(opcaux);
        break;
    case 5:
        MenuRelatorio();
        break;
    case 6:
        SalvarArquivo();
        break;
    }
    MenuPrincipal();
}

int MenuAmigo()
{
    int opcaux;
    system("cls");
    printf(" ______________________\n");
    printf("|----------------------|\n");
    printf("|------MENU AMIGO------|\n");
    printf("|                      |\n");
    printf("| [1] Cadastrar        |\n");
    printf("| [2] Alterar          |\n");
    printf("| [3] listar           |\n");
    printf("| [4] Excluir          |\n");
    printf("|______________________|\n\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcaux);

    if (opcaux < 1 || opcaux > 4)
    {
        printf("Opcao invalida!\n");
        system("pause");
        return MenuAmigo();
    }

    return opcaux;
}

void OpcaoAmigo(int opcaux)
{
    switch (opcaux)
    {
    case 1:
        CadastrarAmigo();
        break;
    case 2:
        AlterarAmigo();
        break;
    case 3:
        ListarAmigo();
        break;
    case 4:
        RemoverAmigo();
        break;
    }
    return;
}

Tamigo CadastrarAmigo()
{
    Tamigo a;
    char straux[100];
    int dia, mes, ano;

    if (Namigo == 0)
    {
        Gamigo = (Tamigo *)malloc(sizeof(Tamigo));
    }
    else
    {
        Gamigo = (Tamigo *)realloc(Gamigo, (Namigo + 1) * sizeof(Tamigo));
    }
    fflush(stdin);
    system("cls");
    printf("---Cadastrar amigo---\n\n\n");

    printf("Digite o nome do amigo: ");
    gets(straux);
    a.nome = (char *)malloc((strlen(straux) + 1) * sizeof(char));
    strcpy(a.nome, straux);
    fflush(stdin);

    printf("Digite o apelido do amigo: ");
    gets(straux);
    a.apelido = (char *)malloc((strlen(straux) + 1) * sizeof(char));
    strcpy(a.apelido, straux);
    fflush(stdin);

    printf("Digite o telefone do amigo: ");
    gets(straux);
    a.telefone = (char *)malloc((strlen(straux) + 1) * sizeof(char));
    strcpy(a.telefone, straux);
    fflush(stdin);

    printf("Digite o email do amigo: ");
    gets(straux);
    a.email = (char *)malloc((strlen(straux) + 1) * sizeof(char));
    strcpy(a.email, straux);
    fflush(stdin);


    while (1)
    {
        system("cls");
        printf("---Digite a data de nascimento---\n\n");

        printf("Digite o dia: ");
        scanf("%d", &dia);
        printf("Digite o mes: ");
        scanf("%d", &mes);
        printf("Digite o ano: ");
        scanf("%d", &ano);

        if (ValidaData(dia, mes, ano) == 0)
        {
            printf("Data invalida! Tente novamente.\n");
            system("pause");
        }
        else
        {
            a.dataNasc.dia = dia;
            a.dataNasc.mes = mes;
            a.dataNasc.ano = ano;
            break; 
        }
    }

    Gamigo[Namigo] = a;
    Namigo++; 

    printf("Amigo cadastrado com sucesso!\n");
    system("pause");

    return a;
}

void AlterarAmigo()
{
    int opcamg = 0, opcaux = 0, opcaux2 = 0;
    char straux[100];
    int dia, ano, mes;
    fflush(stdin);
    system("cls");
    printf("o numero de amigos é %d\n", Namigo);
    if (Namigo == 0)
    {
        printf("Nenhum amigo cadastrado!\n");
        printf("Deseja cadastrar um amigo? (1) Sim (2) Nao: ");
        scanf("%d", &opcaux2);
        if (opcaux2 == 2)
        {
            MenuAmigo();
        }
        else
        {
            CadastrarAmigo();
        }
    }

    printf("---Alterar amigo---\n\n");

    printf("Qual amigo deseja alterar?\n");
    for (int i = 0; i < Namigo; i++)
    {
        printf("Amigo [%d]: %s\n", i + 1, Gamigo[i].nome);
    }
    printf("Digite o numero do amigo: ");
    scanf("%d", &opcamg);
    if (opcamg > Namigo || opcamg < 1)
    {
        printf("Opcao invalida!\n");
        system("pause");
        AlterarAmigo();
    }
    opcamg--;
    system("cls");
    printf("---oque deseja alterar no amigo?---\n");
    printf("[1] - Nome\n");
    printf("[2] - Apelido\n");
    printf("[3] - Telefone\n");
    printf("[4] - Email\n");
    printf("[5] - Data de Nascimento\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcaux);
    if (opcaux > 5 || opcaux < 1)
    {
        printf("Opcao invalida!\n");
        system("pause");
        AlterarAmigo();
    }

    switch (opcaux)
    {
    case 1:
        fflush(stdin);
        printf("Digite o novo nome: ");
        gets(straux);
        Gamigo[opcamg].nome = (char *)realloc(Gamigo[opcamg].nome, (strlen(straux) + 1) * sizeof(char));
        strcpy(Gamigo[opcamg].nome, straux);
        break;
    case 2:
        fflush(stdin);
        printf("Digite o novo apelido: ");
        gets(straux);
        Gamigo[opcamg].apelido = (char *)realloc(Gamigo[opcamg].apelido, (strlen(straux) + 1) * sizeof(char));
        strcpy(Gamigo[opcamg].apelido, straux);
        break;
    case 3:
        fflush(stdin);
        printf("Digite o novo telefone: ");
        gets(straux);
        Gamigo[opcamg].telefone = (char *)realloc(Gamigo[opcamg].telefone, (strlen(straux) + 1) * sizeof(char));
        strcpy(Gamigo[opcamg].telefone, straux);
        break;
    case 4:
        fflush(stdin);
        printf("Digite o novo email: ");
        gets(straux);
        Gamigo[opcamg].email = (char *)realloc(Gamigo[opcamg].email, (strlen(straux) + 1) * sizeof(char));
        strcpy(Gamigo[opcamg].email, straux);
        break;
    case 5:
        system("cls");
        printf("---Digite a nova data de nascimento---\n\n");
        printf("Digite o dia: ");
        scanf("%d", &dia);
        printf("Digite o mes: ");
        scanf("%d", &mes);
        printf("Digite o ano: ");
        scanf("%d", &ano);
        if (ValidaData(dia, mes, ano) == 0)
        {
            printf("Data invalida!\n");
            system("pause");
            AlterarAmigo();
        }
        else
        {
            Gamigo[opcamg].dataNasc.dia = dia;
            Gamigo[opcamg].dataNasc.mes = mes;
            Gamigo[opcamg].dataNasc.ano = ano;
        }

        break;
    }
    system("pause");
    MenuPrincipal();
}

void ListarAmigo()
{
    int opcamg = 0, opcaux = 0;
    system("cls");
    printf("---Amigos cadastrados---\n\n");

    if (Namigo == 0)
    {
        printf("Nenhum amigo cadastrado!\n");
        printf("Deseja cadastrar um amigo? (1) Sim (2) Nao: ");
        scanf("%d", &opcaux);
        if (opcaux == 1)
        {
            CadastrarAmigo();
        }
        MenuPrincipal();
    }

    printf(" Qual amigo voce deseja visualizar?\n");
    for (int i = 0; i < Namigo; i++)
    {
        printf("Amigo [%d]: %s\n", i + 1, Gamigo[i].nome);
    }
    printf("Digite o numero do amigo: ");
    scanf("%d", &opcamg);
    if (opcamg > Namigo || opcamg < 1)
    {
        printf("Opcao invalida!\n");
        system("pause");
        ListarAmigo();
    }
    opcamg--;
    system("cls");
    printf("Nome: %s\n", Gamigo[opcamg].nome);
    printf("Apelido: %s\n", Gamigo[opcamg].apelido);
    printf("Telefone: %s\n", Gamigo[opcamg].telefone);
    printf("Email: %s\n", Gamigo[opcamg].email);
    printf("Data de Nascimento: %d/%d/%d\n", Gamigo[opcamg].dataNasc.dia, Gamigo[opcamg].dataNasc.mes, Gamigo[opcamg].dataNasc.ano);
    system("pause");
    MenuPrincipal();
}

void RemoverAmigo()
{
    int opcamg = 0, opcaux = 0, opcaux2 = 0;

    if (Namigo == 0)
    {
        printf("Nenhum amigo cadastrado!\n");
        printf("Deseja cadastrar um amigo? (1) Sim (2) Nao: ");
        scanf("%d", &opcaux2);

        if (opcaux2 == 1)
        {
            CadastrarAmigo();
        }
        MenuPrincipal();
        return;
    }

    system("cls");
    printf("---Remover amigo---\n\n");
    printf("Qual amigo voce deseja remover?\n");

    for (int i = 0; i < Namigo; i++)
    {
        printf("Amigo [%d]: %s\n", i + 1, Gamigo[i].nome);
    }

    printf("Digite o numero do amigo: ");
    scanf("%d", &opcamg);

    if (opcamg < 1 || opcamg > Namigo)
    {
        printf("Opcao invalida!\n");
        system("pause");
        return RemoverAmigo();
    }

    system("cls");
    opcamg--;
    for (int i = 0; i < Nencontro; i++)
    {
        for (int j = 0; j < Gencontro[i].numAmigoEncontro; j++)
        {

            if (strcmp(Gamigo[opcamg].nome, Gencontro[i].amigoEncontro[j]) == 0)
            {
                printf("O amigo %s esta cadastrado em um encontro!\n", Gamigo[opcamg].nome);
                printf("Voce nao pode remover um amigo que esta em um encontro!\n");
                system("pause");
                MenuPrincipal();
            }
        }
    }

    printf("Voce deseja realmente remover o amigo %s?\n", Gamigo[opcamg].nome);
    printf("(1) Sim (2) Nao: ");
    scanf("%d", &opcaux);

    if (opcaux < 1 || opcaux > 2)
    {
        printf("Opcao invalida!\n");
        system("pause");
        return RemoverAmigo();
    }

    if (opcaux == 2)
    {
        MenuPrincipal();
        return;
    }

    if (Namigo == 1)
    {
        free(Gamigo);
        Gamigo = NULL;
    }
    else
    {
        for (int i = opcamg; i < Namigo - 1; i++)
        {
            Gamigo[i] = Gamigo[i + 1];
        }

        Tamigo *temp = (Tamigo *)realloc(Gamigo, (Namigo - 1) * sizeof(Tamigo));
        if (temp == NULL && Namigo > 1)
        {
            printf("Erro ao realocar memoria!\n");
            system("pause");
            return;
        }
        Gamigo = temp;
    }

    Namigo--;
    printf("Amigo removido com sucesso!\n");
    system("pause");
    MenuPrincipal();
}
void SalvarAmigo()
{
    FILE *arquivo = fopen("amigosTCA.txt", "w");
    for (int i = 0; i < Namigo; i++)
    {
        fprintf(arquivo, "%s\n", Gamigo[i].nome);
        fprintf(arquivo, "%s\n", Gamigo[i].apelido);
        fprintf(arquivo, "%s\n", Gamigo[i].telefone);
        fprintf(arquivo, "%s\n", Gamigo[i].email);
        fprintf(arquivo, "%d\n", Gamigo[i].dataNasc.dia);
        fprintf(arquivo, "%d\n", Gamigo[i].dataNasc.mes);
        fprintf(arquivo, "%d\n", Gamigo[i].dataNasc.ano);
    }
    fclose(arquivo);
}

void RecuperarAmigo()
{
    char c, straux[100];
    int i = 0;
    int sep = 0;
    FILE *arquivo = fopen("amigosTCA.txt", "r");
    if (arquivo)
    {
        while (!feof(arquivo))
        {
            c = fgetc(arquivo);
            if (c != '\n')
            {
                straux[i++] = c;
            }
            else
            {
                straux[i] = '\0';
                i = 0;
                switch (sep)
                {
                case 0:
                    if (Namigo == 0)
                    {
                        Gamigo = (Tamigo *)malloc(sizeof(Tamigo));
                    }
                    else
                    {
                        Gamigo = (Tamigo *)realloc(Gamigo, (Namigo + 1) * sizeof(Tamigo));
                    }
                    Gamigo[Namigo].nome = (char *)malloc((strlen(straux) + 1) * sizeof(char));
                    strcpy(Gamigo[Namigo].nome, straux);
                    sep++;
                    break;
                case 1:
                    Gamigo[Namigo].apelido = (char *)malloc((strlen(straux) + 1) * sizeof(char));
                    strcpy(Gamigo[Namigo].apelido, straux);
                    sep++;
                    break;
                case 2:
                    Gamigo[Namigo].telefone = (char *)malloc((strlen(straux) + 1) * sizeof(char));
                    strcpy(Gamigo[Namigo].telefone, straux);
                    sep++;
                    break;
                case 3:
                    Gamigo[Namigo].email = (char *)malloc((strlen(straux) + 1) * sizeof(char));
                    strcpy(Gamigo[Namigo].email, straux);
                    sep++;
                    break;
                case 4:
                    Gamigo[Namigo].dataNasc.dia = atoi(straux);
                    sep++;
                    break;
                case 5:
                    Gamigo[Namigo].dataNasc.mes = atoi(straux);
                    sep++;
                    break;
                case 6:
                    Gamigo[Namigo].dataNasc.ano = atoi(straux);
                    sep = 0;
                    Namigo++;
                    break;
                }
            }
        }
        fclose(arquivo);
    }
}

int MenuLocal()
{
    int opcaux;
    system("cls");
    printf(" ______________________\n");
    printf("|----------------------|\n");
    printf("|------MENU LOCAL------|\n");
    printf("|                      |\n");
    printf("| [1] Cadastrar        |\n");
    printf("| [2] Alterar          |\n");
    printf("| [3] Listar           |\n");
    printf("| [4] Excluir          |\n");
    printf("|______________________|\n\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcaux);

    if (opcaux < 1 || opcaux > 4)
    {
        printf("Opcao invalida!\n");
        system("pause");
        return MenuLocal(); 
    }

    return opcaux;
}

void OpcaoLocal(int opcaux)
{
    switch (opcaux)
    {
    case 1:
        CadastrarLocal();
        break;
    case 2:
        AlterarLocal();
        break;
    case 3:
        ListarLocal();
        break;
    case 4:
        RemoverLocal();
        break;
    }
    MenuPrincipal();
}

Tlocal CadastrarLocal()
{
    Tlocal a;
    char straux[100];
    if (Nlocal == 0)
    {
        Glocal = (Tlocal *)malloc(sizeof(Tlocal));
    }
    else
    {
        Glocal = (Tlocal *)realloc(Glocal, (Nlocal + 1) * sizeof(Tlocal));
    }
    fflush(stdin);
    system("cls");
    printf("---Cadastrar local---\n\n");
    printf("Digite o nome do local: ");
    gets(straux);
    a.nomeLocal = (char *)malloc((strlen(straux) + 1) * sizeof(char));
    strcpy(a.nomeLocal, straux);
    fflush(stdin);

    printf("Digite o logradouro do local: ");
    gets(straux);
    a.endereco.logradouro = (char *)malloc((strlen(straux) + 1) * sizeof(char));
    strcpy(a.endereco.logradouro, straux);
    fflush(stdin);

    printf("Digite o numero do local: ");
    scanf("%d", &a.endereco.numero);
    fflush(stdin);

    printf("Digite o bairro do local: ");
    gets(straux);
    a.endereco.bairro = (char *)malloc((strlen(straux) + 1) * sizeof(char));
    strcpy(a.endereco.bairro, straux);
    fflush(stdin);

    printf("Digite a cidade do local: ");
    gets(straux);
    a.endereco.cidade = (char *)malloc((strlen(straux) + 1) * sizeof(char));
    strcpy(a.endereco.cidade, straux);
    fflush(stdin);

    printf("Digite o estado do local: ");
    gets(straux);
    a.endereco.estado = (char *)malloc((strlen(straux) + 1) * sizeof(char));
    strcpy(a.endereco.estado, straux);
    fflush(stdin);

    Glocal[Nlocal] = a;
    printf("Local cadastrado com sucesso!\n");
    system("pause");
    Nlocal++;
    return a;
}

void AlterarLocal()
{
    int opcloc = 0, opcaux = 0, opcaux2 = 0;
    char straux[100];
    if (Nlocal == 0)
    {
        printf("Nenhum local cadastrado!\n");
        printf("Deseja cadastrar um local? (1) Sim (2) Nao: ");
        scanf("%d", &opcaux2);
        if (opcaux2 == 2)
        {
            MenuPrincipal();
        }
        else
        {
            CadastrarLocal();
        }
    }
    system("cls");
    printf("---Alterar local---\n\n");
    printf("Qual local deseja alterar?\n");
    for (int i = 0; i < Nlocal; i++)
    {
        printf("local [%d] - %s\n", i + 1, Glocal[i].nomeLocal);
    }
    printf("Digite o numero do local: ");
    scanf("%d", &opcloc);
    if (opcloc > Nlocal || opcloc < 1)
    {
        printf("Opcao invalida!\n");
        system("pause");
        AlterarLocal();
    }
    opcloc--;
    system("cls");
    printf("---Alterar local [%s]---\n\n", Glocal[opcloc].nomeLocal);
    printf("Escolha a opcao para alterar:\n");
    printf("[1] Nome\n");
    printf("[2] Logradouro\n");
    printf("[3] Numero\n");
    printf("[4] Bairro\n");
    printf("[5] Cidade\n");
    printf("[6] Estado\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcaux);
    if (opcaux < 1 || opcaux > 6)
    {
        printf("Opcao invalida!\n");
        system("pause");
        AlterarLocal();
    }
    switch (opcaux)
    {
    case 1:
        fflush(stdin);
        printf("Digite o novo nome do local: ");
        gets(straux);
        Glocal[opcloc].nomeLocal = (char *)malloc((strlen(straux) + 1) * sizeof(char));
        strcpy(Glocal[opcloc].nomeLocal, straux);
        break;
    case 2:
        fflush(stdin);
        printf("Digite o novo logradouro do local: ");
        gets(straux);
        Glocal[opcloc].endereco.logradouro = (char *)malloc((strlen(straux) + 1) * sizeof(char));
        strcpy(Glocal[opcloc].endereco.logradouro, straux);
        break;
    case 3:
        fflush(stdin);
        printf("Digite o novo numero do local: ");
        scanf("%d", &Glocal[opcloc].endereco.numero);
        break;
    case 4:
        fflush(stdin);
        printf("Digite o novo bairro do local: ");
        gets(straux);
        Glocal[opcloc].endereco.bairro = (char *)malloc((strlen(straux) + 1) * sizeof(char));
        strcpy(Glocal[opcloc].endereco.bairro, straux);
        break;
    case 5:
        fflush(stdin);
        printf("Digite a nova cidade do local: ");
        gets(straux);
        Glocal[opcloc].endereco.cidade = (char *)malloc((strlen(straux) + 1) * sizeof(char));
        strcpy(Glocal[opcloc].endereco.cidade, straux);
        break;
    case 6:
        fflush(stdin);
        printf("Digite o novo estado do local: ");
        gets(straux);
        Glocal[opcloc].endereco.estado = (char *)malloc((strlen(straux) + 1) * sizeof(char));
        strcpy(Glocal[opcloc].endereco.estado, straux);
        break;
    }
    printf("Alteracao efetuada com sucesso!\n");
    system("pause");
    MenuPrincipal();
}

void ListarLocal()
{
    int opcaux = 0, opcaux2 = 0;
    if (Nlocal == 0)
    {
        printf("Nenhum local cadastrado!\n");
        printf("Deseja cadastrar um local? (1) Sim (2) Nao: ");
        scanf("%d", &opcaux2);
        if (opcaux2 == 2)
        {
            MenuPrincipal();
        }
        else
        {
            CadastrarLocal();
        }
    }
    system("cls");
    printf("---Listar local---\n");
    for (int i = 0; i < Nlocal; i++)
    {
        printf("local [%d] - %s\n", i + 1, Glocal[i].nomeLocal);
    }
    printf("Digite o numero do local: \n");
    scanf("%d", &opcaux);
    if (opcaux > Nlocal || opcaux < 1)
    {
        printf("Opcao invalida!\n");
        system("pause");
        ListarLocal();
    }
    opcaux--;
    system("cls");
    printf("---Local [%s]---\n\n", Glocal[opcaux].nomeLocal);
    printf("Logradouro: %s\n", Glocal[opcaux].endereco.logradouro);
    printf("Numero: %d\n", Glocal[opcaux].endereco.numero);
    printf("Bairro: %s\n", Glocal[opcaux].endereco.bairro);
    printf("Cidade: %s\n", Glocal[opcaux].endereco.cidade);
    printf("Estado: %s\n", Glocal[opcaux].endereco.estado);
    system("pause");
    MenuPrincipal();
}

void RemoverLocal()
{
    int opcaux = 0, opcaux2 = 0;

    if (Nlocal == 0)
    {
        printf("Nenhum local cadastrado!\n");
        printf("Deseja cadastrar um local? (1) Sim (2) Nao: ");
        scanf("%d", &opcaux2);

        if (opcaux2 == 2)
        {
            MenuPrincipal();
            return;
        }
        else
        {
            CadastrarLocal();
            return;
        }
    }

    system("cls");
    printf("---Remover local---\n");
    for (int i = 0; i < Nlocal; i++)
    {
        printf("Local [%d] - %s\n", i + 1, Glocal[i].nomeLocal);
    }

    printf("Digite o numero do local: ");
    scanf("%d", &opcaux);

    if (opcaux < 1 || opcaux > Nlocal)
    {
        printf("Opcao invalida!\n");
        system("pause");
        return RemoverLocal();
    }

    opcaux--; 
    printf("Voce deseja realmente remover o local %s? (1) Sim (2) Nao: ", Glocal[opcaux].nomeLocal);
    scanf("%d", &opcaux2);

    if (opcaux2 < 1 || opcaux2 > 2)
    {
        printf("Opcao invalida!\n");
        system("pause");
        return RemoverLocal();
    }

    if (opcaux2 == 2)
    {
        MenuPrincipal();
        return;
    }

   
    if (Nlocal == 1)
    {
        free(Glocal);
        Glocal = NULL; 
    }
    else
    {
        for (int i = opcaux; i < Nlocal - 1; i++)
        {
            Glocal[i] = Glocal[i + 1];
        }

        
        Glocal = (Tlocal *)realloc(Glocal, (Nlocal - 1) * sizeof(Tlocal));
        if (Glocal == NULL && Nlocal > 1)
        {
            printf("Erro ao realocar memoria!\n");
            system("pause");
            return;
        }
    }

    Nlocal--;
    printf("Local removido com sucesso!\n");
    system("pause");
    MenuPrincipal();
}
void SalvarLocal()
{
    FILE *arquivo = fopen("locaisTCA.txt", "w");
    for (int i = 0; i < Nlocal; i++)
    {
        fprintf(arquivo, "%s\n", Glocal[i].nomeLocal);
        fprintf(arquivo, "%s\n", Glocal[i].endereco.logradouro);
        fprintf(arquivo, "%d\n", Glocal[i].endereco.numero);
        fprintf(arquivo, "%s\n", Glocal[i].endereco.bairro);
        fprintf(arquivo, "%s\n", Glocal[i].endereco.cidade);
        fprintf(arquivo, "%s\n", Glocal[i].endereco.estado);
    }
    fclose(arquivo);
}

void RecuperarLocal()
{
    char c, straux[100];
    int i = 0;
    int sep = 0;
    FILE *arquivo = fopen("locaisTCA.txt", "r");
    if (arquivo)
    {
        while (!feof(arquivo))
        {
            c = fgetc(arquivo);
            if (c != '\n')
            {
                straux[i++] = c;
            }
            else
            {
                straux[i] = '\0';
                i = 0;
                switch (sep)
                {
                case 0:
                    if (Nlocal == 0)
                    {
                        Glocal = (Tlocal *)malloc(sizeof(Tlocal));
                    }
                    else
                    {
                        Glocal = (Tlocal *)realloc(Glocal, (Nlocal + 1) * sizeof(Tlocal));
                    }
                    Glocal[Nlocal].nomeLocal = (char *)malloc((strlen(straux) + 1) * sizeof(char));
                    strcpy(Glocal[Nlocal].nomeLocal, straux);
                    sep++;
                    break;
                case 1:
                    Glocal[Nlocal].endereco.logradouro = (char *)malloc((strlen(straux) + 1) * sizeof(char));
                    strcpy(Glocal[Nlocal].endereco.logradouro, straux);
                    sep++;
                    break;
                case 2:
                    Glocal[Nlocal].endereco.numero = atoi(straux);
                    sep++;
                    break;
                case 3:
                    Glocal[Nlocal].endereco.bairro = (char *)malloc((strlen(straux) + 1) * sizeof(char));
                    strcpy(Glocal[Nlocal].endereco.bairro, straux);
                    sep++;
                    break;
                case 4:
                    Glocal[Nlocal].endereco.cidade = (char *)malloc((strlen(straux) + 1) * sizeof(char));
                    strcpy(Glocal[Nlocal].endereco.cidade, straux);
                    sep++;
                    break;
                case 5:
                    Glocal[Nlocal].endereco.estado = (char *)malloc((strlen(straux) + 1) * sizeof(char));
                    strcpy(Glocal[Nlocal].endereco.estado, straux);
                    sep = 0;
                    Nlocal++;
                    break;
                }
            }
        }
        fclose(arquivo);
    }
}

int MenuCategoria()
{
    int opcaux;
    system("cls");
    printf(" ______________________\n");
    printf("|----------------------|\n");
    printf("|----MENU CATEGORIA----|\n");
    printf("|                      |\n");
    printf("| [1] Cadastrar        |\n");
    printf("| [2] Alterar          |\n");
    printf("| [3] Listar           |\n");
    printf("| [4] Excluir          |\n");
    printf("|______________________|\n\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcaux);


    if (opcaux < 1 || opcaux > 4)
    {
        printf("Opcao invalida!\n");
        system("pause");
        return MenuCategoria();
    }

    return opcaux;
}

void OpcaoCategoria(int opcaux)
{
    switch (opcaux)
    {
    case 1:
        CadastrarCategoria();
        break;
    case 2:
        AlterarCategoria();
        break;
    case 3:
        ListarCategoria();
        break;
    case 4:
        RemoverCategoria();
        break;
    }

    MenuPrincipal();
}

Tcategoria CadastrarCategoria()
{
    Tcategoria a;
    char straux[100];
    if (Ncategoria == 0)
    {
        Gcategoria = (Tcategoria *)malloc(sizeof(Tcategoria));
    }
    else
    {
        Gcategoria = (Tcategoria *)realloc(Gcategoria, (Ncategoria + 1) * sizeof(Tcategoria));
    }
    system("cls");
    printf("--- Cadastrar categoria ---\n\n");
    printf("Nome da categoria: ");
    fflush(stdin);
    gets(straux);
    a.nomeCategoria = (char *)malloc((strlen(straux) + 1) * sizeof(char));
    strcpy(a.nomeCategoria, straux);

    Gcategoria[Ncategoria] = a;
    Ncategoria++;
    printf("Categoria cadastrada com sucesso!\n");
    system("pause");
    return a;
}

void AlterarCategoria()
{
    int opcaux2 = 0, opcaux = 0;
    char straux[100];
    system("cls");
    if (Ncategoria == 0)
    {
        printf("Nenhuma categoria cadastrada!\n");
        printf("Deseja cadastrar uma categoria? (1) Sim (2) Nao: ");
        scanf("%d", &opcaux);
        if (opcaux == 2)
        {
            MenuPrincipal();
        }
        else
        {
            CadastrarCategoria();
        }
    }
    system("cls");
    printf("---Alterar categoria---\n\n");
    printf("Qual categoria deseja alterar?\n");
    for (int i = 0; i < Ncategoria; i++)
    {
        printf("[%d] - %s\n", i + 1, Gcategoria[i].nomeCategoria);
    }
    printf("Digite o numero da categoria: ");
    scanf("%d", &opcaux2);
    if (opcaux2 < 1 || opcaux2 > Ncategoria)
    {
        printf("Opcao invalida!\n");
        system("pause");
        return AlterarCategoria();
    }
    opcaux2--;
    system("cls");
    printf("---Alterar categoria [%s]---\n\n", Gcategoria[opcaux].nomeCategoria);
    printf("Novo nome da categoria: ");
    fflush(stdin);
    gets(straux);
    Gcategoria[opcaux2].nomeCategoria = (char *)malloc((strlen(straux) + 1) * sizeof(char));
    strcpy(Gcategoria[opcaux2].nomeCategoria, straux);
    fflush(stdin);
    printf("Categoria alterada com sucesso!\n");
    system("pause");
    MenuPrincipal();
}

void ListarCategoria()
{
    int aux2 = 0;
    system("cls");
    if (Ncategoria == 0)
    {
        printf("Nenhuma categoria cadastrada!\n");
        printf("Deseja cadastrar uma categoria? (1) Sim (2) Nao: ");
        scanf("%d", &aux2);
        if (aux2 == 2)
        {
            MenuPrincipal();
        }
        else
        {
            CadastrarCategoria();
        }
    }

    system("cls");
    printf("---Listar categoria---\n\n");
    for (int i = 0; i < Ncategoria; i++)
    {
        printf("[%d] - Nome: %s\n", i + 1, Gcategoria[i].nomeCategoria);
    }
    system("pause");
    MenuPrincipal();
}

void RemoverCategoria()
{
    int opcaux2 = 0, opcaux = 0;
    system("cls");
    if (Ncategoria == 0)
    {
        printf("Nenhuma categoria cadastrada!\n");
        printf("Deseja cadastrar uma categoria? (1) Sim (2) Nao: ");
        scanf("%d", &opcaux2);
        if (opcaux2 == 2)
        {
            MenuPrincipal();
        }
        else
        {
            CadastrarCategoria();
        }
    }
    system("cls");
    printf("---Remover categoria---\n\n");
    printf("Qual categoria deseja remover?\n");
    for (int i = 0; i < Ncategoria; i++)
    {
        printf("[%d] - %s\n", i + 1, Gcategoria[i].nomeCategoria);
    }
    printf("Digite o numero da categoria: ");
    scanf("%d", &opcaux);
    if (opcaux < 1 || opcaux > Ncategoria)
    {
        printf("Opcao invalida!\n");
        system("pause");
        return RemoverCategoria(); 
    }
    opcaux--;
    printf("Voce deseja realmente remover a categoria %s? (1) Sim (2) Nao: ", Gcategoria[opcaux].nomeCategoria);
    scanf("%d", &opcaux2);
    if (opcaux2 < 1 || opcaux2 > 2)
    {
        printf("Opcao invalida!\n");
        system("pause");
        return RemoverCategoria(); 
    }
    if (opcaux2 == 2)
    {
        MenuPrincipal();
    }
    if (Ncategoria == 1)
    {
        free(Gcategoria);
        Gcategoria = NULL;
    }
    else
    {
        for (int i = opcaux; i < Ncategoria - 1; i++)
        {
            Gcategoria[i] = Gcategoria[i + 1];
        }
        Gcategoria = (Tcategoria *)realloc(Gcategoria, (Ncategoria - 1) * sizeof(Tcategoria));
        if (Gcategoria == NULL)
        {
            printf("Erro ao remover categoria!\n");
            system("pause");
            return;
        }
    }
    Ncategoria--;
    printf("Categoria removida com sucesso!\n");
    system("pause");
    MenuPrincipal();
}

void SalvarCategoria()
{
    FILE *arquivo = fopen("categoriaTCA.txt", "w");
    for (int i = 0; i < Ncategoria; i++)
    {
        fprintf(arquivo, "%s\n", Gcategoria[i].nomeCategoria);
    }
    fclose(arquivo);
}

void RecuperarCategoria()
{
    char c, straux[100];
    int i = 0;
    FILE *arquivo = fopen("categoriaTCA.txt", "r");
    if (arquivo)
    {
        while (!feof(arquivo))
        {
            c = fgetc(arquivo);
            if (c != '\n')
            {
                straux[i++] = c;
            }
            else
            {
                straux[i] = '\0';
                i = 0;
                if (Ncategoria == 0)
                {
                    Gcategoria = (Tcategoria *)malloc(sizeof(Tcategoria));
                }
                else
                {
                    Gcategoria = (Tcategoria *)realloc(Gcategoria, (Ncategoria + 1) * sizeof(Tcategoria));
                }
                Gcategoria[Ncategoria].nomeCategoria = (char *)malloc((strlen(straux) + 1) * sizeof(char));
                strcpy(Gcategoria[Ncategoria].nomeCategoria, straux);
                Ncategoria++;
            }
        }
        fclose(arquivo);
    }
}

int MenuEncontro()
{
    int opcaux;
    system("cls");
    printf(" ______________________\n");
    printf("|----------------------|\n");
    printf("|----MENU ENCONTRO-----|\n");
    printf("|                      |\n");
    printf("| [1] Cadastrar        |\n");
    printf("| [2] Alterar          |\n");
    printf("| [3] Listar           |\n");
    printf("| [4] Excluir          |\n");
    printf("|______________________|\n\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcaux);

    
    if (opcaux < 1 || opcaux > 4)
    {
        printf("Opcao invalida!\n");
        system("pause");
        return MenuEncontro();
    }

    return opcaux;
}

void OpcaoEncontro(int opcaux)
{
    switch (opcaux)
    {
    case 1:
        CadastrarEncontro();
        break;
    case 2:
        AlterarEncontro();
        break;
    case 3:
        ListarEncontro();
        break;
    case 4:
        RemoverEncontro();
        break;
    }
}

void CadastrarEncontro()
{
    int opcerro, opcaux, opcesc = 0, auxhora = 0, dia = 0, mes = 0, ano = 0;
    int opcdo = 0;
    char straux[100];
    if (Nencontro == 0)
    {
        Gencontro = (Tencontro *)malloc(1 * sizeof(Tencontro));
    }
    else
    {
        Gencontro = (Tencontro *)realloc(Gencontro, (Nencontro + 1) * sizeof(Tencontro));
    }
    Tencontro a;
    a.numAmigoEncontro = 0;
    system("cls");
    if (Namigo == 0)
    {
        printf("Nenhum amigo cadastrado!\n");
        printf("Voce nao pode cadastrar um encontro sem amigos!\n\n");
        printf("Deseja cadastrar um amigo? (1) Sim (2) Nao: ");
        scanf("%d", &opcerro);
        if (opcerro < 1 || opcerro > 2)
        {
            printf("Opcao invalida!\n");
            system("pause");
            return CadastrarEncontro();
        }
        if (opcerro == 2)
        {
            MenuPrincipal();
        }
        else
        {
            CadastrarAmigo();
        }
    }
    opcerro = 0;
    system("cls");
    if (Nlocal == 0)
    {
        printf("Nenhum local cadastrado!\n");
        printf("Voce nao pode cadastrar um encontro sem locais!\n\n");
        printf("Deseja cadastrar um local? (1) Sim (2) Nao: ");
        scanf("%d", &opcerro);
        if (opcerro < 1 || opcerro > 2)
        {
            printf("Opcao invalida!\n");
            system("pause");
            return CadastrarEncontro();
        }
        if (opcerro == 2)
        {
            MenuPrincipal();
        }
        else
        {
            CadastrarLocal();
        }
    }
    opcerro = 0;
    system("cls");
    if (Ncategoria == 0)
    {
        printf("Nenhuma categoria cadastrada!\n");
        printf("Voce nao pode cadastrar um encontro sem categorias!\n\n");
        printf("Deseja cadastrar uma categoria? (1) Sim (2) Nao: ");
        scanf("%d", &opcerro);
        if (opcerro < 1 || opcerro > 2)
        {
            printf("Opcao invalida!\n");
            system("pause");
            return CadastrarEncontro();
        }
        if (opcerro == 2)
        {
            MenuPrincipal();
        }
        else
        {
            CadastrarCategoria();
        }
    }

    do
    {
        if (a.numAmigoEncontro == Namigo)
        {
            printf("voce ja cadastrou todos os amigos!\n");
            system("pause");
            break;
        }
        system("cls");
        printf(" ---Cadastrar encontro---\n\n");
        printf("Escolha o amigo para adicionar ao encontro: \n");
        for (int i = 0; i < Namigo; i++)
        {
            printf("[%d] %s\n", i + 1, Gamigo[i].nome);
        }
        printf("Digite o numero do amigo: ");
        scanf(" %d", &opcaux);
        if (opcaux < 1 || opcaux > Namigo)
        {
            printf("Opcao invalida!\n");
            system("pause");
            continue;
        }
        opcaux--;

        int jaAdicionado = 0;
        for (int i = 0; i < a.numAmigoEncontro; i++)
        {
            if (strcmp(a.amigoEncontro[i], Gamigo[opcaux].nome) == 0)
            {
                jaAdicionado = 1;
                break;
            }
        }

        if (jaAdicionado)
        {
            printf("Este amigo ja foi adicionado ao encontro!\n");
            system("pause");
            continue;
        }

        if (a.numAmigoEncontro == 0)
        {
            a.amigoEncontro = (char **)malloc(sizeof(char *));
        }
        else
        {
            a.amigoEncontro = (char **)realloc(a.amigoEncontro, (a.numAmigoEncontro + 1) * sizeof(char *));
        }
        a.amigoEncontro[a.numAmigoEncontro] = (char *)malloc((strlen(Gamigo[opcaux].nome) + 1) * sizeof(char));

        fflush(stdin);
        strcpy(a.amigoEncontro[a.numAmigoEncontro], Gamigo[opcaux].nome);
        fflush(stdin);
        a.numAmigoEncontro++;
        opcaux = 0;
        printf("Deseja adicionar mais amigos? (1) Sim (2) Nao: ");
        scanf("%d", &opcesc);
        if (opcesc < 1 || opcesc > 2)
        {
            printf("Opcao invalida!\n");
            system("pause");
            continue;
        }
        if (opcesc == 2)
        {
            opcdo = 1;
        }
    } while (opcdo == 0);

    system("cls");
    printf(" ---Cadastrar encontro--- \n\n");
    printf("Escolha o local para adicionar ao encontro: \n");
    for (int i = 0; i < Nlocal; i++)
    {
        printf("[%d] %s\n", i + 1, Glocal[i].nomeLocal);
    }
    printf("Digite o numero do local: ");
    scanf("%d", &opcaux);
    if (opcaux < 1 || opcaux > Nlocal)
    {
        printf("Opcao invalida!\n");
        system("pause");
        CadastrarEncontro();
    }
    opcaux--;
    fflush(stdin);
    a.localEncontro = Glocal[opcaux];
    opcaux = 0;

    system("cls");

    printf(" ---Cadastrar encontro--- \n\n");
    printf("Escolha a categoria para adicionar ao encontro: \n");
    for (int i = 0; i < Ncategoria; i++)
    {
        printf("[%d] %s\n", i + 1, Gcategoria[i].nomeCategoria);
    }
    printf("Digite o numero da categoria: ");
    scanf("%d", &opcaux);
    if (opcaux < 1 || opcaux > Ncategoria)
    {
        printf("Opcao invalida!\n");
    }
    opcaux--;
    fflush(stdin);
    a.categoriaEncontro = Gcategoria[opcaux];
    opcaux = 0;
    while (auxhora == 0)
    {
        system("cls");
        printf(" ---Cadastrar encontro---\n\n");
        printf("digite a hora e o minuto do encontro (sem nada entre eles, apenas o espaco):   ");
        scanf("%d %d", &a.horarioEncontro.hora, &a.horarioEncontro.min);
        auxhora = ValidaHora(a.horarioEncontro.hora, a.horarioEncontro.min);
        if (auxhora == 0)
        {
            printf(" a hora e invalida\n");
            system("pause");
        }
    }

    opcaux = 0;
    while (opcaux == 0)
    {
        system("cls");
        printf(" ---Cadastrar encontro---\n\n");
        printf("Digite o dia do encontro: ");
        scanf("%d", &dia);
        printf("Digite o mes do encontro: ");
        scanf("%d", &mes);
        printf("Digite o ano do encontro: ");
        scanf("%d", &ano);
        if (ValidaData(dia, mes, ano) == 0)
        {
            printf("Data invalida! Tente novamente.\n");
            system("pause");
        }
        else
        {
            a.dataEncontro.dia = dia;
            a.dataEncontro.mes = mes;
            a.dataEncontro.ano = ano;
            opcaux = 1;
        }
    }
    system("cls");
    fflush(stdin);
    printf(" ---Cadastrar encontro---\n\n");
    printf("Digite o motivo do encontro: \n");
    gets(straux);
    a.descricao = (char *)malloc((strlen(straux) + 1) * sizeof(char));
    strcpy(a.descricao, straux);
    fflush(stdin);
    Gencontro[Nencontro] = a;
    Nencontro++;
    printf("Encontro cadastrado com sucesso!\n");
    system("pause");
    MenuPrincipal();
}
void AlterarEncontro()
{
    int opcaux = 0, opcaux2 = 0, opcaux3 = 0, auxhora = 0, dia = 0, mes = 0, ano = 0;
    char straux[100];
    system("cls");
    fflush(stdin);
    if (Nencontro == 0)
    {
        printf("Nenhum encontro cadastrado!\n");
        printf("Deseja cadastrar um encontro? (1) Sim (2) Nao: ");
        fflush(stdin);
        scanf("%d", &opcaux);
        if (opcaux == 1)
        {
            CadastrarEncontro();
        }
        else
        {
            MenuPrincipal();
        }
    }

    system("cls");
    printf(" ---Alterar encontro---\n\n");
    printf("Escolha o encontro para alterar: \n");
    for (int i = 0; i < Nencontro; i++)
    {
        printf("encontro [%d]\n", i + 1);
    }
    printf("Digite o numero do encontro: ");
    scanf("%d", &opcaux);
    if (opcaux < 1 || opcaux > Nencontro)
    {
        printf("Opcao invalida!\n");
        system("pause");
        AlterarEncontro();
    }
    opcaux--;
    system("cls");
    printf(" ---Alterar encontro---\n\n");
    printf("Escolha o campo para alterar: \n");
    printf("1 - Amigo\n");
    printf("2 - Local\n");
    printf("3 - Categoria\n");
    printf("4 - Horario\n");
    printf("5 - Data\n");
    printf("6 - Motivo\n");
    printf("7 - Sair\n");
    printf("Digite o numero do campo: ");
    scanf("%d", &opcaux2);
    if (opcaux2 < 1 || opcaux2 > 7)
    {
        printf("Opcao invalida!\n");
        system("pause");
        AlterarEncontro();
    }
    switch (opcaux2)
    {
    case 1:
        printf("---Alterar amigo---\n\n");

        printf("Qual amigo deseja adicionar?\n");
        for (int i = 0; i < Namigo; i++)
        {
            printf("Amigo [%d]: %s\n", i + 1, Gamigo[i].nome);
        }
        printf("Digite o numero do amigo: ");
        scanf("%d", &opcaux3);
        if (opcaux3 < 1 || opcaux3 > Namigo)
        {
            printf("Opcao invalida!\n");
            system("pause");
            AlterarEncontro();
        }
        for (int i = 0; i < Gencontro[opcaux].numAmigoEncontro; i++)
        {
            if (strcmp(Gencontro[opcaux].amigoEncontro[i], Gamigo[opcaux3 - 1].nome) == 0)
            {
                printf("Amigo ja cadastrado!\n");
                system("pause");
                AlterarEncontro();
            }
        }
        opcaux3--;
        fflush(stdin);
        Gencontro[opcaux].amigoEncontro = (char **)realloc(Gencontro[opcaux].amigoEncontro, (Gencontro[opcaux].numAmigoEncontro + 1) * sizeof(char *));
        Gencontro[opcaux].amigoEncontro[Gencontro[opcaux].numAmigoEncontro] = (char *)malloc((strlen(Gamigo[opcaux3].nome) + 1) * sizeof(char));
        strcpy(Gencontro[opcaux].amigoEncontro[Gencontro[opcaux].numAmigoEncontro], Gamigo[opcaux3].nome);
        Gencontro[opcaux].numAmigoEncontro++;
        printf("Amigo adicionado com sucesso!\n");
        system("pause");
        break;
    case 2:
        printf("---Alterar local---\n\n");
        printf("Qual local deseja substituir?\n");
        for (int i = 0; i < Nlocal; i++)
        {
            printf("Local [%d]: %s\n", i + 1, Glocal[i].nomeLocal);
        }
        printf("Digite o numero do local: ");
        scanf("%d", &opcaux3);
        if (opcaux3 < 1 || opcaux3 > Nlocal)
        {
            printf("Opcao invalida!\n");
            system("pause");
            AlterarEncontro();
        }
        opcaux3--;
        fflush(stdin);
        Gencontro[opcaux].localEncontro = Glocal[opcaux3];
        printf("Local substituido com sucesso!\n");
        system("pause");
        break;
    case 3:
        printf("---Alterar categoria---\n\n");
        printf("Qual categoria deseja substituir?\n");
        for (int i = 0; i < Ncategoria; i++)
        {
            printf("Categoria [%d]: %s\n", i + 1, Gcategoria[i].nomeCategoria);
        }
        printf("Digite o numero da categoria: ");
        scanf("%d", &opcaux3);
        if (opcaux3 < 1 || opcaux3 > Ncategoria)
        {
            printf("Opcao invalida!\n");
            system("pause");
            AlterarEncontro();
        }
        opcaux3--;
        fflush(stdin);
        Gencontro[opcaux].categoriaEncontro = Gcategoria[opcaux3];
        printf("Categoria substituida com sucesso!\n");
        system("pause");

        break;
    case 4:
        while (auxhora == 0)
        {
            auxhora = 0;
            system("cls");
            printf("---Alterar horario---\n\n");
            printf("digite a nova hora(sem caracteres entre elas): ");
            scanf("%d %d", &Gencontro[opcaux].horarioEncontro.hora, &Gencontro[opcaux].horarioEncontro.min);
            if (ValidaHora(Gencontro[opcaux].horarioEncontro.hora, Gencontro[opcaux].horarioEncontro.min) == 0)
            {
                printf("Horario invalido!\n");
                system("pause");
            }
            else
            {
                auxhora = 1;
            }
        }
        printf("Horario alterado com sucesso!\n");
        system("pause");
        break;
    case 5:
        while (auxhora == 0)
        {
            auxhora = 0;
            system("cls");
            printf("---Alterar horario---\n\n");
            printf("digite o novo dia: ");
            scanf("%d", &dia);
            printf("digite o novo mes: ");
            scanf("%d", &mes);
            printf("digite o novo ano: ");
            scanf("%d", &ano);
            if (ValidaData(dia, mes, ano) == 0)
            {
                printf("Data invalida!\n");
                system("pause");
            }
            else
            {
                auxhora = 1;
                Gencontro[opcaux].dataEncontro.dia = dia;
                Gencontro[opcaux].dataEncontro.mes = mes;
                Gencontro[opcaux].dataEncontro.ano = ano;
            }
        }
        printf("Data alterada com sucesso!\n");
        system("pause");
        break;
    case 6:
        system("cls");
        printf("---Alterar motivo---\n\n");
        printf("Digite o novo motivo: ");
        fflush(stdin);
        gets(straux);
        Gencontro[opcaux].descricao = (char *)malloc((strlen(straux) + 1) * sizeof(char));
        strcpy(Gencontro[opcaux].descricao, straux);
        printf("Motivo alterado com sucesso!\n");
        system("pause");

        break;
    case 7:
        MenuPrincipal();

        break;
    }
    MenuPrincipal();
}

void ListarEncontro()
{
    int opcaux;

    system("cls");
    if (Nencontro == 0)
    {
        printf("Nenhum encontro cadastrado!\n");
        printf("Deseja cadastrar um encontro? (1) Sim (2) Nao: ");
        system("pause");
        fflush(stdin);
        scanf("%d", &opcaux);
        if (opcaux == 1)
        {
            CadastrarEncontro();
        }
        else
        {
            MenuPrincipal();
        }
    }
    system("cls");
    printf(" ---Listar encontro---\n\n");
    for (int i = 0; i < Nencontro; i++)
    {
        printf("Encontro [%d]\n", i + 1);
    }
    printf("qual encontro deseja listar?:  \n");
    scanf("%d", &opcaux);
    if (opcaux < 1 || opcaux > Nencontro)
    {
        printf("Opcao invalida!\n");
        system("pause");
        ListarEncontro();
    }
    opcaux--;
    system("cls");
    printf(" ---Listar encontro---\n\n");
    printf("Encontro %d\n", opcaux + 1);
    printf("Amigos encontro:\n");
    for (int i = 0; i < Gencontro[opcaux].numAmigoEncontro; i++)
    {
        printf("Amigo %d: %s\n", i + 1, Gencontro[opcaux].amigoEncontro[i]);
    }
    printf("Local: %s\n", Gencontro[opcaux].localEncontro.nomeLocal);
    printf("Categoria: %s\n", Gencontro[opcaux].categoriaEncontro.nomeCategoria);
    printf("Horario: %d:%d\n", Gencontro[opcaux].horarioEncontro.hora, Gencontro[opcaux].horarioEncontro.min);
    printf("Data: %d/%d/%d\n", Gencontro[opcaux].dataEncontro.dia, Gencontro[opcaux].dataEncontro.mes, Gencontro[opcaux].dataEncontro.ano);
    printf("Descricao: %s\n", Gencontro[opcaux].descricao);
    system("pause");
    MenuPrincipal();
}

void RemoverEncontro()
{
    int opcaux, opcesc;
    system("cls");
    if (Nencontro == 0)
    {
        printf("Nenhum encontro cadastrado!\n");
        printf("Deseja cadastrar um encontro? (1) Sim (2) Nao: ");
        system("pause");
        fflush(stdin);
        scanf("%d", &opcaux);
        if (opcaux == 1)
        {
            CadastrarEncontro();
        }
        else
        {
            MenuPrincipal();
        }
    }
    system("cls");
    printf(" ---Remover encontro---\n\n");
    for (int i = 0; i < Nencontro; i++)
    {
        printf("Encontro [%d]\n", i + 1);
    }
    printf("Qual encontro deseja remover?:  \n");
    scanf("%d", &opcaux);
    if (opcaux < 1 || opcaux > Nencontro)
    {
        printf("Opcao invalida!\n");
        system("pause");
        RemoverEncontro();
    }
    opcaux--;
    system("cls");
    printf(" Voce deseja remover o encontro %d?\n", opcaux + 1);
    printf(" (1) Sim (2) Nao\n");
    scanf("%d", &opcesc);
    if (opcesc == 2)
    {
        MenuPrincipal();
    }
    if (Nencontro == 1)
    {
        free(Gencontro);
        Gencontro = NULL;
    }
    else
    {
        for (int i = opcaux; i < Nencontro - 1; i++)
        {
            Gencontro[i] = Gencontro[i + 1];
        }
        Gencontro = (Tencontro *)realloc(Gencontro, (Nencontro - 1) * sizeof(Tencontro));
        if (Gencontro == NULL)
        {
            printf("Erro ao remover o encontro!\n");
            MenuPrincipal();
        }
    }
    Nencontro--;
    printf("Encontro removido com sucesso!\n");
    system("pause");
    MenuPrincipal();
}

void SalvarEncontro()
{
    FILE *arquivo = fopen("encontroTCA.txt", "w");
    for (int i = 0; i < Nencontro; i++)
    {
        fprintf(arquivo, "%d\n", Gencontro[i].numAmigoEncontro);
        for (int j = 0; j < Gencontro[i].numAmigoEncontro; j++)
        {
            fprintf(arquivo, "%s\n", Gencontro[i].amigoEncontro[j]);
        }
        fprintf(arquivo, "%s\n", Gencontro[i].localEncontro.nomeLocal);
        fprintf(arquivo, "%s\n", Gencontro[i].categoriaEncontro.nomeCategoria);
        fprintf(arquivo, "%d\n", Gencontro[i].horarioEncontro.hora);
        fprintf(arquivo, "%d\n", Gencontro[i].horarioEncontro.min);
        fprintf(arquivo, "%d\n", Gencontro[i].dataEncontro.dia);
        fprintf(arquivo, "%d\n", Gencontro[i].dataEncontro.mes);
        fprintf(arquivo, "%d\n", Gencontro[i].dataEncontro.ano);
        fprintf(arquivo, "%s\n", Gencontro[i].descricao);
    }
    fclose(arquivo);
}
void RecuperarEncontro()
{
    char c, straux[100];
    int i = 0, j = 0, sep = 0;
    FILE *arquivo = fopen("encontroTCA.txt", "r");
    if (arquivo)
    {
        while (!feof(arquivo))
        {
            c = fgetc(arquivo);
            if (c != '\n')
            {
                straux[i++] = c;
            }
            else
            {
                straux[i] = '\0';
                i = 0;
                switch (sep)
                {
                case 0:
                    if (Nencontro == 0)
                    {
                        Gencontro = (Tencontro *)malloc(sizeof(Tencontro));
                    }
                    else
                    {
                        Gencontro = (Tencontro *)realloc(Gencontro, (Nencontro + 1) * sizeof(Tencontro));
                    }
                    Gencontro[Nencontro].numAmigoEncontro = atoi(straux);
                    sep++;
                    break;
                case 1:
                    if (j == 0)
                    {

                        Gencontro[Nencontro].amigoEncontro = (char **)malloc(Gencontro[Nencontro].numAmigoEncontro * sizeof(char *));
                    }
                    Gencontro[Nencontro].amigoEncontro[j] = (char *)malloc((strlen(straux) + 1) * sizeof(char));
                    strcpy(Gencontro[Nencontro].amigoEncontro[j], straux);
                    j++;
                    if (j == Gencontro[Nencontro].numAmigoEncontro)
                    {
                        j = 0;
                        sep++;
                    }
                    break;
                case 2:
                    for (j = 0; j < Nlocal; j++)
                    {
                        if (strcmp(straux, Glocal[j].nomeLocal) == 0)
                        {
                            Gencontro[Nencontro].localEncontro = Glocal[j];
                            break;
                        }
                    }
                    sep++;
                    break;
                case 3:
                    for (j = 0; j < Ncategoria; j++)
                    {
                        if (strcmp(straux, Gcategoria[j].nomeCategoria) == 0)
                        {
                            Gencontro[Nencontro].categoriaEncontro = Gcategoria[j];
                            break;
                        }
                    }
                    sep++;

                    break;
                case 4:
                    Gencontro[Nencontro].horarioEncontro.hora = atoi(straux);
                    sep++;

                    break;
                case 5:
                    Gencontro[Nencontro].horarioEncontro.min = atoi(straux);
                    sep++;

                    break;
                case 6:
                    Gencontro[Nencontro].dataEncontro.dia = atoi(straux);
                    sep++;

                    break;
                case 7:
                    Gencontro[Nencontro].dataEncontro.mes = atoi(straux);
                    sep++;

                    break;
                case 8:
                    Gencontro[Nencontro].dataEncontro.ano = atoi(straux);
                    sep++;
                    break;
                case 9:
                    Gencontro[Nencontro].descricao = (char *)malloc((strlen(straux) + 1) * sizeof(char));
                    strcpy(Gencontro[Nencontro].descricao, straux);
                    Nencontro++;
                    sep = 0;
                    j = 0;

                    break;
                }
            }
        }
        fclose(arquivo);
    }
}
void MenuRelatorio()
{
    int opcaux;
    system("cls");
    printf(" _____________________________\n");
    printf("|-----------------------------|\n");
    printf("|--------MENU RELATORIO-------|\n");
    printf("|                             |\n");
    printf("| [1] Listar Amigo            |\n");
    printf("| [2] Listar Local            |\n");
    printf("| [3] Listar Categoria        |\n");
    printf("| [4] Listar Encontro         |\n");
    printf("| [5] Relatorio por Categoria |\n");
    printf("| [6] Sair                    |\n");
    printf("|_____________________________|\n\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcaux);

    
    if (opcaux < 1 || opcaux > 6)
    {
        printf("Opcao invalida!\n");
        system("pause");
        return MenuRelatorio(); 
    }
    OpcaoRelatorio(opcaux);
}
void OpcaoRelatorio(int opcaux)
{
    system("cls");
    switch (opcaux)
    {
    case 1:
        ListarAmigo();
        break;
    case 2:
        ListarLocal();
        break;
    case 3:
        ListarCategoria();
        break;
    case 4:
        ListarEncontro();
        break;
    case 5:
        RelatorioPorCategoria();
        break;
    case 6:
        MenuPrincipal();
        break;
    }
}

void RelatorioPorCategoria()
{
    if (Nencontro == 0)
    {
        printf("Nenhum encontro cadastrado!\n");
        system("pause");
        return MenuPrincipal();
    }
    int opcaux, numenc = 0;
    system("cls");
    printf(" ---Relatorio por Categoria---\n\n");
    printf("Categorias cadastradas:\n");
    for (int i = 0; i < Ncategoria; i++)
    {
        printf("[%d] - %s\n", i + 1, Gcategoria[i].nomeCategoria);
    }

    printf("Qual categoria deseja relatorizar?:  \n");
    scanf("%d", &opcaux);
    if (opcaux < 1 || opcaux > Ncategoria)
    {
        printf("Opcao invalida!\n");
        system("pause");
        RelatorioPorCategoria();
    }

    opcaux--;
    system("cls");
    printf(" ---Encontros encontrados---\n");
    for (int i = 0; i < Nencontro; i++)
    {
        if (strcmp(Gencontro[i].categoriaEncontro.nomeCategoria, Gcategoria[opcaux].nomeCategoria) == 0)
        {
            printf("Encontro[%d] possui esta categoria\n", i + 1);
            numenc++;
        }
        else
        {
            printf("Encontro[%d] NAO possui esta categoria\n", i + 1);
        }
    }
    if (numenc == 0)
    {
        printf("Nenhum encontro possui esta categoria!\n");
    }
    system("pause");
    MenuPrincipal();
}
int ValidaData(int dia, int mes, int ano)
{

    if (ano < 1 || ano > 9999)
    {
        return 0;
    }

   
    if (mes < 1 || mes > 12)
    {
        return 0; 
    }

    
    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
    {
        diasNoMes[1] = 29;
    }

    if (dia < 1 || dia > diasNoMes[mes - 1])
    {
        return 0;
    }

    return 1; 
}
int ValidaHora(int hora, int min)
{
    if (hora < 0 || hora > 23)
    {
        return 0;
    }
    if (min < 0 || min > 59)
    {
        return 0;
    }
    return 1; 
}
void SalvarArquivo()
{
    system("cls");
    SalvarAmigo();
    SalvarLocal();
    SalvarCategoria();
    SalvarEncontro();
    printf("Arquivos salvos com sucesso!\n");
    system("pause");
    system("cls");
    exit(0);
}
void RecuperarArquivo()
{
    RecuperarAmigo();
    RecuperarLocal();
    RecuperarCategoria();
    RecuperarEncontro();
    system("cls");
    printf("Arquivos recuperados com sucesso!\n");
    system("pause");
    system("cls");
}