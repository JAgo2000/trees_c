#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/////////////////////////////////#include
typedef struct node_s
{
    char songtitle[256], interpreter[256];
    struct node_s *parent, *left, *right;
} node_t;
///////////////////////////////////////////////////////////////node_t;
node_t *create_node(char songtitle[],char interpreter[])
{
    node_t *new_node;
    if ((new_node = malloc(sizeof(node_t))) == 0)
    {
        fprintf(stderr,"kein Speicher alloziert,create_node\n");
        return 0;
    }


    strcpy(new_node->interpreter,interpreter);
    strcpy(new_node->songtitle,songtitle);
    new_node->parent = 0;
    new_node->right  = 0;
    new_node->left   = 0;

    return (new_node);
}
//////////////////////////////////////////////////////////////////////////////////create_node
node_t *insert_node(node_t *rootnode,char songtitle[],char interpreter[])
{
    node_t *node_new=create_node(songtitle, interpreter);
    node_t *node_search=rootnode;

    if (node_search == 0)
    {
        return(node_new);
    }
    else
    {
        long ende=0;
        while(ende==0)
        {
            if (strcmp(node_new->songtitle,node_search->songtitle)<=0)
            {
                if((node_search->left)==0)
                {
                    node_new->parent=node_search;
                    node_search->left=node_new;

                    ende=1;
                }
                else
                {
                    node_search=node_search->left;
                }
            }
            else
            {
                if((node_search->right)==0)
                {
                    node_new->parent=node_search;
                    node_search->right=node_new;
                    ende=1;
                }
                else
                {
                    node_search=node_search->right;
                }
            }
        }

    }
    return(rootnode);
}
////////////////////////////////////////////////////////////print_tree
void print_tree(node_t *roodnode, long level)
{

    long i;
    if(roodnode)
    {
        if (roodnode->left) print_tree(roodnode->left, level + 1);

        for (i = 0; i < level; ++i) fprintf(stdout, "  ");

        printf("%s,%s\n", roodnode->songtitle,roodnode->interpreter);



        if (roodnode->right) print_tree(roodnode->right, level + 1);
    }
    else
    {
        printf("ungueltiger Zeiger,print_tree\n");
    }

}
///////////////////////////////////////////////////////////////////////destroy_tree
void destroy_tree(node_t *rootnode)
{
    if(rootnode==0)
    {
        printf("ungueltiger Zeiger,print_tree\n");
        return;
    }
    if(rootnode->left)
        destroy_tree(rootnode->left);
    if(rootnode->right)
        destroy_tree(rootnode->right);


    free(rootnode);

}
///////////////////////////////////////////////////////////////////read_from_keyboard(node_t *fill)

void read_from_keyboard(node_t *fill)
{
    printf("Geben Sie den Songtitel an!\n");
    char zeichen;
    long n=0;

    while((zeichen=getchar())!='\n')
    {

        fill->songtitle[n]=zeichen;
        n++;
        if(n>255)
        {
            break;
        }
    }
    fill->songtitle[n]='\0';
    n=0;
    printf("Geben Sie den Interpreten an!\n");
    while((zeichen=getchar())!='\n')
    {

        fill->interpreter[n]=zeichen;
        n++;
        if(n>255)
        {
            break;
        }
    }
    fill->interpreter[n]='\0';
}
///////////////////////////////////////////////////////////count_nodes
long count_nodes(node_t *rootnode)
{
    if(rootnode)
    {
        long anzahl=1;

        if(rootnode->left)
            anzahl=count_nodes(rootnode->left)+anzahl;
        if(rootnode->right)
            anzahl=count_nodes(rootnode->right)+anzahl;

        return (anzahl);
    }
    else
    {
        printf("ungueltiger Zeiger,count_nodes\n");
        return(0);
    }
}
///////////////////////////////////////////////////////////////////search_node
node_t *search_node(node_t *rootnode,char songtitle[])
{
    if(rootnode)
    {
        if ((strcmp(songtitle, rootnode->songtitle))==0)
        {

            return (rootnode);

        }

        if ((strcmp(songtitle, rootnode->songtitle))<=0)
        {
            if (rootnode->left != 0)
            {
                rootnode=search_node(rootnode->left,songtitle);
            }
            else
            {
                printf("Nicht gefunden! \n");
                return(0);
            }
        }
        else
        {
            if (rootnode->right != 0)
            {
                rootnode=search_node(rootnode->right,songtitle);

            }
            else
            {
                printf("Nicht gefunden! \n");
                return(0);

            }
        }
    }
    else
    {
        printf("ungueltiger Zeiger,search_node\nw");
        return 0;
    }
    if ((strcmp(songtitle, rootnode->songtitle))==0) /* gefunden */
    {
        printf("rootnodereturn\n");
        return (rootnode);

    }
    else
    {
        return(0);
    }

}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
node_t **search_all(node_t* rootnode,char interpreter[],long *found,node_t **node_found_array)
{
    if(rootnode)
    {

        if(strcmp(interpreter,rootnode->interpreter)==0)
        {
            if(*found!=0)
            {
                node_found_array=realloc(node_found_array,sizeof(node_t*)*(*found+1));

            }
            else
            {
                node_found_array = malloc(sizeof(node_t*));

            }
            if(node_found_array)
            {
                node_found_array[*found]=rootnode;
                printf("%p\n",node_found_array);
                *found=*found+1;
            }

        }

        if(rootnode->left)
            node_found_array=search_all(rootnode->left,interpreter,found,node_found_array);
        if(rootnode->right)
            node_found_array=search_all(rootnode->right,interpreter,found,node_found_array);

    }
    else
    {
        printf("ungueltiger Zeiger,search_interpreter_all\n");
    }
    if(*found)
    {
        return(node_found_array);
    }
    else
    {
        return(0);
    }
}
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
long max_depth(node_t *rootnode,long *tiefe,long level)
{
    if(*tiefe<level+1)
    {
        *tiefe=level+1;
    }
    if(rootnode)
    {
        if (rootnode->left) max_depth(rootnode->left,tiefe,level + 1);

        if (rootnode->right) max_depth(rootnode->right,tiefe, level + 1);
    }
    else
    {
        printf("ungueltiger Zeiger,print_tree\n");
        return(0);
    }
    return(*tiefe);

}
/////////////////////////////////////////////////////////////////////////////////
void print_level(node_t*rootnode,long level,long *level_of_interest)
{
    if(rootnode)
    {
        if(level==*level_of_interest)
        {
            printf("%s\n",rootnode->songtitle);
        }
        if(rootnode->left)
        {
            print_level(rootnode->left,level+1,level_of_interest);
        }
        if(rootnode->right)
        {
            print_level(rootnode->right,level+1,level_of_interest);
        }
    }
    else
    {
        printf("ungueltiger Zeiger,print_level\n");
    }

}
////////////////////////////////////////////////////////////////////////////////////
node_t **save_tree(node_t *node,node_t **save_array,long *saved)
{
    if(save_array)
    {
        if((*saved)>1)
        {
            if((save_array=realloc(save_array,sizeof(node_t*)*(*saved)))==0)
            {
                printf("fehlerrealloc,save_tree\n");
                return(0);
            }


        }
        if(*saved)
        {
            save_array[(*saved)-1]=node;
        }
        if(node->left)
        {
            *saved=*saved+1;
            save_array=save_tree(node->left,save_array,saved);
        }

        if(node->right)
        {
            *saved=*saved+1;
            save_array=save_tree(node->right,save_array,saved);
        }

        return(save_array);
    }
    else
    {
        return(0);
    }

}
//////////////////////////////////////////////////////////////////////////////////////
node_t *delete_node(node_t *rootnode,char songtitle[],char interpreter[])
{
    node_t **found_array_interpreter=0;
    node_t **found_array=0;
    node_t *found_node=0;

    long found=0;


    if(rootnode==0)
    {
        printf("ungueltiger Zeiger,delete_node\n");
        return(rootnode);
    }
    else
    {
        if((found_array=malloc(sizeof(node_t)))==0)
        {
            printf("allozieren fehlgeschlagen,delete_node\n");
            return(0);
        }
        found_array_interpreter=search_all(rootnode,interpreter,&found,found_array_interpreter);
        while(found!=0&&found_node==0)
        {
            found_node=search_node(found_array_interpreter[found-1],songtitle);
            found=found-1;
        }

        if(found_node==0)
        {
            return(rootnode);
        }


        if((found_node->left==0)&&(found_node->right==0))//blatt
        {
            if(found_node->parent)
            {
                if((found_node->parent->left)==found_node)
                {
                    found_node->parent->left=0;
                }
                else
                {
                    found_node->parent->right=0;
                }
            }
            else
            {
                rootnode=0;
            }
            free(found_node);
            free(found_array_interpreter);
            return(rootnode);
        }
        ////////////////

        if((found_node->left!=0)||(found_node->right!=0))
        {

            found=0;
            found_array=save_tree(found_node,found_array,&found);

            if(found_node->parent->left==found_node)
            {
                found_node->parent->left=0;
            }
            else
            {
                found_node->parent->right=0;
            }


            long n=0;

            while(found>n)
            {
                insert_node(rootnode,found_array[n]->songtitle,found_array[n]->interpreter);
                n++;
            }
            if(found_node->parent==0)
            {
                rootnode=found_array[0];
            }

        }
        free(found_array);
        free(found_node);
        free(found_array_interpreter);
    }
    return(rootnode);
}
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////7
///////////////////////////////////////////////////////////////////////////////////
int main()
{
    long auswahl=-1;
    node_t *rootnode=0;
    node_t *search=0;
    node_t *print=create_node("0","0");
    char array[255]= {0};
    char array2[255]= {0};
    long count=0;
    node_t **node_found_array;
    long found=0;
    long tiefe=0;
    long level_of_interest=0;
    while(auswahl!=0)
    {
        printf("0. Programm beenden\n");
        printf("1. Gesamten Baum loeschen\n");
        printf("2. Neuen Knoten von der Tastatur einlesen und im Baum ablegen\n");
        printf("3. Baum ausgeben\n");
        printf("4. Anzahl der Knoten bestimmen\n");
        printf("5. Ersten Knoten mit Songtitle suchen\n");
        printf("6. Alle Knoten mit Interpreter suchen\n");
        printf("7. Maximale Tiefe des Baumes ausgeben\n");
        printf("8. Ebene x des Baumes ausgeben\n");
        printf("9. Bestimmten Knoten löschen\n");
        scanf("%ld",&auswahl);
        getchar();
        printf("rootnode=%p\n",rootnode);
        switch(auswahl)
        {
        case(0):
        {
            printf("exit......\n\n");
            break;
        }

        case(1):
        {

            destroy_tree(rootnode);
            rootnode=0;
            break;
        }

        case(2):
        {
            read_from_keyboard(print);
            rootnode=insert_node(rootnode,print->songtitle,print->interpreter);
            break;
        }
        case(3):
        {
            print_tree(rootnode,0);
            break;
        }
        case(4):
        {
            count=count_nodes(rootnode);
            printf("Anzahl=%ld\n",count);
            break;
        }
        case(5):
        {
            printf("Geben Sie den zu suchenden Songtitel an: ");
            scanf("%s",array);
            getchar();
            search=search_node(rootnode,array);
            if(search)
            {
                printf("%s\n",search->songtitle);
            }
            else
            {
                printf("Not found\n");
            }
        }
        break;
        case(6):
        {
            node_found_array=0;
            printf("Geben Sie den zu suchenden Interpreten an: ");
            scanf("%s",array);
            getchar();
            node_found_array=search_all(rootnode,array,&found,node_found_array);
            if(node_found_array)
            {


                while(found!=0)
                {
                    printf("%s %s\n",node_found_array[found-1]->songtitle,node_found_array[found-1]->interpreter);
                    found=found-1;
                }
            }
            else
            {
                printf("Not found\n");
            }
            free(node_found_array);
            break;
        }
        case(7):
        {
            max_depth(rootnode,&tiefe,0);
            printf("Max_Tiefe=%ld\n",tiefe);
            tiefe=0;
            break;
        }
        case(8):
        {
            printf("Geben Sie den auszugebenden Level an: ");
            scanf("%ld",&level_of_interest);
            getchar();
            print_level(rootnode,0,&level_of_interest);
            level_of_interest=0;
            break;
        }
        case(9):
        {
            printf("Geben Sie den zu suchenden Songtitel an: ");
            scanf("%s",array);
            getchar();
            printf("Geben Sie den zu suchenden Interpreten an: ");
            scanf("%s",array2);
            getchar();
            rootnode=delete_node(rootnode,array,array2);
            print_tree(rootnode,0);
            break;
        }
        default:
        {
            printf("falsche Eingabe\n\n");
        }
        }

    }
    return 0;
}
