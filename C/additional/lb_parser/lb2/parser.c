#include <stdio.h>
#include <stdint.h>
#include <string.h>

int sig_cmp(const unsigned char sig[8]){	//Сравнение каждой ячеки массива с сигнатурой PNG
	if(sig[0] != 137) return 1;
	if(sig[1] != 80) return 1;
	if(sig[2] != 78) return 1;
	if(sig[3] != 71) return 1;
	if(sig[4] != 13) return 1;
	if(sig[5] != 10) return 1;
	if(sig[6] != 26) return 1;
	if(sig[7] != 10) return 1;
	return 0;
}

int name_cmp(const unsigned char name[4], const char* check){		// Соответствие названия чанка требуемым
	char tmp[5];					// Переменная для конвертации массива фиксированной длины в строку
	for(int i = 0; i < 4; i++)
		tmp[i] = name[i];			// Непосредственный посимвольный перенос из name в tmp
	tmp[4] = 0;						// Добавление нуль-символа в конец в массива, дабы обозначить, что tmp - строка
	return strcmp(tmp, check);		// Стадартная функция, сравнивает две строки. При равенстве возвращает ноль.
}


typedef struct{						// Структура для хранения требуемой информации о чанке
	unsigned long int pos;			// Положение чанка в файле
	uint32_t len;					// Размер чанка
	unsigned char name[4];			// Название чанка
	uint32_t crc;					// Значение CRC
}chunk_info;


int bytesToInt(unsigned char bytes[4]){		//Преобразование череды байтов в целое число
	return 	(uint32_t)bytes[0] << 24|		//Байты складываются друг с другом так, что кажый последующий сдвигается влево на 8
			(uint32_t)bytes[1] << 16|
			(uint32_t)bytes[2] << 8 |
			(uint32_t)bytes[3];
}


void read_chunk(FILE *fp, chunk_info *chunk){	// Чтение очередного чанка из файла
	unsigned char bytes[4];						// Доополнительный массив для получения длины и CRC кода

	chunk->pos = ftell(fp);						// Получение позиции чанка
	fread(bytes, 4, 1, fp);						// Чтение байтов, составляющих размер чанка
	chunk->len = bytesToInt(bytes);				// Преобразование считанных байтов в целое число

	fread(chunk->name, 1, 4, fp);				// Чтение названия чанка
	fseek(fp, chunk->len, SEEK_CUR);			// Перемещение в конец чанка (т.к. то что в них содержится нас не интересует)

	fread(bytes, 4, 1, fp);						// Чтение байтов, составляющих код CRC
	chunk->crc = bytesToInt(bytes);				// Проеобразование считанных байтов в целое число
}


void print_chunk_info(chunk_info *chunk){
	printf("%c%c%c%c is found on %ld\t|Length: %u\t|CRC: 0x%x\n",	chunk->name[0],		/*форматный вывод*/
									chunk->name[1],									/*Название не является строкой, значит выводим посимвольно*/
									chunk->name[2],
									chunk->name[3],
									chunk->pos,										/*ftell возвращает long int, значит используем идентификатор %ld*/
									chunk->len,										/*Длина является беззнаковой переменной, значит используем идентификатор %u*/
									chunk->crc);									/*Требуется вывести CRC шестнадцатиричным числом, значит используем идентификатор %x*/
}


int main(int argc, char **argv){	// Программа получает файл, который требуется пропарсить, как аргумент
	if (argc != 2){					// Проверка, введен ли аргумент
		fprintf(stderr, "Wrong input. Use: program_name <file>\n");
		return 0;
	}

	FILE *fp = fopen(argv[1], "rb"); // Попытка открыть файл, как бинарный

	if (!fp){						// Если fp == NULL, то завершаем программу с ошибкой
		fprintf(stderr, "There's no permission or file doesn't exists\n");
		return 0;
	}

	unsigned char sig[8];			// Создаем массив для сигнатуры
	fread(sig, 1, 8, fp);			// Считываем данные из файла в массив sig
	if(sig_cmp(sig)){				// Проверка, верная ли сигнатура
		fprintf(stderr, "Signature is wrong\n");		// Вывод сообщения об ошибке
		fclose(fp);										// Закрываем файл
		return 0;
	}
	else
		fprintf(stdout, "Signature is OK\n");

	chunk_info cur_chunk;						// Объект структуры для хранения информации о текущем чанке
	read_chunk(fp, &cur_chunk);					// Считываем первый, после сигнатуры, чанк
	if(name_cmp(cur_chunk.name, "IHDR")){		// Если он не IHDR, то заврешаем программу с ошибкой
		fprintf(stderr, "IHDR wasn't found\n");	// Сообщение об ошибке
		fclose(fp);								// Закрываем файл
		return 0;
	}
	fprintf(stdout, "IHDR OK\n");

	char bad_iend;			// Переменная которая определит, чтение завершено встречей IEND или концом файла
	char idat_cnt = 0;		// Количество найденных чанков IDAT
	while(!feof(fp) && (bad_iend = name_cmp(cur_chunk.name, "IEND"))){	// Цикл в котором один за другим считываются чанки из файла
		read_chunk(fp, &cur_chunk);										// Читаем очередной чанк
		if(!name_cmp(cur_chunk.name, "IDAT")){							// Проверяем, содержит ли он в себе изображение, то есть IDAT 
			print_chunk_info(&cur_chunk);								// Если да, то выводим информацию о нем
			idat_cnt++;													// Увеличиваем количество найденных чанков изображения
		}
	}
	if(!idat_cnt){														// Если файл не содержал чанков IDAT, то
		fprintf(stderr, "IDAT wasn't found\n");							// Выводим сообщение об ошибке
		fclose(fp);														// Закрываем файл
		return 0;
	}

	if(bad_iend){														// Проверяем был ли достигнут чанк IEND, если нет, то
		fprintf(stderr, "Bad IEND chunk\n");							// Выводим сообщение об ошибке
		fclose(fp);														// Закрываем файл
		return 0;
	}
	fprintf(stdout, "IEND is found\n");									// При отстутствии ошибок, сообщаем пользователю об успешной проверке файла
	fprintf(stdout, "File parsed successfully\n");

	fclose(fp);															// Закрываем файл
	return 0;															// Работа программы завершена
}
