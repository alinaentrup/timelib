/**
*
* Tag des Jahres
* Autor: Alina Entrup
* Erstellt am: 29.03.2022 / 26.04.2022 / 10.05.2022 / 17.05.2022 / 24.05.2022
* 
**/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int tage_pro_monat[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

/*
Die Funktion überprüft, ob ein gegebenes Jahr nach den Regeln des gregorianischen Kalender ein Schaltjahr
ist. Bei Jahreszahlen vor dem Jahr 1582 wird ein Fehler zurückgegeben. 
*/
int is_leapyear(int year){
    if(year<1582) return -1;
    if(year%4==0){
        if(year%100==0){
            if(year%400==0){
                return 1;
            }
            return 0;
        }
        return 1;
    }
    return 0;
}


/*
Die Funktion liest 3 Ganzzahlwerte (Integer) ein, für Tag, Monat und Jahr. Wenn das angegebene Datum
ungültig ist, wird erneut eingelesen, solange bis ein gültiges Datum eingegeben wurde.
*/
void input_date(int *day, int *month, int *year) {
    char datum[10];
    printf(" *** Tag des Jahres *** \n");
    printf("Bitte geben Sie ein Datum ein: ");
    scanf("%10s",datum);
    char *token=strtok(datum,".");
    *day=atoi(token);
    token=strtok(NULL,".");
    *month=atoi(token);
    token=strtok(NULL,".");
    *year=atoi(token);
}

/*
Die Funktion bestimmt für einen gegebenen Monat eines gegebenen Jahres, wie viele Tage der Monat hat. Der
Wert des Monats muss zwischen 1 und 12 liegen. Schaltjahre werden berücksichtigt.
*/
int get_days_for_month(int month, int year) {
    tage_pro_monat[1]=28;
    if((month<1 || month>12) || (year<1582 || year>2400)) return -1;
    if(is_leapyear(year)) tage_pro_monat[1]++;
    return tage_pro_monat[month];
}


/*
Die Funktion überprüft, ob ein eingegebenes Datum gültig ist. Daten vor dem 1.1.1582 sind ungültig, genauso
wie alle Daten nach dem 31.12.2400.
*/
int exists_date(int day, int month, int year) {
    if (year<1582 || year>2400) return 0;
    if(month<1 || month>12) return 0;
    if(tage_pro_monat[month-1]<day || day<1) return 0;
    return 1;
}


/*
Die Funktion berechnet für ein gegebenes Datum des gregorianischen Kalenders bestehend aus Tag, Monat
und Jahr die Nummer des Tages, gezählt von Jahresbeginn (1. Januar) an. Schaltjahre werden bei der
Berechnung berücksichtigt. Ist das übergebene Datum ungültig, beträgt der Rückgabewert -1.
*/
int day_of_the_year(int day, int month, int year) {
    if(!exists_date(day,month,year)) return -1;
    int erg=0;
    if(is_leapyear(year)) {
        tage_pro_monat[1]++;
    }
    if(month==1) {
        return day;
    }
    
    for (int i = 0; i <= month-1; i++) {
        erg+=get_days_for_month(i,year);
    }  
    if(is_leapyear(year)) tage_pro_monat[1]--;
    erg+=day;
    return erg;
}

/*
Berechnet den Wochentag eines Datums.
*/
int day_of_the_week(int day, int month, int year){
    return (day+=month<3?year--:year-2,23*month/9+day+4+year/4-year/100+year/400)%7;
}


/*
Berechnet die Wochennummer des Datums.
*/
int week_of_the_year(int day, int month, int year){
    int erg=(day_of_the_year(day,month,year)/7)+1;
    //if(day_of_the_week(day,month,year)<day_of_the_week(31,12,year-1)) erg++;
    return erg;
}

int main()
{
    int year,month,day=0;
    input_date(&day,&month,&year);
    printf("Das Datum ist der %d. Tag des Jahres %d \n",day_of_the_year(day,month,year),year);
    printf("und der %d. Tag der %d. Woche",day_of_the_week(day,month,year),week_of_the_year(day,month,year));
    
    
    return 0;
}
