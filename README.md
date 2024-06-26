# RegEx-to-NFA
Proyecto universitario

## ERRORES:
* Error de CMake / CMakeList para encontrar el ejecutable. <span style="color: green;">CORREGIDO</span>
* Errores de logica en las funciones de operadores. <span style="color: green;">CORREGIDO</span>
* Aparente error en la lectura de la regex. <span style="color: green;">CORREGIDO</span>
<span style="color: yellow;">
(Para una expresion regular cualquiera, el primer caracter operador (".", "+", "*") que lea provocara que la funccorrespondiente a este no funcione, y tenga que comentar la llamada a la funcion para que el programa pueda terminar de corcon normalidad. Al terminar de correr el programa con la funcion comentada, generara un archivo dot igual a cualquier otro cde correr el programa con alguna llamada a la funcion comentada.)
</span>

## CAMBIOS
* Se configuró CMakeList para la compilación del proyecto.
* El proyecto se compila desde la terminal de la siguiente forma:
`cd output`
`.\main.exe ..\regex.json ..\output.json`