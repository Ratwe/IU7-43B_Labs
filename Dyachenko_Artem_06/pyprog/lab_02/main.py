from tkinter import *
from tkinter.ttk import Entry, Label, Frame, Scrollbar, Button

import matplotlib.pyplot as plt
import numpy as np

from sympy import *
import tkinter as tk

win = tk.Tk()
ent1 = Entry(width=20)
ent2 = Entry(width=20)
ent3 = Entry(width=20)
ent4 = Entry(width=20)
ent5 = Entry(width=20)
ent6 = Entry(width=20)
table_frame = Frame(win)
table_scroll = Scrollbar(table_frame)
table = ttk.Treeview(table_frame, yscrollcommand=table_scroll.set)

roots = []
extremums = []
bends = []


def diff(n, func):
    x = Symbol('x')
    y = eval(func)

    diffed = y.diff(x)
    f = lambdify(x, diffed)

    # print("[DB]: f'(", n, ") = ", f(n), sep='')
    return f(n)


def diff2(n, func):
    x = Symbol('x')
    y = eval(func)

    diffed = y.diff(x)
    # print("[DB]: diffed =", diffed)

    y = eval(str(diffed))
    diffed = y.diff(x)
    f = lambdify(x, diffed)

    # print("[DB]: f'(", n, ") = ", f(n), sep='')
    return f(n)


def root(a, b, eps, n_max, func):
    # print("[DB]: eps = {0}, n_max = {1}".format(eps, n_max))
    # вычисление корней
    x = Symbol('x')
    f = lambdify(x, func)  # сделали функцию
    it = 0

    # комбинированный метод
    while it < n_max:
        if not diff(a, func) or not diff(b, func) or not (f(a) - f(b)):  # деление на 0
            it += 1
            continue

        if f(a) * diff2(a, func) < 0:
            a -= f(a) * (a - b) / (f(a) - f(b))
        elif f(a) * diff2(a, func) > 0:
            a -= f(a) / diff(a, func)

        if f(b) * diff2(b, func) < 0:
            b -= f(b) * (b - a) / (f(b) - f(a))
        elif f(b) * diff2(b, func) > 0:
            b -= f(b) / diff(b, func)

        it += 1
        if abs(a - b) < 2 * eps:
            return 0, float((a + b) / 2), it

    return 2, '-', it


def calc():
    table.delete(*table.get_children())

    func = ent1.get()
    a = float(ent2.get())
    b = float(ent3.get())
    h = float(ent4.get())
    n_max = int(ent5.get())
    eps = float(ent6.get())
    eeps = h/2

    roots.clear()
    extremums.clear()
    bends.clear()

    cur = a
    num = 1
    while cur < b - h / 2:
        err, x, it = root(cur, cur + h, eps, n_max, func)
        xp = Symbol('x')
        f = lambdify(xp, func)

        if f(cur) * f(cur + h) > 0:
            # ("[DB]: diff({0}) = {1}, diff({2}) = {3}".format(f(cur), diff(f(cur), func), f(cur + h), diff(f(cur + h), func)))
            # if diff(f(cur)) > 0 and f(cur) > f(cur + h * 0.9):  # точки экстремума
            #     extremums.append(cur + h / 2)
            # elif diff(f(cur)) < 0 and f(cur) < f(cur + h * 0.9):  # точки экстремума
            #     extremums.append(cur + h / 2)
            if abs(diff(cur + h / 2, func)) < eeps:  # точки экстремума
                extremums.append(cur + h / 2)
            print(round(cur, 2), abs(diff2(f(cur + h / 2), func)))
            if abs(diff2(f(cur + h / 2), func)) < eeps:  # точки перегиба
                bends.append(cur + h / 2)
            cur += h
            continue

        if err:
            x = '-'
            f_x = '-'
        else:
            f_x = f(x)
            roots.append(x)
            if abs(diff(cur + h / 2, func)) < eeps:  # точки экстремума
                extremums.append(cur + h / 2)
            if abs(diff2(f(cur + h / 2), func)) < eeps:  # точки перегиба
                bends.append(cur + h / 2)

        try:
            table.insert(parent='', index='end', text='',
                         values=(num, '[' + str(round(cur, 1)) + ', ' + str(round(cur + h, 1))
                                 + ']', round(x, 3), round(f_x, 3), it, err))
        except:
            table.insert(parent='', index='end', text='',
                         values=(num, '[' + str(round(cur, 1)) + ', ' + str(round(cur + h, 1))
                                 + ']', '-', '-', it, err))
        cur += h
        num += 1

    table.pack()


def plot():
    func = ent1.get()
    a = int(ent2.get())
    b = int(ent3.get())

    x = Symbol('x')
    f = lambdify(x, func)

    # график
    X = np.linspace(a, b, int((b - a) * 1000))
    Y = [f(i) for i in X]
    Y = np.array(Y)

    # корни
    XR = np.array(roots)
    YR = [f(i) for i in XR]
    YR = np.array(YR)

    # экстремумы
    XE = np.array(extremums)
    YE = [f(i) for i in XE]
    YE = np.array(YE)

    # точки перегиба
    XB = np.array(bends)
    YB = [f(i) for i in XB]
    YB = np.array(YB)
    print("[DB]: bends ", bends)

    # легенда и оси
    plt.xlabel('ось x', color='gray')
    plt.ylabel('ось y', color='gray')

    plt.axis([a, b, min(Y) * 1.3, max(Y) * 1.3])
    plt.title('График')
    plt.plot(X, Y, 'g', XR, YR, 'ro', XE, YE, 'yp', XB, YB, 'bd')

    plt.plot(X, Y, 'g', label='f(x)')
    plt.plot(XR, YR, 'ro', label='корни')
    plt.plot(XE, YE, 'yp', label='критические точки')
    plt.plot(XB, YB, 'bd', label='точки перегиба')
    plt.legend(title='Легенда', title_fontsize='10', loc=1)
    plt.show()


def main():
    win.title('ЛР 2, Дьяченко Артём ИУ7-23Б')
    win.geometry('1080x720')
    win.resizable(False, False)

    # ввод значений
    enter = Label(win, text="Введите функцию:")
    enter.grid(row=0, column=0)

    ent1.grid(row=0, column=1)
    ent1.insert(0, "sin(x)")
    func = ent1.get()

    enter = Label(win, text="Введите начало отрезка:")
    enter.grid(row=1, column=0)

    ent2.grid(row=1, column=1)
    ent2.insert(0, "-10")
    a = float(ent2.get())

    enter = Label(win, text="Введите конец отрезка:")
    enter.grid(row=2, column=0)

    ent3.grid(row=2, column=1)
    ent3.insert(0, "10")
    b = float(ent3.get())

    enter = Label(win, text="Введите шаг:")
    enter.grid(row=3, column=0)

    ent4.grid(row=3, column=1)
    ent4.insert(0, "0.05")
    h = float(ent4.get())

    enter = Label(win, text="Введите максимум итераций:")
    enter.grid(row=4, column=0)

    ent5.grid(row=4, column=1)
    ent5.insert(0, "3")
    n_max = int(ent5.get())

    enter = Label(win, text="Введите точность:")
    enter.grid(row=5, column=0)

    ent6.grid(row=5, column=1)
    ent6.insert(0, "0.01")
    eps = float(ent6.get())

    # вывод таблицы
    # print("| Номер |     [xi, xi+1]     |    x'   |  f(x')  | Итераций | Код ошибки |")
    # print("-" * 73)
    # cur = a
    # num = 1
    # while cur <= b + h / 2:
    #     err, x, it = root(cur, cur + h, eps, n_max, func)
    #     xp = Symbol('x')
    #     f = lambdify(xp, func)
    #     if err:
    #         x = '-'
    #         f_x = '-'
    #     else:
    #         f_x = f(x)
    #     print("| {:^5d} | [{:^7.3f}, {:^7.3f}] | {:^7.3} | {:^7.3} | {:^8d} | {:^10} |".format(num, cur, cur + h, x,
    #                                                                                              f_x, it, err))
    #     cur += h
    #     num += 1

    table_frame.grid(row=0, column=8, columnspan=2, rowspan=4)

    for i in range(3):
        win.grid_columnconfigure(i, minsize=100)

    for i in range(6):
        win.grid_rowconfigure(i, minsize=50)

    table['columns'] = ('#', '[a, b]', "x'", "f(x')", 'Итераций', 'Код')

    table.column("#0", width=0, stretch=NO)
    table.column("#", anchor=CENTER, width=80)
    table.column("[a, b]", anchor=CENTER, width=80)
    table.column("x'", anchor=CENTER, width=80)
    table.column("f(x')", anchor=CENTER, width=80)
    table.column("Итераций", anchor=CENTER, width=80)
    table.column("Код", anchor=CENTER, width=50)

    table.heading("#0", text="", anchor=CENTER)
    table.heading("#", text="#", anchor=CENTER)
    table.heading("[a, b]", text="[a, b]", anchor=CENTER)
    table.heading("x'", text="x'", anchor=CENTER)
    table.heading("f(x')", text="f(x')", anchor=CENTER)
    table.heading("Итераций", text="Итераций", anchor=CENTER)
    table.heading("Код", text="Код", anchor=CENTER)

    # кнопка построения таблицы
    btn_calc = Button(win, text='Вычислить', command=calc)
    btn_calc.grid(row=6, column=0)

    # кнопка построения таблицы
    btn_plot = Button(win, text='График', command=plot)
    btn_plot.grid(row=6, column=1)

    table.pack()
    win.mainloop()


main()

