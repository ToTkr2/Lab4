# Lab4
一.实验目的及基本要求
---
设计和实现最佳置换算法、先进先出置换算法、最近最久未使用置换算法、页面缓冲置换算法；通过页面访问序列随机发生器实现对上述算法的测试及性能比较。  

二.实验分析
---
2.1最佳置换算法（OPT）
---

最佳(Optimal, OPT)置换算法所选择的被淘汰页面将是以后永不使用的，或者是在最长时间内不再被访问的页面,这样可以保证获得最低的缺页率。但由于人们目前无法预知进程在内存下的若千页面中哪个是未来最长时间内不再被访问的，因而该算法无法实现。  

2.2先进先出置换算法（FIFO）
---

优先淘汰最早进入内存的页面，亦即在内存中驻留时间最久的页面。该算法实现简单，只需把调入内存的页面根据先后次序链接成队列，设置一个指针总指向最早的页面。但该算法与进程实际运行时的规律不适应，因为在进程中，有的页面经常被访问。 

2.3最近最久未使用算法（LRU）
---

选择最近最长时间未访问过的页面予以淘汰，它认为过去一段时间内未访问过的页面，在最近的将来可能也不会被访问。该算法为每个页面设置一个访问字段，来记录页面自上次被访问以来所经历的时间，淘汰页面时选择现有页面中值最大的予以淘汰。 

2.4改进的时钟置换算法
---

简单的CLOCK算法是给每一帧关联一个附加位，称为使用位。当某一页首次装入主存时，该帧的使用位设置为1;当该页随后再被访问到时，它的使用位也被置为1。对于页替换算法，用于替换的候选帧集合看做一个循环缓冲区，并且有一个指针与之相关联。当某一页被替换时，该指针被设置成指向缓冲区中的下一帧。当需要替换一页时，操作系统扫描缓冲区，以查找使用位被置为0的一帧。每当遇到一个使用位为1的帧时，操作系统就将该位重新置为0；如果在这个过程开始时，缓冲区中所有帧的使用位均为0，则选择遇到的第一个帧替换；如果所有帧的使用位均为1,则指针在缓冲区中完整地循环一周，把所有使用位都置为0，并且停留在最初的位置上，替换该帧中的页。由于该算法循环地检查各页面的情况。  

CLOCK算法的性能比较接近LRU，而通过增加使用的位数目，可以使得CLOCK算法更加高效。在使用位的基础上再增加一个修改位，则得到改进型的CLOCK置换算法。这样，每一帧都处于以下四种情况之一：  
1.	最近未被访问，也未被修改(u=0, m=0)。  
2.	最近被访问，但未被修改(u=1, m=0)。  
3.	最近未被访问，但被修改(u=0, m=1)。  
4.	最近被访问，被修改(u=1, m=1)。  
算法执行如下操作步骤：  
1.	从指针的当前位置开始，扫描帧缓冲区。在这次扫描过程中，对使用位不做任何修改。选择遇到的第一个帧(u=0, m=0)用于替换。  
2.	如果第1)步失败，则重新扫描，查找(u=0, m=1)的帧。选择遇到的第一个这样的帧用于替换。在这个扫描过程中，对每个跳过的帧，把它的使用位设置成0。  
3.	如果第2)步失败，指针将回到它的最初位置，并且集合中所有帧的使用位均为0。重复第1步，并且如果有必要，重复第2步。这样将可以找到供替换的帧  

三.代码分析
---
代码中一共包含四个函数，分别是  
void FIFO();		//先进先出置换算法  
void FIFO();    //最佳置换算法  
void LPU();     //最近最久未使用算法  
void Clock();    //改进的时钟置换算法  

```
typedef struct page_replacement_algorithm

{
    char page;
    char interrupt;

}PRA;
```

此结构体为页面状态，page为当前页面引用号，interrupt为是否出现缺页的标志  
```
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
这段代码是随机生成工作区，我设定为生成n个10以内的数
FIFO算法：

void FIFO()

{

    memset(ans,'0',sizeof(ans));

    queue<char> q;

    PRA pra[MAX];

    int n,m,p,internum=1;

    printf("请输入页面走向和物理块数\n");

    scanf("%d %d",&n,&m);

    getchar();

     srand ( (unsigned) time (NULL)); //用时间做种，每次产生随机数不一样

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


    queue<char> qq;

    int cnt = 0,tot = 0;

    for(int i=0; i<m; i++){

        qq = q;

        for(int j=0; j<=i; j++){

            ans[j][i] = qq.front();

            qq.pop();

        }

        pra[i].interrupt = '*';

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

    printf("\n先进先出置换算法:\n");

    printf("%8s:","页面走向");

    for(int r=0; r<n; r++) printf("%3c ",pra[r].page);

    printf("\n");

    for(int i=0; i<m; i++){

        printf("%6s%2d:","物理块",i+1);

        for(int j=0; j<n; j++) printf("%3c ",ans[i][j]);

        printf("\n");

    }

    printf("%8s:","缺页中断");

    for(int r=0; r<n; r++) printf("%3c ",pra[r].interrupt);

    printf("\n");

    printf("缺页次数：%d\n",internum);

}
```
LPU算法：
```
void LRU()

{

    memset(ans,'0',sizeof(ans));

    PRA pra[MAX];

    int n,m,p,internum=1;

    printf("请输入页面走向和物理块数\n");

    scanf("%d %d",&n,&m);

    getchar();

      srand ( (unsigned) time (NULL)); //用时间做种，每次产生随机数不一样

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
    printf("请输入n个字符：\n");

    for(int i=0; i<n; i++) scanf("%c",&pra[i].page);*/

    for(int i=0; i<m; i++){
        for(int j=0; j<=i; j++){

            ans[j][i] = pra[j].page;

        }
    pra[i].interrupt = '*';

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

    printf("最近最久未使用置换算法\n");

    printf("%8s:","页面走向");

    for(int r=0; r<n; r++) printf("%3c ",pra[r].page);

    printf("\n");

    for(int i=0; i<m; i++){

    printf("%6s%2d:","物理块",i+1);

    for(int j=0; j<n; j++) printf("%3c ",ans[i][j]);

    printf("\n");

    }

    printf("%8s:","缺页中断");

    for(int r=0; r<n; r++) printf("%3c ",pra[r].interrupt);

    printf("\n");

    printf("缺页次数：%d\n",internum);
}
```
OPT算法：  
```
void OPT()

{

    memset(ans,'0',sizeof(ans));


    memset(mark,0,sizeof(mark));

    PRA pra[MAX];

    int n,m,p,internum=1;

    printf("请输入页面走向(字符表示)和物理块数(整型):\n");

    scanf("%d %d",&n,&m);

    getchar();
/*
    printf("请输入n个字符(不要有空格):\n");

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

    printf("\n最佳置换算法:\n");

    printf("%8s:","页面走向");

    for(int r=0; r<n; r++) printf("%3c ",pra[r].page);

    printf("\n");

    for(int i=0; i<m; i++){

        printf("%6s%2d:","物理块",i+1);

    for(int j=0; j<n; j++) printf("%3c ",ans[i][j]);

    printf("\n");
    }

    printf("%8s:","缺页中断");

    for(int r=0; r<n; r++) printf("%3c ",pra[r].interrupt);

    printf("\n");

    printf("缺页次数：%d\n",internum);

}
```
改进的CLOCK算法：  
```
void Clock()
{
    int p,n,m;
    int index = 1;
    int page_lack = 0;
    memset(mark, -1, sizeof(mark));
int page[MAX];

 printf("请输入页面走向(字符表示)和物理块数(整型):\n");

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
        if(page_in_block[page[i]]){//如果page[i]已经在内存中
            nru[page_in_block[page[i]]] = 1;//重新标记这个物理块中的页面被访问过了
            cout<<endl<<"第"<<i<<"次: 页面"<<page[i]<<"已经存在物理块"<< page_in_block[page[i]] << "中!"<<endl;
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
                    if(nru[index] == 0){//替换该页面
                        nru[index] = 1;
                        page_in_block[mark[index]] = 0;
                        cout<<endl<<"第"<<i<<"次: 物理块"<<index<<"中的页面"<< mark[index] <<"最近未被使用，将要被页面"<<page[i]<<"替换!"<<endl;
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
   printf("缺页次数：%d\n",page_lack);
}
```
五．	实验结果
---
1.最佳置换算法实验结果：  
由图可知随机生成的序列号为7,3,6,5,4,4,1,0,8,2,3,3 设置的物理块为2，缺页次数为9  
![image text](https://github.com/ToTkr2/Lab4/blob/master/img/1.png)  
2.先进先出置换算法实验结果：  
由图可知随机生成的序列号为1,4,6,5,8,9,0,0,2,9,1,4 设置的物理块为2，缺页次数为11  
![image text](https://github.com/ToTkr2/Lab4/blob/master/img/2.png)  
3.最近最久未使用置换算法实验结果：  
由图可知随机生成的序列号为2,2,2,7,8,3,1,9,2,0,2,6,设置的物理块为2，缺页次数为10  
![image text](https://github.com/ToTkr2/Lab4/blob/master/img/1.1.png)  
4.改进的CLOCK置换算法实验结果：  
由图可知替换过程,设置的物理块为2，缺页次数为10  
 ![image text](https://github.com/ToTkr2/Lab4/blob/master/img/1.2.png)  

参考网页：https://www.cnblogs.com/hujunzheng/p/4831007.html
https://blog.csdn.net/qq_35685675/article/details/80744458






