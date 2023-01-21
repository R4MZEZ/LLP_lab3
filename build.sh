cd parser
yacc -d mongo.y
lex lex.l
cd ..
cmake .
make
#./LLP3 127.0.0.1
#gcc -w lex.yy.c y.tab.c -o out
#./out < query.ms
#rm lex.yy.c y.tab.c y.tab.h out