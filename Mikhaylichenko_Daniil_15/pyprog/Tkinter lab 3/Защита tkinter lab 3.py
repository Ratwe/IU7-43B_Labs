"""
Зашифровывать символы в два старших бита цвета
"""
from tkinter import *
from tkinter import messagebox as box
from PIL import Image


def make_open_button(string, cipher_check):
    return Button(window, text=string, command=lambda: open_file(cipher_check))


def create_name(path):
    global i
    for i in range(len(path) - 1, -1, -1):
        if path[i] == '/' or path[i] == 0:
            break
    return 'ciphered_{}'.format(path[i:])


def get_bin_symbol_from_text(text):
    for symbol in text:
        bin_symbol = bin(ord(symbol))[2:]
        while len(bin_symbol) < 8:
            bin_symbol = '0' + bin_symbol
        bits_list = [
            bin_symbol[0], bin_symbol[1], bin_symbol[2], bin_symbol[3],
            bin_symbol[4], bin_symbol[5], bin_symbol[6], bin_symbol[7]
        ]
        yield bits_list


def new_coordinates(x, y, img):
    length, width = img.size
    x += 1
    if x == length:
        x = 0
        y += 1
        if y > width:
            print('Error')
    return x, y


def new_color(r, g, b, v, bin_symbol):
    # print('1. r = {}, g = {}, b = {}, v = {}'.format(r, g, b, v))
    rf_add = bin_symbol[0]
    rs_add = bin_symbol[1]
    gf_add = bin_symbol[2]
    gs_add = bin_symbol[3]
    bf_add = bin_symbol[4]
    bs_add = bin_symbol[5]
    vf_add = bin_symbol[6]
    vs_add = bin_symbol[7]
    # print('- rf_add = {}, rs_add = {}, gf_add = {}, gs_add = {}'.format(rf_add, rs_add, gf_add, gs_add))
    # print('- bf_add = {}, bs_add = {}, vf_add = {}, vs_add = {}'.format(bf_add, bs_add, vf_add, vs_add))
    while len(rf_add) < 8:
        rf_add += '0'
    while len(rf_add) < 7:
        rs_add += '0'
    while len(rf_add) < 8:
        gf_add += '0'
    while len(rf_add) < 7:
        gs_add += '0'
    while len(rf_add) < 8:
        bf_add += '0'
    while len(rf_add) < 7:
        bs_add += '0'
    while len(rf_add) < 8:
        vf_add += '0'
    while len(rf_add) < 7:
        vs_add += '0'
    # print('- rf_add = {}, rs_add = {}, gf_add = {}, gs_add = {}'.format(rf_add, rs_add, gf_add, gs_add))
    # print('- bf_add = {}, bs_add = {}, vf_add = {}, vs_add = {}'.format(bf_add, bs_add, vf_add, vs_add))
    r += int(('0b' + rf_add), 2)
    r += int(('0b' + rs_add), 2)
    g += int(('0b' + gf_add), 2)
    g += int(('0b' + gs_add), 2)
    b += int(('0b' + bf_add), 2)
    b += int(('0b' + bs_add), 2)
    v -= int(('0b' + vf_add), 2)
    v -= int(('0b' + vs_add), 2)
    # print('2. r = {}, g = {}, b = {}, v = {}'.format(r, g, b, v))
    return r, g, b, v


def paint_pixel(bin_symbol, img, x, y):
    pxl = img.getpixel((x, y))
    r, g, b, v = pxl[0], pxl[1], pxl[2], pxl[3]
    # print('>', r, bin(r))
    r, g, b, v = new_color(r, g, b, v, bin_symbol)
    # print('>>', r, bin(r))
    img.putpixel((x, y), (r, g, b, v))
    return img


def open_file(cipher_check):
    if cipher_check:
        path = cipher_path_entry.get()
    else:
        path = path_entry.get()
    try:
        img = Image.open(path)
        img.show()
    except (FileNotFoundError, AttributeError, PermissionError):
        box.showinfo('Error!', 'Оно сломалось...')


def cipher_msg():
    path = path_entry.get()
    img = Image.open(path)
    text = msg_entry.get() + '߿'
    x = y = 0
    for bin_symbol in get_bin_symbol_from_text(text):
        # print('symbol = ', *bin_symbol)
        img = paint_pixel(bin_symbol, img, x, y)
        x, y = new_coordinates(x, y, img)
    new_file_name = create_name(path)
    img.save(new_file_name)
    cipher_path_entry.delete(0, END)
    cipher_path_entry.insert(0, new_file_name)


window = Tk()
window.title('Шифровщик')
window.geometry('450x150')

path_label = Label(window, text='Файл:')
path_label.grid(row=0, column=0)

cipher_path_label = Label(window, text='Шифр. файл:')
cipher_path_label.grid(row=1, column=0)

msg_label = Label(window, text='Сообщение:')
msg_label.grid(row=2, column=0)

path_entry = Entry(window, justify=LEFT)
path_entry.insert(0, 'Лемминги.png')
path_entry.grid(stick='we', row=0, column=1, columnspan=2)

cipher_path_entry = Entry(window, justify=LEFT)
cipher_path_entry.grid(stick='we', row=1, column=1, columnspan=2)

msg_entry = Entry(window, justify=LEFT)
msg_entry.insert(0, 'Я хочу пиццу!')
msg_entry.grid(stick='we', row=2, column=1, columnspan=2)

open_btn = make_open_button('Открыть файл', False)
open_btn.grid(row=3, column=1, stick='we')

open_cipher_btn = make_open_button('Открыть шифр. файл', True)
open_cipher_btn.grid(row=4, column=1, stick='we')

Button(window, text='Зашифровать', command=lambda: cipher_msg()).grid(row=3, column=2, stick='we')

for i in range(4):
    window.grid_columnconfigure(i, minsize=100)

window.mainloop()
