#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

void azzera( char griglia[10][10] );
void stampa( char griglia1[10][10], char griglia2[10][10] );
void stampaSingolo( char griglia1[10][10] );
void mettiNaviAuto( char griglia[10][10] );
void mettiNaviManuale( char griglia[10][10] );
int vive( char griglia[10][10] );
void sparo( char attacco[10][10], char naviPc[10][10] );
int sparoPc( char attaccoPc[10][10], char navi[10][10] );
int sparoPcAffondare( char attaccoPc[10][10], char navi[10][10] );
void intelligenza( char griglia[10][10] );
int affondato( char navi[10][10] );
void pulizia( char attacco[10][10] );

void azzera( char griglia[10][10] )
{
   int i, j;
   for( i = 0; i < 10; ++i )
      for( j = 0; j < 10; ++j )
         griglia[i][j] = '.';
}

void stampa( char griglia1[10][10], char griglia2[10][10])
{
   int i, j;

   printf("  ");
   for( i = 0; i < 10; ++i )
      printf("%d ", i );
   printf("\t\t");
   printf("  ");
   for( i = 0; i < 10; ++i )
      printf("%d ", i );
   printf("\n");

   for( i = 0; i < 10; ++i ) {
      printf("%d ", i );
      for( j = 0; j < 10; ++j )
         printf("%c ", griglia1[i][j] );  
      printf("\t\t"); 
      printf("%d ", i );
      for( j = 0; j < 10; ++j )
         printf("%c ", griglia2[i][j] );
      printf("\n");
   }
   printf("\n");
}

void stampaSingolo( char griglia[10][10] )
{
   int i, j;

   printf("  ");
   for( i = 0; i < 10; ++i )
      printf("%d ", i );
   printf("\n");

   for( i = 0; i < 10; ++i ) {
      printf("%d ", i );
      for( j = 0; j < 10; ++j )
         printf("%c ", griglia[i][j] ); 
      printf("\n");
   }
}

void mettiNaviAuto( char griglia[10][10] )
{
   int i, a, b;
   int incrociato;
   int orizzontale;
   srand( time( NULL ) );
   
   // nave da 5
   if( rand() % 2 ) {   // decide se è orizzontale o verticale, si orizzontale, no verticale
      a = rand() % 10;
      b = rand() % 6;
      for( i = b; i < ( b + 5 ); ++i )
         griglia[a][i] = '#';
   }
   else {
      a = rand() % 6;
      b = rand() % 10;  
      for( i = a; i < ( a + 5 ); ++i )
         griglia[i][b] = '#';    
   }

   // nave da 4
   do {
      incrociato = 0;
      if( rand() % 2 ) {   // decide se è orizzontale o verticale, si orizzontale, no verticale
         do {
         orizzontale = 1;
         a = rand() % 10;
         b = rand() % 7;
      }while( griglia[a][b] == '#' || griglia[a-1][b-1] == '#' || griglia[a-1][b] == '#' || griglia[a-1][b+1] == '#' || griglia[a][b-1] == '#' || griglia[a][b+1] == '#' || griglia[a+1][b-1] == '#' || griglia[a+1][b] == '#' || griglia[a+1][b+1] == '#' );
      for( i = b; i < ( b + 4 ); ++i )
         if( griglia[a][i] == '#' || griglia[a-1][i-1] == '#' || griglia[a-1][i] == '#' || griglia[a-1][i+1] == '#' || griglia[a][i-1] == '#' || griglia[a][i+1] == '#' || griglia[a+1][i-1] == '#' || griglia[a+1][i] == '#' || griglia[a+1][i+1] == '#' )
            incrociato = 1;
      }
      else {
         orizzontale = 0;
         do {
            a = rand() % 7;
            b = rand() % 10;
         }while( griglia[a][b] == '#' || griglia[a-1][b-1] == '#' || griglia[a-1][b] == '#' || griglia[a-1][b+1] == '#' || griglia[a][b-1] == '#' || griglia[a][b+1] == '#' || griglia[a+1][b-1] == '#' || griglia[a+1][b] == '#' || griglia[a+1][b+1] == '#' );       
         for( i = a; i < ( a + 4 ); ++i )
            if( griglia[i][b] == '#' || griglia[i-1][b-1] == '#' || griglia[i-1][b] == '#' || griglia[i-1][b+1] == '#' || griglia[i][b-1] == '#' || griglia[i][b+1] == '#' || griglia[i+1][b-1] == '#' || griglia[i+1][b] == '#' || griglia[i+1][b+1] == '#' )
               incrociato = 1;   
      }
   }while( incrociato == 1 );

   if( orizzontale ) {
      for( i = b; i < ( b + 4 ); ++i )
         griglia[a][i] = '#';
   }
   else { 
      for( i = a; i < ( a + 4 ); ++i )
         griglia[i][b] = '#';  
   }

   // nave da 3
   do {
      incrociato = 0;
      if( rand() % 2 ) {   // decide se è orizzontale o verticale, si orizzontale, no verticale
         do {
         orizzontale = 1;
         a = rand() % 10;
         b = rand() % 8;
      }while( griglia[a][b] == '#' || griglia[a-1][b-1] == '#' || griglia[a-1][b] == '#' || griglia[a-1][b+1] == '#' || griglia[a][b-1] == '#' || griglia[a][b+1] == '#' || griglia[a+1][b-1] == '#' || griglia[a+1][b] == '#' || griglia[a+1][b+1] == '#' );
      for( i = b; i < ( b + 3 ); ++i )
         if( griglia[a][i] == '#' || griglia[a-1][i-1] == '#' || griglia[a-1][i] == '#' || griglia[a-1][i+1] == '#' || griglia[a][i-1] == '#' || griglia[a][i+1] == '#' || griglia[a+1][i-1] == '#' || griglia[a+1][i] == '#' || griglia[a+1][i+1] == '#' )
            incrociato = 1;
      }
      else {
         orizzontale = 0;
         do {
            a = rand() % 8;
            b = rand() % 10;
         }while( griglia[a][b] == '#' || griglia[a-1][b-1] == '#' || griglia[a-1][b] == '#' || griglia[a-1][b+1] == '#' || griglia[a][b-1] == '#' || griglia[a][b+1] == '#' || griglia[a+1][b-1] == '#' || griglia[a+1][b] == '#' || griglia[a+1][b+1] == '#' );       
         for( i = a; i < ( a + 3 ); ++i )
            if( griglia[i][b] == '#' || griglia[i-1][b-1] == '#' || griglia[i-1][b] == '#' || griglia[i-1][b+1] == '#' || griglia[i][b-1] == '#' || griglia[i][b+1] == '#' || griglia[i+1][b-1] == '#' || griglia[i+1][b] == '#' || griglia[i+1][b+1] == '#' )
               incrociato = 1;   
      }
   }while( incrociato == 1 );

   if( orizzontale ) {
      for( i = b; i < ( b + 3 ); ++i )
         griglia[a][i] = '#';
   }
   else { 
      for( i = a; i < ( a + 3 ); ++i )
         griglia[i][b] = '#';  
   }

   // nave da 3
   do {
      incrociato = 0;
      if( rand() % 2 ) {   // decide se è orizzontale o verticale, si orizzontale, no verticale
         do {
         orizzontale = 1;
         a = rand() % 10;
         b = rand() % 8;
      }while( griglia[a][b] == '#' || griglia[a-1][b-1] == '#' || griglia[a-1][b] == '#' || griglia[a-1][b+1] == '#' || griglia[a][b-1] == '#' || griglia[a][b+1] == '#' || griglia[a+1][b-1] == '#' || griglia[a+1][b] == '#' || griglia[a+1][b+1] == '#' );
      for( i = b; i < ( b + 3 ); ++i )
         if( griglia[a][i] == '#' || griglia[a-1][i-1] == '#' || griglia[a-1][i] == '#' || griglia[a-1][i+1] == '#' || griglia[a][i-1] == '#' || griglia[a][i+1] == '#' || griglia[a+1][i-1] == '#' || griglia[a+1][i] == '#' || griglia[a+1][i+1] == '#' )
            incrociato = 1;
      }
      else {
         orizzontale = 0;
         do {
            a = rand() % 8;
            b = rand() % 10;
         }while( griglia[a][b] == '#' || griglia[a-1][b-1] == '#' || griglia[a-1][b] == '#' || griglia[a-1][b+1] == '#' || griglia[a][b-1] == '#' || griglia[a][b+1] == '#' || griglia[a+1][b-1] == '#' || griglia[a+1][b] == '#' || griglia[a+1][b+1] == '#' );       
         for( i = a; i < ( a + 3 ); ++i )
            if( griglia[i][b] == '#' || griglia[i-1][b-1] == '#' || griglia[i-1][b] == '#' || griglia[i-1][b+1] == '#' || griglia[i][b-1] == '#' || griglia[i][b+1] == '#' || griglia[i+1][b-1] == '#' || griglia[i+1][b] == '#' || griglia[i+1][b+1] == '#' )
               incrociato = 1;   
      }
   }while( incrociato == 1 );

   if( orizzontale ) {
      for( i = b; i < ( b + 3 ); ++i )
         griglia[a][i] = '#';
   }
   else { 
      for( i = a; i < ( a + 3 ); ++i )
         griglia[i][b] = '#';  
   }

   // nave da 2
   do {
      incrociato = 0;
      if( rand() % 2 ) {   // decide se è orizzontale o verticale, si orizzontale, no verticale
         do {
         orizzontale = 1;
         a = rand() % 10;
         b = rand() % 9;
      }while( griglia[a][b] == '#' || griglia[a-1][b-1] == '#' || griglia[a-1][b] == '#' || griglia[a-1][b+1] == '#' || griglia[a][b-1] == '#' || griglia[a][b+1] == '#' || griglia[a+1][b-1] == '#' || griglia[a+1][b] == '#' || griglia[a+1][b+1] == '#' );
      for( i = b; i < ( b + 2 ); ++i )
         if( griglia[a][i] == '#' || griglia[a-1][i-1] == '#' || griglia[a-1][i] == '#' || griglia[a-1][i+1] == '#' || griglia[a][i-1] == '#' || griglia[a][i+1] == '#' || griglia[a+1][i-1] == '#' || griglia[a+1][i] == '#' || griglia[a+1][i+1] == '#' )
            incrociato = 1;
      }
      else {
         orizzontale = 0;
         do {
            a = rand() % 9;
            b = rand() % 10;
         }while( griglia[a][b] == '#' || griglia[a-1][b-1] == '#' || griglia[a-1][b] == '#' || griglia[a-1][b+1] == '#' || griglia[a][b-1] == '#' || griglia[a][b+1] == '#' || griglia[a+1][b-1] == '#' || griglia[a+1][b] == '#' || griglia[a+1][b+1] == '#' );       
         for( i = a; i < ( a + 2 ); ++i )
            if( griglia[i][b] == '#' || griglia[i-1][b-1] == '#' || griglia[i-1][b] == '#' || griglia[i-1][b+1] == '#' || griglia[i][b-1] == '#' || griglia[i][b+1] == '#' || griglia[i+1][b-1] == '#' || griglia[i+1][b] == '#' || griglia[i+1][b+1] == '#' )
               incrociato = 1;   
      }
   }while( incrociato == 1 );

   if( orizzontale ) {
      for( i = b; i < ( b + 2 ); ++i )
         griglia[a][i] = '#';
   }
   else { 
      for( i = a; i < ( a + 2 ); ++i )
         griglia[i][b] = '#';  
   }

   // nave da 2
   do {
      incrociato = 0;
      if( rand() % 2 ) {   // decide se è orizzontale o verticale, si orizzontale, no verticale
         do {
         orizzontale = 1;
         a = rand() % 10;
         b = rand() % 9;
      }while( griglia[a][b] == '#' || griglia[a-1][b-1] == '#' || griglia[a-1][b] == '#' || griglia[a-1][b+1] == '#' || griglia[a][b-1] == '#' || griglia[a][b+1] == '#' || griglia[a+1][b-1] == '#' || griglia[a+1][b] == '#' || griglia[a+1][b+1] == '#' );
      for( i = b; i < ( b + 2 ); ++i )
         if( griglia[a][i] == '#' || griglia[a-1][i-1] == '#' || griglia[a-1][i] == '#' || griglia[a-1][i+1] == '#' || griglia[a][i-1] == '#' || griglia[a][i+1] == '#' || griglia[a+1][i-1] == '#' || griglia[a+1][i] == '#' || griglia[a+1][i+1] == '#' )
            incrociato = 1;
      }
      else {
         orizzontale = 0;
         do {
            a = rand() % 9;
            b = rand() % 10;
         }while( griglia[a][b] == '#' || griglia[a-1][b-1] == '#' || griglia[a-1][b] == '#' || griglia[a-1][b+1] == '#' || griglia[a][b-1] == '#' || griglia[a][b+1] == '#' || griglia[a+1][b-1] == '#' || griglia[a+1][b] == '#' || griglia[a+1][b+1] == '#' );       
         for( i = a; i < ( a + 2 ); ++i )
            if( griglia[i][b] == '#' || griglia[i-1][b-1] == '#' || griglia[i-1][b] == '#' || griglia[i-1][b+1] == '#' || griglia[i][b-1] == '#' || griglia[i][b+1] == '#' || griglia[i+1][b-1] == '#' || griglia[i+1][b] == '#' || griglia[i+1][b+1] == '#' )
               incrociato = 1;   
      }
   }while( incrociato == 1 );

   if( orizzontale ) {
      for( i = b; i < ( b + 2 ); ++i )
         griglia[a][i] = '#';
   }
   else { 
      for( i = a; i < ( a + 2 ); ++i )
         griglia[i][b] = '#';  
   }

}

void mettiNaviManuale( char griglia[10][10] )
{
   int i, a, b;

   printf("Ricordati che le navi non si possono toccare, neanche gli angoli.\n");

   for( i = 0; i < 19; ++i ) {
      if( i == 0 ){
         stampaSingolo( griglia );
         printf("Ora inserisci la nave da 5\n");
      }
      if( i == 5 ){
         stampaSingolo( griglia );
         printf("Ora inserisci la nave da 4\n");
      }
      if( i == 9 ){
         stampaSingolo( griglia );
         printf("Ora inserisci la nave da 3\n");
      }
      if( i == 12 ){
         stampaSingolo( griglia );
         printf("Ora inserisci la nave da 3\n");
      }
      if( i == 15 ){
         stampaSingolo( griglia );
         printf("Ora inserisci la nave da 2\n");
      }
      if( i == 17 ){
         stampaSingolo( griglia );
         printf("Ora inserisci la nave da 2\n");
      }
      printf("Inserisci il numero di riga: ");
      scanf("%d", &a );
      printf("Inserisci il numero di colonna: ");
      scanf("%d", &b );
      griglia[a][b] = '#';
   }

   printf("Perfetto le navi sono state inserite.\n");
}

int vive( char griglia[10][10] )
{
   int i, j;
   for( i = 0; i < 10; ++i )
      for( j = 0; j < 10; ++j )
         if( griglia[i][j] == '#' )
            return 1;
   return 0;
}

void sparo( char attacco[10][10], char naviPc[10][10] )
{
   int a, b;

   printf("Che casella vuoi attaccare?\n");
   printf("Inserisci il numero di riga: ");
   scanf("%d", &a );
   printf("Inserisci il numero di colonna: ");
   scanf("%d", &b );
   while( attacco[a][b] != '.' ) {
      printf("Hai gia' attacato questa casella.\n");
      printf("Che casella vuoi attaccare?\n");
      printf("Inserisci il numero di riga: ");
      scanf("%d", &a );
      printf("Inserisci il numero di colonna: ");
      scanf("%d", &b );
   }
 
   printf("\n");
   if( naviPc[a][b] == '#' ){
      attacco[a][b] = '%';
      naviPc[a][b] = '%';
      printf("Grande! Hai colpito una nave!\n");
      if( affondato( naviPc ) )
         printf("Mitico! Nave affondata!!!\n");
   }
   else {
      attacco[a][b] = 'x';
      naviPc[a][b] = 'x';
   }

}

int sparoPc( char attaccoPc[10][10], char navi[10][10] )
{
   int a, b;
   int colpito = 0;

   srand( time( NULL ) );

   do {
      a = rand() % 10;
      b = rand() % 10; 
   }while( attaccoPc[a][b] != '.');
 
   if( navi[a][b] == '#' ){
      attaccoPc[a][b] = '%';
      navi[a][b] = '%';
      printf("Il computer ha colpito una tua nave\n");
      colpito = 1;
   }
   else {
      attaccoPc[a][b] = 'x';
      navi[a][b] = 'x';
   }
   return colpito;
}

int sparoPcAffondare( char attaccoPc[10][10], char navi[10][10] )
{
   int a, b;
   int colpito = 1; 

   for( a = 0; a < 10; ++a ){
   for( b = 0; b < 10; ++b ){
      if( attaccoPc[a][b] == '%' ){
         if( attaccoPc[a-1][b] == '.' && a-1 > 0 ){
            a = a - 1;
            if( navi[a][b] == '#' ){
               attaccoPc[a][b] = '%';
               navi[a][b] = '%';
               printf("Il computer ha colpito una tua nave\n");
      	       if( affondato( navi ) ){
                  pulizia( attaccoPc );
         	  colpito = 0;
                  printf("Il computer ha affondato una tua nave.\n");
               }
            }
            else {
               attaccoPc[a][b] = 'x';
               navi[a][b] = 'x';
            }
         return colpito;
         }
         else if( attaccoPc[a][b+1] == '.' && b+1 < 10 ){
            b = b + 1;
            if( navi[a][b] == '#' ){
               attaccoPc[a][b] = '%';
               navi[a][b] = '%';
               printf("Il computer ha colpito una tua nave\n");
      	       if( affondato( navi ) ){
                  pulizia( attaccoPc );
         	  colpito = 0;
                  printf("Il computer ha affondato una tua nave.\n");
               }
            }
            else {
               attaccoPc[a][b] = 'x';
               navi[a][b] = 'x';
            }
         return colpito;
         }
         else if( attaccoPc[a+1][b] == '.' && a+1 < 10 ){
            a = a + 1;
             if( navi[a][b] == '#' ){
               attaccoPc[a][b] = '%';
               navi[a][b] = '%';
               printf("Il computer ha colpito una tua nave\n");
      	       if( affondato( navi ) ){
                  pulizia( attaccoPc );
         	  colpito = 0;
                  printf("Il computer ha affondato una tua nave.\n");
               }
            }
            else {
               attaccoPc[a][b] = 'x';
               navi[a][b] = 'x';
            }
         return colpito;
         }
         else if( attaccoPc[a][b-1] == '.' && b-1 > 0 ){
            b = b - 1;
            if( navi[a][b] == '#' ){
               attaccoPc[a][b] = '%';
               navi[a][b] = '%';
               printf("Il computer ha colpito una tua nave\n");
      	       if( affondato( navi ) ){
                  pulizia( attaccoPc );
         	  colpito = 0;
                  printf("Il computer ha affondato una tua nave.\n");
               }
            }
            else {
               attaccoPc[a][b] = 'x';
               navi[a][b] = 'x';
            }
         return colpito;
         }
      }
   }}
   return colpito;
}

void intelligenza( char griglia[10][10] )
{
   int i, j;
   for( i = 0; i < 10; ++i )
      for( j = 0; j < 10; ++j )
         if( griglia[i][j] == '%' ) {
            if( i-1 >= 0 && j-1 >= 0 )
               griglia[i-1][j-1] = 'x';
            if( i-1 >= 0 && j+1 < 10 )
               griglia[i-1][j+1] = 'x';
            if( i+1 < 10 && j-1 >= 0 )
               griglia[i+1][j-1] = 'x';
            if( i+1 < 10 && j+1 < 10 )
               griglia[i+1][j+1] = 'x';
         }

   for( i = 0; i < 10; ++i )
      for( j = 0; j < 10; ++j )
         if( griglia[i][j] == '.' && ( griglia[i+1][j] == 'x' || i+1 > 9 ) && ( griglia[i][j-1] == 'x' || j-1 < 0 ) && ( griglia[i-1][j] == 'x' || i-1 < 0 ) && ( griglia[i][j+1] == 'x' || j+1 > 9 ) ) 
            griglia[i][j] = 'x';  
}

int affondato( char navi[10][10] )
{
   int a, b;

   for( a = 0; a < 10; ++a )
   for( b = 0; b < 10; ++b )
      if( navi[a][b] == '%' )
         if( ( navi[a+1][b] == '#' && a+1 < 10 ) || ( navi[a-1][b] == '#' && a-1 > 0 ) || ( navi[a][b+1] == '#' && b+1 < 10 ) || ( navi[a][b-1] == '#' && b-1 > 0 ) )       
            return 0;  
   return 1;
}

void pulizia( char attacco[10][10] )
{
   int a, b;

   // sappiamo che non ci sono navi superstiti, togliamo delle possibilita
   for( a = 0; a < 10; ++a ){
   for( b = 0; b < 10; ++b ){
      if( attacco[a][b] == '%' ){
         if( attacco[a+1][b] == '.' && a+1 < 10) attacco[a+1][b] = 'x';
         if( attacco[a-1][b] == '.' && a-1 >= 0) attacco[a-1][b] = 'x';
         if( attacco[a][b+1] == '.' && b+1 < 10) attacco[a][b+1] = 'x';
         if( attacco[a][b-1] == '.' && b-1 >= 0) attacco[a][b-1] = 'x';
      }  
   }}   
}
