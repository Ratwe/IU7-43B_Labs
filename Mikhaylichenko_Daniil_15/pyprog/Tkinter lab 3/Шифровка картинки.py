"""
Михайличенко Даниил ИУ7-23Б

- Программа по шифровке сообщения в картинку
  и дальнейшей расшифровки
"""

'''
+-----------------------+
|Подключаемые библиотеки|
+-----------------------+
'''
from tkinter import *
from tkinter import messagebox as box
from tkinter import filedialog as fd
from PIL import Image

'''
+------------------+
|Внутренние функции|
+------------------+
'''


# Описание программы
def description():
    box.showinfo('О программе:', 'Шифровка сообщения в картинку\n\
                \n©Михайличенко Даниил ИУ7-23Б\n28.03.2022')


# Функция создания кнопки выбора файла
def make_choose_button(string, cipher_check):
    return Button(window,
                  text=string,
                  bd=3,
                  command=lambda: choose_file(cipher_check),
                  font=('Comic Sans MS', 10),
                  bg='#AD62AA'
                  )


# Функция создания кнопки открытия файла
def make_open_button(string, cipher_check):
    return Button(window,
                  text=string,
                  bd=3,
                  command=lambda: open_file(cipher_check),
                  font=('Comic Sans MS', 10),
                  bg='#AD62AA'
                  )


# Функция создания имени для шифрованого файла
def create_name(path):
    for i in range(len(path) - 1, -1, -1):
        if path[i] == '/' or path[i] == 0:
            break

    return 'ciphered_{}'.format(path[i:])


# Функция высчитывания координаты следущего пикселя
def new_coordinates(x, y, img):
    length, width = img.size
    x += 1
    if x == length:
        x = 0
        y += 1

        if y > width:
            print('Пиксели кончились')

    return x, y


# Функция получения двоичной записи кода символа в виде матрицы
def get_bin_symbol_from_text(text):
    for symbol in text:

        bin_symbol = bin(ord(symbol))[2:]

        while len(bin_symbol) < 11:
            bin_symbol = '0' + bin_symbol

        bits_list = [
            [bin_symbol[0], bin_symbol[1], bin_symbol[2], bin_symbol[3]],
            [bin_symbol[4], bin_symbol[5], bin_symbol[6], bin_symbol[7]],
            [bin_symbol[8], bin_symbol[9], bin_symbol[10]]
        ]

        yield bits_list


# Функция получения части битов символа (нахождение разности между картинками)
def get_bits(img, c_img, x, y):
    pxl = img.getpixel((x, y))
    c_pxl = c_img.getpixel((x, y))

    r = abs(int(pxl[0]) - int(c_pxl[0]))
    g = abs(int(pxl[1]) - int(c_pxl[1]))
    b = abs(int(pxl[2]) - int(c_pxl[2]))
    v = abs(int(pxl[3]) - int(c_pxl[3]))

    return [r, g, b, v]


# Создание нового цвета пикселя
def new_color(r, g, b, v, bin_symbol_part):
    r += int(bin_symbol_part[0])
    g += int(bin_symbol_part[1])
    b += int(bin_symbol_part[2])

    if len(bin_symbol_part) == 4:
        v -= int(bin_symbol_part[3])

    return r, g, b, v


# Функция изменения цвета пикселя (шифровка символа)
def paint_pixel(bin_symbol_part, img, x, y):
    pxl = img.getpixel((x, y))

    r, g, b, v = pxl[0], pxl[1], pxl[2], pxl[3]

    r, g, b, v = new_color(r, g, b, v, bin_symbol_part)

    img.putpixel((x, y), (r, g, b, v))

    return img


'''
+-----------------------+
|Основные функции кнопок|
+-----------------------+
'''


# Функция выбора файла (для шифровки или расшифровки)
def choose_file(cipher_check):
    file_path = fd.askopenfilename(
        parent=window,
        title='Выберите файл',
        filetypes=[('png images', '.png')]
    )

    if cipher_check:
        cipher_path_entry.delete(0, END)

        if file_path == '':
            cipher_path_entry.insert(0, '')
        else:
            cipher_path_entry.insert(0, file_path)

    else:
        path_entry['state'] = 'normal'
        path_entry.delete(0, END)

        if file_path == '':
            path_entry.insert(0, 'C:/Users/danpo/OneDrive/Изображения/Saved Pictures/Лемминги.png')
        else:
            path_entry.insert(0, file_path)


# Функция открытия файла (основного или шифрованного)
def open_file(cipher_check):
    if cipher_check:
        path = cipher_path_entry.get()
    else:
        path = path_entry.get()

    try:
        img = Image.open(path)
        img.show()

    except (FileNotFoundError, AttributeError):
        box.showinfo('Внимание!', 'Файл не найден!')

    except PermissionError:
        box.showinfo('Внимание!', 'Отказано в доступе!')


# Функция шифровки сообщения в картинку
def cipher_msg():
    path = path_entry.get()
    img = Image.open(path)

    text = msg_entry.get() + '߿'

    x = y = 0

    for bin_symbol in get_bin_symbol_from_text(text):
        for part in range(3):
            img = paint_pixel(bin_symbol[part], img, x, y)
            x, y = new_coordinates(x, y, img)

    new_file_name = create_name(path)
    img.save(new_file_name)

    cipher_path_entry.delete(0, END)
    cipher_path_entry.insert(0, new_file_name)


# Функция дешифровки картинки
def decipher_msg():
    path = path_entry.get()
    img = Image.open(path)

    cipher_path = cipher_path_entry.get()
    try:
        c_img = Image.open(cipher_path)
    except (FileNotFoundError, AttributeError):
        box.showinfo('Внимание!', 'Файл не найден!')
        return

    symbol = string = ''
    x = y = 0

    while symbol != '߿':
        first_part = get_bits(img, c_img, x, y)
        x, y = new_coordinates(x, y, img)

        second_part = get_bits(img, c_img, x, y)
        x, y = new_coordinates(x, y, img)

        third_part = get_bits(img, c_img, x, y)
        x, y = new_coordinates(x, y, img)

        code = first_part[0] * (2 ** 10) + first_part[1] * (2 ** 9) + \
               first_part[2] * (2 ** 8) + first_part[3] * (2 ** 7) + \
               second_part[0] * (2 ** 6) + second_part[1] * (2 ** 5) + \
               second_part[2] * (2 ** 4) + second_part[3] * (2 ** 3) + \
               third_part[0] * (2 ** 2) + third_part[1] * 2 + third_part[2]

        symbol = chr(code)
        string += symbol

    decipher_entry.delete(0, END)
    decipher_entry.insert(0, string[:-1])


'''
+---------------------+
|Графический интерфейс|
+---------------------+
'''
# Создание окна
window = Tk()
window.title('Шифровщик')
window.geometry('600x250')
window['bg'] = '#413C69'

# Создание пункта меню
mainmenu = Menu(window)
window.config(menu=mainmenu)
mainmenu.add_cascade(label='О программе...', command=description)

# Создание лейблов
path_label = Label(window, text='Файл:', font=('Comic Sans MS', 10),
                   bg='#413C69', fg='#EAB9C9')
path_label.grid(row=0, column=0)

cipher_path_label = Label(window, text='Шифр. файл:', font=('Comic Sans MS', 10),
                          bg='#413C69', fg='#EAB9C9')
cipher_path_label.grid(row=1, column=0)

msg_label = Label(window, text='Сообщение:', font=('Comic Sans MS', 10),
                  bg='#413C69', fg='#EAB9C9')
msg_label.grid(row=2, column=0)

decipher_label = Label(window, text='Расшифровка:', font=('Comic Sans MS', 10),
                       bg='#413C69', fg='#EAB9C9')
decipher_label.grid(row=5, column=0)

# Создание полей ввода
path_entry = Entry(window, justify=LEFT, font=('Comic Sans MS', 10), bg='#EAB9C9')
path_entry.insert(0, 'Лемминги.png')
path_entry.grid(stick='we', row=0, column=1, columnspan=3)

cipher_path_entry = Entry(window, justify=LEFT, font=('Comic Sans MS', 10), bg='#EAB9C9')
cipher_path_entry.grid(stick='we', row=1, column=1, columnspan=3)

msg_entry = Entry(window, justify=LEFT, font=('Comic Sans MS', 10), bg='#EAB9C9')
msg_entry.insert(0, 'Я хочу пиццу!')
msg_entry.grid(stick='we', row=2, column=1, columnspan=3)

decipher_entry = Entry(window, justify=LEFT, font=('Comic Sans MS', 10), bg='#EAB9C9')
decipher_entry.grid(stick='we', row=5, column=1, columnspan=3)

# Создание кнопок
choose_btn = make_choose_button('Выбрать файл', False)
choose_btn.grid(row=3, column=1, stick='we', padx=3, pady=3)

cipher_choose_btn = make_choose_button('Выбрать шифр. файл', True)
cipher_choose_btn.grid(row=4, column=1, stick='we', padx=3, pady=3)

open_btn = make_open_button('Открыть файл', False)
open_btn.grid(row=3, column=2, stick='we', padx=3, pady=3)

open_cipher_btn = make_open_button('Открыть шифр. файл', True)
open_cipher_btn.grid(row=4, column=2, stick='we', padx=3, pady=3)

Button(window,
       text='Зашифровать',
       bd=3,
       command=lambda: cipher_msg(),
       font=('Comic Sans MS', 10),
       bg='#AD62AA'
       ).grid(row=3, column=3, stick='we', padx=3, pady=3)

Button(window,
       text='Расшифровать',
       bd=3,
       command=lambda: decipher_msg(),
       font=('Comic Sans MS', 10),
       bg='#AD62AA'
       ).grid(row=4, column=3, stick='we', padx=3, pady=3)

# Размер кнопок
for i in range(4):
    window.grid_columnconfigure(i, minsize=100)

window.mainloop()
