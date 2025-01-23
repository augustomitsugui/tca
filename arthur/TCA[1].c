#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#define CLS (_WIN32 ? system("cls") : system("clear"));
#define SPAUSE                                              \
    printf("Pressione qualquer tecla para continuar. . ."); \
    getch();
#define GTS        \
    fflush(stdin); \
    gets(str);     \
    fflush(stdin);
#pragma GCC optimize("O3")

typedef struct
{

    int hora;
    int minuto;
} tHoraio;
typedef struct
{

    int ano;
    int mes;
    int dia;
} tData;
typedef struct
{

    char *numero;
    char *logradouro;
    char *bairro;
    char *cidade;
    char *estado;

} tEndereco;
typedef struct
{

    char *categoria;
    int id;
} tCategoria;
typedef struct
{

    tData nascimento;
    int id;
    char *nome;
    char *apelido;
    char *email;
    char *telefone;

} tAmigo;
typedef struct
{

    int id;
    tEndereco endereco;
    char *nomelocal;

} tLocal;
typedef struct
{

    tData data;            //
    tHoraio horario;       //
    tAmigo **amigos;       //
    tCategoria *categoria; //
    tLocal *local;         //
    int Namigos;           //
    char *descricao;       //
    char *nome;            //

} tEncontro;

tEncontro *Listaencontro = NULL;
tAmigo *Listaamigo = NULL;
tLocal *Listalocal = NULL;
tCategoria *Listacategoria = NULL;

int Numencontro = 0, Numamigo = 0, Numcategoria = 0, Numlocal = 0;

//                            // inicio meio e fim
void title();                  // digita o titulo
void menuprincipal();          // explode o menu principal
void switchprincipal(char op); // invoca as funoces manter ou relatorios com um SC.
void limpamemoria();           // limpa memoria alocada
void end();                    // titulo de saida e fim
//
void mainamigo();                          // invoca a main amigo
void menuamigo();                          // invoca as opcoes de acao para com um amigo
void switchamigo(char op);                 // switchcase do menu amigo
void incluiamigo();                        // inclui amigos
tAmigo criaamigo();                        // cria amigos
void orientaexcluiamigo();                 // orienta a exlusao de amigos
void editaamigo();                         // edita dados dos amigos
void excluiamigo(int opAmigo);             // lista negra
void menueditaamigo(int opAmigo);          // "o que deseja fazer com este amigo?"
void alteraramigo(char editor, int amigo); // factualmente muda os dados do amigo
bool validanome(char *nome);               // cheks if theres a friend w that name
bool validaemail(char *email);             // validates emails and checks for doubles
bool validanumero(char *num);              // checks for doubles
int buscaxnome(int op);                    // buscapelonome
//
void maincat();                // invoca a main categoria
void menucategoria();          // invoca o menu categoria
void switchcategoria(char op); // invoca as opcoes de acao para com uma categoria
void incluicategoria();        // inclui categorias
tCategoria criacategoria();    // cria categorias
void editacategoria();         // orienta a edicao de categoria
void alteracategoria(int cat); // edita categorias
void orientaexcluicat();       // orienta a exclusao de categorias
void excluicat(int opCat);     // exclui categorias
//
void mainencontro();                     // invoca a main encontro
void menuencontro();                     // invoca o menu encontro
void switchencontro(char op);            // invoca as opcoes de acao para com um encontro
void incluiencontro();                   // inclui encontros
tEncontro criaencontro();                // cria encontros
tAmigo showchavfr(tAmigo *vet[], int t); // exibe os amigos disponiveis para a incusao num encontro
bool validanomenc(char *str);            // checks for doubles
//
void mainlocal();                        // invoca a main local
void menulocal();                        // invoca o menu local
void switchlocal(char op);               // invoca as opcoes de acao para com um local
void incluilocal();                      // inclui locais
tLocal crialocal();                      // cria locais
void orientaeditalocal();                // orienta a edicao de locais
void editalocal(char editor, int local); // edita locais
void orientaexcluilocal();               // orienta a exclusao de locais
void excluilocal(int opLocal);           // exclui locais
void menueditalocal(int opLocal);        // "o que deseja fazer com este local?"
//
void mainrelatorios();                                       // invoca a main relatorios
void menurelatorios();                                       // puxa as opcoes de relatorios
void switchrelatorios(char op);                              // invoca as funcoes de relatorio
void exibeamigo(bool prolongar, bool rel);                   // printa os amigos e suas informacoes
void exibecategoria(bool rel);                               // printa as categorias
void exibelocal(bool prolongar, bool rel);                   // printa os locais e suas informacoes
void exibeencontro(bool rel, bool prolongar, bool detalhar); // printa os encontros
//
void verifica_alocacao(void *v);                   // verifica se alocacao dinamica deu certo
char valida16();                                   // valida operador do menu principal
char valida14();                                   // valida operadoeres 1 a 4
bool validanascimento(int dias, int mes, int ano); // valida datas de nascimento
bool validadataenc(int dias, int mes, int ano);    // valida datas para encontros
bool validarhorario(int hora, int min);            // valida horarios
bool validasimnao();                               // valida sim e nao
char valida15();                                   // valida 1 a 5
char valida13();                                   // valida 1 a 3
char valida12();                                   // valida 1 a 2
void ERRO(int opErro);                             // mensagem de erro
bool adviser();                                    // Pergunta se o usuario quer prossegiuir com a ma ideia

int main()
{
    char op;
    title();
    do
    {
        menuprincipal();
        op = valida16();
        switchprincipal(op);

    } while (op != '6');

    limpamemoria();
    end();
}

bool validanomenc(char *str)
{
    for (int i = 0; i < Numencontro; i++)
    {
        if (strcmp(str, Listaencontro[i].nome) == 0)
        {
            return false;
        }
    }
    return true;
}

void switchencontro(char op)
{
    switch (op)
    {
    case '1':
        incluiencontro();
        break;
    case '2':
        // editaencontro();
        break;
    case '3':
        // excluiencontro();
        break;
    }
    return;
}

void exibeencontro(bool rel, bool prolongar, bool detalhar)
{
    CLS if (!detalhar)
    {
        if (!prolongar)
        {
            printf("ENCONTROS [%d]:\n\n\n", Numencontro);
            printf("------------------------------------------\n\n");
            for (int i = 0; i < Numencontro; i++)
            {
                printf("\n[%d] Encontro: %s\n", i + 1, Listaencontro[i].nome);
                printf("\"%s\"\n", Listaencontro[i].descricao);
                printf("------------------------------------------\n\n");
            }
        }
        else
        {
            printf("ENCONTROS [%d]:\n\n\n", Numencontro);
            printf("------------------------------------------\n\n");
            for (int i = 0; i < Numencontro; i++)
            {
                printf("Encontro [%d]: %s\n", i + 1, Listaencontro[i].nome);
                printf("\"%s\" \n", Listaencontro[i].descricao);
                printf("Local: %s\n", Listaencontro[i].local->nomelocal);
                printf("Amigos:\n\n");
                for (int j = 0; j < Listaencontro[i].Namigos; j++)
                {
                    printf("[%d] %s, (%s)\n", j + 1, Listaencontro[i].amigos[j]->nome, Listaencontro[i].amigos[j]->apelido);
                }
                printf("\n");
                printf("Categoria: %s\n", Listaencontro[i].categoria->categoria);
                printf("Horario: %d:%d\n", Listaencontro[i].horario.hora, Listaencontro[i].horario.minuto);
                printf("Data: %d/%d/%d\n", Listaencontro[i].data.dia, Listaencontro[i].data.mes, Listaencontro[i].data.ano);
                printf("------------------------------------------\n\n");
            }
        }
    }
    else
    {
        printf("ENCONTROS [%d]:\n\n\n", Numencontro);
        printf("------------------------------------------\n\n");
        for (int i = 0; i < Numencontro; i++)
        {
            printf("Encontro [%d]: %s\n", i + 1, Listaencontro[i].nome);
            printf("Descrito como: \"%s\"\n", Listaencontro[i].descricao);

            printf("Local:\n");
            printf("%s, %s, %s, %s, %s\n\n", Listaencontro[i].local->endereco.logradouro, Listaencontro[i].local->endereco.numero, Listaencontro[i].local->endereco.bairro, Listaencontro[i].local->endereco.cidade, Listaencontro[i].local->endereco.estado);
            printf("Amigos(%d):\n\n", Listaencontro[i].Namigos);
            printf("===============================\n");
            for (int j = 0; j < Listaencontro[i].Namigos; j++)
            {
                if (Listaencontro[i].amigos[j] == NULL)
                {
                    printf("Erro: amigos[%d] é NULL!\n", j);
                    exit(1);
                }
            
                printf("[%d] %s, (%s)\n", j + 1, Listaencontro[i].amigos[j]->nome, Listaencontro[i].amigos[j]->apelido);
                printf("Dados:\n Nasimento: (%d/%d/%d), Telefone: %s, E-mail: %s\n", Listaencontro[i].amigos[j]->nascimento.dia, Listaencontro[i].amigos[j]->nascimento.mes, Listaencontro[i].amigos[j]->nascimento.ano, Listaencontro[i].amigos[j]->telefone, Listaencontro[i].amigos[j]->email);
                printf("===============================\n");
            }
            printf("\n");
            printf("Categoria: %s\n", Listaencontro[i].categoria->categoria);
            printf("Horario: %d:%d\n", Listaencontro[i].horario.hora, Listaencontro[i].horario.minuto);
            printf("Data: %d/%d/%d\n", Listaencontro[i].data.dia, Listaencontro[i].data.mes, Listaencontro[i].data.ano);
            printf("------------------------------------------\n\n");
        }
    }
    if (rel)
    {
        SPAUSE
    }
    return;
}
void mainencontro()
{
    char op;
    do
    {
        menuencontro();
        op = valida14();
        if (op == '4')
        {
            break;
        }
        switchencontro(op);

    } while (op != '4');
    return;
}

void menuencontro()
{

    CLS
        printf("***MENU ENCONTRO***\n\nDigite:\n");
    printf("1. para criar um encontro\n");
    printf("2. para editar um encontro\n");
    printf("3. para excluir um encontro\n");
    printf("4. para voltar\n");
    printf("\nO que deseja fazer?: ");
}

void incluiencontro()
{
    if (Numencontro == 0)
    {
        Listaencontro = (tEncontro *)malloc(1 * sizeof(tEncontro));
    }
    else
    {
        Listaencontro = (tEncontro *)realloc(Listaencontro, (Numencontro + 1) * sizeof(tEncontro));
    }

    verifica_alocacao(Listaencontro);
    Listaencontro[Numencontro] = criaencontro();
    Numencontro++;

    CLS
        printf("Encontro criado com sucesso!");
    Sleep(2000);
    return;
}

tAmigo showchavfr(tAmigo *vet[], int t)
{
    tAmigo *amigos = NULL;
    bool av;
    int num = 0;

    for (int i = 0; i < Numamigo; i++)
    {
        av = true;
        for (int j = 0; j < t; j++)
        {
            if (strcmp(Listaamigo[i].nome, vet[j]->nome) == 0)
            {
                av = false;
                break;
            }
        }
        if (av)
        {
            if (num == 0)
            {
                amigos = (tAmigo *)malloc(sizeof(tAmigo));
                printf("Amigos disponiveis:\n\n\n");
            }
            else
            {
                amigos = (tAmigo *)realloc(amigos, (num + 1) * sizeof(tAmigo));
            }
            verifica_alocacao(amigos);
            amigos[num] = Listaamigo[i];
            printf("%d Amigo: %s, (%s)\n", num + 1, amigos[num].nome, amigos[num].apelido);
            printf("---------------------\n");
            num++;
        }
    }

    int op = 0;
    printf("\n\nQual amigo deseja adicionar?: ");
    while (op < 1 || op > num)
    {
        scanf("%d", &op);
        if (op < 1 || op > num)
        {
            ERRO(1);
        }
    }

    tAmigo escolhido = amigos[op - 1];
    free(amigos);
    return escolhido;
}

tEncontro criaencontro()
{
    char str[100];
    tEncontro encontro;
    CLS

        printf("**CRIACAO DE ENCONTROS***\n\n");
    printf("Voce tem %d encontros no momento\n\n", Numencontro);
    printf("Qual sera o nome de seu encontro?: ");

    do
    {
        GTS if (validanomenc(str))
        {
            encontro.nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
            strcpy(encontro.nome, str);
            break;
        }
        else
        {
            printf("Ja existe um encontro com esse nome! Digite novamente:");
        }

    } while (!validanomenc(str));
    /////////////////////////////////////////////////////////////////
    CLS
        printf("Seu encontro precisa de um local.\n\n");
    if (Numlocal == 0)
    {
        printf("Voce precisa criar um local para seu encontro.\n");
        printf("Voce esta sendo direcionado tempoarariamente para a criacao de um local.\n");
        Sleep(3000);

        incluilocal();
        CLS
            encontro
                .local = &Listalocal[Numlocal - 1];
        printf("O local criado foi adicionado com sucesso!\n");
    }
    else
    {
        printf("Digite 1 para adicionar um local existente.\nDigite 2 para adicionar um novo local.\n");
        printf("Opcao: ");
        char op = valida12();
        if (op == '1')
        {
            int opl = 0;
            exibelocal(true, false);
            (Numlocal == 1) ? (printf("\n\nDigite 1 para escolher o local disponivel: ")) : (printf("\n\nDigite um numero de 1 a %d para escolher: ", Numlocal));
            while (opl < 1 || opl > Numlocal)
            {
                fflush(stdin);
                scanf(" %d", &opl);
                if (opl < 1 || opl > Numlocal)
                {
                    ERRO(1);
                }
            }
            encontro.local = &Listalocal[opl - 1];
        }
        else
        {
            incluilocal();
            encontro.local = &Listalocal[Numlocal - 1];
            CLS
                printf("O local criado foi adicionado com sucesso!\n");
        }
    }
    /////////////////////////////////////////////////////////////////////
    CLS
        encontro.amigos = (tAmigo **)malloc(1 * sizeof(tAmigo *));
    printf("Seu encontro precisa de pelo menos um amigo.\n");
    if (Numamigo == 0)
    {
        printf("Voce esta sendo direcionado tempoarariamente para a criacao de um amigo.\n");
        Sleep(3000);
        incluiamigo();
        encontro.amigos[0] = &Listaamigo[Numamigo - 1];
        encontro.Namigos = 1;
        printf("O amigo criado foi adicionado com sucesso!\n");
        Sleep(1000);
    }
    else
    {
        printf("Digite 1 para adicionar um amigo existente.\nDigite 2 para adicionar um novo amigo.\n");
        printf("Opcao: ");
        char op = valida12();
        if (op == '1')
        {
            int opl = 0;
            exibeamigo(true, false);
            (Numamigo == 1) ? (printf("\n\nDigite 1 para escolher o amigo disponivel: ")) : (printf("\n\nDigite um numero de 1 a %d para escolher: ", Numamigo));
            while (opl < 1 || opl > Numamigo)
            {
                fflush(stdin);
                scanf(" %d", &opl);
                if (opl < 1 || opl > Numamigo)
                {
                    ERRO(1);
                }
            }
            encontro.amigos[0] = &Listaamigo[opl - 1];
            encontro.Namigos = 1;
        }
        else
        {
            printf("Voce esta sendo direcionado tempoarariamente para a criacao de um amigo.\n");
            Sleep(3000);
            incluiamigo();
            encontro.amigos[0] = &Listaamigo[Numamigo - 1];
            encontro.Namigos = 1;
            printf("O amigo criado foi adicionado com sucesso!\n");
            Sleep(1000);
        }
    }

    bool op;
    do // adicao de novos amigos
    {
        CLS
            printf("Deseja adicionar mais amigos?(S/N): ");
        op = validasimnao();
        if (op)
        {
            if (encontro.Namigos == Numamigo)
            {
                printf("Voce esta sendo direcionado tempoarariamente para a criacao de um novo amigo.\n");
                Sleep(3000);
                incluiamigo();
                encontro.amigos = (tAmigo **)realloc(encontro.amigos, (encontro.Namigos + 1) * sizeof(tAmigo *));
                verifica_alocacao(encontro.amigos);
                encontro.amigos[encontro.Namigos] = &Listaamigo[Numamigo - 1];
                Sleep(2000);
                encontro.Namigos++;
                CLS
                    printf("O amigo criado foi adicionado com sucesso!\n");
                Sleep(2000);
                continue;
            }
            else
            {
                encontro.amigos = (tAmigo **)realloc(encontro.amigos, (encontro.Namigos + 1) * sizeof(tAmigo *));
                verifica_alocacao(encontro.amigos);
                CLS
                    tAmigo aux = showchavfr(encontro.amigos, encontro.Namigos);
                encontro.amigos[encontro.Namigos] = &aux;
                printf("%s", encontro.amigos[encontro.Namigos]->nome);
                Sleep(3000);
                encontro.Namigos++;
            }
        }
        else
        {
            break;
        }

    } while (op);
    CLS
        printf("Seu encontro precisa de uma categoria.\n");
    if (Numcategoria == 0)
    {
        printf("Voce esta sendo direcionado tempoarariamente para a criacao de uma categoria.\n");
        Sleep(3000);
        incluicategoria();
        encontro.categoria = &Listacategoria[Numcategoria - 1];
        printf("A categoria criada foi adicionada com sucesso!\n");
    }
    else
    {
        printf("Digite 1 para adicionar uma categoria existente.\nDigite 2 para adicionar uma nova categoria.\n");
        printf("Opcao: ");
        char op = valida12();
        if (op == '1')
        {
            exibecategoria(false);
            (Numcategoria == 1) ? (printf("\n\nDigite 1 para escolher a categoria disponivel: ")) : (printf("\n\nDigite um numero de 1 a %d para escolher: ", Numcategoria));
            int opl = 0;
            while (opl < 1 || opl > Numcategoria)
            {
                fflush(stdin);
                scanf(" %d", &opl);
                if (opl < 1 || opl > Numcategoria)
                {
                    ERRO(1);
                }
            }
            encontro.categoria = &Listacategoria[opl - 1];
            printf("\nCategoria adicionada com sucesso!\n");
        }
        else
        {
            incluicategoria();
            encontro.categoria = &Listacategoria[Numcategoria - 1];
            printf("A categoria criada foi adicionada com sucesso!\n");
        }
    }
    printf("Descreva o que acontecera em seu encontro: ");
    GTS
        encontro.descricao = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(encontro.descricao);
    strcpy(encontro.descricao, str);
    printf("Que dia sera seu encontro?: ");
    do
    {
        scanf("%d%d%d", &encontro.data.dia, &encontro.data.mes, &encontro.data.ano);
        if (!validadataenc(encontro.data.dia, encontro.data.mes, encontro.data.ano))
        {
            ERRO(-2);
        }
    } while (!validadataenc(encontro.data.dia, encontro.data.mes, encontro.data.ano));
    CLS
        printf("Que horas sera seu encontro?(hh:mm): ");
    do
    {
        scanf("%d%d", &encontro.horario.hora, &encontro.horario.minuto);
        if (!validarhorario(encontro.horario.hora, encontro.horario.minuto))
        {
            ERRO(-2);
        }
    } while (!validarhorario(encontro.horario.hora, encontro.horario.minuto));
    return encontro;
}

bool adviser()
{
    CLS
        ERRO(0);
    bool maideia = validasimnao();
    if (maideia)
    {
        return true;
    }
    return false;
}

void excluilocal(int opLocal)
{
    free(Listalocal[opLocal].endereco.bairro);
    free(Listalocal[opLocal].endereco.cidade);
    free(Listalocal[opLocal].endereco.estado);
    free(Listalocal[opLocal].endereco.logradouro);
    free(Listalocal[opLocal].endereco.numero);
    free(Listalocal[opLocal].nomelocal);

    for (int i = opLocal; i < Numlocal - 1; i++)
        if (opLocal < Numlocal)
        {
            Listalocal[i] = Listalocal[i + 1];
            for (int i = opLocal; i < Numlocal - 1; i++)
            {
                Listalocal[i] = Listalocal[i + 1];
            }
        }

    Numlocal--;
    Listalocal = (tLocal *)realloc(Listalocal, Numlocal * sizeof(tLocal));
    verifica_alocacao(Listalocal);
    printf("Local excluido com sucesso!\n");
    Sleep(2000);
    menulocal();
}

void orientaexcluilocal()
{
    int opLocal;

    CLS
        printf("Digite 1 para pesquisar seu local pelo nome\n");
    printf("Digite 2 para exibir a lista de locais\n");
    printf("Digite 3 para voltar\nDigite a opcao:");

    char opIn = valida13();

    if (opIn == '1')
    {
        opLocal = buscaxnome(2);
        excluilocal(opLocal);
    }
    else if (opIn == '2')
    {
        printf("Qual o numero do local que deseja excluir?: ");
        exibelocal(false, false);

        while (opLocal < 1 || opLocal > Numlocal)
        {
            scanf(" %d", &opLocal);
            if (opLocal < 1 || opLocal >= Numlocal)
            {
                ERRO(19);
            }
        }
        opLocal--;
        excluilocal(opLocal);
    }
    else
    {
        return;
    }
}

void editalocal(char editor, int local)
{

    char str[100];
    CLS

        switch (editor)
    {
    case '1':
        printf("Qual o novo nome de %s?: ", Listalocal[local].nomelocal);
        GTS
            Listalocal[local]
                .nomelocal = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[local].nomelocal);
        strcpy(Listalocal[local].nomelocal, str);
        break;

    case '2':
        printf("Qual o novo estado para seu encontro?: ");
        GTS
            Listalocal[local]
                .endereco.estado = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[local].endereco.estado);
        strcpy(Listalocal[local].endereco.estado, str);
        printf("Qual a nova cidade para seu encontro?: ");
        GTS
            Listalocal[local]
                .endereco.cidade = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[local].endereco.cidade);
        strcpy(Listalocal[local].endereco.cidade, str);
        printf("Qual o novo bairro para seu encontro?: ");
        GTS
            Listalocal[local]
                .endereco.bairro = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[local].endereco.bairro);
        strcpy(Listalocal[local].endereco.bairro, str);
        printf("Qual o novo logradouro para seu encontro?: ");
        GTS
            Listalocal[local]
                .endereco.logradouro = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[local].endereco.logradouro);
        strcpy(Listalocal[local].endereco.logradouro, str);
        printf("Qual o novo numero para seu encontro?: ");
        GTS
            Listalocal[local]
                .endereco.numero = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[local].endereco.numero);
        strcpy(Listalocal[local].endereco.numero, str);
        break;

    case '3':
        printf("Qual o novo numero para seu encontro?: ");
        GTS
            Listalocal[local]
                .endereco.numero = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[local].endereco.numero);
        strcpy(Listalocal[local].endereco.numero, str);
        break;
    }
    CLS
        printf("Local Editado com sucesso!");
    Sleep(1500);
    menulocal();
}

void menueditalocal(int opLocal)
{

    CLS
        printf("Digite 1 para alterar o nome (%s)\n", Listalocal[opLocal].nomelocal);
    printf("Digite 2 para alterar a endereco %s, %s, %s, %s, %s\n", Listalocal[opLocal].endereco.estado, Listalocal[opLocal].endereco.cidade, Listalocal[opLocal].endereco.bairro, Listalocal[opLocal].endereco.logradouro, Listalocal[opLocal].endereco.numero);
    printf("Digite 3 para alterar o numero (%s)\n", Listalocal[opLocal].endereco.numero);
}

char valida12()
{
    char opIn;
    do
    {
        scanf(" %c", &opIn);
        if (opIn != '1' && opIn != '2')
        {
            ERRO(1);
        }
    } while (opIn != '1' && opIn != '2');

    return opIn;
}
char valida13()
{
    char opIn;
    do
    {
        scanf(" %c", &opIn);
        if (opIn != '1' && opIn != '2' && opIn != '3')
        {
            ERRO(1);
        }
    } while (opIn != '1' && opIn != '2' && opIn != '3');

    return opIn;
}

char valida14()
{
    char opIn;
    do
    {
        scanf(" %c", &opIn);
        if (opIn != '1' && opIn != '2' && opIn != '3' && opIn != '4')
        {
            ERRO(1);
        }
    } while (opIn != '1' && opIn != '2' && opIn != '3' && opIn != '4');

    return opIn;
}

char valida15()
{
    char op;
    do
    {
        scanf(" %c", &op);
        if (op != '1' && op != '2' && op != '3' && op != '4' && op != '5')
        {
            ERRO(1);
        }
    } while (op != '1' && op != '2' && op != '3' && op != '4' && op != '5');

    return op;
}
void exibelocal(bool prolongar, bool rel)
{
    CLS

        if (!prolongar)
    {
        printf("LOCAIS:\n\n");
        for (int i = 0; i < Numlocal; i++)
        {
            printf("%d Local: %s\n", i + 1, Listalocal[i].nomelocal);
        }
    }

    else if (prolongar)
    {
        printf("LOCAIS:\n\n");
        for (int i = 0; i < Numlocal; i++)
        {
            printf("\nLocal %d: \n", i + 1);
            printf("Nome: %s\n", Listalocal[i].nomelocal);
            printf("Endereco: %s, %s, %s, %s, %s\n", Listalocal[i].endereco.logradouro, Listalocal[i].endereco.numero, Listalocal[i].endereco.bairro, Listalocal[i].endereco.cidade, Listalocal[i].endereco.estado);
        }
    }

    if (rel)
    {
        SPAUSE
    }
    return;
}

void orientaeditalocal()
{
    int opLocal = 0;
    char editor;

    CLS
        printf("Digite 1 para pesquisar seu local pelo nome\n");
    printf("Digite 2 para exibir a lista de locais\n");
    printf("Digite 3 para voltar\nDigite a opcao: ");
    char opIn = valida13();

    if (opIn == '1')
    {
        opLocal = buscaxnome(2);
        menueditalocal(opLocal);
        printf("\n\nDigite para alterar: ");
        editor = valida13();
        editalocal(editor, opLocal);
    }
    else if (opIn == '2')
    {
        exibelocal(false, false);
        printf("Qual o numero do local que deseja editar?: ");
        while (opLocal < 1 || opLocal > Numlocal)
        {
            scanf(" %d", &opLocal);
            if (opLocal < 1 || opLocal > Numlocal)
            {
                ERRO(19);
            }
        }
        opLocal--;
        menueditalocal(opLocal);
        printf("\n\nDigite para alterar: ");
        editor = valida13();
        editalocal(editor, opLocal);
    }
    else
    {
        return;
    }
}

void incluilocal()
{
    CLS
        printf("Voce tem %d locais no momento\n\n", Numlocal);

    if (Numlocal == 0)
    {
        Listalocal = (tLocal *)malloc(1 * sizeof(tLocal));
    }
    else
    {
        Listalocal = (tLocal *)realloc(Listalocal, (Numlocal + 1) * sizeof(tLocal));
    }
    verifica_alocacao(Listalocal);

    Listalocal[Numlocal] = crialocal();
    Numlocal++;
    CLS
        printf("Local criado com sucesso!\n");
    return;
}

tLocal crialocal()
{
    char str[100];
    tLocal local;
    CLS

        printf("Em qual estado sera seu encontro?: ");
    GTS
        local
            .endereco.estado = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(local.endereco.estado);
    strcpy(local.endereco.estado, str);

    printf("Em qual cidade sera seu encontro?: ");
    GTS
        local
            .endereco.cidade = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(local.endereco.cidade);
    strcpy(local.endereco.cidade, str);

    printf("Em qual bairro sera seu encontro?: ");
    GTS
        local
            .endereco.bairro = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(local.endereco.bairro);
    strcpy(local.endereco.bairro, str);

    printf("Qual o logradouro ser seu encontro?: ");
    GTS
        local
            .endereco.logradouro = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(local.endereco.logradouro);
    strcpy(local.endereco.logradouro, str);

    printf("Qual o numero para seu encontro?: ");
    GTS
        local
            .endereco.numero = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(local.endereco.numero);
    strcpy(local.endereco.numero, str);

    printf("Qual o nome do seu local?: ");
    GTS
        local
            .nomelocal = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(local.nomelocal);
    strcpy(local.nomelocal, str);

    CLS
        printf("Local criado com sucesso!");
    Sleep(1000);
    return local;
}

void switchlocal(char op)
{

    switch (op)
    {
    case '1':
        incluilocal();
        break;
    case '2':
        if (Numlocal < 1)
        {
            ERRO(21);
        }
        else
        {
            orientaeditalocal();
        }
        break;
    case '3':
        if (Numlocal < 1)
        {
            ERRO(22);
        }
        else if (Numlocal < 2)
        {
            if (adviser())
            {
                orientaexcluilocal();
            }
        }
        else
        {
            orientaexcluilocal();
        }
        break;
    }
    return;
}

void mainlocal()
{
    char op;
    do
    {
        menulocal();
        op = valida14();
        if (op == '4')
        {
            break;
        }
        switchlocal(op);

    } while (op != '4');
    return;
}

void menulocal()
{

    CLS
        printf("***MENU LOCAL***\n\nDigite:\n");
    printf("1. para criar um local\n");
    printf("2. para editar um local\n");
    printf("3. para excluir um local\n");
    printf("4. para voltar\n");
    printf("\nO que deseja fazer?: ");
    return;
}

void excluicat(int opCat)
{

    if (opCat < Numcategoria)
    {
        for (int i = opCat; i < Numcategoria - 1; i++)
        {
            Listacategoria[i] = Listacategoria[i + 1];
        }
    }

    Numcategoria--;
    Listacategoria = (tCategoria *)realloc(Listacategoria, Numcategoria * sizeof(tCategoria));
    verifica_alocacao(Listacategoria);
    printf("Categoria excluida com sucesso!\n");
    Sleep(2000);
    menucategoria();
}

void orientaexcluicat()
{
    int opCat = 0;

    CLS
        printf("Digite 1 para pesquisar sua categoria pelo nome\n");
    printf("Digite 2 para exibir a lista de categorias\n");
    printf("Digite 3 para voltar\nDigite a opcao:");

    char opIn = valida13();

    if (opIn == '1')
    {
        int i = buscaxnome(3);
        excluicat(i);
    }
    else if (opIn == '2')
    {
        CLS
            printf("Qual categoria deseja excluir?: \n");
        exibecategoria(false);
        printf("\n: ");
        while (opCat < 1 || opCat > Numcategoria)
        {
            scanf(" %d", &opCat);
            if (opCat < 1 || opCat > Numcategoria)
            {
                ERRO(8);
            }
        }
        opCat--;
        excluicat(opCat);
    }
    else
    {
        menucategoria();
    }
}

void alteracategoria(int cat)
{
    char str[100];

    printf("Qual novo nome deseja para sua categoria?: ");
    GTS
        Listacategoria[cat]
            .categoria = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(Listacategoria[cat].categoria);
    strcpy(Listacategoria[cat].categoria, str);
    printf("Categoria alterada com sucesso!");
    Sleep(2000);
    menucategoria();
}

void exibecategoria(bool rel)
{

    CLS

        printf("CATEGORIAS:\n\n");
    for (int i = 0; i < Numcategoria; i++)
    {
        printf("Categoria %d: %s\n", i + 1, Listacategoria[i].categoria);
    }

    if (rel)
    {
        SPAUSE
    }
    return;
}
void editacategoria()
{
    int opCat = 0;
    char opIn = 'a';

    CLS
        printf("Digite 1 para pesquisar sua categoria pelo nome\n");
    printf("Digite 2 para exibir a lista de categorias\n");
    printf("Digite 3 para voltar\nDigite a opcao: ");

    opIn = valida13();
    if (opIn == '1')
    {
        int i = buscaxnome(3);
        alteracategoria(i);
    }
    else if (opIn == '2')
    {
        printf("Qual categoria deseja editar?: \n");
        exibecategoria(false);
        printf("\n: ");
        while (opCat < 1 || opCat > Numcategoria)
        {
            scanf(" %d", &opCat);
            if (opCat < 1 || opCat > Numcategoria)
            {
                ERRO(8);
            }
        }
        opCat--;
        alteracategoria(opCat);
    }
    else
    {
        return;
    }
}

bool validasimnao()
{
    char op;

    do
    {
        fflush(stdin);
        scanf(" %c", &op);
        if (op != 's' && op != 'n' && op != 'S' && op != 'N')
        {
            ERRO(1);
        }
    } while (op != 's' && op != 'n' && op != 'S' && op != 'N');

    if (op == 's' || op == 'S')
    {
        return true;
    }
    return false;
}

void incluicategoria()
{
    CLS
        printf("Voce tem %d categorias no momento\n", Numcategoria);

    if (Numcategoria == 0)
    {
        Listacategoria = (tCategoria *)malloc(1 * sizeof(tCategoria));
    }
    else
    {
        Listacategoria = (tCategoria *)realloc(Listacategoria, (Numcategoria + 1) * sizeof(tCategoria));
    }
    verifica_alocacao(Listacategoria);
    Listacategoria[Numcategoria] = criacategoria();
    Numcategoria++;

    CLS
        printf("Categoria criada com sucesso!\n");
    Sleep(1000);
    return;
}

tCategoria criacategoria()
{
    char str[100];
    tCategoria categoria;

    printf("\nQual nome deseja para sua categoria?: ");
    GTS
        categoria
            .categoria = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(categoria.categoria);
    strcpy(categoria.categoria, str);
    return categoria;
}

void maincat()
{
    char op;
    do
    {
        menucategoria();
        op = valida14();
        if (op == '4')
        {
            break;
        }
        switchcategoria(op);
    } while (op != '4');
    return;
}

void menucategoria()
{

    CLS
        printf("***MENU CATEGORIA***\n\nDigite:\n");
    printf("1. para criar uma categoria\n");
    printf("2. para editar uma categoria\n");
    printf("3. para excluir uma categoria\n");
    printf("4. para voltar\n");
    printf("\nO que deseja fazer?: ");
    return;
}

void switchcategoria(char op)
{
    switch (op)
    {
    case '1':
        incluicategoria();
        break;
    case '2':
        if (Numcategoria == 0)
        {
            printf("Nao ha categorias para serem editadas!");
            Sleep(2500);
            return;
        }
        else
        {
            editacategoria();
            break;
        }

    case '3':
        if (Numcategoria == 0)
        {
            printf("Nao ha catetgorias para serem excluidas!");
            Sleep(2500);
            return;
        }
        else if (Numcategoria < 2)
        {
            if (adviser())
            {
                orientaexcluicat();
            }
        }
        else
        {
            orientaexcluicat();
            break;
        }
    }
    return;
}

void title()
{

    char word[] = "Hello, world!";

    CLS for (int i = 0; word[i] != '\0'; i++)
    {
        printf("%c", word[i]);
        Sleep(100);
    }
    Sleep(900);
}

void switchrelatorios(char op)
{

    switch (op)
    {
    case '1':
        if (Numamigo < 1)
        {
            CLS
                ERRO(7);
            Sleep(1500);
        }
        else
        {
            exibeamigo(true, true);
        }
        break;

    case '3':
        if (Numcategoria < 1)
        {
            CLS
                ERRO(10);
            Sleep(1500);
        }
        else
        {
            exibecategoria(true);
        }
    case '2':
        if (Numlocal < 1)
        {
            CLS
                ERRO(18);
            Sleep(1500);
        }
        else
        {
            exibelocal(true, true);
        }
    case '4':
        if (Numencontro < 1)
        {
            CLS
                ERRO(15);
            Sleep(1500);
        }
        else
        {
            exibeencontro(true, true, true);
        }
    }

    return;
}

void mainrelatorios()
{
    char op;
    do
    {
        op = valida16();
        if (op == '6')
        {
            break;
        }
        switchrelatorios(op);
    } while (op != '6');
}

void menurelatorios()
{
    CLS
        printf("***MENU DE RELATORIOS***\n\n");
    printf("Digite:\n");
    printf("1. para exibir o relatorio de amigos\n");
    printf("2. para exibir o relatorio de locais\n");
    printf("3. para exibir o relatorio de categorias\n");
    printf("4. para exibir o relatorio de encontros\n");
    printf("5. para voltar\n");
    printf("\nO que deseja fazer?: ");
    char op = valida15();
    switchrelatorios(op);
    return;
}

void exibeamigo(bool prolongar, bool rel)
{

    CLS if (!prolongar)
    {
        printf("AMIGOS:\n\n");
        for (int i = 0; i < Numamigo; i++)
        {
            printf("%d Amigo: %s, (%s)\n", i + 1, Listaamigo[i].nome, Listaamigo[i].apelido);
            printf("---------------------\n");
        }
    }

    else if (prolongar)
    {
        printf("AMIGOS [%d]:\n\n", Numamigo);
        for (int i = 0; i < Numamigo; i++)
        {
            printf("---------------------\n");
            printf("Amigo [%d]: \n\n", i + 1);
            printf("Nome: %s\n", Listaamigo[i].nome);
            printf("Apelido: %s\n", Listaamigo[i].apelido);
            printf("Email: %s\n", Listaamigo[i].email);
            printf("Telefone: %s\n", Listaamigo[i].telefone);
            printf("Nascimento: (%d/%d/%d)\n", Listaamigo[i].nascimento.dia, Listaamigo[i].nascimento.mes, Listaamigo[i].nascimento.ano);
            printf("---------------------\n\n\n");
        }
    }

    if (rel)
    {
        SPAUSE
    }
    return;
}

void editaamigo()
{
    int opAmigo = 0, i = 1;
    char editor;

    CLS
        printf("Digite 1 para pesquisar seu amigo pelo nome\n");
    printf("Digite 2 para exibir a lista de amigos\n");
    printf("Digite 3 para voltar\nDigite a opcao:");

    char opIn = valida13();

    if (opIn == '1')
    {
        i = buscaxnome(1);
        menueditaamigo(i);
        printf("\n\nDigite para editar: ");
        editor = valida13();
        alteraramigo(editor, i);
    }
    else if (opIn == '2')
    {
        printf("Qual o numero do amigo que deseja editar?: \n");
        exibeamigo(false, false);
        while (opAmigo < 1 || opAmigo > Numamigo)
        {
            scanf(" %d", &opAmigo);
            if (opAmigo < 1 || opAmigo > Numamigo)
            {
                ERRO(2);
            }
        }
        opAmigo--;
        menueditaamigo(opAmigo);
        editor = valida15();
        alteraramigo(editor, opAmigo);
    }
    else
    {
        return;
    }
}

void alteraramigo(char editor, int amigo)
{

    char str[100];

    switch (editor)
    {
    case '1':
        printf("Qual o novo nome de %s?: ", Listaamigo[amigo].nome);
        do
        {
            GTS if (validanome(str))
            {
                Listaamigo[Numamigo].nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
                verifica_alocacao(Listaamigo[Numamigo].nome);
                strcpy(Listaamigo[Numamigo].nome, str);
                break;
            }
            else
            {
                printf("\nJa existe um amigo com este nome.\nAdicione um sobrenome para diferencia-lo: ");
            }
        } while (!validanome(str));
        break;

    case '2':
        printf("Qual o novo apelido de %s?: ", Listaamigo[amigo].nome);
        GTS
            Listaamigo[Numamigo]
                .apelido = (char *)malloc((strlen(str) + 1) * sizeof(char));
        strcpy(Listaamigo[Numamigo].apelido, str);
        break;

    case '3':
        do
        {
            GTS if (validanumero(str))
            {
                Listaamigo[Numamigo].telefone = (char *)malloc((strlen(str) + 1) * sizeof(char));
                verifica_alocacao(Listaamigo[Numamigo].telefone);
                strcpy(Listaamigo[Numamigo].telefone, str);
            }
            else
            {
                printf("Ja existe um amigo com este telefone.\nDigite novamente: ");
            }

        } while (!validanumero(str));
        break;

    case '4':
        printf("Qual o novo email de %s?: ", Listaamigo[amigo].nome);
        do
        {
            GTS if (validaemail(str))
            {
                Listaamigo[Numamigo].email = (char *)malloc((strlen(str) + 1) * sizeof(char));
                verifica_alocacao(Listaamigo[Numamigo].email);
                strcpy(Listaamigo[Numamigo].email, str);
            }
            else
            {
                printf("Email invalido! O email deve conter 1 '@' e ao menos 1 '.'\n");
                printf("Digite novamente: ");
            }
        } while (!validaemail(str));
        break;

    case '5':
        printf("Qual eh a data de nascimento de %s? (dd mm aaaa): ", Listaamigo[Numamigo].nome);
        do
        {
            scanf("%d%d%d", &Listaamigo[Numamigo].nascimento.dia, &Listaamigo[Numamigo].nascimento.mes, &Listaamigo[Numamigo].nascimento.ano);
            if (!(validanascimento(Listaamigo[Numamigo].nascimento.dia, Listaamigo[Numamigo].nascimento.mes, Listaamigo[Numamigo].nascimento.ano)))
            {
                ERRO(-1);
            }
        } while (!(validanascimento(Listaamigo[Numamigo].nascimento.dia, Listaamigo[Numamigo].nascimento.mes, Listaamigo[Numamigo].nascimento.ano)));
        break;
    }

    printf("Amigo Editado com sucesso!");
    Sleep(1500);
    return;
}

void menueditaamigo(int opAmigo)
{
    CLS
        printf("Digite 1 para alterar o nome (%s)\n", Listaamigo[opAmigo].nome);
    printf("Digite 2 para alterar o apelido (%s)\n", Listaamigo[opAmigo].apelido);
    printf("Digite 3 para alterar o numero de telefone (%s)\n", Listaamigo[opAmigo].telefone);
    printf("Digite 4 para alterar o email (%s)\n", Listaamigo[opAmigo].email);
    printf("Digite 5 para alterar a data de nasicemnto (%d/%d/%d)\n", Listaamigo[opAmigo].nascimento.dia, Listaamigo[opAmigo].nascimento.mes, Listaamigo[opAmigo].nascimento.ano);
}

void excluiamigo(int opAmigo)
{
    free(Listaamigo[opAmigo].nome);
    free(Listaamigo[opAmigo].apelido);
    free(Listaamigo[opAmigo].email);
    free(Listaamigo[opAmigo].telefone);

    if (opAmigo < Numamigo)
    {
        for (int i = opAmigo; i < Numamigo - 1; i++)
        {
            Listaamigo[i] = Listaamigo[i + 1];
        }
    }

    Numamigo--;
    Listaamigo = (tAmigo *)realloc(Listaamigo, Numamigo * sizeof(tAmigo)); // realloca a Lista para o novo tamanho de Numamigo
    verifica_alocacao(Listaamigo);
    printf("Amigo excluido com sucesso!\n");
    Sleep(2000);
    menuamigo();
}

void orientaexcluiamigo()
{
    int opAmigo;

    CLS
        printf("Digite 1 para pesquisar seu amigo pelo nome\n");
    printf("Digite 2 para exibir a lista de amigos\n");
    printf("Digite 3 para voltar\nDigite a opcao: ");
    char opIn = valida13();

    if (opIn == '1')
    {
        opAmigo = buscaxnome(1);
        excluiamigo(opAmigo);
    }
    else if (opIn == '2')
    {

        printf("Qual o numero do amigo que deseja excluir?: ");
        exibeamigo(false, false);

        while (opAmigo < 1 || opAmigo > Numamigo)
        {
            scanf(" %d", &opAmigo);
            if (opAmigo < 1 || opAmigo >= Numamigo)
            {
                printf("Amigo inválido! Digite novamente: \n");
            }
        }
        opAmigo--;
        excluiamigo(opAmigo);
    }
    else
    {
        return;
    }
}

void limpaamigo()
{
    for (int i = 0; i < Numamigo; i++)
    {
        free(Listaamigo[i].nome);
        free(Listaamigo[i].apelido);
        free(Listaamigo[i].email);
        free(Listaamigo[i].telefone);
    }
    free(Listaamigo);
    return;
}
void limpalocal()
{
    for (int i = 0; i < Numlocal; i++)
    {
        free(Listalocal[i].endereco.estado);
        free(Listalocal[i].endereco.cidade);
        free(Listalocal[i].endereco.bairro);
        free(Listalocal[i].endereco.numero);
        free(Listalocal[i].endereco.logradouro);
        free(Listalocal[i].nomelocal);
    }
    free(Listalocal);
    return;
}
void limpacategoria()
{
    for (int i = 0; i < Numcategoria; i++)
    {
        free(Listacategoria[i].categoria);
    }
    free(Listacategoria);
    return;
}
void limpaencontro()
{
    for (int i = 0; i < Numencontro; i++)
    {
        free(Listaencontro[i].nome);
        free(Listaencontro[i].descricao);
        free(Listaencontro[i].amigos);
        Listaencontro[i].amigos = NULL;
    }
    free(Listaencontro);
    return;
}

void limpamemoria()
{
    if (Numamigo != 0)
    {
        limpaamigo();
    }

    if (Numlocal != 0)
    {
        limpalocal();
    }

    if (Numcategoria != 0)
    {
        limpacategoria();
    }

    if (Numencontro != 0)
    {
        limpaencontro();
    }
    return;
}

void end()
{
    char word[] = "Obrigado por trabalhar com nossos produtos!";

    CLS for (int i = 0; word[i] != '\0'; i++)
    {
        printf("%c", word[i]);
        Sleep(55);
    }
    Sleep(750);
    exit(0);
}

void verifica_alocacao(void *v)
{
    if (!v)
    {
        ERRO(4);
        Sleep(1000);
        limpamemoria();
    }
}

char valida16()
{
    char op;
    do
    {
        scanf(" %c", &op);
        if (op != '1' && op != '2' && op != '3' && op != '4' && op != '5' && op != '6')
        {
            ERRO(1);
        }
    } while (op != '1' && op != '2' && op != '3' && op != '4' && op != '5' && op != '6');

    return op;
}

bool validadataenc(int dias, int mes, int ano)
{
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (ano < 2025)
        return false;
    if (mes < 1 || mes > 12)
        return false;
    if (dias < 1 || dias > meses[mes - 1])
        return false;
    if (ano % 4 == 0 && mes == 2 && dias > 29)
        return false;
    if (ano == 2025 && mes == 2 && dias < 6)
        return false;

    return true;
}

bool validanascimento(int dias, int mes, int ano)
{
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (ano < 1894 || ano > 2024)
        return false;
    if (dias < 1 || dias > meses[mes - 1])
        return false;
    if (mes == 2 && ano % 4 == 0 && dias > 29)
        return false;
    return true;
}

void incluiamigo()
{
    CLS
        printf("Voce tem [%d] amigo(s) no momento.\n\n", Numamigo);

    if (Numamigo == 0)
    {
        Listaamigo = (tAmigo *)malloc(1 * sizeof(tAmigo));
    }
    else
    {
        Listaamigo = (tAmigo *)realloc(Listaamigo, (Numamigo + 1) * sizeof(tAmigo));
    }
    verifica_alocacao(Listaamigo);
    Listaamigo[Numamigo] = criaamigo();
    Numamigo++;

    CLS
        printf("Amigo criado com sucesso!\n");
    Sleep(2000);
    return;
}

tAmigo criaamigo()
{

    char str[100];
    tAmigo amigo;

    printf("Qual o nome do seu %d amigo?: ", Numamigo + 1);
    do
    {
        GTS if (validanome(str))
        {
            amigo.nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
            verifica_alocacao(amigo.nome);
            strcpy(amigo.nome, str);
            break;
        }
        else
        {
            printf("\nJa existe um amigo com este nome.\nAdicione um sobrenome para diferencia-lo: ");
        }
    } while (!validanome(str));

    printf("Qual eh o apelido de %s?: ", amigo.nome);
    GTS
        amigo
            .apelido = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(amigo.apelido);
    strcpy(amigo.apelido, str);

    printf("Qual eh o telefone do seu amigo?: ");
    do
    {
        GTS if (validanumero(str))
        {
            amigo.telefone = (char *)malloc((strlen(str) + 1) * sizeof(char));
            verifica_alocacao(amigo.telefone);
            strcpy(amigo.telefone, str);
        }
        else
        {
            printf("Ja existe um amigo com este telefone.\nDigite novamente: ");
        }

    } while (!validanumero(str));

    printf("Qual o email de %s?: ", amigo.nome);
    do
    {
        GTS if (validaemail(str))
        {
            amigo.email = (char *)malloc((strlen(str) + 1) * sizeof(char));
            verifica_alocacao(amigo.email);
            strcpy(amigo.email, str);
        }
    } while (!validaemail(str));

    printf("Qual eh a data de nascimento de %s? (dd mm aaaa): ", amigo.nome);
    do
    {
        scanf("%d%d%d", &amigo.nascimento.dia, &amigo.nascimento.mes, &amigo.nascimento.ano);
        if (!(validanascimento(amigo.nascimento.dia, amigo.nascimento.mes, amigo.nascimento.ano)))
        {
            ERRO(-1);
        }
    } while (!(validanascimento(amigo.nascimento.dia, amigo.nascimento.mes, amigo.nascimento.ano)));

    CLS return amigo;
}

void switchamigo(char op)
{
    switch (op)
    {
    case '1':
        incluiamigo();
        break;
    case '2':
        if (Numamigo == 0)
        {
            printf("Nao ha amigos para serem editados!");
            Sleep(2500);
            menuamigo();
        }
        else
        {
            editaamigo();
            break;
        }

    case '3':
        if (Numamigo == 0)
        {
            printf("Nao ha amigos para serem excluidos!");
            Sleep(2500);
            menuamigo();
        }
        else if (Numamigo < 2)
        {
            if (adviser())
            {
                orientaexcluiamigo();
            }
        }
        else
        {
            orientaexcluiamigo();
        }
        break;
    case '4':
        break;
    }
    return;
}

void mainamigo()
{
    char op;
    while (op != '4')
    {
        menuamigo();
        op = valida14();
        if (op == '4')
        {
            break;
        }
        switchamigo(op);
    }
    return;
}

void menuamigo()
{

    CLS
        printf("***MENU AMIGO***\n\nDigite:\n");
    printf("1. para criar um amigo\n");
    printf("2. para editar um amigo\n");
    printf("3. para excluir um amigo\n");
    printf("4. para voltar\n");
    printf("\nO que deseja fazer?: ");
}

void switchprincipal(char op)
{

    switch (op)
    {
    case '5':
        menurelatorios();
        break;

    case '1':
        mainamigo();
        break;

    case '2':
        mainlocal();
        break;

    case '3':
        maincat();
        break;

    case '4':
        mainencontro();
        break;
    }
    return;
}

void menuprincipal()
{
    CLS
        printf("***MENU PRINCIPAL***\n\n");
    printf("Digite:\n");
    printf("1. para manter amigo\n");
    printf("2. para manter local\n");
    printf("3. para manter categoria\n");
    printf("4. para manter encontro\n");
    printf("5. para Relatorios\n");
    printf("6. para Sair\n");
    printf("\nO que deseja fazer?: ");
}

bool validanome(char *nome)
{

    for (int i = 0; i < Numamigo; i++)
    {
        if (strcmp(nome, Listaamigo[i].nome) == 0)
        {
            return false;
        }
    }
    return true;
}

bool validaemail(char *email)
{

    int countA = 0, countB = 0;

    // step 1v
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            countA++;
        }
        else if (email[i] == '.')
        {
            countB++;
        }
    }

    if (countA != 1 || countB < 1)
    {
        printf("Email invalido! O email deve conter 1 '@' e ao menos 1 '.'\n");
        return false;
    }

    // step 2v
    for (int i = 0; i < Numamigo; i++)
    {
        if (strcmp(email, Listaamigo[i].email) == 0)
        {
            printf("Email invalido! Este email ja existe!\n");
            return false;
        }
    }
    return true;
}

bool validanumero(char *num)
{

    for (int i = 0; i < Numamigo; i++)
    {
        if (strcmp(num, Listaamigo[i].telefone) == 0)
        {
            return false;
        }
    }
    return true;
}

int buscaxnome(int op)
{
    int i;
    char str[100];

    CLS while (1)
    {
        printf("Digite o nome a ser buscado: ");
        GTS
            printf("Buscando");
        for (int j = 0; j < 3; j++)
        {
            printf(".");
            Sleep(400);
        }
        CLS switch (op)
        {
        case 1:
            for (i = 0; i < Numamigo; i++)
            {
                if (strcmp(Listaamigo[i].nome, str) == 0)
                {
                    printf("Amigo encontrado!");
                    Sleep(1000);
                    CLS return i;
                }
            }
            ERRO(3);
            Sleep(1500);
        case 2:
            for (i = 0; i < Numlocal; i++)
            {
                if (strcmp(Listalocal[i].nomelocal, str) == 0)
                {
                    printf("Local encontrado!");
                    Sleep(1000);
                    CLS return i;
                }
            }
            ERRO(20);
            Sleep(1500);
        case 3:
            for (i = 0; i < Numcategoria; i++)
            {
                if (strcmp(Listacategoria[i].categoria, str) == 0)
                {
                    printf("Categoria encontrada!");
                    Sleep(1000);
                    CLS return i;
                }
            }
            ERRO(9);
            Sleep(1500);
        }
        continue;
    }
}

bool validarhorario(int hora, int min)
{

    if (hora < 0 || hora > 23)
    {
        return false;
    }
    if (min < 0 || min > 59)
    {
        return false;
    }
    return true;
}

void ERRO(int opErro)
{

    switch (opErro)
    {
    case -2:
        printf("Data invalida! Digite novamente: ");
        break;
    case -1:
        printf("Data invalida! Digite novamente: ");
        break;
    case 0:
        printf("Realocar um vetor dinamico para 0 posicoes nao e uma boa ideia.\nTem certeza de que deseja prosseguir?(S/N): ");
        break;
    case 1:
        printf("Operador invalido! Digite novamente: ");
        break;
    case 2:
        printf("Amigo invalido! Digite novamente: ");
        break;
    case 3:
        printf("Amigo nao encontrado! Digite novamente: ");
        break;
    case 4:
        printf("ERRO AO ALOCAR MEMORIA!!!");
        break;
    case 5:
        printf("Nao existem amigos para serem editados!");
        break;
    case 6:
        printf("Nao existem amigos para serem excluidos!");
        break;
    case 7:
        printf("Nao existem amigos para serem listados!");
        break;
    case 8:
        printf("Categoria invalida! Digite novamente: ");
        break;
    case 9:
        printf("Categotria nao encontrada! Digite novamente: ");
        break;
    case 10:
        printf("Nao existem categorias para serem listadas!");
        break;
    case 11:
        printf("Nao existem categorias para serem editadas!");
        break;
    case 12:
        printf("Nao existem categorias para serem excluidas!");
        break;
    case 13:
        printf("Encontro invalido! Digite novamente: ");
        break;
    case 14:
        printf("Encontro nao encontrado! Digite novamente: ");
        break;
    case 15:
        printf("Nao existem encontros para serem listados!");
        break;
    case 16:
        printf("Nao existem encontros para serem editados!");
        break;
    case 17:
        printf("Nao existem encontros para serem listados!");
        break;
    case 18:
        printf("Nao existem Locais para serem listados!");
        break;
    case 19:
        printf("Local invalido! Digite novamente: ");
        break;
    case 20:
        printf("Local nao encontrado! Digite novamente: ");
        break;
    case 21:
        printf("Nao existem Locais para serem editados!");
        break;
    case 22:
        printf("Nao existem Locais para serem excluidos!");
        break;
    default:
        printf("___FUDEU MUITO___");
        limpamemoria();
    }
}
