//---------------------------------------------------------------------------

#pragma hdrstop

#include "uPoligono.h"
#include <Vcl.StdCtrls.hpp>
#include <cmath>

#define SIGN(x) ((x) < 0 ? (-1): (1))
#define ABS(x) ((x) < 0 ? (-x): (x))
#define FLOOR(x) ((x) < 0 ? ((x) - (int)(x) != 0 ? ((int)(x))) : int(x))
//---------------------------------------------------------------------------
#pragma package(smart_init)

void Poligono::desenha(TCanvas *canvas, Janela mundo, Janela vp, int tipoReta, bool D){



	switch (tipoReta) {
		  case 0:
			   LineTo(canvas, mundo, vp, D);
			break;

		  case 1:
			 Dda(canvas, mundo, vp);
			 break;

		  case 2:
			 Bresenham(canvas, mundo, vp);
			 break;

	}

};

void Poligono::LineTo(TCanvas *canvas, Janela mundo, Janela vp, bool D){

	int xvp;
	int yvp;

	if(D){

	for(int x = 0; x < pontos3D.size(); x++){

	xvp = pontos3D[x].xW2Vp(mundo, vp);
	yvp = pontos3D[x].yW2Vp(mundo, vp);

	if(x == 0)
		canvas->MoveTo(xvp, yvp);
	else
		canvas->LineTo(xvp, yvp);

	}
	}  else {

	for(int x = 0; x < pontos.size(); x++){

	xvp = pontos[x].xW2Vp(mundo, vp);
	yvp = pontos[x].yW2Vp(mundo, vp);
	if(x == 0)
		canvas->MoveTo(xvp, yvp);
	else
		canvas->LineTo(xvp, yvp);

	}
	}










};

void Poligono::Dda(TCanvas *canvas, Janela mundo, Janela vp){
	int xvp1;
	int yvp1;
	int xvp2;
	int yvp2;


	//-1 pq estamos pegando de 2 em 2
	for(int i = 0; i < pontos.size() - 1 ; i++){
	xvp1 = pontos[i].xW2Vp(mundo, vp);
	yvp1 = pontos[i].yW2Vp(mundo, vp);

	xvp2 = pontos[i+1].xW2Vp(mundo, vp);
	yvp2 = pontos[i+1].yW2Vp(mundo, vp);

	DdaAlgoritmo(canvas, xvp1,  yvp1,  xvp2, yvp2);

	}

}

void Poligono::DdaAlgoritmo(TCanvas *canvas,  int xvp1, int yvp1, int xvp2, int yvp2){
	 int length;
	 float deltaX, x;
	 float deltaY, y;


	 if( abs((xvp2 - xvp1)) >= abs((yvp2 - yvp1))){
		length = abs((xvp2 - xvp1));
	 } else{
		length = abs((yvp2 - yvp1));
	 }


	 deltaX = (float) (xvp2 - xvp1) / (float) length;
	 deltaY = (float)  (yvp2 - yvp1) / (float) length;
	 x =   xvp1 ;
	 y =  yvp1;

	 for (int i = 0; i < length; i++) {
		 canvas->Pixels[round(x)][round(y)] = clBlack;
		 x += deltaX;
		 y += deltaY;
	 }




}

void Poligono::Bresenham(TCanvas *canvas, Janela mundo, Janela vp){
	int  xvp1, xvp2;
	int  yvp1, yvp2;


	//-1 pq estamos pegando de 2 em 2
	for(int i = 0; i < pontos.size() - 1 ; i++){
	xvp1 = pontos[i].xW2Vp(mundo, vp);
	yvp1 = pontos[i].yW2Vp(mundo, vp);

	xvp2 = pontos[i+1].xW2Vp(mundo, vp);
	yvp2 = pontos[i+1].yW2Vp(mundo, vp);

	BresenhamAlgoritmo(canvas, xvp1, yvp1,  xvp2, yvp2);
	}



}

void Poligono::BresenhamAlgoritmo(TCanvas *canvas,  int xvp1, int yvp1, int xvp2, int yvp2){

	int deltaX, signalX, x;
	int deltaY, signalY, y;
	int interchange;
	int aux;
	int erro;


   deltaX = ABS((xvp2-xvp1));
   deltaY = ABS((yvp2-yvp1));

   signalX = SIGN((xvp2-xvp1));
   signalY = SIGN((yvp2-yvp1));

   x = xvp1;
   y= yvp1;

   if(signalX <0 ){
	x -=1;
   }
  if(signalY <0 ){
	y -=1;
   }

   interchange = FALSE;

   if(deltaY > deltaX){
	  aux = deltaX;
	  deltaX = deltaY;
	  deltaY = aux;
	  interchange = TRUE;
   }

   erro = 2 * deltaY - deltaX;

   for(int i = 0; i < deltaX; i++){

	 canvas->Pixels[round(x)][round(y)] = clBlack;

	 while(erro >=0){
		if(interchange){
		   x +=  signalX;
		}else {
			y +=  signalY;
		}
        erro = erro - 2 * deltaX;
	 }

	 if(interchange){
		  y = y + signalY;
		}else {
		x = x + signalX;

		}
		erro = erro + 2 * deltaY;
	 }

}


UnicodeString Poligono::toString(){
	return IntToStr(id) + "-" + tipo;
};

void Poligono::mostraPontos(TListBox *listbox){
	   listbox->Clear();
	for(int i = 0; i < pontos.size(); i++){
		listbox->Items->Add(pontos[i].toString());

	}

};

void Poligono::translada(double dx, double dy, bool homo){

	if(homo){
	  algoritmoHomogeneo(dx, dy);
	}else {
	for(int i = 0; i < pontos.size(); i++){
	bool homo;
	pontos[i].translada(dx, dy, homo);
	}
}

}

void  Poligono::algoritmoHomogeneo(int x1, int y1){

  bool homo = true;
  char tipo = 'x';
  double x = pontoCentralHomogeneo(x, tipo);
  double  dx;

  tipo = 'y';
  double y = pontoCentralHomogeneo(y, tipo);
  double  dy;

  if(x1 != 0 && y1 != 0 ){
	x = x1;
	y = y1;

	for(int i = 0; i < pontos.size(); i++){

	pontos[i].translada(x, y, homo);
	}
  } else {
     for(int i = 0; i < pontos.size(); i++){
	pontos[i].translada( -1*x, -1*y , homo);
  }

 }
}

double Poligono::pontoCentralHomogeneo(double aux, char tipo){


	 if(tipo == 'x'){
		  double dx;
		  double x = aux;
		  int n=0;

			for (int i = 0; i < pontos.size(); i++) {
				dx += pontos[i].x;
				n += 1;
			}
			x = dx/n;

		return x ;

	 }else {
		 double dy;
		  double y = aux;
		  int n=0;

			for (int i = 0; i < pontos.size(); i++) {
				dy += pontos[i].y;
				n += 1;
			}
			y = dy/n;

		return y ;

	 }

}

void Poligono::escalona(double sx, double sy){
    	for(int i = 0; i < pontos.size(); i++){
	  pontos[i].escalona(sx, sy);
	}
}

void Poligono::rotaciona(int angulo){
    	for(int i = 0; i < pontos.size(); i++){
	  pontos[i].rotaciona(angulo);
	}
}

void Poligono::reflexaoX(){
		for(int i = 0; i < pontos.size(); i++){
	  pontos[i].reflexaoX();
	}
}

void Poligono::reflexaoY(){
		for(int i = 0; i < pontos.size(); i++){
	  pontos[i].reflexaoY();
	}
}


void Poligono::pontoCentral(){

	int dx, dy;
	int n = 0;

	for (int i = 0; i < pontos.size(); i++) {
		dx += pontos[i].x;
		dy += pontos[i].y;
		n += 1;
	}

	pontos[n].pontoCentral(dx, dy, n);

}


void Poligono::Circunferencia(int xc, int yc, int r){
	 int x, y, p;

	 x =0;
	 y = r;
	 DesenhaPontoCircunferencia(xc, yc, x, y);

	 p = 1 -r;
	 while( x<y ){

	  if( p<0 ){

		x ++;

	  } else {

		x++;
		y--;

	  }

	  if( p<0) {

		p += 2 * x + 1;

	  } else {

		p += 2 * (x-y ) + 1 ;
		DesenhaPontoCircunferencia(xc, yc, x, y);
	  }
	 }

}

void Poligono::DesenhaPontoCircunferencia(int xc, int yc, int x, int y){

	pontos.push_back(Ponto( xc + x, yc + y ));
	pontos.push_back(Ponto( xc + y, yc + x ));
	pontos.push_back(Ponto( xc + y, yc - x ));
	pontos.push_back(Ponto( xc + x, yc - y ));
	pontos.push_back(Ponto( xc - x, yc - y ));
	pontos.push_back(Ponto( xc - y, yc - x ));
	pontos.push_back(Ponto( xc - y, yc + x ));
	pontos.push_back(Ponto( xc - x, yc + y ));

}

void Poligono::cohenSutherland(Janela clipping, Poligono *aux){

  	int p1, p2;
	double auxX, auxY;

	for (int i = 0; i < pontos.size() - 1; i++) {

	  double x;
	  double y;
	  double m;

	  //para a primeira intera��o, guardaremos o valor das coordenadas
	  //do p2 pois nessa itera��o eles serao alterados

	  if (i == 0) {

	  //chamada do regionCode para saber em qual regi�o da
	  //janela de clipping o ponto 1 e 2 est� passando

		p1 = pontos[i].regionCode(clipping);
		p2 = pontos[i+1].regionCode(clipping);

		auxX = pontos[i+1].x;
		auxY = pontos[i+1].y;


	  } else {
		pontos[i].x = auxX;
		pontos[i].y = auxY;

		p1 = pontos[i].regionCode(clipping);
		p2 = pontos[i+1].regionCode(clipping);

		auxX = pontos[i+1].x;
		auxY = pontos[i+1].y;
	  }


	  //p1 e p2 = 0 : totalmente contido
	  if(p1 == 0 && p2 == 0){
		aux->pontos.push_back(pontos[i]);
		aux->pontos.push_back(pontos[i+1]);

	  } else if(p1 & p2 ){


	  } else {

		m = coeficienteAngular(pontos[i].x,  pontos[i].y,  pontos[i+1].x,  pontos[i+1].y);

		switch (p1) {
		  //esquerda
		  case 1:
			  y = m * (clipping.xmin - pontos[i].x) + pontos[i].y;

			  pontos[i].x = clipping.xmin;
			  pontos[i].y = y;

			  aux->pontos.push_back(pontos[i]);
			  aux->pontos.push_back(pontos[i+1]);
			break;
		//direita
		  case 2:
			  y = m * (clipping.xmax - pontos[i].x) + pontos[i].y;

			  pontos[i].x = clipping.xmax;
			  pontos[i].y = y;

			  aux->pontos.push_back(pontos[i]);
			  aux->pontos.push_back(pontos[i+1]);

			 break;
		 //baixo
		  case 4:
			 x = pontos[i].x + ( 1/m ) * (clipping.ymin - pontos[i].y);

			 pontos[i].y = clipping.ymin;
			 pontos[i].x = x;
			 aux->pontos.push_back(pontos[i]);
			 aux->pontos.push_back(pontos[i+1]);
			 break;
		 //topo
		  case 8:
			x = pontos[i].x + (1/m) * (clipping.ymax - pontos[i].y);

			pontos[i].y = clipping.ymax;
			pontos[i].x = x;

			aux->pontos.push_back(pontos[i]);
			aux->pontos.push_back(pontos[i+1]);
			 break;
		}

		switch (p2) {
		  //esquerda
		  case 1:
			  aux->pontos.push_back(pontos[i]);

			  y = m * (clipping.xmin - pontos[i+1].x) + pontos[i+1].y;

			  pontos[i+1].x = clipping.xmin;
			  pontos[i+1].y = y;

			  aux->pontos.push_back(pontos[i+1]);
			break;
		//direita
		  case 2:
			  aux->pontos.push_back(pontos[i]);

			  y = m * (clipping.xmax - pontos[i+1].x) + pontos[i+1].y;

			  pontos[i+1].x = clipping.xmax;
			  pontos[i+1].y = y;

			  aux->pontos.push_back(pontos[i+1]);
			 break;
		//baixo
		  case 4:
			 aux->pontos.push_back(pontos[i]);

			 x = pontos[i+1].x + ( 1/m ) * (clipping.ymin - pontos[i+1].y);

			 pontos[i+1].y = clipping.ymin;
			 pontos[i+1].x = x;
			 aux->pontos.push_back(pontos[i+1]);
			 break;
		//topo
		  case 8:
			aux->pontos.push_back(pontos[i]);

			x =  pontos[i+1].x + (1/m) * (clipping.ymax - pontos[i+1].y);

			pontos[i+1].y = clipping.ymax;
			pontos[i+1].x = x;
			aux->pontos.push_back(pontos[i+1]);
			 break;
		}

	  }
	}

}


double Poligono::coeficienteAngular(double x1, double y1, double x2, double y2){

  double m;

  m = ( (y2 - y1) / ( x2 - x1 ));

  return m;
}


 void Poligono::casteljau(Poligono *aux){

    Ponto p0(pontos[0].x, pontos[0].y);
	Ponto p1(pontos[1].x, pontos[1].y);
	Ponto p2(pontos[2].x, pontos[2].y);

	aux->pontos.push_back(Ponto(p0.x, p0.y));
	algoritmoCasteljau(p0, p1, p2, aux);

 }

 void Poligono::algoritmoCasteljau(Ponto p0, Ponto p1, Ponto p2, Poligono *aux){

	int a, b, c;
	Ponto p11(0, 0), p21(0,0), p22(0,0);

	a = p2.x - p0.x;
	b = p2.y - p0.y;

	a = a * a;
	b = b * b;
	c = a + b;

	//se n for-> dividir pra conquistar
	if ( sqrt(c) < 5) {

	  aux->pontos.push_back(Ponto(p2.x, p2.y));

	} else {

		//subdivis�o dos pontos
		p11.x = (p0.x + p1.x)/2;
		p11.y = (p0.y + p1.y)/2;
		p21.x = (p1.x + p2.x)/2;
		p21.y = (p1.y + p2.y)/2;
		p22.x = (p11.x + p21.x)/2;
		p22.y = (p11.y + p21.y)/2;

		algoritmoCasteljau(p0, p11, p22, aux);
		algoritmoCasteljau(p22, p21, p2, aux);
	}

 }

 void Poligono::algoritmoHermite( Poligono *aux){
 //usa 4 pontos = p0, p1, p2 e p3
 // 1� calcular os r's, 2� definir as matrizes, 3� multiplicar mh
 // com gh, depois o resultado com t -> objetivo


	double i;
	int linha, coluna, n;
	Ponto auxP(0,0);

	   //eq 5.5 cal do r1x e r4x
		double r1x = pontos[1].x - pontos[0].x;
		double r1y = pontos[1].y - pontos[0].y;

		double r4x = pontos[3].x - pontos[2].x;
		double r4y = pontos[3].y - pontos[2].y;

		double x4 = pontos[3].x;
		double y4 = pontos[3].y;

		//defini��o das matrizes (CX = MH * GHX) eq 5.13

		// GHX = {x(0)= P1x, x(1)=P4x, x'(0)=r1x, x'(1)=r4x}
		double hx[4][1] = { {pontos[0].x}, {pontos[3].x},  {r1x},  {r4x}} ;

		//GHY = {y(0)= P1y, y(1)=P4y, y'(0)=r1y, y'(1)=r4y}
		double hy[4][1] = { {pontos[0].y}, {pontos[3].y}, {r1y}, {r4y} };

		//matriz de hermite
		double mh[4][4] =  { {2, -2, 1, 1}, {-3, 3, -2, -1}, {0 ,0, 1, 0}, {1, 0, 0, 0} };

		double cx[4][1] = { {0}, {0}, {0}, {0} };
		double cy[4][1] = { {0}, {0}, {0}, {0} };



		//calculo do cx e cy (CX = MH * GHX) multiplica��o de matriz somatorio da linha x coluna

		for ( linha = 0; linha < 4; linha++ ) {

			for ( coluna = 0; coluna < 1; coluna++ ) {

				for (n = 0; n < 4; n++) {

					cx[linha][coluna] += mh[linha][n] * hx[n][coluna];
					cy[linha][coluna] += mh[linha][n] * hy[n][coluna];
				}
			}
		}



		// calculo do T * cx

		for (i = 0; i <= 1; i += 0.1) {

			 double tx[1][1] = { {0} };
			 double ty[1][1] = { {0} };
			 double t[1][4] = { {i*i*i, i*i, i, 1} };

			for (linha = 0; linha < 1; linha++) {

				for (coluna = 0; coluna < 1; coluna++) {

					for (n = 0; n < 4; n++) {

						tx[linha][coluna] += t[linha][n] * cx[n][coluna];
						ty[linha][coluna] += t[linha][n] * cy[n][coluna];
					}
				}
			}

			auxP.x = tx[0][0];
			auxP.y = ty[0][0];

			aux->pontos.push_back(auxP);

		}
 }

 void Poligono::algoritmoBezier( Poligono *aux){
//xt = t * mb * gbx    e yt = t * mb * gby

//definir as matrizes bx e by  direto com os valores de x e y dos pontos
//calcular a multiplica��o das matrizes pra cx =  mb * gbx    e cy = * mb * gby
//calcular a multiplioca��o das matrizes para cx e cy com t


	double i;
	int linha, coluna, n;
	Ponto auxP(0,0);

		double bx[4][1] = { {pontos[0].x}, {pontos[1].x}, {pontos[2].x}, {pontos[3].x} };
		double by[4][1] = {{pontos[0].y},{pontos[1].y}, {pontos[2].y}, {pontos[3].y}};

		double mb[4][4] = { {-1, 3, -3, 1}, {3, -6, 3, 0}, {-3 , 3, 0, 0}, {1, 0, 0, 0} };

		double cx[4][1] = { {0}, {0}, {0}, {0}};
		double cy[4][1] =  { {0}, {0}, {0}, {0}};


        for ( linha = 0; linha < 4; linha++ ) {

			for ( coluna = 0; coluna < 1; coluna++ ) {

				for (n = 0; n < 4; n++) {

					cx[linha][coluna] += mb[linha][n] * bx[n][coluna];
					cy[linha][coluna] += mb[linha][n] * by[n][coluna];
				}
			}
		}

        	for (i = 0; i <= 1; i += 0.1) {

			 double tx[1][1] = { {0} };
			 double ty[1][1] = { {0} };
			 double t[1][4] = { {i*i*i, i*i, i, 1} };

			for (linha = 0; linha < 1; linha++) {

				for (coluna = 0; coluna < 1; coluna++) {

					for (n = 0; n < 4; n++) {

						tx[linha][coluna] += t[linha][n] * cx[n][coluna];
						ty[linha][coluna] += t[linha][n] * cy[n][coluna];
					}
				}
			}

			auxP.x = tx[0][0];
			auxP.y = ty[0][0];

			aux->pontos.push_back(auxP);

		}

 }


 void Poligono::algoritmoBspline(Poligono *aux){
  //mbs = 1/6 (mbs)

	double j;
	int linha, coluna, n, i;
	Ponto auxP(0,0);

		double bsx[4][1] = { {pontos[0].x}, {pontos[1].x}, {pontos[2].x}, {pontos[3].x} };
		double bsy[4][1] = {{pontos[0].y},{pontos[1].y}, {pontos[2].y}, {pontos[3].y}};

		double mbs[4][4] = { {-1, 3, -3, 1}, {3, -6, 3, 0}, {-3 , 0, 3, 0}, {1, 4, 1, 0} };


		for (linha = 0; linha < 4; linha++) {

				for (coluna = 0; coluna < 4; coluna++) {

					mbs[linha][coluna] = ( mbs[linha][coluna]) /6;
			}
		}

		for (i = 0; i < pontos.size() - 3; i++) {

			double cx[4][1] = { {0}, {0}, {0}, {0}};
			double cy[4][1] =  { {0}, {0}, {0}, {0}};

			double bsx[4][1] = {  {pontos[i].x}, {pontos[i+1].x}, {pontos[i+2].x}, {pontos[i+3].x} };
			double bsy[4][1] = { { pontos[i].y}, {pontos[i+1].y}, {pontos[i+2].y}, {pontos[i+3].y}} ;

			for (linha = 0; linha < 4; linha++) {

				for (coluna = 0; coluna < 1; coluna++) {

					for (n = 0; n < 4; n++) {
						cx[linha][coluna] += mbs[linha][n] * bsx[n][coluna];
						cy[linha][coluna] += mbs[linha][n] * bsy[n][coluna];
					}
				}
			}


			for (j = 0; j <= 1; j += 0.1) {

				double tx[1][1] = { {0} };
				double ty[1][1] = { {0} };
				double t[1][4] = { {j*j*j, j*j, j, 1} };

				for (linha = 0; linha  < 1; linha ++) {

					for (coluna = 0; coluna < 1; coluna++) {

						for (n = 0; n < 4; n++) {

							tx[linha][coluna] += t[linha][n] * cx[n][coluna];
							ty[linha][coluna] += t[linha][n] * cy[n][coluna];
						}
					}
				}

				auxP.x = tx[0][0];
				auxP.y = ty[0][0];
				aux->pontos.push_back(auxP);

			}

		}

 }

  void Poligono::algoritmoBsplineFoward(Poligono *aux){
  //mbs = 1/6 (mbs)

	double j;
	int linha, coluna, n, i;
	Ponto auxP(0,0);

		double bsx[4][1] = { {pontos[0].x}, {pontos[1].x}, {pontos[2].x}, {pontos[3].x} };
		double bsy[4][1] = {{pontos[0].y},{pontos[1].y}, {pontos[2].y}, {pontos[3].y}};

		double mbs[4][4] = { {-1, 3, -3, 1}, {3, -6, 3, 0}, {-3 , 0, 3, 0}, {1, 4, 1, 0} };


		for (linha = 0; linha < 4; linha++) {

				for (coluna = 0; coluna < 4; coluna++) {

					mbs[linha][coluna] = ( mbs[linha][coluna]) /6;
			}
		}

		for (i = 0; i < pontos.size() - 3; i++) {

			double cx[4][1] = { {0}, {0}, {0}, {0}};
			double cy[4][1] =  { {0}, {0}, {0}, {0}};

			double bsx[4][1] = {  {pontos[i].x}, {pontos[i+1].x}, {pontos[i+2].x}, {pontos[i+3].x} };
			double bsy[4][1] = { { pontos[i].y}, {pontos[i+1].y}, {pontos[i+2].y}, {pontos[i+3].y}} ;

			for (linha = 0; linha < 4; linha++) {

				for (coluna = 0; coluna < 1; coluna++) {

					for (n = 0; n < 4; n++) {
						cx[linha][coluna] += mbs[linha][n] * bsx[n][coluna];
						cy[linha][coluna] += mbs[linha][n] * bsy[n][coluna];
					}
				}
			}



				double j = 0.1;
				double tx[4][1] = { {0}, {0}, {0}, {0} };
				double ty[4][1] = { {0}, {0}, {0}, {0} };
				double t[4][4] = { {0, 0, 0, 1},  {j*j*j, j*j, j, 0}, {6*j*j*j, 2*j*j, 0, 0}, {6*j*j*j, 0, 0, 0} };

				for (linha = 0; linha  < 4; linha ++) {

					for (coluna = 0; coluna < 1; coluna++) {

						for (n = 0; n < 4; n++) {

							tx[linha][coluna] += t[linha][n] * cx[n][coluna];
							ty[linha][coluna] += t[linha][n] * cy[n][coluna];
						}
					}
				}

				int a;
				aux->pontos.push_back(Ponto(tx[0][0],ty[0][0]));

				for (a = 0; a < 10; a++) {
				   tx[0][0] += tx[1][0];
				   tx[1][0] += tx[2][0];
				   tx[2][0] +=  tx[3][0];

				   ty[0][0] += ty[1][0];
				   ty[1][0] += ty[2][0];
				   ty[2][0] +=  ty[3][0];

				   aux->pontos.push_back(Ponto(tx[0][0],ty[0][0]));
				}


			}


 }

 void Poligono::mostraPontos3D(TListBox *listbox){


    listbox->Clear();
	for (int i = 0; i < pontos3D.size() ; i++) {

		listbox->Items->Add(pontos3D[i].toString());

	}
}


void Poligono::translada3d(double dx, double dy, double dz){

	 for (int i = 0; i < pontos3D.size(); i++) {

		 pontos3D[i].translada3d( dx, dy, dz) ;

	 }
}


void Poligono::escalona3d(double de){

	 for (int i = 0; i < pontos3D.size(); i++) {

		 pontos3D[i].escalona3d(de) ;
	 }
}


void Poligono::rotaciona3d(double angulo, int eixo) {

   for (int i = 0; i < pontos3D.size(); i++) {

	  pontos3D[i].rotaciona3d(angulo, eixo);
   }

}



