#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define EN 10
#define BOY 10

void BosTahtaOlustur(char tahta[][BOY],size_t en,size_t boy);
void TahtaYaz(char tahta[][BOY],char isim[],size_t en,size_t boy, char kimin);
int IcerdeMi(int r, int c, size_t en, size_t boy);
void TahtaYerlestir(char tahta[][BOY], size_t en, size_t boy, char kimin);
void RastgeleYerlestir(char tahta[][BOY], size_t en, size_t boy, int uzunluk);
int YerlesimYoluAcikMi(char tahta[][BOY], size_t en, size_t boy, int r, int c, int uzunluk, char yon);
void OyuncuTahtasiYerlestir(char tahta[][BOY], size_t en, size_t boy, int uzunluk,int gemi);
int oyna(char tahta[][BOY], size_t en, size_t boy,int sira,int bittiMi);
int kontrol(char tahta[][BOY], size_t en, size_t boy,int sira,int bittiMi);
void giris();

int main()
{
    giris();
    char oyuncu_tahta[EN][BOY];
    char bilgisayar_tahta[EN][BOY];

    BosTahtaOlustur(oyuncu_tahta,EN,BOY);
    BosTahtaOlustur(bilgisayar_tahta,EN,BOY);

    TahtaYaz(oyuncu_tahta,"Oyuncu Tahtasi",EN,BOY,'o');
    TahtaYerlestir(bilgisayar_tahta,EN,BOY,'b');
    TahtaYerlestir(oyuncu_tahta,EN,BOY,'o');
    int sira=0;
    int bittiMi=0;

    do{
        if(sira==0)
        {
            sira    = oyna(bilgisayar_tahta,EN,BOY,sira,bittiMi);
            bittiMi = kontrol(bilgisayar_tahta,EN,BOY,sira,bittiMi);
        }
        else
        {
            sira    = oyna(oyuncu_tahta,EN,BOY,sira,bittiMi);
            bittiMi = kontrol(oyuncu_tahta,EN,BOY,sira,bittiMi);
        }

    }while(bittiMi==0);

    if(bittiMi == 1)
    {
        printf(" *** TEBRIKLER KAZANDINIZ !! ***");
        printf("\n");
    }
    else
    {
        printf(" *** UZGUNUM BILGISAYAR KAZANDINIZ !! ***");
        printf("\n");
    }

    return 0;
}

void BosTahtaOlustur(char tahta[][BOY],size_t en,size_t boy)
{
    int i,j;
    for (i=0; i<en; i++){
        for(j=0; j<boy; j++){
            tahta[i][j]='~';
        }
    }
}

void TahtaYaz(char tahta[][BOY],char isim[],size_t en,size_t boy, char kimin)
{
    int i,j;

    printf("    *** %s ***\n\n",isim);
    printf("%4s"," ");

    for(i=0; i<en; i++)
    {
        printf("%3d",i+1);
    }
    printf("\n");
    printf("%4s","+");

    for(i=0; i<en; i++)
    {
        printf("%s","---");
    }
    printf("\n");

    for(i=0; i<en; i++)
    {
        printf("%3d|",i+1);
        for(j=0; j<boy; j++)
        {
            if(kimin == 'o')
            {
                printf("%3c",tahta[i][j]);
            }
            else
            {
               if(tahta[i][j] != '~')
                {
                    if(tahta[i][j] == 'X')
                    {
                        printf("%3c",'~');
                    }
                    else
                    {
                        printf("%3c",tahta[i][j]);
                    }
                }
                else
                {
                    printf("%3c",tahta[i][j]);
                }
            }
        }
        printf("\n");
    }
    printf("\n\n");

}

int IcerdeMi(int r, int c, size_t en, size_t boy)
{
    if(r < en && c < boy)
        return 1;
    return 0;
}

void TahtaYerlestir(char tahta[][BOY], size_t en, size_t boy, char kimin)
{
    if ( kimin == 'o')
    {
        int gemiUzunluk;
        int gemi;

        gemiUzunluk = 5;
        gemi=1;
        OyuncuTahtasiYerlestir(tahta, en , boy, gemiUzunluk,gemi);
        gemiUzunluk = 4;
        gemi=2;
        OyuncuTahtasiYerlestir(tahta, en , boy, gemiUzunluk,gemi);
        gemiUzunluk = 3;
        gemi=3;
        OyuncuTahtasiYerlestir(tahta, en , boy, gemiUzunluk,gemi);
        gemiUzunluk = 3;
        gemi=4;
        OyuncuTahtasiYerlestir(tahta, en , boy, gemiUzunluk,gemi);
        gemiUzunluk = 2;
        gemi=5;
        OyuncuTahtasiYerlestir(tahta, en , boy, gemiUzunluk,gemi);
    }
    else
    {
        srand(time(NULL));
        int gemiUzunluk;

        gemiUzunluk = 5;
        RastgeleYerlestir(tahta, en , boy, gemiUzunluk);
        gemiUzunluk = 4;
        RastgeleYerlestir(tahta, en , boy, gemiUzunluk);
        gemiUzunluk = 3;
        RastgeleYerlestir(tahta, en , boy, gemiUzunluk);
        gemiUzunluk = 3;
        RastgeleYerlestir(tahta, en , boy, gemiUzunluk);
        gemiUzunluk = 2;
        RastgeleYerlestir(tahta, en , boy, gemiUzunluk);

    }
}

void RastgeleYerlestir(char tahta[][BOY], size_t en, size_t boy, int uzunluk)
{
    int r,c,i;
    char yon;

    int icerde,acik;
    do
    {
        r = rand()%en;
        c = rand()%boy;
        yon = rand()%2 == 0 ? 'D': 'Y';

        int r_bitis, c_bitis;
        if (yon == 'Y')
        {
            r_bitis = r;
            c_bitis = c+uzunluk;
        }
        else
        {
            r_bitis = r+uzunluk;
            c_bitis = c;
        }

        icerde = IcerdeMi(r_bitis,c_bitis,en,boy);
        acik   = YerlesimYoluAcikMi(tahta, en ,boy, r, c, uzunluk, yon);

    }while(icerde != 1 || acik != 1);

    for (i=0; i<uzunluk; i++)
    {
        if(yon == 'Y')
        {
            tahta[r][c+i] = 'X';
        }
        else
        {
            tahta [r+i][c] = 'X';
        }
    }
}

int YerlesimYoluAcikMi(char tahta[][BOY], size_t en, size_t boy, int r, int c, int uzunluk, char yon)
{
    int i;
    if (yon == 'Y')
    {
        for(i=-1; i<uzunluk+1; i++)
        {
            if(tahta[r][c+i] != '~')
            {
                return 0;
            }

            if(IcerdeMi(r-1,c+i,en,boy))
            {
                if(tahta[r-1][c+i] != '~')
                {
                    return 0;
                }
            }

            if(IcerdeMi(r+1,c+i,en,boy))
            {
                if(tahta[r+1][c+i] != '~')
                {
                    return 0;
                }
            }
        }
    }
    else
    {
        for(i=-1; i<uzunluk+1; i++)
        {
            if(tahta[r+i][c] != '~')
            {
                return 0;
            }

            if(IcerdeMi(r+i,c-1,en,boy))
            {
                if(tahta[r+i][c-1] != '~')
                {
                    return 0;
                }
            }

            if(IcerdeMi(r+i,c+1,en,boy))
            {
                if(tahta[r+i][c+1] != '~')
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void OyuncuTahtasiYerlestir(char tahta[][BOY], size_t en, size_t boy, int uzunluk,int gemi)
{
    int r,c,i;
    char yon;

    int icerde,acik;
    do
    {
        if(gemi==1)
        {
           printf(" \\\\\\ 5 birim uzunluktaki Carrier gemisini Yerlestir /// \n\n");
        }
        else if(gemi==2)
        {
           printf(" \\\\\\ 4 birim uzunluktaki Battleship gemisini Yerlestir /// \n\n");
        }
        else if(gemi==3)
        {
           printf(" \\\\\\ 3 birim uzunluktaki Cruiser gemisini Yerlestir /// \n\n");
        }
        else if(gemi==4)
        {
           printf(" \\\\\\ 3 birim uzunluktaki Submarine gemisini Yerlestir /// \n\n");
        }
        else if(gemi==5)
        {
           printf(" \\\\\\ 2 birim uzunluktaki Destroyer gemisini Yerlestir /// \n\n");
        }

        printf(" Geminin Pozisyonunu Y/D seklinde giriniz= ");
        scanf(" %c",&yon);
        printf(" satir sayisi= ");
        scanf(" %d",&r);
        printf(" sutun sayisi= ");
        scanf(" %d",&c);

        r=r-1;
        c=c-1;

        int r_bitis, c_bitis;
        if (yon == 'Y')
        {
            r_bitis = r;
            c_bitis = c+uzunluk;

            icerde = IcerdeMi(r_bitis,c_bitis,en,boy);
            acik   = YerlesimYoluAcikMi(tahta, en ,boy, r, c, uzunluk, yon);
        }
        else if(yon =='D')
        {
            r_bitis = r+uzunluk;
            c_bitis = c;

            icerde = IcerdeMi(r_bitis,c_bitis,en,boy);
            acik   = YerlesimYoluAcikMi(tahta, en ,boy, r, c, uzunluk, yon);
        }

        else
        {
            printf("\n *** Atama Yapilamadi Lutfen Konumu Dogru Girdiginizden Emin Olun *** \n\n");
            icerde=0;
            continue;
        }

        if(icerde != 1 || acik != 1)
        {
            printf("\n *** Atama Yapilamadi. Lutfen Belirtilen Konumun Musait Oldugundan ve Bilgileri Dogru Girdiginizden Emin Olun ***\n\n");
        }

    }while(icerde != 1 || acik != 1);

    for (i=0; i<uzunluk; i++)
    {
        if(yon == 'Y')
        {
            tahta[r][c+i] = 'X';
        }
        else
        {
            tahta [r+i][c] = 'X';
        }
    }
    printf("\n");
    TahtaYaz(tahta,"Oyuncu Tahtasi",EN,BOY,'o');

    if(gemi==4 || gemi==3 || gemi==2 || gemi==1)
    {
        printf(" *** Atama Basarili ***\n\n");
    }

    if(gemi==5)
    {
        printf(" *** Gemi Atamalari Basariyla Tamamlandi ***\n\n");
    }
}

int oyna(char tahta[][BOY], size_t en, size_t boy,int sira,int bittiMi)
{
    int r,c;
    if(sira==0)
    {
        TahtaYaz(tahta,"bilgisayar Tahtasi",EN,BOY,'b');
        printf(" \\\\\\ Atis Yapmak Istediginiz Konumu Giriniz /// \n\n");
        printf(" satir sayisi= ");
        scanf(" %d",&r);
        printf(" sutun sayisi= ");
        scanf(" %d",&c);
        printf("\n");
        r=r-1;
        c=c-1;

        if(r>9 || c>9)
        {
            printf(" *** Lutfen satir ve sutun icin 1 ile 10 arasinda bir deger girin ***\n");
            return 0;
        }

        if(tahta[r][c] == 'X')
        {
            tahta[r][c]='H';
            TahtaYaz(tahta,"bilgisayar Tahtasi",EN,BOY,'b');
            printf(" *** Tebrikler Atis Basarili (%d,%d) ***\n\n",(r+1),(c+1));
            sleep(3);
            return 0;
        }
        else if(tahta[r][c] == 'H' || tahta[r][c] == 'M')
        {
            printf(" *** Daha Once Atis Yapilan Bir Nokta Secildi Lutfen Tekrar Deneyin (%d,%d) ***\n\n",(r+1),(c+1));
            return 0;
        }
        else
        {
            tahta[r][c]='M';
            TahtaYaz(tahta,"bilgisayar Tahtasi",EN,BOY,'b');
            printf(" *** Uzgunum Atis Basarisiz Sira Bilgisayarda (%d,%d) ***\n\n",(r+1),(c+1));
            sleep(4);
            return 1;
        }
    }
    else
    {
        r = rand()%en;
        c = rand()%boy;
        r=r-1;
        c=c-1;
        if(r==-1)
        {
            r=0;
        }
        if(c==-1)
        {
           c=0;
        }

        if(tahta[r][c] == 'X')
        {
            tahta[r][c]='H';
            TahtaYaz(tahta,"Oyuncu Tahtasi",EN,BOY,'o');
            printf(" *** Uzgunum Bilgisayar Basarili Atis Yapti (%d,%d) ***\n\n",(r+1),(c+1));
            sleep(4);
            return 1;
        }
        else if(tahta[r][c] == 'H' || tahta[r][c] == 'M')
        {
            return 1;
        }
        else
        {
            tahta[r][c]='M';
            TahtaYaz(tahta,"Oyuncu Tahtasi",EN,BOY,'o');
            printf(" *** Bilgisayar Basarisiz Atis Yapti Sira Sizde (%d,%d) ***\n\n",(r+1),(c+1));
            sleep(3);
            return 0;
        }
    }
}

int kontrol(char tahta[][BOY], size_t en, size_t boy,int sira,int bittiMi)
{
    int i,j;

    if(sira==0)
    {
        for(i=0; i<10; i++)
        {
            for(j=0; j<10; j++)
            {
                if(tahta[i][j]=='X')
                {
                    return 0;
                }
            }
        }
        return 1;
    }
    else
    {
        for(i=0; i<10; i++)
        {
            for(j=0; j<10; j++)
            {
                if(tahta[i][j]=='X')
                {
                    return 0;
                }
            }
        }
        return 2;
    }
}
void giris()
{
    printf("\n        *** AMIRAL BATTI OYUNUNA HOSGELDINIZ *** \n\n");
    printf(" Lutfen Oyuna Baslamadan Once Asagidaki Kurallari Okuyunuz\n\n");
    printf(" 1. Iki oyuncununda 10x10 olmak uzere birer tahtasi vardir\n");
    printf(" 2. Oyun baslamadan once iki oyuncuda kendi tahtasina 5 adet farkli boyuttaki gemilerini yerlestirir\n");
    printf(" 3. Gemiler yanlizca yatay(Y) veya dikey(D) olarak yerlestirilebilir(capraz yerlestirilemez)\n");
    printf("    Yerlestirilen geminin ustune veya bir birim cevresine baska bir gemi atamasi yapilamaz\n");
    printf(" 4. Ardindan oyuncular birbirlerinin tahtalarina atis yaparlar\n");
    printf("    Eger atis yapan oyuncu rakip oyuncunun gemisini tutturursa atis yaptigi yer H olarak isaretlenir ve tekrar atis yapar\n");
    printf("    Eger atis yapan oyuncu rakip oyuncunun gemisini tutturamazsa atis yaptigi yer M olarak isaretlenir ve atis sirasi rakibe gecer\n");
    printf(" 5. Rakip tahtadaki gemileri butun parcalarini vuran taraf oyunu kazanir\n\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n\n");

}


