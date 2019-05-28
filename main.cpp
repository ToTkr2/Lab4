#include <stdio.h>

#include <iostream>

#include <queue>

#include <stack>

#include <set>

#include <string>

#include <cstring>

#include <cmath>

#include <stdlib.h>

#include <time.h>

#define MAX 1111

int mark[MAX];

using namespace std;

typedef struct page_replacement_algorithm

{
    char page;
    char interrupt;

}PRA;

char ans[MAX][MAX];

void FIFO()

{

    memset(ans,'0',sizeof(ans));

    queue<char> q;

    PRA pra[MAX];

    int n,m,p,internum=0;

    printf("������ҳ��������������\n");

    scanf("%d %d",&n,&m);

    getchar();

     srand ( (unsigned) time (NULL)); //��ʱ�����֣�ÿ�β����������һ��

    p = rand() % 10;
    int e = 8;
    int i;
    double t;
    t = rand()%10/10.0;
    for (i = 0; i <n; i++)
    {

            pra[i].page = (p + rand() % e) % 10+48;
        q.push(pra[i].page);
        double r = (rand() % 10) / 10.0;
        if (r < t)
        {
            p = rand() % 10;
        }
        else
        {
            p = (p + 1) % 10;
        }
    }


 /*
 printf("������n���ַ���\n");


    for(int i=0; i<n; i++)
        {
            scanf("%c",&pra[i].page);
           q.push(pra[i].page);
    }


    for(int i=0;i<n;i++)
    {
        printf("%c\n",pra[i].page);
    }
 srand ( (unsigned) time (NULL)); //��ʱ�����֣�ÿ�β����������һ��

    p = rand() % 10;
    int e = 8;
    int i;
    double t;
    t = rand()%10/10.0;
    for (i = 0; i <n; i++)
    {

            pra[i].page = (p + rand() % e) % 11;
        q.push(pra[i].page);
        double r = (rand() % 10) / 10.0;
        if (r < t)
        {
            p = rand() % 10;
        }
        else
        {
            p = (p + 1) % 10;
        }
    }

    for(i=0;i<n;i++)
    {
        printf("%d\n",pra[i].page);
    }

    */
    queue<char> qq;

    int cnt = 0,tot = 0;

    for(int i=0; i<m; i++){

        qq = q;

        for(int j=0; j<=i; j++){

            ans[j][i] = qq.front();

            qq.pop();

        }

        pra[i].interrupt = '*';
        internum++;

    }

    q = qq;

    for(int j=m,i=0; j<n; j++,i=0){

        bool flag = true;

    while(i < m){

            ans[i][j] = ans[i][j-1];

        if(ans[i][j] == q.front()&& flag){

                q.pop();
                flag = false;

            }

            i++;

        }

    if(flag){

           internum++;

            pra[j].interrupt = '*';

            for(int r=0; r<m-1; r++)

            ans[r][j] = ans[r+1][j];

            ans[m-1][j] = q.front();

            q.pop();

        }

    else{

            pra[j].interrupt = ' ';

        }

    }

    printf("\n�Ƚ��ȳ��û��㷨:\n");

    printf("%8s:","ҳ������");

    for(int r=0; r<n; r++) printf("%3c ",pra[r].page);

    printf("\n");

    for(int i=0; i<m; i++){

        printf("%6s%2d:","�����",i+1);

        for(int j=0; j<n; j++) printf("%3c ",ans[i][j]);

        printf("\n");

    }

    printf("%8s:","ȱҳ�ж�");

    for(int r=0; r<n; r++) printf("%3c ",pra[r].interrupt);

    printf("\n");

    printf("ȱҳ������%d\n",internum);

}


void LRU()

{

    memset(ans,'0',sizeof(ans));

    PRA pra[MAX];

    int n,m,p,internum=0;

    printf("������ҳ��������������\n");

    scanf("%d %d",&n,&m);

    getchar();

      srand ( (unsigned) time (NULL)); //��ʱ�����֣�ÿ�β����������һ��

    p = rand() % 10;
    int e = 8;
    int i;
    double t;
    t = rand()%10/10.0;
    for (i = 0; i <n; i++)
    {

            pra[i].page = (p + rand() % e) % 10+48;

        double r = (rand() % 10) / 10.0;
        if (r < t)
        {
            p = rand() % 10;
        }
        else
        {
            p = (p + 1) % 10;
        }
    }
    /*
    printf("������n���ַ���\n");

    for(int i=0; i<n; i++) scanf("%c",&pra[i].page);*/

    for(int i=0; i<m; i++){
        for(int j=0; j<=i; j++){

            ans[j][i] = pra[j].page;

        }
    pra[i].interrupt = '*';
    internum++;
        }

    for(int i=m; i<n; i++){

    bool flag = true;

        for(int j=0; j<m; j++){

        ans[j][i] = ans[j][i-1];

            if(ans[j][i] == pra[i].page){

                pra[i].interrupt = ' ';

                flag = false;

            }

        }

        if(flag){

            pra[i].interrupt = '*';

            internum++;

            for(int j=0; j<m; j++){
                if(ans[j][i] == pra[i-m].page){

                    ans[j][i] = pra[i].page;
                        break;

                }

            }

        }

    }

    printf("������δʹ���û��㷨\n");

    printf("%8s:","ҳ������");

    for(int r=0; r<n; r++) printf("%3c ",pra[r].page);

    printf("\n");

    for(int i=0; i<m; i++){

    printf("%6s%2d:","�����",i+1);

    for(int j=0; j<n; j++) printf("%3c ",ans[i][j]);

    printf("\n");

    }

    printf("%8s:","ȱҳ�ж�");

    for(int r=0; r<n; r++) printf("%3c ",pra[r].interrupt);

    printf("\n");

    printf("ȱҳ������%d\n",internum);
}



void OPT()

{

    memset(ans,'0',sizeof(ans));


    memset(mark,0,sizeof(mark));

    PRA pra[MAX];

    int n,m,p,internum=0;

    printf("������ҳ������(�ַ���ʾ)���������(����):\n");

    scanf("%d %d",&n,&m);

    getchar();
/*
    printf("������n���ַ�(��Ҫ�пո�):\n");

    for(int i=0; i<n; i++) scanf("%c",&pra[i].page);

*/
p = rand() % 10;
    int e = 8;
    int i;
    double t;
    t = rand()%10/10.0;
    for (i = 0; i <n; i++)
    {

            pra[i].page = (p + rand() % e) % 10+48;

        double r = (rand() % 10) / 10.0;
        if (r < t)
        {
            p = rand() % 10;
        }
        else
        {
            p = (p + 1) % 10;
        }
    }

    for(int i=0; i<m; i++){

        for(int j=0; j<=i; j++){

            ans[j][i] = pra[j].page;

        }

        pra[i].interrupt = '*';

        internum++;
    }

    for(int i=m; i<n; i++){

        bool flag = true;

        for(int j=0; j<m; j++){

            ans[j][i] = ans[j][i-1];

            if(ans[j][i] == pra[i].page){

                pra[i].interrupt = ' ';

                flag = false;

            }

        }

        int im;

        bool Goto = true;

        int tot = 0;

        if(flag){

            pra[i].interrupt = '*';

            internum++;

        for(int t=i; t<n;t++){

            for(int j=0; j<m; j++){

                if(ans[j][i] == pra[t].page&& !mark[pra[i].page]){
                        mark[pra[i].page] = 1;

                        tot++;

                        if(tot == 3){

                            ans[j][i] =pra[i].page;

                            Goto = false;

                            break;

                        }

                    }

                    else if(ans[j][i] !=pra[t].page) im = j;

                }

                if(!Goto) break;

            }

            if(tot<3) ans[im][i] =pra[i].page;
        }

    }

    printf("\n����û��㷨:\n");

    printf("%8s:","ҳ������");

    for(int r=0; r<n; r++) printf("%3c ",pra[r].page);

    printf("\n");

    for(int i=0; i<m; i++){

        printf("%6s%2d:","�����",i+1);

    for(int j=0; j<n; j++) printf("%3c ",ans[i][j]);

    printf("\n");
    }

    printf("%8s:","ȱҳ�ж�");

    for(int r=0; r<n; r++) printf("%3c ",pra[r].interrupt);

    printf("\n");

    printf("ȱҳ������%d\n",internum);

}
int nru[MAX];//��ʾ ����� i ���ʱ�򱻷��ʹ�
int page_in_block[MAX];//ҳ�� i �� block���±�����

void Clock()
{
    int p,n,m;
    int index = 1;
    int page_lack = 0;
    memset(mark, -1, sizeof(mark));
int page[MAX];

 printf("������ҳ������(�ַ���ʾ)���������(����):\n");

    scanf("%d %d",&n,&m);

    getchar();
p = rand() % 10;
    int e = 8;
    int i;
    double t;
    t = rand()%10/10.0;

    for (i = 0; i <n; i++)
    {
            page[i]=(p + rand() % e) % 10;


        double r = (rand() % 10) / 10.0;
        if (r < t)
        {
            p = rand() % 10;
        }
        else
        {
            p = (p + 1) % 10;
        }
    }

    for(int i=1; i<=n; ++i){
        if(page_in_block[page[i]]){//���page[i]�Ѿ����ڴ���
            nru[page_in_block[page[i]]] = 1;//���±�����������е�ҳ�汻���ʹ���
            cout<<endl<<"��"<<i<<"��: ҳ��"<<page[i]<<"�Ѿ����������"<< page_in_block[page[i]] << "��!"<<endl;
        }
        else {
            while(true){
                if(index > m) index = 1;
                if(mark[index] == -1) {
                    nru[index] = 1;
                    page_in_block[page[i]] = index;
                    mark[index++] = page[i];
                    ++page_lack;
                    break;
                }
                if(mark[index] == page[i]){
                    nru[index++] = 1;
                    break;
                } else {
                    if(nru[index] == 0){//�滻��ҳ��
                        nru[index] = 1;
                        page_in_block[mark[index]] = 0;
                        cout<<endl<<"��"<<i<<"��: �����"<<index<<"�е�ҳ��"<< mark[index] <<"���δ��ʹ�ã���Ҫ��ҳ��"<<page[i]<<"�滻!"<<endl;
                        page_in_block[page[i]] = index;
                        mark[index++] = page[i];
                        ++page_lack;
                        break;
                    } else
                        nru[index++] = 0;
                }
            }
        }
        for(int k=1; k<=m; ++k)
            cout<<mark[k]<<" ";
        cout<<endl;
    }
   printf("ȱҳ������%d\n",page_lack);
}


int main()

{



    int ca = 0;

    do{

        printf("\n��ѡ���û��㷨���߽�������\n");

        printf("0����������\n1������û�\n2���Ƚ��ȳ�\n3��������δʹ��\n4���Ľ���CLOCK�㷨\n");

        scanf("%d",&ca);

        if(ca == 1) OPT();

        if(ca == 2) FIFO();

        if(ca == 3) LRU();

        if(ca == 4) Clock();

    }while(ca);

    return 0;

}
