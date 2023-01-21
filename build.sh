cd parser
yacc -d mongo.y
lex lex.l
cd ..
cmake .
make
rm parser/lex.yy.c parser/y.tab.*
rm Makefile