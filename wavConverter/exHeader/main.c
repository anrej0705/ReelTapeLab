//Exheader - программа предназначена для извлечения заголовка из WAV файла для дальнейшей работы с ним - модификацией и записью в новый файл
//Формат заголовка должен быть следующим RIFFeeeeWAVEfmt kkkkgghhrrrryyyyooqqppppzzzz
// RIFF - метка формата файла, DWORD 4 байта
// eeee - размер всего файла в байтах DWORD 4 байта
// WAVE - обозначение что файл звуковой DWORD 4 байта
// fmt  - обозначение что дальше будут детали о файле DWORD 4 байта, последний символ неотображается - 0x20 WORD 2 байта
// kkkk - для формата ИКМ(PCM) DWORD 4 байта
// gg - здесь указан кодек, обычно ИКМ(PCM) WORD 2 байта
// hh - здесь указано количество канало WORD 2 байта
// rrrr - частота дискретизации в герцах DWORD 4 байта
// yyyy - скорость передачи данных в байтах в секунду DWORD 4 байта
// oo - количество байт для одной выборки включая все каналы WORD 2 байта
// qq - глубина выборки в битах WORD 2 байта
// data - метка обозначающая что дальше будут данные DWORD 4 байта
// zzzz - размер файла минус размер заголовка DWORD 4 байта
//После извлечения заголовка программа генерирует файл convertParams.ini в котором содержатся
// помеченное тегами FSRC-FSND исходное имя файла
// помеченное тегами FBOD-FBND имя контейнера wav данных
// помеченное тегами FHDT-FHND имя файла с заголовком, записанным этой программой
// помеченное тегами FTGT-FTND имя конечного файла
// флаг состояния конвертации - 0(не конвертирован), 1(конвертирован)
// частоту дискретизации файла в герцах
// количество каналов в файле
// глубину выборки
// количество выборок в одном канале
//Каждый запуск программа проверяет наличие файла convertParams.ini и если
//не находит то создает новый. Найдя этот файл, она открывает его и в первую
//очердь проверяет флаг конвертации. Если 0 - программа завершает работу
//если 1 то программа читает остальные данные, включая имя файла заголовка
//и создает файл согласно записанному имени после тега FHDT. Далее программа
//из прочитанных данных формирует минимальный заголовок и записывает его в файл
#include<locale.h>																																//Библиотека локализацй, нужна для русского языка в консоли
#include<stdbool.h>																																//Библиотека для работы с двоичными числам, C99
#include<stdint.h>																																//Бибилотека для работы с нестандартными числами uint8_t, uint16_t, uint32_t
#include<stdio.h>																																//Библиотека для работы с консолью, вывод в консоль и считывание с нее
#include<conio.h>																																//Бибилотека для работы с вводом
#include<stdlib.h>																																//Бибилотека типов переменных
#include<string.h>																																//Библиотеке символьных переменных
#include "debug.h"																																//Библиотека отладочных сообщений
#define StartMsg					"\nv0.2.7\n"																								//Сообщение для вывода в консоль, 1 часть
#define StartMsgTwo					"Данная программа является компонентом и сама по себе не имеет смысла\n\n"									//Сообщение для вывода в консоль, 2 часть
#define FileSizeMsg					"Размер файла, полный: %d Байт\n"																			//Сообщение для вывода размера файла
#define FileSizeWoutHeaderMsg		"Размер файла без учета заголовка: %d Байт\n"																//Сообщение для вывода размера файла без заголовка
#define SampleRateMsg				"Частота дискретизации: %d Гц\n"																			//Сообщение для вывода частоты дискретизации
#define ByteRateMsg					"Скорость передачи данных: %d Байт/с\n"																		//Сообщение для вывода скорости передачи данных в байтах
#define BitDepthMsg					"Глубина выборки: %d Бит\n"																					//Сообщение для вывода глубины выборки
#define ChannelsMsg					"Количество каналов: %d"																					//Сообщение для вывода количества каналов
#define BytesInSampleMsg			"Количество байт в одной выборке со всех каналов: %d Байт\n"												//Сообщение для вывода количество байт в выборке со всех каналов сразу
#define CodecTypeMsg				"Тип кодирования звука:"																					//Сообщение для вывода типа кодирования звука в файле
const uint8_t wordFilenameShift=4;																												//Смещение в байтах до самого параметра
const uint8_t wordConvertShift=7;																												//Смещение в байтах до самого параметра
const uint8_t wordSampleRateShift=10;																											//Смещение в байтах до самого параметра
const uint8_t wordChannelsShift=8;																												//Смещение в байтах до самого параметра
const uint8_t wordBitsPerSampleShift=13;																										//Смещение в байтах до самого параметра
const uint8_t wordSamplesValueShift=16;																											//Смещение в байтах до самого параметра
const uint16_t pcmFormat=0x0001;
const uint32_t RIFFsignature=0x52494646;																										//метка RIFF, образец
const uint32_t WAVEsignature=0x57415645;																										//метка WAVE, образец
const uint32_t fmtSignature=0x666D7420;																											//метка fmt , образец
const uint32_t dataSignature=0x64617461;																										//метка data, образец
const uint32_t dataFormatLength=0x00000010;
char headerNameSuffix[11]="_header.dat";																										//суффикс к имени преобразуемого файла
char headerBodySuffix[9]="_body.dat";																											//суффикс к имени преобразуемого файла
char headerConvSuffix[9]="_conv.wav";																											//суффикс к имени преобразуемого файла
char fileMassive[256];																															//массив в который читается содержимое файла convertParams.ini
char fileNameRAW[128];																															//массив, в котором хранится имя файла включая путь
char fileNameSrc[64];																															//массив с именем исходного файла
char fileNameHdrDat[64];																														//массив с именем заголовочного файла
char fileNameBodDat[64];																														//массив с именем заголовочного файла
char fileNameTgtDat[64];																														//массив с именем заголовочного файла
char fileName[64];																																//массив с именем файла
char *wordFilenameSource="FSRC";																												//Название для параметра имени файла
char *wordFilenameBody="FBOD";		   																											//Название для параметра имени файла
char *wordFilename="FNAM";																														//Название для параметра имени файла
char *wordFilenameTarget="FTGT";																												//Название для параметра имени файла
char *wordSrcFilenameEnd=">FSND";																												//Название для параметра имени файла
char *wordNameFilenameEnd=">FNND";																												//Название для параметра имени файла
char *wordBodyFilenameEnd=">FBND";																												//Название для параметра имени файла
char *wordTargFilenameEnd=">FTND";																												//Название для параметра имени файла
char *wordConvert="Convert";																													//Название для флага состояния конвертации
char *wordSampleRate="SampleRate";																												//Название для параметра частоты дискретизации
char *wordChannels="Channels";																													//Название для параметра количества каналов
char *wordBitsPerSample="BitsPerSample";																										//Название для параметра обозначающего количество бит в выборке
char *WordCountOfSamples="SamplesInChannel";																									//Название для параметра обозначающего количество выборок
char *cursorSymbol;																																//Параметр в который будет писаться позиция курсора с которого начинается искомое слово
uint8_t fileLength;																																//Общая переменная для хранения информации о длине файла
uint32_t cursorPosit;																															//Позиция курсора до начала числа параметра
uint32_t wordFsrcPos;																															//Позиция тега FSRC
uint32_t wordFnamePos;																															//Позиция тега FNAM
uint32_t wordConvertPos;																														//Сюда пишется позиция, на которую нужно выставить курсор для чтения параметра FSetWasConverted 
uint32_t wordSampleRatePos;																														//Сюда пишется позиция, на которую нужно выставить курсор для чтения параметра FSetSampleRate
uint32_t wordChannelsPos;																														//Сюда пишется позиция, на которую нужно выставить курсор для чтения параметра FSetChannels
uint32_t wordBitsPerSamplePos;																													//Сюда пишется позиция, на которую нужно выставить курсор для чтения параметра FSetBitDepth
uint32_t wordSamplesValuePos;																													//сюда будет писаться количество выборок в 1 канале файла
bool DebugMode=1;																																//режим отлакди, 1 - вкл, 0 - выкл
bool analyzeState;																																//состояние функции чтения, 1 - все хорошо, 0 - где-то случилась ошибка
bool convertState;																																//состояние функции преобразованиа и записи в структуру, 1 - все хорошо, 0 - где-то случилась ошибка
bool cruzo;																																		//состояние считываемое с файла convertParams.ini
bool ahsoka;																																	//состояние функции проверки правильности данных в структуре, 1 - все хорошо, 0 - данные в структуре не совпадают с образцами, закончилась фантазия на имена
bool gabella;																																	//если 1 - информация в заголовок успешно записана, если 0 - произошло что-то такое что не дало записать
bool Egor;																																		//состояние функции чтения из файла convertParams.ini
bool doubledoor;																																//указатель состояния записи в файл, если 1 то все хорошо, если 0 то файл не был записан
FILE* FSet;																																		//Указатель на файл с параметрами заголовка
FILE* FRd;																																		//Указатель на файл с которого все будет читаться
FILE* FWr;																																		//Указатель на файл в который будет идти запись, пока в коде не применен
const int HeaderSize=44;																														//параметр длины заголовка в байтах(от 0 байта до начала самих данных WAVE), заголовок имеет всегда одну и ту же длину
int headerAddrs[14]={0,4,8,12,16,20,22,24,28,32,34,36,40,44};																					//список адресов в заголовке с которых нужно читать параметры файла
int headerWordSizeOf[13]={sizeof(uint32_t),sizeof(uint32_t),sizeof(uint32_t),sizeof(uint32_t),													//список длинн слов, читаемых из заголовка(список связан с headerAddrs и headerWordInvert)
						sizeof(uint32_t),sizeof(uint16_t),sizeof(uint16_t),sizeof(uint32_t),													//здесь я словил шизу
						sizeof(uint32_t),sizeof(uint16_t),sizeof(uint16_t),sizeof(uint32_t),
						sizeof(uint32_t)};																										//список который содержит длину каждого параметра в байтх
int headerWordInvert[13]={1,0,1,1,0,0,0,0,0,0,0,1,0};																							//список для функции, изменяющий порядок байтов - с конца или с начала
int headerDebugPrintParameters[13]={0,0,0,0,0,1,1,0,0,1,1,0};																					//список типов сообщений вывода для функции вывода отладочных параметров
uint8_t FileHeader[44];																															//сюда переписывается заголовок
uint8_t ByteBuffer[4];																															//здесь хранится параметр заголовка чтобы каждый раз не обращаться к основному массиву
uint8_t headerReader(void);																														//функция чтения заголовка в структуру
uint8_t massiveSwap(bool swapState);																											//фукнция изменения порядка следования байтов
uint8_t sByteConverter(uint32_t wordToConvert);																									//функция понижения разрядности
uint8_t GetFileName(char* nameOfFile);																											//функция получения имени файла(на самом деле она ничего не понижает)
uint16_t dByteConverter(uint32_t wordToConvert);																								//функция понижения разрядности(с 32 до 16 бит)
uint32_t qByteConverter(uint32_t wordToConvert);																								//функция понижения разрядности(с 32 до 8 бит)
uint32_t byteConverter(int startOffset, int endOffset, int ByteLenght, bool invertState);														//функция для преобразования нужной части содержимого  массива в одно слово с разной длинной
uint32_t structFiller(int structShift, uint32_t paramToWrite);																					//функция записи в структуру
uint32_t writeBuffer(int startOffset, int endOffset, uint32_t paramToWrite, int wordSize, bool SwapByte);										//функция записи измененной структуры в массив, подготовка к записи в файл
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore);				//функция генерации имени файла из полученного исходника
void storeStructToFile();																														//функция для записи параметров заголовка в отдельный файл в виде структуры
void checkStatus(uint8_t statusCode);																											//функция для проверки состояния выхода из других функций, для обнаружения ошибки
void structAnalyzer(void);																														//функция для проверки структуры и вывода ее содержимого
void structModifier(void);																														//функция для модификации структуры
void clearByteBuffer(void);																														//очистка буфера после работы
void clearHeaderBuffer(void);																													//очистка буфера заголовка после операции чтения файла
void writeDebugHeaderBuffer(void);																												//запись буфер содержимое которого выводится в отладочных целях
void BufferReader(void);																														//функция-затычка для отладочных целей
void printHelpMsg(void);																														//функция-справка в случае пустого вызова или вызова по командам -h.-H,-help,-HELP
void generateHead(void);
int WriteSettingsFile(void);																													//функция записывающая параметры преобразования
int ReadSettingsFile(void);																														//функция считывающая параметры преобразования
struct WaveHeader																																//структура, в которую будет писаться информация с заголовка файла
{																																				//начало структуры заголовка
	uint32_t RiffSign;																															//метка RIFF
	uint32_t chunkSizeBytes;																													//размер файла с заголовком
	uint32_t WaveSign;																															//метка WAVE
	uint32_t fmtSign;																															//метка fmt
	uint32_t DataFormatLenght;																													//длина формата данных
	uint16_t compressionCode;																													//код сжатия
	uint16_t soundChannels;																														//количество каналов
	uint32_t sampleRate;																														//частота выборок
	uint32_t byteRate;																															//скорость передачи данных, байт
	uint16_t BytesInSample;																														//количество байт в одной выборке со всех каналов
	uint16_t BitDepth;																															//глубина дискретизации
	uint32_t dataSign;																															//метка data
	uint32_t chunkSizeWoutHeader;																												//размер файла без заголовка
};																																				//конец структуры заголовка
struct FilSettings																																//структура, в которую пишутся параметры из файла convertParams.ini
{																																				//начало структуры
	int FSetWasConverted;																														//флаг который показывает - был ли конвертирован файл чтоб сделать вывод - писать заголовок или нет
	int FSetBitDepth;																															//глубина дискретизации
	int FSetChannels;																															//количество каналов
	long FSetSampleRate;																														//частота выборок
	uint32_t FSetSamplesValue;																													//количество выборок
};																																				//конец структуры
struct FilSettings FilSet;																														//упрощение имени структуры
struct WaveHeader Wave;																															//упрощение имени структуры
int main(int argc, char* argv[])																												//описание main и метода передачи аргументов из командной строки
{																																				//начало тела main
	memset(fileMassive,0x00,sizeof(fileMassive));																								//чистим массив fileMassive
	memset(fileNameRAW,0x00,sizeof(fileNameRAW));																								//чистим массив fileNameRAWs
	memset(fileNameSrc,0x00,sizeof(fileNameSrc));																								//чистим массив fileNameSrc
	memset(fileName,0x00,sizeof(fileName));																										//чистим массив fileName
	memset(FileHeader,0x00,sizeof(FileHeader));																									//чистим массив FileHeader
	memset(ByteBuffer,0x00,sizeof(ByteBuffer));																									//чистим массив ByteBuffer
	setlocale(LC_ALL, "Rus");																													//русский язык
	if(DebugMode==1)																															//проверка, включен ли режим отладки
	{pringDebugMsg(36,0);}																														//если включен то вывод сообщения
	pringDebugMsg(33,0);																														//уведомление о начале работы проги
	pringDebugMsg(85,argc);																														//сообщение и количестве аргументов, полученных из командной строки
	for(uint8_t i=0;i<64;i++)
	{
		if(!(strcmp(argv[i], "-makehead")))
		{
			pringDebugMsg(101,0);
			printf(" Аргумент -makehead найден\n");
			ReadSettingsFile();
			cursorSymbol=strstr(fileMassive, wordConvert);
			structModifier();
			generateHead();
			exit(0);
		}
	}
	if(argc<2)																																	//начало проверки количества аргументов...
	{																																			//...если аргументов меньше двух
		printf("Не указано имя файла\n");																										//выводим сообщение о том что не указаны аргументы
		printf("Вызов справки -h, -H, -help, -HELP\n\n");																						//и предлагаем вызвать справку
		pringDebugMsg(84,0);																													//инициируем выход из программы с кодом 1(файл не найден)
	}																																			//выход из тела проверки значения
	if(argc>4)																																	//проверяем количество аргументов - их должно быть 2...4
	{																																			//если аргументов больше 2, то
		printf("Слишком много аргументов\n");																									//сообщаем об этом
		pringDebugMsg(84,0);																													//и выходим из программы
	}																																			//выход из тела проверки
	printf(StartMsg);																															//вывод сообщения приветствия
	printf(StartMsgTwo);																														//вывод сообщения, вторая часть
	if(!(strcmp(argv[1], "-h")&&strcmp(argv[1], "-H")&&strcmp(argv[1], "-HELP")&&strcmp(argv[1], "-help")))										//проверяем наличие запроса справки
	{																																			//начало тела
		printHelpMsg();																															//вызываем функцию вывода справки
	}																																			//конец тела
	printf("Второй аргумент отсутсвует, создается файл с именем по умолчанию\n\n");																//костыль
	FRd=fopen(argv[1], "rb");																													//открытие файла указанного в первом аргументе
	fileLength=GetFileName(argv[1]);																											//получаем имя файла
	transformFileName(fileName,fileLength,headerNameSuffix,sizeof(headerNameSuffix),fileNameHdrDat);											//генерируем имя файла с заголовком из исходника
	transformFileName(fileName,fileLength,headerBodySuffix,sizeof(headerBodySuffix),fileNameBodDat);											//генерируем имя файла с телом из исходника
	transformFileName(fileName,fileLength,headerConvSuffix,sizeof(headerConvSuffix),fileNameTgtDat);											//генерируем имя файла с телом из исходника
	if(!FRd)																																	//проверка существования файла НЕ(FRd)=0?
	{																																			//тогда...
		pringDebugMsg(89,0);																													//костыль
		pringDebugMsg(91,0);																													//сообщение об отстутствии файла
		exit(1);																																//выход из программы с кодом 1(файл не найден)
	}																																			//конец тела проверки
	fseek(FRd, 0, SEEK_SET);																													//установка курсора на адрес(успешность данной операции пока не проверяется никак)
	pringDebugMsg(26,0);																														//высираем отладочное сообщение о начале чтения заголовка
	fread(FileHeader, 1, HeaderSize, FRd);																										//выполняем чтение в буффер FileHeader, читаем первые 44 байта(указаны в HeaderSize)
	writeDebugHeaderBuffer();																													//только для режима отладки, запись в отдельный буфер из которого будет выводиться на экран отладки
	pringDebugMsg(25,0);																														//вывод содержимого буфера FileHeader
	pringDebugMsg(29,0);																														//вывод сообщения о том, что начато чтения содержимого этого буфера
	headerReader();																																//вызов функции чтения заголовка
	fclose(FRd);																																//закрытие файла для чтения
	checkStatus(1);																																//проверка кода выхода функции чтения заголовка
	structAnalyzer();																															//вызов функции проверки структуры на правильность
	ReadSettingsFile();																															//вызов функции чтения из файла параметров
	WriteSettingsFile();																														//вызов функции записи параметров в файл
	pringDebugMsg(82,0);																														//вывод сообщения завершения работы программы
	//pringDebugMsg(38,0);					//КОСТЫЛЬ ДЛЯ АВТОМАТИЗАЦИИ																			//программа сообщает от том что щас будет ждать нажатия клавиши Enter
	//getchar();																																//ничего не делать, ждать нажатия клавиши Enter
}																																				//конец тела main
void generateHead(void)
{
	pringDebugMsg(101,0);
	printf(" Генерирую структуру...\n");
	memset(FileHeader,0x00,sizeof(FileHeader));
	writeBuffer(headerAddrs[0], headerAddrs[1], RIFFsignature, headerWordSizeOf[0], headerWordInvert[0]);
	writeBuffer(headerAddrs[1], headerAddrs[2], Wave.chunkSizeBytes, headerWordSizeOf[1], headerWordInvert[1]);
	writeBuffer(headerAddrs[2], headerAddrs[3], WAVEsignature, headerWordSizeOf[2], headerWordInvert[2]);
	writeBuffer(headerAddrs[3], headerAddrs[4], fmtSignature, headerWordSizeOf[3], headerWordInvert[3]);
	writeBuffer(headerAddrs[4], headerAddrs[5], dataFormatLength, headerWordSizeOf[4], headerWordInvert[4]);
	writeBuffer(headerAddrs[5], headerAddrs[6], pcmFormat, headerWordSizeOf[5], headerWordInvert[5]);
	writeBuffer(headerAddrs[6], headerAddrs[7], Wave.soundChannels, headerWordSizeOf[6], headerWordInvert[6]);
	writeBuffer(headerAddrs[7], headerAddrs[8], Wave.sampleRate, headerWordSizeOf[7], headerWordInvert[7]);
	writeBuffer(headerAddrs[8], headerAddrs[9], Wave.byteRate, headerWordSizeOf[8], headerWordInvert[8]);
	writeBuffer(headerAddrs[9], headerAddrs[10], Wave.BytesInSample, headerWordSizeOf[9], headerWordInvert[9]);
	writeBuffer(headerAddrs[10], headerAddrs[11], Wave.BitDepth, headerWordSizeOf[10], headerWordInvert[10]);
	writeBuffer(headerAddrs[11], headerAddrs[12], dataSignature, headerWordSizeOf[11], headerWordInvert[11]);
	writeBuffer(headerAddrs[12], headerAddrs[13], Wave.chunkSizeWoutHeader, headerWordSizeOf[12], headerWordInvert[12]);
	BufferReader();
	pringDebugMsg(81,0);
	FWr=fopen(fileNameHdrDat, "wb");
	if(FWr != NULL)
	{
		printf(" Успех\n");
	}
	else
	{
		printf(" Не удалось создать файл %s\n",fileNameHdrDat);
		exit(0);
	}
	fseek(FWr, 0, SEEK_SET);
	fwrite(FileHeader, sizeof(uint8_t), sizeof(FileHeader), FWr);
	fclose(FWr);
}
inline void printHelpMsg(void)																													//функция вывода справочной информации в консоль
{																																				//начало тела
	printf(StartMsg);																															//выводим версию программы
	printf("Использование: Exheader.exe source_file output_file(выборочно)\n\n");																//справка, начало
	printf("- При отсутствии второго аргумента, файл с заголовком создается в\n  директории запуска Exheader.exe\n");							//справка, продолжение
	printf("- Например, вызов Exheader.exe C:\\foreign8.wav создаст по месту\n  вызова заголовочный файл foreign8_header.dat\n");				//справка, продолжение
	printf("  А вызов Exheader C:\\foreign8.wav C:\\aaa\\foreign8dat.wav создаст по пути C:\\aaa файл foreign8dat.wav.dat\n\n");				//справка, продолжение
	printf("- Конечный файл всегда будет с расширением .dat и содержать в себе\n  сформированный из convertParams.ini заголовок\n");			//справка, продолжение
	exit(1);																																	//выход с кодом 1
}																																				//конец тела справочной функции
inline void writeDebugHeaderBuffer(void)																										//ф-кция копирования заголовка в отдельный буфер для вывода отладочных сообщений
{																																				//начало тела ф-кции
	for(int j=0;j<43;j++)																														//начало цикла копирования массивов
	{																																			//начало тела цикла
		FileHeaderMSG[j]=FileHeader[j];																											//посимвольное копирование с сохранением адреса символа относительно начала массивов
	}																																			//конец тела цикла
}																																				//конец тела функции
uint8_t GetFileName(char* nameOfFile) 																											//функция получения имени файла из пути
{																																				//начало тела
	uint8_t symbolCountInFileName;																												//переменная хранящая длину имени файла, включая расширение
	strcpy(fileNameRAW,nameOfFile);																												//дублирование строки в массив
	uint8_t nameLenght = strlen(nameOfFile);																									//подсчет количества введеных символов
	char *lastSymbolEntry = strrchr(fileNameRAW, 92);																							//нахождение последнего вхождения символа "\"
	uint8_t entryPos = lastSymbolEntry-fileNameRAW+1;																							//указатель на индекс последнего вхождения символа
	if(lastSymbolEntry==NULL)																													//если функция strrchr возвращает NULL...
	{																																			//...то начинаем обработку имени без отделения записи пути к файлу
		pringDebugMsg(89,0);																													//пишем в консоль
		pringDebugMsg(92,0);																													//пишем сообщение о возврате NULL функцией strrchr
		pringDebugMsg(89,0);																													//пишем в консоль
		printf("Длина имени файла = %d\n", nameLenght);																							//пишем сообщение о длине имени файла включая путь до него
		pringDebugMsg(89,0);																													//пишем в консоль
		printf("Имя открываемого файла: ");																										//пишем имя открываемого файла
		for(int i=0;i<nameLenght;i++)																											//начало цикла вывода имени файла
		{																																		//начало тела цикла
			printf("%c",fileNameRAW[i]);																										//посимвольный вывод имени файла из массива
		}																																		//конец тела цикла
		printf("\n");																															//печатам перенос каретки
		pringDebugMsg(89,0);																													//пишем в консоль
		pringDebugMsg(93, entryPos);																											//выводим позицию последнего найденного нужного символа
		pringDebugMsg(89,0);																													//пишем в консоль
		printf("Последнее вхождение символа: %s\n", lastSymbolEntry);																			//пишем последнее вхождение символа
		symbolCountInFileName = strlen(fileNameRAW);																							//подсчитываем длину имени файла, в символах
		pringDebugMsg(89,0);																													//пишем в консоль
		pringDebugMsg(94,symbolCountInFileName);																								//пишем полученное в результате подсчета число
		pringDebugMsg(89,0);																													//пишем в консоль
		printf("Полученное имя файла: ");																										//выводим полученное имя файла
		for(int i=0;i<symbolCountInFileName;i++)																								//начало цикла вывода имени
		{																																		//начало тела цикла
			fileNameSrc[i]=fileNameRAW[i];																										//дублирование оригинального имени файла в массив
			fileName[i]=fileNameRAW[i];																											//переносим имя в другой массив посимвольно
			printf("%c",fileName[i]);																											//и заодно посимвольно выводим переносимое имя в консоль
		}																																		//конец тела цикла
		printf("\n");																															//переносим каретку
		return symbolCountInFileName;																											//возвращаем длину имени файла
	}																																			//конец тела(истина)
	else																																		//иначе отделяем путь до файла от имени файла
	{																																			//начало тела
		pringDebugMsg(89,0);																													//пишем в консоль
		printf("Длина имени, включая путь к файлу = %d\n", nameLenght);																			//пишем длину имени файла
		pringDebugMsg(89,0);																													//пишем в консоль
		printf("Имя открываемого файла: ");																										//пишем имя открываемого файла
		for(int i=0;i<nameLenght;i++)																											//начало цикла вывода имени файла
		{																																		//начало тела цикла
			printf("%c",fileNameRAW[i]);																										//посимвольный вывод имени файла
		}																																		//конец тела цикла
		printf("\n");																															//перенос каретки
		pringDebugMsg(89,0);																													//пишем в консоль
		pringDebugMsg(93, entryPos);																											//пишем позицию символа, который ищем в строке
		pringDebugMsg(89,0);																													//пишем в консоль
		printf("Последнее вхождение символа: %s\n", lastSymbolEntry);																			//строку с той позиции где был найден символь
		symbolCountInFileName = nameLenght-entryPos;																							//считаем количество символов в имени файла
		pringDebugMsg(89,0);																													//пишем в консоль
		pringDebugMsg(94,symbolCountInFileName);																								//пишем полученое в результате вычислений число
		pringDebugMsg(89,0);																													//пишем в консоль
		printf("Полученное имя файла: ");																										//пишем полученное имя файла(уже само имя)
		for(int i=0;i<symbolCountInFileName;i++)																								//начинаем вывод имени файла
		{																																		//начало тела цикла
			fileNameSrc[i]=fileNameRAW[i+entryPos];																								//дублирование оригинального имени файла в массив
			fileName[i]=fileNameRAW[i+entryPos];																								//посимвольно выводим имя файла со смещением в начало имени
			printf("%c",fileName[i]);																											//и сразу же печатаем, также по символу
		}																																		//конец тела
		printf("\n");																															//перенос каретки
		return symbolCountInFileName;																											//возвращаем длину имени файла в место вызова функции
	}																																			//конец тела(ложь)
}																																				//конец тела функции
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore)				//функция генерирования имени файла
{																																				//начало тела функции
	char tempMas[64];																															//инициализируем временный буфер
	memset(tempMas,0x00,sizeof(tempMas));																										//и чистим его
	uint8_t filenameWithoutExtension=sourceLenght-4;																							//инициализация переменной длины имени файла без расширения
	uint8_t generatedFileNameWithSuffix;																										//инициализация переменной длины сгенерированного имени файла
	pringDebugMsg(95,0);																														//пишем в консоль
	pringDebugMsg(96,0);																														//пишем объявление о начале работы функции
	for(int i=0;i<filenameWithoutExtension+suffixLength;i++)																					//начало цикла генерации имени файла
	{																																			//начало тела цикла
		if(i<filenameWithoutExtension)																											//начало переноса имени файла
		{																																		//начало тела
			tempMas[i]=sourceFileName[i];																										//посимвольный перенос имени файла
		}																																		//конец тела
		if(i>=filenameWithoutExtension)																											//начало записи суффикса к имени файла
		{																																		//начало тела
			tempMas[i]=suffixToAttach[i-filenameWithoutExtension];																				//посимвольная запись суффикса к имени файла
		}																																		//конец тела
	}																																			//конец тела цикла
	generatedFileNameWithSuffix = filenameWithoutExtension+suffixLength;																		//формирование длины имени файла вместе с суффиксом
	if(strlen(tempMas)==generatedFileNameWithSuffix)																							//сравниваем полученное имя и расчетную длину файла
	{																																			//начало тела цикла
		pringDebugMsg(95,0);																													//пишем в консоль
		pringDebugMsg(98,0);																													//пишем проверку
	}																																			//конец тела цикла
	else																																		//в случае если длины не совпадают
	{																																			//то пишем в консоль сообщение об ошибке
		pringDebugMsg(15,0);																													//и выходим из программы
	}																																			//конец тела цикла
	pringDebugMsg(95,0);																														//пишем в консоль
	printf("Полученное имя файла: ");																											//пишем сгенерированное имя файла
	for(int i=0;i<generatedFileNameWithSuffix;i++)																								//начало цикла переноса имени файла из временного массива
	{																																			//начало тела цикла
		fileName[i]=tempMas[i];																													//посимвольный перенос имени файла
		arrToStore[i]=tempMas[i];																												//дублируем в массив по указателю для защиты от случайного изменения в ходе работы программы т.к прога где-то багается непонятно где
		printf("%c",arrToStore[i]);																												//и сразу же вывод в консоль
	}																																			//конец тела цикла
	printf("\n");																																//перенос каретки
	pringDebugMsg(95,0);																														//пишем в консоль
	pringDebugMsg(94,generatedFileNameWithSuffix);																								//пишем длину сгенерированного имени
	pringDebugMsg(95,0);																														//пишем в консоль
	pringDebugMsg(97,0);																														//уведомляем что имя файла сохранено в глобальном массиве
}																																				//конец тела функции
uint8_t headerReader(void)																														//костыльная функция 
{																																				//начало тела ф-кции
	uint32_t LongByteWord;																														//объявляем временную 4 байтную переменную
	int hA=0,hB=0,hC=0,hD=0;																													//костыли
	struct WaveHeader Wave;																														//объявление названия структуры в этой функции(зачем?)
	for(int i=0;i<13;i++)																														//начало цикла записи заголовка в структуру
	{																																			//начало тела цикла
		pringDebugMsg(8,0);																														//печатаем разделитель в консоль, для красоты
		pringDebugMsg(7, hB);																													//показываем степень заполненности структуры
		LongByteWord=byteConverter(headerAddrs[hA], headerAddrs[hA+1], headerWordSizeOf[hC], headerWordInvert[hD]);								//вызываем функцию конвертации формата данных, все параметры для этого берем из массивов в начале файла
		checkStatus(0);																															//проверяем флаги-сигнализаторы ошибки
		pringDebugMsg(headerDebugPrintParameters[hB], LongByteWord);																			//пишем отладочное сообщение, в котором указывается название параметра заголовка
		structFiller(hB, LongByteWord);																											//пишем в структуру сконверченное значение
		clearByteBuffer();																														//чистким буфер после окончания работы с ним
		LongByteWord=0;																															//чистим переменную в которую читаем содержимое массива(зачем? переменная уничтожается после выхода из функции)
		hA++;																																	//костыль
		hB++;																																	//костыль
		hC++;																																	//костыль
		hD++;																																	//костыль
	}																																			//конец тела цикла
	pringDebugMsg(8,0);																															//пишем разделитель в консоль, опять таки для красоты
	analyzeState=1;																																//записываем флаг состояния функции(костыль-затычка чтоб прога работала)
	return analyzeState;																														//выкидываем, так на всякий случай, это же значение
}																																				//конец тела функции
uint32_t byteConverter(int startOffset, int endOffset, int ByteLenght, bool invertState)														//функции перекидывания форматов данных из 32 в 8,16,32 разрядные
{																																				//начало тела функции
	uint32_t quadByte;																															//объявляем 4 байтовую временную переменную
	uint16_t doubleByte;																														//объявляем двухбайтовую временную переменную
	uint8_t singleByte;																															//объявляем однобайтовую временную переменную
	int i=0;																																	//объявляем указатель адреса массивов
	int startMarker=startOffset;																												//объявляем и приравниваем полученному параметру указатель начала адреса считывания
	int endMarker=endOffset;																													//объявляем и приравниваем полученному параметру указалель конца адреса считывания
	while(startMarker<endMarker)																												//начало цикла записи временного буфера
	{																																			//начало тела цикла
		ByteBuffer[i]=FileHeader[startMarker];																									//побайтово переписываем в буфер содержимое, находящееся на указанном адресе
		pringDebugMsg(32,ByteBuffer[i]);																										//сообщаем в консоль о проделываемой работе
		i++;																																	//инкреминируем адрес буфера
		startMarker++;																															//инкреминируем адрес массива с которого идет запись
	}																																			//конец тела цикла
	i=0;																																		//чистим переменную(зачем? она более не нужна)
	switch(ByteLenght)																															//начинаем процесс подготовки параметра к выдаче
	{																																			//начало тела switch
		case 0:																																	//в случае если параметр не существует
			pringDebugMsg(30,0);																												//пишем в консоль уведомление об этом
			convertState=0;																														//пишем флаг ошибки
			break;																																//выходим из цикла
		case 1:																																	//в случае если параметр 1 байтный
			pringDebugMsg(31,0);																												//пишем сообщение в консоль об этом
			singleByte=FileHeader[startMarker];																									//записываем параметр в переменную для выдачи
			convertState=1;																														//выставляем флаг успешной операции
			return singleByte;																													//возвращаем переменную на место вызова функции
			break;																																//выходим из цикла
		case 2:																																	//в случае если переменная 2 байтная
			massiveSwap(invertState);																											//вызываем функцию перевертывания переменной и передаем ей параметр с информацией о необходимости переворота
			doubleByte=ByteBuffer[0];																											//пишем младший байт
			doubleByte=doubleByte|ByteBuffer[1]<<8;																								//пишем старший байт
			pringDebugMsg(28,doubleByte);																										//показываем в консоли эту переменную
			convertState=1;																														//выставляем флаг успешной операции
			return doubleByte;																													//возвращаем переменную на место вызова функции
			break;																																//выходим из цикла
		case 4:																																	//в случае если переменная 4 байтная
			massiveSwap(invertState);																											//вызываем функцию переворачивания переменной и передаем ей параметр с информацией о необходимости переворота
			quadByte=ByteBuffer[0];																												//пишем младший байт
			quadByte=quadByte|ByteBuffer[1]<<8;																									//пишем байт постарше
			quadByte=quadByte|ByteBuffer[2]<<16;																								//пишем байт постарше
			quadByte=quadByte|ByteBuffer[3]<<24;																								//пишем старший байт
			pringDebugMsg(27,quadByte);																											//в консоли говорим об этом и показываем результат
			convertState=1;																														//выставляем флаг успешной операции
			return quadByte;																													//возвращаем переменную на место вызова
			break;																																//выходим из цикла
	}																																			//конец тела цикла
	return convertState;																														//возвращаем флаг состояния
}																																				//конец функции
uint8_t massiveSwap(bool swapState)																												//изначально чтение делается наоборот, поэтому под "Перестановка байтов не требуется" подразумевается
{																																				//возврат их нормальный порядок, то есть не наоборот
	uint32_t tempByte;																															//объявляем временную переменную
	uint8_t tempBuffer[4];																														//объявляем временный буфер для этого
	memset(tempBuffer,0x00,sizeof(tempBuffer));																									//и сразу чистим его от вероятного мусора
	if(swapState==1)																															//переворачивать нннада?
	{																																			//если нннада, то...
		pringDebugMsg(34,0);																													//...сообщаем об этом в консоль
		tempBuffer[0]=ByteBuffer[3];																											//начинаем переворачивать
		tempBuffer[1]=ByteBuffer[2];																											//пишем адресуя позиции созданного буфера с начала...
		tempBuffer[2]=ByteBuffer[1];																											//...и общего временного буфера с конца
		tempBuffer[3]=ByteBuffer[0];																											//...затем...
		ByteBuffer[0]=tempBuffer[0];																											//...перекидываем все эти байты адресуя оба буфера с начала
		ByteBuffer[1]=tempBuffer[1];																											//...
		ByteBuffer[2]=tempBuffer[2];																											//...
		ByteBuffer[3]=tempBuffer[3];																											//...
	}																																			//конец переворота
	else																																		//если не нннада, то...
	{pringDebugMsg(35,0);}																														//...пишем в консоль что не нннада и выходим из функции
}																																				//конец тела функции
void checkStatus(uint8_t statusCode)																											//костыльная функция
{																																				//начало тела функции
	pringDebugMsg(74, statusCode);																												//сообщаем об этом в консоль и показываем код проверки
	switch(statusCode)																															//начало проверки
	{																																			//начало тела switch
		case 0:																																	//в случае если указан код 0(состояние конвертации)
			if(convertState!=0)																													//проверка наличия флага ошибки конвертации
			{pringDebugMsg(10,0);}																												//в случе успеха пишем в консоль об этом
			else																																//иначе...
			{pringDebugMsg(20,convertState);pringDebugMsg(15,0);}																				//...показываем содержимое флага
			pringDebugMsg(20,convertState);																										//и выходим программы с кодом 0(ошибка)
			break;																																//выход из цикла
		case 1:																																	//в случае если указан код 1(состояние конвертации)
			if(analyzeState!=0)																													//проверяем состояние заполнения структуры
			{pringDebugMsg(11,0);}																												//в случае успеха пишем об этом
			else																																//иначе...
			{pringDebugMsg(21,analyzeState);pringDebugMsg(16,0);}																				//...показываем содержимое флага
			pringDebugMsg(21,analyzeState);																										//и сообщаем об ошибке
			break;																																//выходим из цикла
		case 2:																																	//в случае если указан код 2(состояние структуры заголовка)
			if(ahsoka!=0)																														//проверяем состояние флага
			{pringDebugMsg(12,0);}																												//в случае если структура заголовка правильная, говорим об этом в консоль
			else																																//иначе...
			{pringDebugMsg(22,ahsoka);pringDebugMsg(17,0);}																						//пишем в консоль уведомление о битой структуре
			pringDebugMsg(22,ahsoka);																											//и показываем состояние флага
			break;																																//выходим из функции
		case 3:																																	//в случае если указан код 3(модификация заголовка)
			if(gabella!=0)																														//если модификация была успешна
			{pringDebugMsg(13,0);}																												//пишем об этом в консоль
			else																																//иначе...
			{pringDebugMsg(23,gabella);pringDebugMsg(18,0);}																					//...пишем в консоль ошибку операции модификации заголовка
			pringDebugMsg(23,gabella);																											//показываем содержимое флага
			break;																																//выходим из функции
		case 4:																																	//в случае если получен код 4
			if(doubledoor!=0)																													//проверяем успешность записи заголовка
			{pringDebugMsg(14,0);}																												//пишем об этом в консоль
			else																																//иначе...
			{pringDebugMsg(24,doubledoor);pringDebugMsg(19,0);}																					//...пишем об ошибки в консоли
			pringDebugMsg(24,doubledoor);																										//и показываем содержимое флага
			break;																																//выходим из функции
		case 5:																																	//в случае если получен код 5
			if(Egor!=0)																															//проверяем успех прочитанных параметров
			{pringDebugMsg(64,0);}																												//в случае если прочитано успешно, пишем в консоль
			else																																//иначе...
			{pringDebugMsg(66,Egor);pringDebugMsg(65,0);}																						//пишем сообщение от ошибки
			pringDebugMsg(66,Egor);																												//и показываем состояние флага
			break;																																//выходим из функции
		case 6:																																	//в случае если получен код 6
			if(cruzo!=0)																														//проверяем успех редактирования структуры
			{pringDebugMsg(72,0);}																												//если все хорошо то пишем в консоль
			else																																//иначе...
			{pringDebugMsg(71,cruzo);pringDebugMsg(73,0);}																						//...уведомляем в консоли об ошибке
			pringDebugMsg(71,cruzo);																											//и показываем состояние переменной
			break;																																//выходим из функции
	}																																			//конец тела цикла
}																																				//конец тела функции
uint32_t structFiller(int structShift, uint32_t paramToWrite)																					//частичная проверка правильности структуры, только по меткам
{																																				//начало функции
	uint32_t qWordToConvert;																													//создаем временную 2 байтную переменную
	uint16_t dWordToConvert;																													//создаем временную 4 байтную переменную
	switch(structShift)																															//начало цикла switch
	{																																			//начало тела цикла
		case 0:																																	//в случае если выбрана запись метки RIFF
			Wave.RiffSign=qByteConverter(paramToWrite);																							//получаем метку с помощью конвертации из исходного массива
			pringDebugMsg(3,0);																													//пишем в консоль уведомление о записи в структуру
			if(Wave.RiffSign==RIFFsignature)																									//сравниваем с эталоном
			{pringDebugMsg(41, structShift);}																									//в случае если полученная метка совпадает с эталоном пишем об этом консоль
			else																																//иначе...
			{pringDebugMsg(42, structShift);}																									//говорим об ошибке
			break;																																//выходим из цикла
		case 1:																																	//в случае если выбрана запись метки размера файла
			Wave.chunkSizeBytes=qByteConverter(paramToWrite);																					//конвертируем в 4 байтный формат
			pringDebugMsg(3,structShift);																										//пишем в консоль уведомление о записи в структуру																									
			pringDebugMsg(41, structShift);																										//сообщаем об успехе в консоль(пока что проверка не осуществляется)
			break;																																//выходим из цикла
		case 2:																																	//в случае если выбрана запись метки WAVE
			Wave.WaveSign=qByteConverter(paramToWrite);																							//конвертируем
			pringDebugMsg(3,structShift);																										//пишем в консоль уведомление о записи в структуру
			if(Wave.WaveSign==WAVEsignature)																									//сравниваем с эталоном
			{pringDebugMsg(41, structShift);}																									//сообщаем об успехе в консоль(пока что проверка не осуществляется)
			else																																//иначе...
			{pringDebugMsg(42, structShift);}																									//сообщаем об ошибке
			break;																																//выход из цикла
		case 3:																																	//в случае если выбрана запись метки fmt
			Wave.fmtSign=qByteConverter(paramToWrite);																							//конвертируем																							
			pringDebugMsg(3,structShift);																										//пишем в консоль уведомление о записи в структуру
			if(Wave.fmtSign==fmtSignature)																										//сравниваем с эталоном
			{pringDebugMsg(41, structShift);}																									//сообщаем об успехе в консоль(пока что проверка не осуществляется)
			else																																//иначе...
			{pringDebugMsg(42, structShift);}																									//пишем об ошибке
			break;																																//выходим из цикла
		case 4:																																	//в случае если выбрана запись формата данных
			Wave.DataFormatLenght=qByteConverter(paramToWrite);																					//конвертируем
			pringDebugMsg(3,structShift);																										//пишем в консоль уведомление о записи в структуру
			pringDebugMsg(41, structShift);																										//сообщаем об успехе в консоль(пока что проверка не осуществляется)
			break;																																//выходим из цикла
		case 5:																																	//в случае если выбрана запись кода сжатия
			Wave.compressionCode=dByteConverter(paramToWrite);																					//конвертируем
			pringDebugMsg(3,structShift);																										//пишем в консоль уведомление о записи в структуру
			pringDebugMsg(41, structShift);																										//сообщаем об успехе в консоль(пока что проверка не осуществляется)
			break;																																//выходим из цикла
		case 6:																																	//в случае если выбрана запись количества каналов
			Wave.soundChannels=dByteConverter(paramToWrite);																					//конвертируем
			pringDebugMsg(3,structShift);																										//пишем в консоль уведомление о записи в структуру
			pringDebugMsg(41, structShift);																										//сообщаем об успехе в консоль(пока что проверка не осуществляется)
			break;																																//выходим из цикла
		case 7:																																	//в случае если выбрана запись частоты дискретизации
			Wave.sampleRate=qByteConverter(paramToWrite);																						//конвертируем
			pringDebugMsg(3,structShift);																										//пишем в консоль уведомление о записи в структуру
			pringDebugMsg(41, structShift);																										//сообщаем об успехе в консоль(пока что проверка не осуществляется)	
			break;																																//выходим из цикла
		case 8:																																	//в случае если выбрана запись битрейта
			Wave.byteRate=qByteConverter(paramToWrite);																							//конвертируем
			pringDebugMsg(3,structShift);																										//пишем в консоль уведомление о записи в структуру
			pringDebugMsg(41, structShift);																										//сообщаем об успехе в консоль(пока что проверка не осуществляется)
			break;																																//выходим из цикла
		case 9:																																	//в случае если выбрана запись емкости семпла в байтах
			Wave.BytesInSample=dByteConverter(paramToWrite);																					//конвертируем
			pringDebugMsg(3,structShift);																										//пишем в консоль уведомление о записи в структуру
			pringDebugMsg(41, structShift); 																									//сообщаем об успехе в консоль(пока что проверка не осуществляется)
			break;																																//выходим из цикла
		case 10:																																//в случае если выбрана запись глубины выборк
			Wave.BitDepth=dByteConverter(paramToWrite);																							//конвертируем
			pringDebugMsg(3,structShift);																										//пишем в консоль уведомление о записи в структуру
			pringDebugMsg(41, structShift);																										//сообщаем об успехе в консоль(пока что проверка не осуществляется)
			break;																																//выходим из цикла
		case 11:																																//в случае если выбрана запись метки data
			Wave.dataSign=qByteConverter(paramToWrite);																							//конвертируем
			pringDebugMsg(3,structShift);																										//пишем в консоль уведомление о записи в структуру
			if(Wave.dataSign==dataSignature)																									//сравниваем с эталоном
			{pringDebugMsg(41, structShift);}																									//сообщаем об успехе в консоль(пока что проверка не осуществляется)
			else																																//иначе...
			{pringDebugMsg(42, structShift);}																									//пишем сообщение об ошибке
			break;																																//выходим из цикла
		case 12:																																//в случае если выбрана запись размера контейнера с семплами
			Wave.chunkSizeWoutHeader=qByteConverter(paramToWrite);																				//конвертируем
			pringDebugMsg(3,structShift);																										//пишем в консоль уведомление о записи в структуру
			pringDebugMsg(41, structShift);																										//сообщаем об успехе в консоль(пока что проверка не осуществляется)
			break;																																//выходим из цикла
	}																																			//конец цикла
}																																				//конец тела функции
uint32_t qByteConverter(uint32_t wordToConvert)																									//конвертер разрядности 32->32 бит
{																																				//начало тела конвертер
	pringDebugMsg(4,0);																															//пишем в уведомление что конвертация не требуется
	return wordToConvert;																														//возвращаем значение
}																																				//конец тела функции
uint16_t dByteConverter(uint32_t wordToConvert)																									//конвертер разрядности 32->16 бит
{																																				//начало тела функции
	uint16_t doubleByteWord;																													//инициализация временной переменной
	//doubleByteWord=wordToConvert<<16;																											//костыль
	doubleByteWord=wordToConvert;																												//записываем в переменную переданный аргумент
	pringDebugMsg(5,0);																															//пишем об этом в консоль
	return doubleByteWord;																														//возвращаем значение на место вызова
}																																				//конец тела функции
uint8_t sByteConverter(uint32_t wordToConvert)																									//конвертер разрядности 32->8 бит
{																																				//начало тела функции
	uint8_t singleByteWord;																														//инициализируем переменную
	//singleByteWord=wordToConvert<<24;																											//костыль?
	singleByteWord=wordToConvert;																												//записываем аргумент в эту переменную
	pringDebugMsg(6,0);																															//пишем в консоль об этом
	return singleByteWord;																														//возвращаем значение на место вызова
}																																				//конец тела функции
void structAnalyzer(void)																														//частичная проверка структуры, только по меткам, ВСЁ В КОСТЫЛЯХ
{																																				//начало функции
	int chechedSteps=0;																															//костыль
	int headerDifference;																														//длина заголовка
	headerDifference=Wave.chunkSizeBytes-Wave.chunkSizeWoutHeader;																				//вычисляем длину заголовка
	pringDebugMsg(9,0);																															//пишем в консоль
	if(Wave.RiffSign==RIFFsignature)																											//сраниваем с эталоном метку RIFF
	{																																			//начало тела
		chechedSteps++;																															//приращиваем показатель проверенных элементов на 1
		pringDebugMsg(39,0);																													//пишем в чат
	}																																			//конец тела
	else																																		//иначе...
	{pringDebugMsg(40,0);}																														//пишем об ошибке
	if(Wave.WaveSign==WAVEsignature)																											//сравниваем метку WAVE
	{																																			//начало тела
		chechedSteps++;																															//инкреминируем значение счетчика прохода
		pringDebugMsg(43,0);																													//пишем в консоль
	}																																			//конец тела
	else																																		//иначе...
	{pringDebugMsg(40,0);}																														//...пишем сообщение об ошибке
	if(Wave.fmtSign==fmtSignature)																												//сравниваем метки fmt
	{																																			//начало тела
		chechedSteps++;																															//инкреминируем значение счетчика прохода
		pringDebugMsg(44,0);																													//пишем в консоль
	}																																			//конец тела
	else																																		//иначе...
	{pringDebugMsg(40,0);}																														//...пишем сообщение об ошибке
	if(Wave.dataSign=dataSignature)																												//сравниваем метку data
	{																																			//начало тела
		chechedSteps++;																															//инкреминируем значение счетчика прохода
		pringDebugMsg(45,0);																													//пишем в консоль
	}																																			//конец тела
	else																																		//иначе...
	{pringDebugMsg(40,0);}																														//...сообщаем об ошибке
	pringDebugMsg(46,0);																														//пишем о начале чтения параметров
	pringDebugMsg(47,0);																														//пишем в консоль
	printf(FileSizeMsg, Wave.chunkSizeBytes);																									//указываем на размер файла, взятый из заголовка
	pringDebugMsg(47,0);																														//пишем в консоль
	printf(FileSizeWoutHeaderMsg, Wave.chunkSizeWoutHeader);																					//пишем в консоль размер без заголовка
	if(headerDifference==36)																													//сравниваем размер заголовка без учета блока данных
	{																																			//начало тела
		chechedSteps++;																															//инкреминируем значение счетчика прохода
		pringDebugMsg(48,0);																													//пишем в консоль
	}																																			//конец тела
	else																																		//иначе...
	{pringDebugMsg(49,0);}																														//...пишем в консоль сообщение об ошибке
	pringDebugMsg(47,0);																														//пишем в консоль
	printf(SampleRateMsg, Wave.sampleRate);																										//пишем частоту дискретизации
	pringDebugMsg(47,0);																														//пишем в консоль
	printf(ByteRateMsg, Wave.byteRate);																											//пишем битрейт
	pringDebugMsg(47,0);																														//пишем в консоль
	printf(BitDepthMsg, Wave.BitDepth);																											//пишем глубину выборки
	pringDebugMsg(47,0);																														//пишем в консоль
	printf(ChannelsMsg, Wave.soundChannels);																									//пишем колво каналов
	pringDebugMsg(50,Wave.soundChannels);																										//пишем колво каналов
	pringDebugMsg(47,0);																														//пишем в консоль
	printf(BytesInSampleMsg, Wave.BytesInSample);																								//пишем количество байт в выборке
	pringDebugMsg(47,0);																														//пишем в консоль
	printf(CodecTypeMsg);																														//пишем тип кодека
	pringDebugMsg(51,Wave.compressionCode);																										//пишем код сжатия
	wordSamplesValuePos=((Wave.chunkSizeWoutHeader-8)*8)/Wave.soundChannels/Wave.BitDepth;														//вычисляем расчетное количество выборок
	pringDebugMsg(68, wordSamplesValuePos);																										//пишем в консоль
	if(chechedSteps==5)																															//сравниваем количество пройденных этапов с требуемым в тз
	{																																			//начало тела цикла
		pringDebugMsg(52,0);																													//пишем в консоль
		ahsoka=1;																																//если все гуд то выкидывает флаг об успехе
		checkStatus(2);																															//вызываем проверку флага
	}																																			//конец тела
	else																																		//иначе...
	{pringDebugMsg(17,0);}																														//сообщаем об ошибке и выходим из программы
}																																				//конец тела функции
void structModifier(void)																														//функция записи в структуру
{																																				//начало тела функции
	float sampleDivide;																															//Костыль, соотношение количество выборок исходного файла к количеству выборок взятых из convertParams.ini
	uint16_t newBytesInSample;																													//Временная переменная для вычисления количества байт в одной выборке со всех каналов
	uint32_t newByteRate;																														//Временная переменная для вычисления скорости передачи данных, Байт/с
	uint32_t newFileSizeWOutHeader;																												//Временная переменная для вычисления размера файла без заголовка
	sampleDivide=Wave.sampleRate/FilSet.FSetSampleRate;																							//Сразу же вычисляю соотношения количества выборок, напечатаю чуть позже
	pringDebugMsg(53,0);																														//Вывод сообщения о начале работе функции
	pringDebugMsg(99, FilSet.FSetSamplesValue);																									//Вывод в консоль
	pringDebugMsg(58,0);																														//Вывод сообщения о том, что щас начнется запись в структуру
	Wave.sampleRate=FilSet.FSetSampleRate;																										//Запись в структуру частоты дискретизации, полученные из файла convertParams.ini
	pringDebugMsg(55, Wave.sampleRate);																											//Вывод сообщения об этом
	Wave.BitDepth=FilSet.FSetBitDepth;																											//Запись в структуру глубины выборки, полученные из файла convertParams.ini
	pringDebugMsg(54, Wave.BitDepth);																											//Вывод сообщения об этом
	Wave.soundChannels=FilSet.FSetChannels;																										//Запись в структуру количество каналов, полученных из файла convertParams.ini
	pringDebugMsg(57, Wave.soundChannels);																										//Вывод сообщения об этом
	newByteRate=(Wave.sampleRate*Wave.BitDepth*Wave.soundChannels)/8;																			//Вычисления скорости передачи данных, байт в секунду
	Wave.byteRate=newByteRate;																													//Запись в структуру результата
	pringDebugMsg(56, Wave.byteRate);																											//Вывод сообщения об этом
	newBytesInSample=(Wave.BitDepth*Wave.soundChannels)/8;																						//Вычисление количества байтов в одной выборке со всех каналов
	Wave.BytesInSample=newBytesInSample;																										//Запись в структуру
	pringDebugMsg(67, Wave.BytesInSample);																										//Вывод сообщения об этом
	printSampleDivide(sampleDivide);																											//Вывод точного соотношения выборок
	newFileSizeWOutHeader=(((FilSet.FSetSamplesValue/sampleDivide)*Wave.BitDepth*Wave.soundChannels)/8)+8;										//Вычисление размера файла без заголовка
	Wave.chunkSizeWoutHeader=newFileSizeWOutHeader;																								//Запись в структуру
	pringDebugMsg(69, Wave.chunkSizeWoutHeader);																								//Вывод в консоль
	Wave.chunkSizeBytes=newFileSizeWOutHeader+36;																								//Добавляю 36 байт заголовка
	pringDebugMsg(70, Wave.chunkSizeBytes);																										//Вывод в консоль
	cruzo=1;																																	//Записываем 1, все хорошо, в дальнейшем будет записан код самопроверки функции
	checkStatus(6);																																//Вызываю функцию проверки флага состояния
}																																				//конец тела функции
int WriteSettingsFile(void)																														//функция подготовки модифицированного заголовка к записи
{																																				//начало тела функции
	pringDebugMsg(75,0);																														//пишем в консоль сообщение о начале работы
	clearHeaderBuffer();																														//чистим буфер заголовка
	writeBuffer(headerAddrs[0], headerAddrs[1], Wave.RiffSign, headerWordSizeOf[0], headerWordInvert[0]);										//пишем в буфер метку RIFF
	writeBuffer(headerAddrs[1], headerAddrs[2], Wave.chunkSizeBytes, headerWordSizeOf[1], headerWordInvert[1]);									//пишем в буфер размер файла
	writeBuffer(headerAddrs[2], headerAddrs[3], Wave.WaveSign, headerWordSizeOf[2], headerWordInvert[2]);										//пишем в буфер метку WAVE
	writeBuffer(headerAddrs[3], headerAddrs[4], Wave.fmtSign, headerWordSizeOf[3], headerWordInvert[3]);										//пишем в буфер метку fmt
	writeBuffer(headerAddrs[4], headerAddrs[5], Wave.DataFormatLenght, headerWordSizeOf[4], headerWordInvert[4]);								//пишем в буфер размер файла
	writeBuffer(headerAddrs[5], headerAddrs[6], Wave.compressionCode, headerWordSizeOf[5], headerWordInvert[5]);								//пишем в буфер код сжатия
	writeBuffer(headerAddrs[6], headerAddrs[7], Wave.soundChannels, headerWordSizeOf[6], headerWordInvert[6]);									//пишем в буфер колво каналов
	writeBuffer(headerAddrs[7], headerAddrs[8], Wave.sampleRate, headerWordSizeOf[7], headerWordInvert[7]);										//пишем в буфер частоту дискретизации
	writeBuffer(headerAddrs[8], headerAddrs[9], Wave.byteRate, headerWordSizeOf[8], headerWordInvert[8]);										//пишем в буфер битрейт
	writeBuffer(headerAddrs[9], headerAddrs[10], Wave.BytesInSample, headerWordSizeOf[9], headerWordInvert[9]);									//пишем в буфер размер выборки в байтах
	writeBuffer(headerAddrs[10], headerAddrs[11], Wave.BitDepth, headerWordSizeOf[10], headerWordInvert[10]);									//пишем в буфер глубину выборки
	writeBuffer(headerAddrs[11], headerAddrs[12], Wave.dataSign, headerWordSizeOf[11], headerWordInvert[11]);									//пишем в буфер метку data
	writeBuffer(headerAddrs[12], headerAddrs[13], Wave.chunkSizeWoutHeader, headerWordSizeOf[12], headerWordInvert[12]);						//пишем в буфер размер файла без заголовка
	BufferReader();																																//копируем содержимое в отдельный массив для показа его содержимого в режиме отладки
	pringDebugMsg(81,0);																														//уведомляем об этом
	printf("%s",fileNameHdrDat);
	FWr=fopen(fileNameHdrDat, "wb");																											//создаем файл заголовка с раннее сгенерированным именем
	if(FWr != NULL)																																//проверяем удалось ли создать файл
	{																																			//начало тела(истина)
		printf(" Успех\n");																														//пишем в консоль что все хорошо
	}																																			//конец тела(истина)
	else																																		//иначе...
	{																																			//начало тела(ложь)
		printf(" Не удалось создать файл %s\n",fileNameHdrDat);																					//...пишем о некоторых проблемах
		exit(0);																																//выходим с кодом ошибки 0
	}																																			//конец тела(ложь)
	fseek(FWr, 0, SEEK_SET);																													//устанавливаем курсор на 0
	fwrite(FileHeader, sizeof(uint8_t), sizeof(FileHeader), FWr);																				//пишем заголовок в файл
	fclose(FWr);																																//закрытие файла для записи
}																																				//конец тела цикла
int ReadSettingsFile(void)																														//читалка параметров из файла
{																																				//начало тела
	uint32_t fSrcTagEndPos;																														//объявляем переменную в которой будем хранить адрес тега FEND для имени исходника
	uint32_t fNamtagEndPos;																														//объявляем переменную в которое будем хранить адрес тега FEND для сгенерированного имени файла
	uint8_t readCursorPos=0;																													//объявляем индексную переменную массива которую будем применять при копировании
	char fSrcNameBuffer[64];																													//объявляем массив в котором будет храниться "очищенное" исходное имя файла(без тегов)
	char fNamNameBuffer[64];																													//объявляем массив в котором будет храниться "очещенное" сгенерированное имя файла(без тегов)
	memset(fSrcNameBuffer, 0x00, sizeof(fSrcNameBuffer));																						//чистим массив исходного имени
	memset(fNamNameBuffer, 0x00, sizeof(fNamNameBuffer));																						//чистим массив сгенерированого имени
	char *endTag;																																//объявляем указатель на индекс слова которое ищется в строке
	pringDebugMsg(59,1);																														//пишем в консоль инфу о чтении файла
	FSet=fopen("convertParams.ini", "rb");																										//открываем файл как бинарник
	if(!FSet)																																	//проверяем факти открытия файла
	{																																			//начало тела
		pringDebugMsg(88,0);																													//если файл не найден, или его невозможно открыть, пытаемся создать его вновь + пишем в консоль
		printf("Файл convertParams.ini не найден или поврежден. Будет создан файл с параметрами из текущего заголовка\n");						//пишем об этом в консоль
		storeStructToFile();																													//записываем настройки в файл
		pringDebugMsg(84,0);																													//выход из программмы
	}																																			//конец тела
	else																																		//иначе...
	{																																			//начало тела
		pringDebugMsg(89,0);																													//...пишем в консоль
		printf("Файл convertParams.ini найден и открыт\n");																						//что файл открыт																																			//конец тела
		fread(fileMassive, 1, sizeof(fileMassive), FSet);																						//читаем файл указанный в аргументах раннее
		cursorSymbol=strstr(fileMassive, wordFilenameSource);																					//ищем тег FSRC
		wordFsrcPos=cursorSymbol-fileMassive+1;																									//пишем адрес начала тега
		cursorPosit=wordFsrcPos+wordFilenameShift;																								//пишем адрес курсора
		fseek(FSet, cursorPosit, SEEK_SET);																										//ставим курсор по адресу
		fscanf(FSet, "%s", &fileNameSrc);																										//читаем содержимое файла по выставленному адресу
		endTag=strstr(fileNameSrc, wordSrcFilenameEnd);																							//записываем в указатель адрес курсора с которого начинается найденное слово FEND
		fSrcTagEndPos=endTag-fileNameSrc;																										//подсчитываем длину нужного фрагмена, в данном случае это имя исходного файла
		while(readCursorPos<fSrcTagEndPos)																										//объявляем цикл дублирования массива в другой массив, который нужен для дебаг целей
		{																																		//начало цикла
			fSrcNameBuffer[readCursorPos]=fileNameSrc[readCursorPos];																			//посимвольно переносим массив
			readCursorPos++;																													//инкреминируем индекс массива
		}																																		//конец тела
		readCursorPos=0;																														//сбрасываем счетчик индекса
		cursorSymbol=strstr(fileMassive, wordFilename);																							//ищем тег FNAM
		wordFnamePos=cursorSymbol-fileMassive+1;																								//пишем адрес начала тега
		cursorPosit=wordFnamePos+wordFilenameShift;																								//пишем адрес курсора
		fseek(FSet, cursorPosit, SEEK_SET);																										//ставим курсор по адресу
		fscanf(FSet, "%s", &fileName);																											//читаем содержимое файла по выставленному адресу
		endTag=strstr(fileName, wordNameFilenameEnd);																							//записываем в указатель адрес курсора с которого начинается найденное слово FEND
		fNamtagEndPos=endTag-fileName;																											//вычисляем длину сгенерированного имени файла
		while(readCursorPos<fNamtagEndPos)																										//объявляем цикл копирования массива в другой массив который нужен для дебаг целей
		{																																		//начало тела цикла
			fNamNameBuffer[readCursorPos]=fileName[readCursorPos];																				//посимвольно переносим массив
			fileNameHdrDat[readCursorPos]=fileName[readCursorPos];
			readCursorPos++;																													//инкреминируем индекс массива
		}																																		//конец тела
		cursorSymbol=strstr(fileMassive, wordConvert);																							//ищем тег Convert
		wordConvertPos=cursorSymbol-fileMassive+1;																								//пишем адрес начала тега
		cursorPosit=wordConvertPos+wordConvertShift;																							//пишем адрес курсора
		fseek(FSet, cursorPosit, SEEK_SET);																										//ставим курсор по адресу
		fscanf(FSet, "%d", &FilSet.FSetWasConverted);																							//читаем содержимое по выставленному адресу
		cursorSymbol=strstr(fileMassive, wordSampleRate);																						//ищем тег SampleRate
		wordSampleRatePos=cursorSymbol-fileMassive+1;																							//пишем адрес начала тега
		cursorPosit=wordSampleRatePos+wordSampleRateShift;																						//пишем адрес курсора
		fseek(FSet, cursorPosit, SEEK_SET);																										//ставим курсор по адресу
		fscanf(FSet, "%d", &FilSet.FSetSampleRate);																								//читаем содержимое файла по выставленному адресу
		cursorSymbol=strstr(fileMassive, wordChannels);																							//ищем тег Channels
		wordChannelsPos=cursorSymbol-fileMassive+1;																								//пишем адрес начала тега
		cursorPosit=wordChannelsPos+wordChannelsShift;																							//пишем адрес курсора
		fseek(FSet, cursorPosit, SEEK_SET);																										//ставим курсор по адресу
		fscanf(FSet, "%d", &FilSet.FSetChannels);																								//читаем содержимое файла по выставленному адресу
		cursorSymbol=strstr(fileMassive, wordBitsPerSample);																					//ищем тег BitsPerSample
		wordBitsPerSamplePos=cursorSymbol-fileMassive+1;																						//пишем адрес начала тега
		cursorPosit=wordBitsPerSamplePos+wordBitsPerSampleShift;																				//пишем адрес курсора
		fseek(FSet, cursorPosit, SEEK_SET);																										//ставим курсор по адресу
		fscanf(FSet, "%d", &FilSet.FSetBitDepth);																								//читаем содержимое файла по выставленному адресу
		cursorSymbol=strstr(fileMassive, WordCountOfSamples);																					//ищем тег BitsPerSample
		wordSamplesValuePos=cursorSymbol-fileMassive+1;																							//пишем адрес начала тега
		cursorPosit=wordSamplesValuePos+wordSamplesValueShift;																					//пишем адрес курсора
		fseek(FSet, cursorPosit, SEEK_SET);																										//ставим курсор по адресу
		fscanf(FSet, "%d", &FilSet.FSetSamplesValue);																							//читаем содержимое файла по выставленному адресу
		pringDebugMsg(89,0);																													//срём в консоль
		pringDebugMsg(94,fSrcTagEndPos);																										//пишем адрес смещения по тегу FSRC
		pringDebugMsg(89,0);																													//пишем в консоль
		printf("Имя исходного файла: %s\n", fSrcNameBuffer);																					//пишем имя исходного файла
		pringDebugMsg(89,0);																													//срём в консоль
		pringDebugMsg(94,fNamtagEndPos);																										//пишем адрес смещения по тегу FNAM
		pringDebugMsg(89,0);																													//пишем в консоль
		printf("Имя файла с заголовком: %s\n", fNamNameBuffer);																					//пишем имя заголовочного файла
		pringDebugMsg(89,0);																													//срём в консоль
		printf("Адреса смещений по тегам Convert,SampleRate,Channels,BitsPerSample,SamplesInChannel\n");										//пишем инфу что щас будут адреса смещений тегов
		pringDebugMsg(89,0);																													//срём в консоль
		pringDebugMsg(90,wordConvertPos);																										//пишем адрес смещения по тегу Convert
		pringDebugMsg(89,0);																													//пишем в консоль
		pringDebugMsg(90,wordSampleRatePos);																									//пишем адрес смещения по тегу SampleRate
		pringDebugMsg(89,0);																													//пишем в консоль
		pringDebugMsg(90,wordChannelsPos);																										//пишем адрес смещения по тегу Channels
		pringDebugMsg(89,0);																													//пишем в консоль
		pringDebugMsg(90,wordBitsPerSamplePos);																									//пишем адрес смещения по тегу BitsPerSample
		pringDebugMsg(89,0);																													//пишем в консоль
		pringDebugMsg(90,wordSamplesValuePos);																									//пишем адрес смещения по тегу BitsPerSample
	}																																			//конец тела
	pringDebugMsg(89,0);																														//пишем в консоль
	if(DebugMode==1)																															//костыль на проверку режима отладки
	{																																			//начало тела
		printf("Кол-во каналов: %d\n", FilSet.FSetChannels);																					//пишем количество каналов
		pringDebugMsg(89,0);																													//пишем в консоль
		printf("Частота дискретизации: %d Гц\n", FilSet.FSetSampleRate);																		//пишем частоту дискретизации
		pringDebugMsg(89,0);																													//пишем в консоль
		printf("Флаг конвертации: %d\n", FilSet.FSetWasConverted);																				//пишем состояние флага конвертации(была ли она или нет)
		pringDebugMsg(89,0);																													//пишем в консоль
		printf("Бит в выборке: %d Бит\n", FilSet.FSetBitDepth);																					//пишем глубину выборки
		pringDebugMsg(89,0);																													//пишем в консоль
		printf("Количество выборок в одном канале: %d\n", FilSet.FSetSamplesValue);																//пишем количество выборок на один канал
	}																																			//конец тела
	pringDebugMsg(60, FilSet.FSetSampleRate);																									//пишем частоту дискретизации в консоль
	pringDebugMsg(62, FilSet.FSetChannels);																										//пишем количество каналов в консоль
	pringDebugMsg(61, FilSet.FSetBitDepth);																										//пишем глубину выборки в консоль
	if(FilSet.FSetWasConverted==0)																												//проверка факта конвертации
	{																																			//начало тела
		pringDebugMsg(63, FilSet.FSetWasConverted);																								//пишем в консоль снова
		Egor=1;																																	//ставим флаг
		checkStatus(5);																															//вызываем проверку флага
		pringDebugMsg(83,0);																													//пишем в консоль уведомление что с файлом еще ничего не делали
	}																																			//конец тела
	else																																		//иначе...
	{																																			//начало тела
		pringDebugMsg(63, FilSet.FSetWasConverted);																								//...начинаем формировать заголовок
		Egor=1;																																	//поднимаем флаг хехе))
		checkStatus(5);																															//вызываем проверку
		fclose(FSet);																															//закрываем файл т.к он больше не нужен в данный момент
		structModifier();																														//пишем заголовок в файл
		return 0;																																//возвращаем 0
	}																																			//конец тела
	fclose(FSet);																																//закрываем поток, если он где-то еще не был закрыт
}																																				//конец функции
inline void clearByteBuffer(void)																												//очистка временного буфера(встраиваемая функция)
{																																				//начало тела
	pringDebugMsg(79,0);																														//пишем в консоль уведомление что идет чистка буфера
	memset(ByteBuffer,0x00,sizeof(ByteBuffer));																									//чистим массив
}																																				//конец тела
inline void clearHeaderBuffer(void)																												//очистка массива заголовка(встраиваемая функция
{																																				//начало тела
	pringDebugMsg(80,0);																														//пишем сообщение о том что щас будем чистить массив
	for(int i=0;i<43;i++)																														//начало цикла чистки
	{																																			//начало тела цикла
		FileHeader[i]=0;																														//чистим побайтово массив
	}																																			//конец тела цикла
}																																				//конец тела функции
inline void BufferReader(void)																													//функция копирование заголовка в отдельный массив для показа отладочных уведомлений(встраиваемая)
{																																				//начало тела
	writeDebugHeaderBuffer();																													//вызываем функцию копирования
	pringDebugMsg(25,0);																														//пишем уведомление об этом
}																																				//конец тела
uint32_t writeBuffer(int startOffset, int endOffset, uint32_t paramToWrite, int wordSize, bool SwapByte)										//функция записи буфера
{																																				//начало тела
	int debugCursorPos=0;																														//инициализируем переменную
	int bufferPos=0;																															//инциаилизируем переменную индекса массивов
	pringDebugMsg(76,paramToWrite);																												//пишем в консоль что начинам писать полученный параметр
	switch(wordSize)																															//выбор способа записи в зависимости от размера полученного на входе
	{																																			//то есть 0 байт - ошибка, 1 байт - пишем 1 байт, 2 байта - байта пишем и т.д
		case 0:																																	//в случае если 0 байт(NANI?)
			pringDebugMsg(77,0);																												//пишем что таких переменных не существует и выходим из программы
			break;																																//выход из цикла
		case 1:																																	//в случае если 1 байт
			ByteBuffer[0]=paramToWrite;																											//пишем в буфер 1 байт
			break;																																//выходим из цикла
		case 2:																																	//в случае если 2 байта
			ByteBuffer[0]=paramToWrite;																											//пишем старший байт
			ByteBuffer[1]=paramToWrite>>8;																										//пишем младший байт
			break;																																//выходим из цикла
		case 4:																																	//в случае если 4 байта
			ByteBuffer[0]=paramToWrite;																											//пишем старший байт
			ByteBuffer[1]=paramToWrite>>8;																										//пишем байт помладше
			ByteBuffer[2]=paramToWrite>>16;																										//пишем байт помладше
			ByteBuffer[3]=paramToWrite>>24;																										//пишем младший байт
			break;																																//выходим из цикла
	}																																			//конец тела цикла
	massiveSwap(SwapByte);																														//переворачиваем массив
	while(debugCursorPos<wordSize)																												//вызываем цикл показа содержимого временного буфера
	{																																			//начало цикла
		pringDebugMsg(78, ByteBuffer[debugCursorPos]);																							//показываем в консоли то что там находится
		debugCursorPos++;																														//инкреминируем индекс
	}																																			//конец цикла
	debugCursorPos=0;																															//сбрасываем переменную
	while(startOffset<endOffset)																												//начало цикла записи копирования из буфера в заголовок с заданным смещением
	{																																			//начало тела цикла
		FileHeader[startOffset]=ByteBuffer[bufferPos];																							//побайтовое копирование из временного массива
		bufferPos++;																															//инкреминируем переменную индекса массива временного буфера
		startOffset++;																															//инкреминируем переменную массива заголовка
	}																																			//конец цикла
	bufferPos=0;																																//сбрасываем переменную
	clearByteBuffer();																															//чистим буфер
}																																				//конец функции
void storeStructToFile(void)																													//функция записи настроек в файл
{																																				//начало функции
	uint8_t crlfSign[2]={0x0D, 0x0A};																											//метка CR LF(перенос каретки на новую строку)
	bool WordConverted=0;																														//инициализируем флаг
	char *FnameSrc="FSRC>";																														//имя исходного файла
	char *FnameBod="FBOD>";																														//имя тела файла
	char *Fnametgt="FTGT>";																														//имя файла после склеивания
	char *Fname="FNAM>";																														//имя файла
	char *WordConvert="Convert=";																												//образец тега Convert
	char *WordSampleRate="SampleRate=";																											//образец тега SampleRate
	char *WordChannels="Channels=";																												//образец тега Channels
	char *WordBitsPerSample="BitsPerSample=";																									//образец тега BitsPerSample
	char *WordCountOfSamples="SamplesInChannel=";																								//образец тега SamplesInChannel
	pringDebugMsg(86,0);																														//уведомляем что щас будем писать в файл
	FSet=fopen("convertParams.ini", "wb");																										//открываем файл на запись как бинарный(зач бинарный? тут текст обычный)
	fseek(FSet, 0, SEEK_SET);																													//устанвливаем курсор на 0
	fprintf(FSet, "%s", FnameSrc);																												//пишем тег FNAM
	fprintf(FSet, "%s", fileNameSrc);																											//пишем имя файла
	fprintf(FSet, "%s", wordSrcFilenameEnd);																									//пишем тег >FSND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", Fname);																													//пишем тег FNAM
	fprintf(FSet, "%s", fileNameHdrDat);																										//пишем имя файла
	fprintf(FSet, "%s", wordNameFilenameEnd);																									//пишем тег >FNND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", FnameBod);																												//пишем тег FBOD
	fprintf(FSet, "%s", fileNameBodDat);																										//пишем имя файла
	fprintf(FSet, "%s", wordBodyFilenameEnd);																									//пишем тег >FBND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", Fnametgt);																												//пишем тег FTGT
	fprintf(FSet, "%s", fileNameTgtDat);																										//пишем имя файла
	fprintf(FSet, "%s", wordTargFilenameEnd);																									//пишем тег >FTND
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", WordConvert);																											//пишем тег Convert
	fprintf(FSet, "%d", WordConverted);																											//пишем флаг состояния
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", WordSampleRate);																										//пишем тег SampleRate
	fprintf(FSet, "%d", Wave.sampleRate);																										//пишем частоту дискретизации числом
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", WordChannels);																											//пишем тег Channels
	fprintf(FSet, "%d", Wave.soundChannels);																									//пишем количество каналов
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", WordBitsPerSample);																										//пишем тег BitsPerSample
	fprintf(FSet, "%d", Wave.BitDepth);																											//пишем глубину выборки
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fprintf(FSet, "%s", WordCountOfSamples);																									//пишем тег BitsPerSample
	fprintf(FSet, "%d", wordSamplesValuePos);																									//пишем количество выборок
	fwrite(crlfSign, sizeof(uint8_t), sizeof(crlfSign), FSet);																					//пишем CR LF
	fclose(FSet);																																//закрываем файл
	pringDebugMsg(87,0);																														//отчитываемся в консоль о проделанной работе
}																																				//конец функции
