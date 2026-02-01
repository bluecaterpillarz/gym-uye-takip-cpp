#include <iostream>
#include <cctype>
#include <windows.h>
#include <fstream>
#include <locale>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

#ifdef _WIN32
    #include <windows.h>
#endif

void setupTurkishSupport() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #else
        setlocale(LC_ALL, "tr_TR.UTF-8");
    #endif
}

string dosya_adi, tc_no, adi, soyadi, dogum_tarihi, durum, ideal_durum, tarih, boy_str, kilo_str, yag_orani_str, yag_orani_durumu;
int yas_global=0;
float boy, kilo, yag_orani, vki;
char cinsiyet;
string baslik[]={"tarih","yas","boy","kilo","vki","vki_degerlendirme","ideal_durum","yag_orani","yag_orani_durumu"};

string bugunTarih() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    stringstream ss;
    ss << ltm->tm_year + 1900 << "-"<< setfill('0') << setw(2) << ltm->tm_mon + 1 << "-"<< setfill('0') << setw(2) << ltm->tm_mday;

    return ss.str();
}//2026-01-15 gibi bir tarih dondurecek
string bugunTarihTR() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday << "."<< setfill('0') << setw(2) << ltm->tm_mon + 1 << "."<< ltm->tm_year + 1900;

    return ss.str();
} //15.01.2026 gibi bir tarih dondurecek.

bool dosya_kontrol(string dosyaAdi){
    ifstream dosya(dosyaAdi);
    if(dosya.is_open()){
        return true;
    }
     return false;
}

string vki_sonuc(float vki_1){
    if (vki_1<18.5){
        durum="zayif";
    }else if(vki_1<24.9){
        durum="normal kilolu";
    }else if(vki_1<=29.9){
        durum="fazla kilolu";
   }else if(vki_1<=34.9){
       durum="1. dereceden obez";
   }else if(vki_1<=39.9){
       durum="2.dereceden obez";
   } else{
       durum="3.dereceden obez";
   }
   return durum;
}

string ideal_vki(float vki2, int yas2){
    if(yas2<19){
        ideal_durum="Cocuklarin ideal vucut kitle indeksi doktor tarafindan degerlendirilmelidir.";
    }else if(yas2>=19 && yas2<=24){
        ideal_durum="İdeal vki 19-24 araliginda olmalidir. Sizin vki degeriniz "+to_string(vki2);
        if(vki2>=19 && vki2<=24){
            ideal_durum+=" bu araliga denk gelmektedir";
        }else {
            ideal_durum+=" bu araliga denk gelmemektedir.";
        }
    }else if(yas2>=25 && yas2<=34){
        ideal_durum="İdeal vki 20-25 araliginda olmalidir. Sizin vki degeriniz "+to_string(vki2);
        if(vki2>=20 && vki2<=25){
            ideal_durum+=" bu araliga denk gelmektedir";
        }else {
            ideal_durum+=" bu araliga denk gelmemektedir.";
        }
    }else if(yas2>=35 && yas2<=44){
        ideal_durum="İdeal vki 21-26 araliginda olmalidir. Sizin vki degeriniz "+to_string(vki2);
        if(vki2>=21 && vki2<=26){
            ideal_durum+=" bu araliga denk gelmektedir";
        }else {
            ideal_durum+=" bu araliga denk gelmemektedir.";
        }
    }else if(yas2>=45 && yas2<=54){
        ideal_durum="İdeal vki 22-27 araliginda olmalidir. Sizin vki degeriniz "+to_string(vki2);
        if(vki2>=22 && vki2<=27){
            ideal_durum+=" bu araliga denk gelmektedir";
        }else {
            ideal_durum+=" bu araliga denk gelmemektedir.";
        }
    }else if(yas2>=55 && yas2<=64){
        ideal_durum="İdeal vki 23-28 araliginda olmalidir. Sizin vki degeriniz "+to_string(vki2);
        if(vki2>=23 && vki2<=28){
            ideal_durum+=" bu araliga denk gelmektedir";
        }else {
            ideal_durum+=" bu araliga denk gelmemektedir.";
        }
    }else {
        ideal_durum="İdeal vki 24-29 araliginda olmalidir. Sizin vki degeriniz "+to_string(vki2);
        if(vki2>=24 && vki2<=29){
            ideal_durum+=" bu araliga denk gelmektedir";
        }else {
            ideal_durum+=" bu araliga denk gelmemektedir.";
        }
    }
    return ideal_durum;
}

void yag_orani_durum(char cinsiyet2, float yag_orani2){
    if (cinsiyet2=='E'){
        if (yag_orani2<2){
            yag_orani_durumu="cok dusuk";
        }else if (yag_orani2>=2 && yag_orani2<=5){
            yag_orani_durumu="en temel duzeyde";
        }else if (yag_orani2>5 && yag_orani2<=13){
            yag_orani_durumu="atlet duzeyinde";
        }else if (yag_orani2>13 && yag_orani2<=17){
            yag_orani_durumu="fitness duzeyinde";
        }else if (yag_orani2>17 && yag_orani2<=24){
            yag_orani_durumu="kabul edilebilir duzeyde";
        }else{
            yag_orani_durumu="yag orani fazla";
        }
    }else{
        if (yag_orani2<10){
            yag_orani_durumu="cok dusuk";
        }else if (yag_orani2>=10 && yag_orani2<=13){
            yag_orani_durumu="en temel duzeyde";
        }else if (yag_orani2>13 && yag_orani2<=20){
            yag_orani_durumu="atlet duzeyinde";
        }else if (yag_orani2>20 && yag_orani2<=24){
            yag_orani_durumu="fitness duzeyinde";
        }else if (yag_orani2>24 && yag_orani2<=31){
            yag_orani_durumu="kabul edilebilir duzeyde";
        }else{
            yag_orani_durumu="yag orani fazla";
        }

    }
}

void yeni_bilgi(){
    bool kontrol;
    do {
    kontrol = false;
    cout << "Boy- lütfen m cinsinden giriniz, örneğin 1.75: ";
    cin >> boy_str;

    // Nokta kontrolü
    size_t nokta_poz = boy_str.find('.');

    if(nokta_poz == string::npos) {
        cout << "Nokta bulunamadı! Örnek: 1.75\n";
        kontrol = true;
        continue;
    }

    if(nokta_poz == 0 || nokta_poz == boy_str.length() - 1) {
        cout << "Hatalı format! Örnek: 1.75\n";
        kontrol = true;
        continue;
    }

    // Float'a çevir
    try {
        boy = stof(boy_str);
    } catch(...) {
        cout << "Geçersiz sayı!\n";
        kontrol = true;
        continue;
    }

    // Aralık kontrolü
    if(boy <= 0 || boy > 3.0) {
        cout << "Boy 0 ile 3 metre arasında olmalı!\n";
        kontrol = true;
    }

    } while(kontrol);
    do{
        kontrol=false;
        cout<<"Kilo- lütfen kg cinsinden giriniz: ";
        cin>>kilo_str;
        try {
        kilo = stof(kilo_str);
    } catch(...) {
        cout << "Geçersiz sayı!\n";
        kontrol = true;
        continue;
    }
    }while(kontrol);

    vki=kilo/(boy*boy);
    durum=vki_sonuc(vki);
    do{
        kontrol=false;
        cout<<"Yag oranini giriniz:";
        cin>>yag_orani_str;
        try {
        yag_orani = stof(yag_orani_str);
    } catch(...) {
        cout << "Geçersiz sayı!\n";
        kontrol = true;
        continue;
    }
    }while(kontrol);

}

void ilk_bilgi(){
    do {
        cout << "Ad: ";
        cin >> adi;
        if(adi.empty()) {
            cout << "Ad boş olamaz! Tekrar deneyin.\n";
        }
    } while(adi.empty());

    do {
        cout << "Soyad: ";
        cin >> soyadi;
        if(soyadi.empty()) {
            cout << "Soyad boş olamaz! Tekrar deneyin.\n";
        }
    } while(soyadi.empty());

    bool tarih_gecerli=false;
    do {
        cout << "Doğum tarihi (GG.AA.YYYY): ";
        cin >> dogum_tarihi;

        if(dogum_tarihi.length() == 10 && dogum_tarihi[2] == '.' && dogum_tarihi[5] == '.') {
            tarih_gecerli = true;
        } else {
            cout << "Hatalı format! Örnek: 15.03.1990\n";
        }
    } while(!tarih_gecerli);
    do {
        cout << "Cinsiyet (E/K): ";
        cin >> cinsiyet;
        cinsiyet = toupper(cinsiyet);
        if(cinsiyet != 'E' && cinsiyet != 'K') {
            cout << "Sadece E veya K girebilirsiniz!\n";
        }
    } while(cinsiyet != 'E' && cinsiyet != 'K');
    yeni_bilgi();
}

int yas_hesaplama(string dogum_tarihi1,string tarih1){
    vector<string>dizi1,dizi2;
    string veri1, veri2;
    stringstream ss1(dogum_tarihi1);
    while(getline(ss1,veri1,'.')){
        dizi1.push_back(veri1);
    }
    stringstream ss2(tarih1);
     while(getline(ss2,veri2,'.')){
        dizi2.push_back(veri2);
    }
    int dogum_gun = stoi(dizi1[0]);
    int dogum_ay = stoi(dizi1[1]);
    int dogum_yil = stoi(dizi1[2]);

    int bugun_gun = stoi(dizi2[0]);
    int bugun_ay = stoi(dizi2[1]);
    int bugun_yil = stoi(dizi2[2]);

    int yas = bugun_yil - dogum_yil;

    if(bugun_ay < dogum_ay || (bugun_ay == dogum_ay && bugun_gun < dogum_gun)){
        yas--;
    }
    return yas;
}


int main()
{
    setupTurkishSupport();
    tarih=bugunTarihTR();

    while (true){
        cout<<"TC Kimlik numarasini giriniz- eger programdan çikmak istiyorsaniz 0'a basiniz: ";
        cin>>tc_no;
        if (tc_no=="0"){
            break;
        }
        string dosya_tc=tc_no+".csv";
        if (dosya_kontrol(dosya_tc)){
            //dosya var, genisletiliyor.
            yeni_bilgi();
            ofstream dosya_Yaz(dosya_tc, ios::app);
            if(dosya_Yaz.is_open()){
                string satir;
                ifstream dosya_Oku(dosya_tc);
                if(dosya_Oku.is_open()){
                    while(getline(dosya_Oku, satir)) {
                        if(satir.find("# Doğum Tarihi: ") != string::npos) {
                            dogum_tarihi = satir.substr(17);
                        }
                        if(satir.find("# Cinsiyeti: ") != string::npos) {
                            cinsiyet = satir.substr(13)[0];
                        }
                    }
                dosya_Oku.close();
                }

                yas_global=yas_hesaplama(dogum_tarihi,tarih);
                ideal_durum=ideal_vki(vki,yas_global);
                yag_orani_durum(cinsiyet, yag_orani);
                dosya_Yaz<<tarih<<","<<yas_global<<","<<boy<<","<<kilo<<","<<vki<<","<<durum<<","<<ideal_durum<<","<<yag_orani<<","<<yag_orani_durumu<<endl;
                cout<<"Tarih: "<<tarih<<"\n"<<"Guncel yas: "<<yas_global<<"\n"<<"Boy: "<<boy<<"\n"<<"Kilo: "<<kilo<<"\n"<<"Vki:"<<vki<<"\n"<<"Vki degerlendirme: "<<durum<<"\n"<<"Ideali: "<<ideal_durum<<"\n"<<"Yag orani: "<<yag_orani<<"\n"<<"Yag orani degerlendirme: "<<yag_orani_durumu<<endl;
                dosya_Yaz.close();
            }else{
                cerr<<"HATA: Dosyaya yazilamadi!\n";
                return 1;
            }
        }else{
            //dosya yok, yeni olusturuluyor.
            ofstream dosya_Yaz(dosya_tc, ios::app);
            if(dosya_Yaz.is_open()){
                    ilk_bilgi();
                    dosya_Yaz<<"# Ad: "<<adi<<"\n"<<"# Soyad: "<<soyadi<<"\n"<<"# Doğum Tarihi: "<<dogum_tarihi<<"\n"<<"# TC Kimlik No: "<<tc_no<<"\n"<<"# Cinsiyeti: "<<cinsiyet<<"\n\n";
                for(int i=0; i<9; i++){
                    dosya_Yaz<<baslik[i];
                    if(i<8){
                        dosya_Yaz<<",";
                    }
                }
                yas_global=yas_hesaplama(dogum_tarihi,tarih);
                ideal_durum=ideal_vki(vki,yas_global);
                yag_orani_durum(cinsiyet,yag_orani);
                dosya_Yaz<<endl<<tarih<<","<<yas_global<<","<<boy<<","<<kilo<<","<<vki<<","<<durum<<","<<ideal_durum<<","<<yag_orani<<","<<yag_orani_durumu<<endl;
                cout<<"Tarih: "<<tarih<<"\n"<<"Guncel yas: "<<yas_global<<"\n"<<"Boy: "<<boy<<"\n"<<"Kilo: "<<kilo<<"\n"<<"Vki:"<<vki<<"\n"<<"Vki degerlendirme: "<<durum<<"\n"<<"Ideali: "<<ideal_durum<<"\n"<<"Yag orani: "<<yag_orani<<"\n"<<"Yag orani degerlendirme: "<<yag_orani_durumu<<endl;
                dosya_Yaz.close();
            }else{
                cerr<<"HATA: Dosya olusturulamadi!\n";
                return 1;
            }
        }
    }
    return 0;
}
