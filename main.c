#include <stdio.h>
#include <time.h>
#include <string.h>

struct TarihSaat {
    int yil, ay, gun, saat, dakika, saniye;
};

union Zaman {
    time_t epochTime;
    struct TarihSaat tarihSaat;
};

time_t tarihSaatToEpoch(struct TarihSaat t);

void tarihSaatAl(union Zaman *zaman, char *mesaj) {
    printf("%s\n", mesaj);
    printf("Yil : ");
    scanf("%d", &zaman->tarihSaat.yil);
    printf("Ay (1-12): ");
    scanf("%d", &zaman->tarihSaat.ay);
    printf("Gun (1-31): ");
    scanf("%d", &zaman->tarihSaat.gun);
    printf("Saat (0-23): ");
    scanf("%d", &zaman->tarihSaat.saat);
    printf("Dakika (0-59): ");
    scanf("%d", &zaman->tarihSaat.dakika);
    printf("Saniye (0-59): ");
    scanf("%d", &zaman->tarihSaat.saniye);

    zaman->epochTime = tarihSaatToEpoch(zaman->tarihSaat);
}

time_t tarihSaatToEpoch(struct TarihSaat t) {
    struct tm zaman;
    memset(&zaman, 0, sizeof(zaman));

    zaman.tm_year = t.yil - 1900;
    zaman.tm_mon  = t.ay - 1;
    zaman.tm_mday = t.gun;
    zaman.tm_hour = t.saat;
    zaman.tm_min  = t.dakika;
    zaman.tm_sec  = t.saniye;

    return mktime(&zaman);
}

void zamanFarkiHesapla(time_t epoch1, time_t epoch2) {
    if (epoch1 > epoch2) {
        time_t temp = epoch1;
        epoch1 = epoch2;
        epoch2 = temp;
    }

    double fark = difftime(epoch2, epoch1);

    int yil = fark / (365 * 24 * 3600);
    fark -= yil * (365 * 24 * 3600);

    int ay = fark / (30 * 24 * 3600);
    fark -= ay * (30 * 24 * 3600);

    int gun = fark / (24 * 3600);
    fark -= gun * (24 * 3600);

    int saat = fark / 3600;
    fark -= saat * 3600;

    int dakika = fark / 60;
    fark -= dakika * 60;

    int saniye = fark;

    printf("Iki tarih arasindaki fark: %d yil, %d ay, %d gun, %d saat, %d dakika, %d saniye\n",
           yil, ay, gun, saat, dakika, saniye);
}

void kalanSureHesapla(time_t deadlineEpoch, time_t simdikiEpoch) {
    if (deadlineEpoch < simdikiEpoch) {
        printf("Proje teslim tarihi geçti \n");
        return;
    }

    double fark = difftime(deadlineEpoch, simdikiEpoch);

    int yil = fark / (365 * 24 * 3600);
    fark -= yil * (365 * 24 * 3600);

    int ay = fark / (30 * 24 * 3600);
    fark -= ay * (30 * 24 * 3600);

    int gun = fark / (24 * 3600);
    fark -= gun * (24 * 3600);

    int saat = fark / 3600;
    fark -= saat * 3600;

    int dakika = fark / 60;
    fark -= dakika * 60;

    int saniye = fark;

    printf("Proje teslim tarihine kalan sure: %d yil, %d ay, %d gun, %d saat, %d dakika, %d saniye\n",
           yil, ay, gun, saat, dakika, saniye);
}

int main() {
    union Zaman tarih1, tarih2, teslimTarihi;
    time_t simdikiZaman = time(NULL);

    // 1. ve 2. tarih karşılaştırması
    tarihSaatAl(&tarih1, "1. Tarihi giriniz:");
    tarihSaatAl(&tarih2, "2. Tarihi giriniz:");

    zamanFarkiHesapla(tarih1.epochTime, tarih2.epochTime);

    // Proje teslim tarihi takibi
    tarihSaatAl(&teslimTarihi, "Son teslim tarihini giriniz:");

    kalanSureHesapla(teslimTarihi.epochTime, simdikiZaman);

    return 0;
}
