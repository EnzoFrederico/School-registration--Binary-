#include<stdio.h>
#include<string.h>

typedef struct {
    char nome[20];
    int turno;
    int DatadeNascimento;
    }sistema;

void imprimirBinTerminal(FILE *arquivo, sistema alunos){
    int i = 0;
    while(fread(&alunos, sizeof(alunos), 1, arquivo)){
        printf("%d - %s, %d, %d\n", i+1, alunos.nome, alunos.turno, alunos.DatadeNascimento);
        i++;
    }
}

void escritaBin (char *nomeDoArquivo){
    FILE *arquivo;
    arquivo = fopen(nomeDoArquivo, "ab");

    sistema alunos;

    printf("Digite o cadastro de um aluno: \n");

        printf("Digite o nome do aluno: \n");
        fgets(alunos.nome, 20, stdin);
        strtok(alunos.nome, "\n");

        printf("Diga qual o turno do aluno (1 ou 2): \n");
        scanf("%d", &alunos.turno);


        printf("Diga quantos anos o aluno tem:\n");
        scanf("%d", &alunos.DatadeNascimento);
        fwrite(&alunos, sizeof(alunos), 1, arquivo);
        while(getchar() != '\n');

        fclose(arquivo);
}

void leituraBin(char *nomeDoArquivo){
    FILE *arquivo;
    arquivo = fopen(nomeDoArquivo, "rb");

    sistema alunos;

    imprimirBinTerminal(arquivo, alunos);

    fclose(arquivo);
}

void edicaoBin(char *nomeDoArquivo){
    FILE *arquivo;
    arquivo = fopen(nomeDoArquivo, "rb+");

    sistema alunos;

    imprimirBinTerminal(arquivo, alunos);

    int i;
    printf("Digite o identificador do aluno que deseja modificar:\n");
        scanf("%d", &i);
        i = i-1;
        getchar();
    printf("Digite o nome do aluno: ");
        scanf("%s", alunos.nome);
    printf("Diga qual o turno do aluno: ");
        scanf("%d", &alunos.turno);
    printf("Diga quantos anos o aluno tem: ");
        scanf("%d", &alunos.DatadeNascimento);
//  Acha a posicao do elemento que quer editar.
    fseek(arquivo, i * sizeof(alunos), SEEK_SET);
    fwrite(&alunos, sizeof(alunos), 1, arquivo);

    fclose(arquivo);
}

void deletarBin(char *nomeDoArquivo){
    sistema alunos;
    FILE *arquivo, *arquivoDel;
	arquivo = fopen(nomeDoArquivo, "rb");
	// Lista dos alunos cadastrados

    imprimirBinTerminal(arquivo, alunos);
    fclose(arquivo);

    int d;
    printf("Qual cadastro voce gostaria de deletar?");
    scanf("%d", &d);

    d = d-1;
    arquivo = fopen(nomeDoArquivo, "rb");
    arquivoDel = fopen("arqDeletado.txt", "wb");


    if(arquivoDel){
	int j = 0;
	   while(fread(&alunos, sizeof(alunos), 1, arquivo)){
	       if (j != d){
	    		fwrite(&alunos, sizeof(alunos), 1, arquivoDel);
	    	}
		j++;
		}

	remove(nomeDoArquivo);
    }
    else{
        printf("Ero ao criar arquivo");
    }

    fclose(arquivoDel);

    arquivo = fopen(nomeDoArquivo, "wb");
    arquivoDel = fopen("arqDeletado.txt", "rb");

    if (arquivo){
        int j = 0;
        while(fread(&alunos, sizeof(alunos), 1, arquivoDel)){
            fwrite(&alunos, sizeof(alunos), 1, arquivo);
            j++;
        }
    }
    else{
        printf("Erro ao abrir arquivo");
        }

    remove("arqDeletado.txt");
    fclose(arquivo);
}

int main(){
    char nomeDoArquivo[] = "alunos.txt";

    int opcao;
    do {
        printf("Digite a opcao desejada:\n");
        printf(" 0 - Encerrar\n 1 - Cadastrar aluno\n 2 - Ler alunos cadastrados\n 3 - Editar cadastro\n 4 - Deletar entrada\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao){
            case 1:
                escritaBin(nomeDoArquivo);
                break;
            case 2:
                leituraBin(nomeDoArquivo);
                break;
            case 3:
                edicaoBin(nomeDoArquivo);
                break;
            case 4:
                deletarBin(nomeDoArquivo);
                break;
            default:
                printf("\nFIM\n");
        }
    }
    while (opcao != 0);
}


