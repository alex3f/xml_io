# Создание библиотеки для работы с репозиторием классов C++

## Цель:
    Необходимо создать библиотеку для работы с XML репозиторием классов C++. 
 
 ## Запуск, сборка, ход выполнения:
    см. xml_io/wiki 
    
## Описание задачи:
В компиляторе существует дерево внутреннего представления программы, которое представлено в виде взаимосвязанных 
экземпляров классов с одним и тем же родителем. В целях оптимизации и создания файлов предкомпилированных заголовков 
необходимо создание репозитория внутреннего представления компилятора.
Для этого необходимо создать библиотеку с 2-мя функциями: Функция выгрузки дерева внутреннего представления в XML репозиторий
И функция загрузки дерева из него. Возможно минимальное редактирование классов представляющих дерево 
внутреннего представления – добавление функций выгрузки/загрузки и, возможно, дополнительных внутренних данных класса.
Так же необходимо описать процесс добавления в новые классы дерева функциональности работы с репозиторием. 
 
Для тестирования библиотеки предлагается создать набор тестовых классов, который должен включать:
- Виртуальное наследование
- Субклассы
- Членами классов должны быть:  
o	Целые  
o	Указатели на целые  
o	Массивы  
o	Экземпляры классов  
o	Указатели на экземпляры классов  
o	Ссылки на экземпляры классов   
o	Указатели на классы с виртуальным родителем  
 
## Формат репозитория:
    XML представление по желанию автора.
 
## Платформа:
    Любая (кроме Win32 и MSVC), но C++
