/* Battaglia navale */

#include "navi.h"

int main()
{
   char navi[10][10];
   char attacco[10][10];
   char naviPc[10][10];
   char attaccoPc[10][10];
   char risposta;
   int colpito = 0;

   azzera( navi );
   azzera( attacco );
   azzera( naviPc );
   azzera( attaccoPc );

   mettiNaviAuto( naviPc );

   printf("\nVuoi inserire le tue navi manualmente o vuoi che sia il compuer a farlo automaticamente inserendole a caso?\n");
   do {
      printf("Devi rispondere s o n: ");
      scanf("%c", &risposta );
   }while( risposta != 's' && risposta != 'n' );

   if( risposta == 's' )
      mettiNaviManuale( navi );
   else
      mettiNaviAuto( navi );

   stampa( navi, attacco );

   while( vive( naviPc ) && vive( navi ) )
   {
      printf("\n\n\n");
      sparo( attacco, naviPc );
      if ( colpito == 1 )
         colpito = sparoPcAffondare( attaccoPc, navi );
      else
         colpito = sparoPc( attaccoPc, navi );  
      intelligenza( attaccoPc );
      stampa( navi, attacco );     
   }

   if( vive( navi ) )
      printf("Grande! Hai vinto!\n");
   else
      printf("Il computer ha vinto\n");

   return 0;

}
