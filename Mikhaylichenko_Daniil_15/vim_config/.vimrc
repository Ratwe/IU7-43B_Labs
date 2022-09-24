"Кодировка
set encoding=UTF-8
set nocompatible

"Нумерация строк
set number

"Табы
set expandtab
set smarttab
set tabstop=4
set softtabstop=4
set shiftwidth=4

"Мышка
set mouse=a

"Перенос строки
set colorcolumn=80
set whichwrap+=<,>,[,]

"Плагины
filetype plugin indent on

"Тема
packadd! dracula
packadd! doki-theme
syntax enable
colorscheme ram

if empty(glob('~/.vim/autoload/plug.vim'))
  silent !curl -fLo ~/.vim/autoload/plug.vim --create-dirs
    \ https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim 
  autocmd VimEnter * PlugInstall --sync | source $MYVIMRC
endif

"Подключаемые плагины
call plug#begin('~/.vim/bundle')
    Plug 'vim-airline/vim-airline'      "Строка состояния
    "Plug 'ryanoasis/vim-devicons'      "Иконки
    Plug 'arcticicestudio/nord-vim'     "Тема норд
    Plug 'preservim/nerdtree'           "Дерево
    Plug 'Xuyuanp/nerdtree-git-plugin'  "git в дереве
    Plug 'frazrepo/vim-rainbow'         "Разный цвет скобок
    Plug 'joshdick/onedark.vim'         "Тема атома
    Plug 'farmergreg/vim-lastplace'     "Возвращение к последнему месту при открытии файла
    "Plug 'preservim/tagbar'            "Для классов 
    Plug 'tpope/vim-commentary'         "Комментирование нескольких строк разом
    Plug 'lilydjwg/colorizer'           "Подсветка цветов
    Plug 'ervandew/supertab'            "Дополнение
    Plug 'jaxbot/semantic-highlight.vim'
call plug#end()

"Строка состояния
let g:airline_powerline_fonts = 1
let g:airline#extensions#keymap#enabled = 0
let g:airline#extensions#tabline#enabled = 1
let g:airline_section_z = "\ue0a1:%l/%L Col:%c"
let g:Powerline_symbols='unicode'
let g:airline#extensions#xkblayout#enabled = 0
"let g:rainbow_active = 1 "Радужная подсветка скобок

"autocmd FileType vim setlocal foldmethod=marker
autocmd VimEnter * NERDTree | wincmd p
autocmd FileType apache setlocal commentstring=#\ %s
