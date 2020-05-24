# Snake 
Classic game snake with 2 enemies guided by AI which is written by me.
Game supports 2 interface: tui in terminal and gui in sfml-window

You are violet snake. Blue enemy is "wavy" snake and white is "straight" that's in tty
In gui you are violet too, but your opponents are green who is "wavy" and blue who is "straight"

To quit the game press 'q', to move your snake press "wasd". Your score is on the screen. 

# Progress check
1. Используя stl контейнеры и алгоритмы, напишите программу myuniq, иммитирующую поведение стандартных утилит sort | uniq (или sort -u).
Она должна, будучи запущена без аргументов командной строки, читать строки с stdin и выводить на stdout отсортированные по алфавиту уникальные строки, опуская совпадающие.
Пример: для строк
bbb
aaa
ccc
aaa
bbb
программа должна вывести строки
aaa
bbb
ccc

2. Используя std::future и std::promise паттерн синхронизации, напишите программу mycat, выполняющую функции стандартноуй утилиты cat, но с условием параллельного выполнения операций чтения и записи в двух потоках. Потоки должны придерживаться семантики high/low watermark буферизации: прекращать наполнять внутренний буфер при переполнении и возобновлять при опустошении до low 20% отметки, прекращать опустошать внутренний буфер при его полном опустошении и возобновлять при достижении high 80% отметки. Используйте атомарные операции чтения/записи по 4K и установите размер буфера в 1MB.

3. Напишите программу mycompute, расставляющие в произвольном порядке знаки операции + - * между цифрами указанными аргументами командной строки, чтобы получить заданное первым аргументом число. Приоритет операций сложения-вычитания ниже умножения, также между цифрами можно не ставить операцию, чтобы получилось многозначное число.

Пример:
mycompute 124 1 2 4
124 = 124
mycompute 16 1 2 4
12+4 = 16
mycompute 9 1 2 4
1+2*4 = 9
mycompute 10 4 3 2
4+3*2 = 10
4*3-2 = 10
