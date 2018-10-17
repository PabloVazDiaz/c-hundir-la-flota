#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

bool check(int tamanio, int x, int y, bool vertical, char sea[10][10]){
    bool colocado=true;
    if(vertical==true){
        if(y>(10-tamanio))
            colocado=false;
        for(int i=0;i<tamanio;i++)
            if(sea[y+i][x]!=char(178))
                colocado=false;
    }
    else{
        if(x>(10-tamanio))
            colocado=false;
        for(int i=0;i<tamanio;i++)
            if(sea[y][x+i]!=char(178))
                colocado=false;
    }

    return colocado;
}

void show( char sea[10][10]){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            cout<<sea[i][j]<<" ";
        }
        cout<<endl;
    }
}

void colocar(bool vertical, int y, int x, int tamanio, char barco, char sea[10][10]){
    for(int i=0;i<tamanio;i++){
            if(vertical==true)
                sea[y+i][x]=barco;
            if(vertical==false)
                sea[y][x+i]=barco;
        }

}

void inicial(char sea[10][10]){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(i==0)
                sea[i][j]=char(48+j);
            else if(j==0)
                sea[i][j]=char(64+i);
            else sea[i][j]=char(178);
        }
    }
}

int main()
{
    char sea[10][10], human_sea[10][10],comp_sea[10][10];
    int coordtocados[2][12];
    int tocx=0, x=0, y=0, z=0;
    char barco='0', ychar, xchar, eleccion;
    bool colocado=false, vertical=true;
    bool ganar=false, perder=false, posicion=false;
    bool tocado=false, hundido=false;
    bool bucle=false, correcto=true, again=false;
    srand(time(NULL));
    inicial(sea);
    inicial(human_sea);
    inicial(comp_sea);
    //Llenado inicial de matriz
    for(int tamanio=3;tamanio<6;tamanio++){
        do{
            if(tamanio==3)
                barco='s';
            if(tamanio==4)
                barco='a';
            if(tamanio==5)
                barco='p';//Cambio del tipo de barco segun tamaño
            x=rand()%100;
            if(x%2==0)
                vertical=true;//Vertical u horizontal en random
            else vertical=false;
            colocado=true;//Cada bucle la condicion se hace true y se niega si no vale esa posicion
            x=rand()%10;
            y=rand()%10;
            colocado=check(tamanio, x, y, vertical, comp_sea);
            //Comprobar que los espacios que le toca estan vacios
    }while (colocado==false);
        colocar(vertical, y, x, tamanio, barco, comp_sea);
        //Colocacion de un barco
    }
    //----------------Colocacion de barcos por parte del ordenador---------------------
    show(sea);
    //Mostrar la matriz del ordenador (provisional)
    for(int tamanio=3;tamanio<6;tamanio++){
        system("cls");
        show(human_sea);
        do{
            if(tamanio==3)
                barco='s';
            if(tamanio==4)
                barco='a';
            if(tamanio==5)
                barco='p';//Cambio del tipo de barco segun tamaño
            do{
            cout<<"Introduce la letra de la fila donde quieres el barco de "<<tamanio<<" espacios:";
            cin>>ychar;
            correcto=true;
            if(ychar<97)
                ychar-=64;
            else ychar-=96;
            y=ychar;
            if(y<1||y>11){
                cout<<"Introduce una letra valida"<<endl;
                correcto=false;
                }
            }while(correcto==false);
            //Humano introduciendo y
            do{
                cout<<"Introduce el numero de la columna donde quieres el barco de "<<tamanio<<" espacios:";
                cin>>xchar;
                correcto=true;
                xchar-=48;
                x=xchar;
                if(x<1||x>11){
                    cout<<"Introduce un numero valido"<<endl;
                    correcto=false;
                    }
            }while(correcto==false);
            //Humano introduciendo x
            do{
                cout<<"Quieres introducirlo en vertical (v) o en horizontal(h)?";
                cin>>eleccion;
                if(eleccion=='v')
                    vertical=true;
                else if(eleccion=='h')
                    vertical=false;
                else correcto=false;
                if(correcto==false)
                    cout<<"Introduce solo v o h para elegir direccion"<<endl;
            }while(correcto==false);
            //Humano eligiendo vertical
            colocado=true;//Cada bucle la condicion se hace true y se niega si no vale esa posicion
            colocado=check(tamanio, x, y, vertical, human_sea);
            if (colocado==false)
                cout<<endl<<"La posicion elegida no es valida"<<endl;
            //Comprobar que los espacios que le toca estan vacios
    }while (colocado==false);
        colocar(vertical, y, x, tamanio, barco, human_sea);
        //Colocacion de un barco
        system("cls");
        show(human_sea);
        cout<<"Estas contento con esta posicion? (y/n)";
        cin>>eleccion;
        if(eleccion=='n'){
            colocar(vertical, y, x, tamanio, char(178), human_sea);
            tamanio--;
        }

    }
    //For colocacion barcos humanos
    system("cls");
    do{
        ganar=true;
        do{
            again=false;
            do{
                hundido=true;
                posicion=false;//Reseteo booleano
                if(tocado==false){
                    x=rand()%11;
                    y=rand()%11;
                }
                //Eleccion de coordenadas si no hay barco tocado
                else{
                    do{
                        bucle=false;
                        z=rand()%tocx;
                        if(z<0||z>=tocx)
                            bucle=true;
                        y=coordtocados[0][z];
                        x=coordtocados[1][z];
                        x+=((rand()%3)-1);
                        y+=((rand()%3)-1);
                    }while(bucle==true);
                }
                //Eleccion de coordenadas si hay barco tocado
                if(human_sea[y][x]==char(178)){
                    cout<<endl<<"AGUA"<<endl;
                    human_sea[y][x]=char(126);
                    posicion=true;
                }
                if(human_sea[y][x]=='a'||human_sea[y][x]=='s'||human_sea[y][x]=='p'){
                    cout<<endl<<"TOCADO"<<endl;
                    barco=human_sea[y][x];
                    human_sea[y][x]=char(207);
                    posicion=true;
                    tocado=true;
                    again=true;
                    coordtocados[0][tocx]=y;
                    coordtocados[1][tocx]=x;
                    tocx++;
                }
                for(int i=0;i<10;i++){
                    for(int j=0;j<10;j++){
                        if(human_sea[i][j]==barco)
                            hundido=false;
                    }
                }
                //Recorrido para comprobar si ha hundido el barco que buscaba
                if(hundido==true){
                    tocado=false;
                    hundido=false;
                    for(int i=0;i<2;i++)
                        for(int j=0;j<tocx;j++)
                            coordtocados[i][j]=-1;//Reseteo matriz de coordernadas tocados
                    tocx=0;
                }
            }while(posicion==false);
            Sleep(1000);
            system("cls");
            show(sea);
            cout<<endl<<endl;
            show(human_sea);
            for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                    if((human_sea[i][j]=='a')||(human_sea[i][j]=='s')||(human_sea[i][j]=='p'))
                        perder=false;
                }//Si encuentra un barco todavia no ha ganado
            }
        }while(again==true);
        //-------------FIN DE LO QUE HACE LA MAQUINA---------------
        cout<<endl<<"TU TURNO"<<endl;
        do{
            do{
                again=false;
                do{
                    char ychar='0';
                    correcto=true;
                    cout<<"Introduce la letra de la fila que atacar: ";
                    cin>>ychar;
                    if(ychar<97)
                        ychar-=64;
                    else ychar-=96;
                    y=ychar;
                    if(y<1||y>11){
                        cout<<"Introduce una letra valida"<<endl;
                        correcto=false;
                    }
                }while(correcto==false);
                do{
                    correcto=true;
                    cout<<"Introduce el numero de la columna que atacar: ";
                    cin>>xchar;
                    xchar-=48;
                    x=xchar;
                    if(x<1||x>11){
                        cout<<"Introduce un numero valido"<<endl;
                        correcto=false;
                    }
                }while(correcto==false);
                posicion=false;
                if(comp_sea[y][x]==char(178)){
                        cout<<endl<<"AGUA"<<endl;
                        sea[y][x]=char(126);
                        comp_sea[y][x]=char(126);
                        posicion=true;
                    }
                if(comp_sea[y][x]=='a'||comp_sea[y][x]=='s'||comp_sea[y][x]=='p'){
                        cout<<endl<<"TOCADO"<<endl;
                        sea[y][x]=char(207);
                        comp_sea[y][x]=char(207);
                        again=true;
                        posicion=true;
                    }
                if(posicion==false)
                    cout<<"Introduce coordenadas validas"<<endl;
            }while(posicion==false);//Turno del humano
             ganar=true;
             for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                    if((comp_sea[i][j]=='a')||(comp_sea[i][j]=='s')||(comp_sea[i][j]=='p'))
                        ganar=false;
                }//Si encuentra un barco todavia no ha ganado
            }
            system("cls");
            show(sea);
            cout<<endl<<endl;
            show(human_sea);
            Sleep(1000);
        }while(again==true);
        //--------------FIN TURNO JUGADOR------------------

    }while(ganar==false&&perder==false);
    //-------------------------------Juego-------------------------
    if(perder==true)
        cout<<endl<<"La maquina te ha ganado"<<endl;
    if(ganar==true)
        cout<<endl<<"HAS GANADO"<<endl;
    return 0;
}
