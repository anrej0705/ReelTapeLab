#### [Проект](https://github.com/users/anrej0705/projects/2)
 
#### [Релизы](https://github.com/anrej0705/ReelTapeLab/releases)

#### [Текущие задачи](https://github.com/users/anrej0705/projects/1/views/1)

### Системные требования

|||
|:----------|:------------|
|ОС|Windows 95|
|CPU|80386|
|HDD|400 Кб|
|RAM|8 Мб|
|Video|640x480|
|Audio|SB16|

|Название программы|Версия|Номер сборки|
|:------------|:------:|:---------|
|WAVPLAY.EXE|N/A|N/A|
|MICREC.EXE|N/A|N/A|
|BIN2AM.EXE|N/A|N/A|
|BIN2FM.EXE|0.0.2|build 3|
|AM2BIN.EXE|N/A|N/A|
|FM2BIN.EXE|0.0.1|build 1|
|WAVREST.EXE|N/A|N/A|
|CALIBRAT.EXE|N/A|N/A|
|WAVHEAD.EXE|0.2.7|build 39|
|WAVCONV.EXE|0.0.2|build 6|
|WAVBIND.EXE|0.0.1|build 2|
|APPSET.EXE|N/A|N/A|
|Плагины|Версия|Номер сборки|
|CRC.DLL|N/A|N/A|
|STACK.DLL|N/A|N/A|
|SIGRECV.DLL|N/A|N/A|
|DENOISE.DLL|N/A|N/A|

*Предварительные системные требования, позже будут скорректированы*

*Требуемое свободное место на HDD для самой программы без учета файлов с которыми она будет работать*

*Подойдет любая 8/16 разрядная звуковая карта*

#### Требования к параметрам WAV файла для FM2BIN:
- Разрядность 8 бит
- Количество каналов: 1
- Хотя бы один в начале должен быть ниже порогового уровня(159 или 0x9F)

### Программы в наборе:

**WavePlayer(WAVPLAY.EXE)** - Простой проигрыватель WAV файлов

**MicRecoder(MICREC.EXE)** - Простая программа записи с микрофона в WAV формат с возможностью настройки параметров

**FileEncoderAM(BIN2AM.EXE)** - Программа для формирования звуковых файлов из исходного двоичного формата, амплитудная модуляция

**FileEncoderFM(BIN2FM.EXE)** - Программа для формирования звуковых файлов из исходного двоичного формата, частотная модуляция

**FileDecoderAM(AM2BIN.EXE)** - Программа для преобразование входного звуквого сигнала AM модуляции в конечный файл

**FileDecoderFM(FM2BIN.EXE)** - Программа для преобразование входного звуквого сигнала FM модуляции в конечный файл

**AnalogRestorator(WAVREST.EXE)** - Очистка и восстановление формы сигнала в файле после оцифровки

**SignalCalibrator(CALIBRAT.EXE)** - Калибровка плотности записи для подбора оптимальных условий

**wavConverter(WAVHEAD.EXE,WAVCONV.EXE,WAVBIND.EXE)** - Конвертер формата WAV в 8-разрядный моно формат

**appSetting(APPSET.EXE)** - Настройщик работы программ, для большего удобства -)

### Плагины:

**CRC-генератор(CRC.DLL)** - Генерирует CRC сумму для проверки целостности данных(или блока данных)

**Стек-менеджер(STACK.DLL)** - Создает стек и управляет им для хранения данных во время работы какого либо приложения

**SIGRECV.DLL** - Плагин, восстанавливающий форму сигнала

**Шумодав(DENOISE.DLL)** - Плагин, удаляющий шум из оцифрованного сигнала

# WAV Converter
:ru:

Набор из трех программ, предназначенный для подготовки оцифрованного файла к
дальнейшей обработки

Версии и номера сборок:
|Название программы|Версия|Номер сборки|
|:------------|:------:|:---------|
|exHeader|0.2.7|build 39|
|exConverter|0.0.2|build 6|
|exStitcher|0.0.1|build 2|

## exHeader
:ru:

:information_source:**Пример вызова: C:\RLab\wavConverter\exHeader.exe foreign.wav**

:information_source:Доступные аргументы:

    -help - Выводит справочную информацию
	
	-debugmode - Включает режим отладки при котором выводятся дополнительные сообщения о работе программы
	
	-makehead - Генерирует и сохраняет заголовок из файла convertParams.ini если он существует
	
	-setlocale=LOCALE_name - Переключает локализацию. Будет проведена попытка загрузки доступной локализации из файла locales.loc
	
	-readheader - Программа считывает заголовок и выводит его параметры на экран
	
	-quiet - Программа не выводит никаких сообщнений во время работы
	
	-ver - Программа отображает свою версию и номер сборки
	

Программа считывает заголовок по меткам **RIFF, WAVE, fmt , data**, проверяет соответствие
требованиям формата и наличия минимально необходимых меток(всего 4). Дополнительные метки 
такие как **IDIT, EXIF, CSET, AGES, GENR** и т.п игнорируются и не будут прочитаны. По
итогу прочитанной из заголовка информацией, создается файл *convertParams.ini*, в который
записываются следующие данные - см. таблицу ниже
*Таблица 1. Структура covnertParams.ini*
|Тег|Описание|Пример|
|:---------------|:----------------------------------------|:------------------------|
|FSRC, FSND|Указатель на исходный файл|FFSRC>war1.wav>FSND|
|FNAM, FNND|Указатель на файл с записанным заголовком|FBOD>war1_header.dat>FBND|
|FBOD, FBND|Указатель на файл с WAV данными|FBOD>war1_body.dat>FBND|
|FTGT, FTND|Указатель на конечное имя файла|FTGT>war1_conv.wav>FTND|
|Convert|Флаг состояния конвертации|Convert=1|
|SampleRate|Частота дискретизации, Гц|SampleRate=192000|
|Channels|Количество каналов в файле|Channels=1|
|BitsPerSample|Глубина выборки в битах|BitsPerSample=8|
|SamplesInChannel|Количество выборок в одном канале|SamplesInChannel=5083700|

### Теги FSRC и FSND
Данная пара тегов указывает на исходный файл, содержащий заголовок и тело. Исходный файл
необходим для чтения заголовка, тела для конвертации

### Теги FNAM и FNND
Указывают на файл с исходным или модифицированным заголовком. Состав заголовка минимальный и
включает в себя только необходимые для правильного воспроизведения теги и данные

### Теги FBOD и FBND
Распологают информацией о имени файла с WAV данными. В процессе работы конвертера создается
файл с указанным в этих тегах именем и в него записываются конвертированные семплы

### Теги FTGT и FTND
Здесь хранится информация о имени конечного файла. После завершения процесса конвертации
тела и модификации заголовка, будет записан файл с заголовком, записанным в этих тегах

При втором запуске exHeader проверяет наличие файла *convertParams.ini*. В случае если
требуемый файл найден и был успешно открыт, из него считывается состояние флага *Convert*
В случае считывания 0 - работа программы будет прервана с указанием на то что файл тела
не был конвертирован. В случае считывания 1 - программа прочитает файл параметров и
сформирует из него новый заголовок, который будет записан с именем указанным в паре
тегов **FNAM и FNND**
____
## exConverter
:ru:

:information_source:**Пример вызова: C:\RLab\wavConverter\exConverter.exe [входящий файл]foreign.wav [конечный файл]foreign8.wav**

:information_source:Доступные аргументы:

    -ignoreini - Программа игнорирует файл convertParams.ini, даже если он обнаружен
	
	-ignorehead - Программа игнорирует первые 44 байта файла, даже если в файле нету заголовка
	
	-insrate=integer - Указание входной частоты дискретизации. Информация из заголовка или convertParams.ini игнорируется
	
	-outsrate=integer - Указание выходной частоты дискретизации. Выходная частота будет записана в convertParams.ini если он обнаружен и если Convert=0
	
	-inchannels=integer - Указание количество каналов исходного файла. Информация из заголовка или convertParams.ini игнорируется
	
	-outchannels=integer - Указание количества каналов выходного файла. Значение будет записано в convertParams.ini если он обнаружен и если Convert=0
	
	-inbits=integer - Указание глубины выборки исходного файла. Информация из заголовка или convertParams.ini игнорируется
	
	-outbits=integer - Указание глубины выборки конечного файла. Значение будет записано в convertParams.ini если он обнаружен и если Convert=0
	
	-insamples=integer - Задание суммарного количества выборок входного файла. Информация из заголовка или convertParams.ini игнорируется
	
	-outsamples=integer - Задание суммарного количества выборок выходного файла. Значение будет записано в convertParams.ini если он обнаружен и если Convert=0
	
	-insamplesmono=integer - Задание количества выборок в одном канале входного файла. Информация из заголовка или convertParams.ini игнорируется
	
	-outsamplesmono=integer - Задание количества выборок в одном канале выходного файла. Значение будет записано в convertParams.ini если он обнаружен и если Convert=0
	
	-debugmode - Включает режим отладки при котором выводятся дополнительные сообщения о работе программы
	
	-help - Отображение справочной информации
	
	-ver - Отображение версии программы и номера сборки
	

Программа конвертирует входящий файл смешивая входные каналы в один(моно), понижая
разрядность до 8 бит при этом сохраняя исходную частоту дискретизации

*Программа является частью комплекта программ для подготовки файлов к обработке*
*и поэтому сама по себе не имеет смысла*

Если в директории запуска обнаруживается *convertParams.ini* и в аргументах не указан
**-ignoreini** то данные из файла параметров будут иметь высший приоритет перед
аргументами командной строки

В ином случае программа прочитает данные из заголовка файла указанного как входящий и
будет проведена конвертация с понижением разрядности и совмещением каналов в один(моно)

**Проект находится в стадии создания прототипа**

**Работоспобность программ не гарантируется**

____
## exStitcher
:ru:

:information_source:Доступные аргументы:

    -ignoreini - Программа игнорирует файл convertParams.ini, даже если он обнаружен
	
    -ihed file_source - Ссылка на файл file_source содержащий заголовок
	
	-ibod file_source - Ссылка на файл file_source содержащий тело
	
	-itag file_source - Конечное имя файла
	
	-debugmode - Включает режим отладки при котором выводятся дополнительные сообщения о работе программы
	
	-help - Отображение справочной информации
	
	-ver - Отображение версии программы и номера сборки
	

Программа склеивает заголовок и тело, указанные в *convertParams.ini* и записывает
конечный результат. В случае отстутствия или невозможности открыть этот файл программа
прекращает свою работу

*В будущем сюда будет добавлена дополнительная информация по конвертеру - как только, так сразу* :wink: :wink:

**Проект находится в стадии создания прототипа**
**Работоспобность программ не гарантируется**

*В будущем сюда будет добавлена дополнительная информация по проекту - как только, так сразу*  :wink: :wink:
