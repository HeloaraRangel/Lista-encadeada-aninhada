#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
  //implementação de uma lista encadeada aninhada.

typedef char string[40];

typedef struct tipoDisciplina {
	string nome;
	int cargaHoraria;
	tipoDisciplina *prox;
}TDisciplina;

typedef struct tipoHistorico {
	TDisciplina *disciplina;
	float nota;
	float percentualFrequencia;
	string condicao; // Aprovado, Reprovado ou Cursando.
	tipoHistorico *prox;	
}THistorico;

typedef struct tipoAluno {
	string nome_aluno;
	char sexo;
	THistorico *historico;
  TDisciplina *disciplinas;
	tipoAluno *ante, *prox;
}TAluno;

typedef struct tipoCurso {
	string nome_curso;
	TAluno *alunos;
	tipoCurso *ante, *prox;
}TCurso;

typedef struct tipoLista {
	TCurso *inicioC;
	TCurso *fimC;
	TDisciplina *inicioD;
	TDisciplina *fimD;
}TLista;

TLista listas;

//Assinatura das fun��es
void inicializa(TLista *L);
int menu();
//====================================
void inserir_disciplina(TLista *L, string nome, int cargaHoraria);
void cadastrar_disciplina(TLista *L);
void exibir_disciplinas(TLista *L);
//==================================
void inserir_curso(TLista *L,string nome_curso);
void cadastrar_curso(TLista *L);
void exibir_cursos(TLista *L);
TCurso *pesquisar_Curso(TLista* L, string nome_curso);
//============================================
void inserir_alunos_em_curso(TLista *L);
void exibir_alunos_em_curso(TLista *L);
//============================================
void excluir_aluno_de_curso(TLista *L);
TDisciplina* pesquisar_disciplina(TLista *L, string nome_disciplina);
//===================================
void cadastrar_historico_para_aluno(TLista *L);
void exibir_historico_de_alunos(TLista *L);
void excluir_historico_de_aluno(TLista *L);
//===========================================

//menu de op��es para o usu�rio solicitar
int main()
{
    int op;
    inicializa(&listas);
  
    do 
    {
      op = menu();
      
      switch (op) 
      {
        case 1: 
          cadastrar_disciplina(&listas);
          break;
        case 2:
          exibir_disciplinas(&listas);
          break;
        case 3: 
          cadastrar_curso(&listas);
          break;
        case 4: 
          exibir_cursos(&listas);
          break;
        case 5:
          inserir_alunos_em_curso(&listas);
          break;
        case 6:
          exibir_alunos_em_curso(&listas);
          break;
        case 7:
            excluir_aluno_de_curso(&listas);
          break;        
        case 8:
            cadastrar_historico_para_aluno(&listas);
          break;
        case 9:
            exibir_historico_de_alunos(&listas);
          break;
        case 10:
            excluir_historico_de_aluno(&listas);
          break;
      }
    
	} while ( op != 0 );

}
//===============================================
//
int menu(){
  //menu das op��es disponiveis para os usuarios
  int opcao;
  
  //system("CLS");
  printf("\n\n\t\t====| MENU |=====\n\n");
  printf("\t0 - Sair (Encerrar a Aplicacao).\n");
  printf("\t1 - Inserir DISCIPLINA.\n");
  printf("\t2 - Exibe Todas as DISCIPLINAS.\n");
  printf("\t3 - Inserir CURSO.\n");
  printf("\t4 - Exibir Todos os CURSOS.\n");
  printf("\t5 - Inserir ALUNO em CURSO.\n");
  printf("\t6 - Exibir Todos os ALUNOS de CURSO especifico.\n");
  printf("\t7 - Excluir ALUNO de CURSO.\n");
  printf("\t8 - Inserir HISTORICO para ALUNO.\n");
  printf("\t9 - Exibir HISTORICO de ALUNO.\n");
  printf("\t10 - Excluir HISTORICO de ALUNO.\n");
  
  printf("\n\tInsira a opcao desejada:");
  fflush(stdin);
  scanf("%d", &opcao);
  
  if ((opcao <0) || (opcao > 10))
  {
    printf("Opcao Invalida!");
    system("PAUSE");
  }

  return opcao;

}
//=============================
//fun��o para inicializar tudo nulo e n�o ter risco de pegar lixo
void inicializa(TLista *L){
  L->inicioC = NULL;
  L->fimC = NULL;
  L->inicioD = NULL;
  L->fimD = NULL;
} 
//=============================
//fun��o para inserir as disciplinas na lista
void inserir_disciplina(TLista *L, string nome, int cargaHoraria) 
{
  TDisciplina *novo = (TDisciplina *)malloc(sizeof(TDisciplina)), *atual, *anterior;
  int sinaliza = 0;
  
  novo->prox = NULL;
  strcpy(novo->nome, nome);
  novo->cargaHoraria = cargaHoraria;

  if (L->inicioD == NULL) 
  {
    //lista ta vazia;
    L->inicioD = novo;
    L->fimD = novo; 
  }

  else 
  {
    atual = L->inicioD;
    anterior = NULL;

    while (atual != NULL) 
    {
      if (strcmp(atual->nome, nome) > 0)
      {
        //inserir na lista
        sinaliza = 1;
        if (atual == L->inicioD) 
        {
        // insere novo elemento na lista
          novo->prox = atual;
          L->inicioD = novo;
        }

        else 
        {
        	//insere o novo no meio 
          novo->prox = anterior->prox;
          anterior->prox = novo;
        }
        
        break;
        
      }

      anterior = atual;
      atual = atual->prox;
      
    }

    if (!sinaliza) 
    {
    //insere o novo no fim da lista
      L->fimD->prox = novo;
      L->fimD = novo;
    }
    
  }
  
}

//=========================================
//fun��o para cadastrar as disciplinas na lista
void cadastrar_disciplina(TLista *L)
{
  string nome;
  int cargaHoraria;

  printf("\n\t===CAMPO PARA CADASTRAR DADOS DA DISCIPLINA===\n");

  printf("Nome da Disciplina:");
  fflush(stdin);
  scanf(" %40[^\n]", nome);
  //---------------------------
  printf("Carga Horaria:");
  fflush(stdin);
  scanf("%d", &cargaHoraria);

  inserir_disciplina(L, nome, cargaHoraria);
} 
//=============================================
//fun��o para exibir as disciplinas
void exibir_disciplinas(TLista *L) 
{
	if (L->inicioD == NULL) 
	{
		printf("N�O HA DISCIPLINAS CADASTRADAS!");
	}
	else 
	{
		int i=1;
	    TDisciplina *atual = L->inicioD;
	    
	    printf("\n\t===EXIBICAO DE TODAS AS DISCIPLINAS===\n");
	    while (atual != NULL) 
	    {
	      printf("%d� - Nome da Disciplina: %s | Carga Horaria: %d\n", i++, atual->nome, atual->cargaHoraria);
	      atual = atual->prox;
	    }
	}

}
//==========================================
//fun��o para inserir os cursos na lista
void inserir_curso(TLista *L, string nome_curso)
{
    TCurso *novo = (TCurso *)malloc(sizeof(TCurso));
    TCurso *anterior, *atual;
    int sinaliza = 0 ;
    
    novo->prox = NULL;
    novo->ante = NULL;
    novo->alunos = NULL;
    strcpy(novo->nome_curso, nome_curso);
    
    if(L->inicioC == NULL) 
    {
        //lista est� vazia
        L->inicioC = novo;
        L->fimC = novo;
    }
    
    else 
    {
        atual = L->inicioC;
        
        while (atual != NULL) 
        {
        	
            if (strcmp(atual->nome_curso, novo->nome_curso) > 0) 
            {
            	//inserir na lista
                anterior = atual->ante;
                sinaliza = 1;
                
                novo->prox = atual;
                atual->ante = novo;
                
                //inserir o primeiro da lista se o anterior for igual a nulo
                if (anterior == NULL) 
                {
                    L->inicioC = novo;
                }
                
                //inserir no meio da lista
                else 
                {
                    anterior->prox = novo;
                    novo->ante = anterior;
                }
                break;
            }
            
            atual = atual->prox;
        }
       
	   //inserir o novo no ultimo da lista 
        if (!sinaliza) 
        {
            L->fimC->prox = novo;
            novo->ante = L->fimC;
            L->fimC = novo;
        }
        
    }
    
}
//==========================================
//fun��o para cadastrar os cursos na lista
void cadastrar_curso(TLista *L) 
{
    string nome_curso;
    
    printf("\n\t===CAMPO PARA CADASTRAR NOME DOS CURSOS===\n");

    printf("Nome do Curso:");
    fflush (stdin);
    scanf(" %40[^\n]", nome_curso);
    
    inserir_curso(L, nome_curso);
}
//==========================================
//fun��o para exibir os cursos na lista
void exibir_cursos(TLista *L) 
{
	if (L->inicioC == NULL) 
	{
		printf("N�O HA CURSOS CADASTRADOS!");
	}
	else 
	{
		int i=1;
	    TCurso *atual = L->inicioC;
	    
	    printf("\n\t===EXIBICAO DE TODOS OS CURSOS===\n");
	    while (atual != NULL) 
	    {
	        printf("%d� - Nome do Curso: %s \n", i++, atual->nome_curso);
	        atual = atual->prox;
	    }
	}
}
//========================================
//fun��o para identificar se realmente existe o curso na lista
TCurso *pesquisar_Curso(TLista* L, string nome_curso) 
{
    TCurso *atual = L->inicioC;
    
    while (atual != NULL) 
    {
        if (strcmp(atual->nome_curso, nome_curso) == 0) 
        {
            break;
        }
        atual = atual->prox;
    }
    return atual;
}
//========================================
//fun��o para identificar se realmente existe a disciplina na lista
TDisciplina* pesquisar_disciplina(TLista *L, string nome_disciplina) {
    TDisciplina *atual = L->inicioD;
    
    while (atual != NULL) {
        if (strcmp(atual->nome, nome_disciplina) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    
    return atual;
}
//===============================================
//fun��o para identificar se realmente existe o aluno na lista de alunos
TAluno *pesquisar_aluno(TCurso *curso, string nome_aluno) 
{
  TAluno *atual = curso->alunos;

    while (atual != NULL) {
        if (strcmp(atual->nome_aluno, nome_aluno) == 0) {
            break;
        }
        atual = atual->prox;
    }

    return atual;
}
//=================================================
//fun��o para cadastrar e inserir alunos nos cursos
void inserir_alunos_em_curso(TLista *L) 
{

    TCurso *curso;
    TAluno *aluno, *atual, *anterior;
    string nome_curso, nome_aluno;
    char sexo;
    
    if (L->inicioC == NULL) 
	{
		printf("N�O HA CURSOS CADASTRADOS PARA INSERIR OS ALUNOS");
	}
	
	else 
	{
	
		printf("\n\t===CAMPO PARA CADASTRAR ALUNOS EM CURSOS===\n");
		
	    do 
	    {
	      printf("\nDigite o nome do curso que deseja para inserir os alunos:");
	      fflush(stdin);
	      scanf(" %40[^\n]", nome_curso);
	
	      curso = pesquisar_Curso(L, nome_curso);
	    
	      if (curso == NULL) 
	      {
	          printf("CURSO NAO ENCONTRADO!");
	      }
	
	    } while (curso == NULL);
	    
		printf("Digite o nome do aluno(a):");
	    fflush(stdin);
	    scanf(" %40[^\n]", nome_aluno); 
	
	    do 
	    {
	      printf("Digite o sexo do aluno(a):");
	      fflush(stdin);
	      scanf("%c", &sexo);
	    } while( (sexo!='f') && (sexo!='F') && (sexo!='m') && (sexo!='M') );
	
		// a partir daqui come�a a inserir os alunos
	    aluno = (TAluno *)malloc(sizeof(TAluno));
	    strcpy(aluno->nome_aluno, nome_aluno);
	    
	    aluno->sexo = sexo;
	    aluno->prox = NULL;
	    aluno->historico = NULL;
	
	    if (curso->alunos == NULL) 
	    {
	        curso->alunos = aluno;
	    }
	        
	    else 
	    {
	        atual = curso->alunos;
	        anterior = NULL;
	        
	        while (atual != NULL && strcmp(atual->nome_aluno, nome_aluno) < 0) 
	        {
	            anterior = atual;
	            atual = atual->prox;
	        }
	        
	        if (anterior == NULL) 
	        {
	            aluno->prox = curso->alunos;
	            curso->alunos = aluno;
	        }
	        else 
	        {
	            anterior->prox = aluno;
	            aluno->prox = atual;
	        }
	    }
	    	printf("Aluno(a) inserido!");
	}

}
//========================================
//fun��o para exibir os alunos nos cursos
void exibir_alunos_em_curso(TLista *L) 
{
    string nome_curso;
    TCurso *curso;
    
    if (L->inicioC == NULL) 
	{
		printf("NAO HA CURSOS CADASTRADOS PARA EXIBIR OS ALUNOS");
	}
    
    else 
	{
		printf("\n\t===CAMPO PARA EXIBIR ALUNOS EM CURSO===\n");
	
	    do 
	    {
	      printf("\nDigite o nome do curso que deseja para exibir os alunos:");
	      fflush(stdin);
	      scanf(" %40[^\n]",nome_curso);
	      
	      curso = pesquisar_Curso(L, nome_curso);
	      
	      if (curso == NULL) 
	      {
	        printf("\nCURSO NAO ENCONTRADO!");
	      }
	    } while (curso == NULL);
	    
	    printf("\n\t===ALUNOS DO CURSO===\n");
	    if (curso->alunos == NULL) 
	    {
	      printf("NAO TEM NENHUM ALUNO MATRICULADO NESSE CURSO!\n");
	    }
	    
	    TAluno *atual = curso->alunos;
	    while (atual != NULL) 
	    {
	      printf("Aluno(a): %s, Sexo: %c\n", atual->nome_aluno, atual->sexo);
	      atual = atual->prox;
	    }
	}
	
}
//========================================
//fun��o para excluir alunos nos cursos
void excluir_aluno_de_curso(TLista *L)
{
    string nome_aluno, nome_curso;
    
    TAluno *aluno, *anterior, *atual;
    TCurso *curso;
    
    if (L->inicioC == NULL) 
	{
		printf("NAO HA CURSOS CADASTRADOS PARA EXCLUIR OS ALUNOS");
	}
    
    else 
	{
		printf("\n\t===CAMPO PARA EXCLUIR ALUNO DE CURSO===\n");
	
	    do 
	    {
	      printf("Digite o nome do curso para excluir o aluno(a):");
	      fflush(stdin);
	      scanf(" %40[^\n]", nome_curso);
	    
	      curso = pesquisar_Curso(L, nome_curso);
	    
	      if (curso == NULL) 
	      {
	        printf("\nCURSO NAO ENCONTRADO!\n");
	      }
	    } while (curso == NULL);
	
	    do
	    {
	      printf("Digite o nome do Aluno(a):");
	      fflush(stdin);
	      scanf(" %40[^\n]", nome_aluno);
	
	      aluno = pesquisar_aluno(curso, nome_aluno);
	
	      if (aluno == NULL) 
	      {
	        printf("\nALUNO(A) NAO ENCONTRADO!");
	      }
		} while(aluno == NULL);
	    
	    anterior = NULL;
	    atual = curso->alunos;
	    
	    while (atual != NULL && strcmp(atual->nome_aluno, nome_aluno) != 0) 
	    {
	        anterior = atual;
	        atual = atual->prox;
	    }
	    
	    if (atual == NULL) 
	    {
	        printf("ALUNO NAO ENCONTRADO NESTE CURSO!");
	    }
	    
	    if (anterior == NULL) 
	    {
	        // O aluno a ser exclu�do � o primeiro da lista de alunos do curso
	        curso->alunos = atual->prox;
	    } 
	    else 
	    {
	        // O aluno a ser exclu�do nao � o primeiro da lista de alunos do curso
	        anterior->prox = atual->prox;
	    }
	    
	    free(atual);
	    printf("Aluno(a) excluido(a)!\n");
	}
    
}
//========================================
//fun��o para cadastrar o historico dos alunos
void cadastrar_historico_para_aluno(TLista *L) 
{
  string nome_aluno, nome_curso, nome_disciplina, condicao;
  float nota, percentualFrequencia; 
  TCurso *curso; 
  TAluno *aluno;
  TDisciplina *disciplina;
  THistorico *atual, *novo, *historico;

	if (L->inicioC == NULL && L->inicioD == NULL) 
	{
		printf("NAO HA CURSOS E DISCIPLINAS CADASTRADADOS PARA SER POSSIVEL CADASTRAR UM HISTORICO!");
	}
	
	else 
	{
		printf("\n\t===CAMPO PARA CADASTRAR HISTORICO DE ALUNO===\n");
		
		do 
	    {
	      printf("\nDigite o nome do curso para inserir historico do aluno(a):");
	      fflush(stdin);
	      scanf(" %40[^\n]", nome_curso);
	    
	      curso = pesquisar_Curso(L, nome_curso);
	    
	      if (curso == NULL) 
	      {
	        printf("CURSO NAO ENCONTRADO!\n");
	      }
	    } while (curso == NULL);
		
		 do 
		{
		   printf("Digite o nome do Aluno(a):");
		   fflush(stdin);
		   scanf(" %40[^\n]", nome_aluno);
		    
		   aluno = pesquisar_aluno(curso,nome_aluno);
		   
		   if(aluno == NULL)
		   {
		     printf("ALUNO(A) NAO ENCONTRADO!\n");
		   }
		  
		} while (aluno == NULL);
		
	    do 
	  {
	    printf("Digite o nome da Disciplina:");
	    fflush(stdin);
	    scanf(" %40[^\n]", nome_disciplina);
	  
	    disciplina = pesquisar_disciplina(L,nome_disciplina);
	  
	    if (disciplina == NULL) 
	    {
	      printf("DISCIPLINA NAO ENCONTRADA!\n");
	    }
	  } while (disciplina == NULL);
	
	  printf("Digite a nota do aluno(a):");
	  fflush(stdin);
	  scanf(" %f", &nota);
		
		do 
		{
			printf("Digite o Percentual de Frequencia do Aluno(a):");
	  		fflush(stdin);   //testar
			scanf(" %f", &percentualFrequencia);
		} while ((percentualFrequencia<0) || (percentualFrequencia>100));
	
	  printf("Digite a Condicao do Aluno(a) na Discplina (Aprovado, Reprovado ou Cursando):");
	  fflush(stdin);
	  scanf(" %40[^\n]", condicao);
	  
	  //a partir daqui come�a a inserir o hist�rico do aluno solicitado
	  novo = (THistorico *)malloc(sizeof(THistorico));
	  novo->disciplina = disciplina;
	  strcpy(novo->condicao , condicao);
	  novo->nota = nota;
	  novo->percentualFrequencia = percentualFrequencia;
	  novo->prox = NULL;
	
	  if (aluno->historico == NULL) 
	  {
	    aluno->historico = novo;
	  }
	
	  else 
	  {
	
	    historico = aluno -> historico;
	    atual = historico;
	    while (historico != NULL)
	    {
	      atual = historico;
	      historico = historico->prox;
	    }
	    
	    atual->prox = novo;
	    
	  }
	  
	} 
	printf("Historico inserido!");
}
//==============================================
//fun��o para exibir os historicos solicitados
void exibir_historico_de_alunos(TLista *L) 
{
  string nome_aluno, nome_curso;

  TCurso *curso;
  TAluno *aluno;
  THistorico *atual;

	if (L->inicioC == NULL && L->inicioD == NULL) 
	{
		printf("NAO HA CURSOS E DISCIPLINAS CADASTRADADOS PARA SER POSSIVEL EXIBIR UM HISTORICO!");
	}
		
	else 
	{
		printf("\n\t===CAMPO PARA EXIBIR HISTORICO DE ALUNO===\n");
		
		do 
		{
			printf("Digite o nome do Curso:");
			fflush(stdin);
			scanf(" %40[^\n]", nome_curso);
			
			curso = pesquisar_Curso(L,nome_curso);
	    
			if (curso == NULL) 
			{
			    printf("\nCURSO NAO ENCONTRADO!");
			}
	  	} while (curso == NULL);
		
		do 
		  {
		    printf("Digite o nome do Aluno(a):");
		    fflush(stdin);
		    scanf(" %40[^\n]", nome_aluno);
		    
		    aluno = pesquisar_aluno(curso,nome_aluno);
		    
		    if(aluno == NULL)
		    {
		      printf("ALUNO(A) NAO ENCONTRADO!\n");
		    }
		  } while (aluno == NULL);
		  
		if (aluno->historico == NULL) 
		{
			printf("O ALUNO(A) NAO POSSUI HISTORICO CADASTRADO!\n");
		}
		  
		else 
		{	  	
			
			atual = aluno->historico;
			printf("\n\t\t===Historico do(a) Aluno(a) %s===\n", nome_aluno);
			while ( atual != NULL)
			{
				printf("\nCurso: %s\n", curso->nome_curso);
			    printf("\nDisciplina: %s, Carga Horaria da disciplina:%d\n",  atual->disciplina->nome, atual->disciplina->cargaHoraria);
			    printf("\nNota: %.2f | Percentual de Frequencia: %.2f | Condicao: %s\n", atual->nota, atual->percentualFrequencia, atual->condicao);
			    printf("===================================================================");
			    atual = atual->prox;
			}
			
		}
  	}

}
//========================================
//fun��o para excluir o historico solicitado
void excluir_historico_de_aluno(TLista *L) 
{
	string nome_aluno, nome_curso, nome_disciplina;

    TCurso *curso; 
    TAluno *aluno;
    TDisciplina *disciplina;
    THistorico *historico, *anterior;

	if (L->inicioC == NULL && L->inicioD == NULL) 
	{
		printf("NAO HA CURSOS E DISCIPLINAS CADASTRADADOS PARA SER POSSIVEL EXCLUIR UM HISTORICO!");
	}
	
	else 
	{
			printf("\n\t===CAMPO PARA EXCLUIR HISTORICO DE ALUNO===\n");
				
			do 
			{
				printf("Digite o nome do Curso:");
			    fflush(stdin);
			    scanf(" %40[^\n]", nome_curso);
			
			    curso = pesquisar_Curso(L,nome_curso);
			        
			    if (curso == NULL) 
			    {
			        printf("CURSO NAO ENCONTRADO!");
			    }
			} while (curso == NULL);
			
			do 
			{
			    printf("Digite o nome do Aluno(a):");
			    fflush(stdin);
			    scanf(" %40[^\n]", nome_aluno);
			        
			    aluno = pesquisar_aluno(curso,nome_aluno);
			        
			    if(aluno == NULL)
			    {
			        printf("ALUNO(A) NAO ENCONTRADO NESTE CURSO!\n");
			    }
			} while (aluno == NULL);
			    
			if (aluno->historico == NULL) 
			{
			    printf("O ALUNO NAO POSSUI HISTORICO CADASTRADO!\n"); 
			}
		
			else 
			{
				do 
			    {
			    printf("Digite o nome da Disciplina:");
			        fflush(stdin);
			        scanf(" %40[^\n]", nome_disciplina);
			        	
			        disciplina = pesquisar_disciplina(L,nome_disciplina);
			        
			        if (disciplina == NULL) 
			        {
			        	printf("\nDISCIPLINA NAO ENCONTRADA!");
			        }
			    } while (disciplina == NULL);
			    
			    historico = aluno->historico;
			    anterior = NULL;
				
					while (historico != NULL) 
					{
						if (strcmp(historico->disciplina->nome, nome_disciplina) == 0)
			    		{
				            if (anterior == NULL)
				            {
				                aluno->historico = historico->prox;
				            }
					        
							else
					        {
					            anterior->prox = historico->prox;
					        }
				            
							free(historico);
				        	printf("Historico excluido!\n"); 
			        	}
			        
						anterior = historico;
			        	historico = historico->prox;
					}
			}
	}
}  
//========================================
