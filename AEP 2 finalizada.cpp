#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
//============================================================================
void confirma ();
void passarArquivo(char nomes[][50], char senhas[][50], int quantidade, int maxTamanho);
void passarVetor(char nomes[][50], char senhas[][50], int *quantidade, int maxUsuarios, int maxTamanho);
int validaSenha(char senha[50]);
void criptografa(char nomes[50]);
void descriptografa(char nomes[50]);
void classifica();
//============================================================================
int main () {

	FILE *arquivo;
	const int maxUsuarios = 100;
	const int maxTamanho = 50;
	int tp = 0, total=0, stop = 0, error = 0, qtd=0;
	char nome[50];
	char senha[50];

	do {
		do {
	    printf("__________________\n");
		printf("|    M E N U     |\n");
        printf("|----------------|\n");
        printf("|  1- Cadastrar  |\n");
        printf("|  2- Listar     |\n");
        printf("|  3- Alterar    |\n");
        printf("|  4- Excluir    |\n");
        printf("|  5- Creditos   |\n");
        printf("|  6- Sair       |\n");
        printf("|________________|\n");
        printf("\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &tp);
		} while(tp == 1 && tp == 2 && tp == 3 && tp == 4 && tp == 5);

		//-------------------------------------------------------------------------
		if (tp == 1) {  //cadastrar
			char linha[50];
			char confirmaSenha[50];
			error = 0;

			system("cls");
			printf("____________\n");
			printf("|          |\n");
			printf("| CADASTRO |\n");
			printf("|__________|\n");
			printf("Digite um nome: ");
			scanf("%s", nome);
		do {
				printf("Digite uma senha: ");
				scanf("%s", senha);
			} while(validaSenha(senha) != 0);
			
			criptografa(nome);
			arquivo = fopen("registro.dad.txt", "r");
			while (fgets(linha, sizeof(linha), arquivo)) {
				linha[strcspn(linha, "\n")] = '\0';
				
				if (strcmp(linha, nome) == 0) { 
					error = 1;
					break;
				}
			}
			fclose(arquivo);
			descriptografa(nome);
			
			if (error == 1) { 
				printf("Falha ao cadastrar...Nome de usuario ja existente. \n");
			} else { 
				arquivo = fopen("registro.dad.txt", "a");
				criptografa(nome);
				criptografa(senha);
				fprintf(arquivo,"%s\n", nome);
				fprintf(arquivo,"%s\n", senha);
				printf("Cadastro realizado com sucesso!\n");
				fclose(arquivo);
			}

			confirma();
			system("cls");
			fclose(arquivo);
			//-------------------------------------------------------------------------
		} else if (tp == 2 || tp == 7 || tp == 8) { 
			char frase1[50];
			char frase2[50];
			char senhaCifrada[50];
			int tam;

			classifica();
			system("cls");
			printf("____________\n");
            printf("|          |\n");
            printf("|  Lista   |\n");
            printf("|__________|\n");
           	printf("\n");
			switch (tp) {
				case 2: 
					arquivo = fopen("registro.dad.txt", "r");
					while (fscanf(arquivo, "%s %s", frase1, frase2) == 2) {
						tam = strlen(frase2);
						for (int i = 0; i < tam; i++) {
							senhaCifrada[i] = '*';
						}
						senhaCifrada[tam] = '\0';

						descriptografa(frase1);
						printf("Nome: %s \t\tSenha: %s\n\n", frase1, senhaCifrada);

					}
					fclose(arquivo);
					break;

				case 7: 
					arquivo = fopen("registro.dad.txt", "r");
					while (fscanf(arquivo, "%s %s", frase1, frase2) == 2) {
						printf("Nome: %s \tSenha: %s\n\n", frase1, frase2);
					}
					fclose(arquivo);
					break;

				case 8: 
					arquivo = fopen("registro.dad.txt", "r");
					while (fscanf(arquivo, "%s %s", frase1, frase2) == 2) {
						descriptografa(frase1);
						descriptografa(frase2);
						printf("Nome: %s \tSenha: %s\n\n", frase1, frase2);
					}
					fclose(arquivo);
					break;
			}

			confirma();
			system("cls");
			//-------------------------------------------------------------------------
	} else if (tp == 3) { 

			char linha[50];
			char novoNome[50];
			char novaSenha[50];
			char nomeAntigo[50];
			int existe = 0, opc = 0;

			system("cls");
    printf("____________\n");
    printf("|          |\n");
    printf("| ALTERAR  |\n");
    printf("|__________|\n");
			printf("\n");
			printf("Digite o nome do usuario a ser alterado: ");
			scanf("%s", nomeAntigo);

			criptografa(nomeAntigo);
			arquivo = fopen("registro.dad.txt", "r");
			while (fgets(linha, sizeof(linha), arquivo)) {
				linha[strcspn(linha, "\n")] = '\0';

				if (strcmp(linha, nomeAntigo) == 0 ) {
					existe = 1;
					break;
				}
			}
			fclose(arquivo);

			if (existe == 0) {
				printf("O nome nao foi encontrado...\n");
				confirma();
				continue;
			}
			descriptografa(nomeAntigo);
			//-------------------------------------------------------------------------
			do {
				printf("\nQual voce deseja alterar:\n1 - Nome\n2 - Senha\nEscolha uma opcao: ");
				scanf("%d", &opc);
			} while	(opc != 1 && opc != 2);

			char nomes[maxUsuarios][maxTamanho];
			char senhas[maxUsuarios][maxTamanho];
			passarVetor(nomes, senhas, &qtd, maxUsuarios, maxTamanho);

			if (opc == 1) {
				printf("\nDigite um novo nome: ");
				scanf("%s", novoNome);

				for(int i=0; i < qtd; i++) {
					if (strcmp(nomes[i], nomeAntigo) == 0) {
						strcpy(nomes[i], novoNome);
					}
				}

				printf("O nome foi salvo com sucesso!\n");
			}
			if (opc == 2) {

				do {
					printf("\nDigite uma nova senha: ");
					scanf("%s", novaSenha);
				} while(validaSenha(novaSenha) != 0);

				for(int i=0; i < qtd; i++) {
					if (strcmp(nomes[i], nomeAntigo) == 0) {
						strcpy(senhas[i], novaSenha);
					}
				}

				printf("A senha foi salva com sucesso!\n");
			}
			passarArquivo(nomes, senhas, qtd, maxTamanho);

			confirma();
			system("cls");
			//-------------------------------------------------------------------------
		} else if (tp == 4) { 
			char nom[50];
			char linha[50];
			int existe = 0;
			char nomes[maxUsuarios][maxTamanho];
			char senhas[maxUsuarios][maxTamanho];

			system("cls");
			printf("____________\n");
			printf("|          |\n");
			printf("| EXCLUIR  |\n");
			printf("|__________|\n");
			printf("\n Digite o nome do usuario: ");
			scanf("%s", nom);

			criptografa(nom);

			arquivo = fopen("registro.dad.txt", "r");
			while (fgets(linha, sizeof(linha), arquivo)) {
				linha[strcspn(linha, "\n")] = '\0';

				if (strcmp(linha, nom) == 0) {
					existe = 1;
					break;
				}
			}
			fclose(arquivo);

			if (existe == 0) {
				printf("O nome nao foi encontrado...\n");
				confirma();
				continue;
			}

			arquivo = fopen("registro.dad.txt", "r");
			if (!arquivo) {
				printf("Erro ao abrir o arquivo.\n");
				continue;
			}

			int contador = 0;
			while (fgets(linha, sizeof(linha), arquivo) != NULL) {
				linha[strcspn(linha, "\n")] = 0;

				if (strcmp(linha, nom) == 0) {
					fgets(linha, sizeof(linha), arquivo);
					continue;
				}

				if (contador % 2 == 0) {
					descriptografa(linha);
					strcpy(nomes[contador / 2], linha);
				} else {
						descriptografa(linha);
						strcpy(senhas[contador / 2], linha);
				}
				contador++;
			}
			fclose(arquivo);

			qtd = contador / 2;
			passarArquivo(nomes, senhas, qtd, maxTamanho);

			printf("O usuario foi excluido com sucesso!\n");
			confirma();
			system("cls");

		} else if (tp == 5) { 
			system("cls");
			printf("============================================================\n");
			printf("|                                                          |\n");
			printf("|         SISTEMA DE GERENCIAMENTO DE CONTAS AEP           |\n");
			printf("|                                                          |\n");
			printf("============================================================\n\n");

			printf("Este software foi desenvolvido para o Projeto AEP \n");
			printf("Curso: Engenharia de Software - ESOFT2A.\n\n");
			printf("Equipe de Desenvolvimento:\n");
			printf("- Gabriel Morais - RA: 24143287-2\n");
			printf("- Eduardo Iba - RA: 24136247-2\n\n");
			printf("Proposito do Sistema:\n");
			printf("O objetivo desse sistema eh auxiliar na gestao de contas, \n");
			printf("permitindo aos usuarios poderem cadastrar, alterar, visualizar \n");
			printf("e excluir contas de forma segura. O sistema inclui criptografia \n");
			printf("para proteger os dados sensiveis.\n\n");

			printf("============================================================\n");
			printf("|                                                          |\n");
			printf("|       Agradecemos por utilizar nosso software!           |\n");
			printf("|                                                          |\n");
			printf("============================================================\n");
			confirma();
			system("cls");
		} else if (tp == 6) { // Sair
			stop = 1;
		} else system("cls");

	} while (stop == 0);

	return 0;
}
//============================================================================
void confirma () {
	int tecla;
	printf("\nPressione qualquer tecla para continuar...");
	tecla = getch();
	system("cls");
}
//============================================================================
void passarVetor(char nomes[][50], char senhas[][50], int *quantidade, int maxUsuarios, int maxTamanho) {
	FILE *arquivo = fopen("registro.dad.txt", "r");
	if (!arquivo) {
		printf("Erro ao abrir o arquivo.\n");
		return;
	}

	int contador = 0;
	char linha[50];

	while (fgets(linha, maxTamanho, arquivo) != NULL && contador < maxUsuarios * 2) {
		linha[strcspn(linha, "\n")] = 0;

		if (contador % 2 == 0) {
			strcpy(nomes[contador / 2], linha);
		} else {
			strcpy(senhas[contador / 2], linha);
		}

		contador++;
	}

	*quantidade = contador / 2;
	for (int i = 0; i < *quantidade; i++) {
		descriptografa(nomes[i]);
		descriptografa(senhas[i]);
	}

	fclose(arquivo);
}
//============================================================================
void passarArquivo(char nomes[][50], char senhas[][50], int quantidade, int maxTamanho) {
	FILE *arquivo = fopen("registro.dad.txt", "w");
	for (int i = 0; i < quantidade; i++) {

		if (strlen(nomes[i]) > 0 && strlen(senhas[i]) > 0) {
			criptografa(nomes[i]);
			criptografa(senhas[i]);

			fprintf(arquivo, "%s\n", nomes[i]);
			fprintf(arquivo, "%s\n", senhas[i]);
		}
	}

	fclose(arquivo);
}
//============================================================================
int validaSenha(char senha[50]) {
	char senha2[50];
	int erro=0, v1=0, v2=0, v3=0, v4=0;

	if (strlen(senha) < 8 || strlen(senha) > 12) {
		erro = 1;
	} else {
		for (int i = 0; i < strlen(senha); i++) {
			if (senha[i] >= 65 && senha[i] <= 90) {
				v1 = 1;
			} else if (senha[i] >= 97 && senha[i] <= 122) {
				v2 = 1;
			} else if (senha[i] >= 48 && senha[i] <= 57) {
				v3 = 1;
			} else if ((senha[i] >= 33 && senha[i] <= 47) || (senha[i] >= 58 && senha[i] <= 64) || (senha[i] >= 91 && senha[i] <= 96) || (senha[i] >= 123 && senha[i] <= 126)) {
				v4 = 1;
			}
		}
	}

	if (erro == 0 && v1 && v2 && v3 && v4) {
		printf("Repita a senha: ");
		scanf("%s", senha2);
		if (strcmp(senha2, senha) == 0) {
			return 0;
		} else {
			printf("Senha invalida.\n\n");
			return 1;
		}
	} else {
		printf("A senha precisa ter entre 8 e 12 caracteres, conter ao menos um caractere especial, um caractere numerico e um caractere maiusculo.\n\n");
		return 1;
	}
}
//============================================================================
void criptografa(char nomes[50]) {
	int tmp = 0;

	for (int i = 0; i < strlen(nomes); i++) {
		tmp = (int)nomes[i];
		nomes[i] = (char)(tmp + 12);
	}
}
//============================================================================
void descriptografa(char nomes[50]) {
	int tmp = 0;

	for (int i = 0; i < strlen(nomes); i++) {
		tmp = (int)nomes[i];
		nomes[i] = (char)(tmp - 12);
	}
}
//============================================================================
void classifica() {
	FILE *arquivo;
	const int maxUsuarios = 100;
	const int maxTamanho = 50;
	int qtd = 0;
	char nomes[maxUsuarios][maxTamanho];
	char senhas[maxUsuarios][maxTamanho];

	passarVetor(nomes, senhas, &qtd, maxUsuarios, maxTamanho);

	for (int i = 0; i < qtd - 1; i++) {
		for (int j = 0; j < qtd - i - 1; j++) {
			if (strcmp(nomes[j], nomes[j + 1]) > 0) {

				char tmpNome[maxTamanho];
				char tmpSenha[maxTamanho];

				strcpy(tmpNome, nomes[j]);
				strcpy(nomes[j], nomes[j + 1]);
				strcpy(nomes[j + 1], tmpNome);

				strcpy(tmpSenha, senhas[j]);
				strcpy(senhas[j], senhas[j + 1]);
				strcpy(senhas[j + 1], tmpSenha);
			}
		}
	}

	passarArquivo(nomes, senhas, qtd, maxTamanho);

	printf("\nUsuarios classificados com sucesso!\n");
}
