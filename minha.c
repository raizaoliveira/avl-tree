#include <stdio.h>
/*#include <stdlib.h>*/
/*#include <math.h>*/
#include "gfx.h"
#define true 1
#define false 0

typedef int bool;

struct s_no
{
	int chave:28;
	int bal:4;
	struct s_no *esq;
	struct s_no *dir;
};

struct s_no *init(int x)
{	
	struct s_no *pt;
	pt = (struct s_no *) malloc( sizeof (struct s_no));
	if (pt == NULL)
	{
		puts("\aMemoria insuficiente.");
		exit(1);
	}
	
	pt->esq = NULL;
	pt->dir = NULL;
	pt->bal = 0;
	pt->chave = x;
	
	return pt;
}
 
/* ROTAÇÂO A DIREITA */  
struct s_no *rot_dir(struct s_no *no)
{  
    struct s_no *aux;  
	printf("\nUsou rotacao a direita\n");
    aux = no->esq;  
    no->esq = aux->dir;
    aux->dir = no;
    return aux;   
}  

/* ROTAÇÂO A ESQUERDA */  
struct s_no *rot_esq(struct s_no *no)
{  
    struct s_no *aux;
	printf("\nUsou rotacao a esquerda\n");
    aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    return aux;   
}  


struct s_no *maloc()
{
	struct s_no *pont;
	pont = (struct s_no*) malloc(sizeof (struct s_no));
	if(pont == NULL)
	{
		puts("\n\aoverflow");
		exit(1);
	}
	else return pont;
}

struct s_no *rotacao_dupla_direita (struct s_no *N3)
{
	struct s_no *N1;
	struct s_no *N2;
	N1 = maloc();
	N2 = maloc();
	N1 = N3->esq;
	N2 = N1->dir;

	puts("Rotacao dupla direita");
       if(N2->esq) N1->dir= N2->esq;
       else N1->dir=NULL;

       if(N2->dir) N3->esq = N2->dir;
       else N3->esq=NULL;

       N2->esq=N1;
       N2->dir=N3;
       
       return N2;
}

struct s_no *rotacao_dupla_esquerda (struct s_no *N1)
{
	
	struct s_no *N3;
	struct s_no *N2;
    	N3 = maloc();
	N2 = maloc();
	N3 = N1->dir;
	N2 = N3->esq;

	puts("Rotacao dupla esquerda");
    	if(N2->esq) N1->dir= N2->esq;
       	else N1->dir=NULL;

    	if(N2->dir) N3->esq = N2->dir;
       	else N3->esq=NULL;

    	N2->esq=N1;
    	N2->dir=N3;    
	return N2;
}

void pre_ordem(struct s_no *pt)
{
	struct s_no *ptaux;
	ptaux = pt;
	if (ptaux != NULL)
	{
		printf("FB:  %d  CHAVE:  %d\n", ptaux->bal, ptaux->chave);
	
		if(ptaux->esq != NULL)
		{
			pre_ordem((pt->esq));
		}
	
		if(ptaux->dir != NULL)
		{
			pre_ordem((pt->dir));
		}
	}

}

int avl_height (struct  s_no *node)
{
    /*retorna a altura da arvore*/
	int esq, dir;

	if (node == NULL) 
	{
		return -1;
	}

    esq = avl_height (node->esq);
    dir = avl_height (node->dir);

	if (esq > dir)
	{
        return esq + 1;
	}
    else
	{
        return dir + 1;
	}
}

int return_FB(struct s_no *pont)
{
	int fb;
	fb = avl_height(pont->esq) - avl_height(pont->dir)  ;
	return fb;
}



struct s_no *CorrigeAVL(struct s_no *pNodo)
{
	if(pNodo != NULL)
	{
		
		pNodo->bal = return_FB(pNodo);
		
		if(pNodo->bal == 2)
		{
			pNodo->esq->bal = return_FB(pNodo->esq);
			
			if(pNodo->esq->bal > 0)
			{
				pNodo = rot_dir(pNodo);
				pNodo->bal = return_FB(pNodo);
			}
			else
			{
				pNodo =  rotacao_dupla_esquerda (pNodo);
				pNodo->bal = return_FB(pNodo);
			}
		}
		else if(pNodo->bal == -2)
		{
			
			pNodo->dir->bal = return_FB(pNodo->dir);
			if(pNodo->dir->bal < 0)
			{
				
				pNodo = rot_esq(pNodo);
				pNodo->bal = return_FB(pNodo);
			}
			else
			{
				
				pNodo = rotacao_dupla_esquerda (pNodo);
				pNodo->bal = return_FB(pNodo);
			}
		}
		pNodo->esq = CorrigeAVL(pNodo->esq);
		pNodo->dir = CorrigeAVL(pNodo->dir);
    }
    return pNodo;
}


struct s_no *InsereAVL(struct s_no *pNodo, int ch)
{
	if (pNodo == NULL)
	{
	    pNodo = init(ch);
		return pNodo;
	}
	else
	{
		if(pNodo->chave == ch)
		{
			printf("\n\aChave %d ja existe.\n", ch);
		}
		else
		{
			if(ch < pNodo->chave)
			{
				pNodo->esq = InsereAVL(pNodo->esq,ch);
			}
			else
			{
				pNodo->dir = InsereAVL(pNodo->dir,ch);
			}
		}
	}
	return pNodo;
}

/****************************************************/  
/* RETORNA MAIOR */  
struct s_no *retorna_maior(struct s_no **no)
{  
    struct s_no *aux;  
    aux = *no;  
    if (aux->dir == NULL)
	{  
        *no=(*no)->esq;  
        return (aux);  
    }
	else
	{	
        return (retorna_maior(&((*no)->dir)));
	}
}  


/****************************************************/  
/* EXCLUI NO */  
int exclui(struct s_no **no, int x)
{ 
    struct s_no *aux;  
    if (*no == NULL)  
        return 0;                 
    if ((*no)->chave == x){  
        aux = *no;  
        /* se não tiver filho na esquerda */  
        if ((*no)->esq==NULL)  
            *no=(*no)->dir; /*então o filho da direita substitui */   
        else   
            /* se não tem filho a direita */  
            if ((*no)->dir==NULL)   
               *no = (*no)->esq; /* então o filho da esquerda substitui */  
            else{ /* senão possui dois filhos */  
               aux = retorna_maior(&((*no)->esq)); /* busca o substituto */  
               (*no)->chave = aux->chave;   
            }  
        free (aux); /* ou é folha */  
        return 1;  
    }else{  
        if (x<(*no)->chave)  
            return (exclui(&((*no)->esq),x));   
        else  
            return (exclui(&((*no)->dir),x));  
    }  
}  


struct s_no *destruir_arvore(struct s_no *no)
{  
    if(no == NULL) 
	{
		printf("\n\tEsta vazia\n");  
		return NULL; /* para garantir o retorno NULL mesmo que a raiz já seja NULL */
	} 
    
	if(no->esq != NULL)
	{
        	no->esq = destruir_arvore(no->esq);
	}
    
	if(no->dir != NULL)
	{
        	no->dir = destruir_arvore(no->dir);
	}
	
    free(no); 
	printf("\nVoltando um nivel..."); 
    return NULL;  
} 

void window(struct s_no *pt, int x, int y, int z)
{
	char str[99];
	struct s_no *aux;
	aux = pt;
	
	if (aux != NULL)
{
	if(aux->esq != NULL)
	{
		gfx_set_color(255, 255, 255);
		gfx_line(x, z, x - y, z + 75);
	}

	if(aux->dir != NULL)
	{
		gfx_set_color(255, 255, 255);
		gfx_line(x, z, x + y, z + 75);
	}
	
	gfx_set_color(207, 207, 207);
	gfx_filled_ellipse(x ,z , 30, 20);

	gfx_set_color( 10, 10, 255);
	gfx_filled_ellipse(x ,z , 30, 20);
	gfx_filled_ellipse(x ,z , 31, 21);

	gfx_set_color(255, 0, 0);
	sprintf(str, "%i", aux->chave);
	gfx_text((x - 20), (z - 7), str);

	window(aux->esq, (x - y), (y / 2), z + 75);
	window(aux->dir, (x + y), (y / 2), z + 75);
}

}




struct s_no *openfile(FILE *p)
{
	struct s_no *ptno;
	ptno = (struct s_no *) malloc(sizeof (struct s_no));
	
	if(fread (ptno, sizeof(ptno), 1, p) == 0)
	{
		free(ptno);
		return NULL;
	}
	else
	{
		ptno->esq = openfile(p) ;
		ptno->dir = openfile(p) ;
		return ptno;

	}

}

void savefile(struct s_no *pt, FILE *p)
{
	if(pt != NULL)
	{
		fwrite(pt, sizeof(struct s_no), 1, p);
		if(pt->esq != NULL)
		{
			savefile(pt->esq, p);
		}
		
		if(pt->dir != NULL)
		{
			savefile(pt->dir, p);
		}
	}
}

int main()
{
	struct s_no *pt;
	int opc;
	int key;
	FILE *p;
	char str[25];
	pt = (struct s_no *) malloc(sizeof(struct s_no));
	pt = NULL;
	
	puts("Welcome");
	do{
		puts("\n********************************\n");
		puts("Informe a opcao desejada:");
		puts("1-inserir\n2-Remover\n3-Abrir \n4-Salvar \n5-Destruir arvore\n6-sair\n");
		puts("********************************\n\n");
		do{
			printf("->    ");
			scanf(" %d", &opc);
		}while((opc < 1) || (opc > 6));
		gfx_init(1000, 600, "AVL");
		switch (opc)
		{
			case 1:
					printf("\nInforme a chave a ser inserida:    ");
					scanf(" %d" , &key);
					pt = InsereAVL(pt, key);
					pt = CorrigeAVL(pt);
					
					break;
			case 2:
					printf("\nInforme a chave a ser removida:    ");
					scanf(" %d" , &key);
					exclui( &pt, key);
					pt = CorrigeAVL(pt);
					pre_ordem(pt);
					break;
			case 3:
					fflush(stdin);
					printf("Informe o nome do arquivo:  ");
					
					gets(str);
					printf("\nString lida:  %s\n", str);

					p = fopen(str, "rb");
					if(!p)
					{
						puts("Nao abriu");
					}
					else
					{
						pt = openfile(p);
					}
					break;
			case 4:
                             		printf("Informe o nome do arquivo:  ");	
					gets(str);
					printf("\nString lida:  %s\n", str);

					p = fopen(str, "w+b");
					if(!p)
					{
						puts("Nao abriu");
					}
					else
					{

						savefile(pt, p);
						fclose(p);
					}
					break;
			case 5:
					pt = destruir_arvore(pt);
					break;
			
		}

	if(pt == NULL)
	{
		gfx_clear();
		gfx_text(500, 50, "Arvore vazia");
	}
	else
	{
		gfx_clear();

		window(pt, 500, 250, 50);
	}

	
	
	

	}while(opc != 6);
	
        gfx_quit();
	
	pt = destruir_arvore(pt);

	
	

	return 0;
}
