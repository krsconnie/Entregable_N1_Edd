### Entregable_N1_Edd
Primer Entregable de laboratorio del ramo de "Estructura de Datos".

Este entregable tiene dos partes:

 1.La primera parte tiene relación con programación de clases. Se les pide incorporar los siguientes métodos nuevos:

        move_right(d): Desplaza la imagen d pixeles a la derecha
        move_up(d): Desplaza la imagen d pixeles hacia arriba
        move_down(d): Desplaza la imagen d pixeles hacia abajo
        rotate(): Rota la imagen 90 grados en sentido contrario a la agujas del reloj

2. La segunda parte tiene relación con estructuras de datos. Para esta parte es necesario que se complete la primera parte. Se pide implementar los siguientes métodos como parte de la clase:
   
        undo(): Deshace el último movimiento aplicado a la imagen (left,right,up,down o rotate)
        redo(): Rehace el último movimiento eliminado con undo()
        repeat(): Repite el último movimiento realizado
        repeat_all(): Repite todos los movimientos realizados sobre la imagen, desde su creación, incluyendo movimientos realizados al llamar a undo(), redo() y repeat(). Por cada movimiento repetido se debe generar una imagen png. El objetivo de este método es generar una "película" con todos los movimientos aplicados a la imagen (algo así como un historial de movimientos).

Los métodos de la segunda parte deben ser implementados usando stacks (pilas) o queues (filas).
Pueden usar estructuras de la STL de C++ o implementar sus propias variantes.

