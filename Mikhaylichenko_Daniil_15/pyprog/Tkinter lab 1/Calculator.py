"""
Михайличенко Даниил ИУ7-23Б

- Программа калькулятора в 6-ричной системе счисления
"""
from tkinter import *
import tkinter.messagebox as box


# Описание пункта меню "О программе..."
def description():
    box.showinfo('О программе:', 'Вариант 15\n\
                 \nСложение и вычитание вещественных чисел в 6-й системе счисления\n\
                 \n©Михайличенко Даниил ИУ7-23Б\n14.02.2022')


# Описание пункта меню "Предупреждение"
def warnings():
    box.showinfo('Предупреждение:', 'Если вы попытаесть через курсор ввести число,\
                 возможно возникновение ошибки!')


# Функция создания кнопки с числом
def make_num_button(num):
    return Button(window, text=num, bg='#f0b897', bd=3, font=('Comic Sans MS', 12), command=lambda: add_number(num))


# Функция создания кнопки операции
def make_operation_button(emoji, operation):
    return Button(window, text=emoji, bg='#edcdbb', bd=3, command=lambda: add_operation(operation))


# Функция создания кнопки "равно"
def make_equal_button(emoji):
    return Button(window, text=emoji, bg='#edcdbb', bd=3, command=lambda: equal())


# Функция счёта в 6сс
def expression(value):
    first_num, second_num = separate(value)
    if first_num[0] == '-':
        first_num = make_system_10(first_num[1:])
        first_num = float('-' + str(first_num))
    else:
        first_num = make_system_10(first_num)
    second_num = make_system_10(second_num)
    if '+' in value:
        # print('>> +')
        result = float(first_num) + float(second_num)
    elif '-' in value:
        # print('>> -')
        result = float(first_num) - float(second_num)
    else:
        result = float(first_num) + float(second_num)
    # print('result 10 {}: '.format(str(float(first_num)) + '+-' + str(float(second_num))), result)
    if str(result)[0] == '-':
        result = make_system_6(str(float(str(result)[1:])))
        result = float('-' + str(result))
    else:
        result = make_system_6(str(result))
    # print('result 6: ', result)
    if float(result) % 1 == 0:
        result = str(int(float(result)))
    return result


# Функция разделения строки на два числа
def separate(value):
    # print('OUR VALUE = {}'.format(value))
    nums = value.replace('+', ' ')
    nums = nums.replace('-', ' ')
    nums = nums.split(' ')
    # print('nums {}'.format(nums))
    if len(nums) == 3:
        first_num, second_num = '-' + nums[1], nums[2]
    elif len(nums) == 2 and nums[0] == '':
        first_num, second_num = '-' + nums[1], '0'
    elif len(nums) == 1:
        first_num, second_num = nums[0], '0'
    elif len(nums) == 4:
        first_num, second_num = '-' + nums[1], '0'
    else:
        first_num, second_num = nums[0], nums[1]
    # print('first_num: ', type(first_num), first_num, '|', 'second_num: ', type(second_num), second_num)
    return first_num, second_num


# Функция перевода в 10сс
def make_system_10(num):
    if '.' in num:
        num = num.split('.')
        int_part = num[0]
        float_part = num[1]
        int_10 = 0
        float_10 = 0
        for i in range(len(int_part)):
            int_10 += int(int_part[i]) * 6 ** (len(int_part) - i - 1)
        for i in range(1, len(float_part) + 1):
            float_10 += int(float_part[i - 1]) * (6 ** (-i))
        new_num = int_10 + float_10
        # print('10: ', type(new_num), new_num)
        return str(new_num)
    else:
        new_num = 0
        for i in range(len(num)):
            new_num += int(num[i]) * 6 ** (len(num) - i - 1)
            # print('10: ', type(new_num), new_num)
        return str(new_num)


# Функция перевода в 6сс
def make_system_6(num):
    if '.' in num:
        num = num.split('.')
        int_part = int(num[0])
        float_part = float('0.' + num[1])
        int_6 = ''
        float_6 = '0.'
        # print('/int_part_10: ', int_part, '||', 'float_part_10: ', float_part)
        while int_part > 0:
            int_6 = str(int_part % 6) + int_6
            int_part //= 6
        if int_6 == '':
            int_6 = 0
        for i in range(4):
            float_part = float_part * 6
            first_num = str(int(float_part))[0]
            float_6 += first_num
            float_part -= int(first_num)
            # print('------------', float_part)
        # print('/int_part_6: ', int_6, '||', 'float_part_6: ', float_6)
        new_num = float(int_6) + float(float_6)
        # print('6: ', type(new_num), new_num)
        return str(new_num)
    else:
        num = int(num)
        new_num = ''
        while num > 0:
            new_num = str(num % 6) + new_num
            num //= 6
        # print('6: ', type(new_num), new_num)
        return new_num


# Функция по добавлению числа на экран
def add_number(num):
    # print('>>>>>', type(calculate))
    new_num = calculate.get()
    if new_num == '0':
        new_num = new_num[1:]
    calculate.delete(0, END)
    calculate.insert(0, new_num + num)


# функция по добавлению точки на экран
def add_point():
    if calculate.get()[-1:] in '.+-':
        pass
    else:
        new_num = calculate.get() + '.'
        calculate.delete(0, END)
        calculate.insert(0, new_num)


# Функция по добавлению операции на экран
def add_operation(operation):
    value = calculate.get()
    # print('VALUE = {}'.format(value), 'counter = {}'.format(value.count('-')))
    if value[-1] == '.':
        return
    if value[-1] in '+-':
        value = value[:-1]
    elif '-' in value or '+' in value:
        equal()
        value = calculate.get()
    calculate.delete(0, END)
    calculate.insert(0, value + operation)


# Функция по удалению последнего или всех чисел
def delete(All):
    if All:
        calculate.delete(0, END)
        calculate.insert(0, 0)
    else:
        new_string = calculate.get()[:-1]
        if new_string == '':
            new_string = '0'
        calculate.delete(0, END)
        calculate.insert(0, new_string)


# Функция работы кнопки равно
def equal():
    value = calculate.get()
    if value[-1] in '+-':
        value += value[:-1]
    calculate.delete(0, END)
    # print(expression(value))
    if '6' in value or '7' in value or '8' in value or '9' in value:
        box.showinfo('Внимание!', 'Вы ввели недопустимые символы!\n\n(Или поставили несколько точек)')
        calculate.insert(0, 0)
        return
    try:
        eval(value)
    except (NameError, SyntaxError):
        box.showinfo('Внимание!', 'Вы ввели недопустимые символы!\n\n(Или поставили несколько точек)')
        calculate.insert(0, 0)
    else:
        calculate.insert(0, expression(value))


# функция ввода с клавиатуры
def press_key(key):
    # print(repr(key.char))
    if key.char in '012345':
        add_number(key.char)
    elif key.char in '+-':
        add_operation(key.char)
    elif key.char == '.':
        add_point()
    elif key.char == '=' or key.char == '\r':
        equal()
    elif key.char == '\x08':
        delete(False)


# Создание окна
window = Tk()
window.title('Калькулятор 6cc')
window.geometry('325x248+200+200')
window['bg'] = '#bf9270'

# Создание пункта меню
mainmenu = Menu(window)
window.config(menu=mainmenu)
mainmenu.add_cascade(label='О программе...', command=description)
mainmenu.add_cascade(label='Предупреждение', command=warnings)

# Считывание нажатий кнопок клавиатуры
window.bind('<Key>', press_key)

# Создание поля ввода
calculate = Entry(window, justify=RIGHT, bg='#ffedd8', font=('Arial', 22))
calculate.insert(0, '0')
calculate.grid(row=0, column=0, columnspan=4)

# создание кнопок удаления
Button(window, text='C', bg='#edcdbb', bd=3, command=lambda: delete(True)).grid(row=1, column=0,
                                                                                stick='wens', padx=3,
                                                                                pady=3)
Button(window, text='◀', bg='#edcdbb', bd=3, command=lambda: delete(False)).grid(row=1, column=3,
                                                                                 stick='wens', padx=3, pady=3)

# Создание кнопок операций
make_operation_button('➖', '-').grid(row=1, column=2, stick='wens', padx=3, pady=3)
make_operation_button('➕', '+').grid(row=1, column=1, stick='wens', padx=3, pady=3)
make_equal_button('=').grid(row=2, column=3, stick='wens', padx=3, pady=3)

# Создание кнопок с числами
make_num_button('0').grid(row=3, column=0, stick='wens', padx=3, pady=3)
make_num_button('1').grid(row=3, column=1, stick='wens', padx=3, pady=3)
make_num_button('2').grid(row=3, column=2, stick='wens', padx=3, pady=3)
make_num_button('3').grid(row=2, column=0, stick='wens', padx=3, pady=3)
make_num_button('4').grid(row=2, column=1, stick='wens', padx=3, pady=3)
make_num_button('5').grid(row=2, column=2, stick='wens', padx=3, pady=3)
Button(window, text='.', bg='#edcdbb', bd=3, command=lambda: add_point()) \
    .grid(row=3, column=3, stick='wens', padx=3, pady=3)

# Размер кнопок
for i in range(4):
    window.grid_columnconfigure(i, minsize=70)
for i in range(1, 6):
    window.grid_rowconfigure(i, minsize=70)

window.mainloop()
