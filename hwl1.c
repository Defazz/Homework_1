
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
FILE *inFile, *outFile;
char signature[9], CDFH_SIGNATURE[9]="504b0102", *path;
unsigned char n, file_name_len [3], file_name_char[3];
int i, sign_count=0, cmpstr;
long long _file_size;
unsigned short file_name, fnl;

path=argv[1];
if (argc !=2)   {
printf ("filename is failure");
return EXIT_FAILURE;
}
// Создаем текстовый файл "hwl1.txt" и записываем в него содержимое полученного
//из командной строки файла

outFile=fopen(path, "r");
inFile=fopen("hwl1.txt", "w");
while (!feof(outFile))  {
if (fread (&n, sizeof(n), 1, outFile) !=-1);
fprintf(inFile, "%02x", n);
_file_size+=2;
}
fclose(inFile);
fclose(outFile);

inFile=fopen("hwl1.txt", "r");
//Переводим указатель в конец файла hwl1.txt минус 8 байт
   if(fseek(inFile,-8, SEEK_END)!=0)

        printf("Ошибка\n");

    cmpstr=1;
//Производим поиск сигнатуры двигаясь с конца файла в начало
    while (_file_size !=0)  {
    _file_size--;
    if (fgets (signature, 9, inFile)==NULL)
    printf ("Сигнатура не прочитана\n");
    else
      fseek(inFile,-9, SEEK_CUR);
   cmpstr=strcmp (signature, CDFH_SIGNATURE);
//Если сигнатура найдена, находим в структуре ZIP длину имени файла, само имя и выводим его на экран.
       if (cmpstr ==0)    {
        sign_count++;
        fseek(inFile,57, SEEK_CUR);
        fgets (file_name_len,3, inFile);
        fnl = strtol(file_name_len,NULL,16);

fseek(inFile,34, SEEK_CUR);
while (fnl !=0) {
fgets (file_name_char, 3, inFile);
file_name = strtol(file_name_char ,NULL,16);
printf("%c", file_name);
fnl--;
        }
printf("\n");
//Возвращаем указатель в то место, где была найдена последняя сигнатура для дальнейшего поиска
        fseek(inFile,-135, SEEK_CUR);
        }
        }
fclose(inFile);

if ((_file_size==0)&&(sign_count==0))
    printf ("It's not zip-file\n");
    else

     return 0;
}
