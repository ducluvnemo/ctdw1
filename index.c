#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_WORD 5000
#define MAX_LINE 1000
#define MAX_LEN 64
#define MAX_DONG 512

typedef struct {
    char tu[MAX_LEN];       // tu
    int soDong[MAX_DONG];   // danh sach dong
    int count;              // so dong khac nhau
    int countWord;          // so lan tu xuat hien
} MucIndex;

MucIndex indexList[MAX_WORD];
int indexCount = 0;

char stopWords[MAX_WORD][MAX_LEN];
int stopCount = 0;

/* ===================== HAM XU LY ===================== */

void chuyenThuong(char *s) {
    for(int i=0; s[i]; i++) s[i] = tolower(s[i]);
}

int laStopWord(char *w) {
    for(int i=0;i<stopCount;i++)
        if(strcmp(stopWords[i], w)==0) return 1;
    return 0;
}

int laDanhTuRieng(char *goc, char *dong, int pos) {
    if(!isupper(goc[0])) return 0;
    while(pos>0 && isspace(dong[pos-1])) pos--;
    if(pos<=0) return 0;
    if(dong[pos-1]=='.') return 0;
    return 1;
}

int timTu(char *w) {
    for(int i=0;i<indexCount;i++)
        if(strcmp(indexList[i].tu, w)==0) return i;
    return -1;
}

void themDong(MucIndex *item, int soDongMoi) {
    // tang so lan xuat hien
    item->countWord++;

    // kiem tra dong da co trong danh sach chua
    for(int i=0;i<item->count;i++)
        if(item->soDong[i]==soDongMoi) return;

    // them vao danh sach dong
    if(item->count < MAX_DONG)
        item->soDong[item->count++] = soDongMoi;
}

int soSanh(const void *a, const void *b) {
    return strcmp(((MucIndex*)a)->tu, ((MucIndex*)b)->tu);
}

/* ===================== MAIN ===================== */
int main(int argc, char *argv[]) {

    if(argc < 2) {
        printf("Ban phai nhap ten file van ban.\n");
        return 1;
    }

    char *fileNhap = argv[1];

    FILE *fs = fopen("stopw.txt","r");
    if(!fs) { printf("Khong mo duoc stopw.txt\n"); return 1; }

    while(stopCount<MAX_WORD && fscanf(fs,"%s",stopWords[stopCount])!=EOF) {
        chuyenThuong(stopWords[stopCount]);
        stopCount++;
    }
    fclose(fs);

    FILE *fv = fopen(fileNhap,"r");
    if(!fv) { printf("Khong mo duoc file %s\n",fileNhap); return 1; }

    printf("Dang xu ly file: %s\n", fileNhap);

    char dong[MAX_LINE];
    int soDong = 0;

    while(fgets(dong,sizeof(dong),fv)) {
        soDong++;
        int len = strlen(dong);
        char tuRaw[MAX_LEN];
        int pos=0;

        for(int i=0;i<=len;i++) {
            if(isalpha(dong[i])) {
                if(pos<MAX_LEN-1) tuRaw[pos++] = dong[i];
            } else {
                if(pos>0) {
                    tuRaw[pos]='\0';
                    pos=0;

                    char tuThuong[MAX_LEN];
                    strcpy(tuThuong,tuRaw);
                    chuyenThuong(tuThuong);

                    if(laStopWord(tuThuong)) continue;
                    if(laDanhTuRieng(tuRaw,dong,i-strlen(tuRaw))) continue;

                    int idx = timTu(tuThuong);
                    if(idx==-1) {
                        if(indexCount>=MAX_WORD) continue;
                        strcpy(indexList[indexCount].tu,tuThuong);
                        indexList[indexCount].count=0;
                        indexList[indexCount].countWord=0;
                        themDong(&indexList[indexCount],soDong);
                        indexCount++;
                    } else {
                        themDong(&indexList[idx],soDong);
                    }
                }
            }
        }
    }
    fclose(fv);

    qsort(indexList,indexCount,sizeof(MucIndex),soSanh);

    char fileXuat[128];
    snprintf(fileXuat,sizeof(fileXuat),"%s_index.txt",fileNhap);
    FILE *fo = fopen(fileXuat,"w");
    if(!fo) { printf("Khong tao duoc file %s\n",fileXuat); return 1; }

    for(int i=0;i<indexCount;i++) {
        fprintf(fo,"%-15s %d",indexList[i].tu,indexList[i].countWord);
        for(int j=0;j<indexList[i].count;j++)
            fprintf(fo,", %d",indexList[i].soDong[j]);
        fprintf(fo,"\n");
    }

    fclose(fo);
    printf("Da tao index: %s\n", fileXuat);
    return 0;
}
