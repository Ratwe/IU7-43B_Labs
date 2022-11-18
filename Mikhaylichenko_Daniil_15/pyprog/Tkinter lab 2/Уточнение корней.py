from tkinter import *
from tkinter.ttk import Treeview, Scrollbar
import tkinter.messagebox as box

from PIL import Image, ImageTk
from sympy import *
import numpy
import matplotlib.pyplot as plt
from settings import *


# Описание программы
def description():
    box.showinfo('О программе:', 'Вариант 6\n\
                 \nУточнение корней комбинированным методом\n\
                 \n©Михайличенко Даниил ИУ7-23Б\n14.03.2022')


# Создание объектов в окне
def make_object(obj_window, obj_type, obj_width, obj_height, obj_x, obj_y, **obj_args):
    frame = Frame(obj_window, width=obj_width, height=obj_height)
    frame.pack_propagate(False)
    frame.place(x=obj_x, y=obj_y)

    obj = obj_type(frame, obj_args)
    obj.pack(fill=BOTH, expand=True)
    return obj


def make_table(tbl_window, tbl_width, tbl_height, tbl_x, tbl_y, **tbl_args):
    tbl_frame = Frame(tbl_window, width=tbl_width, height=tbl_height)
    tbl_frame.pack_propagate(False)
    tbl_frame.place(x=tbl_x, y=tbl_y)

    table_scroll = Scrollbar(tbl_frame)
    tbl = Treeview(tbl_frame, yscrollcommand=table_scroll.set)
    tbl.pack(fill=BOTH, expand=True)
    return tbl


# Функция ввода с клавиатуры
def press_key(key):
    # print(repr(key.char))
    if key.char == '\r':
        main(True)
    elif key.char == '\n':
        main(False)
    elif key.char == '\x1b':
        exit()


def turn_on_interface(on):
    global interface
    if on:
        interface = True
    else:
        interface = False
    print(interface)


def diff1(func, n):
    x = Symbol('x')
    y = eval(func)
    f = lambdify(x, y.diff(x))

    return f(n)


def diff2(func, n):
    x = Symbol('x')
    y = eval(func)
    y = eval(str(y.diff(x)))
    f = lambdify(x, y.diff(x))

    return f(n)


def calc_root(func, a, b, eps, nmax):
    f = lambdify(Symbol('x'), func)
    it = 0

    while it < nmax:
        if diff1(func, a) == 0 or diff1(func, b) == 0 or (f(a) - f(b)) == 0:
            it += 1
            continue

        if f(a) * diff2(func, a) > 0:
            a -= f(a) / diff1(func, a)
        elif f(a) * diff2(func, a) < 0:
            a -= f(a) * (a - b) / (f(a) - f(b))
        else:
            break

        if f(b) * diff2(func, b) > 0:
            b -= f(b) / diff1(func, b)
        elif f(b) * diff2(func, b) < 0:
            b -= f(b) * (b - a) / (f(b) - f(a))
        else:
            break

        it += 1

        if abs(a - b) < 2 * eps:
            return float((a + b) / 2), it, 0

    return '-', it, 1


def calc(table, func_entry, a_entry, b_entry, h_entry, eps_entry, nmax_entry, rts, extrs, bends):
    table.delete(*table.get_children())
    rts.clear()
    extrs.clear()
    bends.clear()

    func = func_entry.get()
    a = float(a_entry.get())
    b = float(b_entry.get())
    h = float(h_entry.get())
    eps = float(eps_entry.get())
    nmax = int(nmax_entry.get())

    temp, i = a, 1

    while temp < b - h / 2:
        x, it, err = calc_root(func, temp, temp + h, eps, nmax)
        f = lambdify(Symbol('x'), func)

        if f(temp) * f(temp + h) > 0:
            if abs(diff1(func, temp + h / 2)) < h / 2:
                extrs += [(temp + h / 2)]
            if abs(diff2(func, f(temp + h / 2))) < h / 2:
                bends += [(temp + h / 2)]

        if err:
            fx = xr = '-'
        else:
            xr = round(x, 3)
            fx = round(f(x), 3)
            if abs(diff1(func, temp + h / 2)) < h / 2:
                extrs += [(temp + h / 2)]
            if abs(diff2(func, f(temp + h / 2))) < h / 2:
                bends += [(temp + h / 2)]

            rts += [x]

        x1, x2 = str(round(temp, 2)), str(round(temp + h, 2))

        table.insert(parent='', index='end', text='',
                     values=(i, '[{}, {}]'.format(x1, x2), xr, fx, it, err))

        temp += h
        i += 1

    table.pack()


def graph(window, func_entry, a_entry, b_entry, rts, extrs, bends, canvas):

    func = func_entry.get()
    a, b = int(a_entry.get()), int(b_entry.get())

    f = lambdify(Symbol('x'), func)

    xs = numpy.linspace(a, b, abs(a - b) * 1000)
    ys = numpy.array([f(i) for i in xs])

    xr = numpy.array(rts)
    yr = numpy.array([f(i) for i in xr])

    xe = numpy.array(extrs)
    ye = numpy.array([f(i) for i in xe])

    xb = numpy.array(bends)
    yb = numpy.array([f(i) for i in xb])

    plt.figure(figsize=(9.8, 4.6))

    plt.plot(xs, ys, label='f(x)')
    plt.plot(xr, yr, 'o', label='Корни')
    plt.plot(xe, ye, 'rp', label='Критические точки')
    plt.plot(xb, yb, 'gd', label='Точки перегиба')
    plt.axis((a, b, min(ys) * 2, max(ys) * 2))

    plt.xlabel('ось x', color='gray')
    plt.ylabel('ось y', color='gray')

    plt.title('График {}'.format(func))
    plt.legend(title='Легенда', title_fontsize='10', loc=1)

    print(interface)
    if not interface:
        plt.savefig('graph.png')
        photo = ImageTk.PhotoImage(Image.open("graph.png"))
        canvas.create_image(0, 0, anchor='nw', image=photo)
        plt.close()
        window.mainloop()
    else:
        plt.show()


def main():
    rts = list()
    extrs = list()
    bends = list()

    global interface
    interface = False

    # Создание окна
    window = Tk()
    window.title('Вычисление корней')
    window.geometry(SIZE)
    window['bg'] = LIGHTBLUE

    # Считывание нажатий кнопок клавиатуры
    window.bind('<Key>', press_key)

    # Создание пункта меню
    mainmenu = Menu(window)
    window.config(menu=mainmenu)

    graphmenu = Menu(mainmenu, tearoff=0)
    graphmenu.add_command(label="Graph interface on", command=lambda: turn_on_interface(True))
    graphmenu.add_command(label="Graph interface off", command=lambda: turn_on_interface(False))

    mainmenu.add_cascade(label="Настройки", menu=graphmenu)
    mainmenu.add_cascade(label='О программе...', command=description)

    # Создание лейблов
    make_object(window, Label, LABEL_WIDTH, LABEL_HEIGHT, LABEL_X, LABEL_Y,
                text="Функция f(x):", bg=LIGHTBLUE)
    make_object(window, Label, LABEL_WIDTH, LABEL_HEIGHT, LABEL_X, LABEL_Y + LABEL_HEIGHT + 2,
                text="Начало отрезка [a, b]:", bg=LIGHTBLUE)
    make_object(window, Label, LABEL_WIDTH, LABEL_HEIGHT, LABEL_X, LABEL_Y + LABEL_HEIGHT * 2 + 4,
                text="Конец отрезка [a, b]:", bg=LIGHTBLUE)
    make_object(window, Label, LABEL_WIDTH, LABEL_HEIGHT, LABEL_X, LABEL_Y + LABEL_HEIGHT * 3 + 6,
                text="Шаг h:", bg=LIGHTBLUE)
    make_object(window, Label, LABEL_WIDTH, LABEL_HEIGHT, LABEL_X, LABEL_Y + LABEL_HEIGHT * 4 + 8,
                text="Точность eps:", bg=LIGHTBLUE)
    make_object(window, Label, LABEL_WIDTH, LABEL_HEIGHT, LABEL_X, LABEL_Y + LABEL_HEIGHT * 5 + 10,
                text="Кол-во итерация Nmax:", bg=LIGHTBLUE)

    # Создание полей ввода
    func_entry = make_object(window, Entry, ENTRY_WIDTH, ENTRY_HEIGHT, ENTRY_X, ENTRY_Y,
                             justify=RIGHT)
    a_entry = make_object(window, Entry, ENTRY_WIDTH, ENTRY_HEIGHT, ENTRY_X, ENTRY_Y + ENTRY_HEIGHT + 2,
                          justify=RIGHT)
    b_entry = make_object(window, Entry, ENTRY_WIDTH, ENTRY_HEIGHT, ENTRY_X, ENTRY_Y + ENTRY_HEIGHT * 2 + 4,
                          justify=RIGHT)
    h_entry = make_object(window, Entry, ENTRY_WIDTH, ENTRY_HEIGHT, ENTRY_X, ENTRY_Y + ENTRY_HEIGHT * 3 + 6,
                          justify=RIGHT)
    eps_entry = make_object(window, Entry, ENTRY_WIDTH, ENTRY_HEIGHT, ENTRY_X, ENTRY_Y + ENTRY_HEIGHT * 4 + 8,
                            justify=RIGHT)
    nmax_entry = make_object(window, Entry, ENTRY_WIDTH, ENTRY_HEIGHT, ENTRY_X, ENTRY_Y + ENTRY_HEIGHT * 5 + 10,
                             justify=RIGHT)

    # Создание кнопок
    make_object(window, Button, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON1_X, BUTTON_Y,
                text="Посчитать",
                bg=YELLOW,
                command=lambda: calc(table, func_entry, a_entry, b_entry, h_entry, eps_entry, nmax_entry,
                                     rts, extrs, bends))
    make_object(window, Button, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON2_X + 10, BUTTON_Y,
                text="График",
                bg=YELLOW,
                command=lambda: graph(window, func_entry, a_entry, b_entry,
                                      rts, extrs, bends, canvas))

    # Создание таблицы
    table = make_table(window, TABLE_WIDTH, TABLE_HEIGHT, TABLE_X, TABLE_Y)

    table['columns'] = ('№', 'xs', 'x', 'f', 'it', 'er')

    table.heading('№', text='№', anchor=CENTER)
    table.heading('xs', text=u'[x\u1D62, x\u1D62\u208A\u2081]', anchor=CENTER)
    table.heading('x', text='x\'', anchor=CENTER)
    table.heading('f', text='f(x\')', anchor=CENTER)
    table.heading('it', text='N', anchor=CENTER)
    table.heading('er', text='Код', anchor=CENTER)

    table.column('#0', width=0, stretch=NO)
    table.column('№', anchor=CENTER, width=60)
    table.column('xs', anchor=CENTER, width=60)
    table.column('x', anchor=CENTER, width=60)
    table.column('f', anchor=CENTER, width=60)
    table.column('it', anchor=CENTER, width=60)
    table.column('er', anchor=CENTER, width=40)

    # Базовые значения
    func_entry.insert(0, 'sin(x)')
    a_entry.insert(0, '-10')
    b_entry.insert(0, '10')
    h_entry.insert(0, '0.5')
    eps_entry.insert(0, '0.01')
    nmax_entry.insert(0, '10')

    canvas = make_object(window, Canvas, GRAPH_WIDTH, GRAPH_HEIGHT, GRAPH_X, GRAPH_Y)
    photo = ImageTk.PhotoImage(Image.open("origin.png"))
    canvas.create_image(0, 0, anchor='nw', image=photo)

    window.mainloop()


if __name__ == '__main__':
    main()
