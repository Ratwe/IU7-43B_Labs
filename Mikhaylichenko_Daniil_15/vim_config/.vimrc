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
set listchars=tab:▷▷⋮
set invlist

"Мышка
set mouse=a

"Перенос строки
set colorcolumn=80
set whichwrap+=<,>,[,]

"Перемещение по вкладкам
nnoremap <C-L> :bnext<CR>
nnoremap <C-K> :bprevious<CR>

"Плагины
filetype plugin indent on

if empty(glob('~/.vim/autoload/plug.vim'))
  silent !curl -fLo ~/.vim/autoload/plug.vim --create-dirs
    \ https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim 
  autocmd VimEnter * PlugInstall --sync | source $MYVIMRC
endif

"Подключаемые плагины
call plug#begin('~/.vim/bundle')
    Plug 'vim-airline/vim-airline'      "Строка состояния
    "Plug 'ryanoasis/vim-devicons'
    Plug 'preservim/nerdtree'           "Дерево
    Plug 'Xuyuanp/nerdtree-git-plugin'  "git в дереве
    Plug 'farmergreg/vim-lastplace'     "Возвращение к последнему месту при открытии файла
    Plug 'preservim/tagbar'             "Для классов 
    Plug 'tpope/vim-commentary'         "Комментирование нескольких строк разом
    Plug 'lilydjwg/colorizer'           "Подсветка цветов
    Plug 'natebosch/vim-lsc'            "Работа сервера с vimом
    Plug 'ycm-core/YouCompleteMe'       "Дополнение
    Plug 'morhetz/gruvbox'              "Тема gruvbox
    Plug 'tomasiser/vim-code-dark' 
    "Plug 'itchyny/lightline.vim'
    "Plug 'ap/vim-buftabline'
    Plug 'Dimercel/todo-vim'
    "Plug 'Yggdroot/indentLine'
    Plug 'joshdick/onedark.vim'
call plug#end()

"Строка состояния
let g:airline_powerline_fonts = 1
let g:airline#extensions#keymap#enabled = 0
let g:airline#extensions#tabline#enabled = 1
let g:airline_section_z = "\ue0a1:%l/%L Col:%c"
let g:Powerline_symbols='unicode'
let g:airline#extensions#xkblayout#enabled = 0

"Дополнение
let g:ycm_clangd_uses_ycmd_caching = 0
let g:ycm_clangd_binary_path = exepath("clangd")

"Сервер
set completeopt-=preview

"autocmd FileType vim setlocal foldmethod=marker
autocmd VimEnter * NERDTree | wincmd p
autocmd FileType apache setlocal commentstring=#\ %s

"Тема
syntax enable
packadd! dracula
packadd! doki-theme
"colorscheme dracula
"highlight Normal ctermfg=white ctermbg=black
colorscheme gruvbox
set background=dark

"set termguicolors
