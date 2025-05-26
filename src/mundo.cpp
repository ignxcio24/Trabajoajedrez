#include "mundo.h"
#include "reglas.h"

#include <math.h>
#include <vector>
#include <iostream>
#include "freeglut.h"
#include <GL/glu.h>

Pantalla currentScreen = START;

Mundo::Mundo() :
    //Inicialización de variables, inicia el ojo y todos los flags posteriores en false que sirven para realizar
    //acciones en el juego, como por ejemplo el modo de juego, si se ha hecho click o no, si se ha terminado la partida, etc.
    x_ojo(3.0f), y_ojo(4.9f), z_ojo(-1.0f),
    angle(-1.5707963268f), targetAngle(angle),
    modeFlag(false), //Cambia el modo de juego a modo normal y si esta en false estás en esquinas opuestas pulsando "T"
    turnFlag(false), //Define el turno actual, si está en false le toca a blanco si está en true a negro 
    clickFlag(true), //Permite que hagas click con el ratón si está en true
    rotationFlag(false), //Controla si la cámara se está girando, si está en true, gira
    modelviewFlag(true), // Define cámara cenital o rotativa, si está en true es cámara rotativa
    //Si está nen rotativa es 3D si no 2D
    fullscrnFlag(false), //Define si está el modo antalla competa activado con la letra "F"
    endFlag(false), //Fin de partida alcanzado
    jaqueFlag(false), //Indica si el jugador contrario está en jaque
    autopilotFlag(false), //define si está activado el mod jugador vs máquina [true=jugador vs máquina, false jugador vs jugador]
    openingFlag(true) //Para pasar de la pantalla de inicio a la del juego
{}
void Mundo::rotarOjo() {
    //Primer requisito, si el rotationFlag está activado(true), cambia la cámara
    if (!rotationFlag)
        return;
    //Pasa el requisito y reiniciamos la variable click, mientras que esté en este método, no se puede
    //hacer click
    clickFlag = false;
    //El ángulo aumenta 0.05 
    angle += 0.05f;
    if (angle >= targetAngle) {
        angle = targetAngle;
        rotationFlag = false;
        clickFlag = true;
    }
    //Giro de modo 3D
    if (modelviewFlag) {
        x_ojo = 3.0f + 4.5f * cos(angle);
        z_ojo = 3.5f + 4.5f * sin(angle);
    }
    //Giro en modo 2D
    else {
        x_ojo = 3.0f + 0.1f * cos(angle);
        z_ojo = 3.499f + 0.1f * sin(angle);
    }
}
//Método que dice hasta donde rota
void Mundo::cambiarOjo() {
    if (modelviewFlag) {
        if (!turnFlag) {
            x_ojo = 3.0f;
            y_ojo = 4.9f;
            z_ojo = -1.0f;
        }
        else {
            x_ojo = 3.0f;
            y_ojo = 4.9f;
            z_ojo = 8.0f;
        }
    }
    else {
        if (!turnFlag) {
            x_ojo = 3.0f;
            y_ojo = 6.45f;
            z_ojo = 3.499f;
        }
        else {
            x_ojo = 3.0f;
            y_ojo = 6.45f;
            z_ojo = 3.501f;
        }
    }
}
void Mundo::modoVSmaquina() {
    autopilotFlag = !autopilotFlag;
    std::cout << (autopilotFlag ? "Humano VS Maquina (Seleccionado)\n" : "Humano VS Humano (Seleccionado)\n");
}
//Define la partida
void Mundo::inicializa() {
    x_ojo = 3.0f;
    y_ojo = 4.9f;
    z_ojo = -1.0f;
    angle = -1.5707963268f;
    turnFlag = false;
    clickFlag = true;
    rotationFlag = false;
    piezas.deseleccionar();
    platform.resetTileColors();
    piezas.setMode(modeFlag);
    endFlag = false;
    openingFlag = true;
    cambiarOjo();
}
void Mundo::dibuja() {
    //CurrentScreen pertenece a pantalla y se inicializa con START al principio de este código
    switch (currentScreen) {
    case START:
        menu.setScreen(MENU_INICIO);
        menu.dibuja();
        break;
    case PLAYING:
        gluLookAt(x_ojo, y_ojo, z_ojo,  // POSICION DEL OJO
                  3.0f, -1.0f, 3.5f,    // DONDE MIRA EL OJO
                  0.0f, 1.0f, 0.0f);    // VECTOR HACIA ARRIBA (+Y)
   
        glPushMatrix();
        glTranslatef(3.0f, 0.2f, 3.5f);
        glColor4ub(255, 255, 255, 255);
        glRotatef(90, 0, -1, 0);
        glutWireSphere(10, 20, 17);
        glPopMatrix();

        platform.dibuja();
        piezas.dibuja();
        break;
    case GAME_OVER:
        menu.setScreen(MENU_FINAL);
        menu.dibuja();
        break;
    default:
        break;
    }
}
void Mundo::tecla(unsigned char key) {
    switch (currentScreen) {
        //En el caso de que sea START(la variable currentScreen)
    case START:
        if (key == 13) {  // El enter del teclado es el número 13
            //Si le da a enter pasa al modo y pantalla "PLAYING"
            currentScreen = PLAYING;
            glutPostRedisplay();
            return;
        }
        //Si se pulsa f, se activa el modo pantalla completa, si no se ajusta la pantalla a la pequeña
        else if (key == 'f' || key == 'F') {
            if (fullscrnFlag == 0) {
                glutFullScreen();
            }
            else {
                glutReshapeWindow(1408, 792);
                glutPositionWindow(52, 0);
            }
            fullscrnFlag = !fullscrnFlag;
            return;
        }
        break;
    case PLAYING:
        if (!rotationFlag) {
            switch (key) {
            case 'f': case 'F':
                if (fullscrnFlag == 0) {
                    glutFullScreen();
                }
                else {
                    glutReshapeWindow(1408, 792);
                    glutPositionWindow(52, 0);
                }
                fullscrnFlag = !fullscrnFlag;
                break;
                //Si toca la letra T, el model flag cambia a false, indicando que está en el modo que se cambia y 
                //Se llama a inicializa para que se cambie
                    //Todas las tecla siguen el mismo "modus operandi"
            case 't': case 'T':
                modeFlag = !modeFlag;
                inicializa();
                break;
            case 'g': case 'G':
                piezas.guardarTablero("lastboard.txt", turnFlag, openingFlag);
                break;
            case 'c': case 'C':
                inicializa();
                piezas.cargarTablero("lastboard.txt", turnFlag, openingFlag);
                if (turnFlag) {
                    rotationFlag = true;
                    targetAngle = angle + 3.14159265f;
                }
                break;
            case 'v': case 'V':
                modelviewFlag = !modelviewFlag;
                cambiarOjo();
                break;
            case 'm': case 'M':
                modoVSmaquina();
                break;
            case 27:
                exit(0);
                break;
            default:
                break;
            }
        }
        break;
        //Igua que los anteriores
    case GAME_OVER:
        if (key == 'r' || key == 'R') {
            currentScreen = START;
            inicializa();
            glutPostRedisplay();
            return;
        }
        if (key == 27) {
            exit(0);
        }
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
void Mundo::leftClick(int mouseX, int mouseY) {
    //Definiciones de la librería GLU
     //Vectores intrínsecos en la librería
     //Hacen la conversión de coordenadas en 2D a 3D
    GLint viewport[4];               // X, Y, ANCHO, ALTURA DE LA PANTALLA
    GLdouble modelview[16];          // 4x4 CAMARA + MODELO DE VISTA
    GLdouble projection[16];         // 4x4 MATRIZ DE PROYECCION
    GLfloat depthZ;                  // PROFUNDIDAD DEL CLICK EN 3D
    GLdouble worldX, worldY, worldZ; // COORDENADAS 3D DEL MUNDO EN PANTALLA

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    // CONVERSION COORDENADAS DE PANTALLA (X,Y,Z) A TABLERO (X,Z) 
    //Lo que queremos conseguir en esta slíneas es convertir un click en la pantalla del usuario(en 2D), a una
    //posición en 3D del tablero, basicamente que pulsando la pantalla te diga que posición del tablero 3D fue
    //seleccionada
    //openGL empieza en esquina superior izquiera de la pantalla, y el eje Y va hacia abajo, por eso, mouseY
    //es igual a viewport[3] - mouseY, wiewport[3] es la altura de la pantalla y mouse Y es la posición del ratón
    //como empieza desde arriba, la posición 200, es en verdad la 600, de abajo arriba
    //mouse Y y mouse X, son variables locales de la función, en el cpp se hace que mouseY sea igual a la altura de la
    mouseY = viewport[3] - mouseY;
    //lee la profundidad, nos dice a qué distancia está el objto bajo el mouse, 1.0 sería "muye lejos" y 0.0 "muy cerca"
    glReadPixels(mouseX, mouseY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depthZ);
    //Transforma el pincho del mouse en coordenadas reales del sistema
    gluUnProject(mouseX, mouseY, depthZ,
        modelview,//Posición orientación de la cámara
        projection, //proyección 3D
        viewport, //Dimensiones d ela pantalla
        &worldX, &worldY, &worldZ); //Coordenadas de las teclas del ratón en el mundo

    //convertimos mundo en casillas del tablero
    //Convierte el click en la casilla del tablero
    int boardX = static_cast<int>(worldX - 0.5f);
    int boardZ = static_cast<int>(worldZ - 0.5f);

    //Verifica si el click está dentro del tablero y si se puede seleccionar
    if (boardX >= 0 && boardX < 5 && boardZ >= 0 && boardZ < 6 && clickFlag) {
        piezas.seleccionar(boardX, boardZ, turnFlag, platform);
    }
}
void Mundo::rightClick(int mouseX, int mouseY) {
    //Igual que antes
    GLint viewport[4];
    GLdouble modelview[16], projection[16];
    GLfloat depthZ = 0.0f;
    GLdouble worldX, worldY, worldZ;

    //Igual que antes
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    //Lo mismo que antes
    mouseY = viewport[3] - mouseY;
    glReadPixels(mouseX, mouseY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depthZ);
    gluUnProject(mouseX, mouseY, depthZ,
        modelview, projection, viewport,
        &worldX, &worldY, &worldZ);

    int boardX = static_cast<int>(worldX - 0.5f);
    int boardZ = static_cast<int>(worldZ - 0.5f);

    //Convierten el click a casillas del tablero
    vector2D destino = { static_cast<float>(boardX), static_cast<float>(boardZ) };
    //Verifica si el click está dentro del tablero y si se puede mover
    //Destino está en reglas.h
    if (destino.x >= 0 && destino.x < 5 && destino.z >= 0 && destino.z < 6) {
        //devuelve la selección de la pieza, con el método getSeleccion
        vector2D seleccion = piezas.getSeleccion();
        //Si la selección no es -1, significa que hay una pieza seleccionada
        if (seleccion.x != -1 && seleccion.z != -1) {
            //selección las he definido en piezas.seleccionar, estás selccionando las casillas que quieres mover,
            //las ponemos en 0 y definimos otra coordenadas de destino, borra la pieza de donde está y las imprime en
            //la de destino cumpliendo las reglas y estando dentro del tablero
            int piece = piezas.getBoard()[static_cast<int>(seleccion.x)][static_cast<int>(seleccion.z)];
            if ((turnFlag == 0 && piece > 0) || (turnFlag == 1 && piece < 0)) {
                if ((seleccion.z == destino.z && seleccion.x == destino.x) ||
                    !Reglas::moveChecker(piece, seleccion, destino, piezas.getBoard()))
                    return;
                //El destino
                piezas.getBoard()[static_cast<int>(destino.x)][static_cast<int>(destino.z)] = piece;
                piezas.getBoard()[static_cast<int>(seleccion.x)][static_cast<int>(seleccion.z)] = 0;
                imprimirMov(piece, seleccion, destino);

                //Deja de seleccionar una pieza y se seleccionan los cuadrados amarillos
                piezas.deseleccionar();
                platform.resetTileColors();
                turnFlag = !turnFlag;
                rotationFlag = true;
                //hay un nuevo target angles para que despues de cambiar la pieza se inicia el bucle
                targetAngle = angle + 3.14159265f;

               
                if (Reglas::jaque(turnFlag, piezas.getBoard(), platform.getTiles())) {
                    endFlag = true;
                    targetAngle = angle;
                    rotationFlag = false;
                }
                else if (Reglas::jaqueMate(!turnFlag, piezas.getBoard(), platform.getTiles())) {
                    endFlag = true;
                    turnFlag = !turnFlag;
                }
                else if (Reglas::jaque(!turnFlag, piezas.getBoard(), platform.getTiles())) {
                    jaqueFlag = true;
                    std::cout << "Jaque!\n";
                }
                else {
                    jaqueFlag = false;
                }
                //Control de la máquina, es el versus máquina
                //Es como: En caso de que estés en vs máquina
                if (endFlag == 0 && autopilotFlag && turnFlag) {
                    if (openingFlag) {
                        computer.makeMoveOpening(openingFlag, turnFlag, autopilotFlag, piezas.getBoard());
                        openingFlag = false;
                    }
                    else if (jaqueFlag) {
                        endFlag = !computer.makeMoveKingSafe(turnFlag, autopilotFlag, piezas.getBoard());
                    }
                    else {
                        endFlag = !computer.makeMove(turnFlag, autopilotFlag, piezas.getBoard());
                    }
                    turnFlag = !turnFlag;
                    targetAngle = angle;
                    rotationFlag = false;
                    if (Reglas::jaque(turnFlag, piezas.getBoard(), platform.getTiles())) {
                        endFlag = true;
                    }
                    else if (Reglas::jaqueMate(!turnFlag, piezas.getBoard(), platform.getTiles())) {
                        endFlag = true;
                        turnFlag = !turnFlag;
                    }
                    else if (Reglas::jaque(!turnFlag, piezas.getBoard(), platform.getTiles())) {
                        std::cout << "Jaque!\n";
                    }
                }
            }
        }
    }
    glutPostRedisplay();
    // COMPROBACION FIN DEL JUEGO.
    //Se comprueba si el juego ha terminado, y te sale un mensaje de cómo ha termiando la partida
    if (endFlag) {
        std::string winner = (turnFlag == 0) ? "BLANCO" : "NEGRO";
        std::cout << "Jaque Mate!\n";
        std::cout << "Ganador: " << winner << std::endl;
        menu.setWinner(winner);
        menu.setScores();
        currentScreen = GAME_OVER;
        return;
    }
}
//Te sale en pantalla lo que vas haciendo para que se registre
//Es un psudocódigo para saber donde están las cosas de forma escrita
void Mundo::imprimirMov(int piece, vector2D origen, vector2D destino) const {
    char turno = (turnFlag == 0) ? 'w' : 'b';
    char abrev = '?';
    switch (abs(piece)) {
    case 1: abrev = 'P'; break; // Peón
    case 2: abrev = 'R'; break; // Torre
    case 3: abrev = 'H'; break; // Caballo
    case 4: abrev = 'B'; break; // Alfil
    case 5: abrev = 'Q'; break; // Reina
    case 6: abrev = 'K'; break; // Rey
    default: break;
    }
    char col_orig = 'e' - static_cast<int>(origen.x);
    int row_orig = static_cast<int>(origen.z) + 1;
    char col_dest = 'e' - static_cast<int>(destino.x);
    int row_dest = static_cast<int>(destino.z) + 1;
    std::cout << turno << " " << abrev << " " << col_orig << row_orig << " " << col_dest << row_dest << std::endl;
}