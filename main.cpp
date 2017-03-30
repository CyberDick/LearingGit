#include <iostream>
#include "PeacockHash.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

// #define MAX_READ 450000
#define MAX_READ 1000000
#define CHECKPOINT 10000
#define SEARCH_COUNT_PER_BATCH 10000

#define KEY_LEN 30

using namespace std;

char read_key[MAX_READ][KEY_LEN];
int read_val[MAX_READ];
char read_key_failed[MAX_READ][KEY_LEN];
int read_val_failed[MAX_READ];
char input_filename[] = "../datasets/d1q.txt";
char input_filenamefailed[] = "../datasets/d2q.txt";
char output_filename[] = "output.txt";
char output_filename_failed[] = "outputfailed.txt";

int main()
{
    FILE * fin = fopen(input_filename, "r");
    FILE * finFailed = fopen(input_filenamefailed,"r");
    FILE * fout = fopen(output_filename, "w+");
    FILE * foutFailed = fopen(output_filename_failed,"w+");
    int i;
    if(fin == NULL){
        printf("can't find the d1q.txt file!\n");
        return -1;
    }
    if(finFailed == NULL){
        printf("can't find the d2q.txt file!\n");
        return -1;
    }
    srand((unsigned int)time(NULL));

    for (i = 0; i < MAX_READ; ++i) {
        fscanf(fin, "%s %d", read_key[i], read_val + i);
    }
    for (i = 0; i < MAX_READ; ++i) {
        fscanf(finFailed, "%s %d", read_key_failed[i], read_val_failed + i);
    }
    fclose(fin);
    fclose(finFailed);

    PeacockHash p;
    // p.init(8, 5, 400000, 1000000);
    p.init(8, 5, 1000000, 5000000);

    // test for correctness
//    for (i = 0; i < SEARCH_COUNT_PER_BATCH; ++i) {
//        int idx = rand() % MAX_READ;
//        int result;
//        p.search((unsigned char *)read_key[idx], result);
//        if (result != read_val[idx])
//            printf("Not matched!\n");
//    }
    fprintf(fout,"%s\n","装载率     冲突率      插入片外访存     插入内片外访存 \
        查询成功片内访存    查询成功片外访存 ");
    for (i = 0; i < MAX_READ; ++i) {
        p.insert(read_key[i], read_val[i]);

        if ((i + 1) % CHECKPOINT == 0) {
            printf("insert and search for existent elements %d elements.\n", i + 1);

            for (int j = 0; j < SEARCH_COUNT_PER_BATCH; ++j) {
                int idx = rand() % i;
                int result;
                p.search((unsigned char *)read_key[idx], result);
            }
            p.collect();
            p.reportInline(fout,false);
            p.clearSearchStat();
        }
    }
    fprintf(foutFailed,"%s\n","查询失败片内访存     查询失败片外访存");
    for (i = 0; i < MAX_READ; ++i) {
        if ((i + 1) % CHECKPOINT == 0) {
            printf("search for non-existent %d elements.\n", i + 1);
            for (int j = 0; j < SEARCH_COUNT_PER_BATCH; ++j) {
                int idx = rand() % i;
                int result;
                p.search((unsigned char *)read_key_failed[idx], result);
            }
            p.collect();
            p.reportInline(foutFailed,true);
            p.clearSearchStat();
        }
    }
    printf("%d", p.totsize);

    fclose(fout);

    return 0;
}

