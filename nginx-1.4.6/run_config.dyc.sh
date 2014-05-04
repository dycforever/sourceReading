#!/bin/bash
PREFIX=/home/dyc/tools
./configure --prefix=$PREFIX/nginx/ \
    --with-pcre=$PREFIX/pcre/ \
    --add-module=$PREFIX/ngx_devel_kit \
    --add-module=$PREFIX/lua-nginx-module \
    --add-module=$PREFIX/set-misc-nginx-module \
    --add-module=$PREFIX/echo-nginx-module \
    --with-debug  &&  make -j8 && make install
