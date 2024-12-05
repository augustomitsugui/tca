#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{

    char *bairro, *cidade, *estado, *logradouro, *num;

} SPlace;

typedef struct
{
    int dia, mes, ano;

} SData;

typedef struct
{
    char *nome;
    SData datanasc;
    char *apelido;
    char *email;
    char *telefone;

} SAmigo;

typedef struct
{
    char *nomelocal;
    SPlace local;
} SLocal;

typedef struct
{
    char *nomecat;

} SCategoria;

typedef struct
{
    int hora, minuto;
} SHora;

typedef struct
{
    SData dataencontro;
    SHora horaencontro;
    char *localencontro;
    char **amigoencontro;
    int enumamigos;
    char *categoriaencontro;
    char *nomeencontro;

    char *descricao;

} SEncontro;

// aperte Ctrl K + Ctrl 0 para minimizar e acessar funções mais facilmente ;)
// aperte Ctrl K + Ctrl J para maximizar (desdobrar) TODAS as funções
// - dicas do otávio augusto :))

SAmigo *GAmigo;
int Namigo = 0;
SEncontro *GEncontro;
int NEncontro = 0;
SLocal *GLocal;
int Nlocal = 0;
SCategoria *GCategoria;
int NCat = 0;

// funcao auxiliar
void limparTela();
void flushs();
int desejaAlterar();
int validaData(int dd, int mm, int yy);
void mensagemErro(int erro);
void pause();
int validaHora(int hora, int min);

// funcao de memoria e arquivo

void salvaAmigo();
void limpaAmigo();
void recuperaAmigo();
void salvaLocal();
void limpaLocal();
void recuperaLocal();
void salvaCat();
void limpaCat();
void recuperaCat();

void recuperaDado();
void salvaDado();
void limpaDado();

// impressoras auxiliares

void listaNomesAmigo();
void listaNomesLocal();
void listaNomesCategoria();

// funcoes de menu
int menuPrincipal();
void menuAmigo();
void listaMenu();
void menuLocal();
void menuCategoria();

// funcao pros amigos
SAmigo cadastraAmigo(int num);
void imprimeAmigo(SAmigo a, int num);
void listaTodosAmigos();
void editaAmigo();
void switchAmigo(int op, int amigo);
void incluiAmigo();
void excluiAmigo();
void listaAmigo();

// funcao pros locais
SLocal cadastraLocal(int num);
void incluiLocal();
void imprimeLocal(SLocal a, int num);
void listaTodosLocais();
void editaLocal();
void switchLocal(int op, int local);
void excluiLocal();
void listaLocal();

// funcao para as caetgorias

void listaCat();
void incluiCategoria();
SCategoria cadastraCategoria(int num);
void imprimeCategoria(SCategoria c, int num);
void listaTodasCategorias();
void editaCategoria();
void switchCat(int op, int cat);
void excluiCat();

// funcoes pra encontro
void incluiEncontro();
SEncontro cadastraEncontro(int num);
void imprimeEncontro(SEncontro e, int enc);

// main e aux

int main()
{

    recuperaDado();
    int op = 0;
    while (op != 6)
    {
        op = menuPrincipal();
    }
    salvaDado();
    limpaDado();

    return 0;
}

int TodosOuUmLista()
{
    int op = 0;

    do
    {
        limparTela();
        printf("\n\nDeseja listar todos ou apenas um específico?\n1. Todos\n2. Específico\n\n");
        scanf("%d", &op);
        if (op == 1)
        {
            return 1;
        }
        else if (op == 2)
        {
            return 2;
        }
        else
        {
            mensagemErro(-1);
        }

    } while (op < 1 || op > 2);

    return 0;
}
void limparTela()
{
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Linux e macOS
#endif
}
void flushs()
{
#ifdef _WIN32
    fflush(stdin); // Windows
#else
    __fpurge(stdin); // Linux e macOS
#endif
}
void pause()
{
#ifdef _WIN32
    system("pause");
#else
    printf("\npressione qualquer tecla pra continuar. . .");
    getchar();
#endif
}

#include <stdio.h>

// Função que valida a hora
int validaHora(int hora, int min)
{
    if (hora < 0 || hora >= 24 || min < 0 || min >= 60)
    {
        return -5;
    }
    return 0;
}

int desejaAlterar()
{

    char opc = 0;
    do
    {
        limparTela();
        printf("Deseja alterar mais alguma coisa? (S/N)");
        scanf(" %c", &opc);
        if (opc == 'N' || opc == 'n')
        {

            limparTela();
            printf("Você escolheu [N], Voltando. . . \n");
            pause();
            return 0;
        }
        else if (opc == 'S' || opc == 's')
        {
            limparTela();
            printf("Você escolheu [S]. . . ");
            printf("\n");
            pause();
            return 1;
        }
        else
        {
            mensagemErro(-1);
            limparTela();
        }

    } while (opc == 'N' || opc == 'n' || opc == 'S' || opc == 's');

    return 0;
}
int validaData(int dd, int mm, int yy)
{
    if (yy >= 1900 && yy <= 9999)
    {
        if (mm >= 1 && mm <= 12)
        {
            if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
            {
                return 1;
            }
            else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
            {
                return 1;
            }
            else if ((dd >= 1 && dd <= 28) && (mm == 2))
            {
                return 1;
            }
            else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
            {
                return 1;
            }
            else
            {
                return -2;
            }
        }
        else
        {
            return -2;
        }
    }
    else
    {
        return -2;
    }
}

// menus

int menuPrincipal()
{

    limparTela();

    printf("1. Manter amigo\n");
    printf("2. Manter local\n");
    printf("3. Manter categoria\n");
    printf("4. Manter encontro\n");
    printf("5. Listas\n");
    printf("6. Sair\n");

    int op = 0;
    printf("Insira sua opção:\n");
    scanf("%d", &op);

    if (op > 6 || op < 1)
    {
        mensagemErro(-1);
    }

    switch (op)
    {
    case 1:
        menuAmigo();
        break;
    case 2:
        menuLocal();
        break;
    case 3:
        menuCategoria();
        break;
    case 4:
        menuEncontro();
    case 5:
        listaMenu();
    case 6:
        break;
    }
    limparTela();
    return op;
}
void menuAmigo()

{

    int op = 0;
    while (op != 4)
    {

        limparTela();
        printf("1. Adicionar Amigo\n");
        printf("2. Editar Amigo\n");
        printf("3. Excluir Amigo\n");
        printf("4. Voltar\n");

        printf("Insira sua opção:\n");
        scanf("%d", &op);

        if (op > 4 || op < 1)
        {
            op = -1;
            mensagemErro(op);
        }
        switch (op)
        {
        case 1:
            incluiAmigo();
            break;
        case 2:
            editaAmigo();
            break;
        case 3:
            excluiAmigo();
            break;
        }
    }
}
void menuLocal()

{

    int op = 0;
    while (op != 4)
    {

        limparTela();
        printf("1. Adicionar Local\n");
        printf("2. Editar Local\n");
        printf("3. Excluir Local\n");
        printf("4. Voltar\n");

        printf("Insira sua opção:\n");
        scanf("%d", &op);

        if (op > 4 || op < 1)
        {
            op = -1;
            mensagemErro(op);
        }
        switch (op)
        {
        case 1:
            incluiLocal();
            break;
        case 2:
            editaLocal();
            break;
        case 3:
            excluiLocal();
            break;
        case 4:
            break;
        }
    }
}
void menuCategoria()
{
    limparTela();
    printf("1. Adicionar Categoria\n");
    printf("2. Editar Categoria\n");
    printf("3. Excluir Categoria\n");
    printf("4. Voltar\n");

    int op = 0;
    printf("Insira sua opção:\n");
    scanf("%d", &op);

    if (op > 3 || op < 1)
    {
        op = -1;
        mensagemErro(op);
    }
    switch (op)
    {
    case 1:
        incluiCategoria();
        break;
    case 2:
        editaCategoria();
        break;
    case 3:
        excluiCat();
        break;
    case 4:
        break;
    }
}
void menuEncontro()
{

    limparTela();
    printf("1. Adicionar Encontro\n");
    printf("2. Editar Encontro\n");
    printf("3. Excluir Encontro\n");
    printf("4. Voltar\n");

    int op = 0;
    printf("Insira sua opção:\n");
    scanf("%d", &op);

    if (op > 4 || op < 1)
    {
        op = -1;
        mensagemErro(op);
    }
    switch (op)
    {
    case 1:
        incluiEncontro();
        break;
    case 2:
        // editaEncontro();
        break;
    case 3:
        //  excluiEncontro();
        break;
    case 4:
        menuPrincipal();
        break;
    }
}
void listaMenu()
{

    limparTela();
    printf("1. Listar amigos\n");
    printf("2. Listar locais\n");
    printf("3. Listar categorias\n");
    printf("4. Listar encontros\n");
    printf("5. Relatorio por Categoria\n");
    printf("6. Voltar\n");

    int op = 0;
    printf("Insira sua opção:\n");
    scanf("%d", &op);

    if (op > 6 || op < 1)
    {
        op = -1;
        mensagemErro(op);
    }
    switch (op)
    {
    case 1:
        listaAmigo();
        break;
    case 2:
        listaLocal();
        break;
    case 3:
        listaCat();
        break;
    case 4:
        // listaTodosEncontros
    case 5:
        // Relatorio por categoria (janta = 1 2, cinema = 4 5 6, escola = 3)
    case 6:
        break;
    }
}

// funcoes de recuperação salvamento e limpeza
void recuperaDado()
{
    recuperaAmigo();
    recuperaLocal();
    recuperaCat();
}
void salvaDado()
{

    salvaAmigo();
    salvaLocal();
    salvaCat();
}
void limpaDado()
{
    limpaAmigo();
    limpaLocal();
    limpaCat();
}

void recuperaAmigo()
{
    int i, sep = 0;
    char str[200], c;

    FILE *pArq;
    pArq = fopen("amigos.txt", "r");
    if (pArq)
    {
        i = 0;

        while ((c = fgetc(pArq)) != EOF)
        {
            if ((c != '\n') && (c != '!'))
            {
                str[i++] = c;
            }
            else if (c == '!' || c == '\n')
            {

                str[i] = '\0';
                i = 0;

                if (sep == 0)
                {
                    if (Namigo == 0)
                    {
                        GAmigo = (SAmigo *)malloc(1 * sizeof(SAmigo));
                    }
                    else
                    {
                        GAmigo = (SAmigo *)realloc(GAmigo, (Namigo + 1) * sizeof(SAmigo));
                    }

                    GAmigo[Namigo].nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GAmigo[Namigo].nome, str);
                }
                else if (sep == 1)
                { // apelido
                    GAmigo[Namigo].apelido = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GAmigo[Namigo].apelido, str);
                }
                else if (sep == 2)
                { // telefone
                    GAmigo[Namigo].telefone = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GAmigo[Namigo].telefone, str);
                }
                else if (sep == 3)
                { // email
                    GAmigo[Namigo].email = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GAmigo[Namigo].email, str);
                }
                else if (sep == 4)
                { // dia nasc
                    GAmigo[Namigo].datanasc.dia = atoi(str);
                }
                else if (sep == 5)
                { // mes nasc
                    GAmigo[Namigo].datanasc.mes = atoi(str);
                }
                else if (sep == 6)
                { // ano nasc
                    GAmigo[Namigo].datanasc.ano = atoi(str);
                }
                sep++;

                if (c == '\n')
                {
                    Namigo++;
                    sep = 0;
                }
            }
        }
    }
    fclose(pArq);
}
void salvaAmigo()
{
    FILE *pArq;

    pArq = fopen("amigos.txt", "w");

    if (pArq == NULL)
    {
        printf("ERRO: Não foi possível salvar as informações.\n");
        exit(0);
    }

    for (int i = 0; i < Namigo; i++)
    {
        fprintf(pArq, "%s!", GAmigo[i].nome);
        fprintf(pArq, "%s!", GAmigo[i].apelido);
        fprintf(pArq, "%s!", GAmigo[i].email);
        fprintf(pArq, "%s!", GAmigo[i].telefone);
        fprintf(pArq, "%i!", GAmigo[i].datanasc.dia);
        fprintf(pArq, "%i!", GAmigo[i].datanasc.mes);
        fprintf(pArq, "%i!", GAmigo[i].datanasc.ano);
        fprintf(pArq, "%c", '\n');
    }

    fclose(pArq);
}
void limpaAmigo()
{
    if (Namigo == 0)
    {
        return;
    }

    else
    {
        for (int i = 0; i < Namigo; i++)
        {
            free(GAmigo[i].nome);
            free(GAmigo[i].apelido);
            free(GAmigo[i].email);
            free(GAmigo[i].telefone);
        }

        free(GAmigo);
    }
}

void recuperaCat()
{
    int i;
    char str[100], c;

    FILE *pArq;
    pArq = fopen("cat.txt", "r");
    if (pArq)
    {
        i = 0;

        while ((c = fgetc(pArq)) != EOF)

        {

            if ((c != '\n') && (c != '!') && (c != EOF))
            {
                str[i++] = c;
            }

            else if ((c == '!') || (c == '\n'))
            {
                str[i] = '\0';
                i = 0;

                if (c == '!') // nome
                {
                    if (NCat == 0)
                    {
                        GCategoria = (SCategoria *)malloc(1 * sizeof(SCategoria));
                    }
                    else
                    {
                        GCategoria = (SCategoria *)realloc(GCategoria, (NCat + 1) * sizeof(SCategoria));
                    }

                    GCategoria[NCat].nomecat = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GCategoria[NCat].nomecat, str);
                }
                else if (c == '\n')
                {
                    NCat++;
                }
            }
        }
    }
    fclose(pArq);
}
void salvaCat()
{

    FILE *pArq;

    pArq = fopen("cat.txt", "w");

    if (pArq == NULL)
    {
        printf("ERRO: Nao foi possivel salvar as informaceos");
        exit(0);
    }

    for (int i = 0; i < NCat; i++)
    {
        fprintf(pArq, "%s!", GCategoria[i].nomecat);
        fprintf(pArq, "%c", '\n');
    }

    fclose(pArq);
}
void limpaCat()
{
    if (NCat == 0)
    {
        return;
    }

    else
    {
        for (int i = 0; i < NCat; i++)
        {
            free(GCategoria[i].nomecat);
        }

        free(GCategoria);
    }
}

void recuperaLocal()
{
    int i, sep = 0;
    char str[200], c;

    FILE *pArq;
    pArq = fopen("locais.txt", "r");
    if (pArq)
    {
        i = 0;

        while ((c = fgetc(pArq)) != EOF)
        {
            if ((c != '\n') && (c != '!'))
            {
                str[i++] = c;
            }
            else if (c == '!' || c == '\n')
            {

                str[i] = '\0';
                i = 0;

                if (sep == 0)
                { // nome
                    if (Nlocal == 0)
                    {
                        GLocal = (SLocal *)malloc(1 * sizeof(SLocal));
                    }
                    else
                    {
                        GLocal = (SLocal *)realloc(GLocal, (Nlocal + 1) * sizeof(SLocal));
                    }

                    GLocal[Nlocal].nomelocal = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GLocal[Nlocal].nomelocal, str);
                    sep++;
                }
                else if (sep == 1)
                { // bairro
                    GLocal[Nlocal].local.bairro = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GLocal[Nlocal].local.bairro, str);
                    sep++;
                }
                else if (sep == 2)
                { // cidade
                    GLocal[Nlocal].local.cidade = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GLocal[Nlocal].local.cidade, str);
                    sep++;
                }
                else if (sep == 3)
                { // estado
                    GLocal[Nlocal].local.estado = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GLocal[Nlocal].local.estado, str);
                    sep++;
                }
                else if (sep == 4)
                { // logradouro
                    GLocal[Nlocal].local.logradouro = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GLocal[Nlocal].local.logradouro, str);
                    sep++;
                }
                else if (sep == 5)
                { // num
                    GLocal[Nlocal].local.num = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GLocal[Nlocal].local.num, str);
                    sep++;
                }

                if (c == '\n')
                {
                    Nlocal++; // Incrementa o número de locais após processar uma linha
                    sep = 0;  // Resetar para a próxima linha
                }
            }
        }
    }
    fclose(pArq);
}
void salvaLocal()
{

    FILE *pArq;

    pArq = fopen("locais.txt", "w");

    if (pArq == NULL)
    {
        printf("ERRO: Nao foi possivel salvar as informaceos");
        exit(0);
    }

    for (int i = 0; i < Nlocal; i++)
    {
        fprintf(pArq, "%s!", GLocal[i].nomelocal);
        fprintf(pArq, "%s!", GLocal[i].local.bairro);
        fprintf(pArq, "%s!", GLocal[i].local.cidade);
        fprintf(pArq, "%s!", GLocal[i].local.estado);
        fprintf(pArq, "%s!", GLocal[i].local.logradouro);
        fprintf(pArq, "%s!", GLocal[i].local.num);
        fprintf(pArq, "%c", '\n');
    }

    fclose(pArq);
}
void limpaLocal()
{
    if (Nlocal == 0)
    {
        return;
    }

    else
    {
        for (int i = 0; i < Nlocal; i++)
        {
            free(GLocal[i].nomelocal);
            free(GLocal[i].local.bairro);
            free(GLocal[i].local.cidade);
            free(GLocal[i].local.estado);
            free(GLocal[i].local.logradouro);
            free(GLocal[i].local.num);
        }

        free(GLocal);
    }
}

// impressoras

void imprimeAmigo(SAmigo a, int num)
{
    printf("Amigo [%d]\n", num + 1);
    printf("Nome: %s\n", a.nome);
    printf("Apelido: %s\n", a.apelido);
    printf("Telefone: %s\n", a.telefone);
    printf("E-Mail: %s\n", a.email);
    printf("Data de Nascimento: %02d  /  %02d  /  %04d\n", a.datanasc.dia, a.datanasc.mes, a.datanasc.ano);
}
void listaTodosAmigos()
{
    limparTela();
    if (Namigo < 1)
    {
        printf("não existem amigos! adicione um amigo!\n");
    }
    else
    {
        for (int i = 0; i < Namigo; i++)
        {
            imprimeAmigo(GAmigo[i], i);
            printf("\n");
        }
    }
}

void imprimeLocal(SLocal a, int num)

{

    printf("Local [%d]\n", num + 1);
    printf("Nome do Local: %s\n", a.nomelocal);
    printf("Bairro: %s\n", a.local.bairro);
    printf("Cidade: %s\n", a.local.cidade);
    printf("Estado: %s\n", a.local.estado);
    printf("Logradouro: %s\n", a.local.logradouro);
    printf("Número: %s\n", a.local.num);
}
void listaTodosLocais()

{
    limparTela();
    if (Nlocal < 1)
    {
        printf("não existem locais! adicione um local!\n");
    }
    else
    {
        for (int i = 0; i < Nlocal; i++)
        {
            imprimeLocal(GLocal[i], i);
            printf("\n");
        }
    }
}

void imprimeCategoria(SCategoria c, int num)
{
    printf("\nCategoria [%d]\n", num + 1);
    printf("Nome: %s\n\n", c.nomecat);
}
void listaTodasCategorias()
{
    limparTela();
    if (NCat < 1)
    {
        printf("não existem cateogiras! adicione!\n");
    }
    else
    {
        for (int i = 0; i < NCat; i++)
        {
            imprimeCategoria(GCategoria[i], i);
        }
    }
}

void listaNomesAmigo()
{
    limparTela();
    if (Namigo < 1)
    {
        printf("não existe nada adicionado! adicione!!");
        return;
    }

    printf("Amigos:\n\n");

    for (int i = 0; i < Namigo; i++)
    {

        printf("%d. [%s]\n", i + 1, GAmigo[i].nome);
    }
}
void listaNomesLocal()
{

    limparTela();
    printf("Locais:\n\n");

    for (int i = 0; i < Nlocal; i++)
    {

        printf("%d. [%s]\n", i + 1, GLocal[i].nomelocal);
    }
}
void listaNomesCategoria()
{

    limparTela();
    printf("Categorias:\n\n");

    for (int i = 0; i < NCat; i++)
    {

        printf("%d. [%s]\n", i + 1, GCategoria[i].nomecat);
    }
}

void listaAmigo()
{
    int op;
    if (Namigo < 1)
    {
        printf("não existe nada adicionado! adicione!!");
        pause();
        return;
    }

    if (TodosOuUmLista() == 1)
    {
        listaTodosAmigos();
    }
    else
    {
        listaNomesAmigo();
        printf("\nqual deles?");
        scanf("%d", &op);
        op--;
        limparTela();
        imprimeAmigo(GAmigo[op], op);
    }
    pause();
    return;
}
void listaLocal()
{
    int op;
    if (Nlocal < 1)
    {
        printf("não existe nada adicionado! adicione!!");
        pause();
        return;
    }

    if (TodosOuUmLista() == 1)
    {
        listaTodosLocais();
    }
    else
    {
        listaNomesLocal();
        printf("\nqual deles?");
        scanf("%d", &op);
        op--;
        imprimeLocal(GLocal[op], op);
    }
    pause();
    return;
}
void listaCat()
{
    int op;
    if (NCat < 1)
    {
        printf("não existe nada adicionado! adicione!!");
        pause();
        return;
    }

    if (TodosOuUmLista() == 1)
    {
        listaTodasCategorias();
    }

    else
    {
        listaNomesCategoria();
        printf("\nqual deles?\n");
        scanf("%d", &op);
        op--;
        imprimeCategoria(GCategoria[op], op);
    }

    pause();

    return;
}

// cadastro

void incluiAmigo()
{
    if (Namigo == 0)
    {
        GAmigo = (SAmigo *)malloc(1 * sizeof(SAmigo));
    }
    else
    {
        GAmigo = (SAmigo *)realloc(GAmigo, (Namigo + 1) * sizeof(SAmigo));
    }

    GAmigo[Namigo] = cadastraAmigo(Namigo);
    Namigo++;
}
SAmigo cadastraAmigo(int num)
{
    SAmigo a;
    char strAux[100];
    int erro = 0, ig = 0;

    while (erro != 1)
    {
        limparTela();
        printf("nome do amigo: ");
        flushs();
        gets(strAux);
        flushs();

        if (Namigo > 0)
        {
            for (int i = 0; i < Namigo; i++)
            {
                ig = (strcmp(strAux, GAmigo[i].nome));

                if (ig != 0)
                {
                    mensagemErro(-3);
                    erro = 2;
                    break;
                }
            }
        }

        else if (Namigo > 0 && erro != 2)
        {
            erro = 1;
            a.nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(a.nome, strAux);
            flushs();
        }
    }

    limparTela();
    printf("apelido do amigo: ");
    flushs();
    gets(strAux);
    flushs();
    a.apelido = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(a.apelido, strAux);
    flushs();

    limparTela();
    printf("telefone do amigo: ");
    flushs();
    gets(strAux);
    flushs();
    a.telefone = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(a.telefone, strAux);
    flushs();

    limparTela();
    printf("email do amigo: ");
    flushs();
    gets(strAux);
    flushs();
    a.email = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(a.email, strAux);
    flushs();

    erro = 0;
    while (erro != 1)
    {
        printf("dia de nascimento do amigo:\n");
        scanf("%d", &a.datanasc.dia);
        flushs();
        printf("mes de nascimento do amigo:\n");
        scanf("%d", &a.datanasc.mes);
        flushs();
        printf("ano de nascimento do amigo:\n");
        scanf("%d", &a.datanasc.ano);
        flushs();

        erro = validaData(a.datanasc.dia, a.datanasc.mes, a.datanasc.ano);

        if (erro != 1)
        {
            mensagemErro(erro);
        }
    }

    limparTela();
    printf("Amigo adicionado!\n");
    imprimeAmigo(a, num);
    pause();

    return a;
}

void incluiLocal()
{
    if (Nlocal == 0)
    {
        GLocal = (SLocal *)malloc(1 * sizeof(SLocal));
    }
    else
    {
        GLocal = (SLocal *)realloc(GLocal, (Nlocal + 1) * sizeof(SLocal));
    }

    GLocal[Nlocal] = cadastraLocal(Nlocal);
    Nlocal++;
}
SLocal cadastraLocal(int num)
{

    SLocal l;
    char strAux[100];

    limparTela();
    printf("nome do local: ");
    flushs();
    gets(strAux);
    flushs();
    l.nomelocal = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(l.nomelocal, strAux);
    flushs();

    limparTela();
    printf("bairro do local [%s]: ", l.nomelocal);
    flushs();
    gets(strAux);
    flushs();
    l.local.bairro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(l.local.bairro, strAux);
    flushs();

    limparTela();
    printf("cidade do local [%s]: ", l.nomelocal);
    flushs();
    gets(strAux);
    flushs();
    l.local.cidade = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(l.local.cidade, strAux);
    flushs();

    limparTela();
    printf("estado do local [%s]: ", l.nomelocal);
    flushs();
    gets(strAux);
    flushs();
    l.local.estado = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(l.local.estado, strAux);
    flushs();

    limparTela();
    printf("logradouro (rua, avenida, viela, etc) do local [%s]: ", l.nomelocal);
    flushs();
    gets(strAux);
    flushs();
    l.local.logradouro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(l.local.logradouro, strAux);
    flushs();

    limparTela();
    printf("número do local [%s]: ", l.nomelocal);
    flushs();
    gets(strAux);
    flushs();
    l.local.num = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(l.local.num, strAux);
    flushs();

    limparTela();
    printf("Local adicionado!\n");
    imprimeLocal(l, num);
    pause();

    return l; // parece um numero 1 mas é um l
}

void incluiCategoria()
{
    if (NCat == 0)
    {
        GCategoria = (SCategoria *)malloc(1 * sizeof(SCategoria));
    }
    else
    {
        GCategoria = (SCategoria *)realloc(GCategoria, (NCat + 1) * sizeof(SCategoria));
    }

    GCategoria[NCat] = cadastraCategoria(NCat);
    NCat++;
}
SCategoria cadastraCategoria(int num)
{

    SCategoria c;
    char strAux[100];

    limparTela();
    printf("nome da categoria: ");
    flushs();
    gets(strAux);
    flushs();
    c.nomecat = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(c.nomecat, strAux);
    flushs();
    limparTela();

    printf("Categoria adicionada!\n");
    imprimeCategoria(c, num);
    pause();

    return c;
}

// editores

void editaAmigo()
{
    int auxEdita = 1;

    while (auxEdita)
    {
        int op = 0;
        if (Namigo == 0)
        {
            limparTela();
            printf("Não há amigos disponíveis para editar! Adicione um Amigo!\n");
            pause();
            return;
        }

        limparTela();
        printf("Que amigo você deseja editar?\n\n");

        for (int i = 0; i < Namigo; i++)
        {
            imprimeAmigo(GAmigo[i], i);
            printf("\n");
        }

        while (op < 1 || op > Namigo)
        {
            printf("Escolha um amigo: ");
            scanf("%d", &op);
            if (op < 1 || op > Namigo)
            {
                op = -1;
                mensagemErro(op);
            }
        }
        limparTela();

        imprimeAmigo(GAmigo[op - 1], op - 1);

        int amigo = op;

        printf("\n\nO que você deseja editar?\n");
        printf("1. Nome\n");
        printf("2. Apelido\n");
        printf("3. Telefone\n");
        printf("4. Email\n");
        printf("5. Data Nasc\n");
        printf("6. Voltar\n");
        op = 0;
        printf("Insira sua opção:\n");
        scanf("%d", &op);

        if (op > 6 || op < 1)
        {
            op = -1;
            mensagemErro(op);
        }
        if (op == 6)
        {
            limparTela();
            return;
        }
        limparTela();
        switchAmigo(op, amigo - 1);

        auxEdita = desejaAlterar();
    }
}
void switchAmigo(int op, int amigo)
{
    char strAux[100];
    int opaux = 0, auxdata = 0;
    char opc;

    switch (op)
    {
    case 1:
        printf("Alterar [ %s ] para: ", GAmigo[amigo].nome);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o nome para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GAmigo[amigo].nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GAmigo[amigo].nome, strAux);
            printf("Nome alterado com sucesso!\n");
        }
        else
        {
            printf("Alteração cancelada.\n");
        }
        break;

    case 2:
        printf("Alterar [ %s ] para: ", GAmigo[amigo].apelido);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o apelido para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GAmigo[amigo].apelido = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GAmigo[amigo].apelido, strAux);
            printf("Apelido alterado com sucesso!\n");
        }
        else
        {
            printf("Alteração cancelada.\n");
        }
        break;

    case 3:
        printf("Alterar [ %s ] para: ", GAmigo[amigo].telefone);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o telefone para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GAmigo[amigo].telefone = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GAmigo[amigo].telefone, strAux);
            printf("Telefone alterado com sucesso!\n");
        }
        else
        {
            printf("Alteração cancelada.\n");
        }
        break;

    case 4:

        printf("Alterar [ %s ] para: ", GAmigo[amigo].email);
        flushs();
        gets(strAux);
        flushs();

        // Confirmação
        printf("Deseja realmente alterar o email para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GAmigo[amigo].email = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GAmigo[amigo].email, strAux);
            printf("Email alterado com sucesso!\n");
        }
        else
        {
            printf("Alteração cancelada.\n");
        }
        break;

    case 5:
        while (opaux < 1 || opaux > 3)
        {
            limparTela();
            printf("O que deseja editar na data de nascimento?\n");
            printf("1. Dia\n2. Mês\n3. Ano\nEscolha: ");
            scanf("%d", &opaux);
            if (opaux < 1 || opaux > 3)
            {
                mensagemErro(-1);
            }
        }

        printf("Insira o novo valor: ");
        scanf("%d", &auxdata);

        switch (opaux)
        {
        case 1:
            printf("Deseja realmente alterar o dia para %02d? (S/N): ", auxdata);
            break;
        case 2:
            printf("Deseja realmente alterar o mês para %02d? (S/N): ", auxdata);
            break;
        case 3:
            printf("Deseja realmente alterar o ano para %d? (S/N): ", auxdata);
            break;
        }
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            switch (opaux)
            {
            case 1:
                GAmigo[amigo].datanasc.dia = auxdata;
                break;
            case 2:
                GAmigo[amigo].datanasc.mes = auxdata;
                break;
            case 3:
                GAmigo[amigo].datanasc.ano = auxdata;
                break;
            }
            printf("Data de nascimento alterada com sucesso!\n");
        }
        else
        {
            printf("Alteração cancelada.\n");
        }
        break;

    case 6:
        printf("Voltando ao menu principal...\n");
        break;

    default:
        mensagemErro(-1);
        break;
    }
    printf("\n");
    pause();
}

void editaLocal()
{
    int auxEdita = 1;

    while (auxEdita)
    {
        int op = 0;
        if (Nlocal == 0)
        {
            limparTela();
            printf("Não há Locais disponíveis para editar! Adicione um Local!\n");
            pause();
            return;
        }

        limparTela();
        printf("Que Local você deseja editar?\n\n");

        listaTodosLocais();

        while (op < 1 || op > Nlocal)
        {
            printf("Escolha um Local: ");
            scanf("%d", &op);
            if (op < 1 || op > Nlocal)
            {
                op = -1;
                mensagemErro(op);
            }
        }

        limparTela();

        imprimeLocal(GLocal[op - 1], op - 1);

        int Local = op;

        printf("\n\nO que você deseja editar?\n");
        printf("1. Nome do local\n");
        printf("2. bairro\n");
        printf("3. Cidade\n");
        printf("4. Estado\n");
        printf("5. Logradouro\n");
        printf("6. Número\n");
        printf("7. Voltar\n");
        op = 0;
        printf("Insira sua opção:\n");
        scanf("%d", &op);

        if (op > 7 || op < 1)
        {
            op = -1;
            mensagemErro(op);
        }
        if (op == 7)
        {
            limparTela();
            return;
        }
        limparTela();
        switchLocal(op, Local - 1);

        auxEdita = desejaAlterar();
    }
}
void switchLocal(int op, int Local)
{
    char strAux[100];
    char opc;

    switch (op)
    {
    case 1:
        printf("Alterar [ %s ] para: ", GLocal[Local].nomelocal);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o nome do local para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GLocal[Local].nomelocal = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GLocal[Local].nomelocal, strAux);
            printf("\nNome do local alterado com sucesso!\n");
        }
        else
        {
            printf("Alteração cancelada.\n");
        }
        break;

    case 2:
        printf("Alterar [ %s ] para: ", GLocal[Local].local.bairro);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o bairro para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GLocal[Local].local.bairro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GLocal[Local].local.bairro, strAux);
            printf("bairro alterado com sucesso!\n");
        }
        else
        {
            printf("Alteração cancelada.\n");
        }
        break;

    case 3:
        printf("Alterar [ %s ] para: ", GLocal[Local].local.cidade);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar a cidade do local para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GLocal[Local].local.cidade = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GLocal[Local].local.cidade, strAux);
            printf("\ncidade alterada com sucesso!\n");
        }
        else
        {
            printf("Alteração cancelada.\n");
        }
        break;

    case 4:

        printf("Alterar [ %s ] para: ", GLocal[Local].local.estado);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o estado para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GLocal[Local].local.estado = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GLocal[Local].local.estado, strAux);
            printf("\nEstado alterado com sucesso!\n");
        }
        else
        {
            printf("Alteração cancelada.\n");
        }
        break;

    case 5:

        printf("Alterar [ %s ] para: ", GLocal[Local].local.logradouro);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o logradouro para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GLocal[Local].local.logradouro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GLocal[Local].local.logradouro, strAux);
            printf("\nLogradouro alterado com sucesso!\n");
        }
        else
        {
            printf("Alteração cancelada.\n");
        }
        break;
    case 6:

        printf("Alterar [ %s ] para: ", GLocal[Local].local.num);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o número do local para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GLocal[Local].local.num = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GLocal[Local].local.num, strAux);
            printf("\nNúmero alterado com sucesso!\n");
        }
        else
        {
            printf("Alteração cancelada.\n");
        }
        break;

    case 7:

        printf("Voltando ao menu principal...\n");
        printf("\n");
        pause();

    default:
        mensagemErro(-1);
        break;
    }
    printf("\n");
    pause();
    return;
}

void editaCategoria()
{
    int auxEdita = 1;

    while (auxEdita)
    {
        int op = 0;
        if (NCat == 0)
        {
            limparTela();
            printf("Não há categorias disponíveis para editar! Adicione!\n");
            pause();
            return;
        }

        limparTela();
        printf("Qual você deseja editar?\n\n");

        listaTodasCategorias();

        while (op < 1 || op > NCat)
        {
            printf("Escolha um para editar: ");
            scanf("%d", &op);
            if (op < 1 || op > NCat)
            {
                op = -1;
                mensagemErro(op);
            }
        }

        limparTela();

        imprimeCategoria(GCategoria[op - 1], op - 1);

        int categoria = op;

        printf("\n\nO que você deseja editar?\n");
        printf("1. Nome\n");
        printf("2. Voltar\n");
        op = 0;

        printf("Insira sua opção:\n");
        scanf("%d", &op);

        if (op > 2 || op < 1)
        {
            op = -1;
            mensagemErro(op);
        }
        if (op == 2)
        {
            limparTela();
            return;
        }

        limparTela();
        switchCat(op, categoria - 1);

        auxEdita = desejaAlterar();
    }
}
void switchCat(int op, int cat)
{
    char strAux[100];
    char opc;

    switch (op)
    {
    case 1:
        printf("Alterar [ %s ] para: ", GCategoria[cat].nomecat);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o nome da categoria para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GCategoria[cat].nomecat = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GCategoria[cat].nomecat, strAux);
            printf("\nNome alterado com sucesso!\n");
        }
        else
        {
            printf("Alteração cancelada.\n");
        }
        break;

    case 2:

        printf("Voltando ao menu principal...\n");
        printf("\n");
        pause();

    default:
        mensagemErro(-1);
        break;
    }
    printf("\n");
    pause();
    return;
}

// lixeira

void excluiAmigo()
{

    if (Namigo < 1)
    {
        limparTela();
        printf("não há amigos disponíveis! (kkkkkk mo otario)\n");
        pause();
        return;
    }

    listaTodosAmigos();

    printf("\n\nQual deseja excluir? [ 1 - %d ]\n", Namigo);

    int op = 0;
    while (op < 1 || op > Namigo)
    {
        printf("Digite um número entre 1 e %d (por favor não avacalhe): ", Namigo);
        if (scanf("%d", &op) != 1)
        {
            mensagemErro(-1);
            continue;
        }
    }

    int amigo = op - 1;

    char opc;

    do
    {
        limparTela();
        printf("Deseja mesmo excluir [ %s ]?\nEssa ação será I.RREVERSÍVEL.\n(tipo assim vc vai ter menos um pras suas festinhas e coisas ridiculas)\n(S/N)", GAmigo[amigo].nome);
        scanf(" %c", &opc);
        if (opc == 'N' || opc == 'n')
        {

            limparTela();
            printf("Você escolheu [N]; Voltando para menu principal. . . ");
            printf("\n");
            pause();
            return;
        }
        else if (opc == 'S' || opc == 's')
        {
            limparTela();
            printf("Você escolheu [S]; Excluindo. . . ");

            if (Namigo == 1)
            {
                free(GAmigo);
            }
            else
            {
                for (int i = amigo; i < Namigo - 1; i++)
                {
                    GAmigo[i] = GAmigo[i + 1];
                }
                GAmigo = (SAmigo *)realloc(GAmigo, (Namigo - 1) * sizeof(SAmigo));
            }

            Namigo--;

            limparTela();
            printf("exclusao bem sucedida!");
            return;
        }
        else

        {
            op = -1;
            mensagemErro(op);
            limparTela();
        }

    } while (opc != 'S' || opc != 's' || opc != 'N' || opc != 'n');
}
void excluiLocal()
{

    if (Nlocal < 1)
    {
        limparTela();
        printf("não há locais disponíveis!\n");
        pause();
        return;
    }

    listaTodosLocais();

    printf("\n\nQual deseja excluir? [ 1 - %d ]\n", Nlocal);

    int op = 0;
    while (op < 1 || op > Nlocal)
    {
        printf("Digite um número entre 1 e %d (por favor não avacalhe): ", Nlocal);
        if (scanf("%d", &op) != 1)
        {
            mensagemErro(-1);
        }
    }

    int local = op - 1;

    char opc;

    do
    {
        limparTela();
        printf("Deseja mesmo excluir [ %s ]?\nEssa ação será IRREVERSÍVEL.\n\n(S/N)", GLocal[local].nomelocal);
        scanf(" %c", &opc);
        if (opc == 'S' || opc == 's')
        {
            limparTela();
            printf("Você escolheu [S]; Excluindo. . . ");

            if (Nlocal == 1)
            {
                free(GLocal);
            }
            else
            {

                for (int i = local; i < Nlocal - 1; i++)
                {
                    GLocal[i] = GLocal[i + 1];
                }

                GLocal = (SLocal *)realloc(GLocal, (Nlocal - 1) * sizeof(SLocal));
            }

            Nlocal--;

            limparTela();
            printf("exclusao bem sucedida!\n");
            pause();
            return;
        }

        else if (opc == 'N' || opc == 'n')
        {
            limparTela();
            printf("Você escolheu [N]; Voltando para menu principal. . . ");
            printf("\n");
            pause();
            return;
        }
        else

        {
            op = -1;
            mensagemErro(op);
            limparTela();
        }

    } while (opc != 'S' || opc != 's' || opc != 'N' || opc != 'n');
}
void excluiCat()
{

    if (NCat < 1)
    {
        limparTela();
        printf("não há nenhum disponível!\n");
        pause();
        return;
    }

    listaTodasCategorias();

    printf("\n\nQual deseja excluir? [ 1 - %d ]\n", NCat);

    int op = 0;
    while (op < 1 || op > NCat)
    {
        printf("Digite um número entre 1 e %d (por favor não avacalhe): ", NCat);
        if (scanf("%d", &op) != 1)
        {
            mensagemErro(-1);
        }
    }

    int cat = op - 1;

    char opc;

    do
    {
        limparTela();
        printf("Deseja mesmo excluir [ %s ]?\nEssa ação será IRREVERSÍVEL.\n\n(S/N)", GCategoria[cat].nomecat);
        scanf(" %c", &opc);
        if (opc == 'S' || opc == 's')
        {
            limparTela();
            printf("Você escolheu [S]; Excluindo. . . ");

            if (NCat == 1)
            {
                free(GCategoria);
            }
            else
            {

                for (int i = cat; i < NCat - 1; i++)
                {
                    GCategoria[i] = GCategoria[i + 1];
                }

                GCategoria = (SCategoria *)realloc(GCategoria, (NCat - 1) * sizeof(SCategoria));
            }
            NCat--;

            limparTela();
            printf("exclusao bem sucedida!\n");
            pause();
            return;
        }
        else if (opc == 'N' || opc == 'n')
        {
            limparTela();
            printf("Você escolheu [N]; Voltando para menu. . . ");
            printf("\n");
            pause();
            return;
        }
        else

        {
            op = -1;
            mensagemErro(op);
            limparTela();
            return;
        }

    } while (opc != 'S' || opc != 's' || opc != 'N' || opc != 'n');
}

// erros

void mensagemErro(int erro)
{
    limparTela();
    switch (erro)
    {
    default:
        printf("ERRO!. . . ");
        pause();
        limparTela();
        break;
    case -1:
        printf("ERRO! Opção inválida!\n");
        pause();
        limparTela();
        break;

    case -2:
        printf("ERRO! Data Inválida!\n");
        pause();
        limparTela();
        break;
    case -3:
        printf("\nERRO! Já existe um amigo com esse nome!\n");
        pause();
        limparTela();
        break;
    case -4:
        printf("Erro ao alocar memória\n");
        pause();
        limparTela();
        break;
    case -5:
        printf("Hora inválida!!\n");
        pause();
        limparTela();
        break;
    }
}

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

// liberar encontro
void incluiEncontro()
{
    if (Namigo == 0 || Nlocal == 0 || NCat == 0)
    {
        printf("Você ainda não possui ");

        if (Namigo == 0 && Nlocal == 0 && NCat == 0)
        {
            printf("nenhum amigo, nenhum local e nenhuma categoria adicionados.\n");
        }
        else
        {
            if (Namigo == 0)
            {
                printf("nenhum amigo adicionado");
            }

            if (Nlocal == 0)
            {
                if (Namigo == 0)
                {
                    printf(", "); // Adiciona uma vírgula entre os itens se já houver algo antes
                }
                printf("nenhum local adicionado");
            }

            if (NCat == 0)
            {
                if (Namigo == 0 || Nlocal == 0)
                {
                    printf(" e "); // Adiciona 'e' entre os itens, quando necessário
                }
                printf("nenhuma categoria adicionada");
            }

            printf(".\n");
        }

        printf("\nVolte ao menu e crie as opções necessárias!");
    }

    else
    {

        if (NEncontro == 0)
        {
            GEncontro = (SEncontro *)malloc(1 * sizeof(SEncontro));
        }
        else
        {
            GEncontro = (SEncontro *)realloc(GEncontro, (NEncontro + 1) * sizeof(SEncontro));
        }

        GEncontro[NEncontro] = cadastraEncontro(NEncontro);
        NEncontro++;
    }
}

SEncontro cadastraEncontro(int num)
{
    SEncontro e;
    int erro = 0, op = 0;

    limparTela();
    printf("***CRIANDO ENCONTRO***\n");

    // Dia do encontro
    while (erro != 1)
    {
        limparTela();
        printf("dia do encontro:\n");
        scanf("%d", &e.dataencontro.dia);
        printf("\nMês do encontro:\n");
        scanf("%d", &e.dataencontro.mes);
        printf("\nAno do encontro:\n");
        scanf("%d", &e.dataencontro.ano);

        erro = validaData(e.dataencontro.dia, e.dataencontro.mes, e.dataencontro.ano);

        if (erro != 1)
        {
            mensagemErro(erro);
        }
    }
    erro = 0;

    // amg no encontro
    e.enumamigos = 0;
    while (erro != 1)
    {
        limparTela();
        printf("\nQual amigo deseja adicionar no encontro?\n");
        listaNomesAmigo();
        scanf("%d", &op);

        if (op <= 0 || op > Namigo)
        {
            mensagemErro(-1);
        }
        else
        {
            e.amigoencontro = e.enumamigos == 0 ? (char **)malloc(sizeof(char *)) : (char **)realloc(e.amigoencontro, (e.enumamigos + 1) * sizeof(char *));
            if (e.amigoencontro == NULL)
            {
                mensagemErro(-4);
                break;
            }

            e.amigoencontro[e.enumamigos] = (char *)malloc(strlen(GAmigo[op - 1].nome) + 1);
            if (e.amigoencontro[e.enumamigos] == NULL)
            {
                mensagemErro(-4);
                break;
            }

            strcpy(e.amigoencontro[e.enumamigos], GAmigo[op - 1].nome);
            e.enumamigos++;

            printf("\n\nAmigo adicionado no encontro!\n");
            printf("\nSelecionar mais um amigo?\n1. Sim\n2. Não\n");
            scanf("%d", &op);

            erro = op == 1 ? 0 : op == 2 ? 1
                                         : (mensagemErro(-1), 0);
        }
    }
    erro = 0;

    // loc do encontro
    while (erro != 1)
    {
        limparTela();
        printf("Qual é o local do encontro?\n");
        listaNomesLocal();
        scanf("%d", &op);

        if (op <= 0 || op > Nlocal)
        {
            mensagemErro(-1);
        }
        else
        {
            e.localencontro = (char *)malloc(strlen(GLocal[op - 1].nomelocal) + 1);
            if (e.localencontro == NULL)
            {
                mensagemErro(-4);
                break;
            }
            strcpy(e.localencontro, GLocal[op - 1].nomelocal);
            erro = 1;
        }
    }
    erro = 0;

    // cat do encontro
    while (erro != 1)
    {
        limparTela();
        printf("Qual é a categoria do encontro?\n");
        listaNomesCategoria();
        scanf("%d", &op);

        if (op <= 0 || op > NCat)
        {
            mensagemErro(-1);
        }
        else
        {
            e.categoriaencontro = (char *)malloc(strlen(GCategoria[op - 1].nomecat) + 1);
            if (e.categoriaencontro == NULL)
            {
                mensagemErro(-4);
                break;
            }
            strcpy(e.categoriaencontro, GCategoria[op - 1].nomecat);
            erro = 1;
        }
    }
    erro = 0;

    // hr do encontro
    while (erro != 1)
    {
        limparTela();
        printf("Digite a hora do encontro (HH MM): ");
        scanf("%d %d", &e.horaencontro.hora, &e.horaencontro.minuto);

        int verificadorhora = validaHora(e.horaencontro.hora, e.horaencontro.minuto);

        if (verificadorhora == -5)
        {
            mensagemErro(-5);
        }
        else
        {
            printf("\n\nHora Adicionada!!\n");
            pause();
            erro = 1;
        }
    }

    limparTela();
    printf("Encontro adicionado!\n");
    imprimeEncontro(e, num);
    pause();
    return e;
}

void imprimeEncontro(SEncontro e, int enc)
{
    printf("\nEncontro %d\n", enc + 1);

    printf("%s\n", e.nomeencontro);
    printf("Amigos no encontro: %d\n", e.enumamigos);
    printf("Amigos: ");

    for (int i = 0; i < e.enumamigos; i++)
    {
        printf("[%s]; ", e.amigoencontro[i]);
    }

    printf("\nLocal: %s\n", e.localencontro);
    printf("Data: [ ");
    printf(" %02d /", e.dataencontro.dia);
    printf(" %02d /", e.dataencontro.mes);
    printf(" %04d ]\n", e.dataencontro.ano);

    printf("Categoria: %s\n", e.categoriaencontro);
    printf("Hora: [%02i : %02i]\n", e.horaencontro.hora, e.horaencontro.minuto);
}