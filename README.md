# CS2013-Project

Hex-Game

  <img src="https://github.com/CS1103/proyecto-final-proyecto_grupo9/blob/main/hex2.png">


Descripcion del Proyecto
- Hex es un juego de dos jugadores desarrollado sobre una tabla conformada por hexágonos cuya condición de victoria es conectar los lados opuestos de la tabla a través de marcas adyacentes respectivas a cada jugador.

  <img src="https://github.com/CS1103/proyecto-final-proyecto_grupo9/blob/main/hex1.jpeg">

- El programa buscará recrear el juego Hex e implementará a una IA que utilice el algoritmo alpha-beta pruning para decidir los movimientos que realizará en cada turno.

    <img src="https://github.com/CS1103/proyecto-final-proyecto_grupo9/blob/main/alfa_beta.png">


# Resumen del programa

- El programa consta de una matriz ‘board’ en donde se registran los movimientos en el que un jugador humano y la inteligencia artificial desarrollarán la partida. A partir de cada movimiento realizado por el humano, se ejecutará la función ‘next’ que se encargará de calcular el siguiente movimiento que deberá realizar la IA. Para realizar este cálculo se utilizará el algoritmo Alpha Beta Pruning, que permitirá determinar en un árbol de búsqueda el posible mejor movimiento a ejecutar.


:w::
- Adicionalmente, hemos hecho uso de la librería SFML para conseguir una representación más estilizada y llamativa del juego desarrollado. Para ello, se han diseñado las clases ‘Menu’ y ‘Options’, que permitirán la lectura de archivos con información sobre las palabras y botones que deberán mostrar.


# Diagrama UML de clases

- https://miro.com/app/board/uXjVOnzxSAM=/

<img src="https://github.com/CS1103/proyecto-final-proyecto_grupo9/blob/main/uml_diagram.png">

# Link de videos explicativos

- https://drive.google.com/drive/folders/1wcdquM1GDLbwqBkKtoB7NvTfxt-iX-La

# Bibliografia del programa
- https://www.whitman.edu/documents/Academics/Mathematics/2019/Felstiner-Guichard.pdf
- https://github.com/Khumquat1/Hex-Game-in-C-
- https://www.aaai.org/Papers/AAAI/2000/AAAI00-029.pdf
- https://reader.elsevier.com/reader/sd/pii/S0004370201001540?token=6506E2265E0AF62250ABDE31D8801D4B933DC3D21DCD7DED1D068DF8BDFEADB4A691C7D8B25F829D67C1801F651EBB6F&originRegion=us-east-1&originCreation=20220708061633
- http://hex.kosmanor.com/theory/y-hex.pdf
